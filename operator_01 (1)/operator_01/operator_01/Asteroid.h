#pragma once
#include "GameObject.h"
class Asteroid : public GameObject
{
public:
	Asteroid();
	~Asteroid();

	//Inherited Functions
	void Update();
	void Draw();

	//Additional Functions
	void SimpleSet(float x, float y, float xs, float ys, int h);
};

