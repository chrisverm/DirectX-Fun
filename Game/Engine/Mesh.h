// ---------------------------------------------------------------------------
// Mesh.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/02/2014
// ---------------------------------------------------------------------------

#ifndef MESH_H
#define MESH_H

#include <map>
#include <vector>
#include <fstream>
#include <d3d11.h>
#include "Globals.h"

using namespace DirectX;

class Mesh
{
public:
	Mesh(void* vertices, UINT vertexByteSize, UINT numVerts, UINT indices[], UINT numIndices);
	~Mesh();
	void Initialize(ID3D11Device* device, ID3D11InputLayout* inputLayout, D3D_PRIMITIVE_TOPOLOGY topology);
	void SetBuffers(ID3D11DeviceContext* deviceContext);

	static Mesh* Mesh::LoadFromOBJ(std::string objFilePath, std::string faceFormat = "v/vt/vn/vc");

private:
	UINT numVerts, numInds;
	size_t vertexBytes;
	void* vertices;
	UINT* indices;
	
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11InputLayout* inputLayout;
	D3D_PRIMITIVE_TOPOLOGY topology;

	void Test(void* blah);

};

#endif