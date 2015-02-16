/***********************************************************/
/*!
\file	Camera2.h
\author	Malcolm Lim
\par
\brief	Create a camera using Camera.h as it's parents
*/
/***********************************************************/
#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"
#include "Mtx44.h"

/***********************************************************/
/*!
	class Camera2
\brief	Defines a camera and it's method with class Camera's method inside
*/
/***********************************************************/

class Camera3 : public Camera
{
public:
	//Vector3 position;
	//Vector3 target;
	//Vector3 up;

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 defaultview;
	Vector3 Maximum;
	Vector3 Minimum;
	Vector3 TableBound;
	Vector3 BedBound;
	Vector3 GengarMax;
	Vector3 GengarMin;

	int SideRoomXBound;
	int MidofRoom;
	Mtx44 rotation;

	float rotateangle;

	Camera3();
	~Camera3();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	void Update3rd(double dt);
	virtual void Reset();
};

#endif