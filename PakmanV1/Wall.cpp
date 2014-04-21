#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include "Wall.h"
#include "Ball.h"
#include "Pacman.h"
#define MAX_L 30
#define MAX_C 30
#define NBALL 2
#define SBALL 1
#define WALL 3
#define BAR 4
#define DECISION 5
#define DBALL 6
#define END 7

int lab[MAX_L][MAX_C] = {

	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 ,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,2,2,2,2,2,2,5,2,2,2,2,2,2,3 ,3,2,2,2,2,2,2,5,2,2,2,2,2,2,3},
	{3,2,3,3,3,3,3,2,3,3,3,3,3,2,3 ,3,2,3,3,3,3,3,2,3,3,3,3,3,2,3},
	{3,1,3,3,3,3,3,2,3,3,3,3,3,2,3 ,3,2,3,3,3,3,3,2,3,3,3,3,3,1,3},
	{3,2,3,3,3,3,3,2,3,3,3,3,3,2,3 ,3,2,3,3,3,3,3,2,3,3,3,3,3,2,3},
	{3,2,3,3,3,3,3,2,3,3,3,3,3,2,3 ,3,2,3,3,3,3,3,2,3,3,3,3,3,2,3},
	{3,5,2,2,2,5,2,5,2,5,2,2,2,5,2 ,2,5,2,2,2,5,2,5,2,5,2,2,2,5,3},
	{3,2,3,3,3,2,3,3,3,2,3,3,3,3,3 ,3,3,3,3,3,2,3,3,3,2,3,3,3,2,3},
	{3,2,3,3,3,2,2,3,3,2,3,3,3,3,3 ,3,3,3,3,3,2,3,3,2,2,3,3,3,2,3},
	{3,2,3,3,3,3,2,3,3,5,2,2,2,3,3 ,3,3,2,2,2,5,3,3,2,3,3,3,3,2,3},
	{3,2,2,2,2,2,5,3,3,2,3,3,2,3,3 ,3,3,2,3,3,2,3,3,5,2,2,2,2,2,3},
	{3,3,3,3,3,3,2,3,3,2,2,2,5,3,3 ,3,3,5,2,2,2,3,3,2,3,3,3,3,3,3},
	{0,0,0,0,0,3,2,3,3,3,3,3,2,3,3 ,3,3,2,3,3,3,3,3,2,3,0,0,0,0,0},
	{0,0,0,0,0,3,2,3,3,0,0,0,6,0,0 ,0,0,6,0,0,0,3,3,2,3,0,0,0,0,0},
	{3,3,3,3,3,3,2,3,3,0,3,3,3,4,4 ,4,4,3,3,3,0,3,3,2,3,3,3,3,3,3},
	{7,0,0,3,0,0,5,2,2,6,3,0,0,0,0 ,0,0,0,0,3,6,2,2,5,0,0,3,0,0,7},
	{7,3,0,0,0,3,2,3,3,0,3,0,0,0,0 ,0,0,0,0,3,0,3,3,2,3,0,0,0,3,7},
	{3,3,3,3,3,3,2,3,3,0,3,3,3,3,3 ,3,3,3,3,3,0,3,3,2,3,3,3,3,3,3},
	{0,0,0,0,0,3,2,3,3,0,3,3,3,3,3 ,3,3,3,3,3,0,3,3,2,3,0,0,0,0,0},
	{0,0,0,0,0,3,2,3,3,6,0,0,0,0,0 ,0,0,0,0,0,6,3,3,2,3,0,0,0,0,0},
	{3,3,3,3,3,3,2,3,3,2,3,3,3,3,3 ,3,3,3,3,3,2,3,3,2,3,3,3,3,3,3},
	{3,2,2,2,2,2,5,2,2,5,2,2,2,2,2 ,2,2,2,2,2,5,2,2,5,2,2,2,2,2,3},
	{3,2,3,3,3,3,3,3,3,2,3,3,3,3,3 ,3,3,3,3,3,2,3,3,3,3,3,3,3,2,3},
	{3,2,3,3,3,3,3,3,3,2,3,3,3,3,3 ,3,3,3,3,3,2,3,3,3,3,3,3,3,2,3},
	{3,2,3,3,3,3,3,3,3,2,3,3,3,3,3 ,3,3,3,3,3,2,3,3,3,3,3,3,3,2,3},
	{3,2,3,3,3,2,2,2,2,5,2,2,2,2,3 ,3,2,2,2,2,5,2,2,2,2,3,3,3,2,3},
	{3,1,3,3,3,2,3,3,3,3,3,3,3,2,3 ,3,2,3,3,3,3,3,3,3,2,3,3,3,1,3},
	{3,2,3,3,3,5,2,2,2,2,2,2,2,5,3 ,3,5,2,2,2,2,2,2,2,5,3,3,3,2,3},
	{3,2,2,2,2,2,3,3,3,3,3,3,3,2,2 ,2,2,3,3,3,3,3,3,3,2,2,2,2,2,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 ,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
};

