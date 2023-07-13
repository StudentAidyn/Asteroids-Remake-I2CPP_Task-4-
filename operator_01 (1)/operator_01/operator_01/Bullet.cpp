#include "Bullet.h"

Bullet::Bullet() {

}

Bullet::~Bullet() {

}

Bullet::Bullet(float _m20, float _m21, float _m10, float _m11) {
	M3.m10 = _m10;	M3.m20 = _m20;
	M3.m11 = _m11;	M3.m21 = _m21;

	xSpeed = bulletSpeed * sinf(angle());
	ySpeed = -bulletSpeed * cosf(angle());
}

void Bullet::Update() {
	M3.m20 += xSpeed * 5 * GetFrameTime();
	M3.m21 += ySpeed * 5 * GetFrameTime();
}

void Bullet::Draw() {
	DrawPixel(M3.m20, M3.m21, ORANGE);
}