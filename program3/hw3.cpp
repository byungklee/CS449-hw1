#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

GLsizei winWidth = 600, winHeight = 600;

GLfloat xwcMin = 0.0, xwcMax = 225.0;
GLfloat ywcMin = 0.0, ywcMax = 225.0;

int gAngle = 0.0;


class wcPt2D {
public: 
	GLfloat x, y;
};

typedef GLfloat Matrix3x3 [3][3];

Matrix3x3 matComposite;

const GLdouble pi = 3.14159;

void init (void)
 {
 	glClearColor(1.0,1.0,1.0,0.0); 	
 }

//Construct the 3x3 identity matrix
 void matrix3x3SetIdentity(Matrix3x3 matIdent3x3) {
 	GLint row, col;

 	for ( row = 0; row < 3; row++) 
 		for ( col=0;col<3;col++)
 			matIdent3x3[row][col] = (row == col);
 } 


//Premultiply matrix m1 times and m2, store resut in m2.
 void matrix3x3PreMultiply (Matrix3x3 m1, Matrix3x3 m2) {
 	GLint row, col;
 	Matrix3x3 matTemp;

 	for(row = 0; row < 3; row++)
 		for(col=0;col<3;col++) 
 			matTemp[row][col] = m1[row][0] * m2[0][col] + m1[row][1]*m2[1][col]
 								+ m1[row][2] * m1[2][col];

 	for(row = 0; row < 3; row++)
		for(col=0;col<3;col++) 
			m2[row][col] =matTemp [row][col];

 }

 void translate2D (GLfloat tx, GLfloat ty) {
 	Matrix3x3 matTrans1;

 	matrix3x3SetIdentity (matTrans1);
 	matTrans1[0][2] = tx;
 	matTrans1[1][2] = ty;

 	matrix3x3PreMultiply (matTrans1, matComposite);
}

void rotate2D (wcPt2D pivotPt, GLfloat theta) {
	Matrix3x3 matRot;

	matrix3x3SetIdentity(matRot);

	matRot[0][0] = cos(theta);
	matRot[0][1] = -sin(theta);
	matRot[0][2] = pivotPt.x * (1 - cos(theta)) +
					pivotPt.y * sin(theta);
	matRot[1][0] = sin(theta);
	matRot[1][1] = cos(theta);
	matRot[1][2] = pivotPt.y * ( 1- cos (theta)) -
					pivotPt.x * sin(theta);

	matrix3x3PreMultiply (matRot, matComposite);
}

void scale2D (GLfloat sx, GLfloat sy, wcPt2D fixedPt)
{
	Matrix3x3 matScale;
	matrix3x3SetIdentity (matScale);

	matScale[0][0] = sx;
	matScale[0][2] = ( 1- sx) * fixedPt.x;
	matScale[1][1] = sy;
	matScale[1][2] = (1-sy) * fixedPt.y;

	matrix3x3PreMultiply (matScale, matComposite);


}

void transformVerts2D(GLint nVerts, wcPt2D *verts)
{
	GLint k;
	GLfloat temp;
	for(k=0;k<nVerts;k++) {
		temp = matComposite[0][0] * verts[k].x + matComposite[0][1] *
			verts [k].y + matComposite[0][2];
		verts[k].y = matComposite[1][0] * verts[k].x + matComposite[1][1] *
					verts[k].y + matComposite[1][2];
		verts[k].x = temp;		
	}
}

void triangle (wcPt2D *verts) {
	GLint k;

	glBegin(GL_TRIANGLES);
	for(k=0;k<3;k++) {
		glVertex2f(verts [k].x, verts[k].y);
	}
	glEnd();
}

void drawFrame() {
	glLineWidth(15);
	glColor3f(0,0,1);
	glBegin(GL_LINES);
		glVertex2f(70,95);
		glVertex2f(134,95);
		glVertex2f(132,98);
		glVertex2f(90,50);
		glVertex2f(90,50);
		glVertex2f(68,103);
		glVertex2f(60,104);
		glVertex2f(80,104);
	glEnd();
	glLineWidth(10);
	glBegin(GL_LINES);
		glVertex2f(70,95);
		glVertex2f(50,50);
		glVertex2f(132,103);
		glVertex2f(150,50);
		glVertex2f(122,103);
		glVertex2f(142,103);
		
	glEnd();
}

