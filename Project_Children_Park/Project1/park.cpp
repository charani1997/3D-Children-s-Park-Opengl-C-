#include <GL/glut.h>  
#include <math.h>
#define PI 3.1415927

GLUquadric* quad;
// rotaion varables
GLfloat animXRot, animYRot, animZRot = 0;

//camera variables
GLfloat camX = 0, camY = 0, camZ = 0;

//object variables - inside house
GLfloat objY = 0;

//scene variables
GLfloat sceX = 0, sceY = 0, sceZ = 0;

// A quadratic object pointer used to draw the sides of the cylinder
GLUquadricObj* qobj;

GLfloat angle = 0.0f; // Angle of the seesaw
GLfloat deltaAngle = 1.0f; // Amount to change the angle by

GLfloat angle_s = 0.0; // Angle of rotation for the swing
GLfloat timeStep = 0.1; // Time step for the simulation
GLfloat time = 0.0; // Time elapsed since the simulation started
GLfloat angle_r = 0.0;//spring rider angle
GLfloat angle_b = 0.0f;//baloonman angle
GLfloat speed = 2.0;
GLfloat angle_m = 0.0f;

void lightingFunc() {

    GLfloat L0_Ambient[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat L0_Diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat L0_postion[] = { 2.0, 2.0, 2.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, L0_Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, L0_Diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, L0_postion);

    GLfloat L1_Ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat L1_Diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat L1_Specular[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat L1_postion[] = { 14.9, 15, -17, 1.0 };

    GLfloat L2_postion[] = { 0.0, 4.0, 0.0, 1.0 };

    glLightfv(GL_LIGHT1, GL_AMBIENT, L1_Ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, L1_Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, L1_Specular);
    glLightfv(GL_LIGHT1, GL_POSITION, L1_postion);

    glLightfv(GL_LIGHT1, GL_AMBIENT, L1_Ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, L1_Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, L1_Specular);
    glLightfv(GL_LIGHT1, GL_POSITION, L2_postion);


    //Declaration of the light reflecting properties for the materials
    GLfloat specularReflectance[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularReflectance);
    glMateriali(GL_FRONT, GL_SHININESS, 50);
}

void makeCylinder(GLfloat height, GLfloat base) {
    GLUquadric* obj = gluNewQuadric();
    glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(obj, base, base - (0.2 * base), height, 20, 20);
    glPopMatrix();
    glutSwapBuffers();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
    GLfloat globalAmbient[] = { 0.8, 0.8, 0.8, 1.0 };
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);

    glShadeModel(GL_SMOOTH);

    // Changing the global Ambient illumination without any lights present
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Enabling the color tracking of each faces of the materials. this enables the color visibility of the materials
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHT0);//Turn on lighting
    //glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);// enable the normalization of the normal vectors
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);
}
//set materials
void material(GLfloat amb[], GLfloat dif[], GLfloat spec[], GLfloat shin[])
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);
}

void drawAxes() {
    glBegin(GL_LINES);
    GLfloat amb[] = { 1,0,0,1 };
    GLfloat dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec[] = { 1,1,1,1 };
    GLfloat shin[] = { 50 };
    material(amb, dif, spec, shin);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 200);
    glVertex3f(0, 0, -200);
    glEnd();

    glBegin(GL_LINES);
    GLfloat amb1[] = { 0,1,0,1 };
    GLfloat dif1[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    GLfloat spec1[] = { 1,1,1,1 };
    GLfloat shin1[] = { 50 };
    material(amb1, dif1, spec1, shin1);
    glColor3f(0, 1, 0);
    glVertex3f(0, 200, 0);
    glVertex3f(0, -200, -0);
    glEnd();

    glBegin(GL_LINES);
    GLfloat amb2[] = { 0,0,1,1 };
    GLfloat dif2[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    GLfloat spec2[] = { 1,1,1,1 };
    GLfloat shin2[] = { 50 };
    material(amb2, dif2, spec2, shin2);
    glColor3f(0, 0, 1);
    glVertex3f(-200, 0, 0);
    glVertex3f(200, 0, 0);
    glEnd();
}

void cube(GLfloat x, GLfloat y, GLfloat z) {
    glPushMatrix();
    glBegin(GL_QUADS);

    glVertex3f(-x, y, -z);
    glVertex3f(-x, y, z);
    glVertex3f(x, y, z);
    glVertex3f(x, y, -z);

    glVertex3f(-x, y, z);
    glVertex3f(-x, -y, z);
    glVertex3f(x, -y, z);
    glVertex3f(x, y, z);

    glVertex3f(x, y, z);
    glVertex3f(x, -y, z);
    glVertex3f(x, -y, -z);
    glVertex3f(x, y, -z);

    glVertex3f(x, y, -z);
    glVertex3f(x, -y, -z);
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, y, -z);

    glVertex3f(-x, y, -z);
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, -y, z);
    glVertex3f(-x, y, z);

    glVertex3f(-x, -y, -z);
    glVertex3f(-x, -y, z);
    glVertex3f(x, -y, z);
    glVertex3f(x, -y, -z);


    glEnd();
    glPopMatrix();

}


