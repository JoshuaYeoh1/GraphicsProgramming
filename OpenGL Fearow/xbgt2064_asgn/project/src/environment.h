#pragma once
#include "transform.h"
#include "shapes.h"
using namespace std;

static class Environment
{
public:

	static void ground(const Matrix4& viewMatrix, Texture2D* texGround, Vector3 pos)
	{
		float texScale = 4;
		Vector2 size = Vector2(25, 25);

		Transform groundTr;

		groundTr.setPosition(pos);
		groundTr.setRotation(0, 0, 0);
		groundTr.setScale(1, 1, 1);

		glPushMatrix();

		glBindTexture(GL_TEXTURE_2D, texGround->getNativeHandle());
		
		glLoadMatrixf((viewMatrix * groundTr.getMatrix()).data);
		Shapes::drawQuad(size, texScale);

		glBindTexture(GL_TEXTURE_2D, 0);

		glPopMatrix();
	}

	static void grassBlade(const Matrix4& viewMatrix, Texture2D* texGrass, float t)
	{
		Vector2 size = Vector2(voxel*8, voxel*8);

		Transform rootTr, bladeTr;

		rootTr.setPosition(0, 0, 0);
		rootTr.setRotation(5 * sin(t*1.9), 5 * cos(t*1.12), 5 * sin(t*1.4632));
		rootTr.setScale(1, 1, 1);

		bladeTr.setPosition(0, size.y/2, 0);
		bladeTr.setRotation(-90, 0, 0);
		bladeTr.setScale(1, 1, 1);

		glPushMatrix();

		glBindTexture(GL_TEXTURE_2D, texGrass->getNativeHandle());
		
		glLoadMatrixf((viewMatrix * rootTr.getMatrix()).data);

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * bladeTr.getMatrix()).data);
		Shapes::drawQuadTex(size);

		glBindTexture(GL_TEXTURE_2D, 0);

		glPopMatrix();
	}

	static void grass(const Matrix4& viewMatrix, Texture2D* texGrass, Vector3 pos, Vector3 size, float t)
	{
		Transform grass1Tr, grass2Tr;

		grass1Tr.setPosition(pos);
		grass1Tr.setRotation(0, 45, 0);
		grass1Tr.setScale(size);

		grass2Tr.setPosition(pos);
		grass2Tr.setRotation(0, -45, 0);
		grass2Tr.setScale(size);

		glPushMatrix();

		glBindTexture(GL_TEXTURE_2D, texGrass->getNativeHandle());
		
		glLoadMatrixf((viewMatrix * grass1Tr.getMatrix()).data);
		grassBlade(viewMatrix * grass1Tr.getMatrix(), texGrass, t);

		glLoadMatrixf((viewMatrix * grass2Tr.getMatrix()).data);
		grassBlade(viewMatrix * grass2Tr.getMatrix(), texGrass, t);

		glBindTexture(GL_TEXTURE_2D, 0);

		glPopMatrix();
	}
	
	static void clouds(const Matrix4& viewMatrix, Texture2D* texClouds)
	{
		Transform cloudsTr;

		cloudsTr.setPosition(0, 0, 0);
		cloudsTr.setRotation(0, 0, 0);
		cloudsTr.setScale(1,1,1);

		glPushMatrix();

		glBindTexture(GL_TEXTURE_2D, texClouds->getNativeHandle());
		
		glFrontFace(GL_CW);

		glLoadMatrixf((viewMatrix * cloudsTr.getMatrix()).data);
		Shapes::drawCylinder(25, 25, 30, 16);

		glFrontFace(GL_CCW);

		glBindTexture(GL_TEXTURE_2D, 0);

		glPopMatrix();
	}
	
};