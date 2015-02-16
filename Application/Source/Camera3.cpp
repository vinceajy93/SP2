#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

/***********************************************************/
/*!
\brief
	Camera2's constructor
*/
/***********************************************************/
Camera3::Camera3()
{
}

/***********************************************************/
/*!
\brief
	Camera2's destruction
*/
/***********************************************************/
Camera3::~Camera3()
{
}

/***********************************************************/
/*
\brief
	Initialize the Camera variables values
\param pos - position of the camera

\param target - position of the target

\param up - the up direction of the camera's position
*/
/***********************************************************/
void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	defaultview = view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();

	TableBound.Set(150,0,950);
	BedBound.Set(-650,0,1000);
	SideRoomXBound = -1490;
	MidofRoom = 510;
	Maximum.Set(490,490,1490);
	Minimum.Set(-490,-490,-490);
	GengarMax.Set(500,0,0);
	GengarMin.Set(0,0,-500);

	rotateangle = 0;
}

/***********************************************************/
/*!
\brief
	Update the camera position based on key pressed
\param dt - the delta time since the last time the function was called
*/
/***********************************************************/
void Camera3::Update(double dt)
{
	static const float CAMERA_SPEED = 50.f;

	// tilt up
	if(Application::IsKeyPressed(VK_UP))
	{
		float pitch = (float)(CAMERA_SPEED * dt);
		view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		
		if(rotateangle < 0.5)
		{
			rotateangle += dt;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			view = rotation * view;
			target = (position + view);
		}
	}

	// tilt down
	if(Application::IsKeyPressed(VK_DOWN))
	{
		float pitch = (float)(-CAMERA_SPEED * dt);
		view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		if(rotateangle > -0.3)
		{
			rotateangle -= dt;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			view = rotation * view;
			target = (position + view);
		}
	}

	// tilt left
	if(Application::IsKeyPressed(VK_LEFT))
	{
		float pitch = (float)(CAMERA_SPEED * dt);
		view = (target - position).Normalized();
		rotation.SetToRotation(pitch, 0, 1, 0);
		view = rotation * view;
		target = (position + view);
		up = rotation * up;
	}

	// tilt right
	if(Application::IsKeyPressed(VK_RIGHT))
	{
		float pitch = (float)(-CAMERA_SPEED * dt);
		view = (target - position).Normalized();
		rotation.SetToRotation(pitch, 0, 1, 0);
		view = rotation * view;
		target = (position + view);
		up = rotation * up;
	}
}

