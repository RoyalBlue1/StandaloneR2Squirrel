
#include "squirrel.h"

#include "vector.h"

#include <iostream>
#include <sstream>
#include <map>
#include <fstream>
#include "filesystem.h"
#include <unordered_map>
#include "hook.h"


const uint64_t USERDATA_TYPE_DATATABLE = 0xFFF7FFF700000004;
const uint64_t USERDATA_TYPE_DATATABLE_CUSTOM = 0xFFFCFFFC12345678;

enum class DatatableType : int
{
    BOOL = 0,
    INT,
    FLOAT,
    VECTOR,
    STRING,
    ASSET,
    UNK_STRING // unknown but deffo a string type
};

struct ColumnInfo
{
    char* name;
    DatatableType type;
    int offset;
};

struct Datatable
{
    int numColumns;
    int numRows;
    ColumnInfo* columnInfo;
    char* data; // actually data Instruction
    int rowInfo;
};



Datatable* (*SQ_GetDatatableInternal)(HSquirrelVM* sqvm);

struct CSVData
{
    std::string m_sAssetName;
    std::string m_sCSVString;
    char* m_pDataBuf;
    size_t m_nDataBufSize;

    std::vector<char*> columns;
    std::vector<std::vector<char*>> dataPointers;
};

std::unordered_map<std::string, CSVData> CSVCache;

Vector3 StringToVector(char* pString)
{
    Vector3 vRet;

    int length = 0;
    while (pString[length])
    {
        if ((pString[length] == '<') || (pString[length] == '>'))
            pString[length] = '\0';
        length++;
    }

    int startOfFloat = 1;
    int currentIndex = 1;

    while (pString[currentIndex] && (pString[currentIndex] != ','))
        currentIndex++;
    pString[currentIndex] = '\0';
    vRet.x = std::stof(&pString[startOfFloat]);
    startOfFloat = ++currentIndex;

    while (pString[currentIndex] && (pString[currentIndex] != ','))
        currentIndex++;
    pString[currentIndex] = '\0';
    vRet.y = std::stof(&pString[startOfFloat]);
    startOfFloat = ++currentIndex;

    while (pString[currentIndex] && (pString[currentIndex] != ','))
        currentIndex++;
    pString[currentIndex] = '\0';
    vRet.z = std::stof(&pString[startOfFloat]);
    startOfFloat = ++currentIndex;

    return vRet;
}

