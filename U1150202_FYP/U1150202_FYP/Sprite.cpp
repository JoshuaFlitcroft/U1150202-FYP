#include "Sprite.h"

/**
	Default Constructor for the Sprite.
*/
Sprite::Sprite()
{
	// Set position and size to blank values.
	m_position = DirectX::SimpleMath::Vector2();
	m_size = DirectX::SimpleMath::Vector2();

	// Setup the rectangle ready for use.
	m_rectangle = RECT();
}

/**
	Default Deconstructor for the sprite.
*/
Sprite::~Sprite()
{
	if (m_pTexture)
	{
		m_pTexture->Release();
	}
}

/**
	Initialize the texture used for the sprite.

	@param pd3dDevice - Device used to load the texture.
	@param fileName - Name of the file we want to load - from "Sprites/".
	@returns true, if the texture we loaded successfully; false if it wasn't.
*/
bool Sprite::Initialize(ID3D11Device *pd3dDevice, std::wstring fileName)
{
	// Path we can find the texture.
	std::wstring path((L"Sprites/"));
	path += fileName;

	// Stores the result of trying to load the texture.
	HRESULT hr;
	// Load the texture from file.
	hr = DirectX::CreateDDSTextureFromFile(pd3dDevice, path.c_str(), nullptr, &m_pTexture);

	// Failed when trying to load the texture.
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}
/**
	Initialize the texture and the position we want to use for the sprite.
	Note: size is calculated from the loaded texture.

	@param pd3dDevice - Device used to load the texture.
	@param fileName - Name of the file we want to load - from "Sprites/".
	@param xPosition - X position we want for the sprite - position of top left corner.
	@param yPosition - Y position we want for the sprite - position of top left corner.
	@returns true, if the texture was loaded successfully; false if it wasn't.
*/
bool Sprite::Initialize(ID3D11Device *pd3dDevice, std::wstring fileName, float xPosition, float yPosition)
{
	// Failed when trying to load the texture, don't continue.
	if (!Initialize(pd3dDevice, fileName))
	{
		return false;
	}

	m_position = DirectX::SimpleMath::Vector2(xPosition, yPosition);

	// Calculate the width and the height of the loaded texture.
	ID3D11Resource *pTextureResource = NULL;
	ID3D11Texture2D *pLoadedTexture = NULL;
	D3D11_TEXTURE2D_DESC textureDescription;

	m_pTexture->GetResource(&pTextureResource);
	pLoadedTexture = static_cast<ID3D11Texture2D*>(pTextureResource);
	pLoadedTexture->GetDesc(&textureDescription);

	m_size = DirectX::SimpleMath::Vector2(textureDescription.Width, textureDescription.Height);

	calculateRectangle();

	return true;
}
/**
	Initialize the texture, position and size we want to use for the sprite.

	@param pd3dDevice - Device used to load the texture.
	@param fileName - Name of the file we want to load - from "Sprites/".
	@param xPosition - X position we want for the sprite - position of top left corner.
	@param yPosition - Y position we want for the sprite - position of top left corner.
	@param width - Width we want to use for the sprite.
	@param height - Height we want to use for the sprite.
	@returns true, if the texture was loaded successfully; false if it wasn't.
*/
bool Sprite::Initialize(ID3D11Device *pd3dDevice, std::wstring fileName, float xPosition, float yPosition,
						float width, float height)
{
	// Failed when trying to load the texture, don't continue.
	if (!Initialize(pd3dDevice, fileName))
	{
		return false;
	}

	m_position = DirectX::SimpleMath::Vector2(xPosition, yPosition);
	m_size = DirectX::SimpleMath::Vector2(width, height);

	calculateRectangle();

	return true;
}

/**
	Set the position of the sprite to the value passed in.

	@param newPosition - Position that we want the sprite to have.
*/
void Sprite::SetPosition(DirectX::SimpleMath::Vector2 newPosition)
{
	m_position = newPosition;
	// Recalculate the rectangle for rendering.
	calculateRectangle();
}
/**
	Move the sprites position by the amount passed in.

	@param movement - How much to move the sprite by.
*/
void Sprite::MoveSprite(DirectX::SimpleMath::Vector2 movement)
{
	m_position += movement;
	// Recalculate the rectangle for rendering.
	calculateRectangle();
}

/**
	Draw the sprite to the screen.

	@param pSpriteBatch - Used to draw the sprite.
*/
void Sprite::DrawSprite(DirectX::SpriteBatch *pSpriteBatch)
{
	pSpriteBatch->Draw(m_pTexture, m_rectangle, nullptr, DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f),
		DirectX::SpriteEffects_None, 0.0f);
}

/**
	Calculate each of the points in "m_rectangle" from "m_position" and "m_size".
*/
void Sprite::calculateRectangle()
{
	m_rectangle.left = m_position.x;
	m_rectangle.top = m_position.y;
	m_rectangle.right = m_position.x + m_size.x;
	m_rectangle.bottom = m_position.y + m_size.y;
}