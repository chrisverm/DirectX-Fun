// ---------------------------------------------------------------------------
// Material.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/02/2014
// ---------------------------------------------------------------------------

#include "Material.h"

Material::Material(ID3D11VertexShader* vertexShader, ID3D11PixelShader* pixelShader)
	: IsTextured(textured)
{
	this->vertexShader = vertexShader;
	this->pixelShader = pixelShader;

	textured = false;
}

Material::~Material() { }

void Material::SetTexture(ID3D11ShaderResourceView* shaderResourceView, ID3D11SamplerState* samplerState)
{
	this->shaderResourceView = shaderResourceView;
	this->samplerState = samplerState;

	textured = true;
}

void Material::SetShaders(ID3D11DeviceContext* deviceContext)
{
	deviceContext->VSSetShader(vertexShader, NULL, 0);
	deviceContext->PSSetShader(pixelShader, NULL, 0);

	deviceContext->PSSetShaderResources(0, 1, &shaderResourceView);
	deviceContext->PSSetSamplers(0, 1, &samplerState);
}