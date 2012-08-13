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
// 点
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
// 方向
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

// 天线
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
	// 获取天线方向
	Direction getDirection() const;
	// 获取天线相对坐标（相对于中心天线）
	Direction getRelativePosition() const;	
	// 获取振幅方向
	Direction getAmplitudeDirection() const;
	// 获取振幅大小
	double getAmplitude() const;
	// 获取垂直极化方向
	Direction getVDirection() const {
		return this->vDirection;
	};
	// 获取水平极化方向
	Direction getHDirection() const {
		return this->hDirection;
	};
	// 显示天线信息
	void display(int space = 0);
	// 显示天线信息excel
	void displayExcel();
};
// 材料
class Material {
	friend class Surface;
private:
	// 材料相对于空气的折射系数
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
// 平面类
class Surface {
	friend class Model;
	friend class Reflection;
private:
    // 平面的点数
	int pointsNum;
	// 平面定位点，初定为左上和右下
    Point p0, p1;
	// 倾斜平面，另外两个点,左下和右上
	Point p2, p3;
    // 用于表示平面方程ax+by+cz+d=0
	double a,b,c,d; 
	// 平面法向量
	Direction nVector;
	// 材料对象，定义待商榷
    Material material;  
	// 表面突起最大高度
	double maxProtuberH;
	// 表面高度标准差
	double protuberHStandDeviat;
	// 任意形状平面
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
	// 初始化函数
	void init();
	// 计算平面方程
    void calculateEquation(); 
	// 计算法向量
	void calculateVector();
	// 当前面是否在两点连线之外
	bool isOutLine(Point& p0, Point& p1);
	double getA() const;
	double getB() const;
	double getC() const;
	double getD() const;
	// 判断点p是否在平面范围
	bool isPointOn(const Point& p) const;
	// 计算连点连线关于当前平面的交点（平面方程）
	Point calculateIntersectPoint(Point& p0, Point& p1);
	// 计算连点连线与平面方程交点是否在面上
	bool isIntersectPointOn(Point& p0, Point& p1);
	// 计算连点连线与平面方程交点是否横穿面上(p0或p1在面上除外)
	bool isIntersectPointThrough(Point& p0, Point& p1);
	// 判断点p是否在两点
	// 获得法向量
	Direction getNVector() const;
	// 获取材料
	Material getMaterial() const;
	// 显示平面信息
	void display(int space = 0);
	// 显示平面信息
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
// 获取两点间距离
double getDistance(const Point& p0, const Point& p1);

// 获取两点间距离
double getDistanceByDirection(const Direction& d0, const Direction& d1);

// 获取两点连线的中点
Point getCenterPoint(const Point& p0, const Point& p1);

// 获取点p关于面s的对称点pn
// @s:待检验反射面
// @pn:待检验点
Point* getSymmetricPoint (const Surface& s, const Point& p); 

// 获取两点pa、pb连线关于平面s的交点p 
// @s:待检验平面
// @pa:起始点（实际应用中应为某点关于s的对称点）
// @pb:终止点
// return:若有交点，返回交点（反射点或入射点）Point对象
Point* getReflectPoint(const Surface& s, const Point& pa, const Point& pb);

// 获得反射对象
// @s:待检验反射面
// @pt:出射点
// @pr:接收点
// return:若反射成立，返回Reflecttion对象；否则返回null
Reflection* getReflection(const Surface& s, const Point& pt, const Point& pr);

// 多段反射中第一段
Reflection* getFirstReflection(const Point& reflectPoint, const Point& pr, const Antenna& a);


// 计算直线与平面的交点
// @dLine:直线向量
// @nPlane:平面法向量
// @pLine:过直线的一个点
// @pPlane:过平面的一个点
Point* calculateIntersectPoint(Direction& dLine, Direction& nPlane, Point& pLine, Point& pPlane);

// 获取单位方向向量
// @d:方向向量
// return:单位方向向量
Direction getUnitDirection(const Direction& d);

// 计算获得两向量夹角
double getAngleByVectors(const Direction& d0, const Direction& d1);
// 计算获取发射角
double calculateReflectAngle(const Direction& d0, const Direction& d1);
// 计算向量点积
Direction getScalarProduct(const Direction& d0, const Direction& d1);


// 计算多普勒影响下的频率
double getDopplerFrequency(double vDoppler, double frequency, double v);
