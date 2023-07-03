#include "GameObject.h"

GameObject::GameObject() {
	
}

GameObject::~GameObject() {

}

//void GameObject::Rotate(float DeltaTime, Matrix3 matrix) {
//	float c = (float)cos(DeltaTime);
//	float s = (float)sin(DeltaTime + PI);
//	
//	Matrix3 temp;
//	Set(temp);
//	
//	temp.m00 = matrix.m00 * c + matrix.m10 * -s + matrix.m20 * 0;
//	temp.m01 = matrix.m01 * c + matrix.m11 * -s + matrix.m21 * 0;
//	temp.m02 = matrix.m02 * c + matrix.m12 * -s + matrix.m22 * 0;
//	
//	temp.m10 = matrix.m00 * s + matrix.m10 * c + matrix.m20 * 0;
//	temp.m11 = matrix.m01 * s + matrix.m11 * c + matrix.m21 * 0;
//	temp.m12 = matrix.m02 * s + matrix.m12 * c + matrix.m22 * 0;
//	
//	matrix.m00 = temp.m00; matrix.m10 = temp.m10;
//	matrix.m01 = temp.m01; matrix.m11 = temp.m11;
//}

//void GameObject::Set(Matrix3 matrix) {
//
//	matrix.m00 = 1; matrix.m10 = 0; matrix.m20 = 0;
//	matrix.m01 = 0; matrix.m11 = 1; matrix.m21 = 0;
//	matrix.m02 = 0; matrix.m12 = 0; matrix.m22 = 1;
//
//}

//void GameObject::WrapCoordinates(float ix, float iy, float& ox, float& oy) {
//	oy = iy;
//	ox = ix;
//	if (ix < 0.0f) ox = ix + (float)GetScreenWidth();
//	if (ix >= (float)GetScreenWidth()) ox = ix - (float)GetScreenWidth();
//
//	if (iy < 0.0f) oy = iy + (float)GetScreenHeight();
//	if (iy >= (float)GetScreenHeight()) oy = iy - (float)GetScreenHeight();
//
//}
//
//float GameObject::angle(){
//	float result;
//	result = atan2(M3.m10, M3.m11);
//	return result;
//}

void GameObject::Draw() {
	//leave empty as of now
}

void GameObject::SpriteUpdate() {

}
//bool GameObject::Collision(float cx, float cy, float radius, float x, float y) {
//	return sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy)) < radius;
//}