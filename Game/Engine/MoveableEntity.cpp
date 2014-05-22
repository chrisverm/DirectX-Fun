// ---------------------------------------------------------------------------
// MoveableEntity.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/19/2014
// ---------------------------------------------------------------------------

#include "MoveableEntity.h"

MoveableEntity::MoveableEntity(Mesh* mesh, Material* material)
	: DrawableEntity(mesh, material)
{
	linearVel			= Vector3::Zero();
	linearAccel			= Vector3::Zero();
	linearVelClamps		= Clamps1::NoClamps();
	linearAccelClamps	= Clamps1::NoClamps();
	angularVel			= Vector3::Zero();
	angularAccel		= Vector3::Zero();
	angularVelClamps	= Clamps1::NoClamps();
	angularAccelClamps	= Clamps1::NoClamps();
}

MoveableEntity::~MoveableEntity()
{

}

void MoveableEntity::Update(float dt)
{
	linearAccel.ClampLength(linearAccelClamps);
	angularAccel.ClampLength(angularAccelClamps);

	linearVel += linearAccel;
	angularVel += angularAccel;

	linearVel.ClampLength(linearVelClamps);
	angularVel.ClampLength(angularVelClamps);

	// friction ?

	position += linearVel * dt;
	orientation *= Quaternion::FromRollPitchYaw(angularVel * dt);

	linearAccel = Vector3::Zero();
	angularAccel = Vector3::Zero();

	Entity::Update(dt);
}