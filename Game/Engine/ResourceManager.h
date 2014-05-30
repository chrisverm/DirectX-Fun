// ---------------------------------------------------------------------------
// ResourceManager.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/30/2014
// ---------------------------------------------------------------------------

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <d3d11.h>
#include <d3dcompiler.h>
#include "Globals.h"
#include "WICTextureLoader.h"
#include "Mesh.h"
#include "Material.h"

typedef std::map<std::string, Mesh*> MeMap;
typedef std::map<std::string, Material*> MaMap;
typedef std::map<std::string, ID3D11VertexShader*> VSMap;
typedef std::map<std::string, ID3D11PixelShader*> PSMap;
typedef std::map<std::string, ID3D11InputLayout*> ILMap;
typedef std::map<std::string, ID3D11ShaderResourceView*> SRVMap;
typedef std::map<std::string, ID3D11SamplerState*> SSMap;
typedef std::map<std::string, ID3D11RasterizerState*> RSMap;
typedef std::map<std::string, ID3D11DepthStencilState*> DSSMap;

class ResourceManager
{
public:
	static void Release();

	static void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext);

	static bool AddMesh(std::string id, Mesh* mesh);
	static bool AddMaterial(std::string id, Material* material);
	static bool AddVertexShader(std::string id, ID3D11VertexShader* vertexShader);
	static bool AddPixelShader(std::string id, ID3D11PixelShader* pixelShader);
	static bool AddInputLayout(std::string id, ID3D11InputLayout* inputLayout);
	static bool AddShaderResourceView(std::string id, ID3D11ShaderResourceView* shaderResourceView);
	static bool AddSamplerState(std::string id, ID3D11SamplerState* samplerState);
	static bool AddRasterizerState(std::string id, ID3D11RasterizerState* rasterizerState);
	static bool AddDepthStencilState(std::string id, ID3D11DepthStencilState* depthStencilState);

	static bool CreateMesh(std::string id, std::string objFilePath, std::string faceFormat, ID3D11InputLayout* inputLayout);
	static bool CreateMaterial(std::string id, ID3D11VertexShader* vertexShader, ID3D11PixelShader* pixelShader,
		ID3D11ShaderResourceView* shaderResourceView = nullptr, ID3D11SamplerState* samplerState = nullptr);
	static bool CreateVertexShaderAndInputLayout(std::string id, std::wstring filepath, D3D11_INPUT_ELEMENT_DESC layoutDesc[], UINT numElements);
	static bool CreatePixelShader(std::string id, std::wstring filepath);
	static bool CreateShaderResourceView(std::string id, std::wstring textureFilePath);
	static bool CreateSamplerState(std::string id, D3D11_SAMPLER_DESC samplerDesc);
	static bool CreateRasterizerState(std::string id, D3D11_RASTERIZER_DESC rasterizerDesc);
	static bool CreateDepthStencilState(std::string id, D3D11_DEPTH_STENCIL_DESC depthStencilDesc);

	static Mesh* GetMesh(std::string id) { return meshes[ToUpper(id)]; }
	static Material* GetMaterial(std::string id) { return materials[ToUpper(id)]; }
	static ID3D11VertexShader* GetVertexShader(std::string id) { return vertexShaders[ToUpper(id)]; }
	static ID3D11PixelShader* GetPixelShader(std::string id) { return pixelShaders[ToUpper(id)]; }
	static ID3D11InputLayout* GetInputLayout(std::string id) { return inputLayouts[ToUpper(id)]; }
	static ID3D11ShaderResourceView* GetShaderResourceView(std::string id) { return shaderResourceViews[ToUpper(id)]; }
	static ID3D11SamplerState* GetSamplerState(std::string id) { return samplerStates[ToUpper(id)]; }
	static ID3D11RasterizerState* GetRasterizerState(std::string id) { return rasterizerStates[ToUpper(id)]; }
	static ID3D11DepthStencilState* GetDepthStencilState(std::string id) { return depthStencilStates[id]; }

private:
	static ID3D11Device* device;
	static ID3D11DeviceContext* deviceContext;

	static MeMap meshes;
	static MaMap materials;
	static VSMap vertexShaders;
	static PSMap pixelShaders;
	static ILMap inputLayouts;
	static SRVMap shaderResourceViews;
	static SSMap samplerStates;
	static RSMap rasterizerStates;
	static DSSMap depthStencilStates;

};

// Convienience.
typedef ResourceManager Resources;

#endif