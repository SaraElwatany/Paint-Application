#include <iostream>
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include<GL\glu.h>
#include<GL\glut.h>
#include<math.h>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono;
using namespace std::this_thread;
int rectCount, lineCount, cirleCount , triangleCount, squareCount;
GLfloat R, px, py,scx, scy;

void Line(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    GLfloat M, p, dx, dy, x, y, t;

    if ((x2 - x1) == 0)
        M = (y2 - y1);
    else
        M = (y2 - y1) / (x2 - x1);

    if (fabs(M) < 1)
    {
        if (x1 > x2)
        {
            t = x1;
            x1 = x2;
            x2 = t;

            t = y1;
            y1 = y2;
            y2 = t;
        }

        dx = fabs(x2 - x1);
        dy = fabs(y2 - y1);

        p = 2 * dy - dx;

        x = x1;
        y = y1;

        glBegin(GL_POINTS);
        while (x <= x2)
        {
            glVertex2f(x, y);
            x = x + 1;

            if (p >= 0)
            {
                if (M < 1)
                    y = y + 1;
                else
                    y = y - 1;
                p = p + 2 * dy - 2 * dx;
            }
            else
            {
                y = y;
                p = p + 2 * dy;
            }
        }
        glEnd();
    }

    if (fabs(M) >= 1)
    {
        if (y1 > y2)
        {
            t = x1;
            x1 = x2;
            x2 = t;

            t = y1;
            y1 = y2;
            y2 = t;
        }

        dx = fabs(x2 - x1);
        dy = fabs(y2 - y1);

        p = 2 * dx - dy;

        x = x1;
        y = y1;

        glBegin(GL_POINTS);
        while (y <= y2)
        {
            glVertex2f(x, y);
            y = y + 1;

            if (p >= 0)
            {
                if (M >= 1)
                    x = x + 1;
                else
                    x = x - 1;
                p = p + 2 * dx - 2 * dy;
            }
            else
            {
                x = x;
                p = p + 2 * dx;
            }
        }
        glEnd();
    }

    glFlush();
}

// Draw Square Function
void DrawRectangle()
{
    glClear(GL_COLOR_BUFFER_BIT);
    GLfloat x1 = 350, y1 = 30, x2 = 350, y2 = 200, x3 = 400, y3 = 30, x4 = 400, y4 = 200;
    Line(x1, y1, x2, y2);
    Line(x1, y1, x3, y3);
    Line(x3, y3, x4, y4);
    Line(x2, y2, x4, y4);

}


void DrawLine()
{
    glClear(GL_COLOR_BUFFER_BIT);
    GLfloat x1 = 350, y1 = 30, x2 = 350, y2 = 400;
    Line(x1, y1, x2, y2);

}


//Draw Rectangle Function
void DrawSquare() {
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat x1 = 300, y1 = 200, x2 = 400, y2 = 200, x3 = 400, y3 = 100, x4 = 300, y4 = 100;
    Line(x1, y1, x2, y2);
    Line(x2, y2, x3, y3);
    Line(x3, y3, x4, y4);
    Line(x1, y1, x4, y4);


}



// Draw Triangle Function
void DrawTriangle()
{
    glClear(GL_COLOR_BUFFER_BIT);
    GLfloat x1 = 350, y1 = 30, x2 = 350, y2 = 200, x3 = 400, y3 = 30;
    Line(x1, y1, x2, y2);
    Line(x2, y2, x3, y3);
    Line(x1, y1, x3, y3);
}


// Draw Circle Function
int xcenter, ycenter, radius, input;
int input1;
void DrawCirle_midpoint()
{

    int x = 0;
    int y = radius;
    int p = 1 - radius;
    void circleplotpoints(int, int, int, int);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    /*make the first set points of a circle */
    circleplotpoints(xcenter, ycenter, x, y);
    while (x < y)
    {
        x++;
        if (p < 0)
        {
            p += 2 * x + 1;
        }
        else
        {
            y--;
            p += 2 * (x - y) + 1;
        }circleplotpoints(xcenter, ycenter, x, y);
    }
    glEnd();
    glFlush();


}


void circleplotpoints(int xcenter, int ycenter, int x, int y)
{
    glVertex2i(xcenter + x, ycenter + y);
    glVertex2i(xcenter - x, ycenter + y);
    glVertex2i(xcenter + x, ycenter - y);
    glVertex2i(xcenter - x, ycenter - y);
    glVertex2i(xcenter + y, ycenter + x);
    glVertex2i(xcenter - y, ycenter + x);
    glVertex2i(xcenter + y, ycenter - x);
    glVertex2i(xcenter - y, ycenter - x);
}

