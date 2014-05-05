// ---------------------------------------------------------------------------
// Mesh.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/05/2014
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

Mesh* Mesh::LoadFromOBJ(std::string objFilePath, std::string faceFormat)
{
	std::string fileData = "";
	std::string currLine = "";

	std::ifstream file;
	file.exceptions( std::ifstream::failbit | std::ifstream::badbit );
	int lineNum = 0;

	// read OBJ fine in as text
	try
	{
		file.open(objFilePath.c_str());

		while (!file.eof())
		{
			std::getline(file, currLine);
			fileData += currLine + '\n';
			lineNum++;
		}

		file.close();
	}
	catch (std::ifstream::failure e)
	{
		std::wstring wpath = std::wstring(objFilePath.begin(), objFilePath.end());
		std::wstring error = L"Cannot read OBJ from path \"" + wpath + L"\". Stopped at line " + std::to_wstring(lineNum);
		DXTRACE_ERR_MSGBOX(error.c_str(), NULL);
		file.close();
	}

	// remove all comments from file before reading data
	while (std::count(fileData.begin(), fileData.end(), '#') > 0)
	{
		int comment = fileData.find_first_of('#');

		while (comment != 0 && fileData[comment - 1] == ' ')
			comment--;

		while (fileData[comment] != '\n')
			fileData.erase(comment, 1);
	}

	// remove all blank lines from file before reading data
	while (fileData.find("\n\n") != std::string::npos)
	{
		fileData = fileData.erase(fileData.find("\n\n"), 1);
	}

	int numLines = std::count(fileData.begin(), fileData.end(), '\n');

	std::map<std::string, std::vector<void*>> objInfo;
	std::string* split = nullptr;
	int numDelims = 0;

	while (fileData.length() > 0)
	{
		currLine = fileData.substr(0, fileData.find_first_of('\n'));
		split	 = Split(currLine, ' ', &numDelims);
		fileData = fileData.substr(currLine.length() + 1, fileData.length());

		if (split[0] == "f")
		{
			objInfo["f"].push_back(new std::string(split[1]));
		}
		else
		{
			float* data = new float[numDelims];

			for (int i = 0; i < numDelims; i++)
			{
				data[i] = atof(split[i + 1].c_str());
			}

			objInfo[split[0]].push_back(data);
		}
	}

	for (int i = 0; i < objInfo["f"].size(); i++)
	{
		// use faceFormat to determine order of data to include
	}

	/*float v1  = *(float*)objInfo["v"][7];
	float vn1 = *(float*)objInfo["vn"][5];
	float vt1 = *(float*)objInfo["vt"][3];
	float vc1 = *(float*)objInfo["vc"][0];*/

	return nullptr;
}