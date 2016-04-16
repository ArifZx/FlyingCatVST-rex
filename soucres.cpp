#include<GL/glut.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

#define MAX_CAT_FOOT_ANGLE 30
#define MIN_CAT_FOOT_ANGLE -30

#define MAX_CAT_HEAD_ANGLE 20
#define MIN_CAT_HEAD_ANGLE -20

#define MAX_CAT_TAIL_ANGLE 45
#define MIN_CAT_TAIL_ANGLE -45

#define MAX_CAT_WING_ANGLE 45
#define MIN_CAT_WING_ANGLE -15

#define MAX_TREX_JAW_ANGLE 0
#define MIN_TREX_JAW_ANGLE -42

#define MAX_TREX_NECKLE_ANGLE 20
#define MIN_TREX_NECKLE_ANGLE -20

#define MAX_TREX_UPPER_LEG_ANGLE 60
#define MIN_TREX_UPPER_LEG_ANGLE -25

#define MAX_TREX_FOOT_ANGLE 30
#define MIN_TREX_FOOT_ANGLE -26

#define MAX_TREX_LOWER_LEG_ANGLE -30
#define MIN_TREX_LOWER_LEG_ANGLE -90

#define MAX_TREX_TAIL_Z_ANGLE 5
#define MIN_TREX_TAIL_Z_ANGLE -5

#define MAX_TREX_TAIL_Y_ANGLE 25
#define MIN_TREX_TAIL_Y_ANGLE -25

#define MAX_TREX_SHAKE 0.1
#define MIN_TREX_SHAKE 0.0

float frame = 250,
halfFrame = frame/2;
char solid_part = 1;

float xt = 0.0f, yt = 0.0f, zt = 0.0f, xr = 0.0f, yr = 0.0f, zr = 0.0f, xrm = 0.0f, yrm = 0.0f, zrm = 0.0f, xAngle = 0.0f, yAngle = 0.0f, zAngle = 0.0f;

// Cat attribute

float catTailAngle = 0.0f, 
catFootAngle = 0.0, 
catEarAngle = 0.0, 
catHeadAngle = 0.0f, 
catWingAngle = 0.0f;

float catFootRate = (MAX_CAT_FOOT_ANGLE - MIN_CAT_FOOT_ANGLE) / frame,
catHeadRate = (MAX_CAT_HEAD_ANGLE - MIN_CAT_HEAD_ANGLE) / (frame * 2),
catTailRate = (MAX_CAT_TAIL_ANGLE - MIN_CAT_TAIL_ANGLE) / (frame * 8),
catWingRate = (MAX_CAT_WING_ANGLE - MIN_CAT_WING_ANGLE) / (frame);

bool reverseCatMove = false;


// T-rex atribute

float	tRexLeftUpperLegAngle = 17, tRexRightUpperLegAngle = 17,
tRexLeftLowerLegAngle = -60, tRexRightLowerLegAngle = -60,
tRexRightFootAngle = -10, tRexLeftFootAngle = -10,
tRexChestAngle = 8, tRexNeckleAngle = 8, 
tRexUpperHandAngle = 8, tRexLowerHandAngle = 8,
tRexHeadAngleX = 0.0, tRexHeadAngleY = 0.0, tRexHeadAngleZ = -25.0,
tRexJawAngle = 0.0, tRexTailAngleZ = 0.0, tRexTailAnngleY = 0.0,
tRexShake = 0.05;

float	tRexJawRate = (MAX_TREX_JAW_ANGLE - MIN_TREX_JAW_ANGLE) / frame,
tRexNeckleRate = (MAX_TREX_NECKLE_ANGLE - MIN_TREX_NECKLE_ANGLE) / frame,
tRexUpperLegRate = 1.5 * (MAX_TREX_UPPER_LEG_ANGLE - MIN_TREX_UPPER_LEG_ANGLE) / frame,
tRexLowerLegRate = 1.5 * (MAX_TREX_LOWER_LEG_ANGLE - MIN_TREX_LOWER_LEG_ANGLE) / frame,
tRexFootRate = (MAX_TREX_FOOT_ANGLE - MIN_TREX_FOOT_ANGLE) / frame,
tRexTailYRate = (MAX_TREX_TAIL_Y_ANGLE - MIN_TREX_TAIL_Y_ANGLE) / (frame * 10),
tRexTailZRate = (MAX_TREX_TAIL_Z_ANGLE - MIN_TREX_TAIL_Z_ANGLE) / (frame * 10),
tRexShakeRate = (MAX_TREX_SHAKE - MIN_TREX_SHAKE) / (frame);

