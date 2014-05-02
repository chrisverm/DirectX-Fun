// ---------------------------------------------------------------------------
// GameState.h by Christopher Vermilya (C) 2014 All rights Reserved.
// ---------------------------------------------------------------------------

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <d3d11.h>
#include "ResourceManager.h"

class GameState
{
public:
	GameState(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
	{
		this->device = device;
		this->deviceContext = deviceContext;
	}
	virtual ~GameState() { }
	virtual void Unload()
	{
		Resources::Release();
	}
	virtual bool Initialize() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw(float dt) = 0;

protected:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

};

#endif