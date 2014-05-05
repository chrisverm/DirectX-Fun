// ---------------------------------------------------------------------------
// Material.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/04/2014
// ---------------------------------------------------------------------------

#ifndef MATERIAL_H
#define MATERIAL_H

#include <d3d11.h>
#include "Globals.h"

class Material
{
public:
	Material(ID3D11VertexShader* vShader, ID3D11PixelShader* pixelShader);
	~Material();
	void SetTexture(ID3D11ShaderResourceView* shaderResourceView, ID3D11SamplerState* samplerState);
	void SetShaders(ID3D11DeviceContext* deviceContext);

	const bool& IsTextured;

private:
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;

	bool textured;
	ID3D11ShaderResourceView* shaderResourceView;
	ID3D11SamplerState* samplerState;

};

#endif