#include <iostream>
#include <math.h>
using namespace std;


//3D Vector
struct vector {
	int x;
	int y;
	int z;	
};


bool isItConcave(vector* vt, int index);
bool isInsideACube(vector*,int index, vector);

bool isItConcave(vector* vt, int index) {
	bool isItCon = false;
	for(int i = 0;i<index;i++) {
		int nextIndex;
		if(i + 1 == index) 
			nextIndex = 0;
		else
			nextIndex = i + 1;

		int crossProductX = vt[i].y * vt[nextIndex].z - vt[i].z * vt[nextIndex].y;
		int crossProductY = (vt[i].x * vt[nextIndex].z - vt[i].z * vt[nextIndex].x) * -1;
		int crossProductZ = vt[i].x * vt[nextIndex].y - vt[i].y * vt[nextIndex].x;

		cout << "i:" << crossProductX << " j:" << crossProductY << " k:" << crossProductZ << endl;
		if(crossProductZ < 0) {
			isItCon = true;
		}
	}
	return isItCon;

}

//if the point is in range of each coordinates for cube, the point is in the cube.
//calculating 4 vectors. 
//find 4 points corresponding the target point
//if the target is in bound of 4 points, it's in, else it's not.
// creating size 2 cube
// two points (1,1,1) (3,3,3)
bool isInsideACube(vector* co,int index, vector point) {
	if(co[0].x <= point.x && co[1].x >= point.x &&
	   co[0].y <= point.y && co[4].y >= point.y &&
	   co[0].z <= point.z && co[7].z >= point.z)
		return true;
	return false;
}

int main(int argc, char** argv) {
	
vector coordinates[8];
coordinates[0].x = 0;
coordinates[0].y = 0;
coordinates[0].z = 0;

coordinates[1].x = 2;
coordinates[1].y = 0;
coordinates[1].z = 0;

coordinates[2].x = 2;
coordinates[2].y = 0;
coordinates[2].z = 2;

coordinates[3].x = 0;
coordinates[3].y = 0;
coordinates[3].z = 2;

coordinates[4].x = 0;
coordinates[4].y = 2;
coordinates[4].z = 0;

coordinates[5].x = 2;
coordinates[5].y = 2;
coordinates[5].z = 0;

coordinates[6].x = 2;
coordinates[6].y = 2;
coordinates[6].z = 2;

coordinates[7].x = 0;
coordinates[7].y = 2;
coordinates[7].z = 2;

vector point1, point2;
point1.x = 1;
point1.y = 1;
point1.z = 1;

point2.x = 3;
point2.y = 3;
point2.z = 3;

cout << isInsideACube(coordinates,8,point1) << endl;
cout << isInsideACube(coordinates,8,point2) << endl;








//Problem 4.18
	//Vectors E
	vector vt[6];
	vt[0].x =1;
	vt[0].y =0;
	vt[0].z =0;

	vt[1].x =1;
	vt[1].y =1;
	vt[1].z =0;

	vt[2].x =1;
	vt[2].y =-1;
	vt[2].z =0;

	vt[3].x =0;
	vt[3].y =2;
	vt[3].z =0;

	vt[4].x =-3;
	vt[4].y =0;
	vt[4].z =0;

	vt[5].x =0;
	vt[5].y =-2;
	vt[5].z =0;

	cout << "this vector set is " << (isItConcave(vt,6) == true ? "concave" : "not concave") << endl;
	
}