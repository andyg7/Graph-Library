#include <iostream>
#include <GL/glut.h>
#include <string>
#include <utility>
#include "soil/src/SOIL.h"
#include <unistd.h>
#include "8puzzle.h"
#include "board.h"
#include <vector>
#include <string>
using std::cout;
using std::endl;
using std::pair;
using std::make_pair;

Board board (3, 3);
unsigned int id[9] = {0,1,2,3,4,5,6,7,8};

int view_right;
int view_bottom;
int view_top;
int view_left;

void display()
{
	draw_initial_board();
	glutSwapBuffers();
}

void test(int values[])
{
	int index_x[9] = {0,1,2,0,1,2,0,1,2};
	int index_y[9] = {0,0,0,1,1,1,2,2,2};
	int i;
	for(int i=0;i<9;i++){
		glutDisplayFunc(display);
		fill_player(index_x[i],index_y[i],values[i]);
		display();
	}
}

int main(int argc, char *argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("8puzzle");
	init();    
	int final_values[2][9] ={ {1,0,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}};
	int j;

	test(final_values[0]);
	sleep(1);
	test(final_values[1]);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}



void fill_player(int x, int y, int dnumber) 
{
	unsigned int textureId;
	cout<<"X = "<<x<<"Y = "<<y<<"Dnumber"<<dnumber<<endl;
	switch(dnumber){
		case 0: textureId = id[0];break;
		case 1: textureId = id[1];break;
		case 2: textureId = id[2];break;
		case 3: textureId = id[3];break;
		case 4: textureId = id[4];break;
		case 5: textureId = id[5];break;
		case 6: textureId = id[6];break;
		case 7: textureId = id[7];break;
		case 8: textureId = id[8];break;  
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex2f(x * 30 + 5, (3 - y - 1) * 30 + 5);

	glTexCoord2f(1, 0);
	glVertex2f(x * 30 + 5 + 30, (3 - y - 1) * 30 + 5);

	glTexCoord2f(1, 1);
	glVertex2f(x * 30 + 5 + 30, (3 - y -1) * 30 + 5 + 30);

	glTexCoord2f(0, 1);
	glVertex2f(x * 30 + 5, (3 - y - 1)* 30 + 5 + 30);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

/******************************************************************************************/
/*nothign to look here*/
void draw_initial_board(void)
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	for (int i = 1; i < 3; i++) {
		glVertex2f(view_left + 5, i * 30 + 5);
		glVertex2f(view_right - 5, i * 30 + 5);

		glVertex2f(i * 30 + 5, view_bottom + 5);
		glVertex2f(i * 30 + 5, view_top - 5);
	}

	glEnd();
}


/*nothing to change here*/
void init(void)
{
	glClearColor(0.06, 0.06, 0.06, 0.0);

	glMatrixMode(GL_MODELVIEW);

	view_left = 0;
	view_right = 100;
	view_bottom = 0;
	view_top = 100;

	gluOrtho2D(view_left, view_right, view_bottom, view_top);
	glClear(GL_COLOR_BUFFER_BIT);
	if (!loadTexture("textures/0.jpg", &id[0])) {
		cout << "Unable to load blank" << endl;
	}
	if (!loadTexture("textures/1.jpg", &id[1])) {
		cout << "Unable to load 1" << endl;
	}
	if (!loadTexture("textures/2.jpg", &id[2])) {
		cout << "Unable to load 2" << endl;
	}
	if (!loadTexture("textures/3.jpg", &id[3])) {
		cout << "Unable to load 3" << endl;
	}
	if (!loadTexture("textures/4.jpg", &id[4])) {
		cout << "Unable to load 4" << endl;
	}
	if (!loadTexture("textures/5.jpg", &id[5])) {
		cout << "Unable to load 5" << endl;
	}
	if (!loadTexture("textures/6.jpg", &id[6])) {
		cout << "Unable to load 6" << endl;
	}
	if (!loadTexture("textures/7.jpg", &id[7])) {
		cout << "Unable to load 7" << endl;
	}
	if (!loadTexture("textures/8.jpg", &id[8])) {
		cout << "Unable to load 8" << endl;
	}
}


/*nothing to change here**/
bool loadTexture(char *filename, unsigned int *texture){
	*texture = SOIL_load_OGL_texture(filename,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA
			);
	if(*texture == 0){
		return false;
	} else {
		return true;
	}
}
