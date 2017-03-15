#include "bwrepapi.h"

#include <array>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
  BWrepFile replay;
	bool ok = replay.Load(argv[1]);

	// Print game information
	const std::time_t game_date = replay.m_oHeader.getCreationDate();
  char buffer[40];
  // strftime(buffer, sizeof(buffer), "%F", std::localtime(&game_date));
	std::cout << "Game Name: " << replay.m_oHeader.getGameName() << '\n'
		<< "Game Date: " << game_date << '\n'
    // Print map information
	  << "Map Name: " << replay.m_oHeader.getMapName() << '\n'
		<< "Map Size: " << replay.m_oHeader.getMapWidth() << "x" << replay.m_oHeader.getMapHeight() << "\n\n";

	// Print player information
	const std::array<const std::string, 4> race = { "Z", "T", "P", "?" };
	const std::array<const std::string, 3> type = { "?", "Computer", "Human" };
	for (int i=0; i<replay.m_oHeader.getLogicalPlayerCount(); i++) {
    BWrepPlayer player;
    replay.m_oHeader.getLogicalPlayers(player, i);
		std::cout << "Player " << player.getNumber() << ": " << player.getName() << "(" << race.at(static_cast<int>(player.getRace())) << ") " << type.at(static_cast<int>(player.getType())) << '\n';
  }

	return 0;
}