void drawRearGear() {
	//50,50
	glLineWidth(2);
	glColor3f(0.3,0.3,0.3);
	glBegin(GL_LINE_STRIP);
		//for(int i = 0; i <= 360; i = i + 10) {
		
		//}
		int counter = 0;
		int i = 3 * gAngle;
		while(counter != 37) {
			
		if(counter % 2 == 0) {
			glVertex2f(50 + 3 * cos(i*pi/180), 50 + 3 * sin(i*pi/180));
		}
		else
			glVertex2f(50 + 4 * cos(i*pi/180), 50 + 4 * sin(i*pi/180));	


		counter++;
		i = i + 10;
		}
	glEnd();
}

void drawFrontGear() {
glLineWidth(2);
glColor3f(0.3,0.3,0.3);
	glBegin(GL_LINE_STRIP);
		
		int counter = 0;
		int i = gAngle;
		while(counter != 37) {
			
		if(counter % 2 == 0) {
			glVertex2f(90 + 9 * cos(i*pi/180), 50 + 9 * sin(i*pi/180));
		}
		else
			glVertex2f(90 + 10 * cos(i*pi/180), 50 + 10 * sin(i*pi/180));	


		counter++;
		i = i + 10;
		}
	glEnd();
}

void drawChain() {
	glLineWidth(2);
	glColor3f(0.3,0.3,0.3);
	glBegin(GL_LINES);
	 glVertex2f(50,53);
	 glVertex2f(90,60);
	 glVertex2f(50,47);
	 glVertex2f(90,40);
	glEnd();
}

void drawWheel(wcPt2D *verts, int bigRadius, int currentAngle) {
	glLineWidth(3);
	glColor3f(0,0,0);
	glBegin(GL_LINE_STRIP);
		//for(int i = 0; i <= 360; i = i + 10) {
		
		//}
		int counter = 0;
		int i = currentAngle;
		while(counter != 37) {

		glVertex2f(verts[0].x + bigRadius * cos(i*pi/180), verts[0].y + bigRadius * sin(i*pi/180));
		counter++;
		i = i + 10;
		}
	glEnd();

	// glBegin(GL_POLYGON);
	// 	for(int i = 0; i <= 360; i = i + 10) {
	// 		glVertex2f(verts[0].x + 0.2 * bigRadius * cos(i*pi/180),
	// 				   verts[0].y + 0.2 * bigRadius * sin(i*pi/180));
	// 	}
	// glEnd();

	glLineWidth(5);
	glBegin(GL_LINES);
		glVertex2f(verts[0].x,verts[0].y);
		glVertex2f(verts[0].x + bigRadius * cos(currentAngle * pi/180),
					   verts[0].y + bigRadius * sin(currentAngle * pi/180));

		glVertex2f(verts[0].x,verts[0].y);
		glVertex2f(verts[0].x + bigRadius * cos((120 + currentAngle) * pi/180),
					   verts[0].y + bigRadius * sin((120 + currentAngle) * pi/180));

		glVertex2f(verts[0].x,verts[0].y);
		glVertex2f(verts[0].x + bigRadius * cos((240 + currentAngle) * pi/180),
					   verts[0].y + bigRadius * sin((240 + currentAngle) * pi/180));

	glEnd();
}

void displayFcn(void) {

	wcPt2D circle1[1] = {50,50};
	wcPt2D circle2[1] = {150,50};	

	GLfloat tx = 0.0, ty = 100.0;
	GLfloat sx = 1.5, sy = 1.5;
	GLdouble theta = pi/4.0;
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0,0.0,1.0);
	//triangle(verts);

	drawWheel(circle1, 30, 3*gAngle);
	drawWheel(circle2, 30, 3*gAngle);
	drawRearGear();

	gAngle = (gAngle - 1) % 360;
	glColor3f(1.0,0.0,0.0);
	//triangle(verts);
	drawFrame();
		drawFrontGear();
		drawChain();

	glFlush();
	glutPostRedisplay(); // make it animation! 

}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Program#3");
	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
	return 0;
}