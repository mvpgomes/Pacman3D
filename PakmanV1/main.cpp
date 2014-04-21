#include <vector>
#include <iostream>
#include <cstdlib>
#include <GL/glut.h>
#include "Land.h"
#include "Wall.h"
#include "Pacman.h"
#include "Ball.h"
#include "Phantom.h"
#include "Particles.h"
#include "BMPloader.h"
#define ESC 27
#define FPS 33
class Drawable;

/////////////////////////////////////
/*Zona de definição de constantes */
///////////////////////////////////
int w, h;
int cameraNumber = 1;
int lightNumber = 4;
bool _fullScreen = false;
bool _ambient = true;
bool _pause = false;
char life [] = "Lives: ";
char score [] = "Score: ";
char gameover[] = "Game Over!!!    Click 'r' to restart";
char pointsBuffer[5];
char lifeBuff[1];
GLuint texname;
////////////////////////////////////////////////////
///// Coeficiente das componentes das luzes ////////
////////////////////////////////////////////////////
GLfloat light_Ka[] = {0.5f, 0.5f, 0.5f, 0.0f};
GLfloat light_Kd[] = {1.0f, 1.0f, 1.0f, 1.0f};	
GLfloat light_Ks[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat zeroAmb[] = {  0.,  0.,  0.,  1.};
////////////////////
/*Classe Global*/
//////////////////
pacman::Drawable game;
////////////////////////
/*Funções de CALLBACK*/
///////////////////////
void initDataGame();

void updateCamera(){
	pacman::Pacman *pac = (pacman::Pacman *) game.obj(2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	switch( cameraNumber )
	{
	default:
	case 1:{
		gluPerspective(45.0, ((float)w)/h, 1, 50);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(pac->getPosition(0), pac->getPosition(1) - 20.0f, pac->getPosition(2) + 25.0f, 
				  pac->getPosition(0), pac->getPosition(1), pac->getPosition(2), 0, 0, 1);
		break;
		   }
	case 2:{
		double f = ((float) w) / h;
		if ( f >= 1. ){
			glOrtho(-20.0f * f , 20.0f * f, -20.0f , 20.0f , -20.0f, 20.0f);
		}
		else{
			glOrtho(-20.0f , 20.0f , -20.0f / f, 20.0f / f, -20.0f, 20.0f);
		}
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		break;
		   }
	case 3:{ //ZOOM
		gluPerspective(20.0, ((float)w)/h, 1, 50);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(pac->getPosition(0), pac->getPosition(1)-20, pac->getPosition(2)+20, 
				  pac->getPosition(0), pac->getPosition(1), pac->getPosition(2), 0, 0, 1);
		}
	}
	
}

void drawHUD()
{
	pacman::Pacman *pac = (pacman::Pacman *) game.obj(2);

	glDisable(GL_LIGHTING);
	// hud display no canto superior direito
	glMatrixMode( GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLfloat) w , 0.0, (GLfloat) h );
	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();
	glColor3f( 0., 1., 0.);
	if(!pac->life()){
		glRasterPos2i(200,h-300);
		for( int i=0; gameover[i] != '\0'; i++){
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, gameover[i]);
		}
	} else{

		glRasterPos2i(10,h-30);
		for( int i=0; life[i] != '\0'; i++){
			glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, life[i]);
		}
		glRasterPos2i(65,h-30);
		_itoa(pac->life(), lifeBuff, 10);
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, lifeBuff[0]);
		glRasterPos2i(100,h-30);
		for( int i=0; life[i] != '\0'; i++)
			glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, score[i]);
		glRasterPos2i(165,h-30);
		_itoa(pac->getScore(), pointsBuffer,10);
		for( int i=0; pointsBuffer[i] != '\0'; i++)
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, pointsBuffer[i]);
	}
	glEnable(GL_LIGHTING);
	
}

