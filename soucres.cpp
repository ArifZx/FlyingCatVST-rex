/*
* Create by Arif Budiman
*
*/
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

float frame = 500;
char solid_part = 1;

float xt = 0.0f, yt = 0.0f, zt = 0.0f, xr = 0.0f, yr = 0.0f, zr = 0.0f, xrm = 0.0f, yrm = 0.0f, zrm = 0.0f, xAngle = 0.0f, yAngle = 0.0f, zAngle = 0.0f;

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

void clamp360(float *data)
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

void display()
{
	float solid = solid_part;
	

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// set camera
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 12.0, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);

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

	glFlush();
	glutSwapBuffers();
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
		zr += 1;
		break;
	case GLUT_KEY_RIGHT:
		yr += 1;
		break;
	case GLUT_KEY_DOWN:
		zr -= 1;
		break;
	case GLUT_KEY_LEFT:
		yr -= 1;
		break;
	}

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
