#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Drawable.h"
#include "Wall.h"
#include "Phantom.h"

/*Angulos de rotação*/
#define UP 0.0f
#define LEFT 90.0f
#define DOWN 180.0f
#define RIGHT 270.0f
#define NULO -1.0f

namespace pacman{
	class Pacman : public pacman::Drawable {
	private:
		int _life;
		float _xMax;
		float _yMax;
		int _elapsedTime;
		float _velocity;
		float _buffer[2]; /*states buffer*/
		float _dir[2];
		float _position[3];
		float _radius;
		float _angle;
		bool _inDecision;
		int _score;
		bool _drawed;
		float _origen[3];
	public:
		Pacman(float v):_life(3), _xMax(14.5f), _yMax(14.5f), _elapsedTime(0), _velocity(v),
			 _radius(0.5f), _angle(UP), _inDecision(false), _score(0), _drawed(true) {
		_buffer[0] = NULO;
		_buffer[1] = NULO;
		_dir[0] = 0.0f;
		_dir[1] = 1.0f;
		_position[0] = 0.5f;
		_position[1] = -4.5f;
		_position[2] = 1.25f;
		_origen[0] = 0.5f;
		_origen[1] = -4.5f;
		_origen[2] = 1.25f;
		}
		
		~Pacman(void){}
	
		//Setters
		void life(int life)	{ _life = life; }
		void time(int time) {_elapsedTime = time;}
		void dir(int i, float dir)	{ _dir[i] = dir; }
		void angle(float angle) {_angle = angle;}		
		void setPosition(int axis, float inc) {	_position[axis] += inc;}
		void setPos(int axis, float pos) { _position[axis] = pos; }
		void buffer(int numb, float state){ _buffer[numb] = state; }
		void changeState(){ _buffer[0] = _buffer[1]; _buffer[1] = NULO; }
		void incAngle(float angle) {_angle += angle;}
		void inDecision(bool state) { _inDecision = state; }
		void velocity(float v) { _velocity = v; }
		void score(int score) { _score = score; }
		void incScore(int score) { _score += score; }
		void drawed(bool drawed)	{ _drawed = drawed; }
		void decLife()	{ if(_life != 0) _life--;  }
		//Getters
		int life()	{ return _life;	}
		int getTime()    const {return _elapsedTime;}
		int score()			{ return _score; }
		float getPosition(int axis) {return _position[axis];}
		float getRadius(){return _radius;}
		float getXmax()  const {return _xMax;}
		float getYmax()  const {return _yMax;}
		float getAngle() const {return _angle;}
		float currentCommand() {return _buffer[0]; }
		float nextCommand() {return _buffer[1]; }
		bool getDecision() { return _inDecision; }
		float getVelocity() { return _velocity; }
		int getScore() { return _score; }
		float dir(int i)	{ return _dir[i]; }
		bool drawed()	{ return _drawed; }
		float origen(int i)	{	return _origen[i]; }

		//methods
		void update(pacman::Drawable *obj);
		float updatePacmanPos();
		void move(float delta, int axis, pacman::Wall *wall);
		void draw(void);
		void drawBrush(float);
		void drawBrushes(void);
		void drawEye(float x);
		void drawEyes(void);
		void drawHead(void);
		void initYellowMaterial();
		void initBlackMaterial();
		void initWhiteMaterial();
		void setState(float state);
		void rotate(float nextAngle);
		float oppositeCoordinate(int axis);
		bool greaterThanCenter(float a, float b, float delta);
		void alertPhantom();
		void drawOrigen();
		void die();
		void revive();
	};

}