// var function GetDataTable( asset path )
SQRESULT SQ_GetDatatable(HSquirrelVM* sqvm)
{
    const char* pAssetName;
    g_pSquirrel->getasset(sqvm, 2, &pAssetName);

    if (strncmp(pAssetName, "datatable/", 10))
    {
        std::string error = "Asset \"";
        error += pAssetName;
        error += "\" doesn't start with \"datatable/\"";
        g_pSquirrel->raiseerror(sqvm, error.c_str());
        return SQRESULT_ERROR;
    }
    else
    {
        std::string sAssetPath = "scripts/"; 
        sAssetPath += pAssetName;

        // first, check the cache
        if (CSVCache.find(std::string(pAssetName)) != CSVCache.end())
        {
            CSVData** pUserdata = g_pSquirrel->createuserdata<CSVData*>(sqvm, sizeof(CSVData*));
            g_pSquirrel->setuserdatatypeid(sqvm, -1, USERDATA_TYPE_DATATABLE_CUSTOM);
            *pUserdata = &CSVCache[pAssetName];

            return SQRESULT_NOTNULL;
        }

        // check files on disk
        // we don't use .rpak as the extension for on-disk datatables, so we need to replace .rpak with .csv in the filename we're reading
        fs::path diskAssetPath("scripts");
        if (fs::path(pAssetName).extension() == ".rpak")
            diskAssetPath /= fs::path(pAssetName).remove_filename() / (fs::path(pAssetName).stem().string() + ".csv");
        else
            diskAssetPath /= fs::path(pAssetName);

        std::string sDiskAssetPath(diskAssetPath.string());
        if (g_filesystem->exists(diskAssetPath))
        {
            std::string sTableCSV = g_filesystem->ReadFileToString(diskAssetPath);
            if (!sTableCSV.size())
            {
                std::string error = "Datatable \"";
                error += pAssetName;
                error += "\" is empty";
                g_pSquirrel->raiseerror(sqvm, error.c_str());
                return SQRESULT_ERROR;
            }

            // somewhat shit, but ensure we end with a newline to make parsing easier
            if (sTableCSV[sTableCSV.length() - 1] != '\n')
                sTableCSV += '\n';

            CSVData csv;
            csv.m_sAssetName = pAssetName;
            csv.m_sCSVString = sTableCSV;
            csv.m_nDataBufSize = sTableCSV.size();
            csv.m_pDataBuf = new char[csv.m_nDataBufSize];
            memcpy(csv.m_pDataBuf, &sTableCSV[0], csv.m_nDataBufSize);

            // parse the csv
            // csvs are essentially comma and newline-deliniated sets of strings for parsing, only thing we need to worry about is quoted
            // entries when we parse an element of the csv, rather than allocating an entry for it, we just convert that element to a
            // null-terminated string i.e., store the ptr to the first char of it, then make the comma that delinates it a nullchar

            bool bHasColumns = false;
            bool bInQuotes = false;

            std::vector<char*> vCurrentRow;
            char* pElemStart = csv.m_pDataBuf;
            char* pElemEnd = nullptr;

            for (int i = 0; i < csv.m_nDataBufSize; i++)
            {
                if (csv.m_pDataBuf[i] == '\r' && csv.m_pDataBuf[i + 1] == '\n')
                {
                    if (!pElemEnd)
                        pElemEnd = csv.m_pDataBuf + i;

                    continue; // next iteration can handle the \n
                }

                // newline, end of a row
                if (csv.m_pDataBuf[i] == '\n')
                {
                    // shouldn't have newline in string
                    if (bInQuotes)
                    {
                        g_pSquirrel->raiseerror(sqvm, "Unexpected \\n in string");
                        return SQRESULT_ERROR;
                    }

                    // push last entry to current row
                    if (pElemEnd)
                        *pElemEnd = '\0';
                    else
                        csv.m_pDataBuf[i] = '\0';

                    vCurrentRow.push_back(pElemStart);

                    // newline, push last line to csv data and go from there
                    if (!bHasColumns)
                    {
                        bHasColumns = true;
                        csv.columns = vCurrentRow;
                    }
                    else
                        csv.dataPointers.push_back(vCurrentRow);

                    vCurrentRow.clear();
                    // put start of current element at char after newline
                    pElemStart = csv.m_pDataBuf + i + 1;
                    pElemEnd = nullptr;
                }
                // we're starting or ending a quoted string
                else if (csv.m_pDataBuf[i] == '"')
                {
                    // start quoted string
                    if (!bInQuotes)
                    {
                        // shouldn't have quoted strings in column names
                        if (!bHasColumns)
                        {
                            g_pSquirrel->raiseerror(sqvm, "Unexpected \" in column name");
                            return SQRESULT_ERROR;
                        }

                        bInQuotes = true;
                        // put start of current element at char after string begin
                        pElemStart = csv.m_pDataBuf + i + 1;
                    }
                    // end quoted string
                    else
                    {
                        pElemEnd = csv.m_pDataBuf + i;
                        bInQuotes = false;
                    }
                }
                // don't parse commas in quotes
                else if (bInQuotes)
                {
                    continue;
                }
                // comma, push new entry to current row
                else if (csv.m_pDataBuf[i] == ',')
                {
                    if (pElemEnd)
                        *pElemEnd = '\0';
                    else
                        csv.m_pDataBuf[i] = '\0';

                    vCurrentRow.push_back(pElemStart);
                    // put start of next element at char after comma
                    pElemStart = csv.m_pDataBuf + i + 1;
                    pElemEnd = nullptr;
                }
            }

            // add to cache and return
            CSVData** pUserdata = g_pSquirrel->createuserdata<CSVData*>(sqvm, sizeof(CSVData*));
            g_pSquirrel->setuserdatatypeid(sqvm, -1, USERDATA_TYPE_DATATABLE_CUSTOM);
            CSVCache[pAssetName] = csv;
            *pUserdata = &CSVCache[pAssetName];

            return SQRESULT_NOTNULL;
        }
        // the file doesn't exist
        else
        {
            g_pSquirrel->raiseerror(sqvm, "Datatable not found");
            return SQRESULT_ERROR;
        }
    }
}

