#include "Stickman.h"
#include "math.h"
#include <GL/glew.h>  
#include <GL/glut.h>
#include <string>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
//#include <cstdio>
//#include <cstdlib>
//#include <GL\gl.h>
using namespace std;
stickman::stickman()
{
}

stickman::~stickman()
{
}
string shaderFilename1="v";
string shaderFilename2="phong";
GLuint progID;
static float tea_angle = 0;
static float distance1 = 0;
static bool foward = 1;//前进方向
static float  lleg_angle1 = 0, lleg_angle2 = 0, rleg_angle1 = 0, rleg_angle2 = 0, larm_angle1 = 0,
larm_angle2 = 0, rarm_angle1 = 0, rarm_angle2 = 0;//腿和胳膊的旋转角度，其中leg1为大腿，arm1为大臂
GLfloat no_mat[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
GLfloat mat_diffuse[] = { 0.5, 0.8, 0.0, 1.0 };
GLfloat mat_specular[] = { 1.0, 0.0, 0.5, 1.0 };
GLfloat no_shininess[] = { 0.5 };
GLfloat low_shininess[] = { 5.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };
std::string loadShaderSrc(const std::string& filename) {//加载Shader文件
	std::ifstream is(filename);
	if (is.is_open()) {
		std::stringstream buffer;
		buffer << is.rdbuf();
		return buffer.str();
	}
	cerr << "Unable to open file " << filename << endl;
	exit(1);
}
void setupShaders() {
	GLenum ERR = glewInit();
	// create shader
	GLuint vertID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);

	//加载文件
	std::string vs = loadShaderSrc("./" + shaderFilename1 + ".vert");
	const char* vss = vs.c_str();
	std::string fs = loadShaderSrc("./" + shaderFilename2 + ".frag");
	const char* fss = fs.c_str();

	// specify shader source
	glShaderSource(vertID, 1, &(vss), NULL);
	glShaderSource(fragID, 1, &(fss), NULL);

	//编译shader
	glCompileShader(vertID);
	glCompileShader(fragID);

	// create program并且attach shaders
	GLint progID = glCreateProgram();
	glAttachShader(progID, vertID);
	glAttachShader(progID, fragID);
	glLinkProgram(progID);
}
	void init(void)
	{
		GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat position[] = { -0.3,0.3, -0.3, 0.0 };
		GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
		GLfloat local_view[] = { 10.0 };
		GLfloat angle[] = { 30.00 };
		glClearColor(0, 0, 0, 0);
		setupShaders();
		glShadeModel(GL_FLAT);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, position);
		glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT, local_view);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_NORMALIZE);
	}
