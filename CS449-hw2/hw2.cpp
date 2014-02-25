/* simple painting program with text, lines, triangles,
rectangles, and points */


#define NULL 0
#define LINE 1
#define RECTANGLE 2
#define TRIANGLE 3
#define POINTS 4
#define TEXT 5
#define CIRCLE 6
#define JAGGED 7

#include <cstdlib>
#include <GL/glut.h> 
#include <iostream>
#include <math.h>

void mouse(int, int, int, int);
void key(unsigned char, int, int);
void display();
void drawSquare(int, int);
void drawPoint(int, int);
void myReshape(GLsizei, GLsizei);

void myinit();
void screen_box(int,int,int);
void screen_box_fill(int, int, int);
void right_menu(int);
void middle_menu(int);
void color_menu(int);
void pixel_menu(int);
void fill_menu(int);

int pick(int, int);

double getRadius(int,int,int,int);
void updateIconColor();
void defaultIcon();

/* globals */

GLsizei wh = 500, ww = 500; /* initial window size */
GLfloat size = 3.0;   /* half side length of square */
int draw_mode = 0; /* drawing mode */
int rx, ry; /*raster position*/

GLfloat r = 1.0, g = 1.0, b = 1.0; /* drawing color */
int fill = 0; /* fill flag */

void drawSquare(int x, int y)
{
  y=wh-y;
        //glColor3ub( (char) rand()%256, (char) rand()%256, (char) rand()%256);
  glColor3f(r,g,b);
  glBegin(GL_POLYGON);
  glVertex2f(x+size, y+size);
  glVertex2f(x-size, y+size);
  glVertex2f(x-size, y-size);
  glVertex2f(x+size, y-size);
  glEnd();
}

double getRadius(int x1, int y1, int x2, int y2)
{
  return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}


/* reshaping routine called whenever window is resized or moved */