bool reverseAnimTrex = false,
animTrexLeftLeg = false,
animTrexreverseJaw = false,
animReverseTrexShake = false;

/* start of material definitions */
GLfloat mat_specular[] =
{ 0.628281, 0.555802, 0.366065, 1.0 };
GLfloat mat_ambient[] =
{ 0.24725, 0.1995, 0.0745, 1.0 };
GLfloat mat_diffuse[] =
{ 0.75164, 0.60648, 0.22648, 1.0 };
GLfloat mat_shininess[] =
{ 128.0 * 0.4 };

GLfloat mat_specular2[] =
{ 0.508273, 0.508273, 0.508373 };
GLfloat mat_ambient2[] =
{ 0.19225, 0.19225, 0.19225 };
GLfloat mat_diffuse2[] =
{ 0.50754, 0.50754, 0.50754 };
GLfloat mat_shininess2[] =
{ 128.0 * 0.6 };

GLfloat mat_specular3[] =
{ 0.296648, 0.296648, 0.296648 };
GLfloat mat_ambient3[] =
{ 0.25, 0.20725, 0.20725 };
GLfloat mat_diffuse3[] =
{ 1, 0.829, 0.829 };
GLfloat mat_shininess3[] =
{ 128.0 * 0.088 };

GLfloat mat_specular4[] =
{ 0.633, 0.727811, 0.633 };
GLfloat mat_ambient4[] =
{ 0.0215, 0.1745, 0.0215 };
GLfloat mat_diffuse4[] =
{ 0.07568, 0.61424, 0.07568 };
GLfloat mat_shininess4[] =
{ 128 * 0.6 };

GLfloat mat_specular5[] =
{ 0.60, 0.60, 0.50 };
GLfloat mat_ambient5[] =
{ 0.0, 0.0, 0.0 };
GLfloat mat_diffuse5[] =
{ 0.5, 0.5, 0.0 };
GLfloat mat_shininess5[] =
{ 128.0 * 0.25 };

/* end of material definitions */

void clampf360(float *data)
{
	if (*data >= 360.0f)
	{
		*data = *data - 360.0f;
	}
	else if (*data <= -360.0f)
	{
		*data = *data + 360.0f;
	}
}

void clampf(float *data, float *maxData, float *minData)
{
	if (*data <= *minData)
	{
		*data = *minData + 0.0f;
	}
	else if (*data >= *maxData)
	{
		*data = *maxData + 0.0f;
	}
}

void Normalize(float v[3])
{
	GLfloat d = sqrt(v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);

	if (d == 0.0) {
		printf("zero length vector");
		return;
	}
	v[1] /= d;
	v[2] /= d;
	v[3] /= d;
}

void NormXprod(float v1[3], float v2[3], float v[3], float out[3])
{
	GLint i, j;
	GLfloat length;

	out[0] = v1[1] * v2[2] - v1[2] * v2[1];
	out[1] = v1[2] * v2[0] - v1[0] * v2[2];
	out[2] = v1[0] * v2[1] - v1[1] * v2[0];
	Normalize(out);
}


void SetMaterial(GLfloat spec[], GLfloat amb[], GLfloat diff[], GLfloat shin[])
{
	glEnable(GL_COLOR_MATERIAL); /* WARNING: Ambient and diffuse material latch immediately to the current color. */
	glColorMaterial(GL_FRONT, GL_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT, GL_SHININESS, shin);
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
}

