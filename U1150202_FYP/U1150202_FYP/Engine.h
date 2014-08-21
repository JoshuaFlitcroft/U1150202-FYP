#ifndef _ENGINE_H
#define _ENGINE_H_

// Lets us draw our 2D sprites.
#include <SpriteBatch.h>
// Lets us draw text to the screen.
#include <SpriteFont.h>

#include "DXEngineBase.h"
#include "Font.h"
#include "Sprite.h"
#include "Text.h"
#include "TeamStats.h"

#import <msxml6.dll>

using namespace MSXML2;

class Engine : public DXEngineBase
{
	public:
		Engine();
		virtual ~Engine();

		bool LoadContent();
		void UnloadContent();

		void Update(float dt);
		void Render();
	private:
		DirectX::SpriteBatch *m_pSpriteBatch;
		Font *m_pFont;
		Sprite *m_pSprite;

		Text m_textToDisplay;

		TeamStats teamStats;

		void renderSpriteBatch();
};

#endif

