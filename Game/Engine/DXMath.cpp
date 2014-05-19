// ---------------------------------------------------------------------------
// DXMath.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/18/2014
// ---------------------------------------------------------------------------

#include "DXMath.h"

#pragma region Vector2

Vector2::Vector2(float x, float y)
{
	X = x;
	Y = y;
}

float Vector2::operator[](const int index) const
{
	return *(&X + index);
};

Vector2::operator DirectX::XMFLOAT2()
{
	return DirectX::XMFLOAT2(X, Y);
}

Vector2::operator DirectX::XMFLOAT3()
{
	return DirectX::XMFLOAT3(X, Y, 0.0f);
}

Vector2::operator DirectX::XMFLOAT4()
{
	return DirectX::XMFLOAT4(X, Y, 0.0f, 0.0f);
}

Vector2::operator DirectX::XMVECTOR()
{
	return DirectX::XMVectorSet(X, Y, 0.0f, 0.0f);
}

Vector2 Vector2::Zero()
{
	return Vector2(0.0f, 0.0f);
}

#pragma endregion

#pragma region Vector3

Vector3::Vector3(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

float Vector3::operator[](const int index) const
{
	return *(&X + index);
};

Vector3::operator DirectX::XMFLOAT3()
{
	return DirectX::XMFLOAT3(X, Y, Z);
}

Vector3::operator DirectX::XMFLOAT4()
{
	return DirectX::XMFLOAT4(X, Y, Z, 0.0f);
}

Vector3::operator DirectX::XMVECTOR()
{
	return DirectX::XMVectorSet(X, Y, Z, 0.0f);
}

Vector3 Vector3::Zero()
{
	return Vector3(0.0f, 0.0f, 0.0f);
}

Vector3 Vector3::Right()
{
	return Vector3(1.0f, 0.0f, 0.0f);
}

Vector3 Vector3::Up()
{
	return Vector3(0.0f, 1.0f, 0.0f);
}

Vector3 Vector3::Forward()
{
	return Vector3(0.0f, 0.0f, 1.0f);
}

#pragma endregion

#pragma region Vector4

Vector4::Vector4(float x, float y, float z, float w)
{
	X = x;
	Y = y;
	Z = z;
	W = w;
}

float Vector4::operator[](const int index) const
{
	return *(&X + index);
};

Vector4::operator DirectX::XMFLOAT4()
{
	return DirectX::XMFLOAT4(X, Y, Z, W);
}

Vector4::operator DirectX::XMVECTOR()
{
	return DirectX::XMVectorSet(X, Y, Z, W);
}

Vector4 Vector4::Zero()
{
	return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
}

#pragma endregion

#pragma region Clamps2

Clamps2::Clamps2(float minX, float maxX, float minY, float maxY)
{
	MinX = minX;
	MaxX = maxX;
	MinY = minY;
	MaxY = maxY;
}

Vector2 Clamps2::Minimum()
{
	return Vector2(MinX, MinY);
}

Vector2 Clamps2::Maximum()
{
	return Vector2(MaxX, MaxY);
}

#pragma endregion

#pragma region Clamps3

Clamps3::Clamps3(float minX, float maxX, float minY, float maxY, 
				 float minZ, float maxZ)
{
	MinX = minX;
	MaxX = maxX;
	MinY = minY;
	MaxY = maxY;
	MinZ = minZ;
	MaxZ = maxZ;
}

Vector3 Clamps3::Minimum()
{
	return Vector3(MinX, MinY, MinZ);
}

Vector3 Clamps3::Maximum()
{
	return Vector3(MaxX, MaxY, MaxZ);
}

#pragma endregion

#pragma region Clamps4

Clamps4::Clamps4(float minX, float maxX, float minY, float maxY,
				 float minZ, float maxZ, float minW, float maxW)
{
	MinX = minX;
	MaxX = maxX;
	MinY = minY;
	MaxY = maxY;
	MinZ = minZ;
	MaxZ = maxZ;
	MinW = minW;
	MaxW = maxW;
}

Vector4 Clamps4::Minimum()
{
	return Vector4(MinX, MinY, MinZ, MinW);
}

Vector4 Clamps4::Maximum()
{
	return Vector4(MaxX, MaxY, MaxZ, MaxW);
}

#pragma endregion

#pragma region Matrix2

Matrix2::Matrix2(float r1c1, float r1c2, float r2c1, float r2c2)
{
	R1C1 = r1c1;
	R1C2 = r1c2;
	R2C1 = r2c1;
	R2C2 = r2c2;
}

Vector2 Matrix2::operator[](const int index) const
{
	return Vector2(*(&R1C1 + index * 2 + 0), 
				   *(&R1C1 + index * 2 + 1));
}

Matrix2 Matrix2::Identity()
{
	return Matrix2(1.0f, 0.0f,
				   0.0f, 1.0f);
}

#pragma endregion

#pragma region Matrix3

Matrix3::Matrix3(float r1c1, float r1c2, float r1c3,
				 float r2c1, float r2c2, float r2c3,
				 float r3c1, float r3c2, float r3c3)
{
	R1C1 = r1c1;
	R1C2 = r1c2;
	R1C3 = r1c3;
	R2C1 = r2c1;
	R2C2 = r2c2;
	R2C3 = r2c3;
	R3C1 = r3c1;
	R3C2 = r3c2;
	R3C3 = r3c3;
}

Vector3 Matrix3::operator[](const int index) const
{
	return Vector3(*(&R1C1 + index * 3 + 0), 
				   *(&R1C1 + index * 3 + 1),
				   *(&R1C1 + index * 3 + 2));
}

Matrix3::operator DirectX::XMFLOAT3X3()
{
	return DirectX::XMFLOAT3X3(R1C1, R1C2, R1C3,
							   R2C1, R2C2, R2C3,
							   R3C1, R3C2, R3C3);
}

Matrix3::operator DirectX::XMMATRIX()
{
	return DirectX::XMMATRIX(R1C1, R1C2, R1C3, 0.0f,
							 R2C1, R2C2, R2C3, 0.0f,
							 R3C1, R3C2, R3C3, 0.0f,
							 0.0f, 0.0f, 0.0f, 0.0f);
}

Matrix3 Matrix3::Identity()
{
	return Matrix3(1.0f, 0.0f, 0.0f,
				   0.0f, 1.0f, 0.0f,
				   0.0f, 0.0f, 1.0f);
}

#pragma endregion

#pragma region Matrix4

Matrix4::Matrix4(float r1c1, float r1c2, float r1c3, float r1c4,
				 float r2c1, float r2c2, float r2c3, float r2c4,
				 float r3c1, float r3c2, float r3c3, float r3c4,
				 float r4c1, float r4c2, float r4c3, float r4c4)
{
	R1C1 = r1c1;
	R1C2 = r1c2;
	R1C3 = r1c3;
	R1C4 = r1c4;
	R2C1 = r2c1;
	R2C2 = r2c2;
	R2C3 = r2c3;
	R2C4 = r2c4;
	R3C1 = r3c1;
	R3C2 = r3c2;
	R3C3 = r3c3;
	R3C4 = r3c4;
	R4C1 = r4c1;
	R4C2 = r4c2;
	R4C3 = r4c3;
	R4C4 = r4c4;
}

Vector4 Matrix4::operator[](const int index) const
{
	return Vector4(*(&R1C1 + index * 4 + 0), 
				   *(&R1C1 + index * 4 + 1),
				   *(&R1C1 + index * 4 + 2),
				   *(&R1C1 + index * 4 + 3));
}

Matrix4::operator DirectX::XMFLOAT4X4()
{
	return DirectX::XMFLOAT4X4(R1C1, R1C2, R1C3, R1C4,
							   R2C1, R2C2, R2C3, R2C4,
							   R3C1, R3C2, R3C3, R3C4,
							   R4C1, R4C2, R4C3, R4C4);
}

Matrix4::operator DirectX::XMMATRIX()
{
	return DirectX::XMMATRIX(R1C1, R1C2, R1C3, R1C4,
							 R2C1, R2C2, R2C3, R2C4,
							 R3C1, R3C2, R3C3, R3C4,
							 R4C1, R4C2, R4C3, R4C4);
}

Matrix4 Matrix4::Identity()
{
	return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
				   0.0f, 1.0f, 0.0f, 0.0f,
				   0.0f, 0.0f, 1.0f, 0.0f,
				   0.0f, 0.0f, 0.0f, 1.0f);
}

