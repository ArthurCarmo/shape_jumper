#include <GL/glut.h>
#include <cmath>

#include "point.h"
#include "line.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

bool triangle::overlaps(const point p) const {
	point   vec1 (p.x - this->A.x, p.y - this->A.y),
		vec2 (p.x - this->B.x, p.y - this->B.y),
		vec3 (p.x - this->C.x, p.y - this->C.y);
		
	double norm1 = vec1.vector_len();
	double norm2 = vec2.vector_len();
	double norm3 = vec3.vector_len();
		
	double angle12 = std::acos( ( vec1.x*vec2.x + vec1.y * vec2.y ) / ( norm1 * norm2 ) );
	double angle13 = std::acos( ( vec1.x*vec3.x + vec1.y * vec3.y ) / ( norm1 * norm3 ) );
	double angle23 = std::acos( ( vec2.x*vec3.x + vec2.y * vec3.y ) / ( norm2 * norm3 ) );
	
	return (angle12 + angle13 + angle23) >= 2*M_PI - EPSILON && (angle12 + angle13 + angle23) <= 2*M_PI + EPSILON;
	
}

bool triangle::overlaps(const circle c) const {
	return c.overlaps(*this);
}

bool triangle::overlaps(const rectangle r) const {
	return r.overlaps(*this);	
}

bool triangle::overlaps(const triangle t) const {

	if(this->overlaps(t.A)) return true;
	if(t.overlaps(this->A)) return true;

	segment t1_AB (this->A, this->B),
		t1_AC (this->A, this->C),
		t1_BC (this->B, this->C),
		
		t2_AB (t.A, t.B),
		t2_AC (t.A, t.C),
		t2_BC (t.B, t.C);
	
	return  t1_AB.overlaps(t2_AB) || t1_AB.overlaps(t2_AC) || t1_AB.overlaps(t2_BC)
		|| t1_AC.overlaps(t2_AB) || t1_AC.overlaps(t2_AC) || t1_AC.overlaps(t2_BC)
		|| t1_BC.overlaps(t2_AB) || t1_BC.overlaps(t2_AC) || t1_BC.overlaps(t2_BC);
}
	
bool triangle::onscreen() const { return true; }

void triangle::draw() const {

	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(1);

	if(this->fill) {
		glBegin(GL_POLYGON);	
			glVertex2d(this->A.x, this->A.y);
			glVertex2d(this->B.x, this->B.y);
			glVertex2d(this->C.x, this->C.y);
		glEnd();
	} else {
		glBegin(GL_LINE_LOOP);	
			glVertex2d(this->A.x, this->A.y);
			glVertex2d(this->B.x, this->B.y);
			glVertex2d(this->C.x, this->C.y);
		glEnd();
	}
	
	glFlush();
}

void triangle::translade(double x, double y) {
	this->A.x += x;
	this->A.y += y;
	this->B.x += x;
	this->B.y += y;
	this->C.x += x;
	this->C.y += y;
}