/////////////////////////////////////
/*Função de preenchimento da matriz*/
/////////////////////////////////////
void pacman::Wall::draw(){

	pacman::Ball *ballNs = new pacman::Ball(0.1f, false);
	pacman::Ball *ballS = new pacman::Ball(0.2f, true);

	int i, j;
	float forward, downward;
	
	for(i=0, downward = yAxis(); i < MAX_L ; i++, downward -= wallSize())
	{
		for(j=0, forward = xAxis(); j < MAX_C ; j++, forward += wallSize()){

			switch(lab[i][j])
			{
			case 1: //bolas especiais
				{
					glColor3f(1.0f, .0f, .0f);
					glPushMatrix();
					initBallsMaterial();
					glTranslatef(forward, downward, 1.25f);
					ballS->draw();
					glPopMatrix();
					break;
				}
			case 2: // bolas normais
				{
					glColor3f(1.0f, 1.0f, 1.0f);
					glPushMatrix();
					initBallsNSMaterial();
					glTranslatef(forward, downward, 1.25f);
					ballNs->draw();
					glPopMatrix();
					break;
				}
			
			case 3: //paredes
				{
					float size = wallSize()/2.0f;
					float walk = wallSize()/4.0f;
					initBlueMaterial();
					glColor3f(.2f, .2f, 1.0f);
					
					//for(int i = 0; i < 2; i++){
						//for(float x = -walk; x < 2;j++){

								glPushMatrix();
								glTranslatef(forward-walk, downward+walk, 1.0f);
								glScalef(1.0f, 1.0f, .5f);
								glutSolidCube(size);
								glPopMatrix();
					
								glPushMatrix();
								glTranslatef(forward+walk, downward+walk, 1.0f);
								glScalef(1.0f, 1.0f, .5f);
								glutSolidCube(size);
								glPopMatrix();

								glPushMatrix();
								glTranslatef(forward-walk, downward-walk, 1.0f);
								glScalef(1.0f, 1.0f, .5f);
								glutSolidCube(size);
								glPopMatrix();

								glPushMatrix();
								glTranslatef(forward+walk, downward-walk, 1.0f);
								glScalef(1.0f, 1.0f, .5f);
								glutSolidCube(size);
								glPopMatrix();
							
							//}
					//}
					break;
				}
			case 4: //barreira
				{
					glColor3f(1.0f, .4f, 1.0f);
					glPushMatrix();
					initGreenMaterial();
					glTranslatef(forward, downward, 1.0f);
					glScalef(1.0f, 0.25f, .5f);
					glutSolidCube(wallSize());
					glPopMatrix();
					break;
				}
			case 5 : //decisoes
				{
					glColor3f(1.0f, 1.0f, 1.0f);
					glPushMatrix();
					initBallsNSMaterial();
					glTranslatef(forward, downward, 1.25f);
					ballNs->draw();
					glPopMatrix();
					break;
				}
			case 6 : //Decisoes sem bolas
				{
					break;
				}
			case 7 : //fim
				{
				break;
				}

			default:;
				
			}
		}
	}

}

void pacman::Wall::eatBall(float x, float y, int axis, int tile){
	int i,j;
	float xAux = x;
	float yAux = y;
	
	if(axis != 0){ //recebe os parametros trocados
		xAux = y;
		yAux = x;
	}

	j = iMatrixX(xAux);
	i = iMatrixY(yAux);

	setMatrix(i,j,tile);
}

void pacman::Wall::setMatrix(int i, int j, int tile){
	lab[i][j] = tile;
}

int pacman::Wall::getNumLab(int l,int c){ return lab[l][c]; }

