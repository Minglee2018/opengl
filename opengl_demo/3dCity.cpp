#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <iostream>
using namespace std;

float cc[20][2];

void init(void);
void display(void);
void keyboard(unsigned char, int, int);
void resize(int, int);
void draw_star(float, float);
void house(float, float, float);
void apart(float, float, float);
void circle1(float);
void stand(float, float, float);
float  h = 5, h1 = 6, d1 = 4, g = 1, g1 = 2;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1100, 1100);
	glutInitWindowPosition(100, 10);
	glutCreateWindow("3D map");
	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutReshapeFunc(resize);

	glutMainLoop();
	return 0;
}

void apart(float x, float y, float z)
{
	int i;
	int j;
	glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_POLYGON);
	glVertex3f( GLfloat(x), GLfloat(y), GLfloat(z + 0.5));
	glVertex3f(GLfloat(x + 45), GLfloat(y), GLfloat(z + 0.5));
	glVertex3f(GLfloat(x + 45), GLfloat(y + 100), GLfloat(z + 0.5));
	glVertex3f(GLfloat(x), GLfloat(y + 100), GLfloat(z + 0.5));
	glEnd();  glColor3f(0.8f, 0.8f, 0.8f);
	for (j = 0; j < 8; j++)
	{

		glPushMatrix();
		glTranslatef(0, float(-12 * j), 0);
		for (i = 0; i < 4; i++)
		{
			glPushMatrix();
			glTranslatef(float(11 * i), 0, 0);
			glBegin(GL_POLYGON);
			glVertex3f(float(x + 2), float(y + 98), float(z));
			glVertex3f(float(x + 10), float(y + 98), float(z));
			glVertex3f(float(x + 10), float(y + 88), float(z));
			glVertex3f(float(x + 2), float(y + 88), float(z));
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}glColor3f(0, 0, 0);
	for (j = 0; j < 8; j++)
	{

		glPushMatrix();
		glTranslatef(0, float(-12 * j), 0);
		for (i = 0; i < 4; i++)
		{
			glPushMatrix();
			glTranslatef(float(11 * i), 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex3f(float(x + 2), float(y + 98), float(z));
			glVertex3f(float(x + 10), float(y + 98), float(z));
			glVertex3f(float(x + 10), float(y + 88), float(z));
			glVertex3f(float(x + 2), float(y + 88), float(z));
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}

	glColor3f(0.6f, 0.6f, 0.6f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x),		float(y), float(z + 45 - 0.5));
	glVertex3f(float(x + 45),	float(y), float(z + 45 - 0.5));
	glVertex3f(float(x + 45),	float(y + 100), float(z + 45 - 0.5));
	glVertex3f(float(x),		float(y + 100), float(z + 45 - 0.5));
	glEnd();  	glColor3f(0.8f, 0.8f, 0.8f);

	for (j = 0; j < 8; j++)
	{

		glPushMatrix();
		glTranslatef(0, float(-12 * j), 0);
		for (i = 0; i < 4; i++)
		{
			glPushMatrix();
			glTranslatef(float(11 * i), 0, 0);
			glBegin(GL_POLYGON);
			glVertex3f(float(x + 2), float(y + 98), float(z + 45));
			glVertex3f(float(x + 10), float(y + 98), float(z + 45));
			glVertex3f(float(x + 10), float(y + 88), float(z + 45));
			glVertex3f(float(x + 2), float(y + 88), float(z + 45));
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}glColor3f(0, 0, 0);

	for (j = 0; j < 8; j++)
	{

		glPushMatrix();
		glTranslatef(0, float(-12 * j), 0);
		for (i = 0; i < 4; i++)
		{
			glPushMatrix();
			glTranslatef(float(11 * i), 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex3f(float(x + 2), float(y + 98), float(z + 45));
			glVertex3f(float(x + 10), float(y + 98), float(z + 45));
			glVertex3f(float(x + 10), float(y + 88), float(z + 45));
			glVertex3f(float(x + 2), float(y + 88), float(z + 45));
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}

	glColor3f(0.6f, 0.6f, 0.6f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x + 0.5), float(y), float(z));
	glVertex3f(float(x + 0.5), float(y), float(z + 45));
	glVertex3f(float(x + 0.5), float(y + 100), float(z + 45));
	glVertex3f(float(x + 0.5), float(y + 100), float(z));
	glEnd();
	glColor3f(0.8f, 0.8f, 0.8f);
	for (j = 0; j < 8; j++)
	{

		glPushMatrix();
		glTranslatef(0, float(-12 * j), 0);
		for (i = 0; i < 4; i++)
		{
			glPushMatrix();
			glTranslatef(0, 0, float(11 * i));
			glBegin(GL_POLYGON);
			glVertex3f(float(x), float(y + 98), float(z + 2));
			glVertex3f(float(x), float(y + 98), float(z + 10));
			glVertex3f(float(x), float(y + 88), float(z + 10));
			glVertex3f(float(x), float(y + 88), float(z + 2));
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}glColor3f(0, 0, 0);
	for (j = 0; j < 8; j++)
	{

		glPushMatrix();
		glTranslatef(0, float(-12 * j), 0);
		for (i = 0; i < 4; i++)
		{
			glPushMatrix();
			glTranslatef(0, 0, float(11 * i));
			glBegin(GL_LINE_LOOP);
			glVertex3f(float(x), float(y + 98), float(z + 2));
			glVertex3f(float(x), float(y + 98), float(z + 10));
			glVertex3f(float(x), float(y + 88), float(z + 10));
			glVertex3f(float(x), float(y + 88), float(z + 2));
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}

	glColor3f(0.6f, 0.6f, 0.6f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x + 45 - 0.5), float(y), float(z - 0.5));
	glVertex3f(float(x + 45 - 0.5), float(y), float(z + 45 - 0.5));
	glVertex3f(float(x + 45 - 0.5), float(y + 100), float(z + 45 - 0.5));
	glVertex3f(float(x + 45 - 0.5), float(y + 100), float(z  - 0.5));
	glEnd(); glColor3f(0.8f, 0.8f, 0.8f);
	for (j = 0; j < 8; j++)
	{

		glPushMatrix();
		glTranslatef(0, float(-12 * j), 0);
		for (i = 0; i < 4; i++)
		{
			glPushMatrix();
			glTranslatef(0, 0, float(11 * i));
			glBegin(GL_POLYGON);
			glVertex3f(float(x + 45), float(y + 98), float(z + 2));
			glVertex3f(float(x + 45), float(y + 98), float(z + 10));
			glVertex3f(float(x + 45), float(y + 88), float(z + 10));
			glVertex3f(float(x + 45), float(y + 88), float(z + 2));
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}
	glColor3f(0, 0, 0);
	for (j = 0; j < 8; j++)
	{

		glPushMatrix();
		glTranslatef(0, float(-12 * j), 0);
		for (i = 0; i < 4; i++)
		{
			glPushMatrix();
			glTranslatef(0, 0, float(11 * i));
			glBegin(GL_LINE_LOOP);
			glVertex3f(float(x + 45), float(y + 98), float(z + 2));
			glVertex3f(float(x + 45), float(y + 98), float(z + 10));
			glVertex3f(float(x + 45), float(y + 88), float(z + 10));
			glVertex3f(float(x + 45), float(y + 88), float(z + 2));
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}

	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x), float(y), float(z- 0.5));
	glVertex3f(float(x + 45), float(y), float(z - 0.5));
	glVertex3f(float(x + 45), float(y), float(z + 45 - 0.5));
	glVertex3f(float(x), float(y), float(z + 45 - 0.5));
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(float(x), float(y + 100), float(z));
	glVertex3f(float(x + 45), float(y + 100), float(z));
	glVertex3f(float(x), float(y + 100), float(z + 45));
	glVertex3f(float(x), float(y + 100), float(z + 45));
	glEnd();
}


void house(float x, float y, float z)
{
	glColor3f(0.01f, 0.05f, 0.3f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x), float(y), float(z));
	glVertex3f(float(x), float(y), float(z + 30));
	glVertex3f(float(x), float(y + 15), float(z + 30));
	glVertex3f(float(x), float(y +15), float(z));
	glEnd();

	glColor3f(0.01f, 0.05f, 0.3f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x - 15), float(y), float(z));
	glVertex3f(float(x - 15), float(y + 15), float(z));
	glVertex3f(float(x - 15), float(y + 15), float(z + 30));
	glVertex3f(float(x - 15), float(y), float(z + 30));
	glEnd();

	glColor3f(0.01f, 0.05f, 0.3f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x), float(y), float(z+30));
	glVertex3f(float(x - 15), float(y), float(z + 30));
	glVertex3f(float(x - 15), float(y + 15), float(z + 30));
	glVertex3f(float(x), float(y + 15), float(z + 30));
	glEnd();

	glColor3f(0.01f, 0.05f, 0.3f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x - 15), float(y), float(z));
	glVertex3f(float(x - 15), float(y + 15), float(z));
	glVertex3f(float(x), float(y + 15), float(z));
	glVertex3f(float(x), float(y), float(z));
	glEnd();


	glColor3f(0.01f, 0.05f, 1.5f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x - 15), float(y), float(z));
	glVertex3f(float(x), float(y), float(z));
	glVertex3f(float(x), float(y), float(z + 30));
	glVertex3f(float(x - 15), float(y), float(z + 30));
	glEnd();
	
	glColor3f(0.51f, 0.015f, 0.008f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x + 1.69 * 3), float(y + 3.5 * 3), float(z));
	glVertex3f(float(x - 2.5 * 3), float(y + 7.5 * 3), float(z));
	glVertex3f(float(x - 2.5 * 3), float(y + 7.5 * 3), float(z + 30));
	glVertex3f(float(x + 1.69 * 3), float(y + 3.5 * 3), float(z + 30));	
	glEnd();

	glColor3f(0.51f, 0.015f, 0.008f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x - 6.69 * 3), float(y + 3.5 * 3), float(z));
	glVertex3f(float(x - 6.69 * 3), float(y + 3.5 * 3), float(z + 30));
	glVertex3f(float(x - 2.5 * 3), float(y + 7.5 * 3), float(z + 30));
	glVertex3f(float(x - 2.5 * 3), float(y + 7.5 * 3), float(z));
	glEnd();


	glColor3f(0.1f, 0.015f, 0.13f);
	glBegin(GL_POLYGON);
	glVertex3f(x, y + 15, z);
	glVertex3f(float(x), float(y+15), float(z));
	glVertex3f(float(x - 15), float(y + 5), float(z));
	glVertex3f(float(x - 2.5 * 3), float(y + 7.5 * 3), float(z));
	glEnd();

	glColor3f(0.1f, 0.015f, 0.13f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x), float(y + 15), float(z + 30));
	glVertex3f(float(x - 15), float(y + 15), float(z + 30));
	glVertex3f(float(x - 2.5 * 3), float(y + 7.5 * 3), float(z + 30));
	glEnd();
}