void myReshape(GLsizei w, GLsizei h)
{

/* adjust clipping box */

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

/* adjust viewport and clear */

  glViewport(0,0,w,h);
  glClearColor (0.8, 0.8, 0.8, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  display();
  glFlush();

/* set global size for use by drawing routine */

  ww = w;
  wh = h;
}

void myinit()
{

  glViewport(0,0,ww,wh);


/* Pick 2D clipping window to match size of X window. This choice
avoids having to scale object coordinates each time window is
resized. */

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(0.0, (GLdouble) ww , 0.0, (GLdouble) wh , -1.0, 1.0);

/* set clear color to black and clear window */

glClearColor (0.8, 0.8, 0.8, 1.0);
glClear(GL_COLOR_BUFFER_BIT);
glFlush();
}

void drawPoint(int x,int y)
{
  glPointSize(1);
  glBegin(GL_POINTS);
  glVertex2f(x,wh-y);
  glEnd();
  glFlush();
}

void mouse(int btn, int state, int x, int y)
{
  std::cout << "MOUSE OPERATION: " << btn << " " << state << std::endl;
  static int count;
  int where;
  static int xp[2],yp[2];
  if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
  {

   glPushAttrib(GL_ALL_ATTRIB_BITS);
   where = pick(x,y);
   glColor3f(r, g, b);
   if(where != 0)
   {
    count = 0;
    draw_mode = where;
    updateIconColor();
    glFlush();
  }
  else switch(draw_mode)
  { 
   case(CIRCLE):
   std::cout << "CIRCLE" << std::endl;
   if(count==0)
   {
    count++;
    xp[0] = x;
    yp[0] = y;
    drawPoint(x,y);
  }
  else
  {
    double r = getRadius(x,y,xp[0],yp[0]);
    if(fill)glBegin(GL_POLYGON);
    else glBegin(GL_LINE_LOOP);
    for(int i=0;i<360; i = i + 10) {
      glVertex2f(xp[0] + r*cos(i*3.14/180), wh-yp[0]+r*sin(i * 3.14/180));
    }
    glEnd();
    draw_mode =0;
    count = 0;
  }

  break;
  case(LINE):
  if(count==0)
  {
    count++;
    xp[0] = x;
    yp[0] = y;
    drawPoint(x,y);

  }
  else
  {
    glBegin(GL_LINES);
    glVertex2i(x,wh-y);
    glVertex2i(xp[0],wh-yp[0]);
    glEnd();
    draw_mode=0;
    count=0;
  }
  break;
  case(RECTANGLE):
  if(count == 0)
  {
    count++;
    xp[0] = x;
    yp[0] = y;
    drawPoint(x,y);
  }
  else
  {
    if(fill) glBegin(GL_POLYGON);
    else glBegin(GL_LINE_LOOP);
    glVertex2i(x, wh-y);
    glVertex2i(x, wh-yp[0]);
    glVertex2i(xp[0]+1,wh-yp[0]+1);
    glVertex2i(xp[0],wh-y);
    glEnd();
    draw_mode=0;
    count=0;
  }
  break;
  case (TRIANGLE):
  switch(count)
  {
    case(0):
    count++;
    xp[0] = x;
    yp[0] = y;
    drawPoint(x,y);
    break;
    case(1):
    count++;
    xp[1] = x;
    yp[1] = y;
    drawPoint(x,y);
    break;
    case(2):
    if(fill) glBegin(GL_POLYGON);
    else glBegin(GL_LINE_LOOP);
    glVertex2i(xp[0],wh-yp[0]);
    glVertex2i(xp[1],wh-yp[1]);
    glVertex2i(x,wh-y);
    glEnd();
    draw_mode=0;
    count=0;
  }
  break;
  case(POINTS):
  {
   drawSquare(x,y);
   count++;
 }      
 break;
 case(TEXT):
 {
  rx=x;
  ry=wh-y;  
  glRasterPos2i(rx,ry);
  count=0;
  break;
}
case(JAGGED): 
{   
  std::cout << "JAGGED " << std::endl;
  if(count == 0) {
    count++;
    xp[0] = x;
    yp[0] = y;
    drawPoint(x,y);
  }
  else {
    if(x == xp[0] && y == yp[0]) {
      count = 0;
      draw_mode = 0;
    }  
    else {
      glBegin(GL_LINES);
      glVertex2i(xp[0],wh-yp[0]);
      glVertex2i(x,wh-y);
      glEnd();
      xp[0]=x;
      yp[0]=y;
    }
  }
  break;
}

}

  glPopAttrib();  
  glFlush();
  }
  if(draw_mode == 0) {
    defaultIcon();
  }
}

int pick(int x, int y)
{
  y = wh - y;
  if(y < wh-ww/10) 
  {
    return 0;
  }
  else if(x < 1*ww/10) 
  {
    defaultIcon();
    glColor3f(0.9,0.9,1.0);
    screen_box_fill(0,wh-ww/10,ww/10);
    return CIRCLE;
  }
  else if(x < 2*ww/10) {
    defaultIcon();
    glColor3f(0.9,0.9,1.0);
    screen_box_fill(ww/10,wh-ww/10,ww/10);    
    return LINE;
  }
  else if(x < 3*ww/10) {    
    defaultIcon();
    glColor3f(0.9,0.9,1.0);
    screen_box_fill(2*ww/10,wh-ww/10,ww/10);
    return RECTANGLE;
  }
  else if(x < 4*ww/10) {    
    defaultIcon();
    glColor3f(0.9,0.9,1.0);
    screen_box_fill(3*ww/10,wh-ww/10,ww/10);    
    return TRIANGLE;
  }
  else if(x < 5*ww/10) {
    defaultIcon();
    glColor3f(0.9,0.9,1.0);
    screen_box_fill(4*ww/10,wh-ww/10,ww/10);    
    return POINTS;
  }
  else if(x < 6*ww/10) {     
    defaultIcon();
    glColor3f(0.9,0.9,1.0);
    screen_box_fill(5*ww/10,wh-ww/10,ww/10);    
    return TEXT;
  }
  else if(x < 7*ww/10) {    
    defaultIcon();
    glColor3f(0.9,0.9,1.0);
    screen_box_fill(6*ww/10,wh-ww/10,ww/10);    
    return JAGGED;
  }
  else return 0;
}

void screen_box(int x, int y, int s )
{
  glBegin(GL_LINE_LOOP);
  glVertex2i(x, y);
  glVertex2i(x+s, y);
  glVertex2i(x+s, y+s);
  glVertex2i(x, y+s);
  glEnd();
}
void screen_box_fill(int x, int y, int s )
{
  s= s-1;
  glBegin(GL_QUADS);
  glVertex2i(x, y);
  glVertex2i(x+s, y);
  glVertex2i(x+s, y+s);
  glVertex2i(x, y+s);
  glEnd();
}

void right_menu(int id)
{
 if(id == 1) exit(0);
 else display();
}

void middle_menu(int id)
{

}

void defaultIcon() {
  int shift = 0;
  //First icon
  glColor3f(0.8,0.8,0.8);
  screen_box_fill(0,wh-ww/10,7*ww/10);
  glColor3f(1.0,1.0,1.0);
  screen_box(0,wh-ww/10,ww/10);
    //Second icon
    //glColor3f(1.0, 0.0, 0.0);
  screen_box(ww/10,wh-ww/10,ww/10);
    //Third icon
    //glColor3f(0.0, 1.0, 0.0);
  screen_box(ww/5,wh-ww/10,ww/10);
    //Fourth icon
    //glColor3f(0.0, 0.0, 1.0);
  screen_box(3*ww/10,wh-ww/10,ww/10);
    //Fifth icon
    //glColor3f(1.0, 1.0, 0.0);
  screen_box(2*ww/5,wh-ww/10,ww/10);
    //Sixth icon
    //glColor3f(0.0, 1.0, 1.0);
  screen_box(5*ww/10,wh-ww/10,ww/10);
    //Seventh icon
    //glColor3f(1.0, 0.0, 1.0);
  screen_box(6*ww/10,wh-ww/10,ww/10);

    //Circle  
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_POLYGON);
  for(int i=0;i<360; i = i + 10) {
    glVertex2f(ww/10*0.5 + ww/10*0.3* cos(i*3.14/180),wh-ww/20 + ww/10*0.3*sin(i * 3.14/180));
  }
  glEnd();

    //Line Icon
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
       //glVertex2i(ww/40,wh-ww/20);
  glVertex2i(ww/10 + ww/10*0.2,wh-ww/20);
  glVertex2i(ww/10 + ww/10*0.8,wh-ww/20);
    //  glVertex2i(ww/40+ww/20,wh-ww/20);
  glEnd();

    //Square Icon x,y,size
  screen_box_fill(2*ww/10 + ww/10*0.3,wh-ww/10+ww/40,ww/25);

    //Triangle Icon
  glBegin(GL_TRIANGLES);
  glVertex2i(3*ww/10+ww/40,wh-ww/10+ww/40);
  glVertex2i(3*ww/10+ww/20,wh-ww/40);
  glVertex2i(3*ww/10+3*ww/40,wh-ww/10+ww/40);
  glEnd();

    //Point Icon
  glPointSize(3.0);
  glBegin(GL_POINTS);
  glVertex2i(4*ww/10+ww/20, wh-ww/20);
  glEnd();     

  glRasterPos2i(5*ww/10,wh-ww/20);
  glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');
  shift=glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'A');
  glRasterPos2i(5*ww/10+shift,wh-ww/20);
  glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'B');
  shift+=glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'B');
  glRasterPos2i(5*ww/10+shift,wh-ww/20);
  glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');

    //JAGGED LINE ICON
  glBegin(GL_LINE_STRIP);
  glVertex2i(6*ww/10+2*ww/100, wh-ww/20);
  glVertex2i(6*ww/10+4*ww/100, wh-ww/20 - 4 * ww/100);
  glVertex2i(6*ww/10+6*ww/100, wh-ww/20 + 4 * ww/100);
  glVertex2i(6*ww/10+8*ww/100, wh-ww/20);
  glEnd();
  glFlush();
}

