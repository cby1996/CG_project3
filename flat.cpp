#include "flat.h"


flat::flat()
{
}


flat::~flat()
{
}
#include<stdarg.h>  
 
#include<GL/glut.h>  
#include<math.h>  
#include<iostream>  


//#pragma comment(lib,"libpng16.lib")  

void draw(void)
{
	glutSolidTeapot(1.0);
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	draw();
	glFlush();
}

void reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0*(GLfloat)h / (GLfloat)w,
		2.0*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-2.0*(GLfloat)h / (GLfloat)w,
		2.0*(GLfloat)h / (GLfloat)w, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int ac, char** av)
{
	glutInit(&ac, av);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("lighttest");
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(800, 800);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glShadeModel(GL_FLAT);

	//��ɫ�Ļ����� �� ��ɫ��������⡣Ч������ �ռ䶼�Ǻ�ɫ�Ĺ⵫���������淴�����ɫ�Ĺ�  

	GLfloat light_position[] = { 0.0f, 0.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat light_diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); //����������ڻ���������Ϸ����һ�ֹ�  

	GLfloat light_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_diffuse);//������,���ǻ����⣬��������˵Ĺ�  

	GLfloat light_specular[] = { 0.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_diffuse);//�߹�  

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(&display);
	glutReshapeFunc(&reshape);
	glutMainLoop();
	return 0;
}