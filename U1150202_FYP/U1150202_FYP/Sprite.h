#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SpriteBatch.h>
#include <DDSTextureLoader.h>
#include <SimpleMath.h>

class Sprite
{
public:
	Sprite();
	virtual ~Sprite();

	virtual bool Initialize(ID3D11Device *pd3dDevice, std::wstring fileName);
	virtual bool Initialize(ID3D11Device *pd3dDevice, std::wstring fileName, float xPosition, float yPosition);
	virtual bool Initialize(ID3D11Device *pd3dDevice, std::wstring fileName, float xPosition, float yPosition,
		float width, float height);

	void SetPosition(DirectX::SimpleMath::Vector2 newPosition);
	void MoveSprite(DirectX::SimpleMath::Vector2 movement);

	void DrawSprite(DirectX::SpriteBatch *pSpriteBatch);
protected:
	// Texture we want to use for the sprite.
	ID3D11ShaderResourceView *m_pTexture;

	// Rectangle used when drawing the sprite.
	RECT m_rectangle;

	// Stores the current position of the sprite.
	DirectX::SimpleMath::Vector2 m_position;
	// Stores the size of the sprite - x = width, y = height.
	DirectX::SimpleMath::Vector2 m_size;

	void calculateRectangle();
};

#endif
