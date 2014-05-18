// ---------------------------------------------------------------------------
// DXMath.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/17/2014
// ---------------------------------------------------------------------------

#include "DXMath.h"

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