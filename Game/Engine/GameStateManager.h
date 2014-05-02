// ---------------------------------------------------------------------------
// GameStateManager.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/02/2014
// ---------------------------------------------------------------------------

#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include <map>
#include <string>
#include "dxerr.h"
#include "GameState.h"

typedef std::map<std::string, GameState*> StateMap;

class GameStateManager
{
public:
	static void Release();

	static bool AddState(std::string id, GameState* state);
	static bool ChangeState(std::string id); // add enum animation/transition param

	static GameState* const* CurrentState;

	static GameState* GetState(std::string id) { return states[id]; }

private:
	static StateMap states;
	static GameState* currentState;
	
};

#endif