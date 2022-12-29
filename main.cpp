#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include <bits/stdc++.h>
#include "BmpLoader.h"
#define PI 3.1415926535898
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=800, windowWidth=800,M_PI=3.1416;
double eyeX=0.0, eyeY=500.0, eyeZ=800.0, refX = 0, refY=0,refZ=0,value=10;
int rr=0,p=0,t_angle=0.0f, t_angle2=0.0f;
GLfloat br1=0.0,br2=0.0,alpha = 0.0,alpha1 = 0.0, theta = 0.0,theta1 = 0.0, axis_x=0.0, axis_y=0.0,axis_x1=0.0, axis_y1=0.0,axis_z=0.0,rotat=0.0,upx=0,upz=0,upy=1,xx=1,yy=1,zz=1, angle_P = 270.0, angle_Y = 270.0, angle_R = 90.0;
GLboolean shp=false,brr=false,crr=false,pop=false,bRotate = false,bRotate1 = false, uRotate = false,uRotate1 = false,lamp_am=false,tlamp_on=false,lamp_duf=false,lamp_on=false,lamp_spec=false,lamp_off=true;
unsigned int ID1, ID2,ID3,ID4,ID5,ID[100];
GLfloat t1=0,t2=0,t3=0,sh1=0,cc1=0;

static void drawBox(GLfloat size, GLenum type)
{
  static GLfloat n[6][3] =
  {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };
  static GLint faces[6][4] =
  {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };
  GLfloat v[8][3];
  GLint i;

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

  for (i = 5; i >= 0; i--) {
    glBegin(type);
    glNormal3fv(&n[i][0]);
    glVertex3fv(&v[faces[i][0]][0]);glTexCoord2f(0,0);
    glVertex3fv(&v[faces[i][1]][0]);glTexCoord2f(0,1);
    glVertex3fv(&v[faces[i][2]][0]);glTexCoord2f(1,1);
    glVertex3fv(&v[faces[i][3]][0]);glTexCoord2f(1,0);
    glEnd();
  }
}

static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void drawcube(float r,float g,float b,float alp,float sh)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, alp };
    GLfloat mat_ambient[] = { r, g, b, alp };
    GLfloat mat_diffuse[] = { r, g, b, alp };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, alp };
    GLfloat mat_shininess[] = {sh};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    drawBox(1,GL_QUADS);
}


void drawtrapezoid(float r,float g,float b,float alp,float sh)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, alp };
    GLfloat mat_ambient[] = { r, g, b, alp };
    GLfloat mat_diffuse[] = { r, g, b, alp };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, alp };
    GLfloat mat_shininess[] = {sh};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);
    //Trapezoid
    glVertex3f(0.0f, 0.0f, 0.5f);
    glVertex3f(2.0f, 0.0f, 0.5f);
    glVertex3f(1.5f, 1.0f, 0.0f);
    glVertex3f(0.50f, 1.0f, 0.0f);

    glEnd();
}

void drawsphere(GLfloat a,GLfloat b,GLfloat c,GLfloat r,int rrr)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { a*0.5,b*0.5, c*0.5, 1.0 };
    GLfloat mat_diffuse[] = { a, b, c, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};
    GLfloat mat_emission1[] = { 1,1,1, 0.0 };

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    if(rrr==1  && tlamp_on==true) glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission1);
    else glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    GLUquadricObj *obj=gluNewQuadric();
    gluQuadricTexture(obj,GL_TRUE);
    gluSphere(obj,r,50,20);
    gluDeleteQuadric(obj);

}

void drawcylinder(GLfloat a,GLfloat b,GLfloat c,GLfloat d)
{
    GLfloat mat_ambient[] = { a*0.5,b*0.5, c*0.5, 1.0 };
    GLfloat mat_diffuse[] = { a, b, c, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

   glPushMatrix();
    glRotatef(90,1,0,0);
    glBegin(GL_QUAD_STRIP);
    GLUquadricObj *obj = gluNewQuadric();
    gluQuadricTexture(obj,TRUE);
    gluCylinder(obj, 3.0, 3, 7, 20, 30);
    gluDeleteQuadric(obj);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glBegin(GL_QUAD_STRIP);
    GLUquadricObj *obj1 = gluNewQuadric();
    gluQuadricTexture(obj1,TRUE);
    gluDisk(obj1, d, 3, 20, 30);
    gluDeleteQuadric(obj1);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-6.7,0);
    glRotatef(90,1,0,0);
    glPushMatrix();
    glBegin(GL_QUAD_STRIP);
    GLUquadricObj *obj2 = gluNewQuadric();
    //gluQuadricTexture(obj2,TRUE);
    gluDisk(obj2, d, 3, 20, 30);
    gluDeleteQuadric(obj2);
    glEnd();
    glPopMatrix();
    glPopMatrix();

}

