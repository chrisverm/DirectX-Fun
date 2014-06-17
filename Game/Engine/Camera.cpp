// ---------------------------------------------------------------------------
// Camera.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 6/17/2014
// ---------------------------------------------------------------------------

#include "Camera.h"

Camera::Camera() : Entity(), ProjMatrix(projMatrix), ViewMatrix(viewMatrix)
{

}

Camera::~Camera() { }

void Camera::Update(float dt)
{
	Entity::Update(dt);

	// clamp rotation angles
}

void Camera::SetAspectRatio(float ratio)
{
	aspectRatio = ratio;
}

void Camera::SetProjMatrix()
{
	assert(aspectRatio != 0);
	assert(FieldOfView != 0);
	assert(FarPlane != NearPlane);

	float tanHalfFOV = tan(FieldOfView / 2.0f);

	projMatrix[0][0] = (1.0f / tanHalfFOV) / aspectRatio;
	projMatrix[1][1] = (1.0f / tanHalfFOV);
	projMatrix[2][2] = -(FarPlane + NearPlane) / (NearPlane - FarPlane);
	projMatrix[2][3] = (2.0f * FarPlane * NearPlane) / (NearPlane - FarPlane);
	projMatrix[3][2] = 1;
}

void Camera::SetViewMatrix()
{
	Vector3 Forward = Orientation.GetRotationMatrix4()[2];
	Forward.Normalize();

	Vector3 Right = Vector3::Cross(Vector3(0, 1, 0), Forward);
	Right.Normalize();

	Vector3 Up = Vector3::Cross(Forward, Right);
	Up.Normalize();

	viewMatrix[0][0] = Right.X;
	viewMatrix[1][0] = Right.Y;
	viewMatrix[2][0] = Right.Z;
	viewMatrix[0][1] = Up.X;
	viewMatrix[1][1] = Up.Y;
	viewMatrix[2][1] = Up.Z;
	viewMatrix[0][2] = Forward.X;
	viewMatrix[1][2] = Forward.Y;
	viewMatrix[2][2] = Forward.Z;
	viewMatrix[0][3] = -Position.X;
	viewMatrix[1][3] = -Position.Y;
	viewMatrix[2][3] = -Position.Z;
	viewMatrix[3][3] = 1.0f;
}