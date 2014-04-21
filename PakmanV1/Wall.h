#pragma once
#include "Drawable.h"

namespace pacman{

	class Wall : public Drawable
	{
		float _yAxis;
		float _xAxis;
		float _wallSize;
		bool _drawed;
	public:
		Wall(void): _wallSize(1.0f), _yAxis(14.5f), _xAxis(-14.5f), _drawed(true){};
		~Wall(void){};

		void drawed(bool drawed)	{ _drawed = drawed; }
		bool drawed()	{ return _drawed; }

		float wallSize() const {return _wallSize;}
		float yAxis() const { return _yAxis; }
		float xAxis() const { return _xAxis; }
		int iMatrixX(float pos);
		int iMatrixY(float pos);
		void draw(void);
		int getNumLab(int l, int c);

		float itopos(int pos, float limitAxis);
		float incPosValid(float pos,int axis);
		void setMatrix(int i, int j, int tile);
		float centerPos(float pos, int axis);
		float inc(float n, float p);
		void eatBall(float x, float y, int axis, int tile);
		//int *indices(float x, float y, int axis);

		//tests
		bool isWall(float x, float y, int axis);
		void removeBar(float x, float y, int axis);
		bool isDball(float x, float y, int axis);
		bool isPhantomWall(float x, float y, int axis);
		bool isDecision(float x, float y, int axis);
		bool isDecided(float x, float y, float angle1, float angle2, int axis);
		bool isDecided(float x, float y, float angle, int axis);
		bool isEdge(float x, float y, int axis);
		bool isNormalBall(float x, float y, int axis);
		bool isSpecialBall(float x, float y, int axis);
		void initBlueMaterial();
		void initBallsNSMaterial();
		void initBallsMaterial();
		void initGreenMaterial();
	};
}