void Camera3::Update3rd(double dt)
{
	static const float Move = 250.f;
	static const float Turn = 50.f;
	if(Application::IsKeyPressed('W'))
	{
		Vector3 temptarget = target;
		Vector3 tempposition = position;
		float yaw = (float)(Move * dt);
		view = (target - position).Normalized();
		position += (view * yaw);
		target += (view * yaw);
		
		if(position.z < GengarMax.z && position.z > GengarMin.z && position.x < GengarMax.x && position.x > GengarMin.x)	
		{
			target = temptarget;
			position = tempposition;
		}

		if(position.z < MidofRoom)
		{
			if(position.x > Maximum.x || position.x < Minimum.x || position.y > Maximum.y || position.y < Minimum.y || position.z < Minimum.z)
			{
				target = temptarget;
				position = tempposition;
			}
		}

		else if(position.z > MidofRoom)
		{
			if(position.z > TableBound.z)
			{
				if(position.z > BedBound.z)
				{
					if(position.x > TableBound.x || position.x < BedBound.x || position.y > Maximum.y || position.y < Minimum.y || position.z > Maximum.z)
					{
						target = temptarget;
						position = tempposition;
					}
				}

				else
				{
					if(position.x > TableBound.x || position.x < SideRoomXBound || position.y > Maximum.y || position.y < Minimum.y || position.z > Maximum.z)
					{
						target = temptarget;
						position = tempposition;
					}
				}
			}
			else
			{
				if(position.x > Maximum.x || position.x < SideRoomXBound || position.y > Maximum.y || position.y < Minimum.y || position.z > Maximum.z)
				{
					target = temptarget;
					position = tempposition;
				}
			}
		}

		target.y = temptarget.y;
		position.y = tempposition.y;
	}

	if(Application::IsKeyPressed('S'))
	{
		Vector3 temptarget = target;
		Vector3 tempposition = position;
		float yaw = (float)(-Move * dt);
		view = (target - position).Normalized();
		position += (view * yaw);
		target += (view * yaw);

		if(position.z < GengarMax.z && position.z > GengarMin.z && position.x < GengarMax.x && position.x > GengarMin.x)	
		{
			target = temptarget;
			position = tempposition;
		}

		if(position.z < MidofRoom)
		{
			if(position.x > Maximum.x || position.x < Minimum.x || position.y > Maximum.y || position.y < Minimum.y || position.z < Minimum.z)
			{
				target = temptarget;
				position = tempposition;
			}
		}

		else if(position.z > MidofRoom)
		{
			if(position.z > TableBound.z)
			{
				if(position.z > BedBound.z)
				{
					if(position.x > TableBound.x || position.x < BedBound.x || position.y > Maximum.y || position.y < Minimum.y || position.z > Maximum.z)
					{
						target = temptarget;
						position = tempposition;
					}
				}

				else
				{
					if(position.x > TableBound.x || position.x < SideRoomXBound || position.y > Maximum.y || position.y < Minimum.y || position.z > Maximum.z)
					{
						target = temptarget;
						position = tempposition;
					}
				}
			}
			else
			{
				if(position.x > Maximum.x || position.x < SideRoomXBound || position.y > Maximum.y || position.y < Minimum.y || position.z > Maximum.z)
				{
					target = temptarget;
					position = tempposition;
				}
			}
		}

		target.y = temptarget.y;
		position.y = tempposition.y;
	}

	if(Application::IsKeyPressed('A'))
	{
		Vector3 temptarget = target;
		Vector3 tempposition = position;
		float yaw = (float)(-Move * dt);
		view = (target - position).Normalized();
		position += (view.Cross(up) * yaw);
		target += (view.Cross(up) * yaw);

		if(position.z < GengarMax.z && position.z > GengarMin.z && position.x < GengarMax.x && position.x > GengarMin.x)	
		{
			target = temptarget;
			position = tempposition;
		}

		if(position.z < MidofRoom)
		{
			if(position.x > Maximum.x || position.x < Minimum.x || position.y > Maximum.y || position.y < Minimum.y || position.z < Minimum.z)
			{
				target = temptarget;
				position = tempposition;
			}
		}

		else if(position.z > MidofRoom)
		{
			if(position.z > TableBound.z)
			{
				if(position.z > BedBound.z)
				{
					if(position.x > TableBound.x || position.x < BedBound.x || position.y > Maximum.y || position.y < Minimum.y || position.z > Maximum.z)
					{
						target = temptarget;
						position = tempposition;
					}
				}

				else
				{
					if(position.x > TableBound.x || position.x < SideRoomXBound || position.y > Maximum.y || position.y < Minimum.y || position.z > Maximum.z)
					{
						target = temptarget;
						position = tempposition;
					}
				}
			}
			else
			{
				if(position.x > Maximum.x || position.x < SideRoomXBound || position.y > Maximum.y || position.y < Minimum.y || position.z > Maximum.z)
				{
					target = temptarget;
					position = tempposition;
				}
			}
		}
		
		target.y = temptarget.y;
		position.y = tempposition.y;
	}

	if(Application::IsKeyPressed('D'))
	{
		Vector3 temptarget = target;
		Vector3 tempposition = position;
		float yaw = (float)(Move * dt);
		view = (target - position).Normalized();
		position += (view.Cross(up) * yaw);
		target += (view.Cross(up) * yaw);

		if(position.z < GengarMax.z && position.z > GengarMin.z && position.x < GengarMax.x && position.x > GengarMin.x)	
		{
			target = temptarget;
			position = tempposition;
		}

		if(position.z < MidofRoom)
		{
			if(position.x > Maximum.x || position.x < Minimum.x || position.y > Maximum.y || position.y < Minimum.y || position.z < Minimum.z)
			{
				target = temptarget;
				position = tempposition;
			}
		}

		else if(position.z > MidofRoom)
		{
			if(position.z > TableBound.z)
			{
				if(position.z > BedBound.z)
				{
					if(position.x > TableBound.x || position.x < BedBound.x || position.y > Maximum.y || position.y < Minimum.y || position.z > Maximum.z)
					{
						target = temptarget;
						position = tempposition;
					}
				}

				else
				{
					if(position.x > TableBound.x || position.x < SideRoomXBound || position.y > Maximum.y || position.y < Minimum.y || position.z > Maximum.z)
					{
						target = temptarget;
						position = tempposition;
					}
				}
			}
			else
			{
				if(position.x > Maximum.x || position.x < SideRoomXBound || position.y > Maximum.y || position.y < Minimum.y || position.z > Maximum.z)
				{
					target = temptarget;
					position = tempposition;
				}
			}
		}

		target.y = temptarget.y;
		position.y = tempposition.y;
	}

	// tilt up
	if(Application::IsKeyPressed(VK_UP))
	{
		float pitch = (float)(Turn * dt);
		view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		
		if(rotateangle < 0.5)
		{
			rotateangle += dt;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			view = rotation * view;
			target = (position + view);
		}
	}

	// tilt down
	if(Application::IsKeyPressed(VK_DOWN))
	{
		float pitch = (float)(-Turn * dt);
		view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		if(rotateangle > -0.3)
		{
			rotateangle -= dt;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			view = rotation * view;
			target = (position + view);
		}
	}

	// tilt left
	if(Application::IsKeyPressed(VK_LEFT))
	{
		float pitch = (float)(Turn * dt);
		view = (target - position).Normalized();
		rotation.SetToRotation(pitch, 0, 1, 0);
		view = rotation * view;
		target = (position + view);
		up = rotation * up;
	}

	// tilt right
	if(Application::IsKeyPressed(VK_RIGHT))
	{
		float pitch = (float)(-Turn * dt);
		view = (target - position).Normalized();
		rotation.SetToRotation(pitch, 0, 1, 0);
		view = rotation * view;
		target = (position + view);
		up = rotation * up;
	}
}

/***********************************************************/
/*!
\brief
	Reset's the camera's variables to default
*/
/***********************************************************/
void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
	view = defaultview;
}