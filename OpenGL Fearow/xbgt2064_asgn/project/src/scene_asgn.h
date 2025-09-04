#pragma once
#include "framework/scenebase.h"
#include "framework/texture/texture_utils.h"
#include <glad/glad.h>
#include <map>
#include "transform.h"
#include "shapes.h"
#include "fearow.h"
#include "simplelabel.h"
#include "environment.h"
using namespace std;

class SceneASGN : public SceneBase
{
public:

	Texture2D* texFace1, * texFace2, * texFace3;
	Texture2D* texFeathersBeige, * texFeathersBrown;
	Texture2D* texPink, * texRed, * texWhite;
	Texture2D* texGround, * texGrass, * texClouds;

	void loadTextures()
	{
		TextureConfig cfgRepeatLinear(TextureWrapMode::REPEAT, TextureWrapMode::REPEAT, TextureFilterMode::LINEAR, true);
		TextureConfig cfgClampLinear(TextureWrapMode::CLAMP, TextureWrapMode::CLAMP, TextureFilterMode::LINEAR, true);
		TextureConfig cfgRepeatPixel(TextureWrapMode::REPEAT, TextureWrapMode::REPEAT, TextureFilterMode::NEAREST, true);
		TextureConfig cfgClampPixel(TextureWrapMode::CLAMP, TextureWrapMode::CLAMP, TextureFilterMode::NEAREST, true);

		texFace1 = TextureUtils::loadFromFile("../assets/face1.jpg", cfgClampLinear);
		texFace2 = TextureUtils::loadFromFile("../assets/face2.jpg", cfgClampLinear);
		texFace3 = TextureUtils::loadFromFile("../assets/face3.jpg", cfgClampLinear);
		texFeathersBeige = TextureUtils::loadFromFile("../assets/feathers_beige.jpg", cfgRepeatLinear);
		texFeathersBrown = TextureUtils::loadFromFile("../assets/feathers_brown.jpg", cfgRepeatLinear);
		texPink = TextureUtils::loadFromFile("../assets/pink.jpg", cfgRepeatLinear);
		texRed = TextureUtils::loadFromFile("../assets/red.jpg", cfgRepeatLinear);
		texWhite = TextureUtils::loadFromFile("../assets/white.jpg", cfgRepeatLinear);
		texGround = TextureUtils::loadFromFile("../assets/ground.jpg", cfgRepeatLinear);
		texGrass = TextureUtils::loadFromFile("../assets/grass.png", cfgClampLinear);
		texClouds = TextureUtils::loadFromFile("../assets/clouds.png", cfgRepeatLinear);

		glEnable(GL_TEXTURE_2D);
	}

	Transform rootTr, wiggleTr, bodyTr;
	Transform neck1Tr, neck2Tr, headTr, faceTr, beak1Tr, beak2Tr;
	Transform thighRTr, shinRTr, ankleRTr;
	Transform thighLTr, shinLTr, ankleLTr;
	Transform wingR1Tr, wingR2Tr;
	Transform wingL1Tr, wingL2Tr;
	Transform tail1Tr, tail2Tr, tail3Tr, tail4Tr;
	Transform cloudsTr;

