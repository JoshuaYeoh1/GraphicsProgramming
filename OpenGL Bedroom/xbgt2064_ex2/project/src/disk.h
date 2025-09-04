#pragma once
#include <glad/glad.h>
#include <corecrt_math.h>

const float PI = 3.14159;

class Disk
{
public:
	static void draw(float innerRadius=.5, float outerRadius=1, int slices=32)
	{
		float anglePerSlice = 2 * PI / slices;

		glBegin(GL_TRIANGLE_STRIP);
		
		for (int i = 0; i <= slices; i++)
		{
			float theta = anglePerSlice * i;

			float cosine = cos(theta);
			float sine = sin(theta);

			float innerUVR = innerRadius / outerRadius * 0.5;

			glTexCoord2f(0.5+innerUVR*cosine, 0.5+innerUVR*sine);	// Set Texture Coordinate
			glVertex3f(cosine*innerRadius, sine*innerRadius, 0);
							
			glTexCoord2f(0.5+0.5*cosine, 0.5+0.5*sine);	// Set Texture Coordinate
			glVertex3f(cosine*outerRadius, sine*outerRadius, 0);
		}

		glEnd();
	}
};