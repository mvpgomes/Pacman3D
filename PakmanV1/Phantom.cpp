#pragma once
#include <iostream>
#include "Phantom.h"
#include <math.h>
#include <GL\glut.h>

#define PI 3.14159265
#define STEPS 32

/*Angulos de rotação*/
#define UP 0.0f
#define LEFT 90.0f
#define DOWN 180.0f
#define RIGHT 270.0f

/* ----------------- Listas de vértices para a malha poligonal. ---------------------------*/
float px[STEPS],py[STEPS];

// Função que desenha a malha poligonal que representa o corpo
void pacman::Phantom::drawBody()
{
	int i,j;
	float angle;
	// Função que calcula os pontos
	for (i=0; i<STEPS; i++)
	{
		angle=2.0f*PI*float(i)/float(STEPS);
		px[i]=float(cos(angle));
		py[i]=float(sin(angle));
	}
	// Função que desenha o corpo 
	glBegin(GL_QUADS);
	for (i=0; i<STEPS; i++)
	{
		j=i-1;
		if (j<0)
			j=STEPS-1;
		
		glNormal3f(px[i],0.0f,py[i]);
		glVertex3f(px[i],py[i],-1.0f);
		glVertex3f(px[j],py[j],-1.0f);
		glVertex3f(px[j],py[j],1.0f);
		glVertex3f(px[i],py[i],1.0f);
	}
	glEnd();
	
	// Função que desenha o topo
	glBegin(GL_TRIANGLES);
	for (i=0; i<STEPS; i++)
	{
		j=i-1;
		if (j<0)
			j=STEPS-1;
		
		glNormal3f(px[i],0.0f,py[i]);
		glVertex3f(px[i],py[i],1.0f);
		glVertex3f(px[j],py[j],1.0f);
		glVertex3f(0.0f,0.0f,1.7f);
	}
	glEnd();

	// Função que desenha os pés
	glBegin(GL_TRIANGLES);
	for(i=0;i<STEPS;i++)
	{
		j=i-1;
		if(j<0)
			j=STEPS-1;
		
		glNormal3f(px[i],0.0f,py[i]);
		glVertex3f(px[i],py[i],-1.0f);
		glVertex3f(px[j],py[j],-1.0f);
		glVertex3f((px[i]+px[j])/2,(py[i]+py[j])/2,-1.3f);
	}
	glEnd();
	
}

/* -----------------------------------------------------------------------*/

// Função que desenha o olho
void pacman::Phantom::drawEye(void) {
	glPushMatrix();
	glRotatef(getAngle(),0.0f,1.0f,0.0f);
	glColor4f(1.0f,1.0f,1.0f, 1.0f);
	initWhiteMaterial();
	glutSolidSphere(.15f, 16.0f, 16.0f);
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.06f, -0.07f);
	//Iris do olho
	initBlackMaterial();
	glutSolidSphere(.1f, 16.0f, 16.0f);
	glPopMatrix();
	glPopMatrix();
}

/* -----------------------------------------------------------------------*/
/*metodo que verifica se a é maior que b consoante a direccao*/
bool pacman::Phantom::greaterThanCenter(float a, float b, float delta){
	float b1 = b + delta;

	if(dir() == LEFT || dir() == DOWN){ 

		if(a > b1 && a < b){
		return true;
		}
	} else{

		if(a > b && a < b1){
		return true;
		}
	}

	return false;
}

/*Retorna a coordenada oposta XX ou YY*/
float pacman::Phantom::oppositeCoordinate(int axis){
	if(axis == 0){ return getPosition(1);} 
	return getPosition(0);
}

void pacman::Phantom::rotate(float nextAngle){

	if(nextAngle == LEFT){
		angle(LEFT);
	}
	if(nextAngle == DOWN){
		angle(DOWN);
	}
	if(nextAngle == RIGHT){
		angle(RIGHT);
	}
	if(nextAngle == UP){
		angle(UP);
	}
}
/*
* calcProb, this function works in the range 0 to 99
* return true if the random is less than percentage
* false others cases.
*/
bool calcProb(int percentage){
	int guess = rand() % 100;

	if(guess < percentage){
		return true;
	}
	return false;
}

void pacman::Phantom::drawOrigen(){

	setPos(0, origen(0));
	setPos(1, origen(1));
	setPos(2, origen(2));

}

