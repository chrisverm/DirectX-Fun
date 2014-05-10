// ---------------------------------------------------------------------------
// Mesh.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/05/2014
// ---------------------------------------------------------------------------

#ifndef MESH_H
#define MESH_H

#include <map>
#include <vector>
#include <fstream>
#include <d3d11.h>
#include "Globals.h"
#include "ResourceManager.h"

using namespace DirectX;

struct MeshDesc
{
	UINT NumVerts, NumInds;
	size_t VertexBytes;
	float* Vertices;
	UINT* Indices;

	D3D_PRIMITIVE_TOPOLOGY Topology;

	D3D11_INPUT_ELEMENT_DESC* VertexDesc;
	UINT NumSemantics;
	std::string ILName;
};

class Mesh
{
public:
	Mesh(MeshDesc* desc);
	~Mesh();
	void Initialize(ID3D11Device* device, ID3D11InputLayout* inputLayout);
	void SetBuffers(ID3D11DeviceContext* deviceContext);

	static Mesh* Mesh::LoadFromOBJ(std::string objFilePath, std::string faceFormat = "3v/3vn/2vt");

	const UINT& NumVertices;
	const UINT& NumIndices;
	const std::string& ILName;

private:
	UINT numVerts, numInds;
	size_t vertexBytes;
	float* vertices;
	UINT* indices;
	
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11InputLayout* inputLayout;
	D3D_PRIMITIVE_TOPOLOGY topology;

	// input layout name, used for finding in ResourceManager
	std::string iLName;

};

#endif