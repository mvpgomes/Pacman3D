#include <iostream>
#include "Drawable.h"
#include "Phantom.h"

void pacman::Drawable::deleteObj(){
	int size = _game.size();

	 for(int i = 0; i < size; i++){
		 _game.pop_back();
	 }
}

void pacman::Drawable::draw(){
	int size = _game.size();

	 for(int i = 0; i < size; i++){
		
		  if(_game[i]->drawed()){
			_game[i]->draw();}

	 }

}

void pacman::Drawable::phantomWhite(){
	int size = _game.size();
	pacman::Phantom *phan;

	for(int i = 3; i < size-1; i++){
		phan = (pacman::Phantom *) _game[i];
		phan->incEdibol();
	}

}

void pacman::Drawable::phantomColor(){
	int size = _game.size();
	pacman::Phantom *phan;

	for(int i = 3; i < size-1; i++){
		phan = (pacman::Phantom *) _game[i];
		phan->decEdibol();
	}

}

void pacman::Drawable::phantomWait(int id) {
	pacman::Phantom *phan;

	phan = (pacman::Phantom *) _game[id];
	phan->drawed(false);

}

void pacman::Drawable::phantomRun(int id) {
	pacman::Phantom *phan;

	phan = (pacman::Phantom *) _game[id];
	phan->drawed(true);

}