#include <iostream>
#include <vector>
#include "math.h"
using namespace std;
// base components
const double C = 300000000;
const double F = 5900000000;
const double PI = 3.1415926;
const double E = 2.718281828;
const double WAVE_LENGTH = C / F;
const int NUM_OF_PATHS = 7;
const int NUM_OF_REFLECTS = 3;
const int NUM_OF_SCATTER = 1;
class Surface;

double dBtoPercent(double dBvalue);
class ComplexNumber {
	friend class ComplexNumber;
private:
	double im,re;
public:
	ComplexNumber(double re, double im):re(re), im(im) {};
	double Re() {
	    return this->re;
	};
	double Im() {
	    return this->im;
	};
    ComplexNumber operator +(ComplexNumber& c);
    ComplexNumber operator -(ComplexNumber& c);
    ComplexNumber operator -();
    ComplexNumber operator *(ComplexNumber& c);
    ComplexNumber operator /(ComplexNumber& c);
    ComplexNumber operator +(double c);
    ComplexNumber operator -(double c);
    ComplexNumber operator *(double c);
    ComplexNumber operator /(double c);
};
// ��
class Point {
	friend class Surface;
	friend class Direction;
public:
	double x,y,z;
	Point(double x, double y, double z):x(x), y(y), z(z) {};
	Point():x(0),y(0),z(0){};
	Direction operator +(Point& p);
	Point operator +(Direction& d);
	double operator *(Direction& d);
	Point operator *(double m);
	Point operator /(double m);
	Direction operator -(Point& p);
	Direction operator -(const Point& p);
	Point operator -(const Direction& p);
	bool operator>(Point& p);
	bool operator<(Point& p);
	
	double calculateD(Direction& d);
    Point getSymmetricPoint (const Surface& s); 

	void display() {
		cout<<"("<<this->x<<","<<this->y<<","<<this->z<<")"<<endl;
	}
	void displayExcel() {
		cout<<"("<<this->x<<","<<this->y<<","<<this->z<<")\t";
	}
};
// ����
class Direction {
	friend class Surface;
	friend class Point;    
public:
	double i,j,k;
	Direction(double i, double j, double k):i(i), j(j), k(k) {};
	Direction():i(0),j(0),k(0){};
	Direction operator +(Direction& d);
	Direction operator +=(Direction& d);
	double operator *(Direction& d);
	double operator *(Point& p);
	double operator *(const Point& p);
	Direction operator *(double module);
	Direction operator *=(double module);
	Direction operator ^(Direction& d);
	Direction operator -(Direction& d);
	Direction operator -();
	bool operator ==(Direction& d);
	double getModule();
	Direction getUnitDirection();
	Direction getSymmDirect(const Surface& s);
	Direction getRelDirectOnReflect(const vector<Surface>& surfaces);
	void display() {
		cout<<"("<<this->i<<","<<this->j<<","<<this->k<<")"<<endl;
	}	
	void displayExcel() {
		cout<<"("<<this->i<<","<<this->j<<","<<this->k<<")\t";
	}
};