float pacman::Phantom::updatePhantomPos(float x, float y){
	int t = glutGet(GLUT_ELAPSED_TIME);	
	int elapsedTime = t - getTime();
	float v = getVelocity();
	float delta = elapsedTime * v;

	updatePos(x, y);
	time(t);
	
	return delta;
}
/* --------------------------------------------------------------------- */
void pacman::Phantom::updatePos(float x, float y){
	updateEyesPos(x,y);
	_xPac = x;	// atualiza coordenadas do pacman
	_yPac = y;
}

/* --------------------------------------------------------------------- */
void pacman::Phantom::selectionMove(pacman::Drawable *obj, float delta){
	
	if(dir() == LEFT){
		move(-delta, 0, obj);
	}

	if(dir() == RIGHT){
		move(delta,0, obj);
	}
	
	if(dir() == UP){
		move(delta,1, obj);
	}
	
	if(dir() == DOWN){
		move(-delta,1, obj);
	}
}
/* --------------------------------------------------------------------- */
void pacman::Phantom::update(pacman::Drawable *obj){
	pacman::Pacman *pac = (pacman::Pacman *) obj->obj(2); 

	float delta;
	delta = updatePhantomPos(pac->getPosition(0), pac->getPosition(1));

	if( !drawed() ){
		drawOrigen();
		edibol(0);
		velocity(0.005f);
		dir(UP);
	} else{
		selectionMove(obj, delta);
	}
}

float pacman::Phantom::generateToken(){
	float dist1, dist2;

	if(dir() == LEFT || dir() == RIGHT){
		dist1 = calcDist(_xPac, _yPac, getPosition(0), getPosition(1)+1); //distancia para cima
		dist2 = calcDist(_xPac, _yPac, getPosition(0), getPosition(1)-1); //distancia pra baixo

		if(dist1 < dist2 && !_edibol){
			return UP;
		}
		return DOWN;
		
	} 
		dist1 = calcDist(_xPac, _yPac, getPosition(0)+1, getPosition(1)); //distancia pra direita
		dist2 = calcDist(_xPac, _yPac, getPosition(0)-1, getPosition(1)); //distancia pra esquerda
		
		if(dist1 < dist2 && !_edibol){
			return RIGHT;
		}
		return LEFT;
}

void pacman::Phantom::simulationCmd(int stopped){
		throwProb();

		if(stopped){
			if(!changeDir()){
				dir(invCommand(generateToken()));
			} else{
				dir(generateToken());
			}
		}else{

			if(changeDir()){
				dir(generateToken());
			}
		}

}

bool pacman::Phantom::interpenetra(){
	return (calcDist(getPosition(0), getPosition(1), _xPac, _yPac) < 2 * radius()); 
}

void pacman::Phantom::move(float delta, int axis, pacman::Drawable *obj){ 
	pacman::Pacman *pac = (pacman::Pacman *) obj->obj(2);
	pacman::Wall *wall = (pacman::Wall *) obj->obj(1);
	float nextCenter, next, validPos, centerPos;
	int sym = 1;

	if (delta < 0){
		sym = -sym;
	}

	next = getPosition(axis) + delta + sym * radius();
	nextCenter = getPosition(axis) + delta; //posicao a contar do centro

	if( interpenetra() && pac->drawed() ){
		if(edibol()) {
			waitting(id()); 
			return;
		} 
		pac->die();
	}

	if(wall->isDecision(nextCenter, oppositeCoordinate(axis), axis)){
		centerPos = wall->centerPos(nextCenter, axis); //calcula o centro do quadrado
		
		if(greaterThanCenter(nextCenter, centerPos, delta)){

			validPos = delta - sym*wall->inc(centerPos, nextCenter);
			
			simulationCmd(0);

			if(changeDir()){
			setPosition(axis, validPos);
			return;
			}

		}
	}
		
	//Paredes
	if (wall->isPhantomWall(next, oppositeCoordinate(axis), axis)){
		validPos = wall->incPosValid(getPosition(axis), axis); //calcula inc
		setPosition(axis,sym*validPos);
		simulationCmd(1);
		return;
	}

	//Fim de mapa
	if(wall->isEdge(nextCenter, oppositeCoordinate(axis), axis)){
		setPos(0, -getPosition(0));
		return;
	}

	wall->removeBar(nextCenter, oppositeCoordinate(axis), axis);

	rotate(dir());
	setPosition(axis,delta);
}

void pacman::Phantom::throwProb(){

	if(_edibol){

		if(calcProb(25)){
			_changeDir = true;
		} else{
			_changeDir = false;
		}

	} else{
	
		if(calcProb(75)){
			_changeDir = true;
		} else{
			_changeDir = false;
		}
	
	}
}

