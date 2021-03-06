//Not able to draw edges maybe check with glFlush and glutSwapBuffers or GLUT_DOUBLE or GLUT_SINGLE
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include<windows.h>
#include <GL/glut.h>


#endif

#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<math.h>

using namespace std;

void find_spanning_tree();
void bitmap_output(int x, int y, char *string, void *font);

//Global variables
int pointer=0,point=0,line=0,lpointer=0,upointer=-1,undo_cost_stack_pointer=-1;
int costmatrix[100][100],undo_cost_stack[100],lineundostack[100][100];
int undone=0,nf=0,f=0,found=0,nodenum=1,load=0;
int t[100][2],totalcost;
bool paused=false;
bool enterpressed=false,resdisplay=false;
char undostack[100];
char num[2];
char text[15]="Mode: None";
float sx=-1,sy=-1;
float oldx[100][100],linepoints[2][2],linex[100][4];
float fade=0.1;
GLfloat width=900,height=600;

//This functions writes the integer into char array
void int_str(int rad,char r[])
{
	sprintf(r,"%d",rad);
}

//whenever undo function is called the cost is pushed into the stack
void push(int n){
	undo_cost_stack[++undo_cost_stack_pointer]=n;
}

//when redo function is called the cost is popped out
int pop(){
	if(undo_cost_stack_pointer>=0){
		return undo_cost_stack[undo_cost_stack_pointer--];
	}
	return 999;
}

