#ifndef BASE_H 
#define BASE_H 
#include "base.h"
#endif 
using namespace std;

class Geometry {
public:
	Geometry() {};
	virtual ~Geometry() = 0;
	virtual bool pointInside(const Point& p) = 0;
};

class Ball: public Geometry {
private:
    Point center;
	double radius;
public:
	Ball(Point center = Point(), double radius = 1):
	  center(center), radius(radius) {};
	bool pointInside(const Point& p);
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
		Direction sectionNVector = Direction(0, 0, 1), 
		bool centerInside = true):
	  center(center), radius(radius), sectionCenter(sectionCenter), sectionNVector(sectionNVector), centerInside(centerInside) {};
	bool pointInside(const Point& p);
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
};