float pacman::Phantom::invCommand(float cmd){

	if(cmd == RIGHT){
		return LEFT;
	}
	if(cmd == LEFT){
		return RIGHT;
	}
	if(cmd == UP){
		return DOWN;
	}
	return UP;
}

/* -----------------------------------------------------------------------*/

// Função que desenha a sombrancelha
void pacman::Phantom::drawBrush(void){
    glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	initBlackMaterial();
	glutSolidSphere(0.07f, 16.0f, 16.0f);
}

/* ------------------------------------------------------------------------*/
/* Função que desenha o corpo do fantasma. */
void pacman::Phantom::draw(void){
	glPushMatrix();
	glTranslatef(getPosition(0),getPosition(1), getPosition(2));
	glRotatef(angle(),0.0f,0.0f,1.0f);
	glScalef(.5f,.5f,1.0f);
	// desenha o olho esquerdo
	glPushMatrix();
	glTranslatef(-0.4f, .9f, .3f);
	drawEye();
	glPopMatrix();
	// desenha o olho direito
	glPushMatrix();
	glTranslatef(0.4f, .9f, .3f);
	drawEye();
	glPopMatrix();
	// desenha a sombrancelha esquerda
	glPushMatrix();
	glTranslatef(0.4f,.9f,.55f);
	glRotatef(20.0f,0.0f,.0f,1.0f);
	glScalef(1.8f,0.7f,1.0f);
	drawBrush();
	glPopMatrix();
	// desenha sobrancelha esquerda
	glPushMatrix();
	glTranslatef(-0.4f, .9f,.55f);
	glRotatef(-20.0f,0.0f,0.0f,1.0f);
	glScalef(1.8f,.7f,1.0f);
	drawBrush();
	glPopMatrix();
	glPushMatrix();
	glScalef(1.0f,1.0f,0.5f);
	if(getEdibol() == 0){
		initColorMaterial();
	}else{
		initWhiteMaterial();
	}
	drawBody();
	glPopMatrix();
	glPopMatrix();
	
}


/* --------------------------------------------------------------------------*/

/* Função que actualiza o angulo dos olhos dos fantasmas.*/
void pacman::Phantom::updateEyesPos(float x, float y){
	float i =  ( x - getPosition(0));
	float j =  (getPosition(1) - y);
	float angle = calcAngle(i,j);
	eyesAngle(angle);
}
/* -------------------------------------------------------------------- */
// Função que calcula o angulo para movimentar o olho do fantasma.
float pacman::Phantom::calcAngle(float x, float y){
		float angle = atan(x/y) * 180 / PI;
		if(y<0){
			return angle + 180.0f;
		}
		else
			return angle;
}
/* --------------------------------------------------------------------- */
// Função que calcula a distancia
float pacman::Phantom::calcDist(float x1, float y1, float x2, float y2){
	return sqrt(pow((x2-x1),2) + pow((y2 - y1),2));
}

/* ------------------ Materiais dos fantasmas. ----------------------------------*/

// Material Branco
void pacman::Phantom::initWhiteMaterial(){
	
	GLfloat material_w_Ka[] = {0.53f,0.50f,0.50f,1.0f}; 
	GLfloat material_w_Kd[] = {1.0f,1.0f,1.0f,1.0f}; 
	GLfloat material_w_Ks[] = {0.85,0.85,0.85,1.0f};  
	GLfloat shine = 0.25f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_w_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_w_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_w_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, shine*128);


}

//Material Colorido
void pacman::Phantom::initColorMaterial(){
	GLfloat material_c_Ka[] = {getColor(0)*0.65,getColor(1)*0.10,getColor(2)*0.12,1.0f};
	GLfloat material_c_Kd[] = {getColor(0),getColor(1),getColor(2),1.0f};
	GLfloat material_c_Ks[] = {getColor(0)*0.85,getColor(1)*0.12, getColor(2)*0.15,1.0f};
	GLfloat shine = 10.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_c_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_c_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_c_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
}


// Material Preto
void pacman::Phantom::initBlackMaterial(){
	GLfloat material_b_Ka[] = {0.0f,0.0f,0.0f,0.0f}; 
	GLfloat material_b_Kd[] = {0.01f,0.01f,0.01f,1.0f}; 
	GLfloat material_b_Ks[] = {0.0f,0.0f,0.0f,1.0f};  
	GLfloat shine = 0.25f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_b_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_b_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_b_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, shine*128);
}

/* -------------------------------------------------------------------- */