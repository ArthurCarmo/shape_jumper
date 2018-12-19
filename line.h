#ifndef _LINE_H
#define _LINE_H

#include <algorithm>
#include <utility>


#include "sjfwd.h"
#include "point.h"

#define EPSILON 0.00000001

class line {

	public:
		// l = ax + by + c
		double a;
		double b;
		double c;
		
		double angular_coefficient() const {
			return -this->a / this->b;
		}
		
		double distance(const line l) const {
			if(std::abs(this->b) < EPSILON) {
				if(std::abs(l.b) < EPSILON){
					return std::abs(-l.c / l.a + this->c / this->a);
				}return 0;
			}
			if(this->angular_coefficient() != l.angular_coefficient()) return 0;
			return this->distance(point(l.x_at(0), 0));
		}
		
		double distance(const point p) const {
			return std::abs(a*p.x + b*p.y + c) / std::sqrt(a*a + b*b);
		}
		
		virtual point closest_from(const point p) const {
			point ans;
			line normal_through_p;
			
			double aux;
			double dist = std::abs(this->a*p.x + this->b*p.y + this->c) / std::sqrt(this->a*this->a + this->b*this->b);
			
			if(dist < EPSILON) return p;
			
			if(std::abs(this->b) < EPSILON) {
				ans.x = -this->c / this->a;
				ans.y = p.y;
				return ans;
			} else if (std::abs(this->a) < EPSILON) {
				ans.x = p.x;
				ans.y = -this->c / this->b;
				return ans;
			}
			
			normal_through_p.a = -this->b / this->a;
			normal_through_p.b = 1;
			normal_through_p.c = -normal_through_p.a*p.x - p.y;
			
			ans = this->interception_point(normal_through_p);
			
			return ans;
		}
		
		double x_at(const double y) const {
			if(std::abs(this->b) < EPSILON) return -this->c / this->b;
			return (this->b*y + this->c) / -this->a;
		}
		
		double y_at(const double x) const {
			if(std::abs(this->b) < EPSILON) return -this->c / this->a;
			return (this->a*x + this->c) / -this->b;
		}
		
		double eval_at(const point p) const {
			return a*p.x + b*p.y + c;
		}
		
		point interception_point(const line &l) const {
		
			point interception;
			if(std::abs(this->a) < EPSILON) {
				if(std::abs(l.a) < EPSILON) return 1.0/0.0;
				
				interception.x = (l.b*this->c - this->b*l.c) / (this->b * l.a);
				interception.y = -this->c / this->b;
				return interception;
			}
			
			if(std::abs(this->b) < EPSILON) {
				if(std::abs(l.b) < EPSILON) return 1.0/0.0;
					
				interception.x = -this->c / this->a;
				interception.y = (l.a*this->c - this->a*l.c) / (this->a * l.b);
				return interception;
			}
			
			if(std::abs(l.a) < EPSILON) {
				interception.x = (this->b*l.c - l.b*this->c) / (l.b * this->a);
				interception.y = -l.c / l.b;
				return interception;
			}
			
			if(std::abs(l.b) < EPSILON) {
				interception.x = -l.c / l.b;
				interception.y = (this->a*l.c - l.a*this->c) / (l.a * this->b);
				return interception;
			}
			
			interception.x = (this->b*l.c - l.b*this->c )/ (this->a*l.b - l.a*this->b);
			interception.y = this->y_at(interception.x);
			return interception;
		}
};

#define X_BOUND 1
#define Y_BOUND 2

class segment : public line {

	public:
		int bound_by;
		double x_ubound;
		double x_lbound;
		double y_ubound;
		double y_lbound;

		
		segment(point p1, point p2) { 
			this->bound_by = X_BOUND;
			if(abs(p1.y - p2.y) < EPSILON) { 
				this->a = 0;
				this->b = 1;
				this->c = -p1.y;
				
			} else if(abs(p1.x - p2.x) < EPSILON) {
				this->a = 1;
				this->b = 0;
				this->c = -p1.x;
			} else {
				this->a = (p1.y - p2.y)/ (p1.x - p2.x);
				this->b = -1;
				this->c = -this->a*p1.x + p1.y;
			}
			this->x_ubound = std::max(p1.x, p2.x);
			this->x_lbound = std::min(p1.x, p2.x);
			this->y_ubound = std::max(p1.y, p2.y);
			this->y_lbound = std::min(p1.y, p2.y);
			
		}
		
		segment(double xu = 0.0f, double xl = 0.0f, double yu = 0.0f, double yl = 0.0f, int bb = X_BOUND) 
		: x_ubound(xu), x_lbound(xl), y_ubound(yu), y_lbound(yl), bound_by(bb) { }
		
		void change_bounds(int bound_type, double lb, double ub) {
			double b1, b2;
			this->bound_by = bound_type;
			if(this->bound_by == X_BOUND){
				x_ubound = ub;
				x_lbound = lb;
				b1 = this->y_at(x_ubound);
				b2 = this->y_at(x_lbound);
				y_ubound = std::max(b1, b2);
				y_lbound = std::min(b1, b2);
			}else{
				y_ubound = ub;
				y_lbound = lb;
				b1 = this->x_at(y_ubound);
				b2 = this->x_at(y_lbound);
				x_ubound = std::max(b1, b2);
				x_lbound = std::min(b1, b2);
			}
		}
		
		void change_bounds(point p1, point p2){
			*this = segment(p1, p2);
		}
		
		std::pair<point, point> limits() const {
			std::pair<point, point> ans  ( std::make_pair( point(this->x_lbound, this->y_lbound),
							   point(this->x_ubound, this->y_ubound) )
						);
					
			if(this->a < 0 == this->b < 0){
				ans.first.y = this->y_ubound;
				ans.second.y = this->y_lbound;
			}
			
			return ans;
		}
		
		bool overlaps(const segment s) const {
			point intercept;
			intercept = this->interception_point(s);
			if(this->distance(s) > EPSILON) return false;
			
			return intercept.x >= this->x_lbound && intercept.x <= this->x_ubound 
				&& intercept.y >= this->y_lbound && intercept.y <= this->y_ubound
				&& intercept.x >= s.x_lbound && intercept.x <= s.x_ubound 
				&& intercept.y >= s.y_lbound && intercept.y <= s.y_ubound;
		}
		
		point closest_from(const point p) const {
			point ans;
			line normal_through_p;
			
			double aux;
			double dist = std::abs(this->a*p.x + this->b*p.y + this->c) / std::sqrt(this->a*this->a + this->b*this->b);
			
			if(dist < EPSILON) {
				ans.x = p.x;
				ans.y = p.y;
				
				if(ans.x < this->x_lbound || ans.x > this->x_ubound ||
					ans.y < this->y_lbound || ans.y > this->y_ubound){
				
					point lim1 (this->x_lbound, this->y_lbound),
						lim2 (this->x_ubound, this->y_ubound);
					
					if(this->a < 0 == this->b < 0){
						lim1.y = this->y_ubound;
						lim2.y = this->y_lbound;
					}
				
					dist = p.distance(lim1);
					aux = p.distance(lim2);
					ans.x = lim1.x;
					ans.y = lim1.y;
				
					if(dist > aux) { ans.x = lim2.x; ans.y = lim2.y; }
				}
				return ans;
			}
			
			if(std::abs(this->b) < EPSILON) {
				ans.x = -this->c / this->a;
				ans.y = p.y;
				if(ans.x < this->x_lbound || ans.x > this->x_ubound ||
					ans.y < this->y_lbound || ans.y > this->y_ubound){
				
					point lim1 (this->x_lbound, this->y_lbound),
						lim2 (this->x_ubound, this->y_ubound);
					
					if(this->a < 0 == this->b < 0){
						lim1.y = this->y_ubound;
						lim2.y = this->y_lbound;
					}
				
					dist = p.distance(lim1);
					aux = p.distance(lim2);
					ans.x = lim1.x;
					ans.y = lim1.y;
				
					if(dist > aux) { ans.x = lim2.x; ans.y = lim2.y; }
				}
				return ans;
			} 
			
			if (std::abs(this->a) < EPSILON) {
				ans.x = p.x;
				ans.y = -this->c / this->b;
				if(ans.x < this->x_lbound || ans.x > this->x_ubound ||
					ans.y < this->y_lbound || ans.y > this->y_ubound){
					
					point lim1 (this->x_lbound, this->y_lbound),
						lim2 (this->x_ubound, this->y_ubound);
						
					if(this->a < 0 == this->b < 0){
						lim1.y = this->y_ubound;
						lim2.y = this->y_lbound;
					}
					
					dist = p.distance(lim1);
					aux = p.distance(lim2);
					ans.x = lim1.x;
					ans.y = lim1.y;
					
					if(dist > aux) { ans.x = lim2.x; ans.y = lim2.y; }
				}
				return ans;
			}
			
			normal_through_p.a = this->b / this->a;
			normal_through_p.b = -1;
			normal_through_p.c = p.y - normal_through_p.a*p.x;
			
			ans = this->interception_point(normal_through_p);
			
			if(ans.x < this->x_lbound || ans.x > this->x_ubound ||
				ans.y < this->y_lbound || ans.y > this->y_ubound){
				
				point lim1 (this->x_lbound, this->y_lbound),
					lim2 (this->x_ubound, this->y_ubound);
					
				if(this->a < 0 == this->b < 0){
					lim1.y = this->y_ubound;
					lim2.y = this->y_lbound;
				}
				
				dist = p.distance(lim1);
				aux = p.distance(lim2);
				ans.x = lim1.x;
				ans.y = lim1.y;
				
				if(dist > aux) { ans.x = lim2.x; ans.y = lim2.y; }
			}
			
			return ans;
		}
};

#endif
