#include "math.h"
#include "base.h"
double dBtoPercent(double dBvalue) {
    return pow(10, dBvalue / 20);
};
ComplexNumber ComplexNumber::operator +(ComplexNumber& c) {
    double re = this->re + c.re;
	double im = this->im + c.im;
	return ComplexNumber(re, im);
}
ComplexNumber ComplexNumber::operator -(ComplexNumber& c) {
    double re = this->re - c.re;
	double im = this->im - c.im;
	return ComplexNumber(re, im);
}	
ComplexNumber ComplexNumber::operator -() {
    double re = -this->re;
	double im = -this->im;
	return ComplexNumber(re, im);
}
ComplexNumber ComplexNumber::operator *(ComplexNumber& c) {
    double re = this->re * c.re - this->im * c.im;
	double im = this->im * c.re + this->re * c.im;
	return ComplexNumber(re, im);
}
ComplexNumber ComplexNumber::operator /(ComplexNumber& c) {
	double d = pow(c.re, 2) + pow(c.im, 2);
    double re = (this->re * c.re + this->im * c.im) / d;
	double im = (this->im * c.re - this->re * c.im) / d;
	return ComplexNumber(re, im);
}
ComplexNumber ComplexNumber::operator +(double c) {
    double re = this->re + c;
	double im = this->im;
	return ComplexNumber(re, im);
}
ComplexNumber ComplexNumber::operator -(double c) {
    double re = this->re - c;
	double im = this->im;
	return ComplexNumber(re, im);
}	
ComplexNumber ComplexNumber::operator *(double c) {
    double re = this->re * c;
	double im = this->im * c;
	return ComplexNumber(re, im);
}
ComplexNumber ComplexNumber::operator /(double c) {
    double re = this->re / c;
	double im = this->im / c;
	return ComplexNumber(re, im);
}
// Point 
Direction Point::operator-(Point& p) {
	double i = this->x - p.x;
	double j = this->y - p.y;
	double k = this->z - p.z;
	return Direction(i, j, k);	
}
Direction Point::operator-(const Point& p) {
	double i = this->x - p.x;
	double j = this->y - p.y;
	double k = this->z - p.z;
	return Direction(i, j, k);	
}
Point Point::operator-(const Direction& p) {
	double i = this->x - p.i;
	double j = this->y - p.j;
	double k = this->z - p.k;
	return Point(i, j, k);	
}
Direction Point::operator+(Point& p) {
	double i = this->x + p.x;
	double j = this->y + p.y;
	double k = this->z + p.z;
	return Direction(i, j, k);	
}
Point Point::operator+(Direction& d) {
	double x = this->x + d.i;
	double y = this->y + d.j;
	double z = this->z + d.k;
	return Point(x, y, z);	
}
double Point::operator*(Direction& d) {
	double x = this->x * d.i;
	double y = this->y * d.j;
	double z = this->z * d.k;
	return (x + y + z);	
}
Point Point::operator*(double m) {
	double x = this->x * m;
	double y = this->y * m;
	double z = this->z * m;
	return Point(x, y, z);	
}
Point Point::operator/(double m) {
	double x = this->x / m;
	double y = this->y / m;
	double z = this->z / m;
	return Point(x, y, z);	
}
bool Point::operator<(Point& p) {
    if (this->x < p.x && this->y < p.y && this->z < p.z) {
	    return true;
	} else {
	    return false;
	}
}
bool Point::operator>(Point& p) {
    if (this->x > p.x && this->y > p.y && this->z > p.z) {
	    return true;
	} else {
	    return false;
	}
}
double Point::calculateD(Direction& d) {
	return -(this->operator*(d));
}

