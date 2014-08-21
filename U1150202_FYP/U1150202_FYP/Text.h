#ifndef _TEXT_H_
#define _TEXT_H_

#include <SimpleMath.h>

class Text
{
	public:
		Text();
		~Text();

		void Initialize(std::wstring text, DirectX::SimpleMath::Vector2 position);
		
		// Return the text we want to display.
		std::wstring GetTextToDisplay() { return m_textToDisplay; }
		// Return the position we want to draw the text.
		DirectX::SimpleMath::Vector2 GetTextPosition() { return m_textPosition; }
	private:
		// Stores the text that we want to draw on screen.
		std::wstring m_textToDisplay;
		// Stores the position that we want to draw the text.
		DirectX::SimpleMath::Vector2 m_textPosition;
};

#endif

