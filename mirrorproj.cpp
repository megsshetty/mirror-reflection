#include "GL/glut.h"
#include <stdlib.h>
#include <stdio.h>
float rotationangle;
GLUquadric *wall;
int sides,height;
void background (GLfloat order)
{
    GLfloat position[4] = {-3, 5., 1.8, 1.};
    glEnable (GL_CULL_FACE);

	glFrontFace (order);
    glColor3f (0., 0., 0.);
	glBegin(GL_QUADS);
    glColor3f (.15, 0.15, 0.15);
    glVertex3f (-3., 3., -3.);
    glColor3f(0.0,0.25,0.25);
    glVertex3f (-3., -3., -3.);
    glColor3f(0.15,0.0,0.5);
    glVertex3f (3., -3., -3);
    glColor3f(0.75,0.25,0.75);
    glVertex3f (3., 3., -3.);
    glColor3f (0.5, 1.5, .25);
    glVertex3f (-3., 3., 4.);
    glColor3f(0.15,.0,1.0);
    glVertex3f (-3., -3., 4.);
    glColor3f(0.5,0.,0.5);
    glVertex3f (-3., -3., -3.);
    glColor3f(1.25,0.25,0.25);
    glVertex3f (-3., 3., -3.);
    glEnd();
	glDisable (GL_CULL_FACE);
    glRotatef (rotationangle, 1., 0., 0.1);
    glColor3f (1., 1., 1.);
    gluCylinder(wall, .35, 0., height, sides, 8);
    }

 void display( )
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt (0., 1., 7.,
               -1., 0., 0.,
               0., 1., 0.);

	glRotatef (-rotationangle*.35, 0., 1., 0.);
	glPushMatrix ();
	glScalef (1., 1., -1.);
	glTranslatef (0., 0., 4.0);
    background(GL_CW);
	glPopMatrix ();
    glClear (GL_DEPTH_BUFFER_BIT);
	glPushAttrib (0xffffffff);
	glDisable (GL_LIGHTING);
	/* Create imperfect reflector effect by blending a black
	   mirror over the reflected scene with alpha of 0.05 */
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f (0.05, 0., 0., 0.0);
	glBegin (GL_QUADS);

	    glVertex3f (3., 1., -2.0);
	    glVertex3f (3., -1., -2.0);
	    glVertex3f (-2.5, -1., -2.0);
	    glVertex3f (-2.5, 1., -2.0);

	glEnd ();
	glPopAttrib();
    background(GL_CCW);
    glutSwapBuffers();

	{
		int err = glGetError();
		if (err != GL_NO_ERROR)
			printf ("Error %x\n", err);
	}

}

void reshape(int w, int h)
{
    glViewport (0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (50., (float)w/(float)h, 1., 20.);
}

 void init ()
{
   glEnable (GL_DEPTH_TEST);

    {
        GLfloat white[4] = {1.,1.25, 1., 0.};


        glEnable (GL_LIGHTING);
        glEnable (GL_LIGHT1);
        glLightfv (GL_LIGHT1, GL_DIFFUSE, white);
        glLightfv (GL_LIGHT1, GL_SPECULAR, white);

        glEnable (GL_COLOR_MATERIAL);
        glColorMaterial (GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        glMaterialfv (GL_FRONT, GL_SPECULAR, white);
	    glMaterialf (GL_FRONT, GL_SHININESS, 20.);
    }
   }
   void myKeyboardFunc( unsigned char key, int x, int y )
   {
   if(key==' ')
   {
   rotationangle = 70.0;
    glutPostRedisplay ();
    }

   }


int main(int argc, char** argv)
{
    glutInit (&argc,argv);
    glutInitDisplayMode (GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    printf("press spacebar for rotation\n");
    printf("enter the no sides of base\n");
    scanf("%d",&sides);
    printf("enter the height of the object u need ranging from 0 to 1.9\n");
    scanf("%d",&height);
    glutInitWindowSize (500,500);
    glutInitWindowPosition (0,0);

    glutCreateWindow ("Mirror reflection");

    wall = gluNewQuadric ();
    glutDisplayFunc (display);
    glutReshapeFunc (reshape);
    glutKeyboardFunc( myKeyboardFunc );
    init ();
    glutMainLoop ();
    return 0;
}