void rotate() {
    if (rectCount != 0) {
        glLoadIdentity();

       // glTranslatef(px, py, 0);
        glRotatef(R, 0, 0, 1);
        //glTranslatef(-px, -py, 0);
        DrawRectangle();
    }
    else if (cirleCount != 0) {
        glLoadIdentity();

       // glTranslatef(px, py, 0);
        glRotatef(R, 0, 0, 1);
        //glTranslatef(-px, -py, 0);
        DrawCirle_midpoint();
    }
    else if (triangleCount != 0) {
        glLoadIdentity();

       // glTranslatef(px, py, 0);
        glRotatef(R, 0, 0, 1);
      //  glTranslatef(-px, -py, 0);
        DrawTriangle();
    }
    else if (squareCount != 0) {
        glLoadIdentity();

       // glTranslatef(px, py, 0);
        glRotatef(R, 0, 0, 1);
     //   glTranslatef(-px, -py, 0);
        DrawSquare();
    }
    else if (lineCount != 0) {
        glLoadIdentity();

       // glTranslatef(px, py, 0);
        glRotatef(R, 0, 0, 1);
        //glTranslatef(-px, -py, 0);
        DrawLine();
    }
}
void Scalling() {
    if (rectCount != 0) {
        glLoadIdentity();

        glScalef(0.5f, 0.5f, 0.5f);
        //glRotatef(R, 0, 0, 1);
        //glTranslatef(-px, -py, 0);
        DrawRectangle();
    }
    else if (cirleCount != 0) {
        glLoadIdentity();

        glScalef(0.5f, 0.5f, 0.5f);
        //glRotatef(R, 0, 0, 1);
        //glTranslatef(-px, -py, 0);
        DrawCirle_midpoint();
    }
    else if (triangleCount != 0) {
        glLoadIdentity();

        glScalef(0.5f, 0.5f, 0.5f);
        //glRotatef(R, 0, 0, 1);
        //  glTranslatef(-px, -py, 0);
        DrawTriangle();
    }
    else if (squareCount != 0) {
        glLoadIdentity();

        glScalef(0.5f, 0.5f, 0.5f);
        // glRotatef(R, 0, 0, 1);
         //   glTranslatef(-px, -py, 0);
        DrawSquare();
    }
    else if (lineCount != 0) {
        glLoadIdentity();

        glScalef(0.5f, 0.5f, 0.5f);
        //glRotatef(R, 0, 0, 1);
        //glTranslatef(-px, -py, 0);
        DrawLine();
    }
}
void Translate() {
    if (rectCount != 0) {
        glLoadIdentity();

        glTranslatef(px, py, 0);
        //glRotatef(R, 0, 0, 1);
        //glTranslatef(-px, -py, 0);
        DrawRectangle();
    }
    else if (cirleCount != 0) {
        glLoadIdentity();

        glTranslatef(px, py, 0);
        //glRotatef(R, 0, 0, 1);
        //glTranslatef(-px, -py, 0);
        DrawCirle_midpoint();
    }
    else if (triangleCount != 0) {
        glLoadIdentity();

        glTranslatef(px, py, 0);
        //glRotatef(R, 0, 0, 1);
        //  glTranslatef(-px, -py, 0);
        DrawTriangle();
    }
    else if (squareCount != 0) {
        glLoadIdentity();

        glTranslatef(px, py, 0);
       // glRotatef(R, 0, 0, 1);
        //   glTranslatef(-px, -py, 0);
        DrawSquare();
    }
    else if (lineCount != 0) {
        glLoadIdentity();

        glTranslatef(px, py, 0);
        //glRotatef(R, 0, 0, 1);
        //glTranslatef(-px, -py, 0);
        DrawLine();
    }
}
void MyInit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}