/* Carregamento da textura. */
void LoadTexture(const std::string fileName){
	pacman::Land *l = (pacman::Land *) game.obj(0);
	pacman::BMPloader * bitmap = new pacman::BMPloader(fileName); 
	if ( bitmap->Isvalid() )
	{
		glGenTextures(1, &texname);
		glBindTexture(GL_TEXTURE_2D, texname);	
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap->Width(), bitmap->Heigth(), 0, GL_RGB,
					 GL_UNSIGNED_BYTE, bitmap->Image());
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	l->texture(true);
	delete bitmap;
} 

void updateDirectionalLight(){
	GLfloat light_pos[] = { 1.0f, -1.0f, .50f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);
}

void updateSpotLight() {
	pacman::Pacman *pac = (pacman::Pacman *) game.obj(2);

	GLfloat spot_direction[] = { pac->dir(0),  pac->dir(1), -.5f}; 
	GLfloat spotlight_pos[] = { pac->getPosition(0), pac->getPosition(1) - 0.2f,pac->getPosition(2) + pac->getRadius(),1.0f};
	

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_Ka);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_Kd);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_Ks);
	

	glLightfv(GL_LIGHT1, GL_POSITION, spotlight_pos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0f);
	
}

void upDate(){
	updateCamera(); //updates the camera
	updateDirectionalLight();
	updateSpotLight();
}

void updateScene()
{
	pacman::Pacman *pac = (pacman::Pacman *) game.obj(2);
	if(pac->life() ){
		game.update(game.obj(2));	//pacman
		game.update(game.obj(3));	//phantom 1
		game.update(game.obj(4));   //phantom 2
		game.update(game.obj(5));   //phantom 3
	}
	game.update(game.obj(6));   //particles
	upDate();
}

void myDisplay(void) 
{
	updateScene();
	glClearColor(.0f , .0f, .05f, 0.f); //limpa
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	
	game.draw(); //desenha
	drawHUD();
	glFlush();
}

void myReshape(GLsizei width, GLsizei height)
{   
	w = width;   h = height; 
	glViewport( 0, 0, w, h);

}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(FPS,Timer, 0);
}

void keyPressed(int key, int x, int y){
	pacman::Pacman *pac = (pacman::Pacman *) game.obj(2);

	if(key == GLUT_KEY_LEFT){
		pac->setState(LEFT);
	}

	if(key == GLUT_KEY_RIGHT){
		pac->setState(RIGHT);
	}
	
	if(key == GLUT_KEY_UP){
		pac->setState(UP);
	}
	
	if(key == GLUT_KEY_DOWN){
		pac->setState(DOWN);
	}

}

void extraKeys(unsigned char key, int x, int y){
	pacman::Phantom *p1 = (pacman::Phantom *) game.obj(3);
	pacman::Phantom *p2 = (pacman::Phantom *) game.obj(4);
	pacman::Phantom *p3 = (pacman::Phantom *) game.obj(5);
	pacman::Land *land = (pacman::Land *) game.obj(0);
	pacman::Pacman *pac = (pacman::Pacman *) game.obj(2);

	switch ( key ) {
		case ESC:
			exit(0);
			break;
		case 'q':
			exit(0);
			break;
		case '1':
		case '2':
			{
			int camera = key - '0';
			if ( camera != cameraNumber ){
				cameraNumber = camera;
				glutPostRedisplay();
				}
			}
			break;
		case '3':
			{
			int camera = key - '0';
			if ( camera != cameraNumber ){
				cameraNumber = camera;
				glutPostRedisplay();
				}
			}
			break;
		case '4':
			{
			glDisable(GL_LIGHT1);
			glEnable(GL_LIGHT0);
            int light = key -'0';
			if(light != lightNumber){
				lightNumber = light;
				glutPostRedisplay();
				}
			}
			break;
		case '5':
			{
			glDisable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
            int light = key -'0';
			if(light != lightNumber){
				lightNumber = light;
				glutPostRedisplay();
				}
			}
			break;
		case 'f':
			_fullScreen = ! _fullScreen;
			
			if ( _fullScreen ){
				glutFullScreen();
			} else{
				glutReshapeWindow(700, 700);
				glutPositionWindow(30,30);
			}
			glutPostRedisplay();
			break;
		case 32:
			{
			_ambient = ! _ambient;
			if ( _ambient ){
				glLightModelfv( GL_LIGHT_MODEL_AMBIENT, light_Ka);
			} else{
				glLightModelfv( GL_LIGHT_MODEL_AMBIENT, zeroAmb);
			}
			glutPostRedisplay();
			}
			break;
		case 'p':
			{
				_pause = !_pause;
				break;
			}
		case 'w':
				//p1.dir(UP);
				break;
		case 'a':
				//p1.dir(LEFT);
				break;
		case 'd':
				//p1.dir(RIGHT);
				break;
		case 'i':
				p1->dir(UP);
				p2->dir(UP);
				p3->dir(UP);
				break;
		case 'r':
			if(!pac->life()){
				game.deleteObj();
				initDataGame();
			}
			break;
		case 't':
				LoadTexture("tile.bmp");
				break;
		case 'b':
				LoadTexture("bandeira.bmp");
				break;
		case 'o':
				LoadTexture("azul.bmp");
				break;
		case 'n':
				land->texture(false);
				break;
		default:
			break;
	}	
}

