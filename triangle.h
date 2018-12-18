#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "sjfwd.h"
#include "shape.h"
#include "point.h"

class triangle : public shape {

	public:
		point A;
		point B;
		point C;
		
		triangle(point a, point b, point c, bool fl = false){ 
			this->A = a;
			this->B = b;
			this->C = c;
			this->fill = fl;
		}
			
		
		bool overlaps(const point) const;
		bool overlaps(const circle) const;
		bool overlaps(const rectangle) const;
		bool overlaps(const triangle) const;
		
		bool onscreen() const;
		
		void draw() const;
		void translade(double, double);
};

#endif
