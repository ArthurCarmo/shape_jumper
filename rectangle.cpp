#include <GL/glut.h>
#include <algorithm>

#include "point.h"
#include "line.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

bool rectangle::overlaps(const point p) const {
	return this->center.x - this->xlen/2 <= p.x && p.x <= this->center.x + this->xlen/2
		&& this->center.y - this->ylen/2 <= p.y && p.y <= this->center.y + this->ylen/2;
}
	
bool rectangle::overlaps(const circle c) const {
	point closest_to_circle;
	
	if(c.center.x >= this->center.x) closest_to_circle.x = std::min(this->center.x + this->xlen/2, c.center.x);
	else 				 closest_to_circle.x = std::max(this->center.x - this->xlen/2, c.center.x);
	
	if(c.center.y >= this->center.y) closest_to_circle.y = std::min(this->center.y + this->ylen/2, c.center.y);
	else 				 closest_to_circle.y = std::max(this->center.y - this->ylen/2, c.center.y);
		
	return c.overlaps(closest_to_circle);
}

bool rectangle::overlaps(const rectangle r) const {
	return abs(this->center.x - r.center.x) < (this->xlen+r.xlen)/2
		&& abs(this->center.y - r.center.y) < (this->ylen+r.ylen)/2;
}
		
bool rectangle::overlaps(const triangle t) const {

	point up_right		(this->center.x+this->xlen/2, this->center.y+this->ylen/2),
	down_right		(this->center.x+this->xlen/2, this->center.y-this->ylen/2),
	up_left			(this->center.x-this->xlen/2, this->center.y+this->ylen/2),
	down_left		(this->center.x-this->xlen/2, this->center.y-this->ylen/2);
		
		
	if(this->overlaps(t.A)) return true;
	if(t.overlaps(down_right)) return true;
		
	segment sqr_up		(up_left, up_right);
	segment sqr_down	(down_left, down_right);
	segment sqr_left	(down_left, up_left);
	segment sqr_right	(down_right, up_right);

	segment t_AB		(t.A, t.B);
	segment t_AC		(t.A, t.C);
	segment t_BC		(t.B, t.C);
	
	return	sqr_down.overlaps(t_AB) || sqr_down.overlaps(t_AC) || sqr_down.overlaps(t_BC)
	||	sqr_up.overlaps(t_AB) || sqr_up.overlaps(t_AC) || sqr_up.overlaps(t_BC)
	||	sqr_right.overlaps(t_AB) || sqr_right.overlaps(t_AC) || sqr_right.overlaps(t_BC)
	||	sqr_left.overlaps(t_AB) || sqr_left.overlaps(t_AC) || sqr_left.overlaps(t_BC);
	
}

bool rectangle::onscreen() const { return true; }
		
void rectangle::draw() const {

	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(1);

	if(this->fill) {
		glBegin(GL_TRIANGLES);	
			glVertex2d(this->center.x+this->xlen/2, this->center.y+this->ylen/2);
			glVertex2d(this->center.x+this->xlen/2, this->center.y-this->ylen/2);
			glVertex2d(this->center.x-this->xlen/2, this->center.y+this->ylen/2);
		glEnd();

		glBegin(GL_TRIANGLES);
			glVertex2d(this->center.x+this->xlen/2, this->center.y-this->ylen/2);
			glVertex2d(this->center.x-this->xlen/2, this->center.y+this->ylen/2);
			glVertex2d(this->center.x-this->xlen/2, this->center.y-this->ylen/2);
		glEnd();
		
	} else {
		glBegin(GL_LINE_LOOP);
			glVertex2d(this->center.x+this->xlen/2, this->center.y+this->ylen/2);
			glVertex2d(this->center.x+this->xlen/2, this->center.y-this->ylen/2);
			glVertex2d(this->center.x-this->xlen/2, this->center.y-this->ylen/2);
			glVertex2d(this->center.x-this->xlen/2, this->center.y+this->ylen/2);
		glEnd();
	}

	glFlush();
}

void rectangle::translade(double x, double y) {
	this->center.x += x;
	this->center.y += y;
}
