
#include "hookutils.h"
#include "MinHook.h"
#include <iostream>

void HookEnabler::CreateHook(LPVOID ppTarget, LPVOID ppDetour, LPVOID* ppOriginal, const char* targetName)
{
	// the macro for this uses ppTarget's name as targetName, and this typically starts with &
	// targetname is used for debug stuff and debug output is nicer if we don't have this
	if (*targetName == '&')
		targetName++;

	if (MH_CreateHook(ppTarget, ppDetour, ppOriginal) == MH_OK)
	{
		HookTarget* target = new HookTarget;
		target->targetAddress = ppTarget;
		target->targetName = (char*)targetName;

		m_hookTargets.push_back(target);
	}
	else
	{
		if (targetName != nullptr)
			std::cerr << "MH_CreateHook failed for function {}" << targetName;
		else
			std::cerr << "MH_CreateHook failed for unknown function";
	}
}

HookEnabler::~HookEnabler()
{
	for (auto& hook : m_hookTargets)
	{
		if (MH_EnableHook(hook->targetAddress) != MH_OK)
		{
			if (hook->targetName != nullptr)
				std::cerr << "MH_EnableHook failed for function {}" << hook->targetName;
			else
				std::cerr << "MH_EnableHook failed for unknown function";
		}
		else
			std::cout << "Enabling hook {}" << hook->targetName;
	}
}