	void setTransforms()
	{
		rootTr.setPosition(0, 0, 0);
		rootTr.setRotation(0, 0, 0);
		rootTr.setScale(1, 1, 1);
		
		wiggleTr.setPosition(0, 0, 0);
		wiggleTr.setRotation(0, 0, 0);
		wiggleTr.setScale(1, 1, 1);

		bodyTr.setPosition(0, voxel*12, 0);
		bodyTr.setRotation(0, 0, 0);
		bodyTr.setScale(1, 1, 1);

		neck1Tr.setPosition(0, voxel*2, voxel*6.5);
		neck1Tr.setRotation(0, 0, 0);
		neck1Tr.setScale(1, 1, 1);

		neck2Tr.setPosition(0, voxel*3.49, voxel*.55);
		neck2Tr.setRotation(0, 0, 0);
		neck2Tr.setScale(1, 1, 1);

		headTr.setPosition(0, 0, voxel*4.5);
		headTr.setRotation(0, 0, 0);
		headTr.setScale(1, 1, 1);

		faceTr.setPosition(0, -voxel*.25, voxel*5.501);
		faceTr.setRotation(90, 0, 180);
		faceTr.setScale(1, 1, 1);

		beak1Tr.setPosition(0, -voxel, voxel*5);
		beak1Tr.setRotation(0, 0, 0);
		beak1Tr.setScale(1.5, 1, 1);

		beak2Tr.setPosition(0, -voxel, voxel*5);
		beak2Tr.setRotation(0, 0, 0);
		beak2Tr.setScale(1.5, 1, 1);

		thighRTr.setPosition(-voxel*2, -voxel*3, -voxel*2);
		thighRTr.setRotation(0, 0, 0);
		thighRTr.setScale(1, 1, 1);

		shinRTr.setPosition(0, -voxel*4+voxel/2, 0);
		shinRTr.setRotation(0, 0, 0);
		shinRTr.setScale(1, 1, 1);

		ankleRTr.setPosition(0, -voxel*4+voxel/2, 0);
		ankleRTr.setRotation(0, 0, 0);
		ankleRTr.setScale(1, 1, 1);

		thighLTr.setPosition(voxel*2, -voxel*3, -voxel*2);
		thighLTr.setRotation(0, 0, 0);
		thighLTr.setScale(1, 1, 1);

		shinLTr.setPosition(0, -voxel*4+voxel/2, 0);
		shinLTr.setRotation(0, 0, 0);
		shinLTr.setScale(1, 1, 1);

		ankleLTr.setPosition(0, -voxel*4+voxel/2, 0);
		ankleLTr.setRotation(0, 0, 0);
		ankleLTr.setScale(1, 1, 1);

		wingR1Tr.setPosition(-voxel*4, voxel*2.5, voxel);
		wingR1Tr.setRotation(0, 0, 0);
		wingR1Tr.setScale(1, 1, 1);

		wingR2Tr.setPosition(-voxel*8, 0, 0);
		wingR2Tr.setRotation(0, 0, 0);
		wingR2Tr.setScale(1, 1, 1);

		wingL1Tr.setPosition(voxel*4, voxel*2.5, voxel);
		wingL1Tr.setRotation(0, 0, 0);
		wingL1Tr.setScale(-1, 1, 1);

		wingL2Tr.setPosition(-voxel*8, 0, 0);
		wingL2Tr.setRotation(0, 0, 0);
		wingL2Tr.setScale(1, 1, 1);

		tail1Tr.setPosition(-voxel*2.5, voxel*3, -voxel*5);
		tail1Tr.setRotation(-105, 10, 0);
		tail1Tr.setScale(1, 1, 1);

		tail2Tr.setPosition(-voxel*.5, voxel*3, -voxel*5);
		tail2Tr.setRotation(-100, 5, 0);
		tail2Tr.setScale(1, 1, 1);

		tail3Tr.setPosition(voxel*.5, voxel*3, -voxel*5);
		tail3Tr.setRotation(-100, -5, 0);
		tail3Tr.setScale(1, 1, 1);

		tail4Tr.setPosition(voxel*2.5, voxel*3, -voxel*5);
		tail4Tr.setRotation(-105, -10, 0);
		tail4Tr.setScale(1, 1, 1);

		cloudsTr.setPosition(0, -6, 0);
		cloudsTr.setRotation(0, 0, 0);
		cloudsTr.setScale(1, 1, 1);
	}

	SimpleLabel* label;

	void init() override
	{
		loadTextures();
		setTransforms();
		label = new SimpleLabel("../assets/sharetech.fontdata");

		glClearColor(.5f, .8f, .9f, 1); //sky colour
	}

	void deinit() override
	{
		glDisable(GL_TEXTURE_2D);
	}

	float MathfAbs(float val)
	{
		if (val<0) return -val;
		else return val;
	}

	float t, delta;
	float faceVal;

	void update() override
	{
		t = App::getTime();
		delta = App::getDeltaTime();
		faceVal = sin(t);

		rootTr.rotateYBy(50 * delta);
		wiggleTr.setPosition(-2+voxel* sin(t*1.75), .6 * MathfAbs(sin((t+1.75)*4)), voxel* sin(t*1.5));

		bodyTr.setRotation(0, 10 * sin(t*2.124), 10 * sin(t*2.458));

		neck1Tr.setRotation(25 + 25 * sin(t*1.241), 15 * sin(t*1.124), 0);
		neck2Tr.setRotation(-15 + 25 * sin(t*1.57), 10 * sin(t*1.463), 0);

		headTr.setRotation(15 * sin(t*2.135), 15 * sin(t*2.86), 0);

		beak1Tr.setRotation(-10 - 10 * sin(t*4), 0, 0);
		beak2Tr.setRotation(10 + 10 * sin(t*4), 0, 0);

		thighRTr.setRotation(35 + 20 * sin(t*4.12), 0, 0);
		shinRTr.setRotation(35 + 20 * sin(t*4.246), 0, 0);
		ankleRTr.setRotation(35 + 20 * sin(t*4.679), 0, 0);

		thighLTr.setRotation(35 + 20 * -sin(t*4.235), 0, 0);
		shinLTr.setRotation(35 + 20 * -sin(t*4.358), 0, 0);
		ankleLTr.setRotation(35 + 20 * -sin(t*4.72), 0, 0);

		wingR1Tr.setRotation(25 * sin(t*8), 0, 60 * cos(t*8));
		wingR2Tr.setRotation(10 * cos(t*8), 0, 60 * sin(t*8));

		wingL1Tr.setRotation(25 * sin(t*8), 0, 60 * -cos(t*8));
		wingL2Tr.setRotation(10 * cos(t*8), 0, 60 * sin(t*8));

		tail1Tr.setRotation(-105 + 5* sin(t*4.53), 10, 0);
		tail2Tr.setRotation(-100 + 5* sin(t*4.13), 5, 0);
		tail3Tr.setRotation(-100 + 5* sin(t*4.796), -5, 0);
		tail4Tr.setRotation(-105 + 5* sin(t*4.9), -10, 0);

		cloudsTr.rotateYBy(-5 * delta);
	}