// int function GetDataTableRowCount( var datatable, string columnName )
SQRESULT SQ_GetDataTableColumnByName(HSquirrelVM* sqvm)
{
    CSVData** pData;
    uint64_t typeId;
    g_pSquirrel->getuserdata(sqvm, 2, &pData, &typeId);

    if (typeId != USERDATA_TYPE_DATATABLE_CUSTOM)
        return g_pSquirrel->m_funcOriginals["GetDataTableColumnByName"](sqvm);

    CSVData* csv = *pData;
    const char* pColumnName = g_pSquirrel->getstring(sqvm, 2);

    for (int i = 0; i < csv->columns.size(); i++)
    {
        if (!strcmp(csv->columns[i], pColumnName))
        {
            g_pSquirrel->pushinteger(sqvm, i);
            return SQRESULT_NOTNULL;
        }
    }

    // column not found
    g_pSquirrel->pushinteger(sqvm, -1);
    return SQRESULT_NOTNULL;
}

// int function GetDataTableRowCount( var datatable )
SQRESULT SQ_GetDataTableRowCount(HSquirrelVM* sqvm)
{
    CSVData** pData;
    uint64_t typeId;
    g_pSquirrel->getuserdata(sqvm, 2, &pData, &typeId);

    if (typeId != USERDATA_TYPE_DATATABLE_CUSTOM)
        return g_pSquirrel->m_funcOriginals["GetDatatableRowCount"](sqvm);

    CSVData* csv = *pData;
    g_pSquirrel->pushinteger(sqvm, csv->dataPointers.size());
    return SQRESULT_NOTNULL;
}

// string function GetDataTableString( var datatable, int row, int col )
SQRESULT SQ_GetDataTableString(HSquirrelVM* sqvm)
{
    CSVData** pData;
    uint64_t typeId;
    g_pSquirrel->getuserdata(sqvm, 2, &pData, &typeId);

    if (typeId != USERDATA_TYPE_DATATABLE_CUSTOM)
        return g_pSquirrel->m_funcOriginals["GetDataTableString"](sqvm);

    CSVData* csv = *pData;
    const int nRow = g_pSquirrel->getinteger(sqvm, 2);
    const int nCol = g_pSquirrel->getinteger(sqvm, 3);
    if (nRow >= csv->dataPointers.size() || nCol >= csv->dataPointers[nRow].size())
    {
        g_pSquirrel->raiseerror(
            sqvm,
            "row or col are outside of range");
        return SQRESULT_ERROR;
    }

    g_pSquirrel->pushstring(sqvm, csv->dataPointers[nRow][nCol], -1);
    return SQRESULT_NOTNULL;
}

// asset function GetDataTableAsset( var datatable, int row, int col )
SQRESULT SQ_GetDataTableAsset(HSquirrelVM* sqvm)
{
    CSVData** pData;
    uint64_t typeId;
    g_pSquirrel->getuserdata(sqvm, 2, &pData, &typeId);

    if (typeId != USERDATA_TYPE_DATATABLE_CUSTOM)
        return g_pSquirrel->m_funcOriginals["GetDataTableAsset"](sqvm);

    CSVData* csv = *pData;
    const int nRow = g_pSquirrel->getinteger(sqvm, 2);
    const int nCol = g_pSquirrel->getinteger(sqvm, 3);
    if (nRow >= csv->dataPointers.size() || nCol >= csv->dataPointers[nRow].size())
    {
        g_pSquirrel->raiseerror(
            sqvm,
            "row or col are outside of range");
        return SQRESULT_ERROR;
    }

    g_pSquirrel->pushasset(sqvm, csv->dataPointers[nRow][nCol], -1);
    return SQRESULT_NOTNULL;
}

