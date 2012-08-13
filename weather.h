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
public:
	Rain(double f, double r, double a_ele, double a_tilt):Weather(f),r(r),a_ele(a_ele),a_tilt(a_tilt){};
	void init();   
	void setAngles(double a_ele, double a_tilt) {
		this->a_ele = a_ele;
		this->a_tilt = a_tilt;
	};
};