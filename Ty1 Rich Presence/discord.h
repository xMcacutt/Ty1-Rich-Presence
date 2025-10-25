#pragma once
#include <string>
#include "discord_rpc.h"
#include <chrono>

class discord
{
private:
	discord() {}
	discord(const discord&) = delete;
	discord& operator=(const discord&) = delete;
	std::string lastState;
	std::string lastDetails;
	std::string lastKey;
public:
	static discord& getInstance() {
		static discord instance;
		return instance;
	}
	void InitDiscord();
	void UpdateDiscordPresence(const std::string& status, const std::string& details, const std::string& key);
};

