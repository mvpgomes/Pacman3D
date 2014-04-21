#pragma once
#include "Pacman.h"
#include "Wall.h"
#include "Drawable.h"

/*Angulos de rotação*/
#define UP 0.0f
#define LEFT 90.0f
#define DOWN 180.0f
#define RIGHT 270.0f
#define NULO -1.0f

namespace pacman{
	class Phantom : public pacman::Drawable{
		private:
			int _id;
			float _angle;
			float _radius;
			float _eyesAngle;
			float _color[3];
			float _position[3];
			float _origen[3];
			float _dir;		/* only buffer */
			int _edibol;
			int _time;
			float _velocity;
			bool _inDecision;
			bool _changeDir;
			float _xPac;
			float _yPac;
			bool _drawed;
	public:
		Phantom(int id, float x, float y, float z, float velocity ,float R, float G,float B) : _id(id), _angle(0.0f), _radius(0.5f),
			_eyesAngle(0.0f), _dir(NULO) ,_edibol(0), _time(0), _velocity(velocity), _inDecision(false), _changeDir(false), 
			_xPac(NULO), _yPac(NULO), _drawed(true) {
			_color[0] = R;
			_color[1] = G;
			_color[2] = B;
			_position[0] = x; _origen[0] = x;
			_position[1] = y; _origen[1] = y;
			_position[2] = z; _origen[2] = z;			
		}

		Phantom(void){}

		~Phantom(void) {}

		//Setters
		void angle(float angle) { _angle = angle; }
		void radius(float radius) { _radius = radius; }
		void changeDir(bool state) { _changeDir = state; }
		void setPos(int axis, float val) { _position[axis] = val;  }
		void setPosition(int axis, float inc) {	_position[axis] += inc;}
		void eyesAngle(float angle) {_eyesAngle = angle;}
		void incEdibol() { _edibol++; _velocity = 0.003f; }
		void decEdibol() { if(_edibol != 0) _edibol--; _velocity = 0.005f; }
		void time(int t) { _time = t; }
		void velocity(float v) { _velocity = v; }
		void dir(float dir){ _dir = dir; }
		void incAngle(float angle) {_angle += angle;}
		void inDecision(bool state) { _inDecision = state; }
		void drawed(bool drawed)	{ _drawed = drawed; }
		void edibol(int edibol)		{ _edibol = edibol;	}

		//Getters
		int id()		{   return _id;	}
		float getPosition(int axis) {return _position[axis];} 
		float radius()		{ return _radius; }
		float getAngle() const {return _eyesAngle;}
		float angle()	{ return _angle; }
		int getEdibol()  {return _edibol; }
		float getColor(int c) { return _color[c]; }
		int getTime()	{ return _time; }
		float getVelocity() { return _velocity; }
		bool getDecision() { return _inDecision; }
		int edibol()	{ return _edibol;	}
		bool changeDir() { return _changeDir; }
		float dir() {return _dir; }
		float origen(int i) { return _origen[i]; }
		bool drawed()	{ return _drawed; }

		// Métodos
		public:
			//void update(pacman::Wall wall, float x, float y);
			void update(pacman::Drawable *obj);
			float updatePhantomPos(float x, float y);
			void move(float delta, int axis, pacman::Drawable *obj);
			void selectionMove(pacman::Drawable *obj, float delta);
			void draw(void);
			void drawBody(void);
			void drawEye(void);
			void drawBrush(void);
			void updatePos(float x, float y);
			void moveEyes(void);
			void updateEyesPos(float x, float y);
			float calcAngle(float x, float y);
			bool greaterThanCenter(float a, float b, float delta);
			void rotate(float nextAngle);
			float oppositeCoordinate(int axis);
			float invCommand(float cmd);
			void throwProb();
			float generateToken();
			float calcDist(float x1, float y1, float x2, float y2);
			void simulationCmd(int stopped);
			void drawOrigen();
			void waitting(int id);
			void explosionPac();
			bool interpenetra();
			void initWhiteMaterial();
			void initColorMaterial();
			void initBlackMaterial();
	};


}