#pragma once
#include "GameObject.h"
//#include "Asteroid.h"

class Helper //Matrix 3
{
public:
	Helper();
	~Helper();
	struct Matx3 {
		float m00, m10, m20;
		float m01, m11, m21;
		float m02, m12, m22;
		Matx3();
		bool Collision(float cx, float cy, float radius, float x, float y) {
			return sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy)) < radius;
		}

		void WrapCoordinates(float ix, float iy, float& ox, float& oy) {
			oy = iy;
			ox = ix;
			if (ix < 0.0f) ox = ix + (float)GetScreenWidth();
			if (ix >= (float)GetScreenWidth()) ox = ix - (float)GetScreenWidth();

			if (iy < 0.0f) oy = iy + (float)GetScreenHeight();
			if (iy >= (float)GetScreenHeight()) oy = iy - (float)GetScreenHeight();

		}

		void Set(Matx3 matrix) {

			matrix.m00 = 1; matrix.m10 = 0; matrix.m20 = 0;
			matrix.m01 = 0; matrix.m11 = 1; matrix.m21 = 0;
			matrix.m02 = 0; matrix.m12 = 0; matrix.m22 = 1;

		}

		void Rotate(float DeltaTime, Matx3 matrix) {
			float c = (float)cos(DeltaTime);
			float s = (float)sin(DeltaTime + PI);

			Matx3 temp;
			Set(temp);

			temp.m00 = matrix.m00 * c + matrix.m10 * -s + matrix.m20 * 0;
			temp.m01 = matrix.m01 * c + matrix.m11 * -s + matrix.m21 * 0;
			temp.m02 = matrix.m02 * c + matrix.m12 * -s + matrix.m22 * 0;

			temp.m10 = matrix.m00 * s + matrix.m10 * c + matrix.m20 * 0;
			temp.m11 = matrix.m01 * s + matrix.m11 * c + matrix.m21 * 0;
			temp.m12 = matrix.m02 * s + matrix.m12 * c + matrix.m22 * 0;

			matrix.m00 = temp.m00; matrix.m10 = temp.m10;
			matrix.m01 = temp.m01; matrix.m11 = temp.m11;
		}
	};

		void Set(Matx3 Matrix);
		void Rotate(float DeltaTime, Matx3 Matrix);
		bool Collision(float cx, float cy, float radius, float x, float y);
		void WrapCoordinates(float ix, float iy, float& ox, float& oy);
		float angle();



};

//float c = (float)cos(-GetFrameTime() * rotSpeed);
//float s = (float)sin(-GetFrameTime() * rotSpeed + PI);

//gameObject temp;
//Set(temp);
//
//temp.m00 = player.m00 * c + player.m10 * -s + player.m20 * 0;
//temp.m01 = player.m01 * c + player.m11 * -s + player.m21 * 0;
//temp.m02 = player.m02 * c + player.m12 * -s + player.m22 * 0;
//
//temp.m10 = player.m00 * s + player.m10 * c + player.m20 * 0;
//temp.m11 = player.m01 * s + player.m11 * c + player.m21 * 0;
//temp.m12 = player.m02 * s + player.m12 * c + player.m22 * 0;
//
//player.m00 = temp.m00; player.m10 = temp.m10;
//player.m01 = temp.m01; player.m11 = temp.m11;