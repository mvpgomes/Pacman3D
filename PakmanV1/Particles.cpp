#include "Particles.h"
#include <cmath>
#include <iostream>
#include <GL/glut.h>

#define frand()			((float)rand()/RAND_MAX)
#define M_PI 3.14159265



void pacman::Particles::createParticles(float x, float y, float z, float radius)
{
 GLfloat v, theta, phi;

 for(int i=0; i<NUM_PARTICLES; i++)
    {
	v = 1.5f *frand()+0.2;
    phi = frand()*M_PI;
    theta = frand()*M_PI;
    particula[i].x = x;
	particula[i].y = y;
    particula[i].z = z;
	particula[i].radius = radius;
    particula[i].vx = v * cos(theta) * sin(phi);
    particula[i].vy = v * cos(phi);
    particula[i].vz = v * sin(theta) * sin(phi);
    particula[i].az = -0.5f;       
	}
}

void pacman::Particles::update(pacman::Drawable *obj){
	int t = glutGet(GLUT_ELAPSED_TIME);	
	float dt = (float)(t - time())/600;
	time(t);
	if( drawed() ){ updateParticles(dt); }
}


void pacman::Particles::draw(){
	
	float alturaChao = 0.75f;

 for (int i=0; i<NUM_PARTICLES; i++)
	{
		if(particula[i].z > alturaChao)
		{	
			initYellowMaterial();
			glPushMatrix();
			glTranslatef(particula[i].x, particula[i].y, particula[i].z);
			glutSolidSphere(particula[i].radius, 16, 16);
			glPopMatrix();
		}
	}
}



void pacman::Particles::updateParticles(float dt)
{
	int i;

	for (i=0; i<NUM_PARTICLES; i++)
	{
		particula[i].x += (dt*particula[i].vx);
		particula[i].y += (dt*particula[i].vy);
		particula[i].z += (dt*particula[i].vz);
		particula[i].vz += (dt*particula[i].az);
	}
}

void pacman::Particles::initYellowMaterial(){
	GLfloat material_b_Ka[] = {0.21f,0.23f,0.07f,1.0f}; 
	GLfloat material_b_Kd[] = {0.87f,0.84f,0.0f,1.0f}; 
	GLfloat material_b_Ks[] = {0.39f,0.22f,0.0f,1.0f};  
	GLfloat shine = 61;

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_b_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_b_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_b_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
}