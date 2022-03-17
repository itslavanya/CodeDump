#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include<windows.h>
#include <GL/glut.h>


#endif

#include <stdlib.h>
#include<stdio.h>
GLfloat v[8][3] = {
                    {-1.0,1.0,1.0},
                    {1.0,1.0,1.0},
                    {1.0,-1.0,1.0},
                    {-1.0,-1.0,1.0},

                    {-1.0,1.0,-1.0},
                    {1.0,1.0,-1.0},
                    {1.0,-1.0,-1.0},
                    {-1.0,-1.0,-1.0}
                          };

void myInit(){

glClearColor(0,0,0,1);
glColor3f(1,0,0);

}
void face(){

}

void cube(GLfloat v0[],GLfloat v1[],GLfloat v2[],GLfloat v3[],GLfloat v4[],GLfloat v5[],GLfloat v6[],GLfloat v7[]){
    face();

}
void draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cube(v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7]);
    glBegin(GL_POLYGON);
        glVertex3f(-0.5,0.5);
        glVertex2f(0.5,0.5);
        glVertex2f(0.5,-0.5);
        glVertex2f(-0.5,-0.5);
    glEnd();
    glutSwapBuffers();


}
int main(int argc, char **argv)
{
    glutInit(&argc,argv );
    glutInitWindowPosition(500,50);
    glutInitWindowSize(600,600);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutCreateWindow("Spinning Color Cube");

    myInit();
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}
