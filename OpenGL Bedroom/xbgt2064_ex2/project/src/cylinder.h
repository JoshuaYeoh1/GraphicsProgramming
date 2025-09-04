#pragma once
#include <glad/glad.h>
#include <corecrt_math.h>

class Cylinder
{
public:
	static void draw(float baseRadius, float topRadius, float height, int slices)
	{
		float anglePerSlice = 2 * PI / slices;

		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i <= slices; i++)
		{
			float theta = anglePerSlice * i;

			float cosine = cos(theta);
			float sine = sin(theta);

			float u = (float)i / slices; // convert i to float

			glTexCoord2f(u, 1);	// Set Texture Coordinate
			glVertex3f(cosine * topRadius, sine * topRadius, height);

			glTexCoord2f(u, 0);	// Set Texture Coordinate
			glVertex3f(cosine * baseRadius, sine * baseRadius, 0);
		}
		glEnd();
	}
};
