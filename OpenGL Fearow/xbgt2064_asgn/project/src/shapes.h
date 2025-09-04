#pragma once
#include <glad/glad.h>
#include "transform.h"
using namespace std;

const float PI = 3.14159;

static class Shapes
{
public:

	static void drawQuad(Vector2 size = Vector2(1,1), float texScale=1)
	{
		Vector2 tex;

		if (size.x > size.y)
		{
			tex = Vector2(texScale, texScale * size.y / size.x);
		}
		else if (size.x < size.y)
		{
			tex = Vector2(texScale * size.x / size.y, texScale);
		}
		else
		{
			tex = Vector2(texScale, texScale);
		}
			
		glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2f(0, tex.y);
		glVertex3f(-size.x*.5, 0, size.y*.5);

		glTexCoord2f(tex.x, tex.y);
		glVertex3f(size.x*.5, 0, size.y*.5);

		glTexCoord2f(0, 0);
		glVertex3f(-size.x*.5, 0, -size.y*.5);

		glTexCoord2f(tex.x, 0);
		glVertex3f(size.x*.5, 0, -size.y*.5);

		glEnd();
	}

	static void drawQuadTex(Vector2 size = Vector2(1,1), float texScale=1)
	{		
		glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2f(0, texScale);
		glVertex3f(-size.x*.5, 0, size.y*.5);

		glTexCoord2f(texScale, texScale);
		glVertex3f(size.x*.5, 0, size.y*.5);

		glTexCoord2f(0, 0);
		glVertex3f(-size.x*.5, 0, -size.y*.5);

		glTexCoord2f(texScale, 0);
		glVertex3f(size.x*.5, 0, -size.y*.5);

		glEnd();
	}

	static void drawCuboid(const Matrix4& viewMatrix, Vector3 size, float texScale=1, bool bottomless=false, bool topless=false)
	{
		Transform bottomTr, topTr, frontTr, backTr, leftTr, rightTr;

		bottomTr.setPosition(0, 0, 0);
		bottomTr.setRotation(180, 0, 0);
		bottomTr.setScale(1, 1, 1);

		topTr.setPosition(0, size.y, 0);
		topTr.setRotation(0, 0, 0);
		topTr.setScale(1, 1, 1);

		frontTr.setPosition(0, size.y*.5, size.z*.5);
		frontTr.setRotation(90, 0, 0);
		frontTr.setScale(1, 1, 1);

		backTr.setPosition(0, size.y*.5, -size.z*.5);
		backTr.setRotation(90, 180, 0);
		backTr.setScale(1, 1, 1);

		leftTr.setPosition(-size.x*.5, size.y*.5, 0);
		leftTr.setRotation(0, 90, 90);
		leftTr.setScale(1, 1, 1);

		rightTr.setPosition(size.x*.5, size.y*.5, 0);
		rightTr.setRotation(0, 90, -90);
		rightTr.setScale(1, 1, 1);

		glPushMatrix();
		
		glLoadMatrixf((viewMatrix * bottomTr.getMatrix()).data);
		if(!bottomless) drawQuad(Vector2(size.x, size.z), texScale);
		
		glLoadMatrixf((viewMatrix * topTr.getMatrix()).data);
		if(!topless) drawQuad(Vector2(size.x, size.z), texScale);
		
		glLoadMatrixf((viewMatrix * frontTr.getMatrix()).data);
		drawQuad(Vector2(size.x, size.y), texScale);
		
		glLoadMatrixf((viewMatrix * backTr.getMatrix()).data);
		drawQuad(Vector2(size.x, size.y), texScale);
		
		glLoadMatrixf((viewMatrix * leftTr.getMatrix()).data);
		drawQuad(Vector2(size.z, size.y), texScale);
		
		glLoadMatrixf((viewMatrix * rightTr.getMatrix()).data);
		drawQuad(Vector2(size.z, size.y), texScale);
		
		glPopMatrix();
	}

	static void drawDisk(float innerRadius=0, float outerRadius=1, int slices=16)
	{
		float anglePerSlice = 2 * PI / slices;

		glBegin(GL_TRIANGLE_STRIP);
		
		for (int i = 0; i <= slices; i++)
		{
			float theta = anglePerSlice * i;

			float cosine = cos(theta);
			float sine = sin(theta);

			float innerUVR = innerRadius / outerRadius * 0.5;

			glTexCoord2f(0.5+innerUVR*cosine, 0.5+innerUVR*sine);
			glVertex3f(cosine*innerRadius, 0, -sine*innerRadius);
							
			glTexCoord2f(0.5+0.5*cosine, 0.5+0.5*sine);
			glVertex3f(cosine*outerRadius, 0, -sine*outerRadius);
		}

		glEnd();
	}

	static void drawCylinder(float baseRadius=1, float topRadius=1, float height=2, int slices=16)
	{
		float anglePerSlice = 2 * PI / slices;

		glBegin(GL_TRIANGLE_STRIP);

		for (int i = 0; i <= slices; i++)
		{
			float theta = anglePerSlice * i;

			float cosine = cos(theta);
			float sine = sin(theta);

			float u = (float)i / slices; // convert i to float

			glTexCoord2f(u, 1);
			glVertex3f(cosine * baseRadius, 0, sine * baseRadius);

			glTexCoord2f(u, 0);
			glVertex3f(cosine * topRadius, height, sine * topRadius);
		}

		glEnd();
	}

	static void drawFullCylinder(const Matrix4& viewMatrix, float baseRadius=1, float topRadius=1, float height=2, int slices=16)
	{
		Transform bodyTr, baseTr, topTr;

		bodyTr.setPosition(0, 0, 0);
		bodyTr.setRotation(0, 0, 0);
		bodyTr.setScale(1, 1, 1);

		baseTr.setPosition(0, 0, 0);
		baseTr.setRotation(180, 0, 0);
		baseTr.setScale(1, 1, 1);

		topTr.setPosition(0, height, 0);
		topTr.setRotation(0, 0, 0);
		topTr.setScale(1, 1, 1);

		glPushMatrix();
		
		glLoadMatrixf((viewMatrix * bodyTr.getMatrix()).data);
		drawCylinder(baseRadius, topRadius, height, slices);
		
		glLoadMatrixf((viewMatrix * bodyTr.getMatrix() * baseTr.getMatrix()).data);
		drawDisk(0, baseRadius, slices);
		
		glLoadMatrixf((viewMatrix * bodyTr.getMatrix() * topTr.getMatrix()).data);
		drawDisk(0, topRadius, slices);
		
		glPopMatrix();
	}
};