void house1()
{

	house(120, 0.1f, 50);

	house(120, 0.1f, 90);

	house(160, 0.1f, 90);

	house(80, 0.1f, 90);

	house(160, 0.1f, 50);

	house(80, 0.1f, 50);

	house(-130, 0.1f, 120);

	house(-130, 0.1f, 160);

	house(-90, 0.1f, 120);

	house(-60, 0.1f, 120);

	house(-90, 0.1f, 160);

	stand(-10, 6, 130);
	stand(30, 6, 130);

	house(-60, 0.1f, 160);
	apart(150, 0, -150);
	apart(80, 0, -90);

	apart(150, 0, -90);
	apart(150, 0, -30);

	apart(-150, 0, -30);
	apart(-150, 0, -110);

	apart(-150, 0, -180);

}
void circle1(float c[20][2])
{
	float x = 0, y = 03;
	int i;
	for (i = 0; i < 20; i++) {
		c[i][0] = float(x *  float(cos((i + 1) * 36 * (3.142f / 360))) -  y * float(sin((i + 1) * 36 * (3.142f / 360)))  );
		c[i][1] = float(x *  float(sin((i + 1) * 36 * (3.142f / 360)))  + y * float(cos((i + 1) * 36 * (3.142f / 360))) );
	}

	for (i = 0; i < 19; i++)
	{
		glBegin(GL_POLYGON);
		glVertex3f(float(c[i][0]), float(c[i][1]), 0);
		glVertex3f(float(c[i][0]), float(c[i][1]), 40);
		glVertex3f(float(c[i + 1][0]), float(c[i + 1][1]), 40);
		glVertex3f(float(c[i + 1][0]), float(c[i + 1][1]), 0);
		glEnd();
	}

	glBegin(GL_POLYGON);
	glVertex3f(c[0][0], c[0][1], 0);
	glVertex3f(c[0][0], c[0][1], 40);
	glVertex3f(c[19][0], c[19][1], 40);
	glVertex3f(c[19][0], c[19][1], 0);
	glEnd();

}