void updateIconColor() {
  std::cout << "Updateing ICON COLOR" << std::endl;  
  glColor3f(r, g, b);
  if(draw_mode==LINE) {
    
   glBegin(GL_LINES);
       //glVertex2i(ww/40,wh-ww/20);
   glVertex2i(ww/10 + ww/10*0.2,wh-ww/20);
   glVertex2i(ww/10 + ww/10*0.8,wh-ww/20);
    //  glVertex2i(ww/40+ww/20,wh-ww/20);
   glEnd();
 }
 else if(draw_mode==RECTANGLE) 
 {
   screen_box_fill(2*ww/10 + ww/10*0.3,wh-ww/10+ww/40,ww/25);
   
 }
 else if(draw_mode==TRIANGLE) 
 {
   glBegin(GL_TRIANGLES);
   glVertex2i(3*ww/10+ww/40,wh-ww/10+ww/40);
   glVertex2i(3*ww/10+ww/20,wh-ww/40);
   glVertex2i(3*ww/10+3*ww/40,wh-ww/10+ww/40);
   glEnd();
}  
  else if(draw_mode==POINTS) 
  {
    glPointSize(3.0);
    glBegin(GL_POINTS);
    glVertex2i(4*ww/10+ww/20, wh-ww/20);
    glEnd();     
  }
  else if(draw_mode==TEXT) 
  {
    int shift=0;
    glRasterPos2i(5*ww/10,wh-ww/20);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');
    shift=glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'A');
    glRasterPos2i(5*ww/10+shift,wh-ww/20);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'B');
    shift+=glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'B');
    glRasterPos2i(5*ww/10+shift,wh-ww/20);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
  }
  else if(draw_mode==CIRCLE) 
  {
    glBegin(GL_POLYGON);
    for(int i=0;i<360; i = i + 10) {
      glVertex2f(ww/10*0.5 + ww/10*0.3* cos(i*3.14/180),wh-ww/20 + ww/10*0.3*sin(i * 3.14/180));
    }
    glEnd();       

  }
  else if(draw_mode==JAGGED) 
  {
    glBegin(GL_LINE_STRIP);
    glVertex2i(6*ww/10+2*ww/100, wh-ww/20);
    glVertex2i(6*ww/10+4*ww/100, wh-ww/20 - 4 * ww/100);
    glVertex2i(6*ww/10+6*ww/100, wh-ww/20 + 4 * ww/100);
    glVertex2i(6*ww/10+8*ww/100, wh-ww/20);
    glEnd();
  }
  glFlush();
}