void main(int argc, char* argv[]) {

    Input:
        printf("Enter 1 to draw  Rectangle :\n");
        printf("Enter 2 to draw Square .\n");
        printf("Enter 3 to draw Line .\n");
        printf("Enter 4 to draw Circle .\n");
        printf("Enter 5 to draw Triangle .\n");
        printf("Print 0 to exit the program.\n");

        scanf_s("%d", &input);
        if (input == 1)
        {
            // Initialize GLUT
            glutInit(&argc, argv);
            // Set up some memory buffers for our display
            glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
            // Set the window size
            glutInitWindowPosition(0, 0);
            glutInitWindowSize(500, 500);
            // Create the window with the title "Hello,GL"
            glutCreateWindow("Paint");
            glClearColor(250, 250, 250, 1);
            //glClearColor(0, 0, 0, 1);
            glColor3f(0.08, 0.38, 0.11);
            MyInit();
            
            glutDisplayFunc(DrawRectangle);
            glutMainLoopEvent();
            rectCount++;
            //sleep_for(nanoseconds(10000));
           // glutLeaveMainLoop();
            //glutMainLoop();
            //glutPostRedisplay();
            //glutTimerFunc(10, main,0);
            //sleep_for(nanoseconds(10000000000));
           // glfwTerminate();
        }
        else if (input == 2)
        {
            // Initialize GLUT
            glutInit(&argc, argv);
            // Set up some memory buffers for our display
            glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
            // Set the window size
            glutInitWindowPosition(0, 0);
            glutInitWindowSize(500, 500);
            // Create the window with the title "Hello,GL"
            glutCreateWindow("Paint");
            glClearColor(250, 250, 250, 1);
            //glClearColor(0, 0, 0, 1);
            glColor3f(0.09, 0.15, 0.51);
            MyInit();
            glutDisplayFunc(DrawSquare);
            glutMainLoopEvent();
            sleep_for(nanoseconds(100000));
            squareCount++;
        }
        else if (input == 3)
        {
            // Initialize GLUT
            glutInit(&argc, argv);
            // Set up some memory buffers for our display
            glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
            // Set the window size
            glutInitWindowPosition(0, 0);
            glutInitWindowSize(500, 500);
            // Create the window with the title "Hello,GL"
            glutCreateWindow("Paint");
            glClearColor(250, 250, 250, 1);
            // glClearColor(0, 0, 0, 1);
            glColor3f(0.64, 0.05, 0.17);
            MyInit();
            glutDisplayFunc(DrawLine);
            glutMainLoopEvent();
            sleep_for(nanoseconds(100000));
            lineCount++;
        }
        else if (input == 4)
        {
            printf("Enter center of the point \n:");
            scanf_s("%d%d", &xcenter, &ycenter);
            printf("Enter radius of the circle \n:");
            scanf_s("%d", &radius);
            // Initialize GLUT
            glutInit(&argc, argv);
            // Set up some memory buffers for our display
            glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
            // Set the window size
            glutInitWindowPosition(0, 0);
            glutInitWindowSize(500, 500);
            // Create the window with the title "Paint"
            glutCreateWindow("Paint");
            glClearColor(250, 250, 250, 1);
            //glClearColor(0, 0, 0, 1);
            glColor3f(0.3, 0.38, 0.23);
            MyInit();

            glutDisplayFunc(DrawCirle_midpoint);

            glutMainLoopEvent();
            sleep_for(nanoseconds(10000));
            cirleCount++;
        }
        else if (input == 5)
        {
            // Initialize GLUT
            glutInit(&argc, argv);
            // Set up some memory buffers for our display
            glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
            // Set the window size
            glutInitWindowPosition(0, 0);
            glutInitWindowSize(500, 500);
            // Create the window with the title "Paint"
            glutCreateWindow("Paint");
            glClearColor(250, 250, 250, 1);
            //glClearColor(0, 0, 0, 1);
            glColor3f(0.11, 0.12, 0.11);
            MyInit();

            glutDisplayFunc(DrawTriangle);

            glutMainLoopEvent();
            sleep_for(nanoseconds(100000));
            triangleCount++;
        }
        else if (input == 0) {
            exit(0);
        }
        else {
            printf("Wrong choose please try again\n\n");
            goto Input;
        }
        int new_x, new_y,scalling_value;
 options:
        printf("Enter 1 to rotate the Shape :\n");
        printf("Enter 2 to translate the Shape.\n");
        printf("Enter 3 to Scale the Shape .\n");
       
        scanf_s("%d",&input1);

        if (input1 == 1) {
            printf("Roatation");
            glClear(GL_COLOR_BUFFER_BIT);
            //printf("\nEnter the Rotation Reference Point [Pivot Point] : ");
           // scanf_s("%f%f", &px, &py);
            printf("\nEnter the Rotation Degree : ");
            scanf_s("%f", &R);
            glutDisplayFunc(rotate);
            glutMainLoopEvent();
           sleep_for(nanoseconds(10000000000000));
           exit(0);
        }
        else if (input1 == 2) {
            glClear(GL_COLOR_BUFFER_BIT);
            printf("\nEnter the Translation Reference Point [Pivot Point] : ");
            scanf_s("%f%f", &px, &py);
            //printf("\nEnter the Rotation Degree : ");
            //scanf_s("%f", &R);
            glutDisplayFunc(Translate);
            glutMainLoopEvent();
            sleep_for(nanoseconds(10000000000000));
            printf("Translatio Done");
            exit(0);
        }
        else if (input1 == 3) {
            glClear(GL_COLOR_BUFFER_BIT);
            glutDisplayFunc(Scalling);
            glutMainLoopEvent();
            sleep_for(nanoseconds(10000000000000));
            printf("Translatio Done");
            exit(0);
            
        }
        else if (input == 0) {
            exit(0);
        }
        else {
            goto options;
        }
}
