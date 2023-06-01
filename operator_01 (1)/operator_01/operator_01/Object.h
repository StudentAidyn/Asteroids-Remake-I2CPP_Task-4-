#pragma once
#include <raylib.h>
#include <list>

class Object
{

public:
	Object();
	~Object();
	void GameLoad();
	void Update();
	void Controller();
	void CUpdate();
	void SpriteUpdate();
	void Draw();
	void End();

	const float MAX_SPEED = 200.0f;
	bool turbo;
	bool boost;
	
	float bulletSpeed = 80;

	const int DefAsteroid = 5;

	float xRandSpd;
	float yRandSpd;

	float xRandPos;
	float yRandPos;

	float rotSpeed;

	//struct that contains a 3D Matrix
	struct gameObject {
		float m00, m10, m20;
		float m01, m11, m21;
		float m02, m12, m22;
		float xSpeed;
		float ySpeed;
		float thrSpeed;
		int Health;

		bool Alive;

		void SimpleSet(float x, float y, float xs, float ys, int h) {
			m20 = x;
			m21 = y;
			xSpeed = xs;
			ySpeed = ys;
			Health = h;

		};

		float angle() {
			float result;
			result = atan2(m10, m11);
			return result;
		}

	};
	//update the matricies using this math:
	// https://www.alanzucconi.com/2016/02/10/tranfsormation-matrix/#:~:text=This%20tutorial%20will%20introduce%20the,rotate%20and%20scale%202D%20graphics.
	
	//Temporary Matrix 
	gameObject helper;

	//player reference
	gameObject player;

	//copies and duplicate objects
	//std::list <gameObject> asteroids;
	gameObject asteroids[20];
	std::list <gameObject> bullet;


	//position finder for the array
	int arrPos = DefAsteroid - 1;

	int points;

	//gameObject[5]; 
	void AddBullet();

	//player - Ship Graphics
	float mx[7] = { 0.0f, 5.0f, -5.0f, 4.0f, -4.0f, 0.0f, 0.0f };
	float my[7] = { -5.0f, 5.0f, 5.0f, 3.0f, 3.0f,  7.0f, 15.0f };
	float sx[7], sy[7];	

	//Helper Functions
	void Set(gameObject &matrix);
	void Rotate(float radians,const gameObject gOi, gameObject gOo);
	void Transform(float DeltaTime);
	void WrapCoordinates(float ix, float iy, float& ox, float& oy);
	void SpeedCap(float ixs, float iys, float& oxs, float& oys);
	bool Collision(float cx, float cy, float radius, float x, float y);
	Vector2 ANGLE(gameObject);
};

