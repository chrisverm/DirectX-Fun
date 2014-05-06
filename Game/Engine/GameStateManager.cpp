// ---------------------------------------------------------------------------
// GameStateManager.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/06/2014
// ---------------------------------------------------------------------------

#include "GameStateManager.h"

StateMap GameStateManager::states;
GameState* GameStateManager::currentState = nullptr;
GameState* const* GameStateManager::CurrentState = &currentState;

void GameStateManager::Release()
{
	for (StateMap::iterator it = states.begin(); it != states.end(); it++)
	{ delete it->second; }

	ResourceManager::Release();
}

bool GameStateManager::AddState(std::string id, GameState* state)
{
	// check if state with this ID already exists
	if (states[id] != nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"A state with the ID \"" + wid + L"\" already exists.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}
	// check if state param is a nullptr
	if (state == nullptr)
	{
		std::wstring error = L"The state currently trying to be added is a nullptr.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}

	states[id] = state;
	return true;
}

bool GameStateManager::ChangeState(std::string id)
{
	// check if state with this ID exists
	if (states[id] == nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"The state with the ID \"" + wid + L"\" does not exist in the GameStateManager.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}

	if (currentState != nullptr)
		currentState->Unload();

	if (states[id]->Initialize())
	{
		currentState = states[id];
		return true;
	}

	return false;
}