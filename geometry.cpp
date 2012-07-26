#include "geometry.h"

bool Ball::pointInside(const Point& p) {
	double distance = getDistance(p, this->center);
	if (distance < this->radius) {
	    return true;
	} else {
	    return false;
	}
}
void Ball::display() {
    cout<<"形状\t球体"<<endl;
	cout<<"球心\t";this->center.display();
	cout<<"半径\t"<<this->radius<<endl;
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
void BallPart::display() {
    cout<<"形状\t部分球体"<<endl;
	cout<<"球心\t";this->center.display();
	cout<<"半径\t"<<this->radius<<endl;
	cout<<"截面圆心\t";this->sectionCenter.display();
	cout<<"球心是否在体内\t"<<this->centerInside<<endl;
}
bool Cylinder::pointInside(const Point& p) {
	double t = -(((this->bottomCenter - p) * (this->topCenter - this->bottomCenter)) 
		/ ((this->topCenter - this->bottomCenter) * (this->topCenter - this->bottomCenter)));
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
void Cylinder::display() {
    cout<<"形状\t圆柱"<<endl;
	cout<<"底面圆心\t";this->bottomCenter.display();
	cout<<"顶面圆心\t";this->topCenter.display();
	cout<<"半径\t"<<this->radius<<endl;
}
bool Cone::pointInside(const Point& p) {
    double t = -(((this->bottomCenter - p) * (this->top - this->bottomCenter)) 
		/ ((this->top - this->bottomCenter) * (this->top - this->bottomCenter)));
	Point footPoint = this->bottomCenter + (this->top - this->bottomCenter) * t;
	double distance = getDistance(p, footPoint);
	if (t > 0 && t < 1) {
		double sectionRadius = (1 - t) * this->radius;
		if (distance < sectionRadius) {
		    return true;
		} else {
		    return false;
		}
	} else {
	    return false;
	}
}
void Cone::display() {
    cout<<"形状\t圆锥"<<endl;
	cout<<"顶点\t";this->top.display();
	cout<<"顶面圆心\t";this->bottomCenter.display();
	cout<<"底面半径\t"<<this->radius<<endl;
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

void Ellipse::display() {
    cout<<"形状\t椭球"<<endl;
	cout<<"焦点0\t";this->focus0.display();
	cout<<"焦点1\t";this->focus1.display();
	cout<<"a\t"<<this->a<<endl;
	cout<<"b\t"<<this->b<<endl;
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
void EllipsePart::display() {
    cout<<"形状\t椭球部分"<<endl;
	cout<<"焦点0\t";this->focus0.display();
	cout<<"焦点1\t";this->focus1.display();
	cout<<"a\t"<<this->a<<endl;
	cout<<"b\t"<<this->b<<endl;
    cout<<"中心在截面的投影\t<<";this->sectionCenter.display();
	cout<<"中心是否在体内\t"<<this->centerInside;
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
void Cuboid::display() {
    cout<<"形状\t长方体"<<endl;
	cout<<"基准点\t";this->p0.display();
	cout<<"长（方向）\t"<<this->length;this->vL.display();
	cout<<"宽（方向）\t"<<this->width;this->vW.display();
	cout<<"高（方向）\t"<<this->height;this->vH.display();
}