// Direction
double Direction::operator*(Point& p) {
	double x = this->i * p.x;
	double y = this->j * p.y;
	double z = this->k * p.z;
	return (x + y + z);	
}
double Direction::operator*(const Point& p) {
	double x = this->i * p.x;
	double y = this->j * p.y;
	double z = this->k * p.z;
	return (x + y + z);	
}
Direction Direction::operator+(Direction& d) {
	double i = this->i + d.i;
	double j = this->j + d.j;
	double k = this->k + d.k;
	return Direction(i, j, k);
}
Direction Direction::operator+=(Direction& d) {
	double i = this->i + d.i;
	double j = this->j + d.j;
	double k = this->k + d.k;
	return Direction(i, j, k);
}
Direction Direction::operator-(Direction& d) {
	double i = this->i - d.i;
	double j = this->j - d.j;
	double k = this->k - d.k;
	return Direction(i, j, k);	
}
Direction Direction::operator-() {
	double i = -this->i;
	double j = -this->j;
	double k = -this->k;
	return Direction(i, j, k);	
}
double Direction::operator*(Direction& d) {
	double i = this->i * d.i;
	double j = this->j * d.j;
	double k = this->k * d.k;
	return (i + j + k);
}
Direction Direction::operator*(double module) {
	double i = this->i * module;
	double j = this->j * module;
	double k = this->k * module;
	return Direction(i, j, k);
}
Direction Direction::operator*=(double module) {
	double i = this->i * module;
	double j = this->j * module;
	double k = this->k * module;
	return Direction(i, j, k);
}
Direction Direction::operator^(Direction& d) {
	double i = this->j * d.k - this->k * d.j;
	double j = this->i * d.k - this->k * d.i;
	double k = this->i * d.j - this->j * d.i;
	return Direction(i, j, k);
}
bool Direction::operator==(Direction& d) {
	if (this->i == d.i && this->j == d.j &&this->k == d.k) {
		return true;
	} else {
	    return false;
	}
}
double Direction::getModule() {
	double module = sqrt(pow(this->i, 2) + pow(this->j, 2) + pow(this->k, 2));
	return module;
}
Direction Direction::getUnitDirection() {
	double l = sqrt(pow(this->i, 2) + pow(this->j, 2) + pow(this->k, 2));
	if (l != 0) {
	    Direction unitD(this->i/l, this->j/l, this->k/l);
	    return unitD;
	} else {
		Direction unitD(0, 0, 0);
	    return unitD;
	}
}
Direction getUnitDirection(const Direction& d) {
	double l = sqrt(pow(d.i, 2) + pow(d.j, 2) + pow(d.k, 2));
	if (l != 0) {
		Direction unitD(d.i/l, d.j/l, d.k/l);
		return unitD;
	} else {
		Direction unitD(0, 0, 0);
		return unitD;
	}
}


Point Point::getSymmetricPoint(const Surface& s) {
	double a = s.getA();
	double b = s.getB();
	double c = s.getC();
	double d = s.getD();
	Point p0(this->x, this->y, this->z);
	if (a ==0 && b == 0 && c == 0 || s.isPointOn(p0)) {
	    return Point(0, 0, 0);
	} else {
		double x0 = this->x;
	    double y0 = this->y;
	    double z0 = this->z;
		double t = -(a * x0 + b* y0 + c * z0 + d) / (a * a + b * b + c * c);

		double x1 = a * t + x0;
		double y1 = b * t + y0;
		double z1 = c * t + z0;
		double x = 2 * x1 - x0;
		double y = 2 * y1 - y0;
		double z = 2 * z1 - z0;
		Point p(x, y, z);
		return p;
	}
}

