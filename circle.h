#ifndef _CIRCLE_H
#define _CIRCLE_H

#include "sjfwd.h"
#include "shape.h"
#include "point.h"

class circle : public shape {

	public:
		double radius;
		
		circle(double cx = 0, double cy = 0, double r = 1, double fl = false) {
			this->center = point(cx, cy);
			this->radius = r;
			this->fill = fl;
		}
		
		bool overlaps(const point) const;
		bool overlaps(const segment) const;
		bool overlaps(const circle) const;
		bool overlaps(const rectangle) const;
		bool overlaps(const triangle) const;
		
		bool onscreen() const;
		
		void draw() const;
		void translade(double, double);
};

#endif
