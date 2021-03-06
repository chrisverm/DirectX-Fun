// ---------------------------------------------------------------------------
// Gameplay.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 6/17/2014
// ---------------------------------------------------------------------------

#include "Gameplay.h"

Gameplay::Gameplay(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
	: GameState(device, deviceContext)
{
	Camera* camera = new Camera();
	camera->FieldOfView = 0.25f * 3.1415926535f;
	camera->NearPlane = 0.1f;
	camera->FarPlane = 100.0f;
	camera->Position = Vector3(0.0f, 0.0f, -5.0f);
	CameraManager::AddNewCamera(camera, true);
}

Gameplay::~Gameplay()
{
	if (crate != nullptr)
	{
		delete crate;
		crate = nullptr;
	}
}

bool Gameplay::Load()
{
	static D3D11_INPUT_ELEMENT_DESC vertex_PNU_Desc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	/* Vertex and Pixel Shaders */
	Resources::CreateVertexShaderAndInputLayout("PNU", L"Shaders/VS_PNU.cso",
		vertex_PNU_Desc, ARRAYSIZE(vertex_PNU_Desc));
	Resources::CreatePixelShader("PNU", L"Shaders/PS_PNU.cso");

	/* Shader Resourve Views */
	Resources::CreateShaderResourceView("Crate", L"Resources/crate_texture.png");

	/* Sampler States */
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	Resources::CreateSamplerState("MIN_MAG_POINT_MIP_LINEAR", samplerDesc);

	/* Meshes */
	Resources::CreateMesh("Crate", "Resources/crate_obj.obj", "3v/3vn/2vt", Resources::GetInputLayout("PNU"));

	/* Materials */
	Resources::CreateMaterial("Crate", Resources::GetVertexShader("PNU"), Resources::GetPixelShader("PNU"),
		Resources::GetShaderResourceView("Crate"), Resources::GetSamplerState("MIN_MAG_POINT_MIP_LINEAR"));

	return true;
}

bool Gameplay::Initialize()
{
	crate = new Crate(Resources::GetMesh("Crate"), Resources::GetMaterial("Crate"));
	crate->Initialize(Game::perModelConstBuffer, Game::perModelData);

	return true;
}

void Gameplay::Update(float dt)
{
	Game::perFrameData->view = CameraManager::ActiveCamera()->ViewMatrix;
	Game::perFrameData->projection = CameraManager::ActiveCamera()->ProjMatrix;

	deviceContext->UpdateSubresource(
		Game::perFrameConstBuffer,
		0,
		NULL,
		Game::perFrameData,
		0,
		0);

	crate->Update(dt);
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

	deviceContext->VSSetConstantBuffers(0, 1, &Game::perFrameConstBuffer);
	deviceContext->VSSetConstantBuffers(1, 1, &Game::perModelConstBuffer);

	crate->Render(deviceContext);

	// Present the buffer
	HR(Game::swapChain->Present(0, 0));
}