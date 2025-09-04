#pragma once
#include "framework/scenebase.h"
#include "framework/texture/texture_utils.h"
#include <glad/glad.h> // Include glad.h to use gl functions
using namespace std;

const float PI = 3.14159;

class SceneEx2 : public SceneBase
{
public:

	Texture2D* texBirch;
	Texture2D* texBlackWool;
	Texture2D* texCobble;
	Texture2D* texOak;
	Texture2D* texOakTop;
	Texture2D* texSpruce;
	Texture2D* texPlanks;

	Texture2D* texWhiteWool;
	Texture2D* texDarkOak;
	Texture2D* texCyanWool;
	Texture2D* texBlanket;

	Texture2D* texJunglePlanks;
	Texture2D* texSmoothStone;

	Texture2D* texAcaciaPlanks;
	Texture2D* texDrawer;

	Texture2D* texClockBase;
	Texture2D* texClockDesign;
	Texture2D* texClockFace;
	Texture2D* texClockHole;
	Texture2D* texClockTop;
	Texture2D* texClockWood;
	Texture2D* texClockWoodDark;
	Texture2D* texPendulumHead;
	Texture2D* texPendulumStick;

	void init() override
	{
		TextureConfig cfgRepeatLinear(TextureWrapMode::REPEAT, TextureWrapMode::REPEAT, TextureFilterMode::LINEAR, true);
		TextureConfig cfgClampLinear(TextureWrapMode::CLAMP, TextureWrapMode::CLAMP, TextureFilterMode::LINEAR, true);
		TextureConfig cfgRepeatPixel(TextureWrapMode::REPEAT, TextureWrapMode::REPEAT, TextureFilterMode::NEAREST, true);
		TextureConfig cfgClampPixel(TextureWrapMode::CLAMP, TextureWrapMode::CLAMP, TextureFilterMode::NEAREST, true);
		
		texBirch = TextureUtils::loadFromFile("../assets/room/birch_log.jpg", cfgRepeatPixel);
		texBlackWool = TextureUtils::loadFromFile("../assets/room/black_wool.jpg", cfgRepeatPixel);
		texCobble = TextureUtils::loadFromFile("../assets/room/cobblestone.jpg", cfgRepeatPixel);
		texOak = TextureUtils::loadFromFile("../assets/room/oak_log.jpg", cfgRepeatPixel);
		texOakTop = TextureUtils::loadFromFile("../assets/room/oak_log_top.jpg", cfgRepeatPixel);
		texSpruce = TextureUtils::loadFromFile("../assets/room/spruce_log.jpg", cfgRepeatPixel);
		texPlanks = TextureUtils::loadFromFile("../assets/room/spruce_planks.jpg", cfgRepeatPixel);

		texWhiteWool = TextureUtils::loadFromFile("../assets/bed/white_wool.jpg", cfgRepeatPixel);
		texDarkOak = TextureUtils::loadFromFile("../assets/bed/dark_oak_planks.jpg", cfgRepeatPixel);
		texCyanWool = TextureUtils::loadFromFile("../assets/bed/cyan_wool.jpg", cfgRepeatPixel);
		texBlanket = TextureUtils::loadFromFile("../assets/bed/blanket.jpg", cfgRepeatLinear);

		texJunglePlanks = TextureUtils::loadFromFile("../assets/barrel/jungle_planks.jpg", cfgRepeatPixel);
		texSmoothStone = TextureUtils::loadFromFile("../assets/barrel/smooth_stone.jpg", cfgRepeatPixel);

		texAcaciaPlanks = TextureUtils::loadFromFile("../assets/shelf/acacia_planks.jpg", cfgRepeatPixel);
		texDrawer = TextureUtils::loadFromFile("../assets/shelf/drawer.jpg", cfgRepeatPixel);

		texClockBase = TextureUtils::loadFromFile("../assets/clock/clock_base.png", cfgClampLinear);
		texClockDesign = TextureUtils::loadFromFile("../assets/clock/clock_design.jpg", cfgClampLinear);
		texClockFace = TextureUtils::loadFromFile("../assets/clock/clock_face.png", cfgClampLinear);
		texClockHole = TextureUtils::loadFromFile("../assets/clock/clock_hole.png", cfgClampLinear);
		texClockTop = TextureUtils::loadFromFile("../assets/clock/clock_top.png", cfgClampLinear);
		texClockWood = TextureUtils::loadFromFile("../assets/clock/clock_wood.jpg", cfgRepeatLinear);
		texClockWoodDark = TextureUtils::loadFromFile("../assets/clock/clock_wood_dark.jpg", cfgRepeatLinear);
		texPendulumHead = TextureUtils::loadFromFile("../assets/clock/pendulum_head.png", cfgClampLinear);
		texPendulumStick = TextureUtils::loadFromFile("../assets/clock/pendulum_stick.png", cfgClampLinear);
		
		glEnable(GL_TEXTURE_2D);
		
		glClearColor(.5f, .8f, .9f, 1); //sky colour
	}

