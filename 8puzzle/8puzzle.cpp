#include <iostream>
#include <GL/glut.h>
#include <string>
#include <utility>
#include "soil/src/SOIL.h"
#include <unistd.h>
#include "8puzzle.h"
#include "board.h"

using std::cout;
using std::endl;
using std::pair;
using std::make_pair;

//typedef pair<int, int> pii;

Board board (3, 3);
int view_left, view_bottom, view_right, view_top;
int current_player = 1;
int state = 1;
unsigned int crossId = 1;
unsigned int oId = 2;
bool againstComputer = false;

void display(void)
{
    fill_board();
    draw_initial_board();

//    if (winner != 0) {
//        display_win(winner);
//    } else if (find_valid_moves(current_player).size() == 0) {
//        display_win(0);
//    }
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Tic Tac Toe");
    init();    
//    glutMouseFunc(process_mouse);
    int x = 100, y = 400;
    int i = (y / 500.0 * 100 - 5) / 30;
    int j = (x / 500.0 * 100 - 5) / 30;

//int k=2;
//while(k){


//     x = 100, y = 100;
//     i = (y / 500.0 * 100 - 5) / 30;
//     j = (x / 500.0 * 100 - 5) / 30;
//  if ( board.getXY(i, j) == 0) {
     //sleep(60);
move_player(i, j);
//fill_player(i,j,1);
sleep(1);

     x = 200, y = 200;
     i = (y / 500.0 * 100 - 5) / 30;
     j = (x / 500.0 * 100 - 5) / 30;



fill_player(i,j,2);
     move_player(i, j);

//k--;
//}

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}


void move_player(int i, int j)
{
//    board.setXY(i, j, 1/*current_player*/);
    board.setXY(i, j, 2/*current_player*/);
    display();
}

/*look here*/
void fill_board(void)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board.getXY(i, j) == 0) {
                continue;
            } else {
                fill_player(j, i, 1 /*board.getXY(i, j)*/);
                fill_player(j, i , 2);
            }
        }
    }
}

/*look here*/
void fill_player(int x, int y, int player) 
{
    unsigned int textureId;

    if (player == 1) {
        textureId = crossId;
    } else {
        textureId = oId;
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
    if (!loadTexture("textures/2.jpg", &crossId)) {
        cout << "Unable to load cross" << endl;
    }
    if (!loadTexture("textures/1.jpg", &oId)) {
        cout << "Unable to load o" << endl;
    }
}

void reset_board(void)
{
    state = 1;
    current_player = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board.setXY(i, j, 0);
        }
    }
    glColor3f(0.06, 0.06, 0.06);
    glBegin(GL_POLYGON);
        glVertex2f(view_left, view_bottom);
        glVertex2f(view_right, view_bottom);
        glVertex2f(view_right, view_top);
        glVertex2f(view_left, view_top);
    glEnd();

    display();
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