void color_menu(int id)
{
   if(id == 1) {r = 1.0; g = 0.0; b = 0.0;} //RED
   else if(id == 2) {r = 0.0; g = 1.0; b = 0.0;} //Green
   else if(id == 3) {r = 0.0; g = 0.0; b = 1.0;} //Blue
   else if(id == 4) {r = 0.0; g = 1.0; b = 1.0;} // 
   else if(id == 5) {r = 1.0; g = 0.0; b = 1.0;} //
   else if(id == 6) {r = 1.0; g = 1.0; b = 0.0;} // 
   else if(id == 7) {r = 1.0; g = 1.0; b = 1.0;} // White 
   else if(id == 8) {r = 0.0; g = 0.0; b = 0.0;} // Black
   
   updateIconColor();
   glFlush();

 }

 void pixel_menu(int id)
 {
   if (id == 1) size = 2 * size;
   else if (size > 1) size = size/2;
 }

 void fill_menu(int id)
 {
   if (id == 1) fill = 1;
   else fill = 0;
 }

 void key(unsigned char k, int xx, int yy) 
 {
   if(draw_mode!=TEXT) {
    std:: cout << "KEY: " << k << std::endl;
    switch(k) {        
      case('r'):
      color_menu(1);
      break;
      case('g'):
      color_menu(2);
      break;
      case('b'):
      std:: cout << "CASE B" << std::endl;
      color_menu(3);
      break;
      case('y'):
      color_menu(6);
      break;
      case('c'):
      color_menu(4);
      break;
      case('m'):
      color_menu(5);
      break;
      case('w'):
      color_menu(7);
      break;
      case('k'):
      color_menu(8);
      break;
    }
    return;
  }

  else {
   glColor3f(r,g,b);
   glRasterPos2i(rx,ry);
   glutBitmapCharacter(GLUT_BITMAP_9_BY_15, k);
   /*glutStrokeCharacter(GLUT_STROKE_ROMAN,i); */
   rx+=glutBitmapWidth(GLUT_BITMAP_9_BY_15,k);
 }

}