Direction Direction::getSymmDirect(const Surface& s) {
	Point p0(0, 0, 0);
	Point p1(this->i, this->j, this->k);
	Point ps0 = p0.getSymmetricPoint(s);
	Point ps1 = p1.getSymmetricPoint(s);
	Direction d = ps1 - ps0;
	return d;
}
Direction Direction::getRelDirectOnReflect(const vector<Surface>& surfaces) {
	Direction d(this->i, this->j, this->k);
	for (int n = surfaces.size() - 1; n >= 0 ; n--) {
		d = d.getSymmDirect(surfaces[n]);
	}
	return d;
}
// Surface
double Surface::getA() const {
	return this->a;
}
double Surface::getB() const {
	return this->b;
}
double Surface::getC() const {
	return this->c;
}
double Surface::getD() const {
	return this->d;
}
bool Surface::isOutLine(Point& p0, Point& p1) {
	if (this->p0.x > p0.x && this->p1.x > p0.x && this->p0.x > p1.x && this->p1.x > p1.x) {
	    return true;
	} 
	if (this->p0.x < p0.x && this->p1.x < p0.x && this->p0.x < p1.x && this->p1.x < p1.x) {
	    return true;
	} 
	if (this->p0.y > p0.y && this->p1.y > p0.y && this->p0.y > p1.y && this->p1.y > p1.y) {
	    return true;
	} 
	if (this->p0.y < p0.y && this->p1.y < p0.y && this->p0.y < p1.y && this->p1.y < p1.y) {
	    return true;
	} 
	if (this->p0.z > p0.z && this->p1.z > p0.z && this->p0.z > p1.z && this->p1.z > p1.z) {
	    return true;
	} 
	if (this->p0.z < p0.z && this->p1.z < p0.z && this->p0.z < p1.z && this->p1.z < p1.z) {
	    return true;
	} 
	return false;
}
void Surface::calculateEquation() {
//	if (this->points.empty()) {
		Direction d10 = this->p1 - this->p0;
		Direction d12 = this->p1 - this->p2;
		Direction dn = (d10 ^ d12).getUnitDirection();
		this->a = dn.i;
		this->b = dn.j;
		this->c = dn.k;
		this->d = -(this->p1 * dn);
/*	} else {
	    Direction d10 = this->points[0] - this->p0;
		Direction d12 = this->points[0] - this->p1;
		Direction dn = d10 ^ d12;
		this->a = dn.i;
		this->b = dn.j;
		this->c = dn.k;
		this->d = -(this->p1 * dn);
	}
*/
}
void Surface::calculateVector() {
	Direction d(this->a, this->b, this->c);
	this->nVector = getUnitDirection(d);
}
void Surface::init() {
	this->calculateEquation();
	this->calculateVector();
} 
Direction Surface::getNVector() const {
	return this->nVector;
}
Material Surface::getMaterial() const {
	return this->material;
}
void Surface::display(int space) {
	cout<<"p0:";
	this->p0.display();
	cout<<"p1:";
	this->p1.display();
	cout<<"equation:"<<this->a<<"x+"<<this->b<<"y+"<<this->c<<"z+"<<this->d<<"=0"<<endl;
	this->material.display();
}
void Surface::displayExcel() {
	this->p0.displayExcel();
	this->p1.displayExcel();
	this->material.displayExcel();
	cout<<this->maxProtuberH<<"\t";
	cout<<this->protuberHStandDeviat<<"\t";
	cout<<endl;
}
Point Surface::calculateIntersectPoint(Point& p0, Point& p1) {
    Direction d = p1 - p0;
    double t = -(this->d + p0 * this->nVector) / (this->nVector * d);
	return Point(p0 + d * t);
}
bool Surface::isIntersectPointOn(Point& p0, Point& p1) {
    Point p = this->calculateIntersectPoint(p0, p1);
	return this->isPointOn(p);
}
bool Surface::isIntersectPointThrough(Point& p0, Point& p1) {
	Direction d = p1 - p0;
    double t = -(this->d + p0 * this->nVector) / (this->nVector * d);
	if (t > 0 && t < 1) {
	    return true;
	} else {
	    return false;
	}
}
bool Surface::isPointOn(const Point& p) const{
	//Point p = const_cast<Point> pc;
	const Direction p_0(p.x - p0.x, p.y - p0.y, p.z - p0.z);
	const Direction p_1(p.x - p1.x, p.y - p1.y, p.z - p1.z);
	const Direction p_2(p.x - p2.x, p.y - p2.y, p.z - p2.z);

	const Direction p_20(p2.x - p0.x, p2.y - p0.y, p2.z - p0.z);
	const Direction p_10(p1.x - p0.x, p1.y - p0.y, p1.z - p0.z);

	const Direction p_21(p2.x - p0.x, p2.y - p0.y, p2.z - p0.z);
	const Direction p_01(p0.x - p1.x, p0.y - p1.y, p0.z - p1.z);

	const Direction p_02(p0.x - p2.x, p0.y - p2.y, p0.z - p2.z);
	const Direction p_12(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);

    if (this->pointsNum == 3) {
		if (getAngleByVectors(p_20, p_10) <= getAngleByVectors(p_20, p_0)) {
		    return false;
		} else if (getAngleByVectors(p_21, p_01) <= getAngleByVectors(p_21, p_1)) {
		    return false;
		} else if (getAngleByVectors(p_02, p_12) <= getAngleByVectors(p_02, p_2)) {
		    return false;
		} else {
		    return true;
		}
	} else if (this->pointsNum == 4) {
		const Direction p_3(p.x - p3.x, p.y - p3.y, p.z - p3.z);

		const Direction p_20(p2.x - p0.x, p2.y - p0.y, p2.z - p0.z);
		const Direction p_30(p3.x - p0.x, p3.y - p0.y, p3.z - p0.z);

		const Direction p_03(p0.x - p3.x, p0.y - p3.y, p0.z - p3.z);
    	const Direction p_13(p1.x - p3.x, p1.y - p3.y, p1.z - p3.z);

		const Direction p_31(p3.x - p1.x, p3.y - p1.y, p3.z - p1.z);
		const Direction p_21(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
	
		const Direction p_12(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
		const Direction p_02(p0.x - p2.x, p0.y - p2.y, p0.z - p2.z);
		if (getAngleByVectors(p_20, p_30) <= getAngleByVectors(p_20, p_0)) {
		    return false;
		} else if (getAngleByVectors(p_03, p_13) <= getAngleByVectors(p_03, p_3)) {
		    return false;
		} else if (getAngleByVectors(p_31, p_21) <= getAngleByVectors(p_31, p_1)) {
		    return false;
		} else if (getAngleByVectors(p_12, p_02) <= getAngleByVectors(p_12, p_2)) {
		    return false;
		} else {
		    return true;
		}
	} 
	    return false;
	/*
	double x0 = p0.x;
	double y0 = p0.y;
	double z0 = p0.z;
	double x1 = p1.x;
	double y1 = p1.y;
	double z1 = p1.z;
	if ((p.x < x0 && p.x < x1) || (p.x > x0 && p.x > x1)) {
		return false;
	} else if ((p.z < z0 && p.z < z1) || (p.z > z0 && p.z > z1)) {
	    return false;
	} else if ((p.y < y0 && p.y < y1) || (p.y > y0 && p.y > y1)) {
		return false;
	} else {
	    return true;
	}
	*/
};
// Antenna
Direction Antenna::getDirection() const {
	return this->direction;
}
Direction Antenna::getRelativePosition() const {
	return this->relativePosition;
}
Direction Antenna::getAmplitudeDirection() const {
	return this->amplitudeDirection;
}
double Antenna::getAmplitude() const {
	return this->amplitude;
}
void Antenna::display(int space) {
	cout<<"direction:";
	this->direction.display();
	cout<<"relative position:";
	this->relativePosition.display();
	cout<<"amplitude:"<<this->amplitude;
	this->amplitudeDirection.display();
}
void Antenna::displayExcel() {
	this->direction.displayExcel();
	this->amplitudeDirection.displayExcel();
	this->relativePosition.displayExcel();
	cout<<this->amplitude<<"\t";
	cout<<endl;
}
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

// 获取两点间距离
double getDistance(const Point& p0, const Point& p1) {
	return sqrt(pow((p0.x - p1.x), 2) + pow((p0.y - p1.y), 2) + pow((p0.z - p1.z), 2));
};
// 获取两点间距离
double getDistanceByDirection(const Direction& d0, const Direction& d1) {
	return sqrt(pow((d0.i - d1.i), 2) + pow((d0.j - d1.j), 2) + pow((d0.k - d1.k), 2));
};
Point getCenterPoint(const Point& p0, const Point& p1) {
    double x = (p0.x + p1.x) / 2;
    double y = (p0.y + p1.y) / 2;
    double z = (p0.z + p1.z) / 2;
	return Point(x, y, z);
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