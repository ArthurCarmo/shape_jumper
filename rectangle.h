#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include "sjfwd.h"
#include "shape.h"
#include "point.h"

class rectangle : public shape {
	
	public: 
		double xlen;
		double ylen;
		
		rectangle(double cx = 0, double cy = 0, double xl = 1, double yl = 1, bool fl = false){ 
			this->center = point(cx, cy);
			this->xlen = xl;
			this->ylen = yl;
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
