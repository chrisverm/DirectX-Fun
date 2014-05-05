// ---------------------------------------------------------------------------
// Mesh.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/02/2014
// ---------------------------------------------------------------------------

#include "Mesh.h"

Mesh::Mesh(void* verts, size_t vBytes, UINT vSize, UINT inds[], UINT iSize)
{
	vertices = verts;
	vertexBytes = vBytes;
	numVerts = iSize;
	indices = inds;
	numInds = iSize;
}

Mesh::~Mesh()
{
	if (vertexBuffer != nullptr)
	{
		ReleaseMacro(vertexBuffer);
		vertexBuffer = nullptr;
	}

	if (indexBuffer != nullptr)
	{
		ReleaseMacro(indexBuffer);
		indexBuffer = nullptr;
	}

	if (vertices != nullptr)
	{
		delete[] vertices;
		vertices = nullptr;
	}

	if (indices != nullptr)
	{
		delete[] indices;
		indices = nullptr;
	}
}

void Mesh::Initialize(ID3D11Device* device, ID3D11InputLayout* inputLayout, D3D_PRIMITIVE_TOPOLOGY topology)
{
	this->inputLayout = inputLayout;
	this->topology = topology;

	// Create the vertex buffer
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = vertexBytes * numVerts;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA initialVertexData;
	initialVertexData.pSysMem = vertices;
	HR(device->CreateBuffer(&vbd, &initialVertexData, &vertexBuffer));

	// Create the index buffer
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * numInds;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA initialIndexData;
	initialIndexData.pSysMem = indices;
	HR(device->CreateBuffer(&ibd, &initialIndexData, &indexBuffer));
}

void Mesh::SetBuffers(ID3D11DeviceContext* deviceContext)
{
	UINT stride = vertexBytes;
	UINT offset = 0;

	deviceContext->IASetPrimitiveTopology(topology);
	deviceContext->IASetInputLayout(inputLayout);
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

Mesh* Mesh::LoadFromOBJ(std::string objFilePath, std::string faceFormat = "v/vt/vn/vc")
{
	std::string data = "";
	std::string line = "";

	std::ifstream file;
	file.exceptions( std::ifstream::failbit | std::ifstream::badbit );
	int numLine = 0;

	// read OBJ fine in as text
	try
	{
		file.open(objFilePath.c_str());

		while (!file.eof())
		{
			std::getline(file, line);
			data += line + '\n';
			numLine++;
		}

		file.close();
	}
	catch (std::ifstream::failure e)
	{
		std::wstring wpath = std::wstring(objFilePath.begin(), objFilePath.end());
		std::wstring error = L"Cannot read OBJ from path \"" + wpath + L"\". Stopped at line " + std::to_wstring(numLine);
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		file.close();
	}

	// remove all comments from file before reading data
	while (std::count(data.begin(), data.end(), '#') > 0)
	{
		int comment = data.find_first_of('#');

		while (comment != 0 && data[comment - 1] == ' ')
			comment--;

		while (data[comment] != '\n')
			data.erase(comment, 1);
	}

	// remove all blank lines from file before reading data
	while (data.find("\n\n") != std::string::npos)
	{
		data = data.erase(data.find("\n\n"), 1);
	}

	int numLines = std::count(data.begin(), data.end(), '\n');

	for (int i = 0; i < numLines; i++)
	{

	}

	std::map<std::string, std::vector<void*>> objMap;
	std::string* split = nullptr;
	std::string id = "", xmfloat = "";

	while (data.length() > 0)
	{
		split = nullptr;
		line = data.substr(0, data.find_first_of('\n'));
		id   = line.substr(0, data.find_first_of(' '));
		data = data.substr(line.length() + 1, data.length());

		

		if (id == "f")
		{
			
		}
		else
		{
			xmfloat = line.substr(id.length(), line.length());
			std::string* xmfloatArr = Split(xmfloat.substr(1, xmfloat.length()), ' ');

			int numData = std::count(xmfloat.begin(), xmfloat.end(), ' ');
			float* floatData = new float[numData]; //malloc(sizeof(float) * numData);

			for (int i = 0; i < numData; i++)
			{
				floatData[i] = atof(xmfloatArr[i].c_str());
			}

			objMap[id].push_back(floatData);

			/*
			if (std::count(xmfloat.begin(), xmfloat.end(), ' ') + 1 == 2)
			{
				std::string* xmfloatArr = Split(xmfloat.substr(1, xmfloat.length()), ' ');
				objMap[id].push_back(new XMFLOAT2(
					atof(xmfloatArr[0].c_str()),
					atof(xmfloatArr[1].c_str())
					));
			}
			if (std::count(xmfloat.begin(), xmfloat.end(), ' ') + 1 == 3)
			{
				std::string* xmfloatArr = Split(xmfloat.substr(1, xmfloat.length()), ' ');
				objMap[id].push_back(new XMFLOAT3(
					atof(xmfloatArr[0].c_str()),
					atof(xmfloatArr[1].c_str()), 
					atof(xmfloatArr[2].c_str())
					));
			}
			if (std::count(xmfloat.begin(), xmfloat.end(), ' ') + 1 == 4)
			{
				std::string* xmfloatArr = Split(xmfloat.substr(1, xmfloat.length()), ' ');
				objMap[id].push_back(new XMFLOAT4(
					atof(xmfloatArr[0].c_str()),
					atof(xmfloatArr[1].c_str()), 
					atof(xmfloatArr[2].c_str()),
					atof(xmfloatArr[3].c_str())
					));
			}
			*/
		}
	}

	float v1  = *(float*)objMap["v"][1];
	float vn1 = *(float*)objMap["vn"][1];
	float vt1 = *(float*)objMap["vt"][1];
	float vc1 = *(float*)objMap["vc"][0];
	
	void* stuff = malloc(sizeof(float) * 10);
	float num1 = 1.0f, num2 = 2.0f;
	memcpy((BYTE*)stuff + 0, &num1, sizeof(float));
	memcpy((BYTE*)stuff + 4, &num2, sizeof(float));

	return nullptr;
}