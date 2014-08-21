#include "Font.h"

/**
	Default Constructor.
*/
Font::Font()
{
}

/**
	Default Deconstructor.
*/
Font::~Font()
{
	delete m_pSpriteFont;
}

/**
	Initialize the font so that it is ready to use.

	@param pd3dDevice - Device used to load the font.
	@param fileName - Name of the font that we want to load.
*/
void Font::Initialize(ID3D11Device *pd3dDevice, std::wstring fileName)
{
	// Path we can find the font.
	std::wstring path((L"Fonts/"));
	path += fileName;

	m_pSpriteFont = new DirectX::SpriteFont(pd3dDevice, path.c_str());
}

/**
	Draw the font to the screen.

	@pSpriteBatch - Used to draw the font.
	@textToDraw - Reference of the object (text and position) that we want to draw.
*/
void Font::DrawText(DirectX::SpriteBatch *pSpriteBatch, Text &textToDraw)
{
	m_pSpriteFont->DrawString(pSpriteBatch, textToDraw.GetTextToDisplay().c_str(),
		textToDraw.GetTextPosition());
}