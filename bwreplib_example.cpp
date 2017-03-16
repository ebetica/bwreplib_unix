#include "bwreplib/bwrepapi.h"

#include <array>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
  BWrepFile replay;
	bool ok = replay.Load(argv[1]);
  std::cout << ok << std::endl;

	// Print game information
	const std::time_t game_date = replay.m_oHeader.getCreationDate();
  char buffer[40];
  strftime(buffer, sizeof(buffer), "%F", std::localtime(&game_date));
	std::cout << "Game Name: " << replay.m_oHeader.getGameName() << '\n'
		<< "Game Date: " << buffer << '\n'
    // Print map information
	  << "Map Name: " << replay.m_oHeader.getMapName() << '\n'
		<< "Map Size: " << replay.m_oMap.GetWidth() << "x" << replay.m_oMap.GetHeight() << "\n\n";

	// Print player information
	const std::array<const std::string, 4> race = { "Z", "T", "P", "?" };
	const std::array<const std::string, 3> type = { "?", "Computer", "Human" };
  std::map<int32_t, std::string> idMap;
	for (int i=0; i<replay.m_oHeader.getLogicalPlayerCount(); i++) {
    BWrepPlayer player;
    replay.m_oHeader.getLogicalPlayers(player, i);
		std::cout << "Player " << player.getNumber() << ": " << player.getName() << "(" << race.at(static_cast<int>(player.getRace())) << ") " << type.at(static_cast<int>(player.getType())) << '\n';
    idMap[i] = player.getName();
  }

	for (int i=0; i<replay.m_oActions.GetActionCount(); i++)
	{
    auto action = replay.m_oActions.GetAction(i);

		// list event
		std::cout << std::left << std::setfill(' ')
			<< std::setw(6) << action->GetTime()
			<< std::setw(6) << action->GetPlayerID()
			<< std::setw(25) << idMap[action->GetPlayerID()]
			<< std::internal << std::setfill('0') << std::setw(4)
			<< std::hex << std::showbase << action->GetID() << '\t'
			<< std::dec << std::noshowbase
			<< std::left << std::setfill(' ') << std::setw(15) << action->GetName()
			<< std::setw(40) << action->GetParameters() << '\n';
	}
	return 0;
}