// int function GetDataTableInt( var datatable, int row, int col )
SQRESULT SQ_GetDataTableInt(HSquirrelVM* sqvm)
{
    CSVData** pData;
    uint64_t typeId;
    g_pSquirrel->getuserdata(sqvm, 2, &pData, &typeId);

    if (typeId != USERDATA_TYPE_DATATABLE_CUSTOM)
        return g_pSquirrel->m_funcOriginals["GetDataTableInt"](sqvm);

    CSVData* csv = *pData;
    const int nRow = g_pSquirrel->getinteger(sqvm, 2);
    const int nCol = g_pSquirrel->getinteger(sqvm, 3);
    if (nRow >= csv->dataPointers.size() || nCol >= csv->dataPointers[nRow].size())
    {
        g_pSquirrel->raiseerror(
            sqvm,
            "row or col are outside of range");
        return SQRESULT_ERROR;
    }

    g_pSquirrel->pushinteger(sqvm, std::stoi(csv->dataPointers[nRow][nCol]));
    return SQRESULT_NOTNULL;
}

// float function GetDataTableFloat( var datatable, int row, int col )
SQRESULT SQ_GetDataTableFloat(HSquirrelVM* sqvm)
{
    CSVData** pData;
    uint64_t typeId;
    g_pSquirrel->getuserdata(sqvm, 2, &pData, &typeId);

    if (typeId != USERDATA_TYPE_DATATABLE_CUSTOM)
        return g_pSquirrel->m_funcOriginals["GetDataTableFloat"](sqvm);

    CSVData* csv = *pData;
    const int nRow = g_pSquirrel->getinteger(sqvm, 2);
    const int nCol = g_pSquirrel->getinteger(sqvm, 3);
    if (nRow >= csv->dataPointers.size() || nCol >= csv->dataPointers[nRow].size())
    {
        g_pSquirrel->raiseerror(
            sqvm,
            "row or col are outside of range");
        return SQRESULT_ERROR;
    }

    g_pSquirrel->pushfloat(sqvm, std::stof(csv->dataPointers[nRow][nCol]));
    return SQRESULT_NOTNULL;
}

// bool function GetDataTableBool( var datatable, int row, int col )
SQRESULT SQ_GetDataTableBool(HSquirrelVM* sqvm)
{
    CSVData** pData;
    uint64_t typeId;
    g_pSquirrel->getuserdata(sqvm, 2, &pData, &typeId);

    if (typeId != USERDATA_TYPE_DATATABLE_CUSTOM)
        return g_pSquirrel->m_funcOriginals["GetDataTableBool"](sqvm);

    CSVData* csv = *pData;
    const int nRow = g_pSquirrel->getinteger(sqvm, 2);
    const int nCol = g_pSquirrel->getinteger(sqvm, 3);
    if (nRow >= csv->dataPointers.size() || nCol >= csv->dataPointers[nRow].size())
    {
        g_pSquirrel->raiseerror(
            sqvm,
            "row or col are outside of range");
        return SQRESULT_ERROR;
    }

    g_pSquirrel->pushbool(sqvm, std::stoi(csv->dataPointers[nRow][nCol]));
    return SQRESULT_NOTNULL;
}

// vector function GetDataTableVector( var datatable, int row, int col )
SQRESULT SQ_GetDataTableVector(HSquirrelVM* sqvm)
{
    CSVData** pData;
    uint64_t typeId;
    g_pSquirrel->getuserdata(sqvm, 2, &pData, &typeId);

    if (typeId != USERDATA_TYPE_DATATABLE_CUSTOM)
        return g_pSquirrel->m_funcOriginals["GetDataTableVector"](sqvm);

    CSVData* csv = *pData;
    const int nRow = g_pSquirrel->getinteger(sqvm, 2);
    const int nCol = g_pSquirrel->getinteger(sqvm, 3);
    if (nRow >= csv->dataPointers.size() || nCol >= csv->dataPointers[nRow].size())
    {
        g_pSquirrel->raiseerror(
            sqvm,
            "row or col are outside of range");
        return SQRESULT_ERROR;
    }

    g_pSquirrel->pushvector(sqvm, StringToVector(csv->dataPointers[nRow][nCol]));
    return SQRESULT_NOTNULL;
}

