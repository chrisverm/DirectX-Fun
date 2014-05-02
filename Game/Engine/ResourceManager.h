// ---------------------------------------------------------------------------
// ResourceManager.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/02/2014
// ---------------------------------------------------------------------------

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <d3d11.h>
#include <d3dcompiler.h>
#include "Globals.h"
#include "WICTextureLoader.h"

typedef std::map<std::string, ID3D11VertexShader*> VSMap;
typedef std::map<std::string, ID3D11PixelShader*> PSMap;
typedef std::map<std::string, ID3D11InputLayout*> ILMap;
typedef std::map<std::string, ID3D11ShaderResourceView*> SRVMap;
typedef std::map<std::string, ID3D11SamplerState*> SSMap;

class ResourceManager
{
public:
	static void Release();

	static void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext);

	static bool AddVertexShader(std::string id, ID3D11VertexShader* vertexShader);
	static bool AddPixelShader(std::string id, ID3D11PixelShader* pixelShader);
	static bool AddInputLayout(std::string id, ID3D11InputLayout* inputLayout);
	static bool AddShaderResourceView(std::string id, ID3D11ShaderResourceView* shaderResourceView);
	static bool AddSamplerState(std::string id, ID3D11SamplerState* samplerState);

	static bool CreateVertexShaderAndInputLayout(std::string id, std::wstring filepath, D3D11_INPUT_ELEMENT_DESC layoutDesc[], UINT numElements);
	static bool CreatePixelShader(std::string id, std::wstring filepath);
	//static bool CreateInputLayout(std::string id, D3D11_INPUT_ELEMENT_DESC layoutDesc[]);
	static bool CreateShaderResourceView(std::string id, std::wstring textureFilePath);
	static bool CreateSamplerState(std::string id, D3D11_SAMPLER_DESC samplerDesc);

	static ID3D11VertexShader* GetVertexShader(std::string id) { return vertexShaders[id]; }
	static ID3D11PixelShader* GetPixelShader(std::string id) { return pixelShaders[id]; }
	static ID3D11InputLayout* GetInputLayout(std::string id) { return inputLayouts[id]; }

private:
	static ID3D11Device* device;
	static ID3D11DeviceContext* deviceContext;

	static VSMap vertexShaders;
	static PSMap pixelShaders;
	static ILMap inputLayouts;
	static SRVMap shaderResourceViews;
	static SSMap samplerStates;

};

// Convienience.
typedef ResourceManager Resources;

#endif