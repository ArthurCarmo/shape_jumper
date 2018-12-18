#ifndef _SHAPE_H
#define _SHAPE_H

#include "point.h"

class shape {

	public:
		point center;
		bool fill;
		
		virtual bool onscreen() const = 0;
		virtual void draw() const = 0;
		virtual void translade(double x, double y) = 0;
		virtual bool overlaps (const circle) const = 0;
		virtual bool overlaps (const rectangle) const = 0;
		virtual bool overlaps (const triangle) const = 0;
		
};

#endif