void Box(float width, float height, float depth, char solid)
{
	char i, j = 0;
	float x = width / 2.0, y = height / 2.0, z = depth / 2.0;

	for (i = 0; i < 4; i++) {
		glRotatef(90.0, 0.0, 0.0, 1.0);
		if (j) {
			if (!solid)
				glBegin(GL_LINE_LOOP);
			else
				glBegin(GL_QUADS);
			glNormal3f(-1.0, 0.0, 0.0);
			glVertex3f(-x, y, z);
			glVertex3f(-x, -y, z);
			glVertex3f(-x, -y, -z);
			glVertex3f(-x, y, -z);
			glEnd();
			if (solid) {
				glBegin(GL_TRIANGLES);
				glNormal3f(0.0, 0.0, 1.0);
				glVertex3f(0.0, 0.0, z);
				glVertex3f(-x, y, z);
				glVertex3f(-x, -y, z);
				glNormal3f(0.0, 0.0, -1.0);
				glVertex3f(0.0, 0.0, -z);
				glVertex3f(-x, -y, -z);
				glVertex3f(-x, y, -z);
				glEnd();
			}
			j = 0;
		}
		else {
			if (!solid)
				glBegin(GL_LINE_LOOP);
			else
				glBegin(GL_QUADS);
			glNormal3f(-1.0, 0.0, 0.0);
			glVertex3f(-y, x, z);
			glVertex3f(-y, -x, z);
			glVertex3f(-y, -x, -z);
			glVertex3f(-y, x, -z);
			glEnd();
			if (solid) {
				glBegin(GL_TRIANGLES);
				glNormal3f(0.0, 0.0, 1.0);
				glVertex3f(0.0, 0.0, z);
				glVertex3f(-y, x, z);
				glVertex3f(-y, -x, z);
				glNormal3f(0.0, 0.0, -1.0);
				glVertex3f(0.0, 0.0, -z);
				glVertex3f(-y, -x, -z);
				glVertex3f(-y, x, -z);
				glEnd();
			}
			j = 1;
		}
	}
}

void disable(void)
{
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_NORMALIZE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void lighting(GLfloat x, GLfloat y, GLfloat z)
{

	GLfloat position[] =
	{ x, y, z, 0.7 };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glDepthFunc(GL_LESS);
	glPolygonMode(GL_FRONT, GL_FILL);

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 80.0);

	glTranslatef(position[0], position[1], position[2]);
	glDisable(GL_LIGHTING);
	Box(0.1, 0.1, 0.1, 0);
	glEnable(GL_LIGHTING);
}

void drawCatFoot(char solid)
{
	float zTrans = -0.3, xTrans = -0.7, zScaleRot = -1;
	for (char i = 0; i < 4; i++)
	{
		zTrans = -zTrans;
		zScaleRot = -zScaleRot;
		if (i % 2 == 0)
		{
			xTrans = -xTrans;
		}
		glPushMatrix();
		glTranslatef(xTrans, 0.0, zTrans);
		glRotatef(catFootAngle, 0, 0, zScaleRot);
		glTranslatef(0.0, -0.3, 0.0);
		Box(0.3, 0.5, 0.25, solid);
		glPopMatrix();
	}
}

void drawCatWing(char solid, bool isLeft)
{
	Box(0.3, 0.3, 0.8, solid);
	
	if(isLeft)glTranslatef(-0.3, 0, 0.05);
	else glTranslatef(-0.3, 0, -0.05);

	Box(0.3, 0.3, 0.7, solid);
	
	if(isLeft) glTranslatef(-0.3, 0, 0.1);
	else glTranslatef(-0.3, 0, -0.1);
	
	Box(0.3, 0.3, 0.5, solid);
}

void drawCatWings(char solid)
{
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.35);
	glRotatef(catWingAngle, -1, 0, 0);
	glTranslatef(0.0, 0.0, 0.35);
	drawCatWing(solid, false);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.35);
	glRotatef(catWingAngle, 1, 0, 0);
	glTranslatef(0.0, 0.0, -0.35);
	drawCatWing(solid, true);
	glPopMatrix();
}

void drawCatTail(char solid)
{
	glRotatef(-45.0, 0.0, 0.0, 1.0);
	Box(1.0, 0.3, 0.25, solid);
}

void drawCatEar(char solid)
{
	Box(0.1, 0.3, 0.3, solid);
}

void drawCatEye(char solid)
{
	Box(0.1, 0.2, 0.2, solid);
}

void drawCatNose(char solid)
{
	Box(0.1, 0.1, 0.1, solid);
}

