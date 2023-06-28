#include "Helper.h"



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