#include "Land.h"

void pacman::Land::initWhiteMaterial(){
	GLfloat material_w_Ka[] = {0.53f,0.50f,0.50f,1.0f}; 
	GLfloat material_w_Kd[] = {1.0f,1.0f,1.0f,1.0f}; 
	GLfloat material_w_Ks[] = {0.85,0.85,0.85,1.0f};  
	GLfloat shine = 0.25f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_w_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_w_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_w_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, shine); 
}


void pacman::Land::drawTexture(){
	_h = _cubeSize * _scaleZ;
	initWhiteMaterial();

	glColor3f(0.1f, 0.1f, 0.1f);
	glPushMatrix();
	glTranslatef(-0.05f, 0.f, .75f);


	float xyinc = 10. / subs();
	float s1, s2, t1, t2;
	t2 = 0;
	glNormal3f( 0., 0., 1.);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	for(float x=-15.0f; x < 15.0f; x+=xyinc){
		t1 = t2;
		t2 = 8. * (x+16) / subs();
		s2 = 0;
		for( float y=-15.0f; y < 15.0f; y+=xyinc)
		{	
			s1 = s2;
			s2 = 8. * (y+16) / subs();

			glTexCoord2f(t1,s1);
			glVertex3f(x,y,0.0f);

			glTexCoord2f(t2,s1);
			glVertex3f(x,y+xyinc,0.0f);
	
			glTexCoord2f(t2,s2);
			glVertex3f(x+xyinc,y+xyinc, 0.0f);
		
			glTexCoord2f(t1,s2);
			glVertex3f(x+xyinc,y,0.0f);
		 } 

	}


	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}



void pacman::Land::drawLand(){
	_h = _cubeSize * _scaleZ;

	GLfloat material_b_Ka[] = {.05f,.05f,.05f,1.f}; 
	GLfloat material_b_Kd[] = {.01f,.01f,.01f,1.f}; 
	GLfloat material_b_Ks[] = {.01f,.01f,.01f,1.f};  
	GLfloat shine = 10.f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_b_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_b_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_b_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);

	glColor3f(0.1f, 0.1f, 0.1f);

	glPushMatrix();
	glTranslatef(0.f, 0.f, .75f);

	glNormal3f( 0., 0., 1.);
	float xyinc = 10. / subs();
	glBegin( GL_QUADS);
	for( float x=-15.; x < 15.; x+=xyinc)
		for( float y=-15.; y < 15.; y+=xyinc)
		{
			glVertex3f( x,        y,       0.);
			glVertex3f( x,        y+xyinc, 0.);
			glVertex3f( x+xyinc,  y+xyinc, 0.);
			glVertex3f( x+xyinc,  y,       0.);
		}

	glEnd();

	glPopMatrix();
			
}