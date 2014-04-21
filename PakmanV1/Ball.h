#pragma once
#include <GL\glut.h>
#include "Drawable.h"


namespace pacman{

	class Ball : public Drawable
	{
		bool _collision, _special;
		float _size;
		bool _drawed;

	public:

		Ball(float size, bool special) : _size(size), _special(special), _collision(false), _drawed(true) {};
		~Ball(void){};
		
		void drawed(bool drawed)	{ _drawed = drawed; }
		bool drawed()	{ return _drawed; }
		void draw(void){
			glutSolidSphere(_size, 16.0f, 16.0f);
		}
	};
}