	void deinit() override
	{
		glDisable(GL_TEXTURE_2D);
	}

	float currentTime, sineTime, frequency = 3;

	void update() override
	{
		currentTime = App::getTime()*frequency;
		sineTime = sin(currentTime);
	}

	void drawQuad(float width=1, float length=1, float texScale=1)
	{
		float texRatioX, texRatioY;

		if (width > length)
		{
			texRatioX = texScale;
			texRatioY = texScale * length / width;
		}
		else
		{
			texRatioX = texScale * width / length;
			texRatioY = texScale;
		}
		
		glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2f(0, texRatioY);
		glVertex3f(-width*.5, 0, length*.5);

		glTexCoord2f(texRatioX, texRatioY);
		glVertex3f(width*.5, 0, length*.5);

		glTexCoord2f(0, 0);
		glVertex3f(-width*.5, 0, -length*.5);

		glTexCoord2f(texRatioX, 0);
		glVertex3f(width*.5, 0, -length*.5);

		glEnd();
	}

	void drawQuadTex(float width=1, float length=1, float texScale=1)
	{		
		glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2f(0, texScale);
		glVertex3f(-width*.5, 0, length*.5);

		glTexCoord2f(texScale, texScale);
		glVertex3f(width*.5, 0, length*.5);

		glTexCoord2f(0, 0);
		glVertex3f(-width*.5, 0, -length*.5);

		glTexCoord2f(texScale, 0);
		glVertex3f(width*.5, 0, -length*.5);

		glEnd();
	}

	void drawCuboid(float width=1, float length=1, float height=1, float texScale=1)
	{
		//bottom
		glPushMatrix();
		glRotatef(180, 1, 0, 0);
		drawQuad(width,length,texScale);
		glPopMatrix();

		//top
		glPushMatrix();
		glTranslatef(0, height, 0);
		drawQuad(width,length,texScale);
		glPopMatrix();

		//front
		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, length*.5, -height*.5);
		drawQuad(width,height,texScale);
		glPopMatrix();

