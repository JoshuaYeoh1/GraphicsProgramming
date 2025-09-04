#include "scenebase.h"
#include <glad/glad.h>

static float lw;

void SceneBase::drawWorldOriginLines()
{
	glGetFloatv(GL_LINE_WIDTH, &lw);
	glLineWidth(1.0f);

	glBegin(GL_LINES);

	glColor3f(1.0f, 0.3f, 0.3f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	glColor3f(0.3f, 1.0f, 0.3f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.3f, 0.3f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();

	glLineWidth(lw);
	glColor3f(1.0f, 1.0f, 1.0f);
}

void SceneBase::drawHorizontalGridLines() {
	glGetFloatv(GL_LINE_WIDTH, &lw);
	glLineWidth(1.0f);

	glDepthFunc(GL_LESS);

	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_LINES);
	for (int i = -5; i <= 5; i++) {
		float f = (float)i;
		glVertex3f(f, 0.0f, -5.0f);
		glVertex3f(f, 0.0f, 5.0f);
		glVertex3f(-5.0f, 0.0f, f);
		glVertex3f(5.0f, 0.0f, f);
	}
	glEnd();

	glDepthFunc(GL_LEQUAL);
	glLineWidth(lw);
	glColor3f(1.0f, 1.0f, 1.0f);
}

void SceneBase::drawVerticalGridLines() {
	glGetFloatv(GL_LINE_WIDTH, &lw);
	glLineWidth(1.0f);

	glDepthFunc(GL_LESS);

	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_LINES);
	for (int i = -5; i <= 5; i++) {
		float f = (float)i;
		glVertex3f(f, -5.0f, 0.0f);
		glVertex3f(f, 5.0f, 0.0f);
		glVertex3f(-5.0f, f, 0.0f);
		glVertex3f(5.0f, f, 0.0f);
	}
	glEnd();

	glDepthFunc(GL_LEQUAL);
	glLineWidth(lw);
	glColor3f(1.0f, 1.0f, 1.0f);
}