void initEnables() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH); //Enable smooth shading
}

void pacman::Phantom::explosionPac(){
	std::cout << "explosion BIGBANG\n";
}

void tick_wait(int id){
	game.phantomRun(id);
}

void pacman::Phantom::waitting(int id){
	game.phantomWait(id);
	glutTimerFunc(5000, tick_wait, id);
}

void tick(int value){
	game.phantomColor();
}

void pacman::Pacman::alertPhantom(){
	game.phantomWhite();
	glutTimerFunc(10000, tick, 0);
}

void vive(int value){
	pacman::Particles *p = (pacman::Particles *) game.obj(6);
	pacman::Pacman *pac = (pacman::Pacman *) game.obj(2);
	if(pac->life()){
		pac->revive();
		p->drawed(false);
	}
}

void pacman::Pacman::die(){
	pacman::Particles *p = (pacman::Particles *) game.obj(6);
	drawed(false);
	decLife();
	////faz as particulas.
	p->drawed(true);
	p->createParticles(getPosition(0), getPosition(1), getPosition(2), 0.1*getRadius());
	glutTimerFunc(4000, vive, 0);
}

void initDataGame(){

/* [0] */	 pacman::Drawable *land = new pacman::Land();			
/* [1] */	 pacman::Drawable *wall = new pacman::Wall();
/* [2] */	 pacman::Drawable *pac = new pacman::Pacman(0.005f);
/* [3] */    pacman::Drawable *p1 = new pacman::Phantom(3, -1.2f,-1.5f, 1.5f, 0.005f, 1.0f, 0.0f, 0.0f);
/* [4] */    pacman::Drawable *p2 = new pacman::Phantom(4,.0f,-1.5f, 1.5f, 0.005f, 1.0f, 0.0f, 1.0f);
/* [5] */	 pacman::Drawable *p3 = new pacman::Phantom(5,1.2f,-1.5f, 1.5f, 0.005f, 0.0f, 1.0f, 1.0f);
/* [6] */	 pacman::Drawable *particles = new pacman::Particles(0.0f, 0.0f, 0.0f, .0f);

//INITIALIZING DATA CENTER	
	game.add(land);
	game.add(wall);
	game.add(pac);
	game.add(p1);
	game.add(p2);
	game.add(p3);
	game.add(particles);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (700, 700);
    glutInitWindowPosition (-1, -1); 
    glutCreateWindow("Pacman3D");
	initEnables();
	initDataGame();
	glutDisplayFunc( myDisplay);
	glutReshapeFunc( myReshape);
	glutKeyboardFunc( extraKeys);
	glutSpecialFunc( keyPressed);
	glutTimerFunc(FPS, Timer, 0);
    glutMainLoop();
}
