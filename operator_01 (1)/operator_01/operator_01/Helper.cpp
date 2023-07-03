#include "Helper.h"

Helper::Helper() {

}

Helper::~Helper() {

}
//Helper::Matrix3{}
bool Helper::Matrix3::Collision(float cx, float cy, float radius, float x, float y) {
	return sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy)) < radius;
}

void Helper::WrapCoordinates(float ix, float iy, float& ox, float& oy) {
	oy = iy;
	ox = ix;
	if (ix < 0.0f) ox = ix + (float)GetScreenWidth();
	if (ix >= (float)GetScreenWidth()) ox = ix - (float)GetScreenWidth();

	if (iy < 0.0f) oy = iy + (float)GetScreenHeight();
	if (iy >= (float)GetScreenHeight()) oy = iy - (float)GetScreenHeight();

}

void Helper::Rotate(float DeltaTime, GameObject::Matrix3 matrix) {
	float c = (float)cos(DeltaTime);
	float s = (float)sin(DeltaTime + PI);

	GameObject::Matrix3 temp;
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

void Helper::Set(GameObject::Matrix3 matrix) {

	matrix.m00 = 1; matrix.m10 = 0; matrix.m20 = 0;
	matrix.m01 = 0; matrix.m11 = 1; matrix.m21 = 0;
	matrix.m02 = 0; matrix.m12 = 0; matrix.m22 = 1;

}

//void Helper::Rotate() {
//	float c = (float)cos(-GetFrameTime() * rotSpeed);
//	float s = (float)sin(-GetFrameTime() * rotSpeed + PI);
//
//	
//	GameObject::Set(temp);
//
//	temp.m00 = player.m00 * c + player.m10 * -s + player.m20 * 0;
//	temp.m01 = player.m01 * c + player.m11 * -s + player.m21 * 0;
//	temp.m02 = player.m02 * c + player.m12 * -s + player.m22 * 0;
//
//	temp.m10 = player.m00 * s + player.m10 * c + player.m20 * 0;
//	temp.m11 = player.m01 * s + player.m11 * c + player.m21 * 0;
//	temp.m12 = player.m02 * s + player.m12 * c + player.m22 * 0;
//
//	player.m00 = temp.m00; player.m10 = temp.m10;
//	player.m01 = temp.m01; player.m11 = temp.m11;
//}
//
//void Helper::Set() {
//
//}