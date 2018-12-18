#include <GL/glut.h>
#include <cmath>

#include "point.h"
#include "line.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

bool circle::overlaps(const point p) const {
	return this->center.distance(p) <= this->radius;
}

bool circle::overlaps(const segment s) const {
	return  this->center.distance(s.closest_from(this->center)) <= this->radius;
}

bool circle::overlaps(const circle c) const {
	return this->center.distance(c.center) <= this->radius + c.radius;
}

bool circle::overlaps(const rectangle r) const {
	return r.overlaps(*this);
}


bool circle::overlaps(const triangle t) const {
	
	if(t.overlaps(this->center)) return true;
	if(this->overlaps(t.A)) return true;
	
	segment t_AB (t.A, t.B),
		t_AC (t.A, t.C),
		t_BC (t.B, t.C);
		
	return	this->overlaps(t_AB)
		|| this->overlaps(t_AC)
		|| this->overlaps(t_BC);
}
		
bool circle::onscreen() const { return true; }

void circle::draw() const {
	int num_segments = 300;
	double theta;
	double x, y;
	
	glColor3f(1.0, 0.0, 0.0);
	
	glBegin(this->fill?GL_TRIANGLE_FAN:GL_LINE_LOOP);
	for(int ii = 0; ii < num_segments; ii++) {
		theta = M_PI * 2 * ii / num_segments;

		x = this->radius * std::cos(theta);
		y = this->radius * std::sin(theta);

		glVertex2f(x + this->center.x, y + this->center.y);
	}
	
	glEnd();
	glFlush();
}

void circle::translade(double x, double y) {
	this->center.x += x;
	this->center.y += y;
}

