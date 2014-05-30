// ---------------------------------------------------------------------------
// ResourceManager.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/30/2014
// ---------------------------------------------------------------------------

#include "ResourceManager.h"

ID3D11Device* ResourceManager::device = nullptr;
ID3D11DeviceContext* ResourceManager::deviceContext = nullptr;

MeMap  ResourceManager::meshes;
MaMap  ResourceManager::materials;
VSMap  ResourceManager::vertexShaders;
PSMap  ResourceManager::pixelShaders;
ILMap  ResourceManager::inputLayouts;
SRVMap ResourceManager::shaderResourceViews;
SSMap  ResourceManager::samplerStates;
RSMap  ResourceManager::rasterizerStates;
DSSMap ResourceManager::depthStencilStates;

void ResourceManager::Release()
{
	for (MeMap::iterator it = meshes.begin(); it != meshes.end(); it = meshes.begin())
	{ delete it->second; meshes.erase(it->first); }

	for (MaMap::iterator it = materials.begin(); it != materials.end(); it = materials.begin())
	{ delete it->second; materials.erase(it->first); }

	for (VSMap::iterator it = vertexShaders.begin(); it != vertexShaders.end(); it = vertexShaders.begin())
	{ ReleaseMacro(it->second); vertexShaders.erase(it->first); }

	for (PSMap::iterator it = pixelShaders.begin(); it != pixelShaders.end(); it = pixelShaders.begin())
	{ ReleaseMacro(it->second); pixelShaders.erase(it->first); }

	for (ILMap::iterator it = inputLayouts.begin(); it != inputLayouts.end(); it = inputLayouts.begin())
	{ ReleaseMacro(it->second); inputLayouts.erase(it->first); }

	for (SRVMap::iterator it = shaderResourceViews.begin(); it != shaderResourceViews.end(); it = shaderResourceViews.begin())
	{ ReleaseMacro(it->second); shaderResourceViews.erase(it->first); }

	for (SSMap::iterator it = samplerStates.begin(); it != samplerStates.end(); it = samplerStates.begin())
	{ ReleaseMacro(it->second); samplerStates.erase(it->first); }
}

void ResourceManager::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	ResourceManager::device = device;
	ResourceManager::deviceContext = deviceContext;
}

