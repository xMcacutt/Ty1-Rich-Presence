#include "pch.h"
#include "discord.h"

void discord::InitDiscord()
{
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	Discord_Initialize("1431358790032429209", &handlers, 1, NULL);
}

void discord::UpdateDiscordPresence(const std::string& status, const std::string& details, const std::string& key)
{
	lastState = status;
	lastDetails = details;
	lastKey = key;
    DiscordRichPresence presence;
    memset(&presence, 0, sizeof(presence));
    presence.state = lastState.c_str();
    presence.details = lastDetails.c_str();
    presence.largeImageKey = lastKey.c_str();
    presence.largeImageText = "Ty the Tasmanian Tiger";
    presence.startTimestamp = time(NULL);
    Discord_UpdatePresence(&presence);
}
