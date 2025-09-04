#pragma once
#include "angle_util/vector.h"
#include "angle_util/matrix.h"

class Transform
{
private:
	Vector3 position;	// default ctor makes zero vector.
	Vector3 rotation;	// default ctor makes zero vector.
	Vector3 scale;		// default ctor makes zero vector.

	mutable Matrix4 matrix;		// default ctor makes identity matrix.
	mutable Matrix4 rotMatrix;

	mutable bool isDirty = false;

	void revalidate() const
	{
		if (isDirty)
		{
			//recalculate matrices

			rotMatrix = Matrix4::rotate(rotation.z, Vector3(0, 0, 1)) *
						Matrix4::rotate(rotation.y, Vector3(0, 1, 0)) *
						Matrix4::rotate(rotation.x, Vector3(1, 0, 0));

			matrix = Matrix4::translate(position) *
					rotMatrix *
					Matrix4::scale(scale);

			isDirty = false;
		}
	}

public:

	Transform() :position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), isDirty(true) {}

	// Custom ctor, DIY
	//Transform(Vector3 t, Vector3 r, Vector3 s) {}

	inline const Vector3 getPosition()
	{
		return position;
	}

	inline const Vector3 getRotation()
	{
		return rotation;
	}

	inline const Vector3 getScale()
	{
		return scale;
	}

	void translateXBy(float tx)
	{
		position.x += tx;
		
		isDirty = true;
	}

	void translateYBy(float ty)
	{
		position.y += ty;
		
		isDirty = true;
	}

	void translateZBy(float tz)
	{
		position.z += tz;
		
		isDirty = true;
	}

	void translateBy(float tx, float ty, float tz)
	{
		position.x += tx;
		position.y += ty;
		position.z += tz;

		isDirty = true;
	}

	void translateBy(Vector3 translation)
	{
		position += translation;

		isDirty = true;
	}

	void setPosition(float tx, float ty, float tz)
	{
		position.x = tx;
		position.y = ty;
		position.z = tz;

		isDirty = true;
	}

	void setPosition(Vector3 newPosition)
	{
		position = newPosition;

		isDirty = true;
	}

	void rotateXBy(float xDegree)
	{
		rotation.x += xDegree;
		
		isDirty = true;
	}

	void rotateYBy(float yDegree)
	{
		rotation.y += yDegree;
		
		isDirty = true;
	}

	void rotateZBy(float zDegree)
	{
		rotation.z += zDegree;
		
		isDirty = true;
	}

	void rotateBy(float xDegree, float yDegree, float zDegree)
	{
		rotation.x += xDegree;
		rotation.y += yDegree;
		rotation.z += zDegree;

		isDirty = true;
	}

	void rotateBy(Vector3 degrees)
	{
		rotation += degrees;

		isDirty = true;
	}

	void setRotation(float xDegree, float yDegree, float zDegree)
	{
		rotation.x = xDegree;
		rotation.y = yDegree;
		rotation.z = zDegree;

		isDirty = true;
	}

	void setRotation(Vector3 newRotation)
	{
		rotation = newRotation;

		isDirty = true;
	}

	void scaleBy(float sx, float sy, float sz)
	{
		scale.x += sx;
		scale.y += sy;
		scale.z += sz;
		
		isDirty = true;
	}

	void scaleBy(Vector3 scales)
	{
		scale += scales;
		
		isDirty = true;
	}

	void setScale(float sx, float sy, float sz)
	{
		scale.x = sx;
		scale.y = sy;
		scale.z = sz;
		
		isDirty = true;
	}

	void setScale(Vector3 newScale)
	{
		scale = newScale;
		
		isDirty = true;
	}

	Vector3 forward()
	{
		revalidate();

		//multiply rotMatrix with Z Axis
		return rotMatrix * Vector3(0, 0, 1);
	}

	Vector3 up()
	{
		revalidate();

		//multiply rotMatrix with Y Axis
		return rotMatrix * Vector3(0, 1, 0);
	}

	Vector3 right()
	{
		revalidate();

		//multiply rotMatrix with X Axis
		return rotMatrix * Vector3(1, 0, 0);
	}

	inline const Matrix4& getMatrix() const
	{
		revalidate();

		return matrix;
	}
};