void setleg_and_arm_Material()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}
void draw_body(void)
{
	glPushMatrix();
	GLfloat no_mat[] = { 1.0, 1.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glColor3f(1.0f, 1.0f, 0.0f);//黄色
	glTranslatef(distance1, 0.3f, 0.0f);//沿着y轴向上平移
	glScalef(0.3f, 0.6f, 0.3f);
	//glTranslatef(distance, 0.0f, 0.0f);
	glutSolidCube(1);
	glPopMatrix();
}
void draw_teapot(void)
{
	glPushMatrix();
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(0, -0.7f, 0.7f);
	glRotatef(tea_angle, 0, 1, 0);
	glScalef(0.1f, 0.1f, 0.1f);
	//glTranslatef(3*distance, 0.0f, 0.0f);
	glutSolidTeapot(2.0);
	glPopMatrix();
}
void draw_head(void)
{

	glPushMatrix();
	GLfloat no_mat[] = { 0.0, 0.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glShadeModel(GL_SMOOTH);
	glColor3f(0.0f, 0.0f, 1.0f);
	glTranslatef(distance1, 0.7f, 0.0f);
	glScalef(0.1f, 0.1f, 0.1f);
	//glTranslatef(3*distance, 0.0f, 0.0f);
	glutWireSphere(1.4, 200, 500);
	glPopMatrix();
}
void draw_leftleg()
{
	glPushMatrix();
	GLfloat no_mat[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(distance1, 0.0f, 0.1f);
	glRotatef(lleg_angle1, 0, 0, 1);
	glTranslatef(0.0f, -0.15f, 0.0f);
	glScalef(0.1f, 0.3f, 0.1f);
	//GLfloat no_mat[] = { 0.0, 1.0, 0.0, 1.0 };
	//setleg_and_arm_Material();
	glutSolidCube(1);
	glColor3f(0.0f, 1.0f, 0.0f);
	GLfloat no_mat1[] = { 0.0, 1.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat1);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat1);
	glTranslatef(0.0f, -1.0f, 0.0f);
	glRotatef(lleg_angle2, 0, 0, 1);

	glScalef(0.5f, 1.0f, 1.0f);
	glTranslatef(0.0f, -0.0f, 0.0f);
	glutSolidCube(1);
	glPopMatrix();


}
void draw_rightleg()
{
	glPushMatrix();
	GLfloat no_mat[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glColor3f(1.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(distance1, 0.0f, -0.1f);
	glRotatef(rleg_angle1, 0, 0, 1);
	glTranslatef(0.0f, -0.15f, 0.0f);
	glScalef(0.1f, 0.3f, 0.1f);
	//GLfloat no_mat[] = { 0.0, 1.0, 0.0, 1.0 };
	glutSolidCube(1);
	glColor3f(0.0f, 1.0f, 0.0f);
	GLfloat no_mat1[] = { 0.0, 1.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat1);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat1);
	glTranslatef(0.0f, -1.0f, 0.0f);
	glRotatef(rleg_angle2, 0, 0, 1);

	glScalef(0.5f, 1.0f, 1.0f);
	glTranslatef(0.0f, -0.0f, 0.0f);
	glutSolidCube(1);
	glPopMatrix();
}
void draw_leftarm()
{
	glPushMatrix();//正前方是左边
	GLfloat no_mat[] = { 1.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(distance1, 0.5f, -0.2f);
	glRotatef(larm_angle1, 0, 0, 1);
	glTranslatef(0.0f, -0.05f, 0.0f);
	glScalef(0.10f, 0.3f, 0.1f);
	//GLfloat no_mat[] = { 1.0, 0.0, 1.0, 1.0 };
	//setleg_and_arm_Material();
	//glTranslatef(0.0f, 0.0f,-distance);
	glutSolidCube(1);
	glColor3f(1.0f, 0.0f, 1.0f);
	GLfloat no_mat1[] = { 0.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat1);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat1);
	glTranslatef(0.0f, -0.75f, 0.0f);
	glRotatef(larm_angle2, 0, 0, 1);
	glTranslatef(0.0f, -0.16f, 0.0f);
	glScalef(0.10 / 0.15f, 1.0f, 1.0f);
	glutSolidCube(1);
	glPopMatrix();

}
void draw_rightarm()
{
	glPushMatrix();
	GLfloat no_mat[] = { 1.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(distance1, 0.5f, 0.2f);
	glRotatef(rarm_angle1, 0, 0, 1);
	glTranslatef(0.0f, -0.05f, 0.0f);
	glScalef(0.10f, 0.3f, 0.1f);
	//GLfloat no_mat[] = { 1.0, 0.0, 1.0, 1.0 };
	//setleg_and_arm_Material();
	//glTranslatef(0.0f,0.0f, -distance);
	glutSolidCube(1);
	glColor3f(1.0f, 0.0f, 1.0f);
	GLfloat no_mat1[] = { 0.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat1);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat1);

	glTranslatef(0.0f, -0.75f, 0.0f);
	glRotatef(rarm_angle2, 0, 0, 1);
	glTranslatef(0.0f, -0.16f, 0.0f);
	glScalef(0.10 / 0.15f, 1.0f, 1.0f);
	glutSolidCube(1);
	glPopMatrix();
}
void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	init();
	glUseProgram(progID);
	

	if (larm_angle1 >= 20)
		foward = 0;
	if
		(larm_angle1 <= -20)
		foward = 1;
	if (distance1 > 0.1)
		distance1 = 0;

	gluLookAt(0.4, -0.15, 0.15, 0, 0, 0, 0, 1, 0);
	glPushMatrix();
	draw_body();
	draw_head();
	draw_leftleg();
	draw_rightleg();
	draw_leftarm();
	draw_rightarm();
	draw_teapot();

	glPopMatrix();
	glutSwapBuffers();
	glFlush();
}
void myidle()
{
	//bool foward = 1;//左臂和右腿向前运动

	if (foward == 1){
		distance1 = distance1 - 0.00006;
		larm_angle1 += 0.05;
		larm_angle2 += 0.1;
		rarm_angle1 -= 0.05;
		rarm_angle2 -= 0.1;
		lleg_angle1 -= 0.05;
		rleg_angle1 += 0.05;
		lleg_angle2 -= 0.1;
		rleg_angle2 += 0.1;
		tea_angle += 0.2;

	}
	else{
		distance1 = distance1 - 0.00006;
		rarm_angle1 += 0.05;
		rarm_angle2 += 0.1;
		larm_angle1 += -0.05;
		larm_angle2 += -0.1;
		lleg_angle1 += 0.05;
		rleg_angle1 -= 0.05;
		lleg_angle2 += 0.1;
		rleg_angle2 -= 0.1;
		tea_angle += 0.2;
	}
	mydisplay();
}


int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 0);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	

	glutCreateWindow("robot animation!");
	glutDisplayFunc(&mydisplay);
	glutIdleFunc(&myidle);
	glutMainLoop();
	return 0;
}
