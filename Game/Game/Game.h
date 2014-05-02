#ifndef GAME_H
#define GAME_H

#include "DX.h"
#include "Globals.h"
#include "ConstantBuffers.h"
#include "GameStateManager.h"
#include "Gameplay.h"

class Game : public DX
{
	friend class Gameplay;
public:
	// Main game loop
	static int Run();
	// if local, wont release memory in DX
	static void Release(bool local = false);
	// Zeros-out data in buffers 
	static void Reset();

	static bool Initialize(HINSTANCE hInstance, int icon);
	static void OnResize();
	static void Update(float dt);
	static void Draw(float dt);

protected:
	static ID3D11Buffer* perFrameConstBuffer;
	static ID3D11Buffer* perModelConstBuffer;
	static PerFrameData* perFrameData;
	static PerModelData* perModelData;

	static bool projChanged;

};

#endif