#pragma once
#include "Drawable.h"
#define NUM_PARTICLES 1000

typedef struct {
	float radius;
	float x, y, z;    // posiçÁ„o
	float vx, vy, vz; // velocidade 
    float az; // aceleraÁ„o gravidade
	//float ax, ay; // aceleracoes extra
} Particle;


namespace pacman{
	
	class Particles : public Drawable
	{
		bool _drawed;
		float _lifespan;
		Particle particula[NUM_PARTICLES];
	
	public:
		Particles(float x, float y, float z, float radius) : _drawed(false), _lifespan(0){
		//createParticles(x,y,z,radius);
		};

		~Particles(void){};

		bool drawed()	{ return _drawed;	}
		void drawed(bool drawed)	{ _drawed = drawed; }
		void createParticles(float x, float y, float z, float radius);
		//void update(int value);

		void updateParticles(float dt);

		void update(pacman::Drawable *obj);
		void time(float time) {  _lifespan = time; }
		float time()  const {return _lifespan;}
		void draw();
		void initYellowMaterial();
};
}