void light()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient1[]  = {.3, .3, .3, 1.0};
    GLfloat light_ambient2[]  = {1, 1, 1, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 0.0,0.0, 1.0 };
    //GLfloat light_positiondir[] = { 0.0, 0.0, 1.0 };





   /* glEnable( GL_LIGHT0);
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient1);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    //glLightfv( GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction2);*/




    GLfloat light_position4[] = { 0, 1000, 0, 1.0 };
    GLfloat spot_direction4[] = { 0.0, -10, 0.0 };
    //glEnable( GL_LIGHT4);
    glLightfv( GL_LIGHT4, GL_AMBIENT, light_ambient2);
    glLightfv( GL_LIGHT4, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT4, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT4, GL_POSITION, light_position4);
    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spot_direction4);
    glLightf( GL_LIGHT4, GL_SPOT_CUTOFF, 70.0);

    GLfloat light_position1[] = { 25,300,15, 1.0 };
    GLfloat spot_direction1[] = { 25, -20, 15.0 };
   // glEnable( GL_LIGHT1);
    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient1);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT1, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction1);
    glLightf( GL_LIGHT1, GL_SPOT_CUTOFF, 15.0);

    GLfloat light_position3[] = { 0, 300, 0, 1.0 };
    GLfloat spot_direction3[] = { 5, -20, 0.0 };
    //glEnable( GL_LIGHT3);
    glLightfv( GL_LIGHT3, GL_AMBIENT, light_ambient2);
    glLightfv( GL_LIGHT3, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT3, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT3, GL_POSITION, light_position3);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction3);
    glLightf( GL_LIGHT3, GL_SPOT_CUTOFF, 20.0);

    GLfloat light_position2[] = { -5, 300, 0, 1.0 };
    GLfloat spot_direction2[] = { -5, -20, 0.0 };
    //glEnable( GL_LIGHT2);
    glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient2);
    glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT2, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction2);
    glLightf( GL_LIGHT2, GL_SPOT_CUTOFF, 20.0);


    /*GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 10.0);*/
}

void emit(float r,float g,float b,float alp,float sh)
{
   GLfloat no_mat[] = { 0.0, 0.0, 0.0, alp };
    GLfloat mat_ambient[] = { r, g, b, alp };
    GLfloat mat_diffuse[] = { r, g, b, alp };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, alp };
    GLfloat mat_shininess[] = {sh};
    GLfloat mat_emission1[] = { 1,1,0, 0.0 };

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission1);
    drawBox(1,GL_QUADS);
}