#pragma endregion

#pragma region Quaternion

Quaternion::Quaternion(float w, float x, float y, float z)
{
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

void Quaternion::Normalize()
{
	float n = w * w + x * x + y * y + z * z;

	if (n == 1) return;

	*this *= 1.0f / sqrt(n);
}

void Quaternion::Rotate(Vector3 axis, float fAngle)
{
	float wLocal = cosf(fAngle / 2);
	float xLocal = sinf(fAngle / 2) * axis.X;
	float yLocal = sinf(fAngle / 2) * axis.Y;
	float zLocal = sinf(fAngle / 2) * axis.Z;

	*this *= Quaternion(wLocal, xLocal, yLocal, zLocal);
}

DirectX::XMMATRIX Quaternion::GetRotationMatrix() const
{
	/*
	return DirectX::XMMATRIX(W*W + X*X - Y*Y - Z*Z, 2*X*Y - 2*W*Z,			2*X*Z + 2*W*Y,			0,
							 2*X*Y + 2*W*Z,			W*W - X*X + Y*Y - Z*Z,	2*Y*Z + 2*W*X,			0,
							 2*X*Z - 2*W*Y,			2*Y*Z - 2*W*X,			W*W + X*X - Y*Y - Z*Z,	0,
							 0,						0,						0,						1);
	*/
	/* optimization for unit quaternions */
	return DirectX::XMMATRIX(1.0f - 2*y*y - 2*z*z,	2*x*y - 2*w*z,			2*x*z + 2*w*y,			0,
							 2*x*y + 2*w*z,			1.0f - 2*x*x - 2*z*z,	2*y*z + 2*w*x,			0,
							 2*x*z - 2*w*y,			2*y*z - 2*w*x,			1.0f - 2*x*x - 2*y*y,	0,
							 0,						0,						0,						1);
}

Quaternion Quaternion::FromRollPitchYaw(float x, float y, float z)
{
	// roll
	const float sr = sin(x * 0.5f);
	const float cr = cos(x * 0.5f);

	// pitch
	const float sp = sin(y * 0.5f);
	const float cp = cos(y * 0.5f);

	// yaw
	const float sy = sin(z * 0.5f);
	const float cy = cos(z * 0.5f);

	return Quaternion(cr * cp * cy + sr * sp * sy,
					  sr * cp * cy - cr * sp * sy,
					  cr * sp * cy + sr * cp * sy,
					  cr * cp * sy - sr * sp * cy);
}

Quaternion Quaternion::operator*(const float& rhs) const
{
	return Quaternion(this->w * rhs,
					  this->x * rhs,
					  this->y * rhs,
					  this->z * rhs);
}

Quaternion Quaternion::operator*(const Quaternion& rhs) const
{
	return Quaternion((this->w * rhs.w) - (this->x * rhs.x) - (this->y * rhs.y) - (this->z * rhs.z),
					  (this->w * rhs.x) + (this->x * rhs.w) + (this->y * rhs.z) - (this->z * rhs.y),
					  (this->w * rhs.y) - (this->x * rhs.z) + (this->y * rhs.w) + (this->z * rhs.x),
					  (this->w * rhs.z) + (this->x * rhs.y) - (this->y * rhs.x) + (this->z * rhs.w));
}

void Quaternion::operator*=(const float& rhs)
{
	this->w *= rhs;
	this->x *= rhs;
	this->y *= rhs;
	this->z *= rhs;
}

void Quaternion::operator*=(const Quaternion& rhs)
{
	this->w = (this->w * rhs.w) - (this->x * rhs.x) - (this->y * rhs.y) - (this->z * rhs.z);
	this->x = (this->w * rhs.x) + (this->x * rhs.w) + (this->y * rhs.z) - (this->z * rhs.y);
	this->y = (this->w * rhs.y) - (this->x * rhs.z) + (this->y * rhs.w) + (this->z * rhs.x);
	this->z = (this->w * rhs.z) + (this->x * rhs.y) - (this->y * rhs.x) + (this->z * rhs.w);
}

Quaternion::operator DirectX::XMFLOAT4()
{
	return DirectX::XMFLOAT4(x, y, z, w);
}

Quaternion::operator DirectX::XMVECTOR()
{
	return DirectX::XMVectorSet(x, y, z, w);
}

Quaternion Quaternion::Identity()
{
	return Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
}

#pragma endregion