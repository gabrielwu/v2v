#ifndef BASE_H 
#define BASE_H 
#include "base.h"
#endif 
using namespace std;

class Geometry {
public:
	Geometry() {};
	//virtual ~Geometry() = 0;!!!
	virtual bool pointInside(const Point& p) = 0;
	virtual void display() = 0;
};

class Ball: public Geometry {
private:
    Point center;
	double radius;
public:
	Ball(Point center = Point(), double radius = 1):
	  center(center), radius(radius) {};
	bool pointInside(const Point& p);
	void display();
};

class BallPart: public Geometry {
private:
    Point center;
	double radius;
	Point sectionCenter;
	Direction sectionNVector;
	bool centerInside;
public:
	BallPart(Point center = Point(), 
		double radius = 1, 
		Point sectionCenter = Point(), 
		bool centerInside = true):
	  center(center), radius(radius), sectionCenter(sectionCenter), centerInside(centerInside) {
	    this->sectionNVector = (sectionCenter - center).getUnitDirection();
	};
	bool pointInside(const Point& p);
	void display();
};
// Ô²Öù
class Cylinder: public Geometry {
private:
	Point topCenter;
	Point bottomCenter;
	double radius;
public:
	Cylinder(Point topCenter = Point(0,0,1), Point bottomCenter = Point(0,0,0), double radius = 1):
	  topCenter(topCenter), bottomCenter(bottomCenter), radius(radius) {};
	bool pointInside(const Point& p);
	void display();
};

// Ô²×¶
class Cone: public Geometry {
private:
	Point top;
	Point bottomCenter;
	double radius;
public:
	Cone(Point top = Point(0,0,1), Point bottomCenter = Point(), double radius = 1):
	  top(top), bottomCenter(bottomCenter), radius(radius) {};
	bool pointInside(const Point& p);
	void display();
};

// ÍÖÇò
class Ellipse: public Geometry {
private:
	Point focus0;
	Point focus1;
	Point center;
	double a;
	double b;
	double c;
public:
    Ellipse(Point focus0, Point focus1, double a, double b) {
	    this->focus0 = focus0;
		this->focus1 = focus1;
		this->a = a;
		this->b = b;
		this->c = getDistance(focus0, focus1) / 2;
		this->center = getCenterPoint(focus0, focus1);
	};
	bool pointInside(const Point& p);
	void display();
};
// ²¿·ÖÍÖÇò
class EllipsePart: public Geometry {
private:
	Point focus0;
	Point focus1;
	Point center;
	double a;
	double b;
	double c;
	Direction sectionNVector;
	Point sectionCenter;
	bool centerInside;
public:
    EllipsePart(Point focus0, Point focus1, double a, double b, Point sectionCenter, bool centerInside) {
	    this->focus0 = focus0;
		this->focus1 = focus1;
		this->a = a;
		this->b = b;
		this->c = getDistance(focus0, focus1) / 2;
		this->center = getCenterPoint(focus0, focus1);
		this->sectionCenter = sectionCenter;
		this->sectionNVector = (sectionCenter - center).getUnitDirection();
		this->centerInside = centerInside;
	};
	bool pointInside(const Point& p);
	void display();
};

// ³¤·½Ìå
class Cuboid: public Geometry {
private:
	Point p0;
	Point p1;
	Point p2;
	Point p3;
	Point p4;
	Point p5;
	Point p6;
	Point p7;
	double length;
	double width;
	double height;
	Direction vL;
	Direction vW;
	Direction vH;
public:
    Cuboid(Direction vL, Direction vW, Direction vH, Point p0) {
		this->vL = vL;
		this->vW = vW;
		this->vH = vH;
	    this->p0 = p0;
        this->p1 = p0 + vL;
		this->p2 = p0 + vW;
		this->p3 = p0 + vH;
		this->p4 = p0 + vL + vW + vH;
		this->p5 = this->p4 - vL;
		this->p6 = this->p4 - vW;
		this->p7 = this->p4 - vH;
		this->length = vL.getModule();
		this->width = vW.getModule();
		this->height = vH.getModule();
	};
    bool pointInside(const Point& p);
	void display();
};