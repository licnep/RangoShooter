#include "menu.h"

void DrawMenu(int x, int y, GLuint textureID, bool blendFlag)
{
	int width = 1024, height = 1024;

	//matrici a caso:
	glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1024, 1024, 0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_COLOR_MATERIAL);
    glPushMatrix();
    glLoadIdentity();

	glColor3f(1.0f, 1.0f, 1.0f);

	//Enable 2D
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	if (blendFlag)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	//Begin Drawing Quads
	glBegin(GL_QUADS);

	// Top-left vertex (corner)
	glTexCoord2i(0, 0);
	glVertex2i(x, y);

	// Bottom-left vertex (corner)
	glTexCoord2i(1, 0);
	glVertex2i( x + width, y);

	// Bottom-right vertex (corner)
	glTexCoord2i(1, 1);
	glVertex2i( x + width, y + height);

	// Top-right vertex (corner)
	glTexCoord2i(0, 1);
	glVertex2i(x, y + height);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);


	glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

