#include <list>
#ifndef BASE_H 
#define BASE_H 
#include "base.h"
#endif 


using namespace std;

class Weather {
protected:
	double fadeRate; // ˥����
	double f; // Ƶ��
public:
	Weather(double f):f(f) {};
	//virtual ~Geometry() = 0;
	virtual void init() = 0;
	double fadePercent(double len); // ˥��ٷֱȣ�dBת��Ϊ��ֵ
};
// ɳ��
class Storm: public Weather {
private:
	int n; // ɳ���ܶ�
	double t; // �¶�
	double v; // ɳ��ˮ�ְٷֱ�
	double e; // lnD��������DΪɳ��ֱ��
	double m; // lnD�ı�׼��

	ComplexNumber* dc_s; // ��ɳ��糣��
	ComplexNumber* dc_w; // ˮ��糣��
	ComplexNumber* dc_sw; // ʪɳ��糣��
	
	double shiftRate; // ������

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
	double shiftRad(double len); // ���ƣ��Ƕ�תΪ����
	void display();
};
// ����
class Rain: public Weather {
private:
	double r; // ������ mm/h
	double k;
	double a;
	double kv; // ��ֱ����ʱ��k 
	double kh; // ˮƽ����ʱ��k
	double av; // ��ֱ����ʱ��a
	double ah; // ˮƽ����ʱ��a
	double a_ele; // ���䲨����
	double a_tilt; // �����ˮƽ�ļ������

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
	double r; // �뾶��mm
	Direction d;
	double v;
public:
	RainDrop(Point p = Point(0,0,0), double r = 1,Direction d = Direction(0,0,-1), double v = 10):p(p),r(r),d(d),v(v){};
};
class Rain2Config {
	friend class Rain2;
private:
	double rRange[2]; // ��ΰ뾶��Χ
	double vRange[2]; // ����ٶȷ�Χ
	Direction dWind; // ����
	double vWind; // ����
	double length; // ��㳤�ȣ���ͬ
	double width;
	double height;
	int density; // ����ܶȣ�1�������������
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
	long amount; // �������
public:
	Rain2(Rain2Config c):config(c){};
	void initRainDrops();
};
