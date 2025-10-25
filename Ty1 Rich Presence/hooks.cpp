#include "pch.h"
#include "hooks.h"

typedef void(__stdcall* FunctionType)();
FunctionType changeLevelOrigin = nullptr;
FunctionType changeTheggsOrigin = nullptr;

std::string currentLevelName = "";
std::string currentThunderEggs = "";

uintptr_t changeLevelOriginAddr;
__declspec(naked) void __stdcall hooks::ChangeLevelHook() {
	__asm {
		pushfd
		pushad
		push eax
		call hooks::OnChangeLevel
		pop eax
		popad
		popfd
		mov [edx+0xAA4],eax
		jmp dword ptr[changeLevelOriginAddr]
	}
}

uintptr_t changeTheggsOriginAddr;
__declspec(naked) void __stdcall hooks::ChangeTheggsHook() {
	__asm {
		pushfd
		pushad
		push eax
		call hooks::OnChangeTheggs
		pop eax
		popad
		popfd
		xor ecx,ebp
		mov eax,[edi+0x2C]
		jmp dword ptr[changeTheggsOriginAddr]
	}
}

void hooks::SetupHooks() {
	MH_Initialize();
	changeLevelOriginAddr = Core::moduleBase + 0xF7DF2;
	auto addr = (char*)(Core::moduleBase + 0xF7DEC);
	MH_CreateHook((LPVOID)addr, &ChangeLevelHook, reinterpret_cast<LPVOID*>(&changeLevelOrigin));
	changeTheggsOriginAddr = Core::moduleBase + 0xF7471;
	addr = (char*)(Core::moduleBase + 0xF746C);
	MH_CreateHook((LPVOID)addr, &ChangeTheggsHook, reinterpret_cast<LPVOID*>(&changeTheggsOrigin));
	MH_EnableHook(MH_ALL_HOOKS);
}

static std::string formatNameForImageKey(const std::string& name) {
	std::string formattedName;
	formattedName.reserve(name.size()); 
	for (char c : name) {
		if (std::isalnum(static_cast<unsigned char>(c))) {
			formattedName += std::tolower(static_cast<unsigned char>(c));
		}
	}
	return formattedName;
}

void hooks::OnChangeLevel(int level) {
	auto& hooksInstance = hooks::getInstance();
	LevelCode newLevel = static_cast<LevelCode>(level);
	hooksInstance.currentLevelName = hooksInstance.getLevelName(newLevel);
}

void hooks::OnChangeTheggs(int count) {
	if (GameState::onMainMenu())
		return;
	auto& hooksInstance = hooks::getInstance();
	hooksInstance.currentThunderEggs = std::to_string(count) + " Thunder Eggs";
	hooksInstance.UpdateDiscord();
}

void hooks::UpdateDiscord() {
	auto& discordInstance = discord::getInstance();
	discordInstance.UpdateDiscordPresence(currentThunderEggs, currentLevelName.c_str(), formatNameForImageKey(currentLevelName));
}