float pacman::Wall::centerPos(float pos, int axis){
	int i;
	float result = 0;

	if(axis == 0){
		i = iMatrixX(pos);
		result = itopos(i, xAxis());
	} else{
		i = iMatrixY(pos);
		result = itopos(i, yAxis());
	}

	return result;
}

bool pacman::Wall::isEdge(float x, float y, int axis){
	int i,j;
	float xAux = x;
	float yAux = y;
	
	if(axis != 0){ //recebe os parametros trocados
		xAux = y;
		yAux = x;
	}

	j = iMatrixX(xAux);
	i = iMatrixY(yAux);

	return (lab[i][j] == END);
}

void pacman::Wall::removeBar(float x, float y, int axis){
	int i,j;
	float xAux = x;
	float yAux = y;
	
	if(axis != 0){ //recebe os parametros trocados
		xAux = y;
		yAux = x;
	}

	j = iMatrixX(xAux);
	i = iMatrixY(yAux);

	if(lab[i][j] == BAR){
		//remove a barra
		lab[i][13] = 0;
		lab[i][14] = 0;
		lab[i][15] = 0;
		lab[i][16] = 0;
	}

}
/*
int *pacman::Wall::indices(float x, float y, int axis){
	int i,j;
	float xAux = x;
	float yAux = y;
	int *result = ;
	if(axis != 0){ //recebe os parametros trocados
		xAux = y;
		yAux = x;
	}

	j = iMatrixX(xAux);
	i = iMatrixY(yAux);
	result[0] = i;
	result[1] = j;
	return result;
}
*/
bool pacman::Wall::isNormalBall(float x, float y, int axis){
	int i,j;
	float xAux = x;
	float yAux = y;
	
	if(axis != 0){ //recebe os parametros trocados
		xAux = y;
		yAux = x;
	}

	j = iMatrixX(xAux);
	i = iMatrixY(yAux);
	
	return (lab[i][j] == NBALL);
}

bool pacman::Wall::isSpecialBall(float x, float y, int axis){
	int i,j;
	float xAux = x;
	float yAux = y;
	
	if(axis != 0){ //recebe os parametros trocados
		xAux = y;
		yAux = x;
	}

	j = iMatrixX(xAux);
	i = iMatrixY(yAux);
	
	return (lab[i][j] == SBALL);
}

bool pacman::Wall::isDecision(float x, float y, int axis){
	int i,j;
	float xAux = x;
	float yAux = y;
	
	if(axis != 0){ //recebe os parametros trocados
		xAux = y;
		yAux = x;
	}

	j = iMatrixX(xAux);
	i = iMatrixY(yAux);

	return (lab[i][j] == DECISION || lab[i][j] == DBALL);
}

bool pacman::Wall::isDball(float x, float y, int axis){
	int i,j;
	float xAux = x;
	float yAux = y;
	
	if(axis != 0){ //recebe os parametros trocados
		xAux = y;
		yAux = x;
	}

	j = iMatrixX(xAux);
	i = iMatrixY(yAux);

	return (lab[i][j] == DECISION);
}

bool pacman::Wall::isDecided(float x, float y, float angle1, float angle2, int axis){
	int i,j;
	float xAux = x;
	float yAux = y;
	
	if(axis != 0){ //recebe os parametros trocados
		xAux = y;
		yAux = x;
	}

	j = iMatrixX(xAux);
	i = iMatrixY(yAux);

	if(angle1 == angle2){
		return false;
	}

	if(angle1 == UP){
		i--;
	}
	if(angle1 == DOWN){
		i = i++;
	}
	if(angle1 == LEFT){
		j--;
	}
	if(angle1 == RIGHT){
		j++;
	}
	if(angle1 == NULO){
		return false;
	}

	return !(lab[i][j] == WALL || lab[i][j] == BAR);
}

bool pacman::Wall::isDecided(float x, float y, float angle, int axis){
	int i,j;
	float xAux = x;
	float yAux = y;
	
	if(axis != 0){ //recebe os parametros trocados
		xAux = y;
		yAux = x;
	}

	j = iMatrixX(xAux);
	i = iMatrixY(yAux);

	if(angle == UP){
		i--;
	}
	if(angle == DOWN){
		i = i++;
	}
	if(angle == LEFT){
		j--;
	}
	if(angle == RIGHT){
		j++;
	}
	if(angle == NULO){
		return false;
	}

	return !(lab[i][j] == WALL || lab[i][j] == BAR);
}

