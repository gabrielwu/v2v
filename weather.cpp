#include <time.h>
#include "weather.h"

void Storm::init() {
	this->calculateDc();
	this->calculateFadeRate();
	this->calculateShiftRate();
}
void Storm::calculateDc() {
	// ��ɳ�Ľ�糣��
	double im_s = 1.8 / this->f * pow(10, (2 * log10(this->f) - 2.8));
    dc_s = new ComplexNumber(3, im_s);
	// ˮ�Ľ�糣��
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
	// ���Ͻ�糣��
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
	cout<<"ɳ����������"<<endl;
    cout<<"ɳ���ܶȣ�1/�����ף�\t"<<this->n<<endl;
    cout<<"���£����϶ȣ�\t"<<this->t<<endl;
    cout<<"ɳ����ˮ�ٷֱ�\t"<<this->v<<endl;
    cout<<"lnD��������DΪɳ��ֱ����\t"<<this->e<<endl;
    cout<<"lnD�ı�׼�DΪɳ��ֱ����\t"<<this->m<<endl;
	cout<<"˥���ʣ�dB/km����\t"<<this->fadeRate<<endl;
	cout<<"�����ʣ���/km����\t"<<this->shiftRate<<endl;
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
	cout<<"������������"<<endl;
    cout<<"��������mm/h��\t"<<this->r<<endl;
}
/*
���ɳ�ʼ�������������
�������������壩���ֳɵ�λ�����壬ÿ��������ֻ������һ�����
������ηֲ�������ܶȣ����������һ��Ҫ������������m
���������ţ�����������n=a*b*c
��1-n�����ѡ��m��������������λ��
�����������ɸ����
*/
void Rain2::initRainDrops() {
	this->amount = this->config.length * this->config.width * this->config.height * this->config.density;
	long m = this->amount;
    double unitL = this->config.rRange[1] / 1000; // �����峤��
	long a = (long)this->config.length / unitL; 
	long b = (long)this->config.width / unitL; 
	long c = (long)this->config.height / unitL; 
	long n = a * b * c;
	srand(time(NULL));
	for (long i = 0L; i < n; i++) {
		//�˴�rand()%(N - 1)����ÿһ��С��(N - i)�����ĸ�����һ����
		if ((rand()%(n - i)) < m) {  //��ȡ����mֵ�� 1 �������� i 
			m--;
		}
	}
}