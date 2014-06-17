// ---------------------------------------------------------------------------
// CameraManager.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 6/17/2014
// ---------------------------------------------------------------------------

#include "CameraManager.h"

int*  CameraManager::windowWidth = nullptr;
int*  CameraManager::windowHeight = nullptr;
bool* CameraManager::projChanged = nullptr;
bool* CameraManager::viewChanged = nullptr;

int CameraManager::numCameras = 0;
int CameraManager::activeIndex = -1;
Camera** CameraManager::cameras = nullptr;

void CameraManager::Initialize(ID3D11DeviceContext* deviceContext, int* windowWidth,
	int* windowHeight, bool* projChanged)
{
	CameraManager::windowWidth = windowWidth;
	CameraManager::windowHeight = windowHeight;
	CameraManager::projChanged = projChanged;
}

int CameraManager::AddNewCamera(Camera* camera, bool makeActive)
{
	numCameras++;

	Camera** newCameraList = new Camera*[numCameras];
	memcpy(newCameraList, cameras, sizeof(Camera)* (numCameras - 1));
	newCameraList[numCameras - 1] = camera;

	delete[] cameras;
	cameras = newCameraList;

	if (makeActive) ChangeActiveCamera(numCameras - 1);

	return numCameras - 1;
}

void CameraManager::ChangeActiveCamera(int index)
{
	if (IsEmpty()) return;

	activeIndex = index;

	// set viewChanged and projChanged to true instead ?
	cameras[activeIndex]->SetProjMatrix();
	cameras[activeIndex]->SetViewMatrix();
}

void CameraManager::Update(float dt)
{
	cameras[activeIndex]->Update(dt);

	if (!IsEmpty())
	{
		/*if (*viewChanged)
		{
			cameras[activeIndex]->SetViewMatrix();
			*viewChanged = false;
		}*/

		if (*projChanged)
		{
			cameras[activeIndex]->SetAspectRatio(AspectRatio());
			cameras[activeIndex]->SetProjMatrix();
			*projChanged = false;
		}
	}
}

void CameraManager::Release()
{
	if (cameras != nullptr)
	{
		for (int i = 0; i < numCameras; i++)
		{
			delete cameras[i];
			cameras[i] = nullptr;
		}

		delete[] cameras;
		cameras = nullptr;
	}

	numCameras = 0;
	activeIndex = -1;
}