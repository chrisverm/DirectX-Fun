#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "GameState.h"
#include "GameStateManager.h"
#include "Game.h"

class Gameplay : public GameState
{
public:
	Gameplay(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	~Gameplay();
	bool Initialize();
	void Update(float dt);
	void Draw(float dt);

private:

};

#endif