// ---------------------------------------------------------------------------
// Camera.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 6/11/2014
// ---------------------------------------------------------------------------

#ifndef CAMERA_H
#define CAMERA_H

#include "DXMath.h"
#include "Entity.h"

struct CAMERA_DESC
{
	float FieldOfView;
	float NearPlane;
	float FarPlane;
};

class Camera : public Entity
{
public:
	float FieldOfView;
	float NearPlane;
	float FarPlane;

	const Matrix4& ProjMatrix;
	const Matrix4& ViewMatrix;

	Camera();
	~Camera();
	void Update(float dt);
	void SetAspectRatio(float ratio);
	void SetProjMatrix();
	void SetViewMatrix();

protected:
	float aspectRatio;
	Matrix4 projMatrix;
	Matrix4 viewMatrix;

};

#endif