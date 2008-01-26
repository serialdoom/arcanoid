/*
 * author: koutsop
 */
#ifndef OBLONG_C
#define OBLONG_C


#include "Oblong.h"

Oblong::Oblong(	const int _x1, 
				const int _y1,
				const int _x2,
				const int _y2,
				const int _width, 
				const int _height): pointUpLeft(_x1, _y1),
									pointDownRight(_x2, _y2),
									width(_width), 
									height(_height){}
/////////////////////////////////////////////////////////////////////



Oblong::Oblong(	const Point _pointUpLeft, 
				const Point _pointDownRight,
				const int _width, 
				const int _height): pointUpLeft(_pointUpLeft),
		  							pointDownRight(_pointDownRight),
									width(_width),
									height(_height) {}
/////////////////////////////////////////////////////////////////////



Oblong::Oblong(	const Point * const _pointUpLeft, 
				const Point * const _pointDownRight,
				const int _width, 
				const int _height): pointUpLeft(_pointUpLeft),
	  								pointDownRight(_pointDownRight),
									width(_width),
									height(_height) {}																						
/////////////////////////////////////////////////////////////////////



//copy constructor
Oblong::Oblong(const Oblong &oblong): pointUpLeft(oblong.pointUpLeft),
									  pointDownRight(oblong.pointDownRight),
									  width(oblong.width),
									  height(oblong.height){}
/////////////////////////////////////////////////////////////////////



void Oblong::SetPointUpLeft(Point point){
	pointUpLeft.SetX( point.GetX() );
	pointUpLeft.SetY( point.GetY() );
	return;
}
/////////////////////////////////////////////////////////////////////



void Oblong::SetPointDownRight( Point point){
	pointDownRight.SetX( point.GetX() );
	pointDownRight.SetY( point.GetY() );
	return;
}
/////////////////////////////////////////////////////////////////////



void Oblong::SetPointUpLeft( int x, int y ){
	pointUpLeft.SetX( x );
	pointUpLeft.SetY( y );
	return;	
}
/////////////////////////////////////////////////////////////////////



void Oblong::SetPointDownRight( int x, int y ){
	pointDownRight.SetX( x );
	pointDownRight.SetY( y );
	return;
}
#endif //define OBLONG_C