		//back
		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, length*.5, -height*.5);
		drawQuad(width,height,texScale);
		glPopMatrix();
		glPopMatrix();

		//left
		glPushMatrix();
		glRotatef(90, 0, 0, 1);
		glRotatef(90, 0, 1, 0);
		glTranslatef(0, width*.5, height*.5);
		drawQuad(length,height,texScale);
		glPopMatrix();

		//right
		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		glPushMatrix();
		glRotatef(90, 0, 0, 1);
		glRotatef(90, 0, 1, 0);
		glTranslatef(0, width*.5, height*.5);
		drawQuad(length,height,texScale);
		glPopMatrix();
		glPopMatrix();
	}

	void drawDisk(float innerRadius=0, float outerRadius=1, int slices=16, float texScale=1)
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

	void drawCylinder(float baseRadius=1, float topRadius=1, float height=2, int slices=16, float texScale=1)
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

	void drawFullCylinder(float baseRadius=1, float topRadius=1, float height=2, int slices=16, float texScale=1)
	{
		drawCylinder(baseRadius, topRadius, height, slices, texScale);

		//top disk
		glPushMatrix();
		glTranslatef(0, height, 0);
		drawDisk(0, topRadius, slices, texScale);
		glPopMatrix();

		//bottom disk
		glPushMatrix();
		glRotatef(180, 1, 0, 0);
		drawDisk(0, baseRadius, slices, texScale);
		glPopMatrix();
	}

	void floor(float width, float length, float height, float texScale=1)
	{
		glBindTexture(GL_TEXTURE_2D, texPlanks->getNativeHandle());

		glPushMatrix();
		glRotatef(180, 1, 0, 0);
		drawCuboid(width, length, height, texScale);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void wall(float width=1, float length=1, float height=1, float texScale=1)
	{
		glBindTexture(GL_TEXTURE_2D, texBirch->getNativeHandle());

		drawCuboid(width, length, height, texScale);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void wallBase(float width=1, float length=1, float height=1, float texScale=1)
	{
		glBindTexture(GL_TEXTURE_2D, texCobble->getNativeHandle());

		drawCuboid(width, length, height, texScale);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void cornerEnd(float radius=1, float height=1, int slices=8, float texScale=1)
	{
		glBindTexture(GL_TEXTURE_2D, texSpruce->getNativeHandle());

		drawCylinder(radius, radius, height, slices, texScale);

		glBindTexture(GL_TEXTURE_2D, texOakTop->getNativeHandle());

		//top disk
		glPushMatrix();
		glTranslatef(0, height, 0);
		drawDisk(0, radius, slices, texScale);
		glPopMatrix();

		//bottom disk
		glPushMatrix();
		glRotatef(180, 1, 0, 0);
		drawDisk(0, radius, slices, texScale);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void cornerPost(float radius = 1, float height = 1, int slices = 8, float texScale = 1)
	{
		glBindTexture(GL_TEXTURE_2D, texOak->getNativeHandle());

		drawCylinder(radius, radius, height, slices, texScale);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void corner(float cornerRadius = .5, float height=1, int slices = 8, float texScale = 1)
	{
		cornerEnd(cornerRadius*1.2, height*.2, slices, texScale);

		glPushMatrix();
		glTranslatef(0, height * .2, 0);
		cornerPost(cornerRadius, height*.6, slices, texScale);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, height * .8, 0);
		cornerEnd(cornerRadius*1.2, height*.2, slices, texScale);
		glPopMatrix();
	}

	void carpet(float radius = 1, int slices = 8, float texScale = 1)
	{
		glBindTexture(GL_TEXTURE_2D, texBlackWool->getNativeHandle());

		drawDisk(0, radius, slices, texScale);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void bed(float width=3, float length=5, float height=5, float legHeight=.4)
	{
		glBindTexture(GL_TEXTURE_2D, texDarkOak->getNativeHandle());
		
		//top right
		glPushMatrix();
		glTranslatef(width * .5 - legHeight * .25, 0, -length * .5 + legHeight * .25);
		drawCuboid(legHeight*.5, legHeight*.5, height,3);
		glPopMatrix();

		//top left
		glPushMatrix();
		glTranslatef(-width * .5 + legHeight * .25, 0, -length * .5 + legHeight * .25);
		drawCuboid(legHeight*.5, legHeight*.5, height,3);
		glPopMatrix();

		//bottom right
		glPushMatrix();
		glTranslatef(width * .5 - legHeight * .25, 0, length * .5 - legHeight * .25);
		drawCuboid(legHeight*.5, legHeight*.5, height,3);
		glPopMatrix();

		//bottom left
		glPushMatrix();
		glTranslatef(-width * .5 + legHeight * .25, 0, length * .5 - legHeight * .25);
		drawCuboid(legHeight*.5, legHeight*.5, height,3);
		glPopMatrix();

		//base
		glPushMatrix();
		glTranslatef(0, legHeight, 0);
		drawCuboid(width-.1, length-.1, height*.2, 3);
		glPopMatrix();
		
		//top
		glPushMatrix();
		glRotatef(180, 1, 0, 0);
		glTranslatef(0, -height+.1, 0);
		drawCuboid(width-.1, length-.1, height*.1, 3);
		glPopMatrix();

		//back
		glPushMatrix();
		glTranslatef(0, legHeight, -length*.5);
		drawCuboid(width-.1, .1, height-legHeight-.1, 3);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, texWhiteWool->getNativeHandle());
		
		//bed
		glPushMatrix();
		glTranslatef(0, legHeight+.2, 0);
		drawCuboid(width-.4, length-.4, height*.2, 3);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, texCyanWool->getNativeHandle());

		//pillow left
		glPushMatrix();
		glTranslatef(-width*.5+.8, legHeight+.2+height*.2, -length*.5+.7);
		drawCuboid(width*.5-.4, .6, .2, 3);
		glPopMatrix();

		//pillow right
		glPushMatrix();
		glTranslatef(+width*.5-.8, legHeight+.2+height*.2, -length*.5+.7);
		drawCuboid(width*.5-.4, .6, .2, 3);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, texBlanket->getNativeHandle());

		//blanket
		glPushMatrix();
		glTranslatef(0, legHeight+.21+height*.2, .5);
		drawQuad(width-.4, length*.7, 1);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void barrel(float radius=1, float height=1, int slices=8)
	{
		glBindTexture(GL_TEXTURE_2D, texJunglePlanks->getNativeHandle());

		//bottom
		drawCylinder(radius*.8, radius, height*.25, slices);

		//middle
		glPushMatrix();
		glTranslatef(0, height *.25, 0);
		drawCylinder(radius, radius, height*.5, slices);
		glPopMatrix();
		
		//top
		glPushMatrix();
		glTranslatef(0, height *.75, 0);
		drawCylinder(radius, radius*.8, height*.25, slices);
		glPopMatrix();

		//lid edge
		glPushMatrix();
		glTranslatef(0, height, 0);
		drawDisk(radius*.6, radius*.8, slices);
		glPopMatrix();

		//lid edge inner
		glPushMatrix();
		glTranslatef(0, height, 0);
		drawCylinder(radius*.6, radius*.6, -height*.1, slices);
		glPopMatrix();

		//lid inner fill
		glPushMatrix();
		glTranslatef(0, height*.9, 0);
		drawDisk(0, radius*.6, slices);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, texSmoothStone->getNativeHandle());

		//ring top
		glPushMatrix();
		glTranslatef(0, height*.70, 0);
		drawFullCylinder(radius*1.05, radius*1.05, height*.1, slices);
		glPopMatrix();

		//ring bottom
		glPushMatrix();
		glTranslatef(0, height*.3-height*.1, 0);
		drawFullCylinder(radius*1.05, radius*1.05, height*.1, slices);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void shelf(float width=3, float length=1, float height=4, float texScale=2, float legHeight=.2)
	{
		glBindTexture(GL_TEXTURE_2D, texAcaciaPlanks->getNativeHandle());

		float legWidth=.1;

		//front right
		glPushMatrix();
		glTranslatef(width * .5 - legWidth, 0, length * .5 - legWidth);
		drawCuboid(.1, .1, legHeight, texScale*3);
		glPopMatrix();

		//front left
		glPushMatrix();
		glTranslatef(-width * .5 + legWidth, 0, length * .5 - legWidth);
		drawCuboid(legWidth, legWidth, legHeight, texScale*3);
		glPopMatrix();

		//back right
		glPushMatrix();
		glTranslatef(width * .5 - legWidth, 0, -length * .5 + legWidth);
		drawCuboid(legWidth, legWidth, legHeight, texScale*3);
		glPopMatrix();

		//back left
		glPushMatrix();
		glTranslatef(-width * .5 + legWidth, 0, -length * .5 + legWidth);
		drawCuboid(legWidth, legWidth, legHeight, texScale*3);
		glPopMatrix();

		//bottom
		glPushMatrix();
		glTranslatef(0, legHeight, 0);
		drawCuboid(width, length, height*.25, texScale);
		glPopMatrix();

		float sidesWidth = .2;

		//left
		glPushMatrix();
		glTranslatef(-width*.5+sidesWidth*.5, legHeight+height*.25, 0);
		drawCuboid(sidesWidth, length, height*.75, texScale);
		glPopMatrix();

		//right
		glPushMatrix();
		glTranslatef(width*.5-sidesWidth*.5, legHeight+height*.25, 0);
		drawCuboid(sidesWidth, length, height*.75, texScale);
		glPopMatrix();

		//2nd
		glPushMatrix();
		glTranslatef(0, legHeight+height*.45, 0);
		drawCuboid(width-sidesWidth*2, length, sidesWidth*.5, texScale);
		glPopMatrix();

		//3rd
		glPushMatrix();
		glTranslatef(0, legHeight+height*.7, 0);
		drawCuboid(width-sidesWidth*2, length, sidesWidth*.5, texScale);
		glPopMatrix();

		//4th
		glPushMatrix();
		glTranslatef(0, legHeight+height-sidesWidth*.5-.15, 0);
		drawCuboid(width-sidesWidth*2, length, sidesWidth*.5, texScale);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, texDrawer->getNativeHandle());

		//drawer
		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, length*.5+.01, -legHeight-height*.25+height*.25*.5);
		drawQuadTex(width*.8, height*.25*.8, 1);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void clockBase(float width=1, float length=1, float height=1, float texScale=1)
	{
		glBindTexture(GL_TEXTURE_2D, texClockBase->getNativeHandle());

		//back
		glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0, length*.5, height*.5);
		drawQuadTex(width,height,texScale);
		glPopMatrix();

		//front
		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0, length*.5, height*.5);
		drawQuadTex(width,height,texScale);
		glPopMatrix();
		glPopMatrix();

		//left
		glPushMatrix();
		glRotatef(90, 0, 0, 1);
		glRotatef(90, 0, 1, 0);
		glTranslatef(0, width*.5, height*.5);
		drawQuadTex(length,height,texScale);
		glPopMatrix();

		//right
		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		glPushMatrix();
		glRotatef(90, 0, 0, 1);
		glRotatef(90, 0, 1, 0);
		glTranslatef(0, width*.5, height*.5);
		drawQuadTex(length,height,texScale);
		glPopMatrix();
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void clockBody(float width=1, float length=1, float height=1, float texScale=1)
	{
		glBindTexture(GL_TEXTURE_2D, texClockHole->getNativeHandle());

		//front
		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0, length*.5, height*.5);
		drawQuadTex(width,height,texScale);
		glPopMatrix();
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, texClockWoodDark->getNativeHandle());

		//front inside
		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0, length*.25, height*.5);
		drawQuad(width,height,texScale);
		glPopMatrix();
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, texClockDesign->getNativeHandle());

		//back
		glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0, length*.5, height*.5);
		drawQuadTex(width,height,texScale);
		glPopMatrix();

		//left
		glPushMatrix();
		glRotatef(90, 0, 0, 1);
		glRotatef(90, 0, 1, 0);
		glTranslatef(0, width*.5, height*.5);
		drawQuadTex(length,height,texScale);
		glPopMatrix();

		//right
		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		glPushMatrix();
		glRotatef(90, 0, 0, 1);
		glRotatef(90, 0, 1, 0);
		glTranslatef(0, width*.5, height*.5);
		drawQuadTex(length,height,texScale);
		glPopMatrix();
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void clockHead(float width=1, float length=1, float height=1, float texScale=1)
	{
		glBindTexture(GL_TEXTURE_2D, texClockFace->getNativeHandle());

		//face
		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0, length*.5+.01, height*.5);
		drawDisk(0, width * .5-.05);
		glPopMatrix();
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, texClockTop->getNativeHandle());

		//hat
		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0, length*.5, height+height*.25);
		drawQuadTex(width,height*.5,texScale);
		glPopMatrix();
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, texClockDesign->getNativeHandle());

		//back
		glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0, length*.5, height*.5);
		drawQuadTex(width,height,texScale);
		glPopMatrix();

		//front
		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0, length*.5, height*.5);
		drawQuadTex(width,height,texScale);
		glPopMatrix();
		glPopMatrix();

		//left
		glPushMatrix();
		glRotatef(90, 0, 0, 1);
		glRotatef(90, 0, 1, 0);
		glTranslatef(0, width*.5, height*.5);
		drawQuadTex(length,height,texScale);
		glPopMatrix();

		//right
		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		glPushMatrix();
		glRotatef(90, 0, 0, 1);
		glRotatef(90, 0, 1, 0);
		glTranslatef(0, width*.5, height*.5);
		drawQuadTex(length,height,texScale);
		glPopMatrix();
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, texClockWood->getNativeHandle());

		//top
		glPushMatrix();
		glTranslatef(0, height, 0);
		drawQuad(width,length,texScale);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void clockPendulum(float width = .1, float height = 1.25)
	{
		glBindTexture(GL_TEXTURE_2D, texPendulumStick->getNativeHandle());

		glPushMatrix();
		glTranslatef(0, 0.01, height*.5);
		drawQuadTex(width, height);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, texPendulumHead->getNativeHandle());

		glPushMatrix();
		glTranslatef(0, 0.02, height);
		drawDisk(0, .2);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void clockPendulumAnim(float angle=10)
	{
		glPushMatrix();
		glRotatef(sineTime*angle, 0, 1, 0);
		clockPendulum();
		glPopMatrix();
	}

	void clock(float width=1, float length=1, float height=4, float texScale=2)
	{
		clockBase(width, length, height*.25);

		glBindTexture(GL_TEXTURE_2D, texClockWood->getNativeHandle());

		glPushMatrix();
		glTranslatef(0, height * .25, 0);
		drawCuboid(width + .2, length + .2, .2);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, 0);

		glPushMatrix();
		glTranslatef(0, height * .25+.2, 0);
		clockBody(width, length, height*.5);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, texClockWood->getNativeHandle());

		glPushMatrix();
		glTranslatef(0, height * .25+.2+height*.5, 0);
		drawCuboid(width + .2, length + .2, .2);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, 0);
		
		glPushMatrix();
		glTranslatef(0, height * .25+.2+height*.5+.2, 0);
		clockHead(width, length, width);
		glPopMatrix();

		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, length*.35, -height * .25-.2-height*.5);
		clockPendulumAnim();
		glPopMatrix();
	}

	void drawOpaques(const Matrix4& viewMatrix)
	{
		float roomWidth = 10, roomLength = 10, roomHeight = 6, roomThickness=.2;

		floor(roomWidth+2, roomLength+2, roomThickness, 8);

		//back wall
		glPushMatrix();
		glTranslatef(0, 0, -roomLength * .5);
		wall(roomWidth-.2, roomThickness-.2, roomHeight-.01, 5);
		wallBase(roomWidth, roomThickness, roomHeight*.3, 5);
		glPushMatrix();
		glTranslatef(roomWidth * .5, 0, 0);
		corner(.5,roomHeight);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-roomWidth * .5, 0, 0);
		corner(.5,roomHeight);
		glPopMatrix();
		glPushMatrix();
		glRotatef(90, 0, 0, 1);
		glTranslatef(roomHeight-.4, -roomWidth * .5, 0);
		cornerPost(.4,roomWidth);
		glPopMatrix();
		glPopMatrix();
		
		//side wall
		glPushMatrix();
		glTranslatef(-roomWidth * .5, 0, 0);
		wall(roomThickness-.2, roomLength-.2, roomHeight-.01, 5);
		wallBase(roomThickness, roomLength, roomHeight*.3, 5);
		glPushMatrix();
		glTranslatef(0, 0, roomLength * .5);
		corner(.5,roomHeight);
		glPopMatrix();
		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, -roomWidth*.5, -roomHeight+.4);
		cornerPost(.4,roomWidth);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glRotatef(45, 0, 1, 0);
		glScalef(1.1, 1, 1);
		glTranslatef(0, .01, -1);
		carpet(2,16);
		glPopMatrix();

		glPushMatrix();
		glScalef(0.8, 0.8, 0.8);
		glRotatef(45, 0, 1, 0);
		glTranslatef(0, 0, -4);
		bed();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-3.5, 0, 3.5);
		barrel(.75,2);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(2, 0, -4.25);
		shelf();
		glPopMatrix();
	}

	void drawAlphaTest(const Matrix4& viewMatrix)
	{
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, .5f);

		glPushMatrix();
		glRotatef(90,0,1,0);
		glTranslatef(-1, 0, -4);
		clock();
		glPopMatrix();

		glDisable(GL_ALPHA_TEST);
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

		glPopAttrib();
	}
};