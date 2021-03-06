// ---------------------------------------------------------------------------
// GameState.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/30/2014
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
	virtual ~GameState() { };
	virtual bool Load() = 0;
	virtual bool Initialize() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw(float dt) = 0;

	void Unload() { this->~GameState(); }

protected:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

};

#endif