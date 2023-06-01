#pragma once
#include <raylib.h>
#include <vector>

class Game {
public:
	Game();
	bool boost = false;
	bool turbo = false;
	long points = 0;
	struct gameObject {
		float x;
		float y;
		float dx;
		float dy;
		float oSize;
		float angle;
	};
	std::vector<gameObject> asteroid;
	gameObject player;
	std::vector<gameObject> bullet;
	std::vector<gameObject> tempAsteroid;

	void GameLoad();
	void Update();
	void Draw();
	void End();
	void WrapCoordinates(float ix, float iy, float &ox, float &oy);
	bool Collision(float cx, float cy, float radius, float x, float y);
	
};


//https://aie.instructure.com/courses/1019/pages/introduction-to-c++-resources
//ZORP - part 9: CLASSES


/* what is needed to make Asteroids
	- Ship
	- Asteroids


	to make ship we need 
	- matrix sceneObject

	to make Asteroids
	- matrix sceneObject
	- matrix spriteObject
	- Vector2 Move

	Point Counter
	- just make it increase
 
 
 
 
*/