void display()
{
  int shift=0;
  glPushAttrib(GL_ALL_ATTRIB_BITS);
   glClearColor (0.8, 0.8, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

  //First icon
  glColor3f(1.0,1.0,1.0);
  screen_box(0,wh-ww/10,ww/10);
    //Second icon
    //glColor3f(1.0, 0.0, 0.0);
  screen_box(ww/10,wh-ww/10,ww/10);
    //Third icon
    //glColor3f(0.0, 1.0, 0.0);
  screen_box(ww/5,wh-ww/10,ww/10);
    //Fourth icon
    //glColor3f(0.0, 0.0, 1.0);
  screen_box(3*ww/10,wh-ww/10,ww/10);
    //Fifth icon
    //glColor3f(1.0, 1.0, 0.0);
  screen_box(2*ww/5,wh-ww/10,ww/10);
    //Sixth icon
    //glColor3f(0.0, 1.0, 1.0);
  screen_box(5*ww/10,wh-ww/10,ww/10);
    //Seventh icon
    //glColor3f(1.0, 0.0, 1.0);
  screen_box(6*ww/10,wh-ww/10,ww/10);

    //Circle  
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_POLYGON);
  for(int i=0;i<360; i = i + 10) {
    glVertex2f(ww/10*0.5 + ww/10*0.3* cos(i*3.14/180),wh-ww/20 + ww/10*0.3*sin(i * 3.14/180));
  }
  glEnd();

    //Line Icon
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
       //glVertex2i(ww/40,wh-ww/20);
  glVertex2i(ww/10 + ww/10*0.2,wh-ww/20);
  glVertex2i(ww/10 + ww/10*0.8,wh-ww/20);
    //  glVertex2i(ww/40+ww/20,wh-ww/20);
  glEnd();

    //Square Icon x,y,size
  screen_box_fill(2*ww/10 + ww/10*0.3,wh-ww/10+ww/40,ww/25);

    //Triangle Icon
  glBegin(GL_TRIANGLES);
  glVertex2i(3*ww/10+ww/40,wh-ww/10+ww/40);
  glVertex2i(3*ww/10+ww/20,wh-ww/40);
  glVertex2i(3*ww/10+3*ww/40,wh-ww/10+ww/40);
  glEnd();

    //Point Icon
  glPointSize(3.0);
  glBegin(GL_POINTS);
  glVertex2i(4*ww/10+ww/20, wh-ww/20);
  glEnd();     

  glRasterPos2i(5*ww/10,wh-ww/20);
  glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');
  shift=glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'A');
  glRasterPos2i(5*ww/10+shift,wh-ww/20);
  glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'B');
  shift+=glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'B');
  glRasterPos2i(5*ww/10+shift,wh-ww/20);
  glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');

    //JAGGED LINE ICON
  glBegin(GL_LINE_STRIP);
  glVertex2i(6*ww/10+2*ww/100, wh-ww/20);
  glVertex2i(6*ww/10+4*ww/100, wh-ww/20 - 4 * ww/100);
  glVertex2i(6*ww/10+6*ww/100, wh-ww/20 + 4 * ww/100);
  glVertex2i(6*ww/10+8*ww/100, wh-ww/20);
  glEnd();
  glFlush();
  glPopAttrib();
}

int main(int argc, char** argv)
{
  int c_menu, p_menu, f_menu;
  glutInit(&argc,argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("square");
  glutDisplayFunc(display);
  c_menu = glutCreateMenu(color_menu);
  glutAddMenuEntry("Red",1);
  glutAddMenuEntry("Green",2);
  glutAddMenuEntry("Blue",3);
  glutAddMenuEntry("Cyan",4);
  glutAddMenuEntry("Magenta",5);
  glutAddMenuEntry("Yellow",6);
  glutAddMenuEntry("White",7);
  glutAddMenuEntry("Black",8);
  p_menu = glutCreateMenu(pixel_menu);
  glutAddMenuEntry("increase pixel size", 1);
  glutAddMenuEntry("decrease pixel size", 2);
  f_menu = glutCreateMenu(fill_menu);
  glutAddMenuEntry("fill on", 1);
  glutAddMenuEntry("fill off", 2);
  glutCreateMenu(right_menu);
  glutAddMenuEntry("quit",1);
  glutAddMenuEntry("clear",2);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutCreateMenu(middle_menu);
  glutAddSubMenu("Colors", c_menu);
  glutAddSubMenu("Pixel Size", p_menu);
  glutAddSubMenu("Fill", f_menu);
  glutAttachMenu(GLUT_MIDDLE_BUTTON);
  myinit ();
  glutReshapeFunc (myReshape);
  glutKeyboardFunc(key);
  glutMouseFunc (mouse);
  glutMainLoop();
}