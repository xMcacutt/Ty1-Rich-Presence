// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "../TygerFrameworkAPI.hpp"
#include "core.h"
#include <windows.h>
#include "discord_rpc.h"
#include "discord.h"
#include "gamestate.h"
#include "hooks.h"

using namespace std;

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

void OnTyInit() {
	discord& discordInstance = discord::getInstance();
	discordInstance.InitDiscord();
	discordInstance.UpdateDiscordPresence("On Main Menu", "", "");
	hooks& hooksInstance = hooks::getInstance();
	hooksInstance.SetupHooks();
}

bool onMenu = true;
bool prevOnMenu = true;
void TickBeforeGame(float seconds) {
	onMenu = GameState::onMainMenu();
	if (onMenu != prevOnMenu)
	{	
		if (onMenu) {
			discord& discordInstance = discord::getInstance();
			discordInstance.UpdateDiscordPresence("On Main Menu", "", "");
		}
		prevOnMenu = onMenu;
	}
}

extern "C" __declspec(dllexport) bool TygerFrameworkPluginInitialize(TygerFrameworkPluginInitializeParam* param) {
    if (!API::Initialize(param))
        return false;
    Core::initialize((HMODULE)API::Get()->param()->TyHModule);
	API::AddOnTyInitialized(OnTyInit);
	API::AddTickBeforeGame(TickBeforeGame);
    return true;
}

extern "C" __declspec(dllexport) void TygerFrameworkPluginRequiredVersion(TygerFrameworkPluginVersion* version) {
    version->Major = 1;
    version->Minor = 1;
    version->Patch = 3;
}