#include "rectangle.h"

//rectangle::rectangle(int x, int y){
//	x = x;
//	y = y;
//}

int rectangle::getx(){
	return x;
}

int rectangle::gety(){
	return y;
}

void rectangle::setx(int x){
	this->x = x;
}

void rectangle::sety(int y){
	this->y = y;
}

rectangle::rectangle(int x, int y){
	this->x = x;
	this->y = y;
}