/*
 *author: koutsop
 */
#include "Point.h"
#define MAX_TMP_SIZE 100

/////////////////////////////////////////////////////////////////////


Point::Point(const Point * const pointPtr){
	x = pointPtr->GetX();
	y = pointPtr->GetY();
}
/////////////////////////////////////////////////////////////////////



bool Point::Compare(Point* point) const{
	assert(point);						//Den mporei ena point na einai null 
	if( (point->GetX()) && (point->GetY() == y) )
		return true;
	else
		return false;
}
/////////////////////////////////////////////////////////////////////



string Point::ToString(void) const{
	char tmp[MAX_TMP_SIZE];				//tmp table gia thn dimiourgia tou sring
	sprintf_s(tmp, MAX_TMP_SIZE, "[%d, %d]", x, y);
	return tmp;
}