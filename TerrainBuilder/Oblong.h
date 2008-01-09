/*
 *author: koutsop
 */
 
#ifndef OBLONG_H
#define OBLONG_H

#include "Point.h"

class Oblong{

	Point pointUpLeft, pointDownRight;
	int width, height;

public:
	Oblong(	const int _x1 = 0, 
			const int _y1 = 0,
			const int _x2 = 0,
			const int _y2 = 0,
			const int _width = 0, 
			const int _height = 0);
		  	  
	Oblong(	const Point _pointUpLeft, 
			const Point _pointDownRight,
			const int _width, 
			const int _height);

	Oblong( const Point * const _pointUpLeft, 
			const Point * const _pointDownRight,
			const int _width, 
			const int _height);

	//copy constructor
	Oblong(const Oblong &oblong);

	//destructor
	virtual~Oblong() {}

	/* @target: Na epistrefei weigth apo ena object Oblong.
	 * @return: thn thmh pou exei to width.
	 */	
	int	GetWidth(void) const { return width; }

	/* @target: Na epistrefei height apo ena object Oblong.
	 * @return: thn thmh pou exei to height.
	 */		
	int GetHeight(void) const { return height; }

	/* @target: Na epistrefei to panw aristera point enos object Oblong.
	 * @return: thn thmh pou exei to panw aristera point.
	 */		
	Point GetPointUpLeft() const { return pointUpLeft; }
	
	/* @target: Na epistrefei to katw de3ia point enos object Oblong.
	 * @return: thn thmh pou exei to katw de3ia  point.
	 */	
	Point GetPointDownRight() const { return pointDownRight; }

	/* @target: Na 8etei thn thmh tou width apo ena object Oblong.
	 * @param : Thn thmh pou 8a parei to width.
	 */	
	void SetWidth(int width) { this->width = width; }

	/* @target: Na 8etei thn thmh tou height apo ena object Oblong.
	 * @param : Thn thmh pou 8a parei to width.
	 */	
	void SetHeight(int height) { this->height = height; }
	
	/* @target: Na 8etei thn thmh tou panw aristero point
	 * @param : Ena point me thn thmh pou 8a parei to panw aristero point
	 */
	void SetPointUpLeft(Point );

	/* @target: Na 8etei thn thmh tou katw de3ia point
	 * @param : Ena point me thn thmh pou 8a parei to katw de3ia point
	 */	
	void SetPointDownRight(Point );
	
	/* @target: Na 8etei thn thmh tou panw aristera point
	 * @param : Duo sentetagmenes x,y me ths times pou 8a parei to panw aristera point
	 */
	void SetPointUpLeft(int , int);

	/* @target: Na 8etei thn thmh tou katw de3ia point
	 * @param : Duo sentetagmenes x,y me ths times pou 8a parei to katw de3ia point
	 */	
	void SetPointDownRight(int , int );
};

#endif //define OBLONG_H