//this function creates nodes using location stored in oldx[][] array
void drawpoint(){
	float angle=2.0f*3.1416f/360;
	int radius= 20;
	for(int i=0;i<pointer;i++){
    glBegin(GL_POINTS);
	glColor3f(0.0, 0.68, 0.71);//Changes the node color purple
	double angle1=0.0;
	glBegin(GL_POLYGON);
	glVertex2d(oldx[i][0]-radius*cos(0.0),radius*sin(0.0)+oldx[i][1]);
	for(int j=0;j<360;j++){

	glVertex2d(oldx[i][0]-radius*cos(angle1),radius*sin(angle1)+oldx[i][1]);
	angle1+=angle;

	}
	glEnd();
	}

	for(int i=0;i<pointer;i++){
	glColor3f(0.93,0.93,0.93);// Node number color is changed
	int_str(nodenum,num);
	nodenum++;
	bitmap_output(oldx[i][0]-5,oldx[i][1]-6,num,GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

//This function prints text in graphics window
void bitmap_output(int x, int y, char *string, void *font)
{
  int len, i;
  glRasterPos2f(x, y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}

//this delays out execution of next instruction
void delay(){
int i=190000000;
while(i--);
}

//this function displays starting window
void frontpage()
{
	glLineWidth(2);
	glColor3f(1.0,0.2,0.4);//Color of Welcome to
	bitmap_output(width/3-50, height-height/10, "PRIM'S ALGORITHM VISUALIZATION",GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(0.93,0.93,0.93);//Welcome line color
	/*glBegin(GL_LINE_LOOP);
		glVertex2f(width/3+30, height-height/9);
		glVertex2f(width/3+240, height-height/9);
	glEnd();
	glColor3f(0.9,0.8,0.9);
	bitmap_output(width/3+10, height-height/6, "PRIM'S ALGORITHM VISUALIZATION",GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(0.9,0.8,0.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(width/3-10, height-height/5.5);
		glVertex2f(width/3+290, height-height/5.5);
	glEnd();*/
	glFlush();
	delay();
	glColor3f(0.03,0.85,0.84);
	bitmap_output(width/2+150, 125, "Press ENTER to Continue",GLUT_BITMAP_HELVETICA_18);
	glFlush();
	delay();
	glutPostRedisplay();
}

//this function displays text instructions in graphics window
void Instructions()
{
	glColor3f(1.0,0.34,0.13);
	bitmap_output(10, height-height/14, "Instructions",GLUT_BITMAP_TIMES_ROMAN_24);
	/*glColor3f(1.0,0.0,0.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(10, height-height/9);
		glVertex2f(130, height-height/9);
	glEnd();*/
	glColor3f(1.0,1.0,1.0);
	bitmap_output(10, height-height/7, "To Draw Nodes: Press N",GLUT_BITMAP_HELVETICA_18);
	bitmap_output(10,height-height/5, "To Draw Edges: Press E",GLUT_BITMAP_HELVETICA_18);
	bitmap_output(10, height-height/4, "Generate MST: Press D",GLUT_BITMAP_HELVETICA_18);
}
//this function draws edges using location stored in linex array
void drawline(){
	glColor3f(0.9f,1.0f,0.8f);
	glLineWidth(4.0);
	char* cst = new char[5];
	int temp;
	glBegin(GL_LINES);
	for(int i=0;i<lpointer;i++){
	glVertex2i(linex[i][0],linex[i][1]);
	glVertex2i(linex[i][2],linex[i][3]);
	}
	glEnd();
	glColor3f(0.0,1.0,0.0);
	for(int i=0;i<lpointer;i++){
		temp=costmatrix[lineundostack[i][0]][lineundostack[i][1]];
		sprintf(cst, "%d", temp);
		bitmap_output((linex[i][0]+linex[i][2])/2-15,(linex[i][1]+linex[i][3])/2+15,cst,GLUT_BITMAP_TIMES_ROMAN_24);
	}
	glFlush();
}

//this function does animation of lines connecting after calculating spanning tree
void blinking_lines(){
	delay();
	glLineWidth(7.0);
	for(int i=0;i<pointer-1;i++){
		glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);
	glVertex2i(oldx[t[i][0]][0],oldx[t[i][0]][1]);
	glVertex2i(oldx[t[i][1]][0],oldx[t[i][1]][1]);
	glEnd();
	delay();
	glFlush();
	 glutPostRedisplay();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2i(oldx[t[i][0]][0],oldx[t[i][0]][1]);
	glVertex2i(oldx[t[i][1]][0],oldx[t[i][1]][1]);
	delay();
	glEnd();
	/*int temp;
	char* cst = new char[5];
	glColor3f(0.0,1.0,0.0);
	for(int i=0;i<lpointer-1;i++){
		temp=costmatrix[t[i][0]][t[i][1]];
		itoa(temp,cst,10);
		bitmap_output((oldx[t[i][0]][0]+oldx[t[i][1]][0])/2-15,(oldx[t[i][0]][1]+oldx[t[i][1]][1])/2+8,cst,GLUT_BITMAP_TIMES_ROMAN_24);
	}*/
	glFlush();
	}
}

//this displays a point when mouse clicked for first time in draw edge mode
void drawPointAt(float x,float y){
	glPointSize(25);
	glColor3f(1.0,0.0,1.0);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();

}

//this function mimics loading animation
void loadpage(){
	delay();
	glLineWidth(40);
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINES);
	glVertex2d(100,300);
	glVertex2d(100+load,300);
	glEnd();
	load+=100;
	glFlush();
	glutPostRedisplay();
}

//this function displays text output after calculating spanning tree
void output(){
	glColor3f(0.0,1.0,0.0);
    int xaxis = 10,yaxis=550;
	bitmap_output(xaxis,yaxis,"Minimum Spanning Tree is",GLUT_BITMAP_HELVETICA_18);
	char* buffer=new char[50];
	char* cst = new char[50];
	char* a=new char[50];
	char* b = new char[50];
	for(int i=0;i<pointer-1;i++){
		sprintf(a, "%d", t[i][0]);
		strcat(a," -> ");
		sprintf(b, "%d", t[i][1]);
		strcat(a,b);
		sprintf(cst, "%d", costmatrix[t[i][0]][t[i][1]]);
		strcat(a," cost = ");
		strcat(a,cst);
		yaxis-=20;
		bitmap_output(xaxis,yaxis,a,GLUT_BITMAP_HELVETICA_18);
	}
	char sumchar[50];
	sprintf(buffer,"%d", totalcost);
	strcat(sumchar,"Spanning Tree Cost = ");
	strcat(sumchar,buffer);
	bitmap_output(xaxis,yaxis-20,sumchar,GLUT_BITMAP_HELVETICA_18);
}

//This is callback function called by OpenGL
void display(){
	nodenum=0;
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.13,0.16,0.19,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,width,0,height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(load<800 && found==0){
			glColor3f(1,1,1.0);
			bitmap_output(100,325,"LOADING",GLUT_BITMAP_HELVETICA_18);
		    loadpage();
		}
	else if(load<800 && found==1){
	        glColor3f(1,1,1.0);
			bitmap_output(100,325,"CALCULATING",GLUT_BITMAP_HELVETICA_18);
		    loadpage();
	}else{
	if(!enterpressed){
		glLineWidth(25);
		frontpage();
	}else if(enterpressed){
			if(!found){
				Instructions();
				glColor3f(0.31,0.8,0.64);
				bitmap_output(width-width/2+200,height-height/9,text,GLUT_BITMAP_HELVETICA_18);
	 		}
	       glPointSize(30);
		   drawpoint();
	       if(sx!=-1&&sy!=-1){
	       drawPointAt(sx,sy);
	      }
	      if(!found)
	      drawline();
	if(found){
	output();
	blinking_lines();
	}
	}
	}
	glFlush();
}

//this is reshape callback function called by OpenGL whenever window is resized
void reshape(int w, int h)
{
	width=w;
	height=h;
	glViewport(0, 0,(GLsizei) w,(GLsizei) h);
   glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	if(w<=h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h/ (GLfloat) w, 2.0* (GLfloat) h / (GLfloat) w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (GLfloat) w/ (GLfloat) h, 2.0* (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
}

//this function takes cost input from user during edge drawing
void input(){
	int posi=-1,posj=-1;
	int cost;
	int center_difference_error = 5;
	for(int i=0;i<pointer;i++){
		if(oldx[i][0]>=(linepoints[0][0]-center_difference_error)&&oldx[i][0]<=(linepoints[0][0]+center_difference_error)){
			if(oldx[i][1]>=(linepoints[0][1]-center_difference_error)&&oldx[i][1]<=(linepoints[0][1]+center_difference_error)){
		       posi=i;
			   break;}
	    }
	}
	for(int i=0;i<pointer;i++){
		if(oldx[i][0]>=(linepoints[1][0]-center_difference_error)&&oldx[i][0]<=(linepoints[1][0]+center_difference_error)){
			if(oldx[i][1]>=(linepoints[1][1]-center_difference_error)&&oldx[i][1]<=(linepoints[1][1]+center_difference_error)){
		       posj=i;
			break;
			}
	    }
	}
	if((posi==posj)||posi==-1||posj==-1){
		glColor3f(1.0,0.0,0.0);
		bitmap_output(20,50,"Invalid node",GLUT_BITMAP_HELVETICA_18);
		glFlush();
		delay();
		delay();
	lpointer--;
	}else{
	cout<<"Enter the cost:";
	cin>>cost;
	lineundostack[lpointer][0]=posi;
	lineundostack[lpointer][1]=posj;
	costmatrix[posi][posj]=costmatrix[posj][posi]=cost;
	}
}

//this is mouse callback function called by OpenGL whenever mouse event occurs
void mousefun(int button,int state,int x,int y){
	found=0;
	if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN){
		if(enterpressed){
		glLoadIdentity();
		float xp=(float)x;
		float yp=height-(float)y;

		if(point){
		oldx[pointer][0]=xp;
		oldx[pointer++][1]=yp;
		undostack[++upointer]='p';
		}

		if(line){
			if(f==0){
			linex[lpointer][0]=xp;
			linex[lpointer][1]=yp;
			f=1;
			linepoints[0][0]=sx=xp;
			linepoints[0][1]=sy=yp;
			}
			else{
			linex[lpointer][2]=linepoints[1][0]=xp;
			linex[lpointer][3]=linepoints[1][1]=yp;
			input();
			lpointer++;
			f=0;
			sx=sy=-1;
			undostack[++upointer]='l';
			}
		}
		glutPostRedisplay();
	  }
	}
}

//this function will print matrix constructed
void printmatrix(){
	for(int i=0;i<pointer;i++){
		for(int j=0;j<pointer;j++){
		cout<<costmatrix[i][j]<<"  ";
		}
		cout<<endl;
	}
}

//this checks if the graph is connected or not
bool isconnected(){
	int count;
	for(int i=0;i<pointer;i++){
	count=0;
	for(int j=0;j<pointer;j++){
	if(costmatrix[i][j]==999)count++;
	}
	if(count>=pointer-1){
		return false;
	}
	}
	return true;
}

//this undo the drawing in the order the graph was drawn
void undo(){
	if(pointer>0&&undostack[upointer--]=='p'){
			 pointer--;
			 undone++;
	} else if(lpointer>0){
			 lpointer--;
			 push(costmatrix[lineundostack[lpointer][0]][lineundostack[lpointer][1]]);
			 costmatrix[lineundostack[lpointer][0]][lineundostack[lpointer][1]]=999;
			 costmatrix[lineundostack[lpointer][1]][lineundostack[lpointer][0]]=999;
		     undone++;
	}
}

//this redo the drawing in the order the graph was drawn
void redo(){
	if(undone){
	      if(undostack[++upointer]=='p'){
					 pointer++;
					 undone--;
		   }
		 else{
			 int  cost=pop();
		     costmatrix[lineundostack[lpointer][0]][lineundostack[lpointer][1]]=cost;
			 costmatrix[lineundostack[lpointer][1]][lineundostack[lpointer][0]]=cost;
			 lpointer++;
             undone--;
		   }
       }
}

//this will call find_spanning_tree function if graph is connected
void find(){
	if(isconnected()){
		load=0;
		find_spanning_tree();
	 }
	else
	 {
		 	glColor3f(1.0,0.0,0.0);
		bitmap_output(30,20,"Graph is not connected",GLUT_BITMAP_HELVETICA_18);
		glFlush();
		delay();
		delay();
	//	cout<<"spanning tree doesn't exist"<<endl;
	 }
}

//this will select edge draw mode
void selectedge(){
     strcpy(text,"Mode: Edge");
	 line=1;
     point=0;
}

//this will select node draw mode
void selectnode(){
	strcpy(text,"Mode: Node");
    point=1;
	line=0;
}

//this is keyboard callback function called by OpenGL whenever keyboard event occurs
void keyboardfun(unsigned char key,int x,int y){
	sx=-1;sy=-1;
	switch(key){
	     case 13 :found=0;
			      enterpressed=true;
			      break;

		 case 'e':
		 case 'E':found=0;
			      selectedge();
			      break;
		 case 'N':
		 case 'n':found=0;
			      selectnode();
			      break;

		 case 'Z':
		 case 'z':found=0;
			      undo();
				  break;

		 case 'Y':
		 case 'y':found=0;
			      redo();
			      break;

		 case 'D':
		 case 'd':found=0;
			      find();
			      break;
		 case ' ':paused=!paused;
			      break;
		 case 27 :exit(0);
	}
		glutPostRedisplay();
}

//this is menu callback function called by OpenGL as menu function
void menu(int id){
	switch(id){
	case 0:find();
		   break;
	case 1:undo();
		   break;
    case 2:redo();
		   break;
    case 3://printmatrix();
		   break;
	case 4:point=1;
		   line=0;
		   strcpy(text,"Mode: Node");
		   break;
    case 5:point=0;
		   line=1;
		   strcpy(text,"Mode: Edge");
		   break;
	}
	glutPostRedisplay();

}

//this function calculates spanning tree using Prim's algorithm
void find_spanning_tree(){
	int k,u,v;
	int sum,min,source;
	int* p = new int[100];
	int* d = new int[100];
	int* s = new int[100];
	min=999;
	source=0;
	for(int i=0;i<pointer;i++){
	   for(int j=0;j<pointer;j++){
		   if(costmatrix[i][j]!=0 && costmatrix[i][j]<=min){
			   min=costmatrix[i][j];
			   source=i;
		   }
	}
	}

	for(int i=0;i<pointer;i++){
		d[i]=costmatrix[source][i];
		p[i]=source;
		s[i]=0;
	}
	s[source]=1;
	sum=0;
	k=0;
	for(int i=1;i<pointer;i++){
	min=999;
	u=-1;
	for(int j=0;j<pointer;j++){
		if(s[j]==0){
			if(d[j]<min){
			min=d[j];
			u=j;
			}
		}
	}
	if(u==-1)return;
	t[k][0]=u;
	t[k++][1]=p[u];
	sum=sum+costmatrix[u][p[u]];
	s[u]=1;
	for(v=0;v<pointer;v++){
		if(s[v]==0 && costmatrix[u][v]<d[v]){
		d[v]=costmatrix[u][v];
		p[v]=u;
		}
	}
	}
	if(sum>=999){
	cout<<"Spanning Tree Doesn't Exist\n";
	}else{
	totalcost=sum;
	found=1;
	}
}

//Program execution starts from here
int main(int argc,char** argv){
	for(int i=0;i<100;i++){
		for(int j=0;j<100;j++)
		if(i==j){
		costmatrix[i][j]=0;
		}
		else costmatrix[i][j]=999;
	}
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(250,50);
	glutInitWindowSize(width,height);
	glutCreateWindow("Prim's Algorithm Visualization");
	glutDisplayFunc(display);
	glutMouseFunc(mousefun);
	glutKeyboardFunc(keyboardfun);
	glutReshapeFunc(reshape);
	glutCreateMenu(menu);
	glutAddMenuEntry("Run",0);
	glutAddMenuEntry("Undo",1);
	glutAddMenuEntry("Redo",2);
	glutAddMenuEntry("Draw node",4);
	glutAddMenuEntry("Draw Edge",5);
	//glutAddMenuEntry("Print matrix",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}
