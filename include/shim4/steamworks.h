#ifndef NOO_STEAMWORKS_H
#define NOO_STEAMWORKS_H

#ifdef STEAMWORKS

#include <steam/steam_api.h>

namespace noo {

namespace util {

bool achieve_steam(std::string name);
bool start_steamworks();
std::string get_steam_language();

void SHIM4_EXPORT load_steam_leaderboard(std::string leaderboard_name);
void SHIM4_EXPORT set_steam_leaderboard(std::string leaderboard_name, int value);


} // End namespace util

} // End namespace noo

#endif // STEAMWORKS

#endif // NOO_STEAMWORKS_H
