// ---------------------------------------------------------------------------
// Gameplay.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/04/2014
// ---------------------------------------------------------------------------

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "GameState.h"
#include "GameStateManager.h"
#include "Game.h"
#include "Mesh.h"
#include "Material.h"

class Gameplay : public GameState
{
public:
	Gameplay(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	~Gameplay();
	bool Initialize();
	void Update(float dt);
	void Draw(float dt);

private:
	Mesh* mesh;
	Material* material;

};

#endif