#include "stdafx.h"
#ifndef HELPER_H 
#define HELPER_H 
#include "helper.h"
#endif 



// 获取两点间距离
double getDistance(const Point& p0, const Point& p1) {
	return sqrt(pow((p0.x - p1.x), 2) + pow((p0.y - p1.y), 2) + pow((p0.z - p1.z), 2));
};
// 获取两点间距离
double getDistanceByDirection(const Direction& d0, const Direction& d1) {
	return sqrt(pow((d0.i - d1.i), 2) + pow((d0.j - d1.j), 2) + pow((d0.k - d1.k), 2));
};
// 获取点p关于面s的对称点pn
Point* getSymmetricPoint (const Surface& s, const Point& p) {
	double a = s.getA();
	double b = s.getB();
	double c = s.getC();
	double d = s.getD();
	
	if (a ==0 && b == 0 && c == 0 || s.isPointOn(p)) {
	    return NULL;
	} else {
		double x0 = p.x;
	    double y0 = p.y;
	    double z0 = p.z;
		double t = -(a * x0 + b* y0 + c * z0 + d) / (a * a + b * b + c * c);

		double x1 = a * t + x0;
		double y1 = b * t + y0;
		double z1 = c * t + z0;
		double x = 2 * x1 - x0;
		double y = 2 * y1 - y0;
		double z = 2 * z1 - z0;
		Point *ps = new Point(x, y, z);
		return ps;
	}
};
// 获取两点pa、pb连线关于平面s的交点p 
Point* getReflectPoint(const Surface& s, const Point& pa, const Point& pb) {
    double a = s.getA();
	double b = s.getB();
	double c = s.getC();
	double d = s.getD();

	if (a ==0 && b == 0 && c == 0) {
	    return NULL;
	} else {
		double x0 = pa.x;
    	double y0 = pa.y;
	    double z0 = pa.z;
		double x1 = pb.x;
		double y1 = pb.y;
		double z1 = pb.z;
		double i = x0 - x1;
		double j = y0 - y1;
		double k = z0 - z1;
		if (i * a + j * b + k * c == 0) {
		    return NULL;
		} else {
			double t = -(a * x0 + b * y0 + c * z0 + d) / (a * i + b * j + c * k);
		    double x = i * t + x0;
			double y = j * t + y0;
			double z = k * t + z0;
			Point *p = new Point(x, y, z);
			if (!s.isPointOn(*p)) {
				return NULL;
			} else {
	            return p;
			}
		}
	}
};
Reflection* getReflection(const Surface& s, const Point& pt, const Point& pr) {
	const Point* symmetricPoint = &pt;
	if (symmetricPoint != NULL) {
	    Point* reflectPoint = getReflectPoint(s, *symmetricPoint, pr);
		if (reflectPoint != NULL) {
			double length = getDistance(pr, *reflectPoint);
			Direction direction(pr.x - reflectPoint->x, pr.y - reflectPoint->y, pr.z - reflectPoint->z);
			direction = getUnitDirection(direction);
			Reflection* reflection = new Reflection(length, *reflectPoint, pt, pr, s, direction);
			reflection->init();
			return reflection;
		} else {
		    return NULL;
		}
	} else {
	    return NULL;
	}
};
// 多段反射中第一段
Reflection* getFirstReflection(const Point& reflectPoint, const Point& pr, const Antenna& a) {
		double length = getDistance(pr, reflectPoint);
		Direction direction(pr.x - reflectPoint.x, pr.y - reflectPoint.y, pr.z - reflectPoint.z);
		direction = getUnitDirection(direction);

		Direction aDirection = a.getDirection();
		double aAmplitude = a.getAmplitude();
		Direction aAmplitudeDirection = a.getAmplitudeDirection();
	//	Direction h = getScalarProduct(direction, aDirection); 
	//	Direction v = getScalarProduct(h, direction);
		Direction dan = getScalarProduct(aAmplitudeDirection, direction);
		Direction v = getScalarProduct(direction, dan);
		if (v * aAmplitudeDirection < 0) {
		    v = -v;
		}
		Direction h(1,0,0);
		// TODO:correct?
	//	double hAmplitude = h * aAmplitudeDirection * aAmplitude;
		double vAmplitude = v * aAmplitudeDirection * aAmplitude;

		Reflection* reflection = new Reflection(length, reflectPoint, pr, direction);
	//	reflection->setHAmplitude(hAmplitude);
		reflection->setHAmplitude(0);
		reflection->setVAmplitude(vAmplitude);
	//	reflection->setH(h);
		reflection->setH(h);
		reflection->setV(v);
		reflection->setReflectAngle(0);

		return reflection;
};

double getAngleByVectors(const Direction& d0, const Direction& d1) {
	Direction da = getUnitDirection(d0);
	Direction db = getUnitDirection(d1);
	double v = da.i * db.i + da.j * db.j + da.k * db.k;
    double angle = acos(v);
	return angle;
}
double calculateReflectAngle(const Direction& d0, const Direction& d1) {
	double v = d0.i * d1.i + d0.j * d1.j + d0.k * d1.k;
	double angle;
	if (v < 0) {
		Direction d2(-d0.i, -d0.j, -d0.k);
		angle = getAngleByVectors(d2, d1);
	} else {
	      angle = getAngleByVectors(d0, d1);
	}
    return angle;
}
Direction getScalarProduct(const Direction& d0, const Direction& d1) {
	double i = d0.j * d1.k - d0.k * d1.j;
	double j = d0.k * d1.i - d0.i * d1.k;
	double k = d0.i * d1.j - d0.j * d1.i;
	Direction d(i, j, k); 
	d = getUnitDirection(d);
	return d;
}

Point* calculateIntersectPoint(Direction& dLine, Direction& nPlane, Point& pLine, Point& pPlane) {
	double planeD = pPlane.calculateD(nPlane);
	double t = -(pLine * nPlane + planeD) / (dLine * nPlane);
	Point* ptr = new Point(pLine + dLine * t);
	return ptr;
}