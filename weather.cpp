#include <time.h>
#include "weather.h"

void Storm::init() {
	this->calculateDc();
	this->calculateFadeRate();
	this->calculateShiftRate();
}
void Storm::calculateDc() {
	// 干沙的介电常数
	double im_s = 1.8 / this->f * pow(10, (2 * log10(this->f) - 2.8));
    dc_s = new ComplexNumber(3, im_s);
	// 水的介电常数
	double theta = 300 / this->t;
	double ep0 = 77.66 + 103.3 * (theta - 1);
	double ep1 = 5.48;
	double ep2 = 3.51;
	double fp = 20.09 - 142.4 * (theta - 1) + 294 * pow((theta - 1), 2);
	double fs = 590 - 1500 * (theta - 1);
    ComplexNumber c0(ep0 - ep1, 0);
    ComplexNumber c1(ep1 - ep2, 0);
    ComplexNumber c2(ep2, 0);
    ComplexNumber c0_1(1, this->f / fp);
    ComplexNumber c1_1(1, this->f / fs);
	dc_w = &(c0 / c0_1 + c1 / c1_1 + c2);
	// 复合介电常数
	dc_sw = &(*dc_s * ((*dc_w - *dc_s) * 3 * v / (*dc_w + *dc_s * 2) / ( - (*dc_w - *dc_s) * v / (*dc_w + *dc_s *2) + 1) + 1));
}
void Storm::calculateFadeRate() {
	this->fadeRate = -0.4288e6 * 
		(dc_sw->Im() / (pow(dc_sw->Re() + 2, 2) + pow(dc_sw->Im(), 2))) * f * n * exp(3 * e + 4.5 * m * m);
}
void Storm::calculateShiftRate() {
	this->shiftRate = 26.2 * ((dc_sw->Re() - 1) * (dc_sw->Re() + 2) + pow(dc_sw->Im(), 2)) 
		/ (pow(dc_sw->Re(), 2) + pow(dc_sw->Im(), 2)) 
		* n * exp(3 * e + 4.5 * m * m);
}
void Storm::display() {
	cout<<"沙尘天气参数"<<endl;
    cout<<"沙尘密度（1/立方米）\t"<<this->n<<endl;
    cout<<"气温（摄氏度）\t"<<this->t<<endl;
    cout<<"沙粒含水百分比\t"<<this->v<<endl;
    cout<<"lnD的期望（D为沙粒直径）\t"<<this->e<<endl;
    cout<<"lnD的标准差（D为沙粒直径）\t"<<this->m<<endl;
	cout<<"衰减率（dB/km）：\t"<<this->fadeRate<<endl;
	cout<<"相移率（°/km）：\t"<<this->shiftRate<<endl;
}
double Weather::fadePercent(double len) {
	double fadeDB = this->fadeRate * (len / 1000);
    return dBtoPercent(fadeDB);
}
double Storm::shiftRad(double len) {
    double shift = this->shiftRate * (len / 1000) / 180 * PI;
	return shift;
}
void Rain::calculateFadeRate() {
	this->k = (kh + kv + (kh - kv) * pow(cos(a_ele), 2) * cos(2 * a_tilt)) / 2;
	this->a = (kh * ah + kv * av + (kh * ah - kv * av) * pow(cos(a_ele), 2) * cos(2 * a_tilt)) / (2 * k);
	this->fadeRate = -k * pow(r, a);
}
void Rain::init() {
    this->kh = 4.0848e-5 * pow(this->f, (1.4550 + 0.3952 * log(this->f)));
    this->kv = 3.7332e-5 * pow(this->f, (1.4169 + 0.4067 * log(this->f)));
    this->ah = 0.8424 + 0.3151 / (pow((log(this->f) - 2.0462), 2) + 0.6394);
    this->av = 0.8158 + 0.2850 / (pow((log(this->f) - 2.0775), 2) + 0.5694);
	this->calculateFadeRate();
}
void Rain::resetAnglesFadeRate(double a_ele, double a_tilt) {
	this->a_ele = a_ele;
	this->a_tilt = a_tilt;
	this->calculateFadeRate();
}
void Rain::display() {
	cout<<"降雨天气参数"<<endl;
    cout<<"降雨量（mm/h）\t"<<this->r<<endl;
}
/*
生成初始场景中雨层的雨滴
将场景（长方体）划分成单位立方体，每个立方体只能容纳一个雨滴
根据雨滴分布（雨滴密度）计算雨层中一共要布设的雨滴总数m
将立方体标号，立方体总数n=a*b*c
从1-n中随机选出m个数，换算成雨滴位置
根据配置生成各雨滴
*/
void Rain2::initRainDrops() {
	this->amount = this->config.length * this->config.width * this->config.height * this->config.density;
	long m = this->amount;
    double unitL = this->config.rRange[1] / 1000; // 立方体长度
	long a = (long)this->config.length / unitL; 
	long b = (long)this->config.width / unitL; 
	long c = (long)this->config.height / unitL; 
	long n = a * b * c;
	srand(time(NULL));
	for (long i = 0L; i < n; i++) {
		//此处rand()%(N - 1)出现每一个小于(N - i)的数的概率是一样的
		if ((rand()%(n - i)) < m) {  //被取到，m值减 1 ，输出结果 i 
			m--;
		}
	}
}