int pacman::Wall::iMatrixX(float pos){
	int p;
	if (pos <= 0){
		p = (int) ceil(pos);
	}
	else{
		p = (int) floor(pos);
		p++;
	}
	return p + 14;
}

int pacman::Wall::iMatrixY(float pos){
	int p;
	int aux;
	if (pos <= 0){
		aux = (int)ceil(pos);
		p = abs(aux);
		p++;
	}
	else{
		p = (int) floor(pos);
		p = -p;
	}
	return p + 14;
}

bool pacman::Wall::isWall(float x, float y, int axis){
	int i,j;
	float xAux = x;
	float yAux = y;
	
	if(axis != 0){ //recebe os parametros trocados
		xAux = y;
		yAux = x;
	}

	j = iMatrixX(xAux);
	i = iMatrixY(yAux);

	return (lab[i][j] == WALL || lab[i][j] == BAR);
}

bool pacman::Wall::isPhantomWall(float x, float y, int axis){
	int i,j;
	float xAux = x;
	float yAux = y;
	
	if(axis != 0){ //recebe os parametros trocados
		xAux = y;
		yAux = x;
	}

	j = iMatrixX(xAux);
	i = iMatrixY(yAux);

	return (lab[i][j] == WALL);
}

float pacman::Wall::itopos(int pos, float limitAxis){
	int j;
	float limit;
	float inc = wallSize();

	if(limitAxis > 0){
		inc = -inc;
	}

	for(j= 0, limit = limitAxis; j < MAX_C ; j++, limit += inc){
		if (j == pos){
			return limit;
		}
	}

	return -1.0f; //caso em que esta fora do mapa

}

float pacman::Wall::inc(float n, float p){
	float nAbs = abs(n);
	float pAbs = abs(p);
	float result = 0;

	if(nAbs > pAbs){
		result = nAbs - pAbs;
	} else{
		result = pAbs - nAbs;
	}

	return result;
}

/*Função que retorna o incremento para que a posição do pacman seja valida*/
float pacman::Wall::incPosValid(float pos, int axis){
	
	float incValidPos;
	
	if(axis == 0){
		incValidPos = itopos(iMatrixX(pos), xAxis());
	} else{
		incValidPos = itopos(iMatrixY(pos), yAxis());
	}
	
	incValidPos = inc(incValidPos, pos);

	return incValidPos;
}


/* Material para as paredes*/
void pacman::Wall::initBlueMaterial(){
	GLfloat material_b_Ka[] = {0.0f,0.0f,0.0f,0.0f}; 
	GLfloat material_b_Kd[] = {0.01f,0.01f,0.86f,1.0f}; 
	GLfloat material_b_Ks[] = {0.29f,0.89f,0.18f,1.0f};  
	GLfloat shine = 40.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_b_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_b_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_b_Ks);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
}

/*Material para as bolas especiais*/
void pacman::Wall::initBallsMaterial(void){

	GLfloat material_b_Ka[] = {0.18f,0.011f,0.011f,0.0f}; 
	GLfloat material_b_Kd[] = {0.61f,0.041f,0.041f,1.0f}; 
	GLfloat material_b_Ks[] = {0.73f,0.63f,0.63f,1.0f};  
	GLfloat shine = 300.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_b_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_b_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_b_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
}

/*Material para as bolas não especiais.*/
void pacman::Wall::initBallsNSMaterial(void){

	GLfloat material_b_Ka[] = {0.25f,0.25f,0.25f,0.0f}; 
	GLfloat material_b_Kd[] = {0.4f,0.4f,0.4f,1.0f}; 
	GLfloat material_b_Ks[] = {0.78f,0.78f,0.78f,1.0f};  
	GLfloat shine = 300.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_b_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_b_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_b_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
}

/* Material para as paredes*/
void pacman::Wall::initGreenMaterial(){
	GLfloat material_g_Ka[] = {0.135f,0.22f,0.15f,0.0f}; 
	GLfloat material_g_Kd[] = {0.54f,0.89f,0.63f,1.0f}; 
	GLfloat material_g_Ks[] = {0.32f,0.32f,0.32f,1.0f};  
	GLfloat shine = 0.1f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_g_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_g_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_g_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, shine*128);
}
