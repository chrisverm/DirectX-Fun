// ---------------------------------------------------------------------------
// Mesh.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/06/2014
// ---------------------------------------------------------------------------

#include "Mesh.h"

Mesh::Mesh(MeshDesc* desc)
	: NumVertices(numVerts), NumIndices(numInds), ILName(desc->ILName)
{
	this->numVerts		= desc->NumVerts;
	this->vertexBytes	= desc->VertexBytes;
	this->numInds		= desc->NumInds;
	this->vertices		= desc->Vertices;
	this->indices		= desc->Indices;
	this->topology		= desc->Topology;

	/* currently not doing anything with vertexDesc & numSemantics in desc */
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

void Mesh::Initialize(ID3D11Device* device, ID3D11InputLayout* inputLayout)
{
	this->inputLayout = inputLayout;

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

	deviceContext->IASetInputLayout(inputLayout);
	deviceContext->IASetPrimitiveTopology(topology);
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

	// remove all unnecessary whitespace from file before reading data
	while (fileData.find("\n\n") != std::string::npos)
	{
		fileData = fileData.erase(fileData.find("\n\n"), 1);
	}
	while (fileData.find(" \n") != std::string::npos)
	{
		fileData = fileData.erase(fileData.find(" \n"), 1);
	}
	while (fileData.find("\n ") != std::string::npos)
	{
		fileData = fileData.erase(fileData.find("\n ") + 1, 1);
	}

	int numLines = std::count(fileData.begin(), fileData.end(), '\n');

	enum Topology
	{
		NONE = 0,
		POINT = 1,
		LINE = 2,
		TRIANGLE = 3,
		QUAD = 4
	};

	std::map<std::string, std::vector<float*>> objInfo;
	std::vector<std::string> faces = std::vector<std::string>(); // COULD INCLUDE START SIZE FOR BETTER EFFICIENCY
	Topology topology = NONE;
	std::string* split = nullptr;
	UINT currLineFloatCount = 0;

	while (fileData.length() > 0)
	{
		currLine = fileData.substr(0, fileData.find_first_of('\n'));
		fileData = fileData.substr(currLine.length() + 1, fileData.length());
		split	 = Split(currLine, ' ', &currLineFloatCount);

		if (split[0] == "f")
		{
			if (topology == NONE)
			{
				topology = (Topology)std::count(currLine.begin(), currLine.end(), ' ');
			}

			faces.push_back(currLine.erase(0, split[0].length() + 1));
		}
		else
		{
			float* data = new float[currLineFloatCount];

			for (UINT i = 0; i < currLineFloatCount; i++)
			{
				data[i] = (float)atof(split[1 + i].c_str());
			}

			objInfo[split[0]].push_back(data);
		}

		delete[] split;
		split = nullptr;
	}

	UINT faceCount = faces.size();
	UINT numFaceElements = 1;
	std::string* formatSplit = Split(faceFormat, '/', &numFaceElements);

	UINT vertexFloatCount = 0;
	for (UINT i = 0; i < numFaceElements; i++)
	{
		std::string val = formatSplit[i].substr(0, formatSplit[i].find_first_not_of("0123456789"));
		vertexFloatCount += (UINT)atoi(val.c_str());
	}

	MeshDesc desc;
	desc.NumVerts = faceCount * topology;
	desc.NumInds = faceCount * topology;;
	desc.VertexBytes = vertexFloatCount * sizeof(float);
	desc.Vertices = new float[desc.VertexBytes * topology * faceCount];

	UINT index = 0;
	for (UINT faceIndex = 0; faceIndex < faceCount; faceIndex++)
	{
		std::string currFace = faces[faceIndex];
		std::string* faceSplit = Split(currFace, ' ');

		for (UINT vertIndex = 0; vertIndex < (UINT)topology; vertIndex++)
		{
			std::string* elemSplit = Split(faceSplit[vertIndex], '/');

			for (UINT elemIndex = 0; elemIndex < numFaceElements; elemIndex++)
			{
				UINT element = (UINT)atoi(elemSplit[elemIndex].c_str()) - 1;
				UINT numElems = (UINT)atoi(formatSplit[elemIndex].c_str());

				for (UINT floatIndex = 0; floatIndex < numElems; floatIndex++)
				{
					std::string id = formatSplit[elemIndex].substr(
						formatSplit[floatIndex].find_first_not_of("0123456789"), 
						formatSplit[elemIndex].length());

					desc.Vertices[index] = ((float*)objInfo[id][element])[floatIndex];

					index++;
				}
			}

			delete[] elemSplit;
			elemSplit = nullptr;
		}

		delete[] faceSplit;
		faceSplit = nullptr;
	}
	
	/*struct Vertex
	{
		XMFLOAT3 Position;
		XMFLOAT3 Normal;
		XMFLOAT2 UV;
	};

	Vertex* verts = (Vertex*)vertices;*/
	
	delete[] formatSplit;
	formatSplit = nullptr;

	// release stored data memory in objInfo map
	std::map<std::string, std::vector<float*>>::iterator it;
	for (it = objInfo.begin(); it != objInfo.end(); it++)
	{
		for (size_t i = 0; i < it->second.size(); i++)
		{
			delete it->second[i];
			it->second[i] = nullptr;
		}
	}

	desc.Indices = new UINT[desc.NumInds];
	for (UINT i = 0; i < desc.NumInds; i++)
	{ desc.Indices[i] = i; }

	switch (topology)
	{
	case POINT:		desc.Topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;		break;
	case LINE:		desc.Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;		break;
	case TRIANGLE:	desc.Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;	break;
	default: DXTRACE_ERR_MSGBOX(L"Problem getting mesh topology.", NULL);	break;
	}

	desc.VertexDesc = nullptr;
	desc.NumSemantics = 0;
	desc.ILName = "";
	
	return new Mesh(&desc);
}