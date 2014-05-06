// ---------------------------------------------------------------------------
// Gameplay.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/06/2014
// ---------------------------------------------------------------------------

#include "Gameplay.h"

Gameplay::Gameplay(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
	: GameState(device, deviceContext)
{
	
}

Gameplay::~Gameplay()
{

}

bool Gameplay::Initialize()
{
	static D3D11_INPUT_ELEMENT_DESC vertex_PNU_Desc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL"	, 0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 12,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0, 24,	D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	Resources::CreateVertexShaderAndInputLayout("PNU", L"Shaders/VS_PNU.cso", 
		vertex_PNU_Desc, ARRAYSIZE(vertex_PNU_Desc));
	Resources::CreatePixelShader("PNU", L"Shaders/PS_PNU.cso");

	/*mesh = */Mesh::LoadFromOBJ("Resources/crate_obj.obj");
	//mesh->Initialize(device, Resources::GetInputLayout("PNU"), D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

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