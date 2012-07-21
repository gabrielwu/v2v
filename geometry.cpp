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
			if ((this->sectionNVector) * (this->sectionCenter - p) > 0) {
			    return true;
			} else {
			    return false;
			}
		} else {
			if ((this->sectionNVector) * (this->sectionCenter - p) < 0) {
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
bool Ellipse::pointInside(const Point& p) {
    double d0 = getDistance(p, this->focus0);
	double d1 = getDistance(p, this->focus1);
	double d = d0 + d1;
	if (d < 2 * this->a) {
	    return true;
	} else {
	    return false;
	}
}

bool EllipsePart::pointInside(const Point& p) {
    double d0 = getDistance(p, this->focus0);
	double d1 = getDistance(p, this->focus1);
    double distance = d0 + d1;
	if (distance < this->a * 2) {
		if (this->centerInside) {
			if ((this->sectionNVector) * (this->sectionCenter - p) > 0) {
			    return true;
			} else {
			    return false;
			}
		} else {
			if ((this->sectionNVector) * (this->sectionCenter - p) < 0) {
			    return true;
			} else {
			    return false;
			}
		}
	} else {
	    return false;
	}

}

bool Cuboid::pointInside(const Point& p) {
    // 分别求“长、宽、高”对应的各自两个面的平面方程，d
	double dL0 = -(this->p0 * this->vL);
	double dL1 = -(this->p4 * this->vL);
	double dW0 = -(this->p0 * this->vW);
	double dW1 = -(this->p4 * this->vW);
	double dH0 = -(this->p0 * this->vH);
	double dH1 = -(this->p4 * this->vH);
	// 计算p到各面的距离
	double pdL0 = abs((this->vL * p + dL0) / (sqrt(this->vL * this->vL)));
	double pdL1 = abs((this->vL * p + dL1) / (sqrt(this->vL * this->vL)));
	double pdW0 = abs((this->vW * p + dW0) / (sqrt(this->vW * this->vW)));
	double pdW1 = abs((this->vW * p + dW1) / (sqrt(this->vW * this->vW)));
	double pdH0 = abs((this->vH * p + dH0) / (sqrt(this->vH * this->vH)));
	double pdH1 = abs((this->vH * p + dH0) / (sqrt(this->vH * this->vH)));
	// 判断
	if (pdL0 < this->length &&
		pdL1 < this->length &&
		pdW0 < this->width &&
		pdW1 < this->width &&
		pdH0 < this->height &&
		pdH1 < this->height) {
	    return true;
	} else {
	    return false;
	}
}