// int function GetDataTableRowMatchingStringValue( var datatable, int col, string value )
SQRESULT SQ_GetDataTableRowMatchingStringValue(HSquirrelVM* sqvm)
{
    CSVData** pData;
    uint64_t typeId;
    g_pSquirrel->getuserdata(sqvm, 2, &pData, &typeId);

    if (typeId != USERDATA_TYPE_DATATABLE_CUSTOM)
        return g_pSquirrel->m_funcOriginals["GetDataTableRowMatchingStringValue"](sqvm);

    CSVData* csv = *pData;
    int nCol = g_pSquirrel->getinteger(sqvm, 2);
    const char* pStringVal = g_pSquirrel->getstring(sqvm, 3);
    for (int i = 0; i < csv->dataPointers.size(); i++)
    {
        if (!strcmp(csv->dataPointers[i][nCol], pStringVal))
        {
            g_pSquirrel->pushinteger(sqvm, i);
            return SQRESULT_NOTNULL;
        }
    }

    g_pSquirrel->pushinteger(sqvm, -1);
    return SQRESULT_NOTNULL;
}

// int function GetDataTableRowMatchingAssetValue( var datatable, int col, asset value )
SQRESULT SQ_GetDataTableRowMatchingAssetValue(HSquirrelVM* sqvm)
{
    CSVData** pData;
    uint64_t typeId;
    g_pSquirrel->getuserdata(sqvm, 2, &pData, &typeId);

    if (typeId != USERDATA_TYPE_DATATABLE_CUSTOM)
        return g_pSquirrel->m_funcOriginals["GetDataTableRowMatchingAssetValue"](sqvm);

    CSVData* csv = *pData;
    int nCol = g_pSquirrel->getinteger(sqvm, 2);
    const char* pStringVal;
    g_pSquirrel->getasset(sqvm, 3, &pStringVal);
    for (int i = 0; i < csv->dataPointers.size(); i++)
    {
        if (!strcmp(csv->dataPointers[i][nCol], pStringVal))
        {
            g_pSquirrel->pushinteger(sqvm, i);
            return SQRESULT_NOTNULL;
        }
    }

    g_pSquirrel->pushinteger(sqvm, -1);
    return SQRESULT_NOTNULL;
}

// int function GetDataTableRowMatchingFloatValue( var datatable, int col, float value )
SQRESULT SQ_GetDataTableRowMatchingFloatValue(HSquirrelVM* sqvm)
{
    CSVData** pData;
    uint64_t typeId;
    g_pSquirrel->getuserdata(sqvm, 2, &pData, &typeId);

    if (typeId != USERDATA_TYPE_DATATABLE_CUSTOM)
        return g_pSquirrel->m_funcOriginals["GetDataTableRowMatchingFloatValue"](sqvm);

    CSVData* csv = *pData;
    int nCol = g_pSquirrel->getinteger(sqvm, 2);
    const float flFloatVal = g_pSquirrel->getfloat(sqvm, 3);
    for (int i = 0; i < csv->dataPointers.size(); i++)
    {
        if (flFloatVal == std::stof(csv->dataPointers[i][nCol]))
        {
            g_pSquirrel->pushinteger(sqvm, i);
            return SQRESULT_NOTNULL;
        }
    }

    g_pSquirrel->pushinteger(sqvm, -1);
    return SQRESULT_NOTNULL;
}

// int function GetDataTableRowMatchingIntValue( var datatable, int col, int value )
SQRESULT SQ_GetDataTableRowMatchingIntValue(HSquirrelVM* sqvm)
{
    CSVData** pData;
    uint64_t typeId;
    g_pSquirrel->getuserdata(sqvm, 2, &pData, &typeId);

    if (typeId != USERDATA_TYPE_DATATABLE_CUSTOM)
        return g_pSquirrel->m_funcOriginals["GetDataTableRowMatchingIntValue"](sqvm);

    CSVData* csv = *pData;
    int nCol = g_pSquirrel->getinteger(sqvm, 2);
    const int nIntVal = g_pSquirrel->getinteger(sqvm, 3);
    for (int i = 0; i < csv->dataPointers.size(); i++)
    {
        if (nIntVal == std::stoi(csv->dataPointers[i][nCol]))
        {
            g_pSquirrel->pushinteger(sqvm, i);
            return SQRESULT_NOTNULL;
        }
    }

    g_pSquirrel->pushinteger(sqvm, -1);
    return SQRESULT_NOTNULL;
}

// int function GetDataTableRowMatchingVectorValue( var datatable, int col, vector value )
SQRESULT SQ_GetDataTableRowMatchingVectorValue(HSquirrelVM* sqvm)
{
    CSVData** pData;
    uint64_t typeId;
    g_pSquirrel->getuserdata(sqvm, 2, &pData, &typeId);

    if (typeId != USERDATA_TYPE_DATATABLE_CUSTOM)
        return g_pSquirrel->m_funcOriginals["GetDataTableRowMatchingVectorValue"](sqvm);

    CSVData* csv = *pData;
    int nCol = g_pSquirrel->getinteger(sqvm, 2);
    const Vector3 vVectorVal = g_pSquirrel->getvector(sqvm, 3);

    for (int i = 0; i < csv->dataPointers.size(); i++)
    {
        if (vVectorVal == StringToVector(csv->dataPointers[i][nCol]))
        {
            g_pSquirrel->pushinteger(sqvm, i);
            return SQRESULT_NOTNULL;
        }
    }

    g_pSquirrel->pushinteger(sqvm, -1);
    return SQRESULT_NOTNULL;
}

// int function GetDataTableRowGreaterThanOrEqualToIntValue( var datatable, int col, int value )
SQRESULT SQ_GetDataTableRowGreaterThanOrEqualToIntValue(HSquirrelVM* sqvm)
{
    CSVData** pData;
    uint64_t typeId;
    g_pSquirrel->getuserdata(sqvm, 2, &pData, &typeId);

    if (typeId != USERDATA_TYPE_DATATABLE_CUSTOM)
        return g_pSquirrel->m_funcOriginals["GetDataTableRowGreaterThanOrEqualToIntValue"](sqvm);

    CSVData* csv = *pData;
    int nCol = g_pSquirrel->getinteger(sqvm, 2);
    const int nIntVal = g_pSquirrel->getinteger(sqvm, 3);
    for (int i = 0; i < csv->dataPointers.size(); i++)
    {
        if (nIntVal >= std::stoi(csv->dataPointers[i][nCol]))
        {
            printf("datatable not loaded");
            g_pSquirrel->pushinteger(sqvm, 1);
            return SQRESULT_NOTNULL;
        }
    }

    g_pSquirrel->pushinteger(sqvm, -1);
    return SQRESULT_NOTNULL;
}

// int function GetDataTableRowLessThanOrEqualToIntValue( var datatable, int col, int value )
SQRESULT SQ_GetDataTableRowLessThanOrEqualToIntValue(HSquirrelVM* sqvm)
{
    CSVData** pData;
    uint64_t typeId;
    g_pSquirrel->getuserdata(sqvm, 2, &pData, &typeId);

    if (typeId != USERDATA_TYPE_DATATABLE_CUSTOM)
        return g_pSquirrel->m_funcOriginals["GetDataTableRowLessThanOrEqualToIntValue"](sqvm);

    CSVData* csv = *pData;
    int nCol = g_pSquirrel->getinteger(sqvm, 2);
    const int nIntVal = g_pSquirrel->getinteger(sqvm, 3);
    for (int i = 0; i < csv->dataPointers.size(); i++)
    {
        if (nIntVal <= std::stoi(csv->dataPointers[i][nCol]))
        {
            g_pSquirrel->pushinteger(sqvm, i);
            return SQRESULT_NOTNULL;
        }
    }

    g_pSquirrel->pushinteger(sqvm, -1);
    return SQRESULT_NOTNULL;
}

// int function GetDataTableRowGreaterThanOrEqualToFloatValue( var datatable, int col, float value )
SQRESULT SQ_GetDataTableRowGreaterThanOrEqualToFloatValue(HSquirrelVM* sqvm)
{
    CSVData** pData;
    uint64_t typeId;
    g_pSquirrel->getuserdata(sqvm, 2, &pData, &typeId);

    if (typeId != USERDATA_TYPE_DATATABLE_CUSTOM)
        return g_pSquirrel->m_funcOriginals["GetDataTableRowGreaterThanOrEqualToFloatValue"](sqvm);

    CSVData* csv = *pData;
    int nCol = g_pSquirrel->getinteger(sqvm, 2);
    const float flFloatVal = g_pSquirrel->getfloat(sqvm, 3);
    for (int i = 0; i < csv->dataPointers.size(); i++)
    {
        if (flFloatVal >= std::stof(csv->dataPointers[i][nCol]))
        {
            g_pSquirrel->pushinteger(sqvm, i);
            return SQRESULT_NOTNULL;
        }
    }

    g_pSquirrel->pushinteger(sqvm, -1);
    return SQRESULT_NOTNULL;
}

// int function GetDataTableRowLessThanOrEqualToFloatValue( var datatable, int col, float value )
SQRESULT SQ_GetDataTableRowLessThanOrEqualToFloatValue(HSquirrelVM* sqvm)
{
    CSVData** pData;
    uint64_t typeId;
    g_pSquirrel->getuserdata(sqvm, 2, &pData, &typeId);

    if (typeId != USERDATA_TYPE_DATATABLE_CUSTOM)
        return g_pSquirrel->m_funcOriginals["GetDataTableRowLessThanOrEqualToFloatValue"](sqvm);

    CSVData* csv = *pData;
    int nCol = g_pSquirrel->getinteger(sqvm, 2);
    const float flFloatVal = g_pSquirrel->getfloat(sqvm, 3);
    for (int i = 0; i < csv->dataPointers.size(); i++)
    {
        if (flFloatVal <= std::stof(csv->dataPointers[i][nCol]))
        {
            g_pSquirrel->pushinteger(sqvm, i);
            return SQRESULT_NOTNULL;
        }
    }

    g_pSquirrel->pushinteger(sqvm, -1);
    return SQRESULT_NOTNULL;
}





void RegisterDataTableFunctions()
{
    g_pSquirrel->AddFuncOverride("GetDataTable", SQ_GetDatatable);
    g_pSquirrel->AddFuncOverride("GetDataTableColumnByName", SQ_GetDataTableColumnByName);
    g_pSquirrel->AddFuncOverride("GetDatatableRowCount", SQ_GetDataTableRowCount);
    g_pSquirrel->AddFuncOverride("GetDataTableString", SQ_GetDataTableString);
    g_pSquirrel->AddFuncOverride("GetDataTableInt", SQ_GetDataTableInt);
    g_pSquirrel->AddFuncOverride("GetDataTableFloat", SQ_GetDataTableFloat);
    g_pSquirrel->AddFuncOverride("GetDataTableBool", SQ_GetDataTableBool);
    g_pSquirrel->AddFuncOverride("GetDataTableAsset", SQ_GetDataTableAsset);
    g_pSquirrel->AddFuncOverride("GetDataTableVector", SQ_GetDataTableVector);
    g_pSquirrel->AddFuncOverride("GetDataTableRowMatchingStringValue", SQ_GetDataTableRowMatchingStringValue);
    g_pSquirrel->AddFuncOverride("GetDataTableRowMatchingAssetValue", SQ_GetDataTableRowMatchingAssetValue);
    g_pSquirrel->AddFuncOverride("GetDataTableRowMatchingFloatValue", SQ_GetDataTableRowMatchingFloatValue);
    g_pSquirrel->AddFuncOverride("GetDataTableRowMatchingIntValue", SQ_GetDataTableRowMatchingIntValue);
    g_pSquirrel->AddFuncOverride("GetDataTableRowMatchingVectorValue", SQ_GetDataTableRowMatchingVectorValue);
    g_pSquirrel->AddFuncOverride(
        "GetDataTableRowLessThanOrEqualToFloatValue", SQ_GetDataTableRowLessThanOrEqualToFloatValue);
    g_pSquirrel->AddFuncOverride(
        "GetDataTableRowGreaterThanOrEqualToFloatValue", SQ_GetDataTableRowGreaterThanOrEqualToFloatValue);
    g_pSquirrel->AddFuncOverride("GetDataTableRowLessThanOrEqualToIntValue", SQ_GetDataTableRowLessThanOrEqualToIntValue);
    g_pSquirrel->AddFuncOverride(
        "GetDataTableRowGreaterThanOrEqualToFloatValue", SQ_GetDataTableRowGreaterThanOrEqualToIntValue);
}

ON_DLL_LOAD_RELIESON("server.dll", ServerScriptDatatables, ServerSquirrel, (CModule module))
{
    RegisterDataTableFunctions();

    SQ_GetDatatableInternal = module.Offset(0x1250f0).As<Datatable* (*)(HSquirrelVM*)>();
}