void init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
}

void draw_star(float x, float y)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex2f(float(x) , float(y));
	glVertex2f(float(x + 1.5), float(y - 4));
	glVertex2f(float(x + 6.5), float(y - 5.5));
	glVertex2f(float(x + 2.5), float(y - 9));
	glVertex2f(float(x + 4.5), float(y - 14));
	glVertex2f(float(x), float(y - 11.5));
	glVertex2f(float(x - 4.5), float(y - 14));
	glVertex2f(float(x - 3), float(y - 9));
	glVertex2f(float(x - 6.5), float(y - 5.5));
	glVertex2f(float(x - 1.5), float(y - 5));
	glVertex2f(float(x), float(y));
	glEnd();
}


void stand(float x, float y, float z)
{
	glColor3f(1, 0.8f, 0);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x, y - h1, z + d1);
	glVertex3f(x + h, y - h1, z + d1);
	glVertex3f(x + h, y, z);
	glEnd();
	glColor3f(1, 0.5, 0);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x + h, y, z);
	glVertex3f(x + h, y - h1, z - d1);
	glVertex3f(x, y - h1, z - d1);
	glEnd();

	glColor3f(0.6f, 0.12f, 0.4f);

	glBegin(GL_POLYGON);
	glVertex3f(x, y - h1, z + d1);
	glVertex3f(x, y - h1 - 2, z + d1);
	glVertex3f(x + 1, y - h1 - 2, z + d1);
	glVertex3f(x + 1, y - h1, z + d1);
	glEnd();

	glColor3f(0.6f, 0.12f, 0.4f);
	glBegin(GL_POLYGON);
	glVertex3f(x + h, y - h1, z + d1);
	glVertex3f(x + h, y - h1 - 2, z + d1);
	glVertex3f(x + h - 1, y - h1 - 2, z + d1);
	glVertex3f(x + h - 1, y - h1, z + d1);
	glEnd();

	glColor3f(0.6f, 0.12f, 0.4f);

	glBegin(GL_POLYGON);
	glVertex3f(x, y - h1, z - d1);
	glVertex3f(x, y - h1 - 2, z - d1);
	glVertex3f(x + 1, y - h1 - 2, z - d1);
	glVertex3f(x + 1, y - h1, z - d1);
	glEnd();

	glColor3f(0.6f, 0.12f, 0.4f);

	glBegin(GL_POLYGON);
	glVertex3f(x + h, y - h1, z - d1);
	glVertex3f(x + h, y - h1 - 2, z - d1);
	glVertex3f(x + h - 1, y - h1 - 2, z - d1);
	glVertex3f(x + h - 1, y - h1, z - d1);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* draw the floor */
	glBegin(GL_QUADS);
	glColor3f(0.8f, 0.6f, 0.4f);
	glVertex3f(-200.0f, 0.0f, -200.0f);
	glColor3f(0.8f, 0.6f, 0.4f);
	glVertex3f(-200.0f, 0.0f, 200.0f);
	glColor3f(0.8f, 0.6f, 0.4f);
	glVertex3f(200.0f, 0.0f, 200.0f);
	glColor3f(0.8f, 0.6f, 0.4f);
	glVertex3f(200.0f, 0.0f, -200.0f);
	glEnd();
	glFlush();

	draw_star(20, 240);
	draw_star(180, 220);
	draw_star(-30, 280);
	draw_star(190, 280);
	draw_star(100, 220);
	draw_star(-230, 250);
	draw_star(-190, 210);
	draw_star(-88, 260);
	draw_star(88, 270);
	draw_star(-170, 280);


	glColor3f(0.3f, 0.015f, 0.13f);
	glPushMatrix();
	glTranslatef(-15, 1, 50);
	glutSolidCube(7);
	glPopMatrix();

	glColor3f(0.3f, 0.015f, 0.13f);
	glPushMatrix();
	glTranslatef(-15, 1, -40);
	glutSolidCube(7);
	glPopMatrix();

	glColor3f(0.3f, 0.015f, 0.13f);
	glPushMatrix();
	glTranslatef(-15, 1, 20);
	glutSolidCube(7);
	glPopMatrix();

	glColor3f(0.3f, 0.015f, 0.13f);
	glPushMatrix();
	glTranslatef(-15, 1, -10);
	glutSolidCube(7);
	glPopMatrix();

	glColor3f(0.3f, 0.015f, 0.13f);
	glPushMatrix();
	glTranslatef(-15, 1, -80);
	glutSolidCube(7);
	glPopMatrix();

	glColor3f(0.3f, 0.015f, 0.13f);
	glPushMatrix();
	glTranslatef(-15, 1, -120);
	glutSolidCube(7);
	glPopMatrix();

	glColor3f(0.3f, 0.015f, 0.13f);
	glPushMatrix();
	glTranslatef(-15, 1, -160);
	glutSolidCube(7);
	glPopMatrix();




	glColor3f(0.015f, 0.3f, 0.13f);
	glPushMatrix();
	glTranslatef(-15, 24, 50);
	glScalef(1.1f, 2.3f, 0.8f);
	glutSolidSphere(10, 15, 6);
	glFlush();
	glPopMatrix();

	glColor3f(0.015f, 0.3f, 0.13f);
	glPushMatrix();
	glTranslatef(-15, 24, -40);
	glScalef(1.1f, 2.3f, 0.8f);
	glutSolidSphere(10, 15, 4);
	glFlush();
	glPopMatrix();

	glColor3f(0.015f, 0.3f, 0.13f);
	glPushMatrix();
	glTranslatef(-15, 24, 20);
	glScalef(1.1f, 2.3f, 0.8f);
	glutSolidSphere(10, 15, 4);
	glFlush();
	glPopMatrix();

	glColor3f(0.015f, 0.3f, 0.13f);
	glPushMatrix();
	glTranslatef(-15, 24, -10);
	glScalef(1.1f, 2.3f, 0.8f);
	glutSolidSphere(10, 15, 4);
	glFlush();
	glPopMatrix();

	glColor3f(0.015f, 0.3f, 0.13f);
	glPushMatrix();
	glTranslatef(-15, 24, -80);
	glScalef(1.1f, 2.3f, 0.8f);
	glutSolidSphere(10, 15, 4);
	glFlush();
	glPopMatrix();

	glColor3f(0.015f, 0.3f, 0.13f);
	glPushMatrix();
	glTranslatef(-15, 24, -120);
	glScalef(1.1f, 2.3f, 0.8f);
	glutSolidSphere(10, 15, 4);
	glFlush();
	glPopMatrix();

	glColor3f(0.015f, 0.3f, 0.13f);
	glPushMatrix();
	glTranslatef(-15, 24, -160);
	glScalef(1.1f, 2.3f, 0.8f);
	glutSolidSphere(10, 15, 4);
	glFlush();
	glPopMatrix();


	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(0.0f, 0.01f, -200); /* road */
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(0.0f, 0.01f, 200);
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(18, 0.01f, 200);
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(18, 0.01f, -200);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(8.5f, 0.02f, -200.0f); /* road */
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(8.5f, 0.02f, 200.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(9.5f, 0.02f, 200.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(9.5f, 0.02f, -200.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(44.0f, 0.01f, -200.0f); /* road */
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(44.0f, 0.01f, 160.0f);
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(54.0f, 0.01f, 160.0f);
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(54.0f, 0.01f, -200.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(54.0f, 0.01f, -180.0f); /* road */
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(54.0f, 0.01f, -160.0f);
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(200.0f, 0.01f, -160.0f);
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(200.0f, 0.01f, -180.0f);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(18.0f, 0.01f, 160.0f); /* road */
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(18, 0.01f, 170);
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(200, 0.01f, 170);
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(200, 0.01f, 160);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(-200, 0.01f, 90); /* road */
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(-200, 0.01f, 100);
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(0, 0.01f, 100);
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(0, 0.01f, 90);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(-90, 0.01f, -200); /* road */
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(-90, 0.01f, 90);
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(-80, 0.01f, 90);
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(-80, 0.01f, -200);
	glEnd();
	house1();
	glFlush();
	glutSwapBuffers();


}


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
	case 'A':
		glTranslatef(5.0, 0.0, 0.0);
		break;
	case 'd':
	case 'D':
		glTranslatef(-5.0, 0.0, 0.0);
		break;
	case 'w':
	case 'W':
		glTranslatef(0.0, 0.0, 5.0);
		break;
	case 's':
	case 'S':
		glTranslatef(0.0, 0.0, -5.0);
		break;
	case 'q':
	case 'Q':
		glRotatef(-2, 1.0, 0.0, 0.0);

	case 'e':
	case 'E':
		glRotatef(2, 0.0, 1.0, 0.0);

	}
	display();
}

void resize(int width, int height)
{
	if (height == 0) height = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(80.0, width / height, 1.0, 600.0);

	glTranslatef(0.0, -15.0, -320.0);

	glMatrixMode(GL_MODELVIEW);
}

