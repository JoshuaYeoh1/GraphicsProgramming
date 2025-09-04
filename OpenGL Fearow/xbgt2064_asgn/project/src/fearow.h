#pragma once
#include "transform.h"
#include "shapes.h"
using namespace std;

const float voxel = .1;

static class Fearow
{
public:

	static void foot(const Matrix4& viewMatrix, Texture2D* texPink, Texture2D* texWhite, float t)
	{
		float texScale = .3;
		float toeWidth = voxel*.75;
		Vector3 soleSize = Vector3(voxel*3, voxel, voxel*2);
		Vector3 toeSSize = Vector3(toeWidth, .15, voxel);
		Vector3 toeMSize = Vector3(toeWidth, voxel*2, voxel);
		Vector3 toeLSize = Vector3(toeWidth, .275, voxel);

		Transform soleTr;
		Transform toeLTr, toeMTr, toeRTr, toeBTr;
		Transform clawLTr, clawMTr, clawRTr, clawBTr;

		soleTr.setPosition(0, -soleSize.y, voxel/2);
		soleTr.setRotation(0, 0, 0);
		soleTr.setScale(1, 1, 1);

		toeLTr.setPosition(soleSize.x/2-toeWidth/2, soleSize.y/2, soleSize.z/2);
		toeLTr.setRotation(130 + 25 * sin(t*2.315), 0, 0);
		toeLTr.setScale(1, 1, 1);

		toeMTr.setPosition(0, soleSize.y/2, soleSize.z/2);
		toeMTr.setRotation(120 + 25 * sin(t*2.1), 0, 0);
		toeMTr.setScale(1, 1, 1);

		toeRTr.setPosition(-soleSize.x/2+toeWidth/2, soleSize.y/2, soleSize.z/2);
		toeRTr.setRotation(130 + 25 * sin(t*2.68), 0, 0);
		toeRTr.setScale(1, 1, 1);

		toeBTr.setPosition(0, soleSize.y/2, -soleSize.z/2);
		toeBTr.setRotation(-120 + 25 * sin(t*2.346), 0, 0);
		toeBTr.setScale(1, 1, 1);

		clawLTr.setPosition(0, toeMSize.y-voxel/2+.015, soleSize.y/2);
		clawLTr.setRotation(90, 0, 0);
		clawLTr.setScale(1, 1, 1);

		clawMTr.setPosition(0, toeLSize.y-voxel/2+.015, soleSize.y/2);
		clawMTr.setRotation(90, 0, 0);
		clawMTr.setScale(1, 1, 1);

		clawRTr.setPosition(0, toeMSize.y-voxel/2+.015, soleSize.y/2);
		clawRTr.setRotation(90, 0, 0);
		clawRTr.setScale(1, 1, 1);

		clawBTr.setPosition(0, toeSSize.y-voxel/2+.015, -soleSize.y/2);
		clawBTr.setRotation(-90, 0, 0);
		clawBTr.setScale(1, 1, 1);

		glPushMatrix();

		glBindTexture(GL_TEXTURE_2D, texPink->getNativeHandle());
		
		glLoadMatrixf((viewMatrix * soleTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * soleTr.getMatrix(), soleSize, texScale);
		
		glLoadMatrixf((viewMatrix * soleTr.getMatrix() * toeLTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * soleTr.getMatrix() * toeLTr.getMatrix(), toeMSize, texScale);
		
		glLoadMatrixf((viewMatrix * soleTr.getMatrix() * toeMTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * soleTr.getMatrix() * toeMTr.getMatrix(), toeLSize, texScale);
		
		glLoadMatrixf((viewMatrix * soleTr.getMatrix() * toeRTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * soleTr.getMatrix() * toeRTr.getMatrix(), toeMSize, texScale);
		
		glLoadMatrixf((viewMatrix * soleTr.getMatrix() * toeBTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * soleTr.getMatrix() * toeBTr.getMatrix(), toeSSize, texScale);
		
		glBindTexture(GL_TEXTURE_2D, texWhite->getNativeHandle());

		glLoadMatrixf((viewMatrix * soleTr.getMatrix() * toeLTr.getMatrix() * clawLTr.getMatrix()).data);
		Shapes::drawCylinder(toeWidth/2, 0, voxel, 6);
		
		glLoadMatrixf((viewMatrix * soleTr.getMatrix() * toeMTr.getMatrix() * clawMTr.getMatrix()).data);
		Shapes::drawCylinder(toeWidth/2, 0, voxel, 6);
		
		glLoadMatrixf((viewMatrix * soleTr.getMatrix() * toeRTr.getMatrix() * clawRTr.getMatrix()).data);
		Shapes::drawCylinder(toeWidth/2, 0, voxel, 6);
		
		glLoadMatrixf((viewMatrix * soleTr.getMatrix() * toeBTr.getMatrix() * clawBTr.getMatrix()).data);
		Shapes::drawCylinder(toeWidth/2, 0, voxel, 6);

		glBindTexture(GL_TEXTURE_2D, 0);

		glPopMatrix();
	}

	static void shin(const Matrix4& viewMatrix, Texture2D* texPink)
	{
		float texScale = .3;
		Vector3 shinSize = Vector3(voxel, voxel*4, voxel);

		Transform shinTr;

		shinTr.setPosition(0, -shinSize.y, 0);
		shinTr.setRotation(0, 0, 0);
		shinTr.setScale(1, 1, 1);

		glPushMatrix();

		glBindTexture(GL_TEXTURE_2D, texPink->getNativeHandle());
		
		glLoadMatrixf((viewMatrix * shinTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * shinTr.getMatrix(), shinSize, texScale, true, true);

		glBindTexture(GL_TEXTURE_2D, 0);

		glPopMatrix();
	}
	
	static void thigh(const Matrix4& viewMatrix, Texture2D* texFeathersBrown)
	{
		float texScale = .5;
		Vector3 thighSize = Vector3(voxel*3, voxel*5.5, voxel*4);

		Transform thighTr;

		thighTr.setPosition(0, voxel, 0);
		thighTr.setRotation(180, 0, 0);
		thighTr.setScale(1, 1, 1);

		glPushMatrix();

		glBindTexture(GL_TEXTURE_2D, texFeathersBrown->getNativeHandle());
		
		glLoadMatrixf((viewMatrix * thighTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * thighTr.getMatrix(), thighSize, texScale, true);

		glBindTexture(GL_TEXTURE_2D, 0);

		glPopMatrix();
	}

	static void body(const Matrix4& viewMatrix, Texture2D* texFeathersBrown, Texture2D* texFeathersBeige)
	{
		float texScale = 1.5;
		Vector3 bodySize = Vector3(voxel*8, voxel*8, voxel*11);
		Vector3 bodyTopSize = Vector3(voxel*8+0.01, voxel, voxel*11+.01);
		Vector3 featherSSize = Vector3(voxel*2, voxel*2, voxel);
		Vector3 featherLSize = Vector3(voxel*1.75, voxel*3, voxel);
		Vector3 featherTSize = Vector3(voxel*3, voxel*2, voxel);
		Vector3 frontSize = Vector3(voxel*5, voxel*1.5, voxel*4.5);

		Transform bodyTr, bodyTopTr;
		Transform backFeatherRTr, backFeatherMTr, backFeatherLTr;
		Transform frontTr, frontRTr, frontLTr;
		Transform frontFeatherRTr, frontFeatherMTr, frontFeatherLTr;

		bodyTr.setPosition(0, -bodySize.y/2, 0);
		bodyTr.setRotation(0, 0, 0);
		bodyTr.setScale(1, 1, 1);

		bodyTopTr.setPosition(0, bodySize.y-voxel+.01, 0);
		bodyTopTr.setRotation(0, 0, 0);
		bodyTopTr.setScale(1, 1, 1);

		backFeatherRTr.setPosition(-voxel*2.5, voxel/2+.01, -bodyTopSize.z/2+voxel/2);
		backFeatherRTr.setRotation(-100, 0, 0);
		backFeatherRTr.setScale(1, 1, 1);

		backFeatherMTr.setPosition(0, voxel/2+.01, -bodyTopSize.z/2+voxel/2);
		backFeatherMTr.setRotation(-100, 0, 0);
		backFeatherMTr.setScale(1, 1, 1);

		backFeatherLTr.setPosition(voxel*2.5, voxel/2+.01, -bodyTopSize.z/2+voxel/2);
		backFeatherLTr.setRotation(-100, 0, 0);
		backFeatherLTr.setScale(1, 1, 1);

		frontTr.setPosition(0, bodySize.y-frontSize.z/2, bodySize.z/2-voxel/2);
		frontTr.setRotation(90, 0, 0);
		frontTr.setScale(1, 1, 1);

		frontRTr.setPosition(-frontSize.x/2+voxel, voxel/1.25, 0);
		frontRTr.setRotation(0, 90, 90);
		frontRTr.setScale(1, 1, 1);

		frontLTr.setPosition(frontSize.x/2-voxel, voxel/1.25, 0);
		frontLTr.setRotation(0, -90, -90);
		frontLTr.setScale(1, 1, 1);

		frontFeatherMTr.setPosition(0, voxel/1.25, frontSize.z/2-voxel*.1);
		frontFeatherMTr.setRotation(90, 0, 0);
		frontFeatherMTr.setScale(.6, .6, .6);

		frontFeatherRTr.setPosition(-voxel*1.5, voxel/1.25, frontSize.z/2-voxel*.1);
		frontFeatherRTr.setRotation(90, 0, 0);
		frontFeatherRTr.setScale(.6, .6, .6);

		frontFeatherLTr.setPosition(voxel*1.5, voxel/1.25, frontSize.z/2-voxel*.1);
		frontFeatherLTr.setRotation(90, 0, 0);
		frontFeatherLTr.setScale(.6, .6, .6);

		glPushMatrix();

		glBindTexture(GL_TEXTURE_2D, texFeathersBrown->getNativeHandle());
		
		glLoadMatrixf((viewMatrix * bodyTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * bodyTr.getMatrix(), bodySize, texScale, false, true);

		glBindTexture(GL_TEXTURE_2D, texFeathersBeige->getNativeHandle());

		glLoadMatrixf((viewMatrix * bodyTr.getMatrix() * frontTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * bodyTr.getMatrix() * frontTr.getMatrix(), frontSize, texScale/2, true);

		glLoadMatrixf((viewMatrix * bodyTr.getMatrix() * frontTr.getMatrix() * frontRTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * bodyTr.getMatrix() * frontTr.getMatrix() * frontRTr.getMatrix(), featherTSize, texScale/3, true);

		glLoadMatrixf((viewMatrix * bodyTr.getMatrix() * frontTr.getMatrix() * frontLTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * bodyTr.getMatrix() * frontTr.getMatrix() * frontLTr.getMatrix(), featherTSize, texScale/3, true);

		glLoadMatrixf((viewMatrix * bodyTr.getMatrix() * frontTr.getMatrix() * frontFeatherMTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * bodyTr.getMatrix() * frontTr.getMatrix() * frontFeatherMTr.getMatrix(), featherLSize, texScale/5, true);

		glLoadMatrixf((viewMatrix * bodyTr.getMatrix() * frontTr.getMatrix() * frontFeatherRTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * bodyTr.getMatrix() * frontTr.getMatrix() * frontFeatherRTr.getMatrix(), featherSSize, texScale/5, true);

		glLoadMatrixf((viewMatrix * bodyTr.getMatrix() * frontTr.getMatrix() * frontFeatherLTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * bodyTr.getMatrix() * frontTr.getMatrix() * frontFeatherLTr.getMatrix(), featherSSize, texScale/5, true);

		glLoadMatrixf((viewMatrix * bodyTr.getMatrix() * bodyTopTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * bodyTr.getMatrix() * bodyTopTr.getMatrix(), bodyTopSize, texScale, true);

		glLoadMatrixf((viewMatrix * bodyTr.getMatrix() * bodyTopTr.getMatrix() * backFeatherMTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * bodyTr.getMatrix() * bodyTopTr.getMatrix() * backFeatherMTr.getMatrix(), featherLSize, texScale/3);

		glLoadMatrixf((viewMatrix * bodyTr.getMatrix() * bodyTopTr.getMatrix() * backFeatherRTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * bodyTr.getMatrix() * bodyTopTr.getMatrix() * backFeatherRTr.getMatrix(), featherSSize, texScale/3);

		glLoadMatrixf((viewMatrix * bodyTr.getMatrix() * bodyTopTr.getMatrix() * backFeatherLTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * bodyTr.getMatrix() * bodyTopTr.getMatrix() * backFeatherLTr.getMatrix(), featherSSize, texScale/3);

		glBindTexture(GL_TEXTURE_2D, 0);

		glPopMatrix();
	}

	static void tail(const Matrix4& viewMatrix, Texture2D* texFeathersBrown, float length=voxel*8)
	{
		float texScale = 2;
		Vector3 tailSize = Vector3(voxel*1.5, length+voxel*4, voxel);

		Transform tailTr;

		tailTr.setPosition(0, 0, 0);
		tailTr.setRotation(0, 0, 0);
		tailTr.setScale(1, 1, 1);

		glPushMatrix();

		glBindTexture(GL_TEXTURE_2D, texFeathersBrown->getNativeHandle());
		
		glLoadMatrixf((viewMatrix * tailTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * tailTr.getMatrix(), tailSize, texScale, true);

		glBindTexture(GL_TEXTURE_2D, 0);

		glPopMatrix();
	}
	
	static void wingFeather(const Matrix4& viewMatrix, Texture2D* texFeathersBrown, Texture2D* texFeathersBeige, float length=voxel*3)
	{
		float texScale = .5;
		Vector3 tipSize = Vector3(voxel*3, voxel*2, voxel*1.5);
		Vector3 mainSize = Vector3(voxel*3, length-tipSize.y, voxel*1.5);

		Transform mainTr, tipTr;

		mainTr.setPosition(0, 0, 0);
		mainTr.setRotation(0, 0, 0);
		mainTr.setScale(1, 1, 1);

		tipTr.setPosition(0, mainSize.y, 0);
		tipTr.setRotation(0, 0, 0);
		tipTr.setScale(1, 1, 1);

		glPushMatrix();

		glBindTexture(GL_TEXTURE_2D, texFeathersBrown->getNativeHandle());
		
		glLoadMatrixf((viewMatrix * mainTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * mainTr.getMatrix(), mainSize, texScale, false, true);

		glBindTexture(GL_TEXTURE_2D, texFeathersBeige->getNativeHandle());

		glLoadMatrixf((viewMatrix * mainTr.getMatrix() * tipTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * mainTr.getMatrix() * tipTr.getMatrix(), tipSize, texScale, true);

		glBindTexture(GL_TEXTURE_2D, 0);

		glPopMatrix();
	}

	static void wingR1(const Matrix4& viewMatrix, Texture2D* texFeathersBrown, Texture2D* texFeathersBeige, float t)
	{
		float texScale = 1.5;
		Vector3 wingSize = Vector3(voxel*1.5, voxel*9, voxel*8);
		Vector3 topSize = Vector3(voxel*.5, voxel*9, voxel*5);
		Vector3 topFeather1Size = Vector3(topSize.x*2/3, voxel*2, voxel*3);
		Vector3 topFeather2Size = Vector3(topSize.x*2/3, voxel*2, voxel*3.5);

		Transform wingTr, feather1Tr, feather2Tr;
		Transform topTr, topFeather1Tr, topFeather2Tr, topFeather3Tr;
		Transform bottomTr, bottomFeather1Tr, bottomFeather2Tr;

		wingTr.setPosition(voxel, 0, 0);
		wingTr.setRotation(0, 0, 90);
		wingTr.setScale(1, 1, 1);

		feather1Tr.setPosition(0, voxel*3.5, -wingSize.z/2);
		feather1Tr.setRotation(-80 + 10 * sin(t*2.3523), 0, 90);
		feather1Tr.setScale(1, 1, 1);

		feather2Tr.setPosition(0, wingSize.y-voxel*2, -wingSize.z/2);
		feather2Tr.setRotation(-80 + 10 * sin(t*2.124), 0, 90);
		feather2Tr.setScale(1, 1, 1);

		topTr.setPosition(wingSize.x/2+topSize.x/2, 0, wingSize.z/2-topSize.z/2);
		topTr.setRotation(0, 0, 0);
		topTr.setScale(1, 1, 1);

		topFeather1Tr.setPosition(-topSize.x/2+topFeather1Size.x/2, topFeather1Size.z/2+voxel*1.5, -topSize.z/2);
		topFeather1Tr.setRotation(-90, 0, 0);
		topFeather1Tr.setScale(1, 1, 1);

		topFeather2Tr.setPosition(-topSize.x/2+topFeather2Size.x/2, topSize.y-topFeather2Size.z/2-voxel/2, -topSize.z/2);
		topFeather2Tr.setRotation(-90, 0, 0);
		topFeather2Tr.setScale(1, 1, 1);

		topFeather3Tr.setPosition(-topSize.x/2+topFeather2Size.x/2, topSize.y, 0);
		topFeather3Tr.setRotation(0, 0, 0);
		topFeather3Tr.setScale(1, 1, 1);

		bottomTr.setPosition(-wingSize.x/2-topSize.x/2, 0, wingSize.z/2-topSize.z/2);
		bottomTr.setRotation(0, 0, 0);
		bottomTr.setScale(1, 1, 1);
		
		bottomFeather1Tr.setPosition(topSize.x/2-topFeather1Size.x/2, topFeather1Size.z/2+voxel*1.5, -topSize.z/2);
		bottomFeather1Tr.setRotation(-90, 0, 0);
		bottomFeather1Tr.setScale(1, 1, 1);
		
		bottomFeather2Tr.setPosition(topSize.x/2-topFeather2Size.x/2, topSize.y-topFeather2Size.z/2-voxel/2, -topSize.z/2);
		bottomFeather2Tr.setRotation(-90, 0, 0);
		bottomFeather2Tr.setScale(1, 1, 1);

		glPushMatrix();

		glBindTexture(GL_TEXTURE_2D, texFeathersBrown->getNativeHandle());
		
		glLoadMatrixf((viewMatrix * wingTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * wingTr.getMatrix(), wingSize, texScale);

		glLoadMatrixf((viewMatrix * wingTr.getMatrix() * bottomTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * wingTr.getMatrix() * bottomTr.getMatrix(), topSize, texScale);

		glLoadMatrixf((viewMatrix * wingTr.getMatrix() * bottomTr.getMatrix() * bottomFeather1Tr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * wingTr.getMatrix() * bottomTr.getMatrix() * bottomFeather1Tr.getMatrix(), topFeather1Size, texScale/3, true);

		glLoadMatrixf((viewMatrix * wingTr.getMatrix() * bottomTr.getMatrix() * bottomFeather2Tr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * wingTr.getMatrix() * bottomTr.getMatrix() * bottomFeather2Tr.getMatrix(), topFeather2Size, texScale/3, true);

		glLoadMatrixf((viewMatrix * wingTr.getMatrix() * feather1Tr.getMatrix()).data);
		wingFeather(viewMatrix * wingTr.getMatrix() * feather1Tr.getMatrix(), texFeathersBrown, texFeathersBeige);

		glLoadMatrixf((viewMatrix * wingTr.getMatrix() * feather2Tr.getMatrix()).data);
		wingFeather(viewMatrix * wingTr.getMatrix() * feather2Tr.getMatrix(), texFeathersBrown, texFeathersBeige, voxel*4);

		glBindTexture(GL_TEXTURE_2D, texFeathersBeige->getNativeHandle());

		glLoadMatrixf((viewMatrix * wingTr.getMatrix() * topTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * wingTr.getMatrix() * topTr.getMatrix(), topSize, texScale);

		glLoadMatrixf((viewMatrix * wingTr.getMatrix() * topTr.getMatrix() * topFeather1Tr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * wingTr.getMatrix() * topTr.getMatrix() * topFeather1Tr.getMatrix(), topFeather1Size, texScale/3, true);

		glLoadMatrixf((viewMatrix * wingTr.getMatrix() * topTr.getMatrix() * topFeather2Tr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * wingTr.getMatrix() * topTr.getMatrix() * topFeather2Tr.getMatrix(), topFeather2Size, texScale/3, true);

		glLoadMatrixf((viewMatrix * wingTr.getMatrix() * topTr.getMatrix() * topFeather3Tr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * wingTr.getMatrix() * topTr.getMatrix() * topFeather3Tr.getMatrix(), topFeather2Size, texScale/3, true);

		glBindTexture(GL_TEXTURE_2D, 0);

		glPopMatrix();
	}

	static void wingR2(const Matrix4& viewMatrix, Texture2D* texFeathersBrown, Texture2D* texFeathersBeige, float t)
	{
		float texScale = 1.5;
		Vector3 wingSize = Vector3(voxel*1.5, voxel*7, voxel*8);

		Transform wingTr, feather1Tr, feather2Tr;

		wingTr.setPosition(0, 0, 0);
		wingTr.setRotation(0, 0, 90);
		wingTr.setScale(1, 1, 1);

		feather1Tr.setPosition(0, voxel*1.5, -wingSize.z/2);
		feather1Tr.setRotation(-80 + 10 * sin(t*2.37), 0, 90);
		feather1Tr.setScale(1, 1, 1);

		feather2Tr.setPosition(0, wingSize.y-voxel*2, -wingSize.z/2);
		feather2Tr.setRotation(-80 + 10 * sin(t*2.52), 0, 90);
		feather2Tr.setScale(1, 1, 1);

		glPushMatrix();

		glBindTexture(GL_TEXTURE_2D, texFeathersBrown->getNativeHandle());
		
		glLoadMatrixf((viewMatrix * wingTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * wingTr.getMatrix(), wingSize, texScale);

		glLoadMatrixf((viewMatrix * wingTr.getMatrix() * feather1Tr.getMatrix()).data);
		wingFeather(viewMatrix * wingTr.getMatrix() * feather1Tr.getMatrix(), texFeathersBrown, texFeathersBeige, voxel*5);

		glLoadMatrixf((viewMatrix * wingTr.getMatrix() * feather2Tr.getMatrix()).data);
		wingFeather(viewMatrix * wingTr.getMatrix() * feather2Tr.getMatrix(), texFeathersBrown, texFeathersBeige, voxel*6);

		glBindTexture(GL_TEXTURE_2D, 0);

		glPopMatrix();
	}

	static void neck1(const Matrix4& viewMatrix, Texture2D* texFeathersBrown)
	{
		float texScale = .75;
		Vector3 neckSize = Vector3(voxel*2, voxel*6, voxel*2);

		Transform neckTr;

		neckTr.setPosition(0, -voxel*1.5, voxel*.5);
		neckTr.setRotation(0, 0, 0);
		neckTr.setScale(1, 1, 1);

		glPushMatrix();

		glBindTexture(GL_TEXTURE_2D, texFeathersBrown->getNativeHandle());
		
		glLoadMatrixf((viewMatrix * neckTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * neckTr.getMatrix(), neckSize, texScale);

		glBindTexture(GL_TEXTURE_2D, 0);

		glPopMatrix();
	}

	static void neck2(const Matrix4& viewMatrix, Texture2D* texFeathersBrown)
	{
		float texScale = .75;
		Vector3 neckSize = Vector3(voxel*1.99, voxel*6, voxel*1.99);

		Transform neckTr;

		neckTr.setPosition(0, 0, -voxel*.9);
		neckTr.setRotation(90, 0, 0);
		neckTr.setScale(1, 1, 1);

		glPushMatrix();

		glBindTexture(GL_TEXTURE_2D, texFeathersBrown->getNativeHandle());
		
		glLoadMatrixf((viewMatrix * neckTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * neckTr.getMatrix(), neckSize, texScale);

		glBindTexture(GL_TEXTURE_2D, 0);

		glPopMatrix();
	}

	static void hair(const Matrix4& viewMatrix,  Texture2D* texRed, float height=voxel*4)
	{
		Transform hairTr;

		hairTr.setPosition(0, -voxel*.5, 0);
		hairTr.setRotation(0, 0, 0);
		hairTr.setScale(.5, 1, 1);

		glPushMatrix();

		glBindTexture(GL_TEXTURE_2D, texRed->getNativeHandle());
		
		glLoadMatrixf((viewMatrix * hairTr.getMatrix()).data);
		Shapes::drawCylinder(voxel, 0, height+voxel*.5, 6);

		glBindTexture(GL_TEXTURE_2D, 0);

		glPopMatrix();
	}

	static void head(const Matrix4& viewMatrix, Texture2D* texFeathersBrown,  Texture2D* texRed, float t)
	{
		float texScale = 1;
		Vector3 headSize = Vector3(voxel*5, voxel*5, voxel*5.5);
		Vector3 topSize = Vector3(voxel*5.01, voxel, voxel*5.51);

		Transform headTr, topTr;
		Transform hair1, hair2, hair3, hair4;

		headTr.setPosition(0, -headSize.y+voxel*2.25, headSize.z/2);
		headTr.setRotation(0, 0, 0);
		headTr.setScale(1, 1, 1);

		topTr.setPosition(0, headSize.y-topSize.y+voxel*.01, 0);
		topTr.setRotation(0, 0, 0);
		topTr.setScale(1, 1, 1);

		hair1.setPosition(0, topSize.y, voxel*1.85);
		hair1.setRotation(0, 0, 10 * sin(t*2.573));
		hair1.setScale(1, 1, 1);

		hair2.setPosition(0, topSize.y, voxel*.7);
		hair2.setRotation(-1, 0, 10 * sin(t*2.712));
		hair2.setScale(1, 1, 1);

		hair3.setPosition(0, topSize.y, -voxel*0.9);
		hair3.setRotation(-20, 0, 10 * sin(t*2.12));
		hair3.setScale(1, 1, 1);

		hair4.setPosition(0, topSize.y, -voxel*2.4);
		hair4.setRotation(-40, 0, 10 * sin(t*2.68));
		hair4.setScale(1, 1, 1);

		glPushMatrix();

		glBindTexture(GL_TEXTURE_2D, texFeathersBrown->getNativeHandle());
		
		glLoadMatrixf((viewMatrix * headTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * headTr.getMatrix(), headSize, texScale, false, true);

		glBindTexture(GL_TEXTURE_2D, texRed->getNativeHandle());
		
		glLoadMatrixf((viewMatrix * headTr.getMatrix() * topTr.getMatrix()).data);
		Shapes::drawCuboid(viewMatrix * headTr.getMatrix() * topTr.getMatrix(), topSize, texScale, true);

		glLoadMatrixf((viewMatrix * headTr.getMatrix() * topTr.getMatrix() * hair1.getMatrix()).data);
		hair(viewMatrix * headTr.getMatrix() * topTr.getMatrix() * hair1.getMatrix(), texRed);

		glLoadMatrixf((viewMatrix * headTr.getMatrix() * topTr.getMatrix() * hair2.getMatrix()).data);
		hair(viewMatrix * headTr.getMatrix() * topTr.getMatrix() * hair2.getMatrix(), texRed, voxel*6);

		glLoadMatrixf((viewMatrix * headTr.getMatrix() * topTr.getMatrix() * hair3.getMatrix()).data);
		hair(viewMatrix * headTr.getMatrix() * topTr.getMatrix() * hair3.getMatrix(), texRed, voxel*5);

		glLoadMatrixf((viewMatrix * headTr.getMatrix() * topTr.getMatrix() * hair4.getMatrix()).data);
		hair(viewMatrix * headTr.getMatrix() * topTr.getMatrix() * hair4.getMatrix(), texRed, voxel*3);

		glBindTexture(GL_TEXTURE_2D, 0);

		glPopMatrix();
	}

	static void beak1(const Matrix4& viewMatrix,  Texture2D* texPink)
	{
		Transform beakTr;

		beakTr.setPosition(0, voxel/2, 0);
		beakTr.setRotation(90, -3, 90);
		beakTr.setScale(1, 1, 1);

		glPushMatrix();

		glBindTexture(GL_TEXTURE_2D, texPink->getNativeHandle());
		
		glLoadMatrixf((viewMatrix * beakTr.getMatrix()).data);
		Shapes::drawCylinder(voxel, 0, voxel*8, 3);

		glBindTexture(GL_TEXTURE_2D, 0);

		glPopMatrix();
	}

	static void beak2(const Matrix4& viewMatrix,  Texture2D* texPink)
	{
		Transform beakTr;

		beakTr.setPosition(0, -voxel/2, 0);
		beakTr.setRotation(90, -6.5, -90);
		beakTr.setScale(1, 1, 1);

		glPushMatrix();

		glBindTexture(GL_TEXTURE_2D, texPink->getNativeHandle());
		
		glLoadMatrixf((viewMatrix * beakTr.getMatrix()).data);
		Shapes::drawCylinder(voxel*.9, 0, voxel*5, 3);

		glBindTexture(GL_TEXTURE_2D, 0);

		glPopMatrix();
	}
};