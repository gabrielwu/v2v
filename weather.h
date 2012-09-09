#include <list>
#ifndef BASE_H 
#define BASE_H 
#include "base.h"
#endif 


using namespace std;

class Weather {
protected:
	double fadeRate; // 衰减率
	double f; // 频率
public:
	Weather(double f):f(f) {};
	//virtual ~Geometry() = 0;
	virtual void init() = 0;
	double fadePercent(double len); // 衰落百分比，dB转化为比值
};
// 沙尘
class Storm: public Weather {
private:
	int n; // 沙尘密度
	double t; // 温度
	double v; // 沙粒水分百分比
	double e; // lnD的期望，D为沙粒直径
	double m; // lnD的标准差

	ComplexNumber* dc_s; // 干沙介电常数
	ComplexNumber* dc_w; // 水介电常数
	ComplexNumber* dc_sw; // 湿沙介电常数
	
	double shiftRate; // 相移率

	void calculateDc();
	void calculateFadeRate();
	void calculateShiftRate();
public:
	Storm(double f, int n, double t, double v, double e, double m):Weather(f), n(n),t(t),v(v),e(e),m(m){
	    this->dc_s = NULL;
	    this->dc_w = NULL;
	    this->dc_sw = NULL;
	};
	void init();
	double shiftRad(double len); // 相移，角度转为弧度
	void display();
};
// 降雨
class Rain: public Weather {
private:
	double r; // 降雨量 mm/h
	double k;
	double a;
	double kv; // 垂直极化时的k 
	double kh; // 水平极化时的k
	double av; // 垂直极化时的a
	double ah; // 水平极化时的a
	double a_ele; // 入射波仰角
	double a_tilt; // 相对于水平的极化倾角

	void calculateFadeRate();
public:
	Rain(double f, double r, double a_ele=0, double a_tilt=0):Weather(f),r(r),a_ele(a_ele),a_tilt(a_tilt){};
	void init();   
	void resetAnglesFadeRate(double a_ele, double a_tilt);
	void display();
};
class RainDrop {
private:
	Point p;
	double r; // 半径，mm
	Direction d;
	double v;
public:
	RainDrop(Point p = Point(0,0,0), double r = 1,Direction d = Direction(0,0,-1), double v = 10):p(p),r(r),d(d),v(v){};
};
class Rain2Config {
	friend class Rain2;
private:
	double rRange[2]; // 雨滴半径范围
	double vRange[2]; // 雨滴速度范围
	Direction dWind; // 风向
	double vWind; // 风速
	double length; // 雨层长度，下同
	double width;
	double height;
	int density; // 雨层密度，1立方米内雨滴数
public:
	Rain2Config(double r[2],
		double v[2],
		Direction d,
		double vW,
		double l, 
		double w, 
		double h,
		int density){
	    this->rRange[0] = r[0];
	    this->rRange[1] = r[1];
	    this->vRange[0] = v[0];
	    this->vRange[1] = v[1];
		this->dWind = d;
		this->vWind = vW;
		this->length = l;
		this->width = w;
		this->height = h;
		this->density = density;
	};
};
class Rain2 {
private:
	Rain2Config config;;
	list<RainDrop> rainDrops;
	long amount; // 雨滴总数
public:
	Rain2(Rain2Config c):config(c){};
	void initRainDrops();
};
