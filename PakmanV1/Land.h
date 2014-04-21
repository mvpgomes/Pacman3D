#pragma once
#include <iostream>
#include <GL\glut.h>
#include "Drawable.h"

namespace pacman{
	class Land : public Drawable
	{
		float _cubeSize;
		float _h;
		float _scaleZ;
		bool _isDrawed;
		int _subs;
		bool _drawed;
		bool _textureOn;
	public:
		Land(void): _cubeSize(30.0f), _scaleZ(0.05f), _isDrawed(true), _subs(250), _drawed(true), _textureOn(false) {};
		virtual ~Land(void){};
		void drawLand();
		float getHeight(){	return _h; }
		int subs()	{ return _subs; }
		void subs(int subs)	{ _subs = subs; }
		void drawed(bool drawed)	{ _drawed = drawed; }
		bool drawed()	{ return _drawed; }
		void drawTexture();
		void draw(){ if(!_textureOn) { drawLand(); } else drawTexture(); }

		void texture(bool text) { _textureOn = text;}
		bool texture() { return _textureOn; }
		void initWhiteMaterial();
	};

}
