#ifndef _FONT_H_
#define _FONT_H_

#include <SpriteFont.h>

#include "Text.h"

class Font
{
	public:
		Font(void);
		~Font(void);

		void Initialize(ID3D11Device *pd3dDevice, std::wstring fileName);
		void DrawText(DirectX::SpriteBatch *pSpriteBatch, Text &textToDraw);
	private:
		DirectX::SpriteFont *m_pSpriteFont;
};

#endif