bool ResourceManager::AddMesh(std::string id, Mesh* mesh)
{
	// ensure id is all uppercase to prevent same string IDs with different char cases
	id = ToUpper(id);

	// check if mesh with this ID already exists
	if (meshes[id] != nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"A mesh with the ID \"" + wid + L"\" already exists.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}
	// check if mesh param is a nullptr
	if (mesh == nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"The mesh passed with the ID \"" + wid + L"\" cannot be a nullptr.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}

	meshes[id] = mesh;

	return true;
}

bool ResourceManager::AddMaterial(std::string id, Material* material)
{
	// ensure id is all uppercase to prevent same string IDs with different char cases
	id = ToUpper(id);

	// check if material with this ID already exists
	if (materials[id] != nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"A material with the ID \"" + wid + L"\" already exists.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}
	// check if material param is a nullptr
	if (material == nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"The material passed with the ID \"" + wid + L"\" cannot be a nullptr.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}

	materials[id] = material;

	return true;
}

bool ResourceManager::AddVertexShader(std::string id, ID3D11VertexShader* vertexShader)
{
	// ensure id is all uppercase to prevent same string IDs with different char cases
	id = ToUpper(id);

	// check if vertex shader with this ID already exists
	if (vertexShaders[id] != nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"A vertex shader with the ID \"" + wid + L"\" already exists.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}
	// check if vertex shader param is a nullptr
	if (vertexShader == nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"The vertex shader passed with the ID \"" + wid + L"\" cannot be a nullptr.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}

	vertexShaders[id] = vertexShader;

	return true;
}

bool ResourceManager::AddPixelShader(std::string id, ID3D11PixelShader* pixelShader)
{
	// ensure id is all uppercase to prevent same string IDs with different char cases
	id = ToUpper(id);

	// check if pixel shader with this ID already exists
	if (pixelShaders[id] != nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"A pixel shader with the ID \"" + wid + L"\" already exists.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}
	// check if pixel shader param is a nullptr
	if (pixelShader == nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"The pixel shader passed with the ID \"" + wid + L"\" cannot be a nullptr.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}

	pixelShaders[id] = pixelShader;

	return true;
}

bool ResourceManager::AddInputLayout(std::string id, ID3D11InputLayout* inputLayout)
{
	// ensure id is all uppercase to prevent same string IDs with different char cases
	id = ToUpper(id);

	// check if input layout with this ID already exists
	if (inputLayouts[id] != nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"An input layout with the ID \"" + wid + L"\" already exists.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}
	// check if input layout param is a nullptr
	if (inputLayout == nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"The input layout passed with the ID \"" + wid + L"\" cannot be a nullptr.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}

	inputLayouts[id] = inputLayout;

	return true;
}

bool ResourceManager::AddShaderResourceView(std::string id, ID3D11ShaderResourceView* shaderResourceView)
{
	// ensure id is all uppercase to prevent same string IDs with different char cases
	id = ToUpper(id);

	// check if shader resource view with this ID already exists
	if (shaderResourceViews[id] != nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"A shader resource view with the ID \"" + wid + L"\" already exists.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}
	// check if shader resource view param is a nullptr
	if (shaderResourceView == nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"The shader resource view passed with the ID \"" + wid + L"\" cannot be a nullptr.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}

	shaderResourceViews[id] = shaderResourceView;

	return true;
}

bool ResourceManager::AddSamplerState(std::string id, ID3D11SamplerState* samplerState)
{
	// ensure id is all uppercase to prevent same string IDs with different char cases
	id = ToUpper(id);

	// check if sampler state with this ID already exists
	if (samplerStates[id] != nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"A sampler state with the ID \"" + wid + L"\" already exists.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}
	// check if sampler state param is a nullptr
	if (samplerState == nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"The sampler state passed with the ID \"" + wid + L"\" cannot be a nullptr.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}

	samplerStates[id] = samplerState;

	return true;
}

bool ResourceManager::AddRasterizerState(std::string id, ID3D11RasterizerState* rasterizerState)
{
	// ensure id is all uppercase to prevent same string IDs with different char cases
	id = ToUpper(id);

	// check if rasterizer state with this ID already exists
	if (samplerStates[id] != nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"A rasterizer state with the ID \"" + wid + L"\" already exists.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}
	// check if rasterizer state param is a nullptr
	if (rasterizerState == nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"The rasterizer state passed with the ID \"" + wid + L"\" cannot be a nullptr.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}

	rasterizerStates[id] = rasterizerState;

	return true;
}

bool ResourceManager::AddDepthStencilState(std::string id, ID3D11DepthStencilState* depthStencilState)
{
	// ensure id is all uppercase to prevent same string IDs with different char cases
	id = ToUpper(id);

	// check if depth stencil state with this ID already exists
	if (depthStencilStates[id] != nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"A depth stencil state with the ID \"" + wid + L"\" already exists.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}
	// check if depth stencil state param is a nullptr
	if (depthStencilState == nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"The depth stencil state passed with the ID \"" + wid + L"\" cannot be a nullptr.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}

	depthStencilStates[id] = depthStencilState;

	return true;
}

bool ResourceManager::CreateMesh(std::string id, std::string objFilePath, std::string faceFormat, ID3D11InputLayout* inputLayout)
{
	// ensure id is all uppercase to prevent same string IDs with different char cases
	id = ToUpper(id);

	// check if mesh with this ID already exists
	if (meshes[id] != nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"A mesh with the ID \"" + wid + L"\" already exists.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}

	Mesh* mesh = Mesh::LoadFromOBJ(objFilePath, faceFormat);

	if (inputLayout == nullptr)
		mesh->Initialize(device, Resources::GetInputLayout(mesh->ILName));
	else
		mesh->Initialize(device, inputLayout);

	AddMesh(id, mesh);

	return true;
}

bool ResourceManager::CreateMaterial(std::string id, ID3D11VertexShader* vertexShader, ID3D11PixelShader* pixelShader,
	ID3D11ShaderResourceView* shaderResourceView, ID3D11SamplerState* samplerState)
{
	// ensure id is all uppercase to prevent same string IDs with different char cases
	id = ToUpper(id);

	// check if material with this ID already exists
	if (materials[id] != nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"A material with the ID \"" + wid + L"\" already exists.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}

	Material* material = new Material(vertexShader, pixelShader);
	material->SetTexture(shaderResourceView, samplerState);

	AddMaterial(id, material);

	return true;
}

bool ResourceManager::CreateVertexShaderAndInputLayout(std::string id, std::wstring filepath, 
			D3D11_INPUT_ELEMENT_DESC layoutDesc[], UINT numElements)
{
	// ensure id is all uppercase to prevent same string IDs with different char cases
	id = ToUpper(id);

	// check if vertex shader with this ID already exists
	if (vertexShaders[id] != nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"A vertex shader with the ID \"" + wid + L"\" already exists.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}

	ID3DBlob* vsBlob = nullptr;
	ID3D11VertexShader* vShader = nullptr;
	ID3D11InputLayout* inputLayout = nullptr;

	D3DReadFileToBlob(filepath.c_str(), &vsBlob);

	HR(device->CreateVertexShader(
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		NULL,
		&vShader));
	AddVertexShader(id, vShader);

	HR(device->CreateInputLayout(
		layoutDesc,
		numElements,
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		&inputLayout));
	AddInputLayout(id, inputLayout);

	return true;
}

bool ResourceManager::CreatePixelShader(std::string id, std::wstring filepath)
{
	// ensure id is all uppercase to prevent same string IDs with different char cases
	id = ToUpper(id);

	// check if pixel shader with this ID already exists
	if (pixelShaders[id] != nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"A pixel shader with the ID \"" + wid + L"\" already exists.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}

	ID3DBlob* psBlob = nullptr;
	ID3D11PixelShader* pShader = nullptr;

	D3DReadFileToBlob(filepath.c_str(), &psBlob);

	HR(device->CreatePixelShader(
		psBlob->GetBufferPointer(),
		psBlob->GetBufferSize(),
		NULL,
		&pShader));
	AddPixelShader(id, pShader);

	return true;
}

bool ResourceManager::CreateShaderResourceView(std::string id, std::wstring textureFilePath)
{
	// ensure id is all uppercase to prevent same string IDs with different char cases
	id = ToUpper(id);

	// check if shader resource view with this ID already exists
	if (shaderResourceViews[id] != nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"A shader resource view with the ID \"" + wid + L"\" already exists.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}

	ID3D11ShaderResourceView* shaderResourceView = nullptr;
	
	HR(DirectX::CreateWICTextureFromFile(
		device, 
		deviceContext, 
		textureFilePath.c_str(), 
		0, 
		&shaderResourceView));
	AddShaderResourceView(id, shaderResourceView);

	return true;
}

bool ResourceManager::CreateSamplerState(std::string id, D3D11_SAMPLER_DESC samplerDesc)
{
	// ensure id is all uppercase to prevent same string IDs with different char cases
	id = ToUpper(id);

	// check if sampler state with this ID already exists
	if (samplerStates[id] != nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"A sampler state with the ID \"" + wid + L"\" already exists.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}
	
	ID3D11SamplerState* ss = nullptr;
	
	HR(device->CreateSamplerState(
		&samplerDesc,
		&ss));
	AddSamplerState(id, ss);

	return true;
}

bool ResourceManager::CreateRasterizerState(std::string id, D3D11_RASTERIZER_DESC rasterizerDesc)
{
	// ensure id is all uppercase to prevent same string IDs with different char cases
	id = ToUpper(id);

	// check if rasterizer state with this ID already exists
	if (rasterizerStates[id] != nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"A rasterizer state with the ID \"" + wid + L"\" already exists.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}

	ID3D11RasterizerState* rasterizerState = nullptr;

	HR(device->CreateRasterizerState(
		&rasterizerDesc, 
		&rasterizerState));

	Resources::AddRasterizerState(id, rasterizerState);

	return true;
}

bool ResourceManager::CreateDepthStencilState(std::string id, D3D11_DEPTH_STENCIL_DESC depthStencilDesc)
{
	// ensure id is all uppercase to prevent same string IDs with different char cases
	id = ToUpper(id);

	// check if depth stencil state with this ID already exists
	if (depthStencilStates[id] != nullptr)
	{
		std::wstring wid = std::wstring(id.begin(), id.end());
		std::wstring error = L"A depth stencil state with the ID \"" + wid + L"\" already exists.";
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		return false;
	}

	ID3D11DepthStencilState* depthStencilState = nullptr;

	HR(device->CreateDepthStencilState(
		&depthStencilDesc, 
		&depthStencilState));

	Resources::AddDepthStencilState(id, depthStencilState);

	return true;
}