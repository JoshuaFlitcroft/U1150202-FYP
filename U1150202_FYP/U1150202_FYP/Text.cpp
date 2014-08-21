#include "Text.h"

/**
	Default Constructor.
*/
Text::Text()
{
}

/**
	Default Deconstructor.
*/
Text::~Text()
{
}

/**
	Setup our object (text and position) using the parameters.

	@param text - Text we want to display.
	@param position - Position we want to display the text.
*/
void Text::Initialize(std::wstring text, DirectX::SimpleMath::Vector2 position)
{
	m_textToDisplay = text;
	m_textPosition = position;
}
