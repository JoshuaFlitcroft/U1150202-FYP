#include "TeamStats.h"

/**
	Default Constructor.
*/
TeamStats::TeamStats()
{
	teamLoaded = false;
}

/**
	Default Deconstructor.
*/
TeamStats::~TeamStats()
{
	// Only delete the elements if they have been loaded.
	if (teamLoaded)
	{
		for (int i = 0; i < TEAM_SIZE; ++i)
		{
			delete m_pPlayerStats[i];
		}
	}
}

/**
	Initialize the team based on the values stored in a XML document.

	@param xmlDocumentName - Name of the XML Document that stores the data about the team.
	@returns true, if the XML file could be loaded; false if it couldn't.
*/
bool TeamStats::InitializeTeam(std::string xmlDocumentName)
{
	MSXML2::IXMLDOMDocument2Ptr xmlDocument;
	xmlDocument.CreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER);

	// Calculate the path to the XML document.
	xmlDocumentName = "XMLs/" + xmlDocumentName;

	// Converts the path to the correct file format.
	_variant_t path;
	path.SetString(xmlDocumentName.c_str());

	if (xmlDocument->load(path) == VARIANT_TRUE)
	{
		m_strTeamName = xmlDocument->selectSingleNode("/Team/Name")->text;

		MSXML2::IXMLDOMNodeListPtr xmlPlayers = xmlDocument->selectNodes("/Team/Players/*");

		// Stores the path to get to the player.
		bstr_t path;

		for (int i = 0; i < TEAM_SIZE; ++i)
		{
			// Calculate the players XML path.
			path = "/Team/Players/" + xmlPlayers->Getitem(i)->nodeName;

			m_pPlayerStats [i] = new PlayerStats();
		
			m_pPlayerStats[i]->m_strPlayerName = xmlDocument->selectSingleNode(path + "/Name")->text;
			m_pPlayerStats[i]->m_strPosition = xmlDocument->selectSingleNode(path + "/Position")->text;
			m_pPlayerStats[i]->m_iOverallRating = atoi(xmlDocument->selectSingleNode(path + "/OverallRating")->text);
		}

		teamLoaded = true;
		return true;
	}
	else
	{
		return false;
	}
}
