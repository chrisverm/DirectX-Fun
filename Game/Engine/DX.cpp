// ---------------------------------------------------------------------------
// DX.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/02/2014
// ---------------------------------------------------------------------------

#include "DX.h"

HINSTANCE DX::hAppInst = 0;
HWND DX::hMainWnd = 0;

GameTimer DX::timer;
UINT DX::msaa4xQuality = 0;
ID3D11Device* DX::device = nullptr;
ID3D11DeviceContext* DX::deviceContext = nullptr;
IDXGISwapChain* DX::swapChain = nullptr;
ID3D11Texture2D* DX::depthStencilBuffer = nullptr;
ID3D11RenderTargetView* DX::renderTargetView = nullptr;
ID3D11DepthStencilView* DX::depthStencilView = nullptr;
D3D11_VIEWPORT DX::viewport;
D3D_DRIVER_TYPE DX::driverType = D3D_DRIVER_TYPE_HARDWARE;
D3D_FEATURE_LEVEL DX::featureLevel;

bool DX::gamePaused = false;
bool DX::minimized = false;
bool DX::maximized = false;
bool DX::resizing = false;

std::wstring DX::windowCaption = L"DirectX Game";
int DX::windowWidth = 800;
int DX::windowHeight = 600;
bool DX::enable4xMsaa = false;

LRESULT CALLBACK
	MainWndProc2(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Forward the global callback to our game's message handling

	// Forward hwnd because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before mhMainWnd is valid.
	return DX::MsgProc(hwnd, msg, wParam, lParam);
}

void DX::Release()
{
	// Release the DX stuff
	ReleaseMacro(renderTargetView);
	ReleaseMacro(depthStencilView);
	ReleaseMacro(swapChain);
	ReleaseMacro(depthStencilBuffer);

	// Restore default device settings
	if (deviceContext)
		deviceContext->ClearState();

	// Release the context and finally the device
	ReleaseMacro(deviceContext);
	ReleaseMacro(device);

	GameStateManager::Release();
}

bool DX::Initialize(int icon)
{
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	if (!InitMainWindow(icon))
		return false;

	if (!InitDirect3D())
		return false;

	ResourceManager::Initialize(device, deviceContext);

	return true;
}

bool DX::InitMainWindow(int iconResource)
{
	// Actually create the window
	WNDCLASS wc;
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = MainWndProc2;  // Can't be a member function!  Hence our global version
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hAppInst;
	
	if(iconResource != 0)
		wc.hIcon     = LoadIcon(hAppInst, MAKEINTRESOURCE(iconResource));
	else
		wc.hIcon	 = LoadIcon(0, IDI_APPLICATION);	

	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = L"D3DWndClassName";

	if( !RegisterClass(&wc) )
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return false;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, windowWidth, windowHeight };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width  = R.right - R.left;
	int height = R.bottom - R.top;

	hMainWnd = CreateWindow(L"D3DWndClassName", windowCaption.c_str(), 
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, hAppInst, 0); 
	if( !hMainWnd )
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return false;
	}

	ShowWindow(hMainWnd, SW_SHOW);
	UpdateWindow(hMainWnd);

	return true;
}

