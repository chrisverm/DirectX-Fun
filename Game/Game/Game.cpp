// ---------------------------------------------------------------------------
// Game.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/04/2014
// ---------------------------------------------------------------------------

#include "Game.h"

#include <iostream> // remove this

// Win32 Entry Point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	// Attach console window! :D
	// Requires use of _CRT_SECURE_NO_WARNINGS for freopen to work
	// see pre-processor stuff for debug in properties

	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);
#endif

	// icon resource
	int icon = 101;

	if (!Game::Initialize(hInstance, icon))
		return 0;

	return Game::Run();
}

ID3D11Buffer* Game::perFrameConstBuffer = nullptr;
ID3D11Buffer* Game::perModelConstBuffer = nullptr;
PerFrameData* Game::perFrameData = nullptr;
PerModelData* Game::perModelData = nullptr;
bool Game::projChanged = false;

bool Game::Initialize(HINSTANCE hInstance, int icon)
{
	hAppInst = hInstance;

	windowCaption = L"DirectX Fun";
	windowWidth = 800;
	windowHeight = 600;

	if (!DX::Initialize(icon))
		return false;

	Gameplay* gameplay = new Gameplay(device, deviceContext);
	GameStateManager::AddState("Gameplay", gameplay);
	GameStateManager::ChangeState("Gameplay");

	return true;
}

void Game::Release(bool local)
{
	if (!local)	DX::Release();

	if (perModelConstBuffer != nullptr)
	{
		ReleaseMacro(perModelConstBuffer);
		perModelConstBuffer = nullptr;
	}

	if (perFrameConstBuffer != nullptr)
	{
		ReleaseMacro(perFrameConstBuffer);
		perFrameConstBuffer = nullptr;
	}

	if (perModelData != nullptr)
	{
		delete perModelData;
		perModelData = nullptr;
	}

	if (perFrameData != nullptr)
	{
		delete perFrameData;
		perFrameData = nullptr;
	}
}

void Game::Reset()
{

}

void Game::OnResize()
{
	DX::OnResize();
}

int Game::Run()
{
	MSG msg = {0};
	timer.Reset();

	// Loop until we get a quit message from windows
	while(msg.message != WM_QUIT)
	{
		// Peek at the next message (and remove it from the queue)
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			// Handle this message
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			// No message, so continue the game loop
			timer.Tick();

			if( gamePaused )
			{
				Sleep(100);
			}
			else
			{
				CalculateFrameStats();

				DX::PreUpdate();

				Game::Update(timer.DeltaTime());
				Game::Draw(timer.DeltaTime());

				DX::PostUpdate();
			}
		}
	}

	Release();

	return (int)msg.wParam;
}

void Game::Update(float dt)
{
	(*GameStateManager::CurrentState)->Update(dt);
}

void Game::Draw(float dt)
{
	(*GameStateManager::CurrentState)->Draw(dt);
}

void Game::CalculateFrameStats()
{
	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if( (timer.TotalTime() - timeElapsed) >= 1.0f )
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::wostringstream outs;   
		outs.precision(6);
		outs << windowCaption << L"    "
			<< L"Width: " << windowWidth << L"    "
			<< L"Height: " << windowHeight << L"    "
			<< L"FPS: " << fps << L"    " 
			<< L"Frame Time: " << mspf << L" (ms)";

		// Include feature level
		switch(featureLevel)
		{
		case D3D_FEATURE_LEVEL_11_1: outs << "    DX 11.1"; break;
		case D3D_FEATURE_LEVEL_11_0: outs << "    DX 11.0"; break;
		case D3D_FEATURE_LEVEL_10_1: outs << "    DX 10.1"; break;
		case D3D_FEATURE_LEVEL_10_0: outs << "    DX 10.0"; break;
		case D3D_FEATURE_LEVEL_9_3:  outs << "    DX 9.3";  break;
		case D3D_FEATURE_LEVEL_9_2:  outs << "    DX 9.2";  break;
		case D3D_FEATURE_LEVEL_9_1:  outs << "    DX 9.1";  break;
		default:                     outs << "    DX ???";  break;
		}

		SetWindowText(hMainWnd, outs.str().c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}