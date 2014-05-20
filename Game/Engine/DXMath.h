// ---------------------------------------------------------------------------
// DXMath.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/19/2014
// ---------------------------------------------------------------------------

#ifndef DX_MATH_H
#define DX_MATH_H

#include <DirectXMath.h>

#define PI 3.14159265f
#define DegsToReds PI / 180.0f
#define RadsToDegs 180.0f / PI

// forward declerations
class Clamps1;
class Clamps2;
class Clamps3;
class Clamps4;

class Vector2
{
public:
	float X, Y;

	Vector2(float x = 0.0f, float y = 0.0f);

	void Normalize();
	void ClampLength(Clamps1 clamps);

	static float Dot(Vector2 v1, Vector2 v2);

	float operator[](const int index) const;
	Vector2 operator-() const;
	Vector2 operator+(const Vector2& rhs) const;
	Vector2 operator-(const Vector2& rhs) const;
	Vector2 operator*(const float& rhs) const;
	Vector2 operator/(const float& rhs) const;
	void operator+=(const Vector2& rhs);
	void operator-=(const Vector2& rhs);
	void operator*=(const float& rhs);
	void operator/=(const float& rhs);

	operator DirectX::XMFLOAT2();
	operator DirectX::XMFLOAT3();
	operator DirectX::XMFLOAT4();
	operator DirectX::XMVECTOR();

	static Vector2 Zero();
	static Vector2 Min();
	static Vector2 Max();
};

class Vector3
{
public:
	float X, Y, Z;

	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

	void Normalize();
	void ClampLength(Clamps1 clamps);

	static float Dot(Vector3 v1, Vector3 v2);
	static Vector3 Cross(Vector3 v1, Vector3 v2);

	float operator[](const int index) const;
	Vector3 operator-() const;
	Vector3 operator+(const Vector3& rhs) const;
	Vector3 operator-(const Vector3& rhs) const;
	Vector3 operator*(const float& rhs) const;
	Vector3 operator/(const float& rhs) const;
	void operator+=(const Vector3& rhs);
	void operator-=(const Vector3& rhs);
	void operator*=(const float& rhs);
	void operator/=(const float& rhs);

	operator DirectX::XMFLOAT3();
	operator DirectX::XMFLOAT4();
	operator DirectX::XMVECTOR();

	static Vector3 Zero();
	static Vector3 Min();
	static Vector3 Max();
	static Vector3 Right();
	static Vector3 Up();
	static Vector3 Forward();
};

class Vector4
{
public:
	float X, Y, Z, W;

	Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);

	void Normalize();
	void ClampLength(Clamps1 clamps);

	static float Dot(Vector4 v1, Vector4 v2);

	float operator[](const int index) const;
	Vector4 operator-() const;
	Vector4 operator+(const Vector4& rhs) const;
	Vector4 operator-(const Vector4& rhs) const;
	Vector4 operator*(const float& rhs) const;
	Vector4 operator/(const float& rhs) const;
	void operator+=(const Vector4& rhs);
	void operator-=(const Vector4& rhs);
	void operator*=(const float& rhs);
	void operator/=(const float& rhs);

	operator DirectX::XMFLOAT4();
	operator DirectX::XMVECTOR();

	static Vector4 Zero();
	static Vector4 Min();
	static Vector4 Max();
};

class Matrix2
{
public:
	float R1C1, R1C2;
	float R2C1, R2C2;

	Matrix2(float r1c1 = 0.0f, float r1c2 = 0.0f,
			float r2c1 = 0.0f, float r2c2 = 0.0f);

	Vector2 operator[](const int index) const;

	static Matrix2 Identity();
};

class Matrix3
{
public:
	float R1C1, R1C2, R1C3;
	float R2C1, R2C2, R2C3;
	float R3C1, R3C2, R3C3;

	Matrix3(float r1c1 = 0.0f, float r1c2 = 0.0f, float r1c3 = 0.0f,
			float r2c1 = 0.0f, float r2c2 = 0.0f, float r2c3 = 0.0f,
			float r3c1 = 0.0f, float r3c2 = 0.0f, float r3c3 = 0.0f);

	Vector3 operator[](const int index) const;

	operator DirectX::XMFLOAT3X3();
	operator DirectX::XMMATRIX();

	static Matrix3 Identity();
};

class Matrix4
{
public:
	float R1C1, R1C2, R1C3, R1C4;
	float R2C1, R2C2, R2C3, R2C4;
	float R3C1, R3C2, R3C3, R3C4;
	float R4C1, R4C2, R4C3, R4C4;

	Matrix4(float r1c1 = 0.0f, float r1c2 = 0.0f, float r1c3 = 0.0f, float r1c4 = 0.0f,
			float r2c1 = 0.0f, float r2c2 = 0.0f, float r2c3 = 0.0f, float r2c4 = 0.0f,
			float r3c1 = 0.0f, float r3c2 = 0.0f, float r3c3 = 0.0f, float r3c4 = 0.0f,
			float r4c1 = 0.0f, float r4c2 = 0.0f, float r4c3 = 0.0f, float r4c4 = 0.0f);

	Vector4 operator[](const int index) const;

	operator DirectX::XMFLOAT4X4();
	operator DirectX::XMMATRIX();

	static Matrix4 Identity();
};

class Clamps1
{
public:
	float Min, Max;

	Clamps1(float min = 0.0f, float max = 0.0f);

	Vector2 MinMaxVector2();

	static Clamps1 NoClamps();
};

class Clamps2
{
public:
	float MinX, MaxX, MinY, MaxY;

	Clamps2(float minX = 0.0f, float maxX = 0.0f, 
			float minY = 0.0f, float maxY = 0.0f);

	Vector2 Minimum();
	Vector2 Maximum();

	static Clamps2 NoClamps();
};

class Clamps3
{
public:
	float MinX, MaxX, MinY, MaxY, MinZ, MaxZ;

	Clamps3(float minX = 0.0f, float maxX = 0.0f, 
			float minY = 0.0f, float maxY = 0.0f,
			float minZ = 0.0f, float maxZ = 0.0f);

	Vector3 Minimum();
	Vector3 Maximum();

	static Clamps3 NoClamps();
};

class Clamps4
{
public:
	float MinX, MaxX, MinY, MaxY, MinZ, MaxZ, MinW, MaxW;

	Clamps4(float minX = 0.0f, float maxX = 0.0f, 
			float minY = 0.0f, float maxY = 0.0f,
			float minZ = 0.0f, float maxZ = 0.0f,
			float minW = 0.0f, float maxW = 0.0f);

	Vector4 Minimum();
	Vector4 Maximum();

	static Clamps4 NoClamps();
};

class Quaternion
{
public:
	Quaternion(float w = 1.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f);
	void Normalize();
	void Rotate(Vector3 axis, float fAngle);

	DirectX::XMMATRIX GetRotationMatrix() const;

	static Quaternion FromRollPitchYaw(float x, float y, float z);
	static Quaternion FromRollPitchYaw(Vector3 vec);

	Quaternion operator*(const float& rhs) const;
	Quaternion operator*(const Quaternion& rhs) const;

	void operator*=(const float& rhs);
	void operator*=(const Quaternion& rhs);

	operator DirectX::XMFLOAT4();
	operator DirectX::XMVECTOR();

	static Quaternion Identity();

private:
	float w, x, y, z;

};

#endif