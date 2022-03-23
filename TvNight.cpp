/*********
 CTIS164 - Project
----------
STUDENT : Ahmet Burak Yuksel
SECTION : 3
----------
PROBLEMS:
----------
ADDITIONAL FEATURES:
1) Rather than using tv button, I designed remote control for tv.
2) Remote control has power, channel+, channel-, volume+, volume-, play, and stop buttons.
3) There are two channels. (News and Movie channel)
4) Volume button works when one of the volume buttons is clicked, shows the current level of volume, and disappears.
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 600

#define TIMER_PERIOD  15 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

//tv modes
#define OFF 0
#define RUN1 1
#define RUN2 2
#define PAUSE1 3
#define PAUSE2 4

int timer = 1;
int tempX;
int tempY;
int mode = OFF;
bool inCloseButton = false;
bool inPauseButton = false;
bool inPlayButton = false;
bool inChanelPlusButton = false;
bool inChanelMinusButton = false;
bool inVolumePlusButton = false;
bool inVolumeMinusButton = false;
int volumeX = -500;
int volumeY = 0;
int volume = 50;

//positions of first channel elements
int redcellX[10] = { -800,-500,-1100,-710,-550,-850,-1190,-930,-1300,-650 };
int redcellY[10] = { 145,100,130,80,20,-30,-50,-80,-100,-90 };

int sVirusX[10] = { -800,-500,-1100,-710,-550,-850,-1190,-930,-1300,-650 };
int sVirusY[10] = { 40,70,110,-50,-90,-30,20,135,-100,100 };

//positions of second channel elements
int policeX = -400;
int policeY = 0;

int ambulanceX = -650;
int ambulanceY = 100;

int fireX = -150;
int fireY = 60;

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height

//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
	float angle;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
	float angle;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}

void print(int x, int y, const char *string, void *font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void *font, const char *string, ...)
{
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char *string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	int len, i;
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}

//background design
void windows() {
	glColor3f(0.1f, 0.1f, 0.1f);
	glRectf(-500, 300, 500, 270);
	glColor3f(0.19f, 0.19f, 0.19f);
	glRectf(-500, 290, 500, 280);
	glColor3f(0.1f, 0.1f, 0.1f);
	glRectf(-500, -60, 500, -30);
	glColor3f(0.19f, 0.19f, 0.19f);
	glRectf(-500, -50, 500, -40);
	glColor3f(0.1f, 0.1f, 0.1f);
	glRectf(-350, -300, -300, 300);
	glColor3f(0.19f, 0.19f, 0.19f);
	glRectf(-340, -300, -310, 300);
	glColor3f(0.1f, 0.1f, 0.1f);
	glRectf(450, -300, 500, 300);
	glColor3f(0.19f, 0.19f, 0.19f);
	glRectf(460, -300, 490, 300);
	glEnd();
}

void moonstars() {
	//moon
	glColor3f(1, 1, 1);
	circle(-500, 340, 150);
	//stars
	glColor3f(1, 1, 1);
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2f(-400, 230);
	glVertex2f(-330, 220);
	glVertex2f(-260, 215);
	glVertex2f(-130, 240);
	glVertex2f(-50, 200);
	glVertex2f(150, 245);
	glVertex2f(240, 245);
	glVertex2f(300, 260);
	glVertex2f(370, 220);
	glVertex2f(420, 230);
	glVertex2f(490, 200);
	glEnd();
}

void television() {
	glColor3f(0, 0, 0);
	glRectf(-450, -180, 250, 180);
	glColor3f(0.19f, 0.19f, 0.19f);
	glRectf(-445, -175, 245, 175);
	glColor3f(0, 0, 0);
	glRectf(-440, -170, 240, 170);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0);
	glVertex2f(-215, -180);
	glColor3f(0, 0, 0);
	glVertex2f(-150, -180);
	glColor3f(0, 0, 0);
	glVertex2f(-275, -220);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0);
	glVertex2f(15, -180);
	glColor3f(0, 0, 0);
	glVertex2f(-50, -180);
	glColor3f(0, 0, 0);
	glVertex2f(75, -220);
	glEnd();

	//table
	glColor3f(1.0f, 0.5f, 0.1f);
	glRectf(-380, -280, 190, -220);
	glColor3f(1.0f, 0.5f, 0.0f);
	glRectf(-420, -240, 230, -210);
	glColor3f(1.0f, 0.5f, 0.0f);
	glRectf(-410, -300, -380, -220);
	glColor3f(1.0f, 0.5f, 0.0f);
	glRectf(190, -300, 220, -220);

	glColor3f(0.19f, 0.19f, 0.19f);
	glRectf(-405, -275, -250, -215);
	glColor3f(0.19f, 0.19f, 0.19f);
	glRectf(55, -275, 215, -215);
	glColor3f(0.19f, 0.19f, 0.19f);
	glRectf(-245, -275, 50, -215);

	glColor3f(1.0f, 0.4f, 0.0f);
	glRectf(-403, -273, -252, -217);
	glColor3f(1.0f, 0.4f, 0.0f);
	glRectf(57, -273, 213, -217);
	glColor3f(1.0f, 0.4f, 0.0f);
	glRectf(-243, -273, 48, -217);
	glEnd();

	glColor3f(0.19f, 0.19f, 0.19f);
	circle_wire(-325, -245, 10);
	glColor3f(0.19f, 0.19f, 0.19f);
	circle_wire(-325, -245, 9);
	glColor3f(0.19f, 0.19f, 0.19f);
	circle_wire(135, -245, 10);
	glColor3f(0.19f, 0.19f, 0.19f);
	circle_wire(135, -245, 9);
	glColor3f(0.19f, 0.19f, 0.19f);
	circle_wire(0, -245, 10);
	glColor3f(0.19f, 0.19f, 0.19f);
	circle_wire(0, -245, 9);
	glColor3f(0.19f, 0.19f, 0.19f);
	circle_wire(-175, -245, 10);
	glColor3f(0.19f, 0.19f, 0.19f);
	circle_wire(-175, -245, 9);
	glEnd();
}

void remote() {
	//left side patch for television
	glColor3f(0.1, 0.2, 0.3);
	glRectf(-500, -300, -450, 185);
	glEnd();

	glColor3f(0.1f, 0.1f, 0.1f);
	glRectf(-500, -60, -450, -30);
	glColor3f(0.19f, 0.19f, 0.19f);
	glRectf(-500, -50, -450, -40);
	glEnd();

	glColor3f(0, 0, 0);
	glRectf(-450, -180, -445, 180);
	glColor3f(0.19f, 0.19f, 0.19f);
	glRectf(-445, -175, -440, 175);
	glEnd();

	//right side patch for television

	glColor3f(0.1, 0.2, 0.3);
	glRectf(250, -300, 450, 185);
	glEnd();

	glColor3f(0.1f, 0.1f, 0.1f);
	glRectf(250, -60, 450, -30);
	glColor3f(0.19f, 0.19f, 0.19f);
	glRectf(250, -50, 450, -40);
	glEnd();

	glColor3f(0, 0, 0);
	glRectf(245, -180, 250, 180);
	glColor3f(0.19f, 0.19f, 0.19f);
	glRectf(240, -175, 245, 175);
	glEnd();

	glColor3f(0.1f, 0.1f, 0.1f);
	glRectf(450, -300, 500, 300);
	glColor3f(0.19f, 0.19f, 0.19f);
	glRectf(460, -300, 490, 300);
	glEnd();

	//remote
	glColor3f(0, 0, 0);
	glRectf(300, -300, 430, -100);
	glColor3f(0.1, 0.1, 0.1);
	glRectf(302, -300, 428, -102);
	glEnd();

	//close button
	glColor3f(1, 0, 0);
	circle(365, -125, 15);
	glColor3f(1, 1, 1);
	circle(365, -125, 10);
	glColor3f(1, 0, 0);
	circle(365, -125, 7);
	glColor3f(1, 0, 0);
	glRectf(360, -130, 370, -115);
	glColor3f(1, 1, 1);
	glRectf(363, -125, 367, -114);
	glEnd();

	//volume channel buttons
	glColor3f(1, 1, 1);
	glRectf(318, -232, 352, -158);
	glColor3f(1, 1, 1);
	glRectf(378, -232, 412, -158);
	glEnd();
	glColor3f(0.19f, 0.19f, 0.19f);
	glRectf(320, -230, 350, -160);
	glColor3f(0.19f, 0.19f, 0.19f);
	glRectf(380, -230, 410, -160);
	glEnd();
	//+ & -
	glColor3f(1, 1, 1);
	glRectf(333, -180, 335, -165);
	glColor3f(1, 1, 1);
	glRectf(393, -180, 395, -165);
	glEnd();
	glColor3f(1, 1, 1);
	glRectf(327, -173, 341, -171);
	glColor3f(1, 1, 1);
	glRectf(387, -173, 401, -171);
	glEnd();
	glColor3f(1, 1, 1);
	vprint(325, -200, GLUT_BITMAP_8_BY_13, "CH");
	glColor3f(1, 1, 1);
	vprint(385, -200, GLUT_BITMAP_8_BY_13, "VOL");
	glColor3f(1, 1, 1);
	glRectf(327, -217, 341, -215);
	glColor3f(1, 1, 1);
	glRectf(387, -217, 401, -215);
	glEnd();

	//play pause buttons
	glColor3f(1, 1, 1);
	circle(340, -265, 15);
	glColor3f(1, 1, 1);
	circle(390, -265, 15);
	glColor3f(0.19f, 0.19f, 0.19f);
	circle(340, -265, 13);
	glColor3f(0.19f, 0.19f, 0.19f);
	circle(390, -265, 13);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2f(335, -270);
	glColor3f(1, 1, 1);
	glVertex2f(335, -260);
	glColor3f(1, 1, 1);
	glVertex2f(350, -265);
	glEnd();
	glColor3f(1, 1, 1);
	glRectf(384, -270, 389, -260);
	glColor3f(1, 1, 1);
	glRectf(392, -270, 397, -260);
	glEnd();
}

void displayoff() {
	glColor3f(0, 0, 0);
	glRectf(-450, -180, 250, 180);
	glColor3f(0.19f, 0.19f, 0.19f);
	glRectf(-445, -175, 245, 175);
	glColor3f(0, 0, 0);
	glRectf(-440, -170, 240, 170);
	glEnd();
}

//channel 1 elements
void smallvirus(float x, float y) {
	glColor3f(0.1f, 0.5f, 0.1f);
	circle(x, y, 15);
	glEnd();

	glColor3f(0.1f, 0.5f, 0.1f);
	glBegin(GL_TRIANGLES);
	glVertex2f(x, y + 25);
	glVertex2f(x - 5, y + 10);
	glVertex2f(x + 5, y + 10);
	glEnd();

	glColor3f(0.1f, 0.5f, 0.1f);
	circle(x, y + 22, 5);
	glEnd();

	glColor3f(0, 1, 0);
	circle(x, y + 22, 2.5);
	glEnd();

	glColor3f(0.1f, 0.5f, 0.1f);
	glBegin(GL_TRIANGLES);
	glVertex2f(x + 5, y - 10);
	glVertex2f(x - 5, y - 10);
	glVertex2f(x, y - 25);
	glEnd();

	glColor3f(0.1f, 0.5f, 0.1f);
	circle(x, y - 22, 5);
	glEnd();

	glColor3f(0, 1, 0);
	circle(x, y - 22, 2.5);
	glEnd();

	glColor3f(0.1f, 0.5f, 0.1f);
	glBegin(GL_TRIANGLES);
	glVertex2f(x + 25, y);
	glVertex2f(x + 5, y + 5);
	glVertex2f(x + 5, y - 5);
	glEnd();

	glColor3f(0.1f, 0.5f, 0.1f);
	circle(x + 22, y, 5);
	glEnd();

	glColor3f(0, 1, 0);
	circle(x + 22, y, 2.5);
	glEnd();

	glColor3f(0.1f, 0.5f, 0.1f);
	glBegin(GL_TRIANGLES);
	glVertex2f(x - 25, y);
	glVertex2f(x - 5, y + 5);
	glVertex2f(x - 5, y - 5);
	glEnd();

	glColor3f(0.1f, 0.5f, 0.1f);
	circle(x - 22, y, 5);
	glEnd();

	glColor3f(0, 1, 0);
	circle(x - 22, y, 2.5);
	glEnd();

	glColor3f(0, 1, 0);
	circle(x, y, 12.5);
	glEnd();

	glColor3f(0.1f, 0.5f, 0.1f);
	circle(x, y, 11);
	glEnd();

	glColor3f(0, 1, 0);
	circle(x, y, 7.5);
	glEnd();

	glColor3f(0.1f, 0.5f, 0.1f);
	circle(x, y, 5);
	glEnd();
}

void drawredcell(float x, float y) {
	glColor3f(1, 1, 1);
	circle(x, y, 22);
	glEnd();

	glColor3f(1, 1, 1);
	circle(x + 15, y, 22);
	glEnd();

	glColor3f(1, 0, 0);
	circle(x, y, 20);
	glEnd();

	glColor4f(1.0f, 0.5f, 0.6f, 0.9f);
	circle(x, y, 18);
	glEnd();

	glColor3f(1, 0, 0);
	circle(x, y, 16);
	glEnd();

	glColor3f(1, 0, 0);
	circle(x + 15, y, 20);
	glEnd();

	glColor4f(1.0f, 0.5f, 0.6f, 0.9f);
	circle(x + 15, y, 18);
	glEnd();

	glColor3f(1, 0, 0);
	circle(x, y, 16);
	glEnd();

	glColor3f(1, 0, 0);
	circle(x + 15, y, 16);
	glEnd();

}

//channel 2 elements
void drawPolice(int x, int y) {
	//Vehicle body
	glColor3f(0.1f, 0.0f, 0.6f);
	glBegin(GL_POLYGON);
	glVertex2f(x + 70, y + 40);
	glVertex2f(x - 40, y + 40);
	glVertex2f(x - 40, y - 20);
	glVertex2f(x + 70, y - 20);
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(x + 67, y + 37);
	glVertex2f(x - 37, y + 37);
	glVertex2f(x - 37, y - 17);
	glVertex2f(x + 67, y - 17);
	glEnd();
	glColor3f(0.1f, 0.0f, 0.6f);
	glBegin(GL_POLYGON);
	glVertex2f(x + 64, y + 34);
	glVertex2f(x - 34, y + 34);
	glVertex2f(x - 34, y - 14);
	glVertex2f(x + 64, y - 14);
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(x + 61, y + 31);
	glVertex2f(x - 31, y + 31);
	glVertex2f(x - 31, y - 11);
	glVertex2f(x + 61, y - 11);
	glEnd();
	glColor3f(0.1f, 0.0f, 0.6f);
	glBegin(GL_POLYGON);
	glVertex2f(x + 58, y + 28);
	glVertex2f(x - 28, y + 28);
	glVertex2f(x - 28, y - 8);
	glVertex2f(x + 58, y - 8);
	glEnd();
	glColor3f(0.1f, 0.0f, 0.6f);
	glBegin(GL_QUADS);
	glVertex2f(x + 70, y + 40);
	glVertex2f(x + 90, y + 20);
	glVertex2f(x + 90, y - 0);
	glVertex2f(x + 70, y - 20);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(x + 70, y + 30);
	glVertex2f(x + 85, y + 10);
	glVertex2f(x + 85, y + 0);
	glVertex2f(x + 70, y - 0);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(x - 40, y - 20);
	glVertex2f(x + 85, y - 20);
	glVertex2f(x + 70, y - 30);
	glVertex2f(x - 40, y - 30);
	glEnd();



	//vehicle's wing
	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(x + 60, y + 40);
	glColor3f(1, 0, 0);
	glVertex2f(x - 20, y + 40);
	glColor3f(0.1f, 0.0f, 0.6f);
	glVertex2f(x - 30, y - 100);
	glEnd();

	//Engines
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y - 20);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y - 10);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 50, y - 15);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y - 0);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y - 10);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex2f(x - 60, y - 5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y + 10);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y - 0);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex2f(x - 75, y + 5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y + 20);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y + 10);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex2f(x - 60, y + 15);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y + 30);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y + 20);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 50, y + 25);
	glEnd();

	//vehicles spoiler
	glBegin(GL_TRIANGLES);
	glColor3f(0.1f, 0.0f, 0.6f);
	glVertex2f(x - 40, y + 30);
	glColor3f(0.1f, 0.0f, 0.6f);
	glVertex2f(x - 40, y + 40);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(x - 70, y + 50);
	glEnd();

	//wheel
	glColor3f(0, 0, 0);
	circle(x + 50, y - 25, 12);
	glColor3f(1, 0, 0);
	circle(x + 50, y - 25, 6);
	glColor3f(0, 0, 0);
	circle(x + 50, y - 25, 3);

	//Vehicle type and number of vehicle
	glColor3f(1, 1, 1);
	vprint(x - 20, y + 25, GLUT_BITMAP_8_BY_13, " POLICE ");
}

void drawAmbulance(int x, int y) {
	//Vehicle body
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(x + 70, y + 40);
	glVertex2f(x - 40, y + 40);
	glVertex2f(x - 40, y - 20);
	glVertex2f(x + 70, y - 20);
	glEnd();
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(x + 67, y + 37);
	glVertex2f(x - 37, y + 37);
	glVertex2f(x - 37, y - 17);
	glVertex2f(x + 67, y - 17);
	glEnd();
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(x + 64, y + 34);
	glVertex2f(x - 34, y + 34);
	glVertex2f(x - 34, y - 14);
	glVertex2f(x + 64, y - 14);
	glEnd();
	glColor3f(0.1f, 0.0f, 0.6f);
	glBegin(GL_POLYGON);
	glVertex2f(x + 61, y + 31);
	glVertex2f(x - 31, y + 31);
	glVertex2f(x - 31, y - 11);
	glVertex2f(x + 61, y - 11);
	glEnd();
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(x + 58, y + 28);
	glVertex2f(x - 28, y + 28);
	glVertex2f(x - 28, y - 8);
	glVertex2f(x + 58, y - 8);
	glEnd();
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex2f(x + 70, y + 40);
	glVertex2f(x + 90, y + 20);
	glVertex2f(x + 90, y - 0);
	glVertex2f(x + 70, y - 20);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(x + 70, y + 30);
	glVertex2f(x + 85, y + 10);
	glVertex2f(x + 85, y + 0);
	glVertex2f(x + 70, y - 0);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(x - 40, y - 20);
	glVertex2f(x + 85, y - 20);
	glVertex2f(x + 70, y - 30);
	glVertex2f(x - 40, y - 30);
	glEnd();


	//vehicle's wing
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(x + 60, y + 40);
	glColor3f(1, 0, 0);
	glVertex2f(x - 20, y + 40);
	glColor3f(0.1f, 0.0f, 0.6f);
	glVertex2f(x - 30, y - 100);
	glEnd();

	//Engines
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y - 20);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y - 10);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 50, y - 15);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y - 0);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y - 10);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex2f(x - 60, y - 5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y + 10);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y - 0);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex2f(x - 75, y + 5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y + 20);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y + 10);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex2f(x - 60, y + 15);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y + 30);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y + 20);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 50, y + 25);
	glEnd();

	//vehicles spoiler
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2f(x - 40, y + 30);
	glColor3f(1, 1, 1);
	glVertex2f(x - 40, y + 40);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(x - 70, y + 50);
	glEnd();

	//wheel
	glColor3f(0, 0, 0);
	circle(x + 50, y - 25, 12);
	glColor3f(0.1f, 0.0f, 0.6f);
	circle(x + 50, y - 25, 6);
	glColor3f(0, 0, 0);
	circle(x + 50, y - 25, 3);

	//Vehicle type and number of vehicle
	glColor3f(1, 1, 1);
	vprint(x - 28, y + 25, GLUT_BITMAP_8_BY_13, " AMBULANCE ");	
}

void drawFire(int x, int y) {

	//Vehicle body
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(x + 70, y + 40);
	glVertex2f(x - 40, y + 40);
	glVertex2f(x - 40, y - 20);
	glVertex2f(x + 70, y - 20);
	glEnd();
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(x + 67, y + 37);
	glVertex2f(x - 37, y + 37);
	glVertex2f(x - 37, y - 17);
	glVertex2f(x + 67, y - 17);
	glEnd();
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(x + 64, y + 34);
	glVertex2f(x - 34, y + 34);
	glVertex2f(x - 34, y - 14);
	glVertex2f(x + 64, y - 14);
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(x + 61, y + 31);
	glVertex2f(x - 31, y + 31);
	glVertex2f(x - 31, y - 11);
	glVertex2f(x + 61, y - 11);
	glEnd();
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(x + 58, y + 28);
	glVertex2f(x - 28, y + 28);
	glVertex2f(x - 28, y - 8);
	glVertex2f(x + 58, y - 8);
	glEnd();
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(x + 70, y + 40);
	glVertex2f(x + 90, y + 20);
	glVertex2f(x + 90, y - 0);
	glVertex2f(x + 70, y - 20);
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(x + 70, y + 30);
	glVertex2f(x + 85, y + 10);
	glVertex2f(x + 85, y + 0);
	glVertex2f(x + 70, y - 0);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(x - 40, y - 20);
	glVertex2f(x + 85, y - 20);
	glVertex2f(x + 70, y - 30);
	glVertex2f(x - 40, y - 30);
	glEnd();


	//vehicle's wing
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0);
	glVertex2f(x + 60, y + 40);
	glColor3f(0, 0, 0);
	glVertex2f(x - 20, y + 40);
	glColor3f(1, 0, 0);
	glVertex2f(x - 30, y - 100);
	glEnd();

	//Engines
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y - 20);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y - 10);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 50, y - 15);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y - 0);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y - 10);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex2f(x - 60, y - 5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y + 10);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y - 0);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex2f(x - 75, y + 5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y + 20);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y + 10);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex2f(x - 60, y + 15);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y + 30);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 40, y + 20);
	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex2f(x - 50, y + 25);
	glEnd();

	//vehicles spoiler
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(x - 40, y + 30);
	glColor3f(1, 0, 0);
	glVertex2f(x - 40, y + 40);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(x - 70, y + 50);
	glEnd();


	//wheel
	glColor3f(0, 0, 0);
	circle(x + 50, y - 25, 12);
	glColor3f(1, 1, 1);
	circle(x + 50, y - 25, 6);
	glColor3f(0.1f, 0.0f, 0.6f);
	circle(x + 50, y - 25, 3);

	//Vehicle type and number of vehicle
	glColor3f(1, 1, 1);
	vprint(x - 28, y + 25, GLUT_BITMAP_8_BY_13, " FIRE DEP. ");
	
}

//channel modes
void displayrun1() {
	//background
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(-440, -170);
	glColor3f(2.0f, 0.5f, 1.0f);
	glVertex2f(-440, 170);
	glColor3f(1, 0, 0);
	glVertex2f(-100, 170);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(2.0f, 0.5f, 1.0f);
	glVertex2f(-440, -170);
	glColor3f(1, 0, 0);
	glVertex2f(240, -170);
	glColor3f(1, 0, 0);
	glVertex2f(-100, 170);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(240, 170);
	glColor3f(1, 0, 0);
	glVertex2f(240, -170);
	glColor3f(2.0f, 0.5f, 1.0f);
	glVertex2f(-100, 170);
	glEnd();

	//drawing redcell and virus
	for (int i = 0; i < 10; i++)
		drawredcell(redcellX[i], redcellY[i]);

	for (int i = 0; i < 10; i++)
		smallvirus(sVirusX[i], sVirusY[i]);

	glColor3f(0, 0, 1);
	glRectf(-440, -150, 240, -110);
	glColor3f(0, 0.3, 0.6);
	glRectf(-440, -148, 240, -112);
	glEnd();

	glColor3f(1, 1, 1);
	vprint(-430, -138, GLUT_BITMAP_TIMES_ROMAN_24, "NEW VARIANT OF CORONAVIRUS HAS ARRIVED USA");

	//volume information
	if (volumeX > -500 && volumeX < -400) {
		glColor3f(0, 0, 0);
		glRectf(-432, 128, -368, 162);
		glColor3f(1,1,1);
		glRectf(-430,130,-370,160);
		glColor3f(0,0,0);
		glRectf(-417, 140, -400, 150);

		glBegin(GL_TRIANGLES);
		glColor3f(0, 0, 0);
		glVertex2f(-415, 145);
		glColor3f(0, 0, 0);
		glVertex2f(-400, 155);
		glColor3f(0, 0, 0);
		glVertex2f(-400, 135);
		glEnd();
		
		glColor3f(0, 0, 0);
		vprint(-393,140, GLUT_BITMAP_8_BY_13, "%d", volume);
		glEnd();
	}

}

void displayrun2() {
	//background
	glColor3f(0.0, 0.4, 0.7);
	glRectf(-440, -170, 240, 170);
	glEnd();

	glColor3f(1,1,1);
	vprint(120, 150, GLUT_BITMAP_8_BY_13, "TRANSFORMERS 2");	
	glEnd();

	//buildings
	glColor3f(0.1f, 0.1f, 0.1f);
	glRectf(-400, -170, -240, 100);
	glColor3f(0.1f, 0.1f, 0.1f);
	glRectf(-200, -170, 0, 160);
	glColor3f(0.1f, 0.1f, 0.1f);
	glRectf(50, -170, 210, 70);
	glEnd();

	//building lights
	//first
	glColor3f(1, 1, 0);
	circle(-350, 30, 25);
	glColor3f(0, 0, 0);
	circle(-285, 30, 25);	
	glColor3f(0, 0, 0);
	circle(-350, -50, 25);
	glColor3f(1, 1, 0);
	circle(-285, -50, 25);
	glColor3f(1, 1, 0);
	circle(-350, -130, 25);
	glColor3f(0, 0, 0);
	circle(-285, -130, 25);
	//second
	glColor3f(0, 0, 0);
	circle(-140, 110, 25);
	glColor3f(1, 1, 0);
	circle(-55, 110, 25);
	glColor3f(1, 1, 0);
	circle(-140, 30, 25);
	glColor3f(1, 1, 0);
	circle(-55, 30, 25);
	glColor3f(0, 0, 0);
	circle(-140, -50, 25);
	glColor3f(1, 1, 0);
	circle(-55, -50, 25);
	glColor3f(1, 1, 0);
	circle(-140, -130, 25);
	glColor3f(0, 0, 0);
	circle(-55, -130, 25);
	//third
	glColor3f(0, 0, 0);
	circle(100, 30, 25);
	glColor3f(1, 1, 0);
	circle(170, 30, 25);
	glColor3f(0, 0, 0);
	circle(100, -50, 25);
	glColor3f(0, 0, 0);
	circle(170, -50, 25);
	glColor3f(1, 1, 0);
	circle(100, -130, 25);
	glColor3f(1, 1, 0);
	circle(170, -130, 25);

	//drawing vehicles
	drawFire(fireX, fireY);
	drawPolice(policeX, policeY);
	drawAmbulance(ambulanceX, ambulanceY);

	//volume information
	if (volumeX > -500 && volumeX < -400) {
		glColor3f(0, 0, 0);
		glRectf(-432, 128, -368, 162);
		glColor3f(1, 1, 1);
		glRectf(-430, 130, -370, 160);
		glColor3f(0, 0, 0);
		glRectf(-417, 140, -400, 150);

		glBegin(GL_TRIANGLES);
		glColor3f(0, 0, 0);
		glVertex2f(-415, 145);
		glColor3f(0, 0, 0);
		glVertex2f(-400, 155);
		glColor3f(0, 0, 0);
		glVertex2f(-400, 135);
		glEnd();

		glColor3f(0, 0, 0);
		vprint(-393, 140, GLUT_BITMAP_8_BY_13, "%d", volume);
		glEnd();
	}
}

void displaypause1() {
	//background
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(-440, -170);
	glColor3f(2.0f, 0.5f, 1.0f);
	glVertex2f(-440, 170);
	glColor3f(1, 0, 0);
	glVertex2f(-100, 170);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(2.0f, 0.5f, 1.0f);
	glVertex2f(-440, -170);
	glColor3f(1, 0, 0);
	glVertex2f(240, -170);
	glColor3f(1, 0, 0);
	glVertex2f(-100, 170);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(240, 170);
	glColor3f(1, 0, 0);
	glVertex2f(240, -170);
	glColor3f(2.0f, 0.5f, 1.0f);
	glVertex2f(-100, 170);
	glEnd();

	//redcells
	for (int i = 0; i < 10; i++)
		drawredcell(redcellX[i], redcellY[i]);

	for (int i = 0; i < 10; i++)
		smallvirus(sVirusX[i], sVirusY[i]);

	//news information
	glColor3f(0, 0, 1);
	glRectf(-440, -150, 240, -110);
	glColor3f(0, 0.3, 0.6);
	glRectf(-440, -148, 240, -112);
	glEnd();
	glColor3f(1, 1, 1);
	vprint(-430, -138, GLUT_BITMAP_TIMES_ROMAN_24, "NEW VARIANT OF CORONAVIRUS HAS ARRIVED USA");

	//pause information
	glColor3f(1,1,1);
	glRectf(-102, -2, -38, 22);
	glColor3f(0.3, 0.3, 0.3);
	glRectf(-100, 0, -40, 20);

	glColor3f(1, 1, 1);
	glRectf(-97, 28, -73, 82);
	glColor3f(1, 1, 1);
	glRectf(-66, 28, -42, 82);

	glColor3f(0.3, 0.3, 0.3);
	glRectf(-95, 30, -75, 80);
	glColor3f(0.3, 0.3, 0.3);
	glRectf(-64, 30, -44, 80);	
	glEnd();

	glColor3f(0, 1, 0);
	vprint(-102, 5, GLUT_BITMAP_8_BY_13, " PAUSED");

	//volume information
	if (volumeX > -500 && volumeX < -400) {
		glColor3f(0, 0, 0);
		glRectf(-432, 128, -368, 162);
		glColor3f(1, 1, 1);
		glRectf(-430, 130, -370, 160);
		glColor3f(0, 0, 0);
		glRectf(-417, 140, -400, 150);

		glBegin(GL_TRIANGLES);
		glColor3f(0, 0, 0);
		glVertex2f(-415, 145);
		glColor3f(0, 0, 0);
		glVertex2f(-400, 155);
		glColor3f(0, 0, 0);
		glVertex2f(-400, 135);
		glEnd();

		glColor3f(0, 0, 0);
		vprint(-393, 140, GLUT_BITMAP_8_BY_13, "%d", volume);
		glEnd();
	}
}

void displaypause2() {
	//background
	glColor3f(0.0, 0.4, 0.7);
	glRectf(-440, -170, 240, 170);
	glEnd();

	glColor3f(1, 1, 1);
	vprint(120, 150, GLUT_BITMAP_8_BY_13, "TRANSFORMERS 2");
	glEnd();

	//buildings
	glColor3f(0.1f, 0.1f, 0.1f);
	glRectf(-400, -170, -240, 100);
	glColor3f(0.1f, 0.1f, 0.1f);
	glRectf(-200, -170, 0, 160);
	glColor3f(0.1f, 0.1f, 0.1f);
	glRectf(50, -170, 210, 70);
	glEnd();

	//building lights
	//first
	glColor3f(1, 1, 0);
	circle(-350, 30, 25);
	glColor3f(0, 0, 0);
	circle(-285, 30, 25);
	glColor3f(0, 0, 0);
	circle(-350, -50, 25);
	glColor3f(1, 1, 0);
	circle(-285, -50, 25);
	glColor3f(1, 1, 0);
	circle(-350, -130, 25);
	glColor3f(0, 0, 0);
	circle(-285, -130, 25);
	//second
	glColor3f(0, 0, 0);
	circle(-140, 110, 25);
	glColor3f(1, 1, 0);
	circle(-55, 110, 25);
	glColor3f(1, 1, 0);
	circle(-140, 30, 25);
	glColor3f(1, 1, 0);
	circle(-55, 30, 25);
	glColor3f(0, 0, 0);
	circle(-140, -50, 25);
	glColor3f(1, 1, 0);
	circle(-55, -50, 25);
	glColor3f(1, 1, 0);
	circle(-140, -130, 25);
	glColor3f(0, 0, 0);
	circle(-55, -130, 25);
	//third
	glColor3f(0, 0, 0);
	circle(100, 30, 25);
	glColor3f(1, 1, 0);
	circle(170, 30, 25);
	glColor3f(0, 0, 0);
	circle(100, -50, 25);
	glColor3f(0, 0, 0);
	circle(170, -50, 25);
	glColor3f(1, 1, 0);
	circle(100, -130, 25);
	glColor3f(1, 1, 0);
	circle(170, -130, 25);

	drawFire(fireX, fireY);
	drawPolice(policeX, policeY);
	drawAmbulance(ambulanceX, ambulanceY);

	//pause information
	glColor3f(1, 1, 1);
	glRectf(-102, -2, -38, 22);
	glColor3f(0.3, 0.3, 0.3);
	glRectf(-100, 0, -40, 20);

	glColor3f(1, 1, 1);
	glRectf(-97, 28, -73, 82);
	glColor3f(1, 1, 1);
	glRectf(-66, 28, -42, 82);

	glColor3f(0.3, 0.3, 0.3);
	glRectf(-95, 30, -75, 80);
	glColor3f(0.3, 0.3, 0.3);
	glRectf(-64, 30, -44, 80);
	glEnd();

	glColor3f(0, 1, 0);
	vprint(-102, 5, GLUT_BITMAP_8_BY_13, " PAUSED");

	//volume information
	if (volumeX > -500 && volumeX < -400) {
		glColor3f(0, 0, 0);
		glRectf(-432, 128, -368, 162);
		glColor3f(1, 1, 1);
		glRectf(-430, 130, -370, 160);
		glColor3f(0, 0, 0);
		glRectf(-417, 140, -400, 150);

		glBegin(GL_TRIANGLES);
		glColor3f(0, 0, 0);
		glVertex2f(-415, 145);
		glColor3f(0, 0, 0);
		glVertex2f(-400, 155);
		glColor3f(0, 0, 0);
		glVertex2f(-400, 135);
		glEnd();

		glColor3f(0, 0, 0);
		vprint(-393, 140, GLUT_BITMAP_8_BY_13, "%d", volume);
		glEnd();
	}
}


//
// To display onto window using OpenGL commands
//
void display() {
	//
	// clear window to black
	//
	glClearColor(0.1, 0.2, 0.3, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	//volume circle (when its between special coordinates volume information becomes visible)
	glColor3f(1, 1, 1);
	circle(volumeX, volumeY, 5);
	glEnd();
	
	//switch for modes
	switch (mode) {
	case OFF:
		moonstars();
		windows();
		television();
		displayoff();
		remote();
		break;
	case RUN1:
		moonstars();
		windows();
		television();
		displayrun1();
		remote();
		break;
	case PAUSE1:
		moonstars();
		windows();
		television();
		displaypause1();
		remote();
		break;
	case RUN2:
		moonstars();
		windows();
		television();
		displayrun2();
		remote();
		break;
	case PAUSE2:
		moonstars();
		windows();
		television();
		displaypause2();
		remote();
		break;
	}		

	glutSwapBuffers();
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP: up = true; break;
	case GLUT_KEY_DOWN: down = true; break;
	case GLUT_KEY_LEFT: left = true; break;
	case GLUT_KEY_RIGHT: right = true; break;
	}

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP: up = false; break;
	case GLUT_KEY_DOWN: down = false; break;
	case GLUT_KEY_LEFT: left = false; break;
	case GLUT_KEY_RIGHT: right = false; break;
	}

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) {
		// Write your codes here.		

		//close button
		if (mode == OFF && inCloseButton == true) {
			mode = RUN1;
			timer = 1;
		}
		else if (inCloseButton == true)
			mode = OFF;

		//pause button
		if (mode == RUN1 && inPauseButton == true) {
			mode = PAUSE1;
			timer = 0;
		}
		if (mode == RUN2 && inPauseButton == true) {
			mode = PAUSE2;
			timer = 0;
		}
		//play button
		if (mode == PAUSE1 && inPlayButton == true) {
			mode = RUN1;
			timer = 1;
		}
		if (mode == PAUSE2 && inPlayButton == true) {
			mode = RUN2;
			timer = 1;
		}
		//chanel buttons
		
		if (mode == RUN1 && inChanelPlusButton == true) {
			timer = 1;
			mode = RUN2;
		}

		else if (inChanelPlusButton == true) {
			if (mode == PAUSE1) {
				timer = 1;
				mode = RUN2;
			}
			else {
				timer = 1;
				mode = RUN1;
			}
		}

		if (mode == RUN1 && inChanelMinusButton == true) {
			timer = 1;
			mode = RUN2;
		}

		else if (inChanelMinusButton == true) {
			if (mode == PAUSE1) {
				timer = 1;
				mode = RUN2;
			}
			else {
				timer = 1;
				mode = RUN1;
			}
		}				

		//volume buttons

		if (volume <= 95 && inVolumePlusButton == true) {
			volume += 5;
			volumeX = -500;
		}
		if (volume >= 5 && inVolumeMinusButton == true) {
			volume -= 5;
			volumeX = -500;
		}

	}
	// to refresh the window it calls display() function
	glutPostRedisplay();

}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display(); // refresh window.
}

void onMoveDown(int x, int y) {
	// Write your codes here.



	// to refresh the window it calls display() function   
	glutPostRedisplay();
}

//checking circle function 
bool checkCircle(float px, float py, float cx, float cy, float R) {
	float dx = px - cx;
	float dy = py - cy;
	float d = sqrt(dx*dx + dy * dy);
	return d <= R;
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
	// Write your codes here.	

	tempX = x - winWidth / 2;
	tempY = winHeight / 2 - y;

	//check if mouse is inside
	inCloseButton = checkCircle(tempX, tempY, 365, -125, 15);
	inPauseButton = checkCircle(tempX, tempY, 390, -265, 15);
	inPlayButton = checkCircle(tempX, tempY, 340, -265, 15);
	inChanelPlusButton = checkCircle(tempX, tempY, 335, -173, 20);
	inChanelMinusButton = checkCircle(tempX, tempY, 335, -215, 20);
	inVolumePlusButton = checkCircle(tempX, tempY, 395, -173, 20);
	inVolumeMinusButton = checkCircle(tempX, tempY, 395, -215, 20);

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	// Write your codes here.

	if (timer) {
		//redcells & virus
		for (int i = 0; i < 10; i++) {
			if (sVirusX[i] < 400 || redcellX[i] < 400) {
				redcellX[i]++;
				sVirusX[i]++;				
			}
			else {
				redcellX[i] = -600;
				sVirusX[i] = -600;				
			}
		}		

		//vehicles
		if (ambulanceX < 380)		
			ambulanceX++;		
		else			
			ambulanceX = -530;
				
		if (policeX < 380)
			policeX++;		
		else
			policeX = -530;
			
		if (fireX < 380)
			fireX++;		
		else		
			fireX = -530;

		if (volumeX < 500)
			volumeX++;		
	}

	// to refresh the window it calls display() function
	glutPostRedisplay(); // display()

}
#endif

void Init() {

	// Smoothing shapes
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	//glutInitWindowPosition(100, 100);
	glutCreateWindow("TV Night by Ahmet Burak Yuksel");

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);

	//
	// keyboard registration
	//
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecialKeyDown);

	glutKeyboardUpFunc(onKeyUp);
	glutSpecialUpFunc(onSpecialKeyUp);

	//
	// mouse registration
	//
	glutMouseFunc(onClick);
	glutMotionFunc(onMoveDown);
	glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
	// timer event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

	Init();

	glutMainLoop();
}
