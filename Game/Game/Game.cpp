// ---------------------------------------------------------------------------
// Game.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/02/2014
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