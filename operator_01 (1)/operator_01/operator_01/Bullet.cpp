#include "Bullet.h"

void Bullet::Update() {

}

Bullet::Bullet(float x, float y, float rotX, float rotY) {
	M3.m20 = x; M3.m21 = y;
	M3.m10 = rotX; M3.m11 = rotY;
}