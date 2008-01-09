/*
 *author: koutsop
 */

#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

class Point{
private:
	int x, y;
	
public:
	//copy constructor
	Point(const Point &point): x(point.x), y(point.y) {}

	//constructor
	Point(const int _x, const int _y): x(_x), y(_y) {}

	//constructor 2
	Point(const Point * const pointPtr);

	//conastructor
	Point(): x(0), y(0) {}
		
	//destructor
	~Point(){ }
	
	/* @target: Na epistrefei thn suntetagmenh x apo ena object point
	 * @return: Thn suntetagmenh x
	 */
	 int GetX(void) const { return x; }
	 
	/* @target: Na epistrefei thn suntetagmenh y apo ena object point
	 * @return: Thn suntetagmenh y
	 */
	 int GetY(void) const { return y; }
	 
	/* @target: Na 8etei thn thmh suntetagmenh x apo ena object point
	 * @input : Thn thmh pou 8a parei h suntetagmenh x
	 */
	 void SetX(const int x) { this->x = x; }
	 
	/* @target: Na 8etei thn thmh suntetagmenh y apo ena object point
	 * @input : Thn thmh pou 8a parei h suntetagmenh y
	 */
	 void SetY(const int y) { this->y = y; }

	 /* @target: Kanei seihrisei an duo points einai idia.
	  * @return: true an ta duo point exoun to idio x,y ena pors ena
	  *		     false an diaferei ena apo ta x,y
	  */
	 bool Compare(Point* point) const;

	 /* @target: Na metatrepei ena ta x,y se morfh string.
	  * @return: Ta x,y me morfh string.
	  */
	 string ToString(void) const;
};

#endif