// ����
class Antenna {
	friend class Model;
private:
    Direction direction;
	Direction vDirection;
	Direction hDirection;
	Direction relativePosition;
	Direction amplitudeDirection;
	Direction h;
	Direction v;
	double amplitude;
public:
	Antenna(Direction direction, 
		    Direction relativePosition, 
			Direction amplitudeDirection, 
			double amplitude = 0):
	  direction(direction), 
	  relativePosition(relativePosition), 
	  amplitudeDirection(amplitudeDirection), 
	  amplitude(amplitude) {
	  };
	Antenna(Direction direction, 
		    Direction relativePosition, 
			Direction vDirection, 
			Direction hDirection,
			double amplitude = 0):
	  direction(direction), 
	  relativePosition(relativePosition), 
	  vDirection(vDirection), 
	  hDirection(hDirection),
	  amplitude(amplitude){};
	// ��ȡ���߷���
	Direction getDirection() const;
	// ��ȡ����������꣨������������ߣ�
	Direction getRelativePosition() const;	
	// ��ȡ�������
	Direction getAmplitudeDirection() const;
	// ��ȡ�����С
	double getAmplitude() const;
	// ��ȡ��ֱ��������
	Direction getVDirection() const {
		return this->vDirection;
	};
	// ��ȡˮƽ��������
	Direction getHDirection() const {
		return this->hDirection;
	};
	// ��ʾ������Ϣ
	void display(int space = 0);
	// ��ʾ������Ϣexcel
	void displayExcel();
};
// ����
class Material {
	friend class Surface;
private:
	// ��������ڿ���������ϵ��
	double n;
	double BrewsterAngle;
	string name;
public:
	Material() {
		this->n = 0;
		this->name = "";
		this->BrewsterAngle = 0;
	}
	Material(double n, string name = ""):n(n), name(name) {
	    BrewsterAngle = atan(n);
	};
	double getN() {  
	    return this->n;
	};
	double getBrewsterAngle() {
		return this->BrewsterAngle;
	};
	void display() {
		cout<<"specific refraction:"<<this->n<<endl;
	};
	void displayExcel() {
		cout<<this->name.c_str()<<"\t";
		cout<<this->n<<"\t";
	};
};
// ƽ����
class Surface {
	friend class Model;
	friend class Reflection;
private:
    // ƽ��ĵ���
	int pointsNum;
	// ƽ�涨λ�㣬����Ϊ���Ϻ�����
    Point p0, p1;
	// ��бƽ�棬����������,���º�����
	Point p2, p3;
    // ���ڱ�ʾƽ�淽��ax+by+cz+d=0
	double a,b,c,d; 
	// ƽ�淨����
	Direction nVector;
	// ���϶��󣬶������ȶ
    Material material;  
	// ����ͻ�����߶�
	double maxProtuberH;
	// ����߶ȱ�׼��
	double protuberHStandDeviat;
	// ������״ƽ��
	//vector<Point> points;
public:
	Surface(const Point& p0, 
		    const Point& p1, 
			const Material& material = Material(), 
			const Direction& nVector = Direction(),
			double mh = 0,
			double phsd = 0):
	    p0(p0),p1(p1),material(material),nVector(nVector),maxProtuberH(mh),protuberHStandDeviat(phsd){
		        //vector<Point> points;
				//this->points = points;
				Point p2(p0.x, p0.y, p1.z);
				Point p3(p1.x, p1.y, p0.z);
				this->p2 = p2;
				this->p3 = p3;
				this->pointsNum = 4;
	};
    /*Surface(vector<Point> points, 
			const Material& material = Material(), 
			const Direction& nVector = Direction()):points(points),material(material),nVector(nVector){
	};*/
	Surface(const Point& p0, 
		    const Point& p1, 
			const Point& p2,
			const Point& p3,
			const Material& material, 
			const Direction& nVector = Direction(),
			double mh = 0,
			double phsd = 0):
	    p0(p0),p1(p1),material(material),nVector(nVector),maxProtuberH(mh),protuberHStandDeviat(phsd){
				this->pointsNum = 4;
		        //vector<Point> points;
				//this->points = points;
	};
	Surface(const Point& p0, 
		    const Point& p1, 
			const Point& p2,
			const Material& material, 
			const Direction& nVector = Direction(),
			double mh = 0,
			double phsd = 0):
	    p0(p0),p1(p1),material(material),nVector(nVector),maxProtuberH(mh),protuberHStandDeviat(phsd){
				this->pointsNum = 3;
		        //vector<Point> points;
				//this->points = points;
	};
	void setMaterial(const Material& m) {
		this->material = m;
	};
	// ��ʼ������
	void init();
	// ����ƽ�淽��
    void calculateEquation(); 
	// ���㷨����
	void calculateVector();
	// ��ǰ���Ƿ�����������֮��
	bool isOutLine(Point& p0, Point& p1);
	double getA() const;
	double getB() const;
	double getC() const;
	double getD() const;
	// �жϵ�p�Ƿ���ƽ�淶Χ
	bool isPointOn(const Point& p) const;
	// �����������߹��ڵ�ǰƽ��Ľ��㣨ƽ�淽�̣�
	Point calculateIntersectPoint(Point& p0, Point& p1);
	// ��������������ƽ�淽�̽����Ƿ�������
	bool isIntersectPointOn(Point& p0, Point& p1);
	// ��������������ƽ�淽�̽����Ƿ�ᴩ����(p0��p1�����ϳ���)
	bool isIntersectPointThrough(Point& p0, Point& p1);
	// �жϵ�p�Ƿ�������
	// ��÷�����
	Direction getNVector() const;
	// ��ȡ����
	Material getMaterial() const;
	// ��ʾƽ����Ϣ
	void display(int space = 0);
	// ��ʾƽ����Ϣ
	void displayExcel();
	Point getP0() const {
	    return this->p0;
	};
	Point getP1() const {
	    return this->p1;
	};
	Point getP2() const {
	    return this->p2;
	};
	Point getP3() const {
	    return this->p3;
	};
};
// ��ȡ��������
double getDistance(const Point& p0, const Point& p1);

// ��ȡ��������
double getDistanceByDirection(const Direction& d0, const Direction& d1);

// ��ȡ�������ߵ��е�
Point getCenterPoint(const Point& p0, const Point& p1);

// ��ȡ��p������s�ĶԳƵ�pn
// @s:�����鷴����
// @pn:�������
Point* getSymmetricPoint (const Surface& s, const Point& p); 

// ��ȡ����pa��pb���߹���ƽ��s�Ľ���p 
// @s:������ƽ��
// @pa:��ʼ�㣨ʵ��Ӧ����ӦΪĳ�����s�ĶԳƵ㣩
// @pb:��ֹ��
// return:���н��㣬���ؽ��㣨����������㣩Point����
Point* getReflectPoint(const Surface& s, const Point& pa, const Point& pb);

// ��÷������
// @s:�����鷴����
// @pt:�����
// @pr:���յ�
// return:���������������Reflecttion���󣻷��򷵻�null
Reflection* getReflection(const Surface& s, const Point& pt, const Point& pr);

// ��η����е�һ��
Reflection* getFirstReflection(const Point& reflectPoint, const Point& pr, const Antenna& a);


// ����ֱ����ƽ��Ľ���
// @dLine:ֱ������
// @nPlane:ƽ�淨����
// @pLine:��ֱ�ߵ�һ����
// @pPlane:��ƽ���һ����
Point* calculateIntersectPoint(Direction& dLine, Direction& nPlane, Point& pLine, Point& pPlane);

// ��ȡ��λ��������
// @d:��������
// return:��λ��������
Direction getUnitDirection(const Direction& d);

// �������������н�
double getAngleByVectors(const Direction& d0, const Direction& d1);
// �����ȡ�����
double calculateReflectAngle(const Direction& d0, const Direction& d1);
// �����������
Direction getScalarProduct(const Direction& d0, const Direction& d1);


// ���������Ӱ���µ�Ƶ��
double getDopplerFrequency(double vDoppler, double frequency, double v);
