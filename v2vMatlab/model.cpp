#include "stdafx.h"
#include <iostream>
#include <vector>
#ifndef MATH_H 
#define MATH_H 
#include "math.h"
#endif 
#ifndef MODEL_H 
#define MODEL_H 
#include "model.h"
#endif 
#ifndef HELPER_H 
#define HELPER_H 
#include "helper.h"
#endif 



using namespace std;

// Point 
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
Direction Point::operator-(Point& p) {
	double i = this->x - p.x;
	double j = this->y - p.y;
	double k = this->z - p.z;
	return Direction(i, j, k);	
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
double Point::calculateD(Direction& d) {
	return -(this->operator*(d));
}
// Direction
Direction Direction::operator+(Direction& d) {
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
Direction Direction::operator^(Direction& d) {
	double i = this->j * d.k - this->k * d.j;
	double j = this->i * d.k - this->k * d.i;
	double k = this->i * d.j - this->j * d.i;
	return Direction(i, j, k);
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
void Surface::calculateEquation() {
	Direction d10 = this->p1 - this->p0;
	Direction d12 = this->p1 - this->p2;
	Direction dn = d10 ^ d12;
	this->a = dn.i;
	this->b = dn.j;
	this->c = dn.k;
	this->d = -(this->p1 * dn);
	/*
	double x0 = this->p0.x;
	double y0 = this->p0.y;
	double z0 = this->p0.z;
	double x1 = this->p1.x;
	double y1 = this->p1.y;
	double z1 = this->p1.z;
	double x2 = this->p2.x;
	double y2 = this->p2.y;
	double z2 = this->p2.z;
	*/
	/* 平面垂直于xOy
	// 左手坐标系,建筑物垂直于xOz
	this->a = z1 - z0;
	this->b = 0;
	this->c = x0 - x1;
	this->d = z0 * (x1 - x0) - x0 * (z1 - z0);
	*/
	// 论文中的坐标系,建筑物垂直于xOy
	/*
	this->a = y1 - y0;
	this->b = x0 - x1;
	this->c = 0;
	this->d = y0 * (x1 - x0) - x0 * (y1 - y0);
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
	cout<<endl;
}
bool Surface::isPointOn(const Point& p) const{
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
// Vehicle


Point Vehicle::getP() const{
    return p;
}
void Vehicle::displayVehichle() {
	cout<<"  location:";
	this->p.display();
	cout<<"  velocity:"<<this->velocity;
	this->direction.display();
}
void Vehicle::displayVehichleExcel() {
	this->p.displayExcel();
	this->direction.displayExcel();
	cout<<this->velocity;
	cout<<endl;
}
// Path
double Path::getTotalLength() const{
	return this->totalLength;
}
void Path::calculateIr() {
	this->ir[0] = cos(this->vPhaseShift) * this->amplitudeReceive[0];
	this->ir[1] = cos(this->hPhaseShift) * this->amplitudeReceive[1];
}
void Path::init() {
	// 有待确认，百度百科电磁波的多普勒是这么计算的，但论文和书中都是用的第二种，暂用书中的方法

	// 第一种
	/*double v = this->relativeVelocity;
	double a = this->relativeAngle;
	this->frequency = sqrt((C + v) * (C - v) / pow((C - v * cos(a)), 2)) * F;
	this->waveLength = C / this->frequency;
	this->delayTime = this->totalLength / C;
	this->vDoppler = v * cos(a);
	*/
	// 第二种
	
	this->frequency = F + (double)this->vDoppler / C * F;
	this->waveLength = WAVE_LENGTH;
	this->delayTime = this->totalLength / (C + this->vDoppler);
	this->vPhaseShift = this->initPhase[0];
	this->hPhaseShift = this->initPhase[1];
}
// TODO:expect MIMO, SISO now
void Path::calculateAmplitudeReceive(const vector<Antenna>& ras) {
	Antenna a = ras[0];
	int size = this->reflections.size();
	Reflection r = this->reflections[size - 1];
	Direction h = r.getH();
	Direction v = r.getV();
	double hAmplitude = r.getHAmplitude();
	double vAmplitude = r.getVAmplitude();
	// TODO:相移
	double vAmplitudeReceive = (h * hAmplitude + v * vAmplitude) * a.getVDirection();
	double hAmplitudeReceive = (h * hAmplitude + v * vAmplitude) * a.getHDirection();
	this->setAmplitudeReceive(vAmplitudeReceive, hAmplitudeReceive);
}
int Path::getNumOfReflect() const {
	return this->numOfReflect;
}
vector<Reflection> Path::getReflections() {
	return this->reflections;
}
/*
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
			// cout<<"yes"<<endl;
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
		Direction h = getScalarProduct(direction, aDirection);
		Direction v = getScalarProduct(h, direction);
		double hAmplitude = h * aAmplitudeDirection * aAmplitude;
		double vAmplitude = v * aAmplitudeDirection * aAmplitude;

		Reflection* reflection = new Reflection(length, reflectPoint, pr, direction);
		reflection->setHAmplitude(hAmplitude);
		reflection->setVAmplitude(vAmplitude);
		reflection->setH(h);
		reflection->setV(v);
		reflection->setReflectAngle(0);

		return reflection;
};
*/

// 构建单条完整传播路径()
// @pt:发射天线点
// @pr:接收天线点
// @surfaces:假定信号传播路径所经反射面的序列
// return: 若传播路径成立，返回Path对象；否则返回null
// Model
bool Model::getReflectPath(const Point& pt, const Point& pr, const vector<Surface>& surfaces) {
	
	vector<Point> symmetricPoints;
	vector<Point> reflectPoints;
	vector<Reflection> reflections;
	vector<Surface>::const_iterator iterSurfaces = surfaces.begin();
    vector<Surface>::const_reverse_iterator rIterSurfaces = surfaces.rbegin();
//	vector<Point>::const_reverse_iterator rIterSymmPoint = symmetricPoints.rbegin();
	vector<Reflection>::iterator iterReflection;
	double totalLength = 0;
	// 迭代计算发射车的镜像（对称）点
	symmetricPoints.push_back(pt);
	for (; iterSurfaces < surfaces.end(); iterSurfaces++) {
		Point* p = getSymmetricPoint(*iterSurfaces, symmetricPoints.back());
	    if (p != NULL) {
	    	symmetricPoints.push_back(*p);
			delete p;
	    } else {
			delete p;
	        return false;
	    }
	}

	// 迭代计算反射（入射）点，同时建立反射对象
	reflectPoints.push_back(pr);
	for (int i = surfaces.size() - 1; i >= 0; i--) {
		Reflection* reflection = getReflection(surfaces[i], symmetricPoints[i+1], reflectPoints.back());
		if (reflection != NULL) {
			Point* reflectPoint = getReflectPoint(surfaces[i], symmetricPoints[i+1], reflectPoints.back());
			reflectPoints.push_back(*reflectPoint);
			iterReflection = reflections.begin();
			reflections.insert(iterReflection, *reflection);
			totalLength += reflection->getLength();
	    } else {
	        return NULL;
	    }
	}

	// 建立第一段反射对象
	Reflection* reflection = getFirstReflection(pt, reflectPoints.back(), this->tAntennas[0]);
	totalLength += reflection->getLength();
	iterReflection = reflections.begin();
	reflections.insert(iterReflection, *reflection);

	// 计算多普勒、振幅衰减
	double vPhaseShift = 0;
	double hPhaseShift = 0;
	unsigned size = reflections.size();
	for (unsigned j = 1; j < size; j++) {
	    Reflection r1 = reflections[j - 1];
		Reflection r2 = reflections[j];
		Direction rd1 = r1.getDirection();
		Direction rn2 = r2.getV();
		// 振幅衰落
		Direction v1 = r1.getV();
		Direction h1 = r1.getH();
		Direction v2 = r2.getV();
		Direction h2 = r2.getH();
		h1 * h2;
		//double hAmplitude = (r1.getH() * h + r1.getV() * h) * r1.getHAmplitude() * r2.getAmplitudeFadeH();
		//double vAmplitude = (r1.getV() * r2.getV() + r1.getH() * r2.getV()) * r1.getVAmplitude() * r2.getAmplitudeFadeV();
		double hAmplitude = (h1 * r1.getHAmplitude() + v1 * r1.getVAmplitude()) * h2 * r2.getAmplitudeFadeH();
		// 注意差别
		double vAmplitude = (h1 * r1.getHAmplitude() + v1 * r1.getVAmplitude()) * (rn2 ^ rd1) * r2.getAmplitudeFadeV();
		// 相移,配合计算振幅
		double BrewsterAngle = r2.getSurface().getMaterial().getBrewsterAngle();
		
		reflections[j].setVPhaseShift(PI);
		vPhaseShift += PI;
		if (vAmplitude < 0) {
			//reflections[i].setV(-v2);
			vAmplitude = -vAmplitude;
		} else {
			reflections[j].setV(-v2);
		}
		if (reflections[j].getReflectAngle() > BrewsterAngle) {
		    reflections[j].setHPhaseShift(PI);
			hPhaseShift += PI;
			if (hAmplitude < 0) {
			    //reflections[i].setH(-h2);
			    hAmplitude = -hAmplitude;
		    }
		} else if (hAmplitude < 0) {
			reflections[j].setH(-h2);
			hAmplitude = -hAmplitude;
		}
		reflections[j].setHAmplitude(hAmplitude);
		reflections[j].setVAmplitude(vAmplitude);	
	}

	int numberOfReflect = surfaces.size();

	// 多普勒
	Vehicle tx = this->getTransmitter();
	Vehicle rx = this->getReceiver();
	Direction txDirection = tx.getDirection();
	Direction rxDirection = rx.getDirection();
	Direction v = txDirection * tx.getVelocity() - rxDirection.getRelDirectOnReflect(surfaces) * rx.getVelocity();
	Direction vUnit = v.getUnitDirection();
	double relativeAngle = getAngleByVectors(vUnit, reflections[0].getDirection());
	double vt = txDirection * reflections[0].getDirection() * tx.getVelocity();
	double vr = rxDirection * reflections[size - 1].getDirection() * rx.getVelocity();
	double vDoppler = vt - vr;

	// TODO:
	// 
	//double f = sqrt((1 + vDoppler / C) / (1 - vDoppler / C)) * F;
	//double waveLength = C / f;


	
	Path* path = new Path(totalLength, numberOfReflect, reflections);
	//path->setHPhaseShift(hPhaseShift);
	//path->setVPhaseShift(vPhaseShift);
	path->calculateAmplitudeReceive(this->rAntennas);
	//path->setHAmplitude(reflections[size - 1].getHAmplitude());
	//path->setVAmplitude(reflections[size - 1].getVAmplitude());
	//path->setV(reflections[size - 1].getV());
	//path->setH(reflections[size - 1].getH());
	// 初始相位都为0，振幅极化方向已做调整
	path->setInitPhase(0, 0);
	path->setVDoppler(vDoppler);
	path->setRelativeAnge(relativeAngle);
	path->setRelativeVelocity(v.getModule());
	path->setRelVelDirect(vUnit);
	path->init();
	//path->setFrequency(f);
	//path->setWaveLength(waveLength);
	path->calculateFDopplerShift();
	path->calculatePhaseReceive();

	if (path != NULL) {
		insertPath(*path);
		delete path;
		return true;
	}
	
	return false;
	//
};
bool Model::calculateLOSPath() {
	Reflection* reflection = getFirstReflection(this->transmitter.getP(), this->receiver.getP(), this->tAntennas[0]);
	vector<Reflection> reflections;
	reflections.push_back(*reflection);

	Vehicle tx = this->getTransmitter();
	Vehicle rx = this->getReceiver();
	Direction txDirection = tx.getDirection();
	Direction rxDirection = rx.getDirection();
	Direction v = txDirection * tx.getVelocity() - rxDirection * rx.getVelocity();
	Direction vUnit = getUnitDirection(v);
	double relativeAngle = getAngleByVectors(vUnit, reflections[0].getDirection());
	double vt = tx.getDirection() * reflections[0].getDirection() * tx.getVelocity();
	double vr = rx.getDirection() * reflections[0].getDirection() * rx.getVelocity();
	double vDoppler = vt - vr;

	//TODO:
	//double f = sqrt((1 + vDoppler / C) / (1 - vDoppler / C)) * F;
	//double waveLength = C / f;

	Path* path = new Path(reflection->getLength(), 0, reflections);
	path->calculateAmplitudeReceive(this->rAntennas);
	//path->setHAmplitude(reflections[0].getHAmplitude());
	//path->setVAmplitude(reflections[0].getVAmplitude());
	//path->setV(reflections[0].getV());
	//path->setH(reflections[0].getH());
	path->setInitPhase(0, 0);
	path->setVDoppler(vDoppler);
	path->setRelativeAnge(relativeAngle);
	path->setRelativeVelocity(v.getModule());
	path->setRelVelDirect(vUnit);
	path->init();
	//path->setFrequency(f);
	//path->setWaveLength(waveLength);
	path->calculateFDopplerShift();
	path->calculatePhaseReceive();
	insertPath(*path);
	delete path;
	// TODO:return 
	return true;
}
bool Model::calculateReflectPaths() {
	unsigned i = 0;
	unsigned j = 0;
    unsigned k = 0;
	switch (NUM_OF_REFLECTS) {
	    case 1:
            for (i = 0; i < this->surfaces.size(); i++) {
	            vector<Surface> s;
		        s.push_back(this->surfaces[i]);
				getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
	        }
			break;
	    case 2:
			for (i = 0; i < this->surfaces.size(); i++) {
	            vector<Surface> s;
		        s.push_back(this->surfaces[i]);
		        getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
		        
	        }
			for (i = 0; i < this->surfaces.size(); i++) {
		        for (j = 0; j < this->surfaces.size(); j++) {
					if (i == j) {
					    continue;
					}
	                vector<Surface> s;
		            s.push_back(this->surfaces[i]);
			        s.push_back(this->surfaces[j]);
		            getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
					
		        }
	        }
			break;
	    case 3:
			for (i = 0; i < this->surfaces.size(); i++) {
	            vector<Surface> s;
		        s.push_back(this->surfaces[i]);
		        getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
		        
	        }
			for (i = 0; i < this->surfaces.size(); i++) {
		        for (j = 0; j < this->surfaces.size(); j++) {
					if (i == j) {
					    continue;
					}
	                vector<Surface> s;
		            s.push_back(this->surfaces[i]);
			        s.push_back(this->surfaces[j]);
		            getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
					
		        }
	        }
			for (i = 0; i < this->surfaces.size(); i++) {
		        for (j = 0; j < this->surfaces.size(); j++) {
					if (i == j) {
						continue;
					}
					for (unsigned k = 0; k < this->surfaces.size(); k++) {
						if (j == k) {
							continue;
						}
	                    vector<Surface> s;
		                s.push_back(this->surfaces[i]);
			            s.push_back(this->surfaces[j]);
						s.push_back(this->surfaces[k]);
		                getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
		                
					}
		        }
	        }
			break;
		default:
			for (i = 0; i < this->surfaces.size(); i++) {
	            vector<Surface> s;
		        s.push_back(this->surfaces[i]);
                getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
		        
	        }
			break;
	}
	// TODO:return 
	return true;
}
bool Model::calculateStrongestPaths() {
	this->calculateLOSPath();
	this->calculateReflectPaths();
	vector<Path> paths = this->strongestPaths;
	if (this->strongestPaths.size() > NUM_OF_PATHS) {
		this->strongestPaths.erase(strongestPaths.begin() + NUM_OF_PATHS, strongestPaths.end());
	} 
	// TODO:return 
	return true;
};
void Model::insertPath(const Path& newPath) {
	if (strongestPaths.empty()) { 
		strongestPaths.push_back(newPath);
	} else {
		vector<Path>::reverse_iterator rIter;
		for (rIter = strongestPaths.rbegin(); rIter < strongestPaths.rend(); ++rIter) {
			if (rIter->getTotalLength() < newPath.getTotalLength()) {
				strongestPaths.insert(rIter.base(), newPath);
				break;
			}
		}		
	}
};
bool Model::calculateImpulseResponse(double t) {
	vector<Path>::iterator iterPath = this->strongestPaths.begin();
	double baseTao = iterPath->getDelayTime();
	for (; iterPath < this->strongestPaths.end(); iterPath++) {
		//iterPath->calculateIr();
		
		double tao = iterPath->getDelayTime();
		double tt = t - (tao - baseTao);
		// 两倍波长
		//double time = 1 / F * 200000000000000000000 + (tao - baseTao);
		//if (tt >= 0 && time >= tt) {
		if (tt >= 0) {
			// TODO:not sure
			double phaseShift = 2 * PI / iterPath->getWaveLength() * C * tt;
			phaseShift += 2 * PI / iterPath->getWaveLength() * iterPath->getVDoppler() * tt;
			//double vInitPhase = iterPath->getVInitPhase();
			//double hInitPhase = iterPath->getHInitPhase();
			iterPath->setVPhaseShift(phaseShift);
			iterPath->setHPhaseShift(phaseShift);
		} else {
			iterPath->setVPhaseShift(PI / 2);
			iterPath->setHPhaseShift(PI / 2);
		   
		}
		iterPath->calculateIr();
	}
	// TODO: return
	return true;
}
// TODO:unsed, solved in getReflectPath()
bool Model::calculateAmplitude() {
	
	vector<Path>::iterator iterPaths = this->strongestPaths.begin();
	for (unsigned i = 0; i < this->strongestPaths.size(); i++) {	

		for(unsigned j = 1; j < this->strongestPaths[i].getReflections().size(); j++) {
			Reflection r1 = this->strongestPaths[i].getReflections()[j - 1];
			Reflection r2 = this->strongestPaths[i].getReflections()[j];
			double hAmplitude = r1.getH() * r2.getH() * r1.getHAmplitude() * r2.getAmplitudeFadeH();
			double vAmplitude = r1.getV() * r2.getV() * r1.getVAmplitude() * r2.getAmplitudeFadeV();
			this->strongestPaths[i].getReflections()[j].setHAmplitude(hAmplitude);
			this->strongestPaths[i].getReflections()[j].setVAmplitude(vAmplitude);
			//this->strongestPaths[i].getReflections()[j].calculateAmplitudeFadeH();
			//this->strongestPaths[i].getReflections()[j].calculateAmplitudeFadeV();
		}
	}
	return true;
}
vector<Path> Model::getStrongestPaths() const{
	return this->strongestPaths;
}

void Model::displayPathIR() {
	unsigned i;
	for(i = 0; i < this->strongestPaths.size(); i++) {	
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		Path path = this->strongestPaths.at(i);
		path.displayVir();
		
	}
	cout<<endl;
	for(i = 0; i < this->strongestPaths.size(); i++) {
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		Path path = this->strongestPaths.at(i);
		path.displayHir();
		
	}
	cout<<endl;
}

void Model::displayPathVIR() {
	for(unsigned i = 0; i < this->strongestPaths.size(); i++) {	
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		Path path = this->strongestPaths.at(i);
		path.displayVir();
	}
	cout<<endl;
}
void Model::displayPathHIR() {
	for(unsigned i = 0; i < this->strongestPaths.size(); i++) {	
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		Path path = this->strongestPaths.at(i);
		path.displayHir();
		
	}
	cout<<endl;
}
void Model::displayPath() {
	cout<<"num of paths:"<<this->strongestPaths.size()<<endl;
	for(unsigned i = 0; i < this->strongestPaths.size(); i++) {
		Path path = this->strongestPaths.at(i);
		cout<<i+1<<"th path:"<<endl;
		cout.setf(ios::fixed);
		cout.precision(10);
		
	    cout<<"  total length:"<<this->strongestPaths.at(i).getTotalLength()<<endl;
		cout<<"  delay time:"<<this->strongestPaths.at(i).getDelayTime()<<endl;
		cout<<"  frequency:"<<path.getFrequency()<<endl;
		cout<<"  frequency shift:"<<path.getFDopplerShift()<<endl;
		cout<<"  wavelength:"<<path.getWaveLength()<<endl;
		
		cout.unsetf(ios_base::fixed);

		Direction tDirection = path.getReflections().begin()->getDirection();
		Direction rDirection = path.getReflections().at(path.getNumOfReflect()).getDirection();
		cout<<"  transmit direction:("<<tDirection.i<<","<<tDirection.j<<","<<tDirection.k<<")"<<endl;
		cout<<"  receive  direction:("<<rDirection.i<<","<<rDirection.j<<","<<rDirection.k<<")"<<endl;
		cout<<"  h:("<<path.getH().i<<","<<path.getH().j<<","<<path.getH().k<<")"<<path.getHAmplitude()<<endl;
		cout<<"  v:("<<path.getV().i<<","<<path.getV().j<<","<<path.getV().k<<")"<<path.getVAmplitude()<<endl;
		cout<<"  h shift:"<<path.getHPhaseShift()<<endl;
		cout<<"  v shift:"<<path.getVPhaseShift()<<endl;

		path.displayIR();

		cout<<"  num of reflect :"<<this->strongestPaths.at(i).getNumOfReflect()<<endl;
		cout<<"  reflections:"<<"num:"<<this->strongestPaths.at(i).getReflections().size()<<endl;
		
		for(unsigned j = 0; j <= this->strongestPaths.at(i).getReflections().size()-1 ; j++) {
			cout<<"   "<<(j + 1)<<"th reflection:"<<endl;
			Reflection r = this->strongestPaths.at(i).getReflections().at(j);
		    Direction d = r.getDirection();
			Point p = r.getReflectPoint();
			Surface s = r.getSurface();
			Direction nVector = s.getNVector();
			double length = r.getLength();
			cout<<"    direction: ("<<d.i<<","<<d.j<<","<<d.k<<")"<<endl;
			cout<<"    reflect point:("<<p.x<<","<<p.y<<","<<p.z<<")"<<endl;

			if (j != 0) {
				cout<<"    n:("<<nVector.i<<","<<nVector.j<<","<<nVector.k<<")"<<endl;
			}
			cout<<"    h:("<<r.getH().i<<","<<r.getH().j<<","<<r.getH().k<<")"<<r.getHAmplitude()<<endl;
			cout<<"    v:("<<r.getV().i<<","<<r.getV().j<<","<<r.getV().k<<")"<<r.getVAmplitude()<<endl;
			cout<<"    h fade:"<<r.getAmplitudeFadeH()<<endl;
			cout<<"    v fade:"<<r.getAmplitudeFadeV()<<endl;
			cout<<"    reflect angle:"<<r.getReflectAngle()<<endl;
			cout<<"    length:"<<length<<endl;
		}
		
	}
}
// TODO:unsed
void Model::displayIR() {
}
void Model::displayModel() {
	cout<<"Tx:"<<endl;
	this->transmitter.displayVehichle();
	cout<<"Rx:"<<endl;
	this->receiver.displayVehichle();
    cout<<"Surfaces:"<<this->surfaces.size()<<endl;
	for (unsigned i = 0; i < this->surfaces.size(); i++) {
		cout<<"  "<<(i + 1)<<"th surface:"<<endl;
		this->surfaces[i].display(4);
	}
	cout<<"transmit antennas:"<<this->tAntennas.size()<<endl;
	for (unsigned j = 0; j < this->tAntennas.size(); j++) {
		cout<<"  "<<(j + 1)<<"th atenna element:"<<endl;
		this->tAntennas[j].display(4);
	}
} 
void Model::displayModelExcel() {
	cout<<"Input"<<endl;

	cout<<"Vehicles\t"<<"location\t"<<"direction\t"<<"velocity\t"<<endl;
	cout<<"Tx\t";
	this->transmitter.displayVehichleExcel();
	cout<<"Rx\t";
	this->receiver.displayVehichleExcel();

    cout<<"Surfaces\t"<<"p0\t"<<"p1\t"<<"material\t"<<"refractive index\t"<<endl;
	for (unsigned i = 0; i < this->surfaces.size(); i++) {
		cout<<"s"<<(i + 1)<<"\t";
		this->surfaces[i].displayExcel();
	}

	cout<<"transmit antennas\t"<<"direction\t"<<"polarization\t"<<"relative location\t"<<"amplitude(power related)\t"<<endl;
	for (i = 0; i < this->tAntennas.size(); i++) {
		cout<<"ta"<<(i + 1)<<"\t";
		this->tAntennas[i].displayExcel();
	}
	cout<<"recieve antennas\t"<<"direction\t"<<"polarization\t"<<"relative location\t"<<"amplitude(power related)\t"<<endl;
	for (i = 0; i < this->rAntennas.size(); i++) {
		cout<<"ra"<<(i + 1)<<"\t";
		this->rAntennas[i].displayExcel();
	}
} 
void Model::displayMaxDelay() {
	cout<<"Vehicles\t"<<"location\t"<<"direction\t"<<"velocity\t"<<endl;
	cout<<"Tx\t";
	this->transmitter.displayVehichleExcel();
	cout<<"Rx\t";
	this->receiver.displayVehichleExcel();

    cout<<"Surfaces\t"<<"p0\t"<<"p1\t"<<"material\t"<<"refractive index\t"<<endl;
	for (unsigned i = 0; i < this->surfaces.size(); i++) {
		cout<<"s"<<(i + 1)<<"\t";
		this->surfaces[i].displayExcel();
	}
	cout<<"max delay:\t";
	int size = this->strongestPaths.size();
	double firstDelay = this->strongestPaths[0].getDelayTime();
	double lastDelay = this->strongestPaths[size - 1].getDelayTime();
	double maxDelay = lastDelay - firstDelay ;
	cout<<maxDelay<<"s\t";
	cout<<endl;
}

double Reflection::getLength() const {
	return this->length;
};
Point Reflection::getReflectPoint() const {
	return this->reflectPoint;
};
Direction Reflection::getH() const {
	return this->h; 
}
Direction Reflection::getV() const {
	return this->v; 
}
Surface Reflection::getSurface() const {
	return this->surface;
}
Reflection::Reflection(double length, 
		       const Point& reflectPoint, 
			   const Point& startPoint, 
			   const Point& endPoint, 
			   const Surface& surface, 
			   const Direction& direction):
	           length(length),
			   reflectPoint(reflectPoint),
			   startPoint(startPoint),
			   endPoint(endPoint),
			   surface(surface),
			   direction(direction) {
	this->v = getScalarProduct(surface.getNVector(), direction);
	this->h = getScalarProduct(direction, this->v);
	this->reflectAngle = calculateReflectAngle(surface.getNVector(), direction);
	    this->vPhaseShift = 0;
	    this->hPhaseShift = 0;
}
Reflection::Reflection(double length, 
	       const Point& reflectPoint, 
		   const Point& endPoint, 
		   const Direction& direction):
           length(length),
		   reflectPoint(reflectPoint),
		   startPoint(startPoint),
		   endPoint(endPoint),
		   surface(surface),
		   direction(direction) {
			   this->amplitudeFadeV = 1;
			   this->amplitudeFadeH = 1;
			   this->vPhaseShift = 0;
			   this->hPhaseShift = 0;
}
bool Reflection::calculateVH() {
	this->v = getScalarProduct(this->direction, this->surface.getNVector());
	this->h = getScalarProduct(this->direction, this->v);
	return true;
}
bool Reflection::calculateAmplitudeFadeV() {
	double n = this->surface.getMaterial().getN();
	double x = this->reflectAngle;
	double b = sqrt(pow(n, 2) - pow(sin(x), 2));
	double a = cos(x);
	this->amplitudeFadeV = (a - b) / (a + b);
	return false;
}
bool Reflection::calculateAmplitudeFadeH() {
	double n = this->surface.getMaterial().getN();
	double x = this->reflectAngle;
	double b = sqrt(n * n - sin(x) * sin(x));
	double a = cos(x) * pow(n, 2);
	this->amplitudeFadeH =  (a - b) / (a + b);
	return true;
}
void Reflection::init() {
	this->calculateVH();
	this->calculateAmplitudeFadeH();
	this->calculateAmplitudeFadeV();
}
Direction Reflection::getDirection() const {
	return this->direction;
};