void drawCatHead(char solid)
{
	Box(0.8, 1.2, 1.2, solid);

	// earR
	glPushMatrix();
	glTranslatef(0.0, 0.7, 0.3);
	glRotatef(catEarAngle, 1.0, 0.0, 0.0);
	drawCatEar(solid);
	glPopMatrix();

	// earL
	glPushMatrix();
	glTranslatef(0.0, 0.7, -0.3);
	glRotatef(catEarAngle, 1.0, 0.0, 0.0);
	drawCatEar(solid);
	glPopMatrix();

	//eye r
	glPushMatrix();
	glTranslatef(0.4, 0.2, 0.2);
	glColor3f(0.0, 0.0, 0.0);
	drawCatEye(solid);
	glPopMatrix();

	//eye l
	glPushMatrix();
	glTranslatef(0.4, 0.2, -0.2);
	glColor3f(0.0, 0.0, 0.0);
	drawCatEye(solid);
	glPopMatrix();

	// nose
	glPushMatrix();
	glTranslatef(0.4, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	drawCatNose(solid);
	glPopMatrix();

}

void drawCat(char solid)
{
	glColor3f(1.0, 0.4, 0.0);
	SetMaterial(mat_specular, mat_ambient, mat_diffuse, mat_shininess);

	// base body
	Box(2.0, 1.0, 1.0, solid);

	glPushMatrix(); // cat foot
	glTranslatef(0.0, -0.4, 0.0);
	drawCatFoot(solid);
	glPopMatrix();

	glPushMatrix(); // cat tail
	glTranslatef(-0.9, 0.4, 0.0);
	glRotatef(catTailAngle, 0, 0, 1);
	glTranslatef(-0.3, 0.3, 0.0);
	drawCatTail(solid);
	glPopMatrix();

	glPushMatrix(); // cat head
	glTranslatef(1.4, 0.2, 0.0);
	glRotatef(catHeadAngle, 1.0, 0.0, 0.0);
	drawCatHead(solid);
	glPopMatrix();

	glPushMatrix(); // cat wing
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.4, 0.3, 0.0);
	drawCatWings(solid);
	glPopMatrix();
}

void drawTrexFoot(char solid)
{
	Box(0.8, 0.2, 0.5, solid);
}

void drawTrexLowerLeg(char solid)
{
	Box(0.4, 1.0, 0.5, solid);
}

void drawTrexUpperLeg(char solid)
{
	Box(1.2, 1.0, 0.5, solid);
	glTranslatef(-0.55, -0.5, 0.0);
	glRotatef(-30, 0.0f, 0.0f, 1.0f);
	Box(0.5, 0.65, 0.5, solid);
	glTranslatef(0.0, -0.1, 0.0);
}

void drawTrexLeg(char solid, bool isLeft)
{
	if (isLeft) 
		glRotatef(tRexLeftUpperLegAngle, 0.0f, 0.0f, 1.0f);
	else 
		glRotatef(tRexRightUpperLegAngle, 0.0f, 0.0f, 1.0f);
	
	drawTrexUpperLeg(solid);
	
	glPushMatrix();
	glRotatef(60, 0.0f, 0.0f, 1.0f);
	
	if(isLeft) 
		glRotatef(tRexLeftLowerLegAngle, 0.0f, 0.0f, 1.0f);
	else 
		glRotatef(tRexRightLowerLegAngle, 0.0f, 0.0f, 1.0f);
	
	glTranslatef(0.0, -0.4, 0.0);
	drawTrexLowerLeg(solid);

	glTranslatef(0.0, -0.4, 0.0);

	glPushMatrix();

	if (isLeft)
		glRotatef(tRexLeftFootAngle, 0.0f, 0.0f, 1.0f);
	else
		glRotatef(tRexRightFootAngle, 0.0f, 0.0f, 1.0f);

	glTranslatef(0.2f, 0.0f, 0.0f);
	drawTrexFoot(solid);

	glPopMatrix();

	glPopMatrix();
}

