#ifndef _POINT_H
#define _POINT_H

#include <cmath>

class point {
	public:
		double x;
		double y;
		point(double a = 0 , double b = 0) : x(a), y(b) { }
	
		double distance(point p) const { return std::sqrt((this->x-p.x)*(this->x-p.x) + (this->y-p.y)*(this->y-p.y)); }
		double vector_len() const { return std::sqrt(this->x*this->x + this->y*this->y); }
		
};

#endif
