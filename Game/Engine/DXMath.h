// ---------------------------------------------------------------------------
// DXMath.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/17/2014
// ---------------------------------------------------------------------------

#ifndef DX_MATH_H
#define DX_MATH_H

#include <DirectXMath.h>

#define PI 3.14159265f
#define DegsToReds PI / 180.0f
#define RadsToDegs 180.0f / PI

struct Vector2
{
	float X, Y;

	Vector2(float x = 0, float y = 0) { X = x; Y = y; }

	static Vector2 Zero() { return Vector2(0.0f, 0.0f); }

	operator DirectX::XMFLOAT2() { return DirectX::XMFLOAT2(X, Y); }
	operator DirectX::XMFLOAT3() { return DirectX::XMFLOAT3(X, Y, 0); }
	operator DirectX::XMFLOAT4() { return DirectX::XMFLOAT4(X, Y, 0, 0); }
	operator DirectX::XMVECTOR() { return DirectX::XMVectorSet(X, Y, 0, 0); }
};

struct Vector3
{
	float X, Y, Z;

	Vector3(float x = 0, float y = 0, float z = 0) { X = x; Y = y; Z = z; }

	static Vector3 Zero()		{ return Vector3(0.0f, 0.0f, 0.0f); }
	static Vector3 Right()		{ return Vector3(1.0f, 0.0f, 0.0f); }
	static Vector3 Up()			{ return Vector3(0.0f, 1.0f, 0.0f); }
	static Vector3 Forward()	{ return Vector3(0.0f, 0.0f, 1.0f); }

	operator DirectX::XMFLOAT3() { return DirectX::XMFLOAT3(X, Y, Z); }
	operator DirectX::XMFLOAT4() { return DirectX::XMFLOAT4(X, Y, Z, 0); }
	operator DirectX::XMVECTOR() { return DirectX::XMVectorSet(X, Y, Z, 0); }
};

struct Vector4
{
	float X, Y, Z, W;

	Vector4(float x = 0, float y = 0, float z = 0, float w = 0) { X = x; Y = y; Z = z; W = w; }

	static Vector4 Zero() { return Vector4(0.0f, 0.0f, 0.0f, 0.0f); }

	operator DirectX::XMFLOAT4() { return DirectX::XMFLOAT4(X, Y, Z, W); }
	operator DirectX::XMVECTOR() { return DirectX::XMVectorSet(X, Y, Z, W); }
};

class Quaternion
{
public:
	Quaternion(float w = 1.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f);
	void Normalize();
	void Rotate(Vector3 axis, float fAngle);

	DirectX::XMMATRIX GetRotationMatrix() const;

	static Quaternion Identity() { return Quaternion(1.0f, 0.0f, 0.0f, 0.0f); }
	static Quaternion FromRollPitchYaw(float x, float y, float z);

	Quaternion operator*(const float& rhs) const;
	Quaternion operator*(const Quaternion& rhs) const;

	void operator*=(const float& rhs);
	void operator*=(const Quaternion& rhs);

	operator DirectX::XMFLOAT4() { return DirectX::XMFLOAT4(x, y, z, w); }
	operator DirectX::XMVECTOR() { return DirectX::XMVectorSet(x, y, z, w); }

private:
	float w, x, y, z;

};

#endif