void drawTrexJaw(char solid)
{
	Box(1.25f, 0.5f, 1.0f, solid);
	glTranslatef(-0.7f, -0.5f, 0.0f);
	glRotatef(tRexJawAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.5f, 0.15f, 0.0f);
	Box(1.2f, 0.3f, 0.7f, solid);
}

void drawTrexHead(char solid)
{
	glRotatef(tRexHeadAngleX, 1, 0, 0);
	glRotatef(tRexHeadAngleY, 0, 1, 0);
	glRotatef(tRexHeadAngleZ, 0, 0, 1);
	glTranslatef(0.6, 0.0, 0.0);
	Box(1.4, 1.25, 1.25, solid);

	glPushMatrix();// jaw
	glTranslatef(1.3f, 0.0f, 0.0f);
	drawTrexJaw(solid);
	glPopMatrix();
}

void drawTrexNeckle(char solid)
{
	glTranslatef(0.7, 0.0, 0.0);
	Box(1.4, 1.2, 1.2, solid);
}

void drawTrexChest(char solid)
{
	glTranslatef(0.5, 0.0, 0.0);
	Box(1.4, 1.4, 1.4, solid);
}

void drawTrexHand(char solid)
{
	glRotatef(tRexUpperHandAngle, 0.0f, 0.0f, 1.0f);
	Box(0.3, 0.6, 0.3, solid);

	glPushMatrix();
	glTranslatef(0.1, -0.1, 0.0);
	glRotatef(tRexLowerHandAngle, 0, 0, 1);
	glTranslatef(0.0, -0.2, 0.0);
	Box(0.15, 0.3, 0.3, solid);
	glPopMatrix();
}

void drawTrexUpperBody(char solid)
{
	glRotatef(tRexChestAngle, 0, 0, 1.0);
	drawTrexChest(solid);

	glPushMatrix(); // left hand
	glTranslatef(0.1, -0.5, -0.7);
	drawTrexHand(solid);
	glPopMatrix();

	glPushMatrix(); // right hand
	glTranslatef(0.1, -0.5, 0.7);
	drawTrexHand(solid);
	glPopMatrix();

	glPushMatrix(); // neckle
	glTranslatef(0.5, 0.1, 0.0);
	glRotatef(tRexNeckleAngle, 0, 0, 1);
	drawTrexNeckle(solid);

	glPushMatrix(); // head
	glTranslatef(0.6, 0.0, 0.0);
	drawTrexHead(solid);
	glPopMatrix();

	glPopMatrix();

}

void drawTrexBackwardBody(char solid)
{
	float width = 1.5f, height = 1.5f, depth = 1.5f;
	for (unsigned char i = 0; i < 5; i++)
	{
		glPushMatrix();
		if (i < 3)
		{
			width += 0.1;
		}
		else
		{
			width += 0.25;
			height -= 0.05;
		}
		height -= 0.2;
		depth -= 0.2;
		glRotatef(tRexTailAngleZ, 0, 0, 1);
		glRotatef(tRexTailAnngleY, 0, 1, 0);
		glTranslatef(-width / 2, 0.0, 0.0);
		Box(width, height, depth, solid);
	}
	glTranslatef(width / 2, 0.0, 0.0);
	for (unsigned char i = 0; i < 5; i++)
	{
		glPopMatrix();
	}
}

void drawTrex(char solid)
{
	glTranslatef(0.0, tRexShake, 0.0);

	SetMaterial(mat_specular4, mat_ambient4, mat_diffuse4, mat_shininess4);
	glColor3f(0.65, 0.3, 0.16);

	glRotatef(15, 0, 0, 1);
	Box(2.0, 1.5, 1.5, solid);

	glPushMatrix();
	glTranslatef(-0.3, -0.7, -0.9);
	drawTrexLeg(solid, true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, -0.7, 0.9);
	drawTrexLeg(solid, false);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.7, 0.0, 0.0);
	glRotatef(tRexChestAngle, 0, 0, 1.0);
	drawTrexUpperBody(solid);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 0.0, 0.0);
	drawTrexBackwardBody(solid);
	glPopMatrix();

}

