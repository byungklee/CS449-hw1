#include <GL/glut.h>
#include <iostream>

GLsizei winWidth = 500, winHeight =500;
GLfloat xComplexMin = -2.00, xComplexMax = 0.50;
GLfloat yComplexMin = -1.25, yComplexMax = 1.25;

GLfloat complexWidth = xComplexMax - xComplexMin;
GLfloat complexHeight = yComplexMax - yComplexMin;

class complexNum {
public:
	GLfloat x,y;
};

struct color { GLfloat r,g,b,;};
void init(void)
{
	glClearColor (1.0,1.0,1.0,0.0);
	glEnable(GL_COLOR_LOGIC_OP);
}

void plotPoint (complexNum z) {
	glBegin(GL_POINTS);
		glVertex2f(z.x,z.y);
	glEnd();
}

complexNum complexSquare(complexNum z) {
	complexNum zSquare;
	zSquare.x = z.x * z.x - z.y * z.y;
	zSquare.y = 2 * z.x * z.y;
	return zSquare;	
}

GLint mandelSqTransf(complexNum z0, GLint maxIter) {
	complexNum z= z0;
	GLint count = 0;
	while((z.x*z.x+z.y*z.y <= 4.0) && (count < maxIter)) {
		z = complexSquare(z);
		z.x += z0.x;
		z.y += z0.y;
		count++;
	}
	return count;
}

void mandelbrot ( GLint nx, GLint ny, GLint maxIter ) {
	complexNum z, zIncr;
	color ptColor;
	GLint iterCount;

	zIncr.x = complexWidth /GLfloat(nx);
	zIncr.y = complexHeight /GLfloat(ny);

	for (z.x = xComplexMin; z.x < xComplexMax;z.x+=zIncr.x) {
		for(z.y = yComplexMin; z.y < yComplexMax; z.y += zIncr.y) {
			iterCount = mandelSqTransf(z,maxIter);
			if(iterCount >= maxIter) {
				ptColor.g = ptColor.b = 0.0;
				ptColor.r = 1;
			} else if( iterCount > (maxIter / 10)) {
					ptColor.r = ptColor.g = ptColor.b = 0.1;
					ptColor.r = 0.5;
			} else if(iterCount > (maxIter / 20)) {
				ptColor.r = ptColor.g = ptColor.b = 0.2;
				ptColor.g =1;
			} else if (iterCount > (maxIter/30)) {
				ptColor.r = ptColor.g = ptColor.b = 0.3;
				ptColor.b =1;
			} else if (iterCount > (maxIter/40)) {
				ptColor.r = ptColor.g = ptColor.b = 0.4;
				ptColor.g = 0.4;
			}else if (iterCount > (maxIter/50)) {
				ptColor.r = ptColor.g = ptColor.b = 0.5;
				ptColor.b = 0.7;
			}else if (iterCount > (maxIter/60)) {
				ptColor.b = 0.6;
				ptColor.r = 0;
				ptColor.g = 0.3;
			}else if (iterCount > (maxIter/70)) {
				ptColor.r = ptColor.g = ptColor.b = 0.7;
				ptColor.r = 0.4;
			}else if (iterCount > (maxIter/80)) {
				ptColor.r = ptColor.g = ptColor.b = 0.8;
				ptColor.g = 0.2;
			}else {
				ptColor.r = ptColor.g = ptColor.b = 1;

			}
			glColor3f(ptColor.r, ptColor.g, ptColor.b);
			plotPoint(z);

 		}
	}
		
}

void displayFcn(void) {
	GLint nx =1000, ny=1000, maxIter=1000;
	glClear(GL_COLOR_BUFFER_BIT);
	mandelbrot(nx,ny,maxIter);
	
	glFlush();	
}

void winReshapeFcn (GLint newWidth, GLint newHeight) {
	glViewport(0,0, newHeight, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D (xComplexMin, xComplexMax, yComplexMin, yComplexMax);
	glClear(GL_COLOR_BUFFER_BIT);
}
//glOrtho( -width/2*zoom, width/2*zoom, -height/2*zoom, height/2*zoom, -1, 1 );
int zoom = 4;

//GLfloat xComplexMin = -2.00, xComplexMax = 0.50;
//GLfloat yComplexMin = -1.25, yComplexMax = 1.25;
int first =0;
float mx,my,mmx,mmy;
void mouse(int button, int state, int x, int y) {
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			std::cout << "eher" <<std::endl;
			mx=x;
			my=500-y;
			glColor3f(0.0,0.0,1.0);
			glLogicOp(GL_XOR);
			first = 0;
	}else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			
			
	}if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
			std::cout << "eher" <<std::endl;
			glScalef(2,2,2);
			displayFcn();
			glFlush();
	}
}
void move(int x,int y) {
	if(first == 1) {
		glRectf(xm,ym,xmm,ymm)
		glFlush();
	}
	xmm = x;
	ymm = 500 -y;
	glRectf(xm,ym,xxm,ymm);
	glFlush();
	first = 1;
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("MANDELBROT SET");
	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMouseFunc(mouse);
	glutMotionFunc(move);
	glutMainLoop();

	return 0;
}