void wall() {
    //..................................Wall.........................................
    glColor3f(0.9, 1.0, 0.6);
    GLfloat amb3[] = { 00.9,1.0,0.6,1 };
    GLfloat dif3[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec3[] = { 1,1,1,1 };
    GLfloat shin3[] = { 60 };
    material(amb3, dif3, spec3, shin3);
    glScalef(100, 8, 1);
    glTranslatef(0, 0.3, 0);
    glutSolidCube(1);
}

void tree()
{
    //...........................................Tree....................................
    glPushMatrix();
    glScalef(1, 1, 1);
    quad = gluNewQuadric();

    glPushMatrix();
    GLfloat amb4[] = { 0, 1, 0,1 };
    GLfloat dif4[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec4[] = { 1,1,1,1 };
    GLfloat shin4[] = { 50 };
    material(amb4, dif4, spec4, shin4);
    glPushMatrix();
    glColor3f(0, 1, 0);
    glScalef(1, 2, 1);

    glRotated(90, -1, 0, 0);
    glutSolidCone(2.5, 4.0, 300, 300);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(0, -6, 0);
    glRotated(90, -1, 0, 0);
    glutSolidCone(3, 4.0, 300, 300);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(0, -3, 0);
    glRotated(90, -1, 0, 0);
    glutSolidCone(2.5, 4.0, 300, 300);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    GLfloat amb5[] = { 0.5, 0.2, 0,1 };
    GLfloat dif5[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec5[] = { 1,1,1,1 };
    GLfloat shin5[] = { 50 };
    material(amb5, dif5, spec5, shin5);
    glColor3f(0.5, 0.2, 0);
    glTranslatef(0, -7, 0);
    glRotatef(90, 1, 0, 0);
    gluCylinder(quad, 1, 1, 10, 32, 32);
    glPopMatrix();

    glPopMatrix();
}

void slide() {
    //......................................Slide.....................................
    glPushMatrix();
    glTranslatef(0.5, 0, -1.5);
    //glTranslatef(0.5, -2.5, -1.5);
    glPushMatrix();
    glColor3f(0, 0, 1);
    GLfloat amb10[] = { 0, 0, 1,1 };
    GLfloat dif10[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec10[] = { 1,1,1,1 };
    GLfloat shin10[] = { 50 };
    material(amb10, dif10, spec10, shin10);
    glTranslatef(0, 5, 5);
    GLUquadricObj* cylin5 = gluNewQuadric(); //supporting rod1
    glRotatef(90, 1, 0, 0);
    gluCylinder(cylin5, 0.05, 0.05, 2, 8, 8);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 1);
    material(amb10, dif10, spec10, shin10);
    glTranslatef(0, 5, 5.75);
    glRotatef(90, 1, 0, 0);
    gluCylinder(cylin5, 0.05, 0.05, 2, 8, 8);//rod2
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 5, 5);
    glPushMatrix();
    glColor3f(0.9, 0.5, 0.3); //horizontal cylinders
    GLfloat amb11[] = { 0.9, 0.5, 0.3,1 };
    GLfloat dif11[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec11[] = { 1,1,1,1 };
    GLfloat shin11[] = { 50 };
    material(amb11, dif11, spec11, shin11);
    gluCylinder(cylin5, 0.05, 0.05, 0.75, 8, 8);
    glColor3f(0.6, 0.3, 0);
    GLfloat amb12[] = { 0.6, 0.3, 0,1 };
    GLfloat dif12[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec12[] = { 1,1,1,1 };
    GLfloat shin12[] = { 50 };
    material(amb12, dif12, spec12, shin12);
    glPushMatrix();//cylinders to climb up
    for (int i = 0; i < 3; i++)
    {
        glTranslatef(0, -0.5, 0);
        gluCylinder(cylin5, 0.05, 0.05, 0.75, 8, 8);
    }
    glPopMatrix();//cylinders horizontal

    for (int i = 0; i < 5; i++)
    {
        glTranslatef(0.15, 0, 0);
        glColor3f(0.9, 0.5, 0.3);
        GLfloat amb13[] = { 0.9, 0.5, 0.3,1 };
        GLfloat dif13[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat spec13[] = { 1,1,1,1 };
        GLfloat shin13[] = { 50 };
        material(amb13, dif13, spec13, shin13);
        gluCylinder(cylin5, 0.05, 0.05, 0.75, 8, 8);
    }
    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    glRotatef(-140, 0, 0, 1);
    for (int i = 0; i < 17; i++) //cylinders along the slide
    {
        glTranslatef(0.12, 0, 0);
        glColor3f(0.9, 0.5, 0.3);
        GLfloat amb13[] = { 0.9, 0.5, 0.3,1 };
        GLfloat dif13[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat spec13[] = { 1,1,1,1 };
        GLfloat shin13[] = { 50 };
        material(amb13, dif13, spec13, shin13);
        gluCylinder(cylin5, 0.05, 0.05, 0.75, 8, 8);
    }
    glPopMatrix();
    glPopMatrix();
    glColor3f(0, 0, 0);
    GLfloat amb14[] = { 0, 0, 0,1 };
    GLfloat dif14[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec14[] = { 1,1,1,1 };
    GLfloat shin14[] = { 50 };
    material(amb14, dif14, spec14, shin14);
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    gluCylinder(cylin5, 0.05, 0.05, 0.8, 8, 8); //slide sides
    glPopMatrix();
    glTranslatef(0, 0, 0.75);
    glRotatef(90, 0, 1, 0);
    gluCylinder(cylin5, 0.05, 0.05, 0.8, 8, 8); //slide side
    glPopMatrix();
    double j = 0;
    for (int i = 0; i < 2; i++)
    {
        glPushMatrix();
        glColor3f(0, 0, 0.9);
        GLfloat amb15[] = { 0, 0, 0.9,1 };
        GLfloat dif15[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat spec15[] = { 1,1,1,1 };
        GLfloat shin15[] = { 50 };
        material(amb15, dif15, spec15, shin15);
        glTranslatef(0.8, 5, 5 + j);
        glRotatef(90, 0, 1, 0);
        glRotatef(50, 1, 0, 0);
        gluCylinder(cylin5, 0.07, 0.07, 2, 8, 8);
        glPopMatrix();
        j += 0.75;
    }
    glPopMatrix();
    glPopMatrix();

}

void draw_cylinder(GLfloat radius, GLfloat height)
{
    //-------------------------------------cylinder--------------------------------
    GLfloat x = 0.0;
    GLfloat y = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */
    glColor3f(0.6, 0.1, 0.0);
    GLfloat amb16[] = { 0.6, 0.1, 0.0,1 };
    GLfloat dif16[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec16[] = { 1,1,1,1 };
    GLfloat shin16[] = { 50 };
    material(amb16, dif16, spec16, shin16);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while (angle < 2 * PI) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        glVertex3f(x, y, 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    angle = 0.0;
    while (angle < 2 * PI) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();
}

void bench() {
    glPushMatrix();
    glPushMatrix();
    glColor3f(0, 0, 1);
    GLfloat amb17[] = { 0, 0, 1,1 };
    GLfloat dif17[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec17[] = { 1,1,1,1 };
    GLfloat shin17[] = { 50 };
    material(amb17, dif17, spec17, shin17);
    glTranslatef(-15, 3.5, 15);
    glRotatef(90, 0, 1, 0);
    glScalef(2, 0.5, 1);
    glutSolidCube(2.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    GLfloat amb18[] = { 0, 0, 0,1 };
    GLfloat dif18[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec18[] = { 1,1,1,1 };
    GLfloat shin18[] = { 50 };
    material(amb18, dif18, spec18, shin18);
    glTranslatef(-15.5, 1.5, 16);
    glScalef(1, 3, 0.2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    GLfloat amb19[] = { 0, 0, 0,1 };
    GLfloat dif19[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec19[] = { 1,1,1,1 };
    GLfloat shin19[] = { 50 };
    material(amb19, dif19, spec19, shin19);
    glTranslatef(-15.5, 1.5, 14);
    glScalef(1, 3, 0.2);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();
}

void MonkeyBar() {
    glPushMatrix();
    glColor3f(0, 0, 1);
    GLfloat amb20[] = { 0,0,1,1 };
    GLfloat dif20[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec20[] = { 1,1,1,1 };
    GLfloat shin20[] = { 50 };
    material(amb20, dif20, spec20, shin20);
    glTranslatef(0, 4, 0);
    glRotatef(90, 0, 1, 0);
    glScalef(0.5, 8, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 1);
    GLfloat amb21[] = { 0,0,1,1 };
    GLfloat dif21[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec21[] = { 1,1,1,1 };
    GLfloat shin21[] = { 50 };
    material(amb21, dif21, spec21, shin21);
    glTranslatef(3, 4, 0);
    glRotatef(90, 0, 1, 0);
    glScalef(0.5, 8, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 1);
    GLfloat amb22[] = { 0,0,1,1 };
    GLfloat dif22[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec22[] = { 1,1,1,1 };
    GLfloat shin22[] = { 50 };
    material(amb22, dif22, spec22, shin22);
    glTranslatef(0, 4, 8);
    glRotatef(90, 0, 1, 0);
    glScalef(0.5, 8, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 1);
    GLfloat amb23[] = { 0,0,1,1 };
    GLfloat dif23[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec23[] = { 1,1,1,1 };
    GLfloat shin23[] = { 50 };
    material(amb23, dif23, spec23, shin23);
    glTranslatef(3, 4, 8);
    glRotatef(90, 0, 1, 0);
    glScalef(0.5, 8, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 1, 1);
    GLfloat amb24[] = { 0, 1, 1,1 };
    GLfloat dif24[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec24[] = { 1,1,1,1 };
    GLfloat shin24[] = { 50 };
    material(amb24, dif24, spec24, shin24);
    glTranslatef(0, 8.25, 4);
    glRotatef(90, 1, 0, 0);
    glScalef(0.5, 8.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 1, 1);
    GLfloat amb25[] = { 0, 1, 1,1 };
    GLfloat dif25[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec25[] = { 1,1,1,1 };
    GLfloat shin25[] = { 50 };
    material(amb25, dif25, spec25, shin25);
    glTranslatef(3, 8.25, 4);
    glRotatef(90, 1, 0, 0);
    glScalef(0.5, 8.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    //glPushMatrix();
    //glColor3f(0, 0, 0);
    //glTranslatef(1.5, 2, 0);
    //glRotatef(90, 0, 0, 1);
    //glScalef(0.5, 2.4, 0.5);
    //glutSolidCube(1);
    //glPopMatrix();

    glPushMatrix();//horizontal bars back
    for (float i = 2; i < 10; i += 2)
    {
        glPushMatrix();
        glColor3f(1, 0, 0);
        GLfloat amb26[] = { 1, 0, 0,1 };
        GLfloat dif26[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat spec26[] = { 1,1,1,1 };
        GLfloat shin26[] = { 50 };
        material(amb26, dif26, spec26, shin26);
        glTranslatef(1.5, i, 0);
        glRotatef(90, 0, 0, 1);
        glScalef(0.5, 2.4, 0.5);
        glutSolidCube(1);
        glPopMatrix();
    }
    glPopMatrix();

    glPushMatrix();//horizontal bars front
    for (float i = 2; i < 10; i += 2)
    {
        glPushMatrix();
        glColor3f(1, 0, 0);
        GLfloat amb27[] = { 1, 0, 0,1 };
        GLfloat dif27[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat spec27[] = { 1,1,1,1 };
        GLfloat shin27[] = { 50 };
        material(amb27, dif27, spec27, shin27);
        glTranslatef(1.5, i, 8);
        glRotatef(90, 0, 0, 1);
        glScalef(0.5, 2.4, 0.5);
        glutSolidCube(1);
        glPopMatrix();
    }
    glPopMatrix();

    glPushMatrix();//horizontal bars top
    for (float i = 2; i < 8; i += 0.8)
    {
        glPushMatrix();
        glColor3f(1, 0, 0);
        GLfloat amb28[] = { 1, 0, 0,1 };
        GLfloat dif28[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat spec28[] = { 1,1,1,1 };
        GLfloat shin28[] = { 50 };
        material(amb28, dif28, spec28, shin28);
        glTranslatef(1.5, 8.5, i);
        glRotatef(90, 0, 0, 1);
        glScalef(0.25, 2.4, 0.25);
        glutSolidCube(1);
        glPopMatrix();
    }
    glPopMatrix();
}

void drawTriangle() {
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.3, 0);
    GLfloat amb29[] = { 0.6, 0.3, 0,1 };
    GLfloat dif29[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec29[] = { 1,1,1,1 };
    GLfloat shin29[] = { 50 };
    material(amb29, dif29, spec29, shin29);
    glVertex3f(-0.75, 0, 0.75);
    glVertex3f(0.75, 0, 0.75);
    glVertex3f(0, 0.5, 0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.6, 0);
    GLfloat amb30[] = { 0.6, 0.6, 0,1 };
    GLfloat dif30[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec30[] = { 1,1,1,1 };
    GLfloat shin30[] = { 50 };
    material(amb30, dif30, spec30, shin30);
    glVertex3f(-0.75, 0, 0.75);
    glVertex3f(0.75, 0, 0.75);
    glVertex3f(0.5, 0, 0.5);
    glVertex3f(-0.5, 0, 0.5);
    glEnd();
}

void drawRoof() {
    for (int i = 0; i <= 360; i += 90) {
        glPushMatrix();
        glRotatef(i, 0, 1, 0);
        drawTriangle();
        glPopMatrix();
    }
}
//void drawTable() {
//    glPushMatrix();
//    glTranslatef(-20, 0.5, -20);
//    glPushMatrix();
//    glColor3f(0, 0, 1);
//    GLfloat amb31[] = { 0, 0, 1,1 };
//    GLfloat dif31[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//    GLfloat spec31[] = { 1,1,1,1 };
//    GLfloat shin31[] = { 50 };
//    material(amb31, dif31, spec31, shin31);
//    glTranslatef(10, 3.5, 6);
//    glRotatef(90, 0, 1, 0);
//    glScalef(1, 0.5, 2);
//    glutSolidCube(2.5);
//    glPopMatrix();
//
//    glPushMatrix();
//    glColor3f(0, 0, 0);
//    GLfloat amb32[] = { 0, 0, 0,1 };
//    GLfloat dif32[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//    GLfloat spec32[] = { 1,1,1,1 };
//    GLfloat shin32[] = { 50 };
//    material(amb32, dif32, spec32, shin32);
//    glTranslatef(10, 1.5, 6);
//    glScalef(1, 4, 0.5);
//    glutSolidCube(1);
//    glPopMatrix();
//    glPopMatrix();
//}

void hut() {
    glPushMatrix();
    //glTranslatef(-20, 0.5, -20);
    glTranslatef(-20, 0, -40);
    glScalef(2, 2, 2);
    glPushMatrix();
    glColor3f(0.8, 0.4, 0.9);
    GLfloat amb33[] = { 0.8,0.4, 0.9,1 };
    GLfloat dif33[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec33[] = { 1,1,1,1 };
    GLfloat shin33[] = { 50 };
    material(amb33, dif33, spec33, shin33);
    glTranslatef(0, 4, 0);
    glRotatef(90, 0, 1, 0);
    glScalef(1, 8, 1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.8, 0.4, 0.9);
    material(amb33, dif33, spec33, shin33);
    glTranslatef(6, 4, 0);
    glRotatef(90, 0, 1, 0);
    glScalef(1, 8, 1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.8, 0.4, 0.9);
    material(amb33, dif33, spec33, shin33);
    glTranslatef(0, 4, 6);
    glRotatef(90, 0, 1, 0);
    glScalef(1, 8, 1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.8, 0.4, 0.9);
    material(amb33, dif33, spec33, shin33);
    glTranslatef(6, 4, 6);
    glRotatef(90, 0, 1, 0);
    glScalef(1, 8, 1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3, 8, 0);
    glScalef(10, 10, 10);
    drawRoof();
    glPopMatrix();

    glPopMatrix();
}

//void drawObject() {
//    glPushMatrix();
//    glPushMatrix();
//    glTranslatef(-15,0,-35);
//    bench();
//    glPopMatrix();
//    glPushMatrix();
//    glTranslatef(-5,0,5);
//    glScalef(2,2,2);
//    drawTable();
//    glPopMatrix();
//    glPopMatrix();
//}

void hut2() {
    glPushMatrix();
    glScalef(1, 1, 1);
    glPushMatrix();
    glTranslatef(-20, 0, -18);
    //glTranslatef(0, 0.5, 0);
    glPushMatrix();
    glColor3f(0, 0, 1);
    GLfloat amb34[] = { 0, 0, 1,1 };
    GLfloat dif34[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec34[] = { 1,1,1,1 };
    GLfloat shin34[] = { 50 };
    material(amb34, dif34, spec34, shin34);
    glTranslatef(0, 4, 0);
    glRotatef(90, 0, 1, 0);
    glScalef(0.5, 8, 1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0, 0);
    GLfloat amb35[] = { 1,0,0,1 };
    GLfloat dif35[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec35[] = { 1,1,1,1 };
    GLfloat shin35[] = { 50 };
    material(amb35, dif35, spec35, shin35);
    glTranslatef(0, 8, 0);
    glScalef(5, 5, 5);
    drawRoof();
    glPopMatrix();
    glPopMatrix();
}

void torus() {
    glPushMatrix();
    glColor3f(0.8, 0.4, 0.5);
    GLfloat amb65[] = { 0.8,0.4,0.5,1 };
    GLfloat dif65[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec65[] = { 1,1,1,1 };
    GLfloat shin65[] = { 50 };
    material(amb65, dif65, spec65, shin65);
    glTranslatef(0, 0.5, -2);
    glRotatef(-90, 1, 0, 0);
    glScalef(5, 5, 5);
    glutSolidTorus(0.1, 1, 50, 50);
    glPopMatrix();
}
void tank() {
    glPushMatrix();
    glTranslatef(-22, 0, -8);
    torus();
    glPopMatrix();
}
void baloonman() {
    glPushMatrix();
    glTranslatef(0, 10.5, -2);
    glScalef(5, 5, 5);
    // Body
    glColor3f(0.8, 0.0, 0.5);
    GLfloat amb38[] = { 0.8,0.0,0.5,1 };
    GLfloat dif38[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec38[] = { 1,1,1,1 };
    GLfloat shin38[] = { 50 };
    material(amb38, dif38, spec38, shin38);
    glutSolidSphere(1.0, 20, 20);

    // Head
    glPushMatrix();
    glTranslatef(0.0, 1.3, 0.0);
    glColor3f(0.8, 0.5, 0.0);
    GLfloat amb39[] = { 0.8, 0.5, 0.0,1 };
    GLfloat dif39[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec39[] = { 1,1,1,1 };
    GLfloat shin39[] = { 50 };
    material(amb39, dif39, spec39, shin39);
    glutSolidSphere(0.5, 20, 20);
    glPopMatrix();

    // Arms
    glPushMatrix();
    glTranslatef(-1.2, 0.2, 0.0);
    glRotatef(45.0, 0.0, 0.0, 1.0);
    glScalef(1.5, 0.2, 0.4);
    glColor3f(0.8, 0.0, 0.9);
    GLfloat amb40[] = { 0.8, 0.0, 0.9,1 };
    GLfloat dif40[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec40[] = { 1,1,1,1 };
    GLfloat shin40[] = { 50 };
    material(amb40, dif40, spec40, shin40);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.2, 0.2, 0.0);
    glRotatef(-45.0, 0.0, 0.0, 1.0);
    glScalef(1.5, 0.2, 0.4);
    glColor3f(0.8, 0.0, 0.9);
    GLfloat amb41[] = { 0.8, 0.0, 0.9,1 };
    GLfloat dif41[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec41[] = { 1,1,1,1 };
    GLfloat shin41[] = { 50 };
    material(amb41, dif41, spec41, shin41);
    glutSolidCube(1.0);
    glPopMatrix();

    // Legs
    glPushMatrix();
    glTranslatef(-0.5, -1.5, 0.0);
    glRotatef(-30.0, 0.0, 0.0, 1.0);
    glScalef(0.2, 1.5, 0.2);
    glColor3f(0.8, 0.0, 0.9);
    GLfloat amb42[] = { 0.8, 0.0, 0.9,1 };
    GLfloat dif42[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec42[] = { 1,1,1,1 };
    GLfloat shin42[] = { 50 };
    material(amb42, dif42, spec42, shin42);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5, -1.5, 0.0);
    glRotatef(30.0, 0.0, 0.0, 1.0);
    glScalef(0.2, 1.5, 0.2);
    glColor3f(0.8, 0.0, 0.9);
    GLfloat amb43[] = { 0.8, 0.0, 0.9,1 };
    GLfloat dif43[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec43[] = { 1,1,1,1 };
    GLfloat shin43[] = { 50 };
    material(amb43, dif43, spec43, shin43);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();
}
void panda() {
    // Draw Body
    glColor3f(1.0f, 1.0f, 1.0f);
    GLfloat amb44[] = { 1.0f, 1.0f, 1.0f,1.0f };
    GLfloat dif44[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec44[] = { 1,1,1,1 };
    GLfloat shin44[] = { 50 };
    material(amb44, dif44, spec44, shin44);
    glTranslatef(0.0f, 0.0f, 0.0f);
    glutSolidSphere(0.75f, 20, 20);


    // Draw Head
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.50f, 20, 20);


    // Draw Eyes
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    GLfloat amb45[] = { 1.0f, 1.0f, 1.0f,1.0f };
    GLfloat dif45[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec45[] = { 1,1,1,1 };
    GLfloat shin45[] = { 50 };
    material(amb45, dif45, spec45, shin45);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.3f, 20, 20);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.3f, 20, 20);
    glPopMatrix();

    // Draw ear
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    GLfloat amb46[] = { 0.0f, 0.0f, 0.0f,1.0f };
    GLfloat dif46[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec46[] = { 1,1,1,1 };
    GLfloat shin46[] = { 50 };
    material(amb46, dif46, spec46, shin46);
    glTranslatef(0.3f, 0.3f, 0.2f);
    glutSolidSphere(0.1f, 5, 5);
    glTranslatef(-0.7f, 0.1f, -0.4f);
    glutSolidSphere(0.1f, 5, 5);
    glPopMatrix();
}

void springRider() {
    glPushMatrix();

    glPushMatrix();
    glColor3f(0, 0, 1);
    GLfloat amb47[] = { 0,0,1,1 };
    GLfloat dif47[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec47[] = { 1,1,1,1 };
    GLfloat shin47[] = { 50 };
    material(amb47, dif47, spec47, shin47);
    glTranslatef(0, -10, 0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    cube(1, 1, 1);//base
    glPopMatrix();


    glPushMatrix();
    glColor3f(0, 0, 1);
    material(amb47, dif47, spec47, shin47);
    glTranslatef(0, -8, 0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    cube(1, 0.2, 0.5);//top base
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -6.5, 0);
    glRotatef(60, 0, 0, 1);
    glRotatef(angle_r, 0.0f, 0.0f, 1.0f);//animation around z axis
    panda();
    glPopMatrix();

    glPopMatrix();
}

void seasaw() {
    //glPushMatrix();
    glColor3f(0, 0, 0);
    GLfloat amb55[] = { 0,0,0,1 };
    GLfloat dif55[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec55[] = { 1,1,1,1 };
    GLfloat shin55[] = { 50 };
    material(amb55, dif55, spec55, shin55);
    glPushMatrix();
    glTranslatef(0.0, 2.5, 0.0);
    glScalef(1.0, 4, 1.0);
    glutSolidCube(1.0);//base


    glPopMatrix();
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);//sea saw
    GLfloat amb56[] = { 0.5, 0.5, 0.5,1 };
    GLfloat dif56[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec56[] = { 1,1,1,1 };
    GLfloat shin56[] = { 50 };
    material(amb56, dif56, spec56, shin56);
    glPushMatrix();
    glTranslatef(0.0, 4.75, 0.0);
    glScalef(7.0, 0.5, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glColor3f(1, 0, 0);//seat
    GLfloat amb57[] = { 1,0,0,1 };
    GLfloat dif57[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec57[] = { 1,1,1,1 };
    GLfloat shin57[] = { 50 };
    material(amb57, dif57, spec57, shin57);
    glPushMatrix();
    glTranslatef(-2.9, 5, 0.0);
    glScalef(1, 0.1, 1);
    glutSolidCube(1.0);
    glPopMatrix();

    glColor3f(1, 0, 0); //seat
    material(amb57, dif57, spec57, shin57);
    glPushMatrix();
    glTranslatef(2.9, 5, 0.0);
    glScalef(1, 0.1, 1);
    glutSolidCube(1.0);
    glPopMatrix();

    glColor3f(0, 0, 1); //handle vertical1
    GLfloat amb58[] = { 0,0,1,1 };
    GLfloat dif58[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec58[] = { 1,1,1,1 };
    GLfloat shin58[] = { 50 };
    material(amb58, dif58, spec58, shin58);
    glPushMatrix();
    glTranslatef(2.3, 5.5, 0.0);
    glRotatef(90, 0, 0, 1);
    glScalef(1, 0.2, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    glColor3f(0, 0, 1); //handle vertical
    material(amb58, dif58, spec58, shin58);
    glPushMatrix();
    glTranslatef(-2.3, 5.5, 0.0);
    glRotatef(90, 0, 0, 1);
    glScalef(1, 0.2, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    glColor3f(0, 0, 1); //handle
    material(amb58, dif58, spec58, shin58);
    glPushMatrix();
    glTranslatef(2.3, 6, 0.0);
    glRotatef(90, 0, 1, 0);
    glScalef(1.5, 0.2, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    glColor3f(0, 0, 1); //handle
    material(amb58, dif58, spec58, shin58);
    glPushMatrix();
    glTranslatef(-2.3, 6, 0.0);
    glRotatef(90, 0, 1, 0);
    glScalef(1.5, 0.2, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();
}

void dustbin() {
    glPushMatrix();
    glTranslatef(0, 0.0, 0);
    glRotatef(-90, 1, 0, 0);
    draw_cylinder(1, 2);

    glPopMatrix();
}
void lamp() {
    glPushMatrix();
    glColor3f(0, 0, 0);
    GLfloat amb59[] = { 0,0,0,1 };
    GLfloat dif59[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec59[] = { 1,1,1,1 };
    GLfloat shin59[] = { 50 };
    material(amb59, dif59, spec59, shin59);
    glTranslatef(0, 4, 0);
    glRotatef(90, 0, 1, 0);
    glScalef(0.6, 8, 0.6);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1);
    GLfloat amb60[] = { 1,1,1,1 };
    GLfloat dif60[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec60[] = { 1,1,1,1 };
    GLfloat shin60[] = { 50 };
    material(amb60, dif60, spec60, shin60);
    glTranslatef(0, 8, 0);

    glutSolidSphere(1, 50, 50);
    glPopMatrix();
}

void icecream() {
    glPushMatrix();
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.1);
    GLfloat amb36[] = { 0.7,0.3,0.1,1 };
    GLfloat dif36[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec36[] = { 1,1,1,1 };
    GLfloat shin36[] = { 50 };
    material(amb36, dif36, spec36, shin36);
    glTranslatef(0, 6.0, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(15, 15, 15);
    glutSolidCone(0.075, 0.4, 100, 100);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0, 6.5, 0.0);
    glColor3f(1.0, 0.8, 0.4);
    GLfloat amb37[] = { 1.0, 0.8, 0.4,1 };
    GLfloat dif37[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec37[] = { 1,1,1,1 };
    GLfloat shin37[] = { 50 };
    material(amb37, dif37, spec37, shin37);
    glScalef(1, 1, 1);
    glutSolidSphere(1.1, 25, 25);
    glPopMatrix();
    glPopMatrix();
}
void swingseat() {
    glPushMatrix();
    glRotatef(angle_s, 1.0, 0.0, 0.0);
    glPushMatrix();
    glColor3f(0, 0, 1);
    GLfloat amb66[] = { 0, 0, 1,1 };
    GLfloat dif66[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec66[] = { 1,1,1,1 };
    GLfloat shin66[] = { 50 };
    material(amb66, dif66, spec66, shin66);
    glTranslatef(0, -2, 0);//top base
    cube(2, 0.2, 1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.7, 0.4, 0.2);
    GLfloat amb67[] = { 0.7, 0.4, 0.2,1 };
    GLfloat dif67[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec67[] = { 1,1,1,1 };
    GLfloat shin67[] = { 50 };
    material(amb67, dif67, spec67, shin67);
    glTranslatef(1, -5, 0);
    //glRotatef(angle_s, 0.0, 0.0, 1.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    cube(3, 0.05, 0.05);//rope1
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1, -5, 0);
    glColor3f(0.7, 0.4, 0.2);
    material(amb67, dif67, spec67, shin67);
    //glRotatef(angle_s, 0.0, 0.0, 1.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    cube(3, 0.05, 0.05);//rope2
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -8, 0);
    glColor3f(1, 0, 0);
    GLfloat amb68[] = { 1,0,0,1 };
    GLfloat dif68[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec68[] = { 1,1,1,1 };
    GLfloat shin68[] = { 50 };
    material(amb68, dif68, spec68, shin68);
    //glRotatef(angle_s, 0.0, 0.0, 1.0);
    //glRotatef(90.0, 0.0, 0.0, 1.0);
    cube(2, 0.05, 1);//seat
    glPopMatrix();

    glPopMatrix();
}

void swing() {
    glPushMatrix();

    glPushMatrix();
    glColor3f(0, 0, 1);
    GLfloat amb69[] = { 0,0,1,1 };
    GLfloat dif69[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec69[] = { 1,1,1,1 };
    GLfloat shin69[] = { 50 };
    material(amb69, dif69, spec69, shin69);
    glTranslatef(0, -1.8, 0);//top
    cube(5, 0.5, 1.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 1);
    material(amb69, dif69, spec69, shin69);
    glTranslatef(2.5, -6, 0);
    //glRotatef(angle_s, 0.0, 0.0, 1.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    cube(4, 0.1, 0.1);//stand 1
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 1);
    material(amb69, dif69, spec69, shin69);
    glTranslatef(-2.5, -6, 0);
    //glRotatef(angle_s, 0.0, 0.0, 1.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    cube(4, 0.1, 0.1);//stand2
    glPopMatrix();
    glPushMatrix();
    swingseat();
    glPopMatrix();
    glPopMatrix();
}

//void ladder() {
//    glPushMatrix();
//    glColor3f(0, 0, 1);
//    GLfloat amb48[] = { 0,0,1,1 };
//    GLfloat dif48[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//    GLfloat spec48[] = { 1,1,1,1 };
//    GLfloat shin48[] = { 50 };
//    material(amb48, dif48, spec48, shin48);
//    glTranslatef(0, 4, 0);
//    glRotatef(90, 0, 1, 0);
//    glScalef(0.5, 8, 0.5);
//    glutSolidCube(1);
//    glPopMatrix();
//
//    glPushMatrix();
//    glColor3f(0, 0, 1);
//    material(amb48, dif48, spec48, shin48);
//    glTranslatef(3, 4, 0);
//    glRotatef(90, 0, 1, 0);
//    glScalef(0.5, 6, 0.5);
//    glutSolidCube(1);
//    glPopMatrix();
//
//    glPushMatrix();//horizontal bars back
//    for (float i = 2; i < 8; i += 2)
//    {
//        glPushMatrix();
//        glColor3f(1, 0, 0);
//        GLfloat amb49[] = {1,0,0,1 };
//        GLfloat dif49[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//        GLfloat spec49[] = { 1,1,1,1 };
//        GLfloat shin49[] = { 50 };
//        material(amb49, dif49, spec49, shin49);
//        glTranslatef(1.5, i, 0);
//        glRotatef(90, 0, 0, 1);
//        glScalef(0.5, 2.4, 0.5);
//        glutSolidCube(1);
//        glPopMatrix();
//    }
//
//}

void merrygo() {
    glPushMatrix();
    glTranslatef(0, 2, 0);
    glColor3f(1, 0, 0);
    GLfloat amb70[] = { 1,0,0,1 };
    GLfloat dif70[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec70[] = { 1,1,1,1 };
    GLfloat shin70[] = { 50 };
    material(amb70, dif70, spec70, shin70);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    draw_cylinder(2, 0.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0, 0);
    material(amb70, dif70, spec70, shin70);
    glTranslatef(0, 4, 0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    cube(2, 0.1, 0.1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0, 0);
    material(amb70, dif70, spec70, shin70);
    glTranslatef(0, 6, 0);
    //glRotatef(90.0, 0.0, 0.0, 1.0);
    cube(1.5, 0.1, 0.1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0, 0);
    material(amb70, dif70, spec70, shin70);
    glTranslatef(0, 6, 0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    cube(1.5, 0.1, 0.1);
    glPopMatrix();
}

//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
void drawPark() {

    //--------------------------------floor(Ground)--------------------------------------------------

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0, 1, 0);
    GLfloat amb50[] = { 0, 1, 0,1 };
    GLfloat dif50[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec50[] = { 1,1,1,1 };
    GLfloat shin50[] = { 50 };
    material(amb50, dif50, spec50, shin50);

    glVertex3f(50, 0, 50);
    glVertex3f(-50, 0, 50);
    glVertex3f(-50, 0, -50);
    glVertex3f(50, 0, -50);

    glEnd();
    glPopMatrix();

    //----------------------------------draw walls-----------------------------------------------------
    // right wall
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, 0.5, 50);
    wall();
    glPopMatrix();

    // left wall
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, 0.5, -50);
    wall();
    glPopMatrix();

    // back wall
    glPushMatrix();
    glTranslatef(0, 0.5, -50);
    wall();
    glPopMatrix();

    // front wall
    glPushMatrix();
    glTranslatef(30, 0.5, 50);
    glScalef(0.4, 1, 1);
    wall();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30, 0.5, 50);
    glScalef(0.4, 1, 1);
    wall();
    glPopMatrix();

    //------------------------------------draw trees------------------------------------------
    for (float i = -48; i <= 50; i += 15)
    {
        glPushMatrix();
        glTranslatef(-48, 17, i);
        tree();
        glPopMatrix();
    }

    for (float i = -48; i <= 50; i += 15)
    {
        glPushMatrix();
        glTranslatef(48, 17, i);
        tree();
        glPopMatrix();
    }

    //for (float i = -48; i < 40; i += 15) //TREES BACK
    //{
    //    glPushMatrix();
    //    glTranslatef(i, 17, -48);
    //    tree();
    //    glPopMatrix();
    //}

    //-----------------------------draw slide--------------------------------------------
    glPushMatrix();
    glTranslatef(20, -15, 0);
    glScalef(5, 5, 5);
    slide();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20, -15, -10);
    glScalef(5, 5, 5);
    //slide();
    glPopMatrix();

    //--------------------------------Climber construction-Monkey bar----------------------------------
    glPushMatrix();
    glTranslatef(30, 0, -40);
    glScalef(1, 1, 1);
    MonkeyBar();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20, 0, -40);
    glScalef(1, 1, 1);
    MonkeyBar();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 0, -40);
    glScalef(1, 1, 1);
    MonkeyBar();
    glPopMatrix();

    //--------------------------------------Cylinder-------------------------------------
    glPushMatrix();
    glTranslatef(20, 0, 35);
    glScalef(1, 1, 1);

    glPushMatrix();
    glTranslatef(5, 0, 10);
    glRotatef(90, -1, 0, 0);
    draw_cylinder(5, 2);
    glPopMatrix();

    //--------------------------------------------Net-------------------------------------
    glPushMatrix();
    glColor3f(1, 0, 0);
    GLfloat amb51[] = { 1,0,0,1 };
    GLfloat dif51[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec51[] = { 1,1,1,1 };
    GLfloat shin51[] = { 50 };
    material(amb51, dif51, spec51, shin51);
    glTranslatef(5, 2, 10);
    glRotatef(90, -1, 0, 0);
    glutWireCone(5, 8, 15, 15);
    glPopMatrix();

    glPopMatrix();

    //-----------------------------------------------Box-mesh-1 bottom----------------------------
    glPushMatrix();
    glColor3f(1, 0, 0);
    GLfloat amb52[] = { 1,0,0,1 };
    GLfloat dif52[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec52[] = { 1,1,1,1 };
    GLfloat shin52[] = { 50 };
    material(amb52, dif52, spec52, shin52);
    glTranslatef(50, -0.5, 15);//bottom
    glLineWidth(3);

    glPushMatrix();
    material(amb52, dif52, spec52, shin52);
    glTranslatef(-30, 2, -20);
    glScalef(1, 1, 1);
    glutWireCube(2);
    glPopMatrix();

    glPushMatrix();
    material(amb52, dif52, spec52, shin52);
    glTranslatef(-30, 2, -22);
    glutWireCube(2);
    glPopMatrix();


    for (float i = 0; i < 2; i += 1)
    {
        glPushMatrix();
        material(amb52, dif52, spec52, shin52);
        glTranslatef(-28, 2, -20 - 2 * i);
        glutWireCube(2);
        glPopMatrix();
    }

    ////2nd row
    for (float i = 0; i < 2; i += 1)
    {
        glPushMatrix();
        material(amb52, dif52, spec52, shin52);
        glTranslatef(-30, 4, -20 - 2 * i);
        glutWireCube(2);
        glPopMatrix();
    }

    for (float i = 0; i < 2; i += 1)
    {
        glPushMatrix();
        material(amb52, dif52, spec52, shin52);
        glTranslatef(-28, 4, -20 - 2 * i);
        glutWireCube(2);
        glPopMatrix();
    }

    ////3rd row
    for (float i = 0; i < 2; i += 1)
    {
        glPushMatrix();
        material(amb52, dif52, spec52, shin52);
        glTranslatef(-30, 6, -20 - 2 * i);
        glutWireCube(2);
        glPopMatrix();
    }

    for (float i = 0; i < 2; i += 1)
    {
        glPushMatrix();
        material(amb52, dif52, spec52, shin52);
        glTranslatef(-28, 6, -20 - 2 * i);
        glutWireCube(2);
        glPopMatrix();
    }

    //4th row
    for (float i = 0; i < 2; i += 1)
    {
        glPushMatrix();
        material(amb52, dif52, spec52, shin52);
        glTranslatef(-30, 8, -20 - 2 * i);
        glutWireCube(2);
        glPopMatrix();
    }

    for (float i = 0; i < 2; i += 1)
    {
        glPushMatrix();
        material(amb52, dif52, spec52, shin52);
        glTranslatef(-28, 8, -20 - 2 * i);
        glutWireCube(2);
        glPopMatrix();
    }

    glPopMatrix();

    //------------------------------------------------box-mesh 2------------------------------------

    glPushMatrix();
    glColor3f(1, 0, 0);
    GLfloat amb53[] = { 1,0,0,1 };
    GLfloat dif53[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec53[] = { 1,1,1,1 };
    GLfloat shin53[] = { 50 };
    material(amb53, dif53, spec53, shin53);
    glTranslatef(50, -0.5, 5);
    glLineWidth(3);

    glPushMatrix();
    material(amb53, dif53, spec53, shin53);
    glTranslatef(-30, 2, -20);
    glScalef(1, 1, 1);
    glutWireCube(2);
    glPopMatrix();

    glPushMatrix();
    material(amb53, dif53, spec53, shin53);
    glTranslatef(-28, 2, -20);
    glutWireCube(2);
    glPopMatrix();

    glPushMatrix();
    material(amb53, dif53, spec53, shin53);
    glTranslatef(-30, 2, -22);
    glutWireCube(2);
    glPopMatrix();

    glPushMatrix();
    material(amb53, dif53, spec53, shin53);
    glTranslatef(-30, 2, -24);
    glutWireCube(2);
    glPopMatrix();

    for (float i = 0; i < 3; i += 1)
    {
        glPushMatrix();
        material(amb53, dif53, spec53, shin53);
        glTranslatef(-28, 2, -20 - 2 * i);
        glutWireCube(2);
        glPopMatrix();
    }

    for (float i = 0; i < 3; i += 1)
    {
        glPushMatrix();
        material(amb53, dif53, spec53, shin53);
        glTranslatef(-26, 2, -20 - 2 * i);
        glutWireCube(2);
        glPopMatrix();
    }

    //2nd row
    for (float i = 0; i < 3; i += 1)
    {
        glPushMatrix();
        material(amb53, dif53, spec53, shin53);
        glTranslatef(-30, 4, -20 - 2 * i);
        glutWireCube(2);
        glPopMatrix();
    }

    for (float i = 0; i < 3; i += 1)
    {
        glPushMatrix();
        material(amb53, dif53, spec53, shin53);
        glTranslatef(-28, 4, -20 - 2 * i);
        glutWireCube(2);
        glPopMatrix();
    }

    for (float i = 0; i < 3; i += 1)
    {
        glPushMatrix();
        material(amb53, dif53, spec53, shin53);
        glTranslatef(-26, 4, -20 - 2 * i);
        glutWireCube(2);
        glPopMatrix();
    }

    ////3rd row
    for (float i = 0; i < 3; i += 1)
    {
        glPushMatrix();
        material(amb53, dif53, spec53, shin53);
        glTranslatef(-30, 6, -20 - 2 * i);
        glutWireCube(2);
        glPopMatrix();
    }

    for (float i = 0; i < 3; i += 1)
    {
        glPushMatrix();
        material(amb53, dif53, spec53, shin53);
        glTranslatef(-28, 6, -20 - 2 * i);
        glutWireCube(2);
        glPopMatrix();
    }

    for (float i = 0; i < 3; i += 1)
    {
        glPushMatrix();
        material(amb53, dif53, spec53, shin53);
        glTranslatef(-26, 6, -20 - 2 * i);
        glutWireCube(2);
        glPopMatrix();
    }

    //4th row
    for (float i = 0; i < 3; i += 1)
    {
        glPushMatrix();
        material(amb53, dif53, spec53, shin53);
        glTranslatef(-30, 8, -20 - 2 * i);
        glutWireCube(2);
        glPopMatrix();
    }

    for (float i = 0; i < 3; i += 1)
    {
        glPushMatrix();
        material(amb53, dif53, spec53, shin53);
        glTranslatef(-28, 8, -20 - 2 * i);
        glutWireCube(2);
        glPopMatrix();
    }

    for (float i = 0; i < 3; i += 1)
    {
        glPushMatrix();
        material(amb53, dif53, spec53, shin53);
        glTranslatef(-26, 8, -20 - 2 * i);
        glutWireCube(2);
        glPopMatrix();
    }
    glPopMatrix();

    //-------------------------------------------------------------------------------
    //glPushMatrix();
    //glTranslatef(0, 2,0);
    //glColor3f(0, 0, 1);
    //glBegin(GL_QUADS);
    //glVertex3f(-30, 0, -15);
    //glVertex3f(-26, 0, -15);
    //glVertex3f(-28, 3, -15);
    //glEnd();
    //glPopMatrix();

    //----------------------------Roads---------------------------------------------------------
    glPushMatrix();
    glColor3f(0.178, 0.190, 0.181);
    GLfloat amb54[] = { 0.178, 0.190, 0.181,1 };
    GLfloat dif54[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec54[] = { 1,1,1,1 };
    GLfloat shin54[] = { 50 };
    material(amb54, dif54, spec54, shin54);
    //glTranslatef(0, 0.5, 0);
    glBegin(GL_QUADS);
    glVertex3f(-5, 0.5, 50);
    glVertex3f(-5, 0.5, -50);
    glVertex3f(5, 0.5, -50);
    glVertex3f(5, 0.5, 50);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.178, 0.190, 0.181);
    material(amb54, dif54, spec54, shin54);
    //glTranslatef(0, 0.5, 0);
    glBegin(GL_QUADS);
    glVertex3f(-50, 0.5, -3);
    glVertex3f(50, 0.5, -3);
    glVertex3f(50, 0.5, 2);
    glVertex3f(-50, 0.5, 2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.178, 0.190, 0.181);
    material(amb54, dif54, spec54, shin54);
    //glTranslatef(0, 0.5, 0);
    glBegin(GL_QUADS);
    glVertex3f(-50, 0.5, 35);
    glVertex3f(50, 0.5, 35);
    glVertex3f(50, 0.5, 40);
    glVertex3f(-50, 0.5, 40);
    glEnd();
    glPopMatrix();

    //----------------------------------------------------------bench----------------------------------
    //glPushMatrix();
    //bench();
    //glPopMatrix();

    glPushMatrix();
    for (float i = 0; i < 50; i += 10)
    {
        glPushMatrix();
        glTranslatef(-30, 0, 30 - 2 * i);
        bench();
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix();
    for (float i = 0; i < 50; i += 10)
    {
        glPushMatrix();
        glTranslatef(60, 0, 30 - 2 * i);
        bench();
        glPopMatrix();
    }
    glPopMatrix();

    //-----------------------------Ice cream hut------------------------------------------------------------
    glPushMatrix();
    hut();
    //drawObject();
    glPopMatrix();

    //----------------------------------------hut2-------------------------------------------------
    //glPushMatrix();
    //glTranslatef(0,0,0);
    //hut2();
    //glPopMatrix();

    //------------------------------icecream---------------------------------------------------------
    glPushMatrix();
    glTranslatef(-7, 0, -24);
    //glTranslatef(0, 0, 0);
    glScalef(2, 1.5, 2);
    icecream();
    glPopMatrix();

    //-----------------------------------------torus----------------------------------------------------
    glPushMatrix();
    glTranslatef(0, 0, 0);
    tank();
    glPopMatrix();
    //---------------------------------------------------baloon man-----------------------------------
    glPushMatrix();
    glTranslatef(-22, 0, -8);
    glRotatef(angle_b, 1.0f, 0.0f, 0.0f);
    baloonman();
    glPopMatrix();

    //---------------------------------------seasaw------------------------------------------------

    glPushMatrix();
    glTranslatef(-20, -0.5, 20);
    glScalef(2, 1, 2);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    seasaw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20, -0.5, 30);
    glScalef(2, 1, 2);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    seasaw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20, -0.5, 42);
    glScalef(2, 1, 2);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    seasaw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20, -0.5, 48);
    glScalef(2, 1, 2);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    seasaw();
    glPopMatrix();

    //--------------------------------------------Dust Bin-------------------------------------------
    glPushMatrix();
    glTranslatef(-45, 0, 37);
    glScalef(2, 2, 2);
    dustbin();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(45, 0, 37);
    glScalef(2, 2, 2);
    dustbin();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-45, 0, -45);
    glScalef(2, 2, 2);
    dustbin();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(45, 0, -45);
    glScalef(2, 2, 2);
    dustbin();
    glPopMatrix();

    //-----------------------------------------------Lamp post----------------------------------------
    glPushMatrix();
    glTranslatef(0, 0, -49);
    lamp();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-49, 0, 0);
    lamp();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(49, 0, 0);
    lamp();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-49, 0, 49);
    lamp();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(49, 0, 49);
    lamp();
    glPopMatrix();

    //----------------------swing-construction--------------------------------------------------
    glPushMatrix();
    glTranslatef(-10, 15.0, 10);
    glScalef(1, 1.5, 1);
    swing();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30, 15.0, 10);
    glScalef(1, 1.5, 1);
    swing();
    glPopMatrix();
    //-----------------------------------spring Rider-----------------------------------------------
    glPushMatrix();
    glTranslatef(13, 11, 30);
    springRider();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(23, 11, 30);
    springRider();
    glPopMatrix();

    //---------------------------merrygo round----------------------------------------------------
    glPushMatrix();
    //glTranslatef(0,0,0);
    glTranslatef(22, -2.3, 11);
    glRotatef(angle_m, 0, 1, 0);
    glScalef(1.2, 1.2, 1.2);
    merrygo();
    glPopMatrix();

}


void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
    //gluLookAt(0.0 + camX, 7.0 + camY, 52.0 + camZ, 0, 0, 0, 0, 1.0, 0);
    gluLookAt(0.0 + camX, 7.0 + camY, 5.0 + camZ, 0, 8, 0, 0, 1.0, 0);
    lightingFunc();

    glTranslatef(sceX, sceY, sceZ);
    glRotatef(animYRot, 0, 1, 0);
    glPushMatrix();
    glPushMatrix();
    //drawAxes();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.01, 0);
    drawPark();
    glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
    //glFlush();
}

//animation timer function
void timer(int value) {
    // Update the angle of the seesaw
    angle += deltaAngle;

    // If the angle is greater than 30 degrees or less than -30 degrees, reverse the direction
    if (angle > 30.0f || angle < -30.0f) {
        deltaAngle = -deltaAngle;
    }

    //baloon man animation
    angle_b += deltaAngle;

    if (angle_b > 10.0f || angle_b < -10.0f) {
        deltaAngle = -deltaAngle;
    }

    //swing animation
    angle_s = 15.0 * sin(time); // Update the angle using a sine function
    time += timeStep; // Increment the time by the time step

    //spring rider animation
    angle_r += deltaAngle;

    if (angle_r > 30.0f || angle_r < -30.0f) {
        deltaAngle = -deltaAngle;
    }
    angle_m += speed;

    glutPostRedisplay();
    glutTimerFunc(60, timer, 0);
}

// keyboardSpecial
void keyboardSpecial(int key, int x, int y) {
    // camera up and down
    if (key == GLUT_KEY_UP) {
        camY += 1;
    }
    if (key == GLUT_KEY_DOWN) {
        camY -= 1;
    }

    // camera left and right
    if (key == GLUT_KEY_LEFT) {
        camX -= 1;
    }
    if (key == GLUT_KEY_RIGHT) {
        camX += 1;
    }

    glutPostRedisplay();
}

// keyboard move object 
void keyboard(unsigned char key, int x, int y) {

    if (key == 'l') {
        animYRot += 1;
    }
    if (key == 'r') {
        animYRot -= 1;
    }

    // Move Scene along X axis
    if (key == 'X') {
        sceX -= 1;
    }
    if (key == 'x') {
        sceX += 1;
    }
    // Move Scene along Y axis
    if (key == 'Y') {
        sceY -= 1;
    }
    if (key == 'y') {
        sceY += 1;
    }
    //Move Scene along Z axis
    if (key == 'Z') {
        sceZ -= 1;
    }
    if (key == 'z') {
        sceZ += 1;
    }

    // Control light source 1
    if (key == '1') {
        glEnable(GL_LIGHT0);
    }
    if (key == '!') {
        glDisable(GL_LIGHT0);
    }

    // Control light source 2
    if (key == '2') {
        glEnable(GL_LIGHT1);
    }
    if (key == '@') {
        glDisable(GL_LIGHT1);
    }

    glutPostRedisplay();
}


void reshape(GLsizei w, GLsizei h) {
    glViewport(0, 0, w, h);
    GLfloat aspect_ratio = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(120.0, aspect_ratio, 1.0, 100.0);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Park");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // keyboard function activation
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);

    glutTimerFunc(60, timer, 0);

    glutMainLoop();

    return 0;
}