void display()
{
	float solid = solid_part;
	

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// set camera
	glLoadIdentity();
	gluLookAt(xr, yr, 10.0, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);

	if (solid) {
		glPushMatrix();
		lighting(0.0, 3.5, 3.5);
		glPopMatrix();
	}
	else
		disable();

	glPushMatrix();
	glTranslatef(-5.0, 0.0, 0.0);
	glRotatef(0.0, 0.0, 1.0, 0.0);
	glRotatef(0.0, 1.0, 0.0, 0.0);
	glRotatef(0.0, 0.0, 0.0, 1.0);
	drawCat(solid);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0f, 0.0f, 0.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	drawTrex(solid);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void tRexTailAnimation()
{
	if (reverseAnimTrex)
	{
		tRexTailAnngleY += tRexTailYRate;
	}
	else
	{
		tRexTailAnngleY += tRexTailYRate;
	}
}

void tRexBiteAnimation()
{
	if (animTrexreverseJaw)
	{
		tRexJawAngle += tRexJawRate;
	}
	else
	{
		tRexJawAngle -= tRexJawRate;
	}

}

void tRexWalkAnimation()
{
	if (reverseAnimTrex)
	{
		tRexLeftUpperLegAngle += tRexUpperLegRate;
		tRexRightUpperLegAngle -= tRexUpperLegRate;
		tRexRightLowerLegAngle -= tRexLowerLegRate;
		tRexLeftLowerLegAngle += tRexLowerLegRate;
	}
	else
	{
		tRexLeftUpperLegAngle -= tRexUpperLegRate;
		tRexRightUpperLegAngle += tRexUpperLegRate;
		tRexRightLowerLegAngle += tRexLowerLegRate;
		tRexLeftLowerLegAngle -= tRexLowerLegRate;
	}

	if (animReverseTrexShake)
	{
		tRexShake += (2 * tRexShakeRate);
	}
	else
	{
		tRexShake -= (2 * tRexShakeRate);
	}

}

void updateStatusTrex()
{
	if (tRexJawAngle >= MAX_TREX_JAW_ANGLE)
	{
		animTrexreverseJaw = false;
	}
	else if (tRexJawAngle <= MIN_TREX_JAW_ANGLE)
	{
		animTrexreverseJaw = true;
	}

	if (tRexShake >= MAX_TREX_SHAKE)
	{
		animReverseTrexShake = false;
	}
	else if (tRexShake <= MIN_TREX_SHAKE)
	{
		animReverseTrexShake = true;
	}

	if (tRexLeftUpperLegAngle >= MAX_TREX_UPPER_LEG_ANGLE)
	{
		reverseAnimTrex = false;
	}
	else if (tRexLeftUpperLegAngle <= MIN_TREX_UPPER_LEG_ANGLE)
	{
		reverseAnimTrex = true;
	}

}

void tRexAnimation()
{
	tRexBiteAnimation();
	tRexWalkAnimation();
	
	updateStatusTrex();
}

void catAnimation()
{
	if (!reverseCatMove)
	{
		catFootAngle += catFootRate;
		catHeadAngle += catHeadRate;
		catTailAngle -= catTailRate;
		catWingAngle -= catWingRate;
	}
	else
	{
		catFootAngle -= catFootRate;
		catHeadAngle -= catHeadRate;
		catTailAngle += catTailRate;
		catWingAngle += catWingRate;
	}
	
	if (catFootAngle >= MAX_CAT_FOOT_ANGLE)
	{
		reverseCatMove = true;
	}
	else if (catFootAngle <= MIN_CAT_FOOT_ANGLE)
	{
		reverseCatMove = false;
	}

}

void animation()
{
	catAnimation();
	tRexAnimation();

	glutPostRedisplay();
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 1.2, -5.5);  /* viewing transform  */
}

void mySpecialKey(int key, int k, int l)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		yt += 0.1;
		break;
	case GLUT_KEY_RIGHT:
		xt += 0.1;
		break;
	case GLUT_KEY_DOWN:
		yt -= 0.1;
		break;
	case GLUT_KEY_LEFT:
		xt -= 0.1;
		break;
	}

	cout << xt << "\n";

	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	/* start of glut windowing and control functions */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("glutmech: Vulcan Gunner");
	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	glutSpecialFunc(mySpecialKey);
	glutIdleFunc(animation);

	glutMainLoop();

	return 0;

}
