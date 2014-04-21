#pragma once
#include <vector>

namespace pacman{
	class Drawable
	{
		std::vector<Drawable*> _game;

	public:
		Drawable(void){};
		~Drawable(void){};
		virtual void draw();
		virtual bool drawed() { return false; }
		void add(Drawable *drawable) { _game.push_back(drawable); }
		virtual void update(Drawable *obj) { obj->update(this); }
		Drawable *obj(int id) { return _game[id]; }
		void phantomWhite();
		void phantomColor();
		void phantomWait(int id);
		void phantomRun(int id);
		void deleteObj();
	};
}
