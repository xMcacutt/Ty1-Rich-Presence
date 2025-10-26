#pragma once
#include "savedata.h"
#include <string>
#include "discord.h"
#include "minhook.h"
#include "gamestate.h"

class hooks
{
public:
	static hooks& getInstance() {
		static hooks instance;
		return instance;
	}
	static void __stdcall ChangeLevelHook();
	static void OnChangeLevel(int level);
	static void __stdcall ChangeTheggsHook();
	static void OnChangeTheggs(int count);
	void SetupHooks(); 
	void UpdateDiscord();

	std::string getLevelName(LevelCode levelCode) {
		auto levelId = static_cast<int>(levelCode);
		auto namePtr = *(char**)(Core::moduleBase + 0x528BF8 + (levelId * 0x4));
		return std::string(namePtr + 0xE);
	}
private:
	hooks() {}
	hooks(const hooks&) = delete;
	hooks& operator=(const hooks&) = delete;
	std::string currentLevelName;
	std::string currentThunderEggs;
};

