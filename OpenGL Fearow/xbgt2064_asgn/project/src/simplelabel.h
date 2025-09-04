#pragma once
#include <string>
#include "mini/ini.h"
#include "framework/texture/texture_utils.h"

// This class implementation assumes that:
// 1. Font is MONOSPACE
// 2. Glyphs in texture atlas follows layout of:
//    -> ASCII indices only
//    -> Glyphs are ordered from char index 32~126
//    -> Glyph starts from bottom left

class SimpleLabel
{
private:

	Texture2D* fontTexture;	// Texture handle for font atlas loaded in ctor

	// Font settings set by ctor and used in makeGlyphQuad
	unsigned int charWidth;
	unsigned int charHeight;
	unsigned int charsPerRow;
	float unitWidth;

	void makeGlyphQuad(char c)
	{
		if (c < 32 || c > 126) c = 63; // 63 is '?'

		int i = c - 32;
		int row = floor(i / charsPerRow);
		int col = i % charsPerRow;

		glBegin(GL_TRIANGLE_STRIP);

		float imgSize = 512.0f;

		float u0 = col * (charWidth / imgSize);
		float u1 = (col + 1) * (charWidth / imgSize);
		float v0 = row * (charHeight / imgSize);
		float v1 = (row + 1) * (charHeight / imgSize);

		glTexCoord2f(u0, v1); glVertex2f(0, 1);
		glTexCoord2f(u0, v0); glVertex2f(0, 0);
		glTexCoord2f(u1, v1); glVertex2f(unitWidth, 1);
		glTexCoord2f(u1, v0); glVertex2f(unitWidth, 0);

		glEnd();
	}

public:

	SimpleLabel(std::string fontPath)
	{
		// Using a third-party library to load .ini style text document
		mINI::INIFile file(fontPath);
		mINI::INIStructure ini;
		file.read(ini);

		if (!ini.has("font"))
		{
			std::cout << "Error loading \"" << fontPath << "\"" << std::endl;
			return;
		}

		charWidth = std::stoi(ini["font"]["w"]);
		charHeight = std::stoi(ini["font"]["h"]);
		charsPerRow = std::stoi(ini["font"]["cpr"]);

		// We assume character height is 1.0
		// Label resizing is by applying scaling before calling render(...)
		// Calculate unitWidth = charWidth/charHeight
		//		Remember about integer division!

		unitWidth = float(charWidth) / charHeight;

		std::string imagePath = ini["font"]["image"];

		static TextureConfig cfg(TextureWrapMode::CLAMP, TextureWrapMode::CLAMP, TextureFilterMode::LINEAR, true);
		
		fontTexture = TextureUtils::loadFromFile("../assets/FontShareTechMono.png", cfg);
	};

	void render(std::string str)
	{
		int lineCount = 0;

		glBindTexture(GL_TEXTURE_2D, fontTexture->getNativeHandle());
		glPushMatrix();

		for (int i = 0; i < str.length(); i++)
		{
			char c = str[i];

			if (c == '\n')
			{
				lineCount++;
				glPopMatrix();
				glPushMatrix();
				glTranslatef(0, -lineCount, 0);
			}
			else
			{
				makeGlyphQuad(c);
				glTranslatef(unitWidth, 0, 0);
			}
		}

		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);
	};
};