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
		switch (levelCode) {
		case LevelCode::A1:
			return "Two Up";
		case LevelCode::A2:
			return "Walk in the Park";
		case LevelCode::A3:
			return "Ship Rex";
		case LevelCode::A4:
			return "Bull's Pen";
		case LevelCode::B1:
			return "Bridge on the River Ty";
		case LevelCode::B2:
			return "Snow Worries";
		case LevelCode::B3:
			return "Outback Safari";
		case LevelCode::B4:
			return "Kumu Caves";
		case LevelCode::C1:
			return "Lyre, Lyre Pants on Fire";
		case LevelCode::C2:
			return "Beyond the Black Stump";
		case LevelCode::C3:
			return "Rex Marks the Spot";
		case LevelCode::C4:
			return "Fluffy's Fjord";
		case LevelCode::D1:
			return "Credits";
		case LevelCode::D2:
			return "Cass' Crest";
		case LevelCode::D3:
			return "Modded Levels";
		case LevelCode::D4:
			return "Crikey's Cove";
		case LevelCode::E1:
			return "Cass' Pass";
		case LevelCode::E2:
			return "Bonus World 1";
		case LevelCode::E3:
			return "Bonus World 2";
		case LevelCode::E4:
			return "Final Battle";
		case LevelCode::Z1:
			return "Rainbow Cliffs";
		default:
			return "The Dreaming";
		}
	}
private:
	hooks() {}
	hooks(const hooks&) = delete;
	hooks& operator=(const hooks&) = delete;
	std::string currentLevelName;
	std::string currentThunderEggs;
};

