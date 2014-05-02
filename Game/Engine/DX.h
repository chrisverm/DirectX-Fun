// ---------------------------------------------------------------------------
// DX.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/02/2014
// ---------------------------------------------------------------------------

#ifndef DX_H
#define DX_H

#include "Windows.h"
#include <d3d11.h>
#include "Globals.h"
#include "GameTimer.h"

#include "GameStateManager.h"

class DX
{
public:
	static void Release();

	static bool Initialize(int icon = 0);
	static LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static void PreUpdate();
	static void PostUpdate();
	static void OnResize();

	float AspectRatio() const { return (float)windowWidth / windowHeight; }

private:
	static bool InitMainWindow(int icon = 0);
	static bool InitDirect3D();

protected:
	static HINSTANCE hAppInst;
	static HWND hMainWnd;

	static GameTimer timer;
	static UINT msaa4xQuality;
	static ID3D11Device* device;
	static ID3D11DeviceContext* deviceContext;
	static IDXGISwapChain* swapChain;
	static ID3D11Texture2D* depthStencilBuffer;
	static ID3D11RenderTargetView* renderTargetView;
	static ID3D11DepthStencilView* depthStencilView;
	static D3D11_VIEWPORT viewport;
	static D3D_DRIVER_TYPE driverType;
	static D3D_FEATURE_LEVEL featureLevel;

	static bool gamePaused;
	static bool minimized;
	static bool maximized;
	static bool resizing;

	static std::wstring windowCaption;
	static int windowWidth;
	static int windowHeight;
	static bool enable4xMsaa;

};

#endif