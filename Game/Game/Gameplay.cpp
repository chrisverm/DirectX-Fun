#include "Gameplay.h"

#include <iostream> // remove this

Gameplay::Gameplay(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
	: GameState(device, deviceContext)
{
	
}

Gameplay::~Gameplay()
{

}

bool Gameplay::Initialize()
{
	

	return true;
}

void Gameplay::Update(float dt)
{

}

void Gameplay::Draw(float dt)
{
	const float color[4] = { 0.4f, 0.6f, 0.75f, 0.0f };

	// Clear the buffer
	deviceContext->ClearRenderTargetView(DX::renderTargetView, color);
	deviceContext->ClearDepthStencilView(
		DX::depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);

	// Present the buffer
	HR(Game::swapChain->Present(0, 0));
}