	void FearowFace()
	{
		if(faceVal<-.2 || faceVal>.2) glBindTexture(GL_TEXTURE_2D, texFace1->getNativeHandle());
		else if((faceVal >= -.2 && faceVal < -.1) || (faceVal <= .2 && faceVal > .1)) glBindTexture(GL_TEXTURE_2D, texFace2->getNativeHandle());
		else glBindTexture(GL_TEXTURE_2D, texFace3->getNativeHandle());

		Shapes::drawQuadTex(Vector2(voxel * 5, voxel * 5));

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void drawFearow(const Matrix4& viewMatrix)
	{
		glPushMatrix();

		glLoadMatrixf((viewMatrix * rootTr.getMatrix()).data);
		
		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix()).data);

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix()).data);
		Fearow::body(viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix(), texFeathersBrown, texFeathersBeige);

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * neck1Tr.getMatrix()).data);
		Fearow::neck1(viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * neck1Tr.getMatrix(), texFeathersBrown);

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * neck1Tr.getMatrix() * neck2Tr.getMatrix()).data);
		Fearow::neck2(viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * neck1Tr.getMatrix() * neck2Tr.getMatrix(), texFeathersBrown);

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * neck1Tr.getMatrix() * neck2Tr.getMatrix() * headTr.getMatrix()).data);
		Fearow::head(viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * neck1Tr.getMatrix() * neck2Tr.getMatrix() * headTr.getMatrix(), texFeathersBrown, texRed, App::getTime());

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * neck1Tr.getMatrix() * neck2Tr.getMatrix() * headTr.getMatrix() * faceTr.getMatrix()).data);
		FearowFace();

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * neck1Tr.getMatrix() * neck2Tr.getMatrix() * headTr.getMatrix() * beak1Tr.getMatrix()).data);
		Fearow::beak1(viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * neck1Tr.getMatrix() * neck2Tr.getMatrix() * headTr.getMatrix() * beak1Tr.getMatrix(), texPink);

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * neck1Tr.getMatrix() * neck2Tr.getMatrix() * headTr.getMatrix() * beak2Tr.getMatrix()).data);
		Fearow::beak2(viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * neck1Tr.getMatrix() * neck2Tr.getMatrix() * headTr.getMatrix() * beak2Tr.getMatrix(), texPink);

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * thighRTr.getMatrix()).data);
		Fearow::thigh(viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * thighRTr.getMatrix(), texFeathersBrown);

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * thighRTr.getMatrix() * shinRTr.getMatrix()).data);
		Fearow::shin(viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * thighRTr.getMatrix() * shinRTr.getMatrix(), texPink);

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * thighRTr.getMatrix() * shinRTr.getMatrix() * ankleRTr.getMatrix()).data);
		Fearow::foot(viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * thighRTr.getMatrix() * shinRTr.getMatrix() * ankleRTr.getMatrix(), texPink, texWhite, App::getTime());

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * thighLTr.getMatrix()).data);
		Fearow::thigh(viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * thighLTr.getMatrix(), texFeathersBrown);

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * thighLTr.getMatrix() * shinLTr.getMatrix()).data);
		Fearow::shin(viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * thighLTr.getMatrix() * shinLTr.getMatrix(), texPink);

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * thighLTr.getMatrix() * shinLTr.getMatrix() * ankleLTr.getMatrix()).data);
		Fearow::foot(viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * thighLTr.getMatrix() * shinLTr.getMatrix() * ankleLTr.getMatrix(), texPink, texWhite, App::getTime());

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * wingR1Tr.getMatrix()).data);
		Fearow::wingR1(viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * wingR1Tr.getMatrix(), texFeathersBrown, texFeathersBeige, App::getTime());

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * wingR1Tr.getMatrix() * wingR2Tr.getMatrix()).data);
		Fearow::wingR2(viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * wingR1Tr.getMatrix() * wingR2Tr.getMatrix(), texFeathersBrown, texFeathersBeige, App::getTime());

		glFrontFace(GL_CW);

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * wingL1Tr.getMatrix()).data);
		Fearow::wingR1(viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * wingL1Tr.getMatrix(), texFeathersBrown, texFeathersBeige, App::getTime());

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * wingL1Tr.getMatrix() * wingL2Tr.getMatrix()).data);
		Fearow::wingR2(viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * wingL1Tr.getMatrix() * wingL2Tr.getMatrix(), texFeathersBrown, texFeathersBeige, App::getTime());

		glFrontFace(GL_CCW);

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * tail1Tr.getMatrix()).data);
		Fearow::tail(viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * tail1Tr.getMatrix(), texFeathersBrown, voxel*6.5);

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * tail2Tr.getMatrix()).data);
		Fearow::tail(viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * tail2Tr.getMatrix(), texFeathersBrown);

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * tail3Tr.getMatrix()).data);
		Fearow::tail(viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * tail3Tr.getMatrix(), texFeathersBrown);

		glLoadMatrixf((viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * tail4Tr.getMatrix()).data);
		Fearow::tail(viewMatrix * rootTr.getMatrix() * wiggleTr.getMatrix() * bodyTr.getMatrix() * tail4Tr.getMatrix(), texFeathersBrown, voxel*6.5);
		
		glPopMatrix();
	}

	void drawLabel(const Matrix4& viewMatrix)
	{
		Transform labelTr;

		labelTr.setPosition(-1.25, -1, 0);
		labelTr.setRotation(0, 0, 0);
		labelTr.setScale(.5, .5, .5);

		glPushMatrix();

		glLoadMatrixf((viewMatrix * labelTr.getMatrix()).data);
		label->render("Joshua Yeoh\n0135760\nFearow");

		glPopMatrix();
	}

	void drawOpaques(const Matrix4& viewMatrix)
	{
		drawFearow(viewMatrix);

		Environment::ground(viewMatrix, texGround, Vector3(0,-4,0));
	}

	void drawAlphaTest(const Matrix4& viewMatrix)
	{
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, .75);

		drawLabel(viewMatrix);

		for (int i = -11; i <= 11; i++)
		{
			for (int j = -11; j <= 11; j++)
			{
				Environment::grass(viewMatrix, texGrass, Vector3(i,-4,j), Vector3(3,3,3), App::getTime());
			}
		}

		glDisable(GL_ALPHA_TEST);
	}

	void drawClouds(const Matrix4& viewMatrix)
	{
		glPushMatrix();

		glLoadMatrixf((viewMatrix * cloudsTr.getMatrix()).data);
		Environment::clouds(viewMatrix * cloudsTr.getMatrix(), texClouds);

		glPopMatrix();
	}

	void drawAlphaBlend(const Matrix4& viewMatrix)
	{
		Matrix4 camMatrix = Matrix4::invert(viewMatrix);
		Vector3 camPos(camMatrix.data[12], camMatrix.data[13], camMatrix.data[14]);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_FALSE);

		map<float, int> sortDict;

		for (map<float,int>::reverse_iterator it = sortDict.rbegin(); it != sortDict.rend(); it++)
		{
			int i = it->second;

			// Then draw according to the sort from end to beginning.
		}		

		drawClouds(viewMatrix);

		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}

	void disableFaceCulling()
	{
		glDisable(GL_CULL_FACE);
		static int polygonModes[2];
		glGetIntegerv(GL_POLYGON_MODE, polygonModes);
		glPolygonMode(GL_BACK, polygonModes[0]);
	}

	void drawGrid()
	{
		drawHorizontalGridLines();
		//drawVerticalGridLines();
		drawWorldOriginLines();
	}

	void draw(const Matrix4& viewMatrix) override
	{
		glLoadMatrixf((GLfloat*)viewMatrix.data);
		//drawGrid();

		glColor3f(1, 1, 1);
		drawOpaques(viewMatrix);

		glPushAttrib(GL_ALL_ATTRIB_BITS);

		disableFaceCulling();
		drawAlphaTest(viewMatrix);
		drawAlphaBlend(viewMatrix);

		glPopAttrib();
	}
};