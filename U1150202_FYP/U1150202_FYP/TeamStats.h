#ifndef _TEAMSTATS_H_
#define _TEAMSTATS_H_

#include <string>
#import <msxml6.dll>

//using namespace MSXML2;

struct PlayerStats
{
	// Stores the name of the player.
	std::string m_strPlayerName;
	// Stores the position of the player.
	std::string m_strPosition;

	// Stores the overall rating of the player.
	int m_iOverallRating;
};

class TeamStats
{
	private:
		// Stores whether "LoadTeam()" has been called - team loaded.
		bool teamLoaded;
	public:
		TeamStats();
		~TeamStats();

		bool InitializeTeam(std::string xmlDocumentName);
		void LoadTeam(MSXML2::IXMLDOMDocument2Ptr &xmlDocument);

		// Stores how many players on a team.
		const static int TEAM_SIZE = 3;

		// Stores the name of the team.
		std::string m_strTeamName;
		// Stores each of the players stats on the team.
		PlayerStats *m_pPlayerStats[TEAM_SIZE];
};

#endif