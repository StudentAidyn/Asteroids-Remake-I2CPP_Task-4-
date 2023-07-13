#include "GameObject.h"

//Functions displayed so the Debugger/system won't complain-------------
GameObject::GameObject() {

}

GameObject::~GameObject() {

}

void GameObject::Update() {

}

void GameObject::Draw() {

}
//---------------------------------------------------------------------

//States angle created from Matrix 3
float GameObject::angle() {
	float result;
	result = atan2(M3.m10, M3.m11);
	return result;
}

//Sets Matrix 3 to an Identity Matrix
void GameObject::Matrix3::Set() {
	m00 = 1; m10 = 0; m20 = 0;
	m01 = 0; m11 = 1; m21 = 0;
	m02 = 0; m12 = 0; m22 = 1;
}