void LoadTexture(const char*filename,int a)
{
    glGenTextures(1, &ID[a]);
    glBindTexture(GL_TEXTURE_2D, ID[a]);
    //printf("%d",ID[a]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID[a]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

void sky()
{
    glBindTexture(GL_TEXTURE_2D, ID[6]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    //sky

    //glTranslatef(50,0,200);
    glRotatef(rotat,0,1,0);
    glRotatef(90,0,0,1);
    drawsphere(1,1,1,1000,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    /*glBindTexture(GL_TEXTURE_2D, ID[34]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();//sun
    glTranslatef(0,50,-15);
    drawsphere(1,1,1,3);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);*/


}

void land_p()
{
    glBindTexture(GL_TEXTURE_2D, ID[1]);
    glEnable(GL_TEXTURE_2D);
    //1st
    glPushMatrix();
    //glTranslatef(300,55,0);
    //glScalef(300,20,3);
    //drawcube(1,1,1,1,60);
    drawsphere(0,1,0,3,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-.3,2);
    //glScalef(300,20,3);
    //drawcube(1,1,1,1,60);
    drawsphere(0,1,0,3,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,4);
    //glScalef(300,20,3);
    //drawcube(1,1,1,1,60);
    drawsphere(0,1,0,3,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2,-.5,0);
    //glScalef(300,20,3);
    //drawcube(1,1,1,1,60);
    drawsphere(0,1,0,3,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4,-1,0);
    //glScalef(300,20,3);
    //drawcube(1,1,1,1,60);
    drawsphere(0,1,0,3,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4,-1.5,1);
    //glScalef(300,20,3);
    //drawcube(1,1,1,1,60);
    drawsphere(0,1,0,3,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4,-1,4);
    //glScalef(300,20,3);
    //drawcube(1,1,1,1,60);
    drawsphere(0,1,0,3,0);
    glPopMatrix();

    //2nd
    glPushMatrix();
    glTranslatef(0,-1,5);
    //glScalef(300,20,3);
    //drawcube(1,1,1,1,60);
    drawsphere(0,1,0,3,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-1.5,7);
    //glScalef(300,20,3);
    //drawcube(1,1,1,1,60);
    drawsphere(0,1,0,3,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-1,9);
    //glScalef(300,20,3);
    //drawcube(1,1,1,1,60);
    drawsphere(0,1,0,3,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-1.5,11);
    //glScalef(300,20,3);
    //drawcube(1,1,1,1,60);
    drawsphere(0,1,0,3,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4,-2,7);
    //glScalef(300,20,3);
    //drawcube(1,1,1,1,60);
    drawsphere(0,1,0,3,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4,-1.5,10);
    //glScalef(300,20,3);
    //drawcube(1,1,1,1,60);
    drawsphere(0,1,0,3,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4,-2,8);
    //glScalef(300,20,3);
    //drawcube(1,1,1,1,60);
    drawsphere(0,1,0,3,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void land_t()
{
    for(int i=0;i<10;i++)
    {
       glPushMatrix();
      glTranslatef(0,0,i*5);
    //glScalef(300,20,3);
    //drawcube(1,1,1,1,60);
      land_p();
      glPopMatrix();
    }


}

void land()
{
    //l_land
    glPushMatrix();
    glTranslatef(-85,0,0);
   /* glPushMatrix();
    glTranslatef(-4,0,0);
    glScalef(3,3,7);
    //drawcube(1,1,1,1,60);
    land_t();
    glPopMatrix();*/

    glPushMatrix();
    glTranslatef(-10,0,0);
    glScalef(10,1,7);
    //drawcube(1,1,1,1,60);
    land_t();
    glPopMatrix();
    glPopMatrix();

    //river hole
    /*glPushMatrix();
    glTranslatef(15,-20,200);
    glScalef(1,40,400);
    drawcube(1,1,1,1,60);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(65,-20,200);
    glScalef(1,40,400);
    drawcube(1,1,1,1,60);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(40,-40,200);
    glScalef(50,1,400);
    drawcube(1,1,1,1,60);
    glPopMatrix();*/

    //r_land
    glPushMatrix();
    glTranslatef(180,0,0);
    //glRotatef( 180,0, 1, 0.0 );
    /*glPushMatrix();
    glTranslatef(-4,0,0);
    glScalef(3,3,7);
    //drawcube(1,1,1,1,60);
    land_t();
    glPopMatrix();*/

    glPushMatrix();
    glTranslatef(-10,0,0);
    glScalef(10,1,7);
    //drawcube(1,1,1,1,60);
    land_t();
    glPopMatrix();
    glPopMatrix();
}

void river()
{
    if(pop==false)
    {glBindTexture(GL_TEXTURE_2D, ID[8]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(20,-3,200);
    glScalef(180,1,410);
    drawcube(1,1,1,1,60);
    glPopMatrix();
     glDisable(GL_TEXTURE_2D);}
     else

     {glBindTexture(GL_TEXTURE_2D, ID[8]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(20,-3,200.5);
    glScalef(180,1,410);
    drawcube(1,1,1,1,60);
    glPopMatrix();
     glDisable(GL_TEXTURE_2D);}
}

void trapi(float r,float g,float b)
{
    //base
    glPushMatrix();
    glScalef(1, .05, 1);
    glTranslatef(.7,20,-.52);
    //glRotatef( alpha,axis_x, axis_y, 0.0 );
    //glRotatef( theta, axis_x, axis_y, 0.0 );
    drawcube(r,g,b,1,60);
    glPopMatrix();

    //side-1
    glPushMatrix();
    glScalef(1, 1, 1);
    glTranslatef(-.3,0,0);
    //glRotatef( alpha,axis_x, axis_y, 0.0 );
    //glRotatef( theta, axis_x, axis_y, 0.0 );
    drawtrapezoid(r,g,b,1,60);
    glPopMatrix();

    //side-2
    glPushMatrix();
    glScalef(1, 1, 1);
    glTranslatef(1.2,0,.5);
    glRotatef( 90,0, 1, 0.0 );
    //glRotatef( theta, axis_x, axis_y, 0.0 );
    drawtrapezoid(r,g,b,1,60);
    glPopMatrix();

    //side-3
    glPushMatrix();
    glScalef(1, 1, 1);
    glTranslatef(1.7,0,-1);
    glRotatef( 180,0, 1, 0.0 );
    //glRotatef( theta, axis_x, axis_y, 0.0 );
    drawtrapezoid(r,g,b,1,60);
    glPopMatrix();

    //side-4
    glPushMatrix();
    glScalef(1, 1, 1);
    glTranslatef(.2,0,-1.5);
    glRotatef( 270,0, 1, 0.0 );
    //glRotatef( theta, axis_x, axis_y, 0.0 );
    drawtrapezoid(r,g,b,1,60);
    glPopMatrix();

}

void bridge_p()
{
    glBindTexture(GL_TEXTURE_2D, ID[3]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(60,3,120);
    drawcube(1,1,1,1,60);
    //drawcube(.2,.2,.2,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[4]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    //glTranslatef(0,50,0);
    glScalef(60,20,3);
    drawcube(1,1,1,1,60);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,60);
    glScalef(60,20,3);
    drawcube(1,1,1,1,60);
    //drawcube(.2,.2,.2,1,60);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-60);
    glScalef(60,20,3);
    drawcube(1,1,1,1,60);
    //drawcube(.2,.2,.2,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void bridge_string()
{
    glPushMatrix();
     glTranslatef(-50,0,0);
    glRotatef(55,0,0,1);
    glPushMatrix();
    glScalef(180,1,1);
    //drawcube(1,1,1,1,60);
    drawcube(1,1,1,1,60);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
     glTranslatef(-40,-15,0);
    glRotatef(55,0,0,1);
    glPushMatrix();
    glScalef(145,1,1);
    //drawcube(1,1,1,1,60);
    drawcube(1,1,1,1,60);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
     glTranslatef(-30,-30,0);
    glRotatef(55,0,0,1);
    glPushMatrix();
    glScalef(110,1,1);
    //drawcube(1,1,1,1,60);
    drawcube(1,1,1,1,60);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
     glTranslatef(-20,-45,0);
    glRotatef(55,0,0,1);
    glPushMatrix();
    glScalef(75,1,1);
    //drawcube(1,1,1,1,60);
    drawcube(1,1,1,1,60);
    glPopMatrix();
    glPopMatrix();
}

void bridge_upper()
{
    //front
   glPushMatrix();
   glTranslatef(0,-30,55);
    glScalef(15,250,7);
    //drawcube(1,1,1,1,60);
    drawcube(.3,0,0,1,60);
    glPopMatrix();

    glPushMatrix();
   glTranslatef(0,0,55);
   glRotatef(180,0,1,0);
    bridge_string();
    glPopMatrix();

    glPushMatrix();
   glTranslatef(0,0,55);
    bridge_string();
    glPopMatrix();

    //back
    glPushMatrix();
   glTranslatef(0,-30,-55);
    glScalef(15,250,7);
    //drawcube(1,1,1,1,60);
    drawcube(.3,0,0,1,60);
    glPopMatrix();

    glPushMatrix();
   glTranslatef(0,0,-55);
    bridge_string();
    glPopMatrix();

    glPushMatrix();
   glTranslatef(0,0,-55);
   glRotatef(180,0,1,0);
    bridge_string();
    glPopMatrix();

    //middle
    glPushMatrix();
   glTranslatef(0,50,0);
    glScalef(7,15,110);
    //drawcube(1,1,1,1,60);
    drawcube(.3,0,0,1,60);
    glPopMatrix();

}

void bridge()
{

    //l_moving
    glPushMatrix();
    glTranslatef(t1,t2,t3);
    glTranslatef(-30,65,0);
    glRotatef(br1,0,0,1);
    bridge_p();
    glPopMatrix();

    //r_moving
    glPushMatrix();
    glRotatef(180,0,1,0);
    glTranslatef(t1,t2,t3);
    glTranslatef(-30,65,0);
    glRotatef(br1,0,0,1);

    bridge_p();
    glPopMatrix();

    //l
    glPushMatrix();
    glTranslatef(-180,65,0);
    glScalef(4,1,1);
    bridge_p();
    glPopMatrix();

    //r
    glPushMatrix();
    glTranslatef(180,65,0);
    glScalef(4,1,1);
    bridge_p();
    glPopMatrix();

    //l
    glPushMatrix();
    glTranslatef(-165,140,0);
    bridge_upper();
    glPopMatrix();

    //r
    glPushMatrix();
    glTranslatef(165,140,0);
    bridge_upper();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, ID[4]);
    glEnable(GL_TEXTURE_2D);

    //base
    glPushMatrix();//chaka 1
    glTranslatef(-300,60,0);
    //glRotatef(90,1,0,0);
    glScalef(10,10,10);
    drawcylinder(1,1,1,.75);
    glPopMatrix();

    glPushMatrix();//chaka 1
    glTranslatef(300,60,0);
    //glRotatef(90,1,0,0);
    glScalef(10,10,10);
    drawcylinder(1,1,1,.75);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

glPopMatrix();

}

void road_p()
{
    glBindTexture(GL_TEXTURE_2D, ID[3]);
    glEnable(GL_TEXTURE_2D);
  glPushMatrix();
  //glTranslatef(40,0,25);
  //glRotatef( 15,0, 1, 0.0 );
    glScalef(.7,.7,1.3);
    glPushMatrix();
    glTranslatef(300,50,-27.5);
    glScalef(300,10,50);
    drawcube(1,1,1,1,60);
    //drawcube(.2,.2,.2,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[4]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(300,55,0);
    glScalef(300,20,3);
    drawcube(1,1,1,1,60);
    //drawcube(.2,.2,.2,1,60);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300,55,-50);
    glScalef(300,20,3);
    drawcube(1,1,1,1,60);
    //drawcube(.2,.2,.2,1,60);
    glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void all_r()
{
    glPushMatrix();
    glPushMatrix();
    glTranslatef(200,50,30);
    glRotatef( 15,0, 1, 0 );
    glRotatef( -10,0, 0, 1 );
    road_p();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(180,50,30);
    glRotatef( -10,0, 0, 1 );
    glRotatef( -15,0, 1, 0 );
    road_p();
    glPopMatrix();
    glPopMatrix();


}

void road()
{
   glPushMatrix();
    all_r();
    glPopMatrix();

    glPushMatrix();
    //glTranslatef(200,50,30);
    glRotatef( 180,0, 1, 0 );
    all_r();
    glPopMatrix();
}

void footpath()
{
    glBindTexture(GL_TEXTURE_2D, ID[10]);
    glEnable(GL_TEXTURE_2D);
     glPushMatrix();
     glTranslatef(300,12,200);
    glScalef(50,20,700);
    drawcube(1,1,1,1,60);
    //drawcube(.2,.2,.2,1,60);
    glPopMatrix();


    glPushMatrix();
     glTranslatef(275,12,200);
    glScalef(5,50,700);
    //drawcube(1,1,1,1,60);
    drawcube(.2,.2,.2,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     glTranslatef(275,50,200);
    glScalef(2.5,60,2.5);
    //drawcube(1,1,1,1,60);
    drawcube(0,0,0,1,60);
    glPopMatrix();

    glPushMatrix();
    //sky
    glTranslatef(275,80,200);
    drawsphere(1,1,1,3,1);
    glPopMatrix();

}

void parking()
{
    glBindTexture(GL_TEXTURE_2D, ID[11]);
    glEnable(GL_TEXTURE_2D);
   glPushMatrix();
     glTranslatef(375,11,250);
    glScalef(100,20,300);
    drawcube(1,1,1,1,60);
    //drawcube(.3,.3,.3,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void containers()
{

    glPushMatrix();
     glTranslatef(-375,30,250);
    glScalef(30,30,60);
    //drawcube(1,1,1,1,60);
    drawcube(.6,0,0,1,60);
    glPopMatrix();

    glPushMatrix();
     glTranslatef(-375,60,249);
    glScalef(30,30,60);
    //drawcube(1,1,1,1,60);
    drawcube(0,0,.6,1,60);
    glPopMatrix();

    glPushMatrix();
     glTranslatef(-375,30,320);
    glScalef(30,30,60);
    //drawcube(1,1,1,1,60);
    drawcube(.6,0,0,1,60);
    glPopMatrix();

    glPushMatrix();
     glTranslatef(-375,30,180);
    glScalef(30,30,60);
    //drawcube(1,1,1,1,60);
    drawcube(0,0,.6,1,60);
    glPopMatrix();

    glPushMatrix();
     glTranslatef(-375,60,180);
    glScalef(30,30,60);
    //drawcube(1,1,1,1,60);
    drawcube(0,.3,0,1,60);
    glPopMatrix();

    glPushMatrix();
     glTranslatef(-375,90,180);
    glScalef(30,30,60);
    //drawcube(1,1,1,1,60);
    drawcube(.6,0,0,1,60);
    glPopMatrix();

    glPushMatrix();
     glTranslatef(-375,30,400);
    glScalef(30,30,60);
    //drawcube(1,1,1,1,60);
    drawcube(0,.3,0,1,60);
    glPopMatrix();

    glPushMatrix();
     glTranslatef(-375,60,400);
    glScalef(30,30,60);
    //drawcube(1,1,1,1,60);
    drawcube(0.6,0,0,1,60);
    glPopMatrix();

    glPushMatrix();
     glTranslatef(-375,90,400);
    glScalef(30,30,60);
    //drawcube(1,1,1,1,60);
    drawcube(0,0,.6,1,60);
    glPopMatrix();

}

void cran()
{

    glPushMatrix();
     glTranslatef(-240,80,180);
     glScalef(10,150,10);
    drawcube(.95,.73,.09,1,60);
    glPopMatrix();

    glPushMatrix();
     glTranslatef(-210,150,180);
     glScalef(50,7,7);
    drawcube(.95,.73,.09,1,60);
    glPopMatrix();

    glPushMatrix();
     glTranslatef(-240,80,350);
     glScalef(10,150,10);
    drawcube(.95,.73,.09,1,60);
    glPopMatrix();

    glPushMatrix();
     glTranslatef(-210,150,350);
     glScalef(50,7,7);
    drawcube(.95,.73,.09,1,60);
    glPopMatrix();
}

void shipyard()
{
        glPushMatrix();
        glTranslatef(-80,10,100);
    glScalef(.7,.7,.7);
    //yard
    glPushMatrix();
     glTranslatef(-320,11,250);
    glScalef(200,20,500);
    //drawcube(1,1,1,1,60);
    drawcube(.3,.3,.3,1,60);
    glPopMatrix();

    //container
   glPushMatrix();
     glTranslatef(50,0,-50);
    //drawcube(1,1,1,1,60);
    containers();
    glPopMatrix();

    glPushMatrix();
     glRotatef( 180,0, 1, 0.0 );
     glTranslatef(750,0,-500);
    //drawcube(1,1,1,1,60);
    containers();
    glPopMatrix();

    glPushMatrix();
     //glTranslatef(750,0,-500);
    //drawcube(1,1,1,1,60);
    cran();
    glPopMatrix();
    glPopMatrix();

}

void car_p(float a,float b,float c)
{
    glPushMatrix();
   // glRotatef(90,0,1,0);
   glPushMatrix();
        glTranslatef(0,120,.5);
      glScalef(40,8,20);
      drawcube(a,b,c,1,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1,.95);
    glPushMatrix();
        glTranslatef(-10,125,5.5);
      glScalef(13,8,10);
      trapi(a,b,c);
    glPopMatrix();

    //glass
    //side-1
    glPushMatrix();
   // glRotatef( 90,0, 1,0.0 );
    glRotatef( -30,1, 0, 0.0 );
    glTranslatef(-10,105,72);
     glScalef(9, 6, 1);
    drawtrapezoid(0.6,0.8,1,1,60);
    glPopMatrix();

    glPushMatrix();
    glRotatef( 90,0, 1,0.0 );
    glRotatef( -30,1, 0, 0.0 );
    glTranslatef(-9.8,105,72);
     glScalef(8, 6, 1);
    drawtrapezoid(0.6,0.8,1,1,60);
    glPopMatrix();

    glPushMatrix();
    glRotatef( -90,0, 1,0.0 );
    glRotatef( -30,1, 0, 0.0 );
    glTranslatef(-8,105,73.5);
     glScalef(8, 6, 1);
    drawtrapezoid(0.6,0.8,1,1,60);
    glPopMatrix();

    glPushMatrix();
    glRotatef( 180,0, 1,0.0 );
    glRotatef( -30,1, 0, 0.0 );
    glTranslatef(-8,105,71);
     glScalef(9, 6, 1);
    drawtrapezoid(0.6,0.8,1,1,60);
    glPopMatrix();
    glPopMatrix();

    //wheel
    glPushMatrix();//chaka 1
    glTranslatef(-10,117,-9);
    glRotatef(90,1,0,0);
    glScalef(1.6,.3,1.6);
    drawcylinder(0,0,0,.75);
    glPopMatrix();

    glPushMatrix();//chaka 1
    glTranslatef(10,117,-9);
    glRotatef(90,1,0,0);
    glScalef(1.6,.3,1.6);
    drawcylinder(0,0,0,.75);
    glPopMatrix();

    glPushMatrix();//chaka 1
    glTranslatef(-10,117,12);
    glRotatef(90,1,0,0);
    glScalef(1.6,.3,1.6);
    drawcylinder(0,0,0,.75);
    glPopMatrix();

    glPushMatrix();//chaka 1
    glTranslatef(10,117,12);
    glRotatef(90,1,0,0);
    glScalef(1.6,.3,1.6);
    drawcylinder(0,0,0,.75);
    glPopMatrix();

    glPopMatrix();
}

void car()
{
    glPushMatrix();
   // glRotatef( -30,1, 0, 0.0 );
    glTranslatef(-280+cc1,-45,-30);
     //glScalef(9, 6, 1);
       car_p(.5,0,0);
    glPopMatrix();

    glPushMatrix();
    glRotatef( 180,0,1, 0.0 );
    glTranslatef(-280+cc1,-45,-30);
     //glScalef(9, 6, 1);
       car_p(0,0,.5);
    glPopMatrix();

    //paking
    glPushMatrix();
    glTranslatef(355,-91,330);
     //glScalef(9, 6, 1);
       car_p(.5,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(355,-91,300);
     //glScalef(9, 6, 1);
       car_p(.5,.5,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(355,-91,270);
     //glScalef(9, 6, 1);
       car_p(0,.5,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(355,-91,240);
     //glScalef(9, 6, 1);
       car_p(.5,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(355,-91,210);
     //glScalef(9, 6, 1);
       car_p(0,.5,.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(355,-91,180);
     //glScalef(9, 6, 1);
       car_p(.5,0,.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(355,-91,150);
     //glScalef(9, 6, 1);
       car_p(0,0,.5);
    glPopMatrix();
}

void ship_p(float a,float b,float c)
{
    glBindTexture(GL_TEXTURE_2D, ID[12]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0,0,-2);
    glRotatef(180,1,0,0);
    glRotatef(45,0,1,0);
    glScalef(1,1,1);
    trapi(a,b,c);
    glPopMatrix();

    glPushMatrix();
   // glRotatef(90,0,1,0);
    glTranslatef(0.1,.5,1);
      glScalef(2,1.5,2.2);
      drawcube(a*.5,b*.5,c*.5,1,60);
    glPopMatrix();

    glPushMatrix();
   // glRotatef(90,0,1,0);
    glTranslatef(0.1,-.5,1);
      glScalef(2.8,1.2,4);
      drawcube(a,b,c,1,60);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,2.2);
    glRotatef(180,1,0,0);
    glRotatef(45,0,1,0);
    glScalef(1,1,1);
    trapi(a,b,c);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glPushMatrix();
   // glRotatef(90,0,1,0);
    glTranslatef(0.1,1.7,1);
      glScalef(.2,2,.2);
      drawcube(1,0,0,1,60);
    glPopMatrix();

    glPushMatrix();
   // glRotatef(90,0,1,0);
    glTranslatef(0.1,1.2,.5);
      glScalef(.2,2,.2);
      drawcube(1,0,0,1,60);
    glPopMatrix();

    glPushMatrix();
   // glRotatef(90,0,1,0);
    glTranslatef(0.1,1.2,1.5);
      glScalef(.2,2,.2);
      drawcube(1,0,0,1,60);
    glPopMatrix();
}

void ship()
{

    glPushMatrix();
   // glRotatef( -30,1, 0, 0.0 );
    glTranslatef(0,25,400+sh1);
     glScalef(20,20,20);
       ship_p(1,1,1);
    glPopMatrix();

    glPushMatrix();
   // glRotatef( -30,1, 0, 0.0 );
    glTranslatef(-200,25,320);
     glScalef(20,20,20);
       ship_p(1,1,1);
    glPopMatrix();

}


void building_p(float a,float b,float c)
{
    glBindTexture(GL_TEXTURE_2D, ID[2]);
    glEnable(GL_TEXTURE_2D);
    //building1
    glPushMatrix();
    //glTranslatef(-240,80,180);
     glScalef(100,300,100);
    drawcube(a,b,c,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    for(GLfloat i=0;i<80;i+=20)
    {
        for(GLfloat j=0;j>=-200;j-=36)
        {
            glPushMatrix();
         glTranslatef(-30+i,140+j,50);
        glScalef(13,13,13);
       emit(1,1,0,1,60);
       glPopMatrix();
        }
    }
    glPopMatrix();

}

void building_f()
{


    glPushMatrix();
    glTranslatef(430,80,-500);
     //glScalef(100,300,100);
    building_p(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(430,50,-400);
     //glScalef(100,300,100);
    building_p(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(430,11,-250);
     //glScalef(100,300,100);
    building_p(1,1,1);
    glPopMatrix();

}

void building()
{
    glPushMatrix();
    building_f();
     glPopMatrix();

    glPushMatrix();
    glTranslatef(-850,0,0);
    building_f();
     glPopMatrix();
}

void makecylinder(float height,float Base)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { .6,.4,.2, 1.0 };
    GLfloat mat_diffuse[] = { .6,.4,.2, 1.0 };
    GLfloat mat_specular[] = { 1, 1,1 , 1.0 };
    GLfloat mat_shininess[] = {60};
//front phase niye kaaj hoche
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

	GLUquadricObj *qobj;
	qobj = gluNewQuadric();
	//glColor3f(247/255, 187/255, 96/255);
	glPushMatrix();
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	gluCylinder(qobj, Base, Base - (0.2 * Base), height, 20, 20);
	glPopMatrix();
}
void maketree(float height,float Base)
{

	glPushMatrix();
	float angle;
	makecylinder(height, Base);
	glTranslatef(0.0f, height,0.0f);
	height -= height * 0.2f;
	Base -= Base * 0.3f;

	if (height > 1)
	{
		angle = 22.5f;
		glPushMatrix();
		glRotatef(angle, -1.0f, 0.0f, 0.0f);
		maketree(height, Base);
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, 0.5f, 0.0f, 0.866f);
		maketree(height, Base);
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, 0.5f, 0.0f, -0.866f);
		maketree(height, Base);
		glPopMatrix();
	}
	glPopMatrix();
}

void tree_p()
{

    glPushMatrix();
    glRotatef(t_angle, 0, 1, 0);
    glRotatef(t_angle2, 0, 1, 0);
    glTranslatef(-300,0,-400);
    glScalef(10,10,10);
    maketree(4.0f,0.1f);
    glPopMatrix();


    glPushMatrix();
    glRotatef(t_angle, 0, 1, 0);
    glRotatef(t_angle2, 0, 1, 0);
    glTranslatef(-300,0,-330);
    glScalef(10,10,10);
    maketree(4.0f,0.1f);
    glPopMatrix();

    glPushMatrix();
    glRotatef(t_angle, 0, 1, 0);
    glRotatef(t_angle2, 0, 1, 0);
    glTranslatef(-300,0,-250);
    glScalef(10,10,10);
    maketree(4.0f,0.1f);
    glPopMatrix();
}

void tree()
{
    glPushMatrix();
    tree_p();
     glPopMatrix();

    glPushMatrix();
    glTranslatef(600,0,0);
    tree_p();
     glPopMatrix();
}

void park_tree()
{
     glPushMatrix();
     glRotatef(t_angle, 0, 1, 0);
    glRotatef(t_angle2, 0, 1, 0);
    glTranslatef(300,100,0);
    glScalef(.7,.7,.7);
    maketree(4.0f,0.1f);
    glPopMatrix();
}

void lamp()
{
    glPushMatrix();
    glTranslatef(0,100,0);
     glScalef(3,20,3);
       drawcube(0,0,0,1,60);
       glPopMatrix();

}

void Yaw() // x axis , p o
{
    refX = eyeX+30.0*(cos(angle_Y*3.1416/180.0));
    refZ = eyeZ+30.0*(sin(angle_Y*3.1416/180.0));
}

void Pitch() // y axis , y t
{

    refY = eyeY+30.0*(cos(angle_P*3.1416/180.0));
    refZ = eyeZ+30.0*(sin(angle_P*3.1416/180.0));

}

void Roll() // z axis ,r e
{
    upx = 100.0*(cos(angle_R*3.1416/180.0));
    upy = 100.0*(sin(angle_R*3.1416/180.0));

}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(0.6,0.8,1,0);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glFrustum(-5,5,-5,5, 4,50);
    gluPerspective(60,1,1,3000);
    //glOrtho(-5,5,-5,5, 4, 50);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ,  refX,refY,refZ,  upx,upy,upz);

    glViewport(0, 0, windowHeight, windowWidth);

    //glRotatef( 50,1, 0, 0.0 );
    glScalef(xx,yy,zz);

    light();
   sky();
     glPushMatrix();
    glTranslatef(-50,10,-550);
    glScalef(3,3,3);
    river();
    land();
    glPopMatrix();
   bridge();
    footpath();
    parking();
    shipyard();
    car();
    road();
    building();
    ship();
    tree();
    //park_tree();
    //lamp();

    glFlush();
    glutSwapBuffers();
    glDisable(GL_TEXTURE_2D);
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 'S':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;
    case 'V':
        bRotate1 = !bRotate1;
        uRotate1 = false;
        axis_x1=0.0;
        axis_y1=1.0;
        break;

    case 'b':
        upz-=1;
        eyeZ-=1;
        break;
    case 'B':
        upz+=1;
        eyeZ+=1;
        break;
    case 'y':
        angle_Y +=  value;
        //if(angle_Y>=90 || angle_Y<=-90) refZ=-refZ;
        Yaw();
        break;
    case 'Y':
        angle_Y -=  value;
        //if(angle_Y>=90 || angle_Y<=-90) refZ=-refZ;
        Yaw();
        break;
    case 'R':
        angle_R +=  value;
        //if(angle_Y>=90 || angle_Y<=-90) refZ=-refZ;
        Roll();
        break;
    case 'r':
        angle_R -=  value;
        //if(angle_Y>=90 || angle_Y<=-90) refZ=-refZ;
        Roll();
        break;
    case 'p':
        angle_P +=  value;
        //if(angle_Y>=90 || angle_Y<=-90) refZ=-refZ;
        Pitch();
        break;
    case 'P':
        angle_P -=  value;
        //if(angle_Y>=90 || angle_Y<=-90) refZ=-refZ;
        Pitch();
        break;
    case 'w': // move eye point upwards along Y axis
        eyeY+=5.0;
        break;
    case 's': // move eye point downwards along Y axis
        eyeY-=5.0;
        break;
    case 'a': // move eye point left along X axis
        eyeX-=5.0;
        break;
    case 'd': // move eye point right along X axis
        eyeX+=5.0;
        break;
    case 'i':
        //eyeX-=1.0;
        //eyeY-=1.0;
        xx+=.1;
        yy+=.1;
        zz+=.1;
        break;

    case 'o':
        //eyeX-=1.0;
        //eyeY-=1.0;
        xx-=.1;
        yy-=.1;
        zz-=.1;
        break;
    case 'Z':
        brr=!brr;
        break;

    case 'N':
        if(lamp_on==false)
        {
            lamp_on=true;
            lamp_duf=true;
            lamp_am=true;
            lamp_spec=true;
            glEnable( GL_LIGHT4);
        }
        else if(lamp_on==true)
        {
            lamp_on=false;
            lamp_duf=false;
            lamp_am=false;
            lamp_spec=false;
            glDisable( GL_LIGHT4);
        }
        break;
    case 'M':
        if(tlamp_on==false)
        {
            tlamp_on=true;
            glEnable( GL_LIGHT3);
            glEnable( GL_LIGHT2);
            glEnable( GL_LIGHT1);
        }
        else if(tlamp_on==true)
        {
            tlamp_on=false;
            glDisable( GL_LIGHT2);
            glDisable( GL_LIGHT3);
            glDisable( GL_LIGHT1);
        }
        break;
    case 'A':
        if(lamp_am==false)
            lamp_am=true;
        else lamp_am=false;
        break;
    case 'D':
        if(lamp_duf==false)
            lamp_duf=true;
        else lamp_duf=false;
        break;
    case 'C':
        if(lamp_spec==false)
            lamp_spec=true;
        else lamp_spec=false;
        break;
    case 'm':
        shp=!shp;
        break;
    case 'c':
        crr=!crr;
        break;
    case 'F':
        eyeX=0.0, eyeY=500.0, eyeZ=800.0;
        upx=0,upz=0,upy=1;
        break;
    case 'E':
        eyeX=0.0, eyeY=500.0, eyeZ=-800.0;
        upx=0,upz=0,upy=1;

        break;
     case 'L':
        eyeX=800.0, eyeY=500.0, eyeZ=0;
        upx=0,upz=0,upy=1;
        break;
     case 'I':
        eyeX=-800.0, eyeY=500.0, eyeZ=0;
        upx=0,upz=0,upy=1;
        break;
     case 'U':
        eyeX=0.0, eyeY=800.0, eyeZ=0;
        upx=0,upz=-1,upy=0;
        break;



    case 27:    // Escape key
        exit(1);
    }

    glutPostRedisplay();
}



void animate()
{

if(crr==true)
    {if(cc1>600) cc1=0;
    if(sh1<=-120 && sh1>=-550) {
    if(cc1>=250 && cc1<=450) cc1+=3;
   else if(cc1>450) cc1+=2;
    if(cc1<200) cc1+=2;
    }
    else cc1+=1;}
if(crr==false) cc1=0;
    if(rr%5==0)
    {
        if(pop==true) {pop=false;}
        else
        {
            pop=true;
        }

    }
    if (bRotate == true)
    {
        theta += 5;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (brr == true)
    {
        if(br1>=55) br1=55;
        else
        {br1 += .5;
        t2+=.2;
        t1-=.1;
        }
    }

    if (brr == false)
    {
        if(br1<=0) br1=0;
        else
        {br1-=.5;
        t2-=.2;
        t1+=.1;
        }
    }

    if(shp==true)
    {
        if(sh1==-200) brr=true;
        if(sh1==-450) brr=false;;
        sh1-=2;
        if(sh1<-900) sh1=0;
    }
    if(shp==false) sh1=0;

    if (bRotate1 == true)
    {
        theta1 += 0.5;
        if(theta1 > 360.0)
            theta1 -= 360.0*floor(theta1/360.0);
    }

    if (uRotate == true)
    {
        alpha += 5;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }

    if (uRotate1 == true)
    {
        alpha1 += 0.5   ;
        if(alpha1 > 360.0)
            alpha1 -= 360.0*floor(alpha1/360.0);
    }
    rotat+=.04;
    rr++;
    glutPostRedisplay();

}

void texture_info()
{
    LoadTexture("F:\\GLUT-Projects\\project-1707052\\1707052\\pics\\grass2.bmp",1);
    LoadTexture("F:\\GLUT-Projects\\project-1707052\\1707052\\pics\\build.bmp",2);
    LoadTexture("F:\\GLUT-Projects\\project-1707052\\1707052\\pics\\road1.bmp",3);
    LoadTexture("F:\\GLUT-Projects\\project-1707052\\1707052\\pics\\brick1.bmp",4);
    LoadTexture("F:\\GLUT-Projects\\project-1707052\\1707052\\pics\\sky.bmp",6);//sky
    LoadTexture("F:\\GLUT-Projects\\project-1707052\\1707052\\pics\\grass.bmp",7);//grass
    LoadTexture("F:\\GLUT-Projects\\project-1707052\\1707052\\pics\\r5.bmp",8);
    LoadTexture("F:\\GLUT-Projects\\project-1707052\\1707052\\pics\\river2.bmp",9);
    LoadTexture("F:\\GLUT-Projects\\project-1707052\\1707052\\pics\\foot1.bmp",10);
    LoadTexture("F:\\GLUT-Projects\\project-1707052\\1707052\\pics\\parking.bmp",11);
    LoadTexture("F:\\GLUT-Projects\\project-1707052\\1707052\\pics\\ship.bmp",12);


}

void printt()
{
    printf("Keyboard options:\n");
    printf(" i    :Zoom in\n");
    printf(" o    :Zoom out\n");
    printf(" a    :Go eye Left\n");
    printf(" d    :Go eye Right\n");
    printf(" w    :Go eye Down\n");
    printf(" s    :Go eye UP\n");
    printf(" F    :Camera movement for Front direction\n");
    printf(" E    :Camera movement for Back direction\n");
    printf(" U    :Camera movement for Up direction\n");
    printf(" L    :Camera movement for Left direction\n");
    printf(" I    :Camera movement for Right direction\n");
    printf(" z    :Bridge rotation up/down\n");
    printf(" m    :Ship movement on\off\n");
    printf(" N    :main Light on/off\n");
    printf(" A    :Light 1 Ambient property on/off\n");
    printf(" D    :Light 1 Diffuse property on/off\n");
    printf(" C    :Light 1 Specular property on/off\n");
    printf(" M    :Spot Light on/off\n");
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("3D bridge");

    glShadeModel( GL_SMOOTH );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    texture_info();
    printt();
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}

