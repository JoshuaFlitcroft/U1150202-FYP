#include "Engine.h"


Engine::Engine()
{
	m_pFont = new Font();
	m_pSprite = new Sprite();

	teamStats = TeamStats();
}


Engine::~Engine()
{

}

bool Engine::LoadContent()
{
	// Setup our SpriteBatch.
	m_pSpriteBatch = new DirectX::SpriteBatch(d3dContext_);

	m_pFont->Initialize(d3dDevice_, std::wstring(L"Calibri18.spritefont"));
	m_pSprite->Initialize(d3dDevice_, std::wstring(L"Test.dds"), 10.0f, 10.0f); 
	
	m_textToDisplay = Text();
	m_textToDisplay.Initialize(std::wstring(L"Sarah"), DirectX::SimpleMath::Vector2(200.0f, 200.0f));

	try
	{
		MSXML2::IXMLDOMDocument2Ptr xmlDoc;
		HRESULT hr = xmlDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER);

		teamStats.InitializeTeam("Players.xml");

		// Make sure the file was loaded correctly before trying to load the players.
		if (xmlDoc->load("Players.xml") == VARIANT_TRUE)
		{
			//xmlDoc->setProperty("SelectionLanguage", "XPath");
			//teamStats.LoadPlayers(xmlDoc);
		}


		if (xmlDoc->load("input.xml") != VARIANT_TRUE)
		{
			DXTRACE_MSG("Unable to load input.xml\n");

			xmlDoc->save("input.xml");
			//xmlDoc->
		}
		else
		{
			DXTRACE_MSG("XML was successfully loaded \n");

			xmlDoc->setProperty("SelectionLanguage", "XPath");
			MSXML2::IXMLDOMNodeListPtr wheels = xmlDoc->selectNodes("/Car/Wheels/*");
			DXTRACE_MSG("Car has %u wheels\n", wheels->Getlength());
		
			DXTRACE_MSG(wheels->Getitem(0)->text);

			//ptr->

			MSXML2::IXMLDOMNodePtr node;
			node = xmlDoc->createNode(MSXML2::NODE_ELEMENT, ("Engine"), (""));
			node->text = ("Engine 1.0");
			xmlDoc->documentElement->appendChild(node);
			hr = xmlDoc->save("output.xml");

			if (SUCCEEDED(hr))
			{
				DXTRACE_MSG("output.xml successfully saved\n");
			}
		}
	}
	catch (_com_error &e)
	{
		DXTRACE_MSG(e.ErrorMessage());
	}










	return true;
}

void Engine::UnloadContent()
{
	if (m_pSpriteBatch != NULL)
	{
		delete m_pSpriteBatch;
	}

	if (m_pFont != NULL)
	{
		delete m_pFont;
	}

	if (m_pSprite != NULL)
	{
		delete m_pSprite;
	}
}

void Engine::Update(float dt)
{
	DXEngineBase::Update(dt);
}

void Engine::Render()
{
	// Swap chain render taken from "Beginning DirectX 11 Game Programming" by Wendy Jones and Allen Sherrod.
	if (d3dContext_ == 0)
	{
		return;
	}

	float clearColor[4] = {0.0f, 0.25f, 0.0f, 1.0f};
	d3dContext_->ClearRenderTargetView(backBufferTarget_, clearColor);

	renderSpriteBatch();

	swapChain_->Present(0, 0);
}

/**
	Draw our variables that require a SpriteBatch - 2D assets, fonts.
*/
void Engine::renderSpriteBatch()
{
	m_pSpriteBatch->Begin();

	m_pSprite->DrawSprite(m_pSpriteBatch);

	m_pFont->DrawTextA(m_pSpriteBatch, m_textToDisplay);

	m_pSpriteBatch->End();
}