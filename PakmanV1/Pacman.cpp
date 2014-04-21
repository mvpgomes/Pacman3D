#include <stdlib.h>
#include <iostream>
#include <GL\glut.h>
#include "Pacman.h"


/*metodo que verifica se a é maior que b consoante a direccao*/
bool pacman::Pacman::greaterThanCenter(float a, float b, float delta){
	float b1 = b-delta;

	if(currentCommand() == LEFT || currentCommand() == DOWN){ 
		if(a > b && a < b1){
		return true;
		}
	} else{
		if(a > b1 && a < b){
		return true;
		}
	}

	return false;
}

/*Retorna a coordenada oposta XX ou YY*/
float pacman::Pacman::oppositeCoordinate(int axis){
	if(axis == 0){ return getPosition(1);} 
	return getPosition(0);
}

/*Função de rotação do pacman*/
void pacman::Pacman::rotate(float nextAngle){

	if(nextAngle == LEFT){
		dir(0, -1.0f);
		dir(1, 0.0f);
		angle(LEFT);
	}
	if(nextAngle == DOWN){
		dir(0, .0f);
		dir(1, -1.0f);
		angle(DOWN);
	}
	if(nextAngle == RIGHT){
		dir(0, 1.0f);
		dir(1, 0.0f);
		angle(RIGHT);
	}
	if(nextAngle == UP){
		dir(0, .0f);
		dir(1, 1.0f);
		angle(UP);
	}
}

float pacman::Pacman::updatePacmanPos()
{
	int t = glutGet(GLUT_ELAPSED_TIME);	
	int elapsedTime = t - getTime();
	float v = getVelocity();
	float delta = elapsedTime * v;
	time(t);

	return delta;
}
void pacman::Pacman::drawOrigen(){
	setPos(0, origen(0));
	setPos(1, origen(1));
	setPos(2, origen(2));
}

void pacman::Pacman::revive(){
	drawed(true);
	drawOrigen();
	angle(UP);
	dir(NULO);
}

void pacman::Pacman::update(pacman::Drawable *obj){ 
	pacman::Wall *wall = (pacman::Wall *) obj->obj(1);

	float delta = updatePacmanPos();

	if (!drawed()) 	return;

	if(currentCommand() == LEFT){

		if(nextCommand() == RIGHT){
			changeState();
			return;
		}
		
		
		move(-delta, 0, wall); //-x direction
	}

	if(currentCommand() == RIGHT){

		if(nextCommand() == LEFT){
			changeState();
			return;
		}

		move(delta,0, wall); //x direction
	}
	
	if(currentCommand() == UP){

		if(nextCommand() == DOWN){
			changeState();
			return;
		}


		move(delta,1, wall); //y direction
	}
	
	if(currentCommand() == DOWN){

		if(nextCommand() == UP){
			changeState();
			return;
		}

		move(-delta,1, wall); //-y direction
	}
}


void pacman::Pacman::setState(float state){
	
	if(currentCommand() == NULO){
		buffer(0, state);
	}else{
		buffer(1, state);
	}
}
///////////////////////////////////////////////////
/*Funcao de locomocao do pacman
* interage com a classe Wall */
void pacman::Pacman::move(float delta, int axis, pacman::Wall *wall){ 
	float next, nextCenter, centerPos;
	int dir = 1;
	float validPos;

	if (delta < 0){
		dir = -dir;
	}

	next = getPosition(axis) + delta + dir * getRadius();
	nextCenter = getPosition(axis) + delta; //posicao a contar do centro

	if(getDecision()){
		centerPos = wall->centerPos(nextCenter, axis);
		validPos = delta - dir*wall->inc(centerPos, nextCenter);
		setPosition(axis, validPos);
		changeState();
		inDecision(false);
		return;
	}

	//quadrado de decisao
	if(wall->isDecision(nextCenter, oppositeCoordinate(axis), axis)){
		
		if(wall->isDball(nextCenter, oppositeCoordinate(axis), axis)){
			wall->eatBall(nextCenter, oppositeCoordinate(axis), axis, 6);
			incScore(5);
		}

		centerPos = wall->centerPos(nextCenter, axis); //calcula o centro do quadrado
		
		if(greaterThanCenter(nextCenter, centerPos, delta)){ //decide se vai ou nao mudar de direcao
		
			if(wall->isDecided(centerPos, oppositeCoordinate(axis), nextCommand(), currentCommand(), axis)){
				inDecision(true);
			}

		}
	}

	//Paredes
	if (wall->isWall(next, oppositeCoordinate(axis), axis)){
		validPos = wall->incPosValid(getPosition(axis), axis); //calcula inc
		setPosition(axis,dir*validPos);
		changeState();
		return;
	}

	//Fim de mapa
	if(wall->isEdge(nextCenter, oppositeCoordinate(axis), axis)){
		setPos(0, -getPosition(0));
		return;
	}
	
	//Bolas normais
	if(wall->isNormalBall(nextCenter, oppositeCoordinate(axis), axis)){
		wall->eatBall(nextCenter, oppositeCoordinate(axis), axis, 0);
		incScore(5);
	}

	//Bolas especiais
	if(wall->isSpecialBall(nextCenter, oppositeCoordinate(axis), axis)){
		wall->eatBall(nextCenter, oppositeCoordinate(axis), axis, 0);
		incScore(10);
		alertPhantom();
	}

	rotate(currentCommand());
	setPosition(axis,delta);
	
}

//////////////////////////////////////////////////////

// Função que desenha a cabeça
void pacman::Pacman::drawHead(void){
	initYellowMaterial();
	glColor3f(1.0f, 1.0f, .0f);
	glutSolidSphere(0.5f, 16, 16);
}

void pacman::Pacman::drawEye(float x){
	//iris do olho
	initBlackMaterial();
	glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(x,0.46f,0.295f);
	glScalef(1.0f, 1.1f, 1.0f);
	glutSolidSphere(0.0625f, 16, 16);
	glPopMatrix();
	//Exterior do olho
	initWhiteMaterial();
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(x,0.375f,0.275f);
	glutSolidSphere(0.125f, 16, 16);
	glPopMatrix();

}

// Função que desenha o olho
void pacman::Pacman::drawEyes(void){
	float x = 0.2f;
    drawEye(x);
	drawEye(-x);
}

void pacman::Pacman::drawBrush(float x){
	initBlackMaterial();
	glColor3f(0.0f,0.0f,0.0f);
	glPushMatrix();
	glTranslatef(x, 0.355f, 0.6f);
	glScalef(1.0f, 0.5f, 0.5f);
	glutSolidSphere(0.125f,16,16);
	glPopMatrix();
}
// Função que desenha a sombracelha
void pacman::Pacman::drawBrushes(void){
	float x = 0.2f;
	drawBrush(x);
	drawBrush(-x);
}

// Função que desenha o Pacman
void pacman::Pacman::draw(void)
{   
	//operacoes aplicadas ao grupo de objs
	glPushMatrix();
	glTranslatef(_position[0],_position[1],_position[2]);
	glRotatef(getAngle(),0.0f,0.0f,1.0f);
	drawEyes();
	drawHead();
	drawBrushes();
	glPopMatrix();
}

void pacman::Pacman::initYellowMaterial(){
	GLfloat material_b_Ka[] = {0.21f,0.23f,0.07f,1.0f}; 
	GLfloat material_b_Kd[] = {0.87f,0.84f,0.0f,1.0f}; 
	GLfloat material_b_Ks[] = {0.39f,0.22f,0.0f,1.0f};  
	GLfloat shine = 61;

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_b_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_b_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_b_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
}

void pacman::Pacman::initBlackMaterial(){
	GLfloat material_b_Ka[] = {0.0f,0.0f,0.0f,0.0f}; 
	GLfloat material_b_Kd[] = {0.01f,0.01f,0.01f,1.0f}; 
	GLfloat material_b_Ks[] = {0.0f,0.0f,0.0f,1.0f};  
	GLfloat shine = 0.25f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_b_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_b_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_b_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
}

void pacman::Pacman::initWhiteMaterial(){

	GLfloat material_w_Ka[] = {0.0f,0.0f,0.0f,1.0f}; 
	GLfloat material_w_Kd[] = {1.0f,1.0f,1.0f,1.0f}; 
	GLfloat material_w_Ks[] = {0.0,0.0,0.0,1.0f};  
	GLfloat shine = 5.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_w_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_w_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_w_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);


}
