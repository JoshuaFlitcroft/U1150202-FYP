#ifndef _ENGINE_BASE_H_
#define _ENGINE_BASE_H_

#include <D3D11.h>
#include <D3DX11.h>
#include <DxErr.h>

/**
	Base for engine and input taken from "Beginning DirectX 11 Game Programming" by Wendy Jones and Allen Sherrod.
*/
class DXEngineBase
{
	public:
		DXEngineBase();
		virtual ~DXEngineBase();

		bool Initialize(HINSTANCE hInstance, HWND hwnd);
		void Shutdown();

		virtual bool LoadContent();
		virtual void UnloadContent();

		virtual void Update(float dt);
		virtual void Render() = 0;
	protected:
		// Engine variables.

		HINSTANCE hInstance_;
		HWND hwnd_;

		D3D_DRIVER_TYPE driverType_;
		D3D_FEATURE_LEVEL featureLevel_;

		ID3D11Device* d3dDevice_;
		ID3D11DeviceContext* d3dContext_;
		IDXGISwapChain* swapChain_;
		ID3D11RenderTargetView* backBufferTarget_;
};

#endif