bool DX::InitDirect3D()
{
	UINT createDeviceFlags = 0;

	// Do we want a debug device?
#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Create the device and determine the supported feature level
	featureLevel = D3D_FEATURE_LEVEL_9_1; // Will be overwritten by next line
	HRESULT hr = D3D11CreateDevice(
		0,
		driverType,
		0,
		createDeviceFlags,
		0,
		0,
		D3D11_SDK_VERSION,
		&device,
		&featureLevel,
		&deviceContext);

	// Handle any device creation or DirectX version errors
	if( FAILED(hr) )
	{
		MessageBox(0, L"D3D11CreateDevice Failed", 0, 0);
		return false;
	}

	// Check for 4X MSAA quality support
	HR(device->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		4,
		&msaa4xQuality));
	assert( msaa4xQuality > 0 ); // Potential problem if quality is 0

	// Set up a swap chain description
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	swapChainDesc.BufferDesc.Width		= windowWidth;
	swapChainDesc.BufferDesc.Height		= windowHeight;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.Format		= DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling	= DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount			= 1;
	swapChainDesc.OutputWindow			= hMainWnd;
	swapChainDesc.Windowed				= true;
	swapChainDesc.SwapEffect			= DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags					= 0;
	if( enable4xMsaa )
	{
		// Set up 4x MSAA
		swapChainDesc.SampleDesc.Count   = 4;
		swapChainDesc.SampleDesc.Quality = msaa4xQuality - 1;
	}
	else
	{
		// No MSAA
		swapChainDesc.SampleDesc.Count   = 1;
		swapChainDesc.SampleDesc.Quality = 0;
	}

	// To correctly create the swap chain, we must use the IDXGIFactory that
	// was used to create the device.
	IDXGIDevice*	dxgiDevice	= 0;
	IDXGIAdapter*	dxgiAdapter = 0;
	IDXGIFactory*	dxgiFactory = 0;
	HR(device->QueryInterface(	__uuidof(IDXGIDevice),	(void**)&dxgiDevice));
	HR(dxgiDevice->GetParent(	__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));
	HR(dxgiAdapter->GetParent(	__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	// Finally make the swap chain and release the DXGI stuff
	HR(dxgiFactory->CreateSwapChain(device, &swapChainDesc, &swapChain));
	ReleaseMacro(dxgiDevice);
	ReleaseMacro(dxgiAdapter);
	ReleaseMacro(dxgiFactory);

	// The remaining steps also need to happen each time the window
	// is resized, so just run the OnResize method
	OnResize();

	return true;
}

void DX::OnResize()
{
	// Release the views, since we'll be destroying
	// the corresponding buffers.
	ReleaseMacro(renderTargetView);
	ReleaseMacro(depthStencilView);
	ReleaseMacro(depthStencilBuffer);

	// Resize the swap chain to match the window and
	// recreate the render target view
	HR(swapChain->ResizeBuffers(
		1, 
		windowWidth, 
		windowHeight, 
		DXGI_FORMAT_R8G8B8A8_UNORM,
		0));
	ID3D11Texture2D* backBuffer;
	HR(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	HR(device->CreateRenderTargetView(backBuffer, 0, &renderTargetView));
	ReleaseMacro(backBuffer);

	// Set up the description of the texture to use for the
	// depth stencil buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width			= windowWidth;
	depthStencilDesc.Height			= windowHeight;
	depthStencilDesc.MipLevels		= 1;
	depthStencilDesc.ArraySize		= 1;
	depthStencilDesc.Format			= DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0; 
	depthStencilDesc.MiscFlags      = 0;
	if( enable4xMsaa )
	{
		// Turn on 4x MultiSample Anti Aliasing
		// This must match swap chain MSAA values
		depthStencilDesc.SampleDesc.Count	= 4;
		depthStencilDesc.SampleDesc.Quality = msaa4xQuality - 1;
	}
	else
	{
		// No MSAA
		depthStencilDesc.SampleDesc.Count   = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	// Create the depth/stencil buffer and corresponding view
	HR(device->CreateTexture2D(&depthStencilDesc, 0, &depthStencilBuffer));
	HR(device->CreateDepthStencilView(depthStencilBuffer, 0, &depthStencilView));

	// Bind these views to the pipeline, so rendering actually
	// uses the underlying textures
	deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	// Update the viewport and set it on the device
	viewport.TopLeftX	= 0;
	viewport.TopLeftY	= 0;
	viewport.Width		= (float)windowWidth;
	viewport.Height		= (float)windowHeight;
	viewport.MinDepth	= 0.0f;
	viewport.MaxDepth	= 1.0f;
	deviceContext->RSSetViewports(1, &viewport);
}

void DX::PreUpdate()
{

}

void DX::PostUpdate()
{

}

LRESULT DX::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
		// WM_ACTIVATE is sent when the window is activated or deactivated.  
		// We pause the game when the window is deactivated and unpause it 
		// when it becomes active.  
	case WM_ACTIVATE:
		if( LOWORD(wParam) == WA_INACTIVE )
		{
			gamePaused = true;
			timer.Stop();
		}
		else
		{
			gamePaused = false;
			timer.Start();
		}
		break;

		// When the window is moved, update our x,y pos for the window.
	case WM_MOVE:
		break;

		// WM_SIZE is sent when the user resizes the window.  
	case WM_SIZE:
		// Save the new client area dimensions.
		windowWidth  = LOWORD(lParam);
		windowHeight = HIWORD(lParam);
		if( device )
		{
			if( wParam == SIZE_MINIMIZED )
			{
				gamePaused = true;
				minimized = true;
				maximized = false;
			}
			else if( wParam == SIZE_MAXIMIZED )
			{
				gamePaused = false;
				minimized = false;
				maximized = true;
				OnResize();
			}
			else if( wParam == SIZE_RESTORED )
			{
				// Restoring from minimized state?
				if( minimized )
				{
					gamePaused = false;
					minimized = false;
					OnResize();
				}

				// Restoring from maximized state?
				else if( maximized )
				{
					gamePaused = false;
					maximized = false;
					OnResize();
				}
				else if( resizing )
				{
					// If user is dragging the resize bars, we do not resize 
					// the buffers here because as the user continuously 
					// drags the resize bars, a stream of WM_SIZE messages are
					// sent to the window, and it would be pointless (and slow)
					// to resize for each WM_SIZE message received from dragging
					// the resize bars.  So instead, we reset after the user is 
					// done resizing the window and releases the resize bars, which 
					// sends a WM_EXITSIZEMOVE message.
				}
				else // API call such as SetWindowPos or mSwapChain->SetFullscreenState.
				{
					OnResize();
				}
			}
		}
		break;

		// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
	case WM_ENTERSIZEMOVE:
		gamePaused = true;
		resizing  = true;
		timer.Stop();
		break;

		// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
		// Here we reset everything based on the new window dimensions.
	case WM_EXITSIZEMOVE:
		gamePaused = false;
		resizing  = false;
		timer.Start();
		OnResize();
		break;

		// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		// The WM_MENUCHAR message is sent when a menu is active and the user presses 
		// a key that does not correspond to any mnemonic or accelerator key. 
	case WM_MENUCHAR:
		// Don't beep when we alt-enter.
		return MAKELRESULT(0, MNC_CLOSE);

		// Catch this message so to prevent the window from becoming too small.
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200; 
		break;

	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_MOUSEWHEEL:
	case WM_MOUSELEAVE:
	case WM_NCMOUSELEAVE:
		break;

	default: // If none of these.
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	
	// if not already returned. Only cases that return themselves are (default: and WM_MENUCHAR:)
	return 0;
}