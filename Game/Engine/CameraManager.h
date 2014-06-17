// ---------------------------------------------------------------------------
// CameraManager.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 6/17/2014
// ---------------------------------------------------------------------------

#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include <d3d11.h>
#include "Camera.h"

class CameraManager
{
public:
	static void Initialize(ID3D11DeviceContext* deviceContext, int* windowWidth,
		int* windowHeight, bool* projChanged);
	static int AddNewCamera(Camera* camera, bool makeActive = false);
	static void ChangeActiveCamera(int index);
	static void Update(float dt);
	static void Release();

	static const bool IsEmpty() { return numCameras <= 0; }
	static const float AspectRatio() { return (float)*windowWidth / *windowHeight; }
	static const Camera* ActiveCamera() { return cameras[activeIndex]; }

private:
	static int* windowWidth;
	static int* windowHeight;
	static bool* projChanged;
	static bool* viewChanged;

	static int numCameras;
	static int activeIndex;
	static Camera** cameras;

};

#endif