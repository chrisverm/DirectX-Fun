// ---------------------------------------------------------------------------
// Gameplay.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 6/17/2014
// ---------------------------------------------------------------------------

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "GameState.h"
#include "GameStateManager.h"
#include "Game.h"
#include "Entity.h"
#include "Mesh.h"
#include "Material.h"
#include "Crate.h"
#include "Camera.h"

class Gameplay : public GameState
{
public:
	Gameplay(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	~Gameplay();
	bool Load();
	bool Initialize();
	void Update(float dt);
	void Draw(float dt);

private:
	Crate* crate;

};

#endif