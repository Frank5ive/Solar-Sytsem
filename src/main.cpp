#include<GL/freeglut.h>

void initialize(){
    glClearColor(0.0f,0.0f,0.0f,1.0f); //setting background color to black

    glMatrixMode(GL_PROJECTION); //set up the prjection matrix
    glLoadIdentity(); //reset projection matrix
    gluOrtho2D(-1.0, 1.0,-1.0,1.0); //set 2D orthographic projection
}

//function to render Scene
void renderScene(){
    glClear(GL_COLOR_BUFFER_BIT); //Clear the color buffer

    //Render logic (empty for now)
    glFlush(); //Ensure all OpenGL commands are executed
}

//main Function
int main(int argc, char** argv){
    //initialize glut
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //single buffer rgb mode
    glutInitWindowSize(800,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("2D solar System");

    initialize();
    glutDisplayFunc(renderScene);

    glutMainLoop();

    return 0;
}