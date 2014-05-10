// ---------------------------------------------------------------------------
// ResourceManager.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/04/2014
// ---------------------------------------------------------------------------

#include "ResourceManager.h"

ID3D11Device* ResourceManager::device = nullptr;
ID3D11DeviceContext* ResourceManager::deviceContext = nullptr;

VSMap  ResourceManager::vertexShaders;
PSMap  ResourceManager::pixelShaders;
ILMap  ResourceManager::inputLayouts;
SRVMap ResourceManager::shaderResourceViews;
SSMap  ResourceManager::samplerStates;

void ResourceManager::Release()
{
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

//bool ResourceManager::CreateInputLayout(std::string id, D3D11_INPUT_ELEMENT_DESC layoutDesc[])
//{
//	// check if input layout with this ID already exists
//	if (inputLayouts[id] != nullptr)
//	{
//		std::wstring wid = std::wstring(id.begin(), id.end());
//		std::wstring error = L"An input layout with the ID \"" + wid + L"\" already exists.";
//		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
//		return false;
//	}
//
//	ID3D11InputLayout* inputLayout = nullptr;
//
//	/*HR(device->CreateInputLayout(
//		vertex_PNU_Desc,
//		ARRAYSIZE(vertex_PNU_Desc),
//		vsBlob->GetBufferPointer(),
//		vsBlob->GetBufferSize(),
//		&inputLayout));*/
//	AddInputLayout(id, inputLayout);
//}

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