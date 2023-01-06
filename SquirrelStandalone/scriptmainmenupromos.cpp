#include "hook.h"
#include "squirrel.h"


// mirror this in script
enum eMainMenuPromoDataProperty
{
    newInfoTitle1,
    newInfoTitle2,
    newInfoTitle3,

    largeButtonTitle,
    largeButtonText,
    largeButtonUrl,
    largeButtonImageIndex,

    smallButton1Title,
    smallButton1Url,
    smallButton1ImageIndex,

    smallButton2Title,
    smallButton2Url,
    smallButton2ImageIndex
};

// void function NSRequestCustomMainMenuPromos()
SQRESULT SQ_RequestCustomMainMenuPromos(HSquirrelVM* sqvm)
{
    return SQRESULT_NULL;
}

// bool function NSHasCustomMainMenuPromoData()
SQRESULT SQ_HasCustomMainMenuPromoData(HSquirrelVM* sqvm)
{
    return SQRESULT_NOTNULL;
}

// var function NSGetCustomMainMenuPromoData( int promoDataKey )
SQRESULT SQ_GetCustomMainMenuPromoData(HSquirrelVM* sqvm)
{
    return SQRESULT_NOTNULL;
}
/*
ON_DLL_LOAD_RELIESON("client.dll", ScriptMainMenuPromos, ClientSquirrel, (CModule module))
{
    g_pSquirrel<ScriptContext::UI>->AddFuncRegistration("void", "NSRequestCustomMainMenuPromos", "", "", SQ_RequestCustomMainMenuPromos);
    g_pSquirrel<ScriptContext::UI>->AddFuncRegistration("bool", "NSHasCustomMainMenuPromoData", "", "", SQ_HasCustomMainMenuPromoData);
    g_pSquirrel<ScriptContext::UI>->AddFuncRegistration(
        "var", "NSGetCustomMainMenuPromoData", "int promoDataKey", "", SQ_GetCustomMainMenuPromoData);
}
*/