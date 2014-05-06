// ---------------------------------------------------------------------------
// Mesh.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/06/2014
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
	int vertsPerFace = 0;

	while (fileData.length() > 0)
	{
		currLine = fileData.substr(0, fileData.find_first_of('\n'));
		split	 = Split(currLine, ' ', &numDelims);
		fileData = fileData.substr(currLine.length() + 1, fileData.length());

		if (split[0] == "f")
		{
			if (vertsPerFace == 0) vertsPerFace = std::count(currLine.begin(), currLine.end(), ' ');

			objInfo["f"].push_back(new std::string(currLine.begin() + split[0].length() + 1, currLine.end()));
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

		delete[] split;
		split = nullptr;
	}
	
	int numFaces = objInfo["f"].size();
	int numFaceElements = 0;
	int vertexFloatSize = 0; // RENAME THIS
	std::string* formatSplit = Split(faceFormat, '/', &numFaceElements);
	numFaceElements += 1;

	for (int i = 0; i < numFaceElements; i++)
	{
		vertexFloatSize += atoi(formatSplit[i].substr(0, 1).c_str());	// WONT WORK FOR NUMBERS OVER 9
	}

	size_t vertexBytes = sizeof(float) * vertexFloatSize;
	float* vertices = new float[vertexFloatSize * vertsPerFace * numFaces];

	int index = 0;
	for (int fIndex = 0; fIndex < objInfo["f"].size(); fIndex++) // which face
	{
		std::string face = *((std::string*)objInfo["f"][fIndex]);
		std::string* faceSplit = Split(face, ' ');

		for (int fVertex = 0; fVertex < vertsPerFace; fVertex++) // which vertex in that face
		{
			std::string* elemSplit = Split(faceSplit[fVertex], '/');

			for (int vElement = 0; vElement < numFaceElements; vElement++) // which element in that vertex
			{
				int ind = atoi(elemSplit[vElement].c_str());

				for (int eIndex = 0; eIndex < atoi(formatSplit[vElement].c_str()); eIndex++) // which float in that element
				{
					std::string id = formatSplit[vElement].substr(1, formatSplit[vElement].length());

					vertices[index] = ((float*)objInfo[id][ind - 1])[eIndex];

					index++;
				}
			}

			delete[] elemSplit;
			elemSplit = nullptr;
		}

		delete[] faceSplit;
		faceSplit = nullptr;
	}

	delete[] formatSplit;
	formatSplit = nullptr;

	//Vertex* verts = (Vertex*)vertices;

	// BELOW HERE IS PLACEHOLDER, HARDCODED TO REMOVE ALL MEMORY LEAKS
	delete[] vertices;
	vertices = nullptr;

	std::vector<void*>* fList = &objInfo["f"];
	std::vector<void*>* vList = &objInfo["v"];
	std::vector<void*>* vnList = &objInfo["vn"];
	std::vector<void*>* vtList = &objInfo["vt"];
	std::vector<void*>* vcList = &objInfo["vc"];
	for (size_t i = 0; i < fList->size(); i++)
	{
		delete (std::string*)(*fList)[i];
		(*fList)[i] = nullptr;
	}
	for (size_t i = 0; i < vList->size(); i++)
	{
		delete[] (float*)(*vList)[i];
		(*vList)[i] = nullptr;
	}
	for (size_t i = 0; i < vnList->size(); i++)
	{
		delete[] (float*)(*vnList)[i];
		(*vnList)[i] = nullptr;
	}
	for (size_t i = 0; i < vtList->size(); i++)
	{
		delete[] (float*)(*vtList)[i];
		(*vtList)[i] = nullptr;
	}
	for (size_t i = 0; i < vcList->size(); i++)
	{
		delete[] (float*)(*vcList)[i];
		(*vcList)[i] = nullptr;
	}

	return nullptr;
}