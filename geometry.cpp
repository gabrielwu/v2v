#include "geometry.h"

bool Ball::pointInside(const Point& p) {
	double distance = getDistance(p, this->center);
	if (distance < this->radius) {
	    return true;
	} else {
	    return false;
	}
}
bool BallPart::pointInside(const Point& p) {
	double distance = getDistance(p, this->center);
	if (distance < this->radius) {
		if (this->centerInside) {
			if ((this->sectionCenter - this->center) * (this->sectionCenter - p) > 0) {
			    return true;
			} else {
			    return false;
			}
		} else {
			if ((this->sectionCenter - this->center) * (this->sectionCenter - p) < 0) {
			    return true;
			} else {
			    return false;
			}
		}
	} else {
	    return false;
	}

}
bool Cylinder::pointInside(const Point& p) {
	double t = ((this->bottomCenter - p) * (this->topCenter - this->bottomCenter)) 
		/ ((this->topCenter - this->bottomCenter) * (this->topCenter - this->bottomCenter));
	Point footPoint = this->bottomCenter + (this->topCenter - this->bottomCenter) * t;
	double distance = getDistance(p, footPoint);
	if (t > 0 && t < 1) {
		if (distance < this->radius) {
		    return true;
		} else {
		    return false;
		}
	} else {
	    return false;
	}
}
bool Cone::pointInside(const Point& p) {
    double t = ((this->bottomCenter - p) * (this->top - this->bottomCenter)) 
		/ ((this->top - this->bottomCenter) * (this->top - this->bottomCenter));
	Point footPoint = this->bottomCenter + (this->top - this->bottomCenter) * t;
	double distance = getDistance(p, footPoint);
	if (t > 0 && t < 1) {
		double sectionRadius = t * this->radius;
		if (distance < sectionRadius) {
		    return true;
		} else {
		    return false;
		}
	} else {
	    return false;
	}
}