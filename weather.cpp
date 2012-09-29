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

bool RainDrop::canMerge(RainDrop rd) {
    double dis = getDistance(this->p, rd.p);
	if((dis * 1000) / this->r > RAINDROP_MERGE_MULTIPLE_R) {
	    return false;
	} else {
	    return true;
	}
}
//���ɳ�ʼ�������������
//�������������壩���ֳɵ�λ�����壬ÿ��������ֻ������һ�����
//������ηֲ�������ܶȣ����������һ��Ҫ������������m
//���������ţ�����������n=a*b*c
//��1-n�����ѡ��m��������������λ��
//�����������ɸ����
//ע��1������ԭ���Ƿ�������

void Rain2::initRainDrops() {
	this->amount = this->config.length * this->config.width * this->config.height * this->config.density;
	long m = this->amount;
    this->unitL = this->config.rRange[1] / 1000; // �����峤��
	this->a = (long)this->config.width / unitL; 
	this->b = (long)this->config.length / unitL; 
	this->c = (long)this->config.height / unitL; 
	long n = a * b * c;
	srand(time(NULL));
	for (long i = 0L; i < n; i++) {
		//�˴�rand()%(N - 1)����ÿһ��С��(N - i)�����ĸ�����һ����
		if ((rand()%(n - i)) < m) {  //��ȡ����mֵ�� 1 ����α��i 
			m--;
			this->addOneRainDrop(i);
		}
	}
}
//ע��1������ԭ���Ƿ�������
void Rain2::addOneRainDrop(long i) {
	long iab = i % (a * b);
	long iaba = iab % a;
	double z = (i / (a * b)) * unitL + 0.5 * unitL;
	// TODO:���߸߶ȣ�
	double y = (iab / a) * unitL + 0.5 * unitL; 	
	double x = iaba * unitL + 0.5 * unitL - 0.5 * this->config.width; // ע��1
	Point p(x, y, z);
	double r = randomDouble2(this->config.rRange);
	Direction vd = Direction(0, 0, -1) * randomDouble2(this->config.vRange) + this->config.dWind * this->config.vWind;
	Direction d = vd.getUnitDirection();
	double v = vd.getModule();
	RainDrop drop(p, r, d, v);
	this->rainDrops.push_back(drop);
}
void Rain2::mergeRainDrops() {
	list<RainDrop> rs = this->rainDrops;
	list<RainDrop>::iterator iter = rs.begin();
	while (rs.size() != 0) {
		RainDrop rd = rs.front();
		list<RainDrop> rdTemp;
		rdTemp.push_back(rd);
		rs.pop_front();
		for (iter = rs.begin(); iter != rs.end(); iter++) {
			if (iter->canMerge(rd)) {
		        rdTemp.push_back(*iter);
			    iter = rs.erase(iter);
			}
		}
		MergedRainDrop mrd(rdTemp);
		mrd.init();
		this->mergedRainDrops.push_back(mrd);
	}
}
void Rain2::traceRainDrops(double t) {
	if (t > 0) {
		// TODO
	}
}
void Rain2Config::display() {
	cout<<"����2����"<<endl;
	cout<<"��ΰ뾶��Χ(mm)\t"<<rRange[0]<<","<<rRange[1]<<endl;
	cout<<"����ٶȷ�Χ(m/s)\t"<<vRange[0]<<","<<vRange[1]<<endl;
	cout<<"��㳤��\t"<<length<<endl;
	cout<<"�����\t"<<width<<endl;
	cout<<"���߶�\t"<<height<<endl;
	cout<<"����ܶȣ�1�������������\t"<<density<<endl;
}
void MergedRainDrop::init() {
	this->sCrossSection = 0;
    list<RainDrop>::iterator iter = this->rainDrops.begin();
	for (; iter != this->rainDrops.end(); iter++) {
	    this->sCrossSection += iter->sCrossSection;
	}
}
// �ϲ���� ��Ա����
bool Rain2Scatter::init() {
    this->direction[0] = (this->points[1] - this->points[0]).getUnitDirection();
	this->direction[1] = (this->points[2] - this->points[1]).getUnitDirection();
	this->length[0] = (this->points[1] - this->points[0]).getModule();
	this->length[1] = (this->points[2] - this->points[1]).getModule();
    this->calculateAmplitudeFade();
	return true;
}
bool Rain2Scatter::calculatePolarAmplitude(Direction& inV, Direction& inH) {
	Direction in = inH + inV;
	Direction polarV0 = (this->direction[0] ^ this->direction[1]).getUnitDirection();
	Direction polarH0 = (polarV0 ^ this->direction[0]).getUnitDirection();
	Direction polarV1 = polarV0;
	Direction polarH1 = (this->direction[1] ^ polarV1).getUnitDirection();
	double amplitudeV0 = in * polarV0;
	double amplitudeH0 = in * polarH0;
	if (amplitudeV0 < 0) {
		polarV0 = -polarV0;
	    polarV1 = -polarV1;
		amplitudeV0 = -amplitudeV0;
	}
	if (amplitudeH0 < 0) {
		polarH0 = -polarH0;
	    polarH1 = -polarH1;
		amplitudeH0 = -amplitudeH0;
	}
	double crossSectionSqrt = sqrt(this->mergedRainDrop.sCrossSection);
	double amplitudeV1 = amplitudeV0 * this->amplitudeFade[0] * crossSectionSqrt;
	double amplitudeH1 = amplitudeH0 * this->amplitudeFade[1] * crossSectionSqrt;
	this->setAmplitude(amplitudeV1, amplitudeH1);
	this->setPolarization(polarV1, polarH1);
    return true;
}
bool Rain2Scatter::calculatePolarAmplitude(Rain2Scatter& pre) {
	Direction inV = pre.polarization[0] * pre.amplitude[0];
	Direction inH = pre.polarization[1] * pre.amplitude[1];
	this->calculatePolarAmplitude(inV, inH);
    return true;
}
void Rain2Scatter::setAmplitude(double v, double h) {
    this->amplitude[0] = v;
	this->amplitude[1] = h;
}
void Rain2Scatter::setPolarization(const Direction& vp, const Direction& hp) {
	this->polarization[0] = vp;
	this->polarization[1] = hp;
}
bool Rain2Scatter::calculateAmplitudeFade() {
    // TODO::1 / ((4 * PI * this->totalLength) / this->waveLength);
	this->amplitudeFade[0] = 1 / ((4 * PI * this->length[0]) / WAVE_LENGTH);
	this->amplitudeFade[1] = 1 / ((4 * PI * this->length[0]) / WAVE_LENGTH);
	return true;
}

// �ϲ����ɢ��·�� ��Ա����
bool Rain2ScatterPath::calculate(Direction& relativeV, const vector<Antenna>& ras) {
	this->calculateDirection();
	this->calculateVDoppler(relativeV);
	this->calculateFDopplerShift();
	this->calculateFrequency();
	this->calculateWaveLength();
	this->calculateLength();
	this->calculateDelayTime();
	this->calculateAmplitudeFade();
	this->calculateAmplitude();
	this->calculatePolarization();
	this->calculateAmplitudeReceive(ras);
	return true;
}
bool Rain2ScatterPath::calculateDirection() {
    Rain2Scatter first = this->scatters.front();
	Rain2Scatter last = this->scatters.back();
	this->tDirection = first.direction[0];
	this->rDirection = first.direction[1];
	return true;
}
bool Rain2ScatterPath::calculateVDoppler(Direction& relativeV) {
    list<Rain2Scatter>::iterator iter = this->scatters.begin();
	this->vDoppler = relativeV * iter->direction[0];
	for (; iter != this->scatters.end(); iter++) {
        this->vDoppler += relativeV * iter->direction[1];
	}
	return true;
}
bool Rain2ScatterPath::calculateFDopplerShift() {
    this->fDopplerShift = (double)this->vDoppler / C * F;
	return true;
}
bool Rain2ScatterPath::calculateFrequency() {
    this->frequency = (double)this->vDoppler / C * F + F;
	return true;
}
bool Rain2ScatterPath::calculateWaveLength() {
    this->waveLength = WAVE_LENGTH;
	return true;
}
bool Rain2ScatterPath::calculateAmplitude() {
	Rain2Scatter last = this->scatters.back();
    this->amplitude[0] = last.amplitude[0];
	this->amplitude[1] = last.amplitude[1];
	return true;
}
bool Rain2ScatterPath::calculateAmplitudeFade() {
    list<Rain2Scatter>::iterator iter = this->scatters.begin();
	this->amplitudeFade = 1 / ((4 * PI * iter->length[0]) / this->waveLength);
	for (; iter != this->scatters.end(); iter++) {
        this->amplitudeFade *= 1 / ((4 * PI * iter->length[0]) / this->waveLength);
	}
	return true;
}
bool Rain2ScatterPath::calculateAmplitudeReceive(const vector<Antenna>& ras) {
	Antenna a = ras[0];
	Direction amplitude = this->polarization[0] * this->amplitude[0] + this->polarization[1] * this->amplitude[1];
	amplitude = amplitude * this->amplitudeFade;
	this->amplitudeReceive[0] = amplitude * a.getVDirection();
	this->amplitudeReceive[1] = amplitude * a.getHDirection();
	return true;
}
bool Rain2ScatterPath::calculateDelayTime() {
    this->delayTime = this->totalLength / (C + this->vDoppler);
	return true;
}
bool Rain2ScatterPath::calculateLength() {
	list<Rain2Scatter>::iterator iter = this->scatters.begin();
	this->totalLength = iter->length[0];
	for (; iter != this->scatters.end(); iter++) {
        this->totalLength += iter->length[1];
	}
	return true;
}
bool Rain2ScatterPath::calculatePhase(double v, double h) {
	this->phase[0] = v;
	this->phase[1] = h;
	return true;
}
bool Rain2ScatterPath::calculatePolarization() {
	Rain2Scatter last = this->scatters.back();
    this->polarization[0] = last.polarization[0];
	this->polarization[1] = last.polarization[1];
	return true;
}
bool Rain2ScatterPath::calculateIr() {
	this->ir[0] = cos(this->phase[0]) * this->amplitudeReceive[0];
	this->ir[1] = cos(this->phase[1]) * this->amplitudeReceive[1];
	return true;
}
void Rain2ScatterPath::displayIr() {
}
void Rain2ScatterPath::displayVir() {
	cout<<pow(this->ir[0], 2)<<"\t";
}
void Rain2ScatterPath::displayHir() {
	cout<<pow(this->ir[1], 2)<<"\t";
}
void Rain2ScatterPath::displayPathTotalLength() {
    cout<<this->totalLength<<"\t";
}
void Rain2ScatterPath::displayAmplitudeV() {
    cout<<this->amplitudeReceive[0]<<"\t";
}
void Rain2ScatterPath::displayAmplitudeH() {
    cout<<this->amplitudeReceive[1]<<"\t";
}

// �ϲ����ɢ��·���ϲ�ģ�� ��Ա����
bool Rain2ScatterPathMergehModel::mergePath() {
    
	return true;
}
void Rain2ScatterPathMergehModel::displaySampleIR() {
	int i;
	cout<<endl;
	cout<<"Vertical polarization IR"<<endl;
	for (i = 0; i < sampleCount; i++) {	    
		this->calculateImpulseResponse(i * sampleInterval);
		cout<<"t"<<(i + 1)<<"\t";
		this->displayVIR();
	}
		
	cout<<"Vertical polarization IR"<<endl;
	for (i = 0; i < sampleCount; i++) {	    
		this->calculateImpulseResponse(i * sampleInterval);
		cout<<"t"<<(i + 1)<<"\t";
		this->displayHIR();
	}
}
void Rain2ScatterPathMergehModel::displayHIR() {
	cout<<pow(this->ir[0], 2)<<"\t";
}
void Rain2ScatterPathMergehModel::displayVIR() {
	cout<<pow(this->ir[1], 2)<<"\t";
}
bool Rain2ScatterPathMergehModel::calculateImpulseResponse(double t) {
	if (this->paths.size() == 0) {
		return false;
	}
	this->ir[0] = 0;
	this->ir[1] = 0;
	list<Rain2ScatterPath>::iterator iterPath; 
	for (iterPath = this->paths.begin(); iterPath != this->paths.end(); iterPath++) {
		double tao = iterPath->delayTime;
		double tt = t - tao; 
		if (tt >= 0) { // tʱ���Ƿ񵽴���ն�
			double phaseShift = 2 * PI / iterPath->waveLength * C * tt;
			phaseShift += 2 * PI / iterPath->waveLength * iterPath->vDoppler * tt;
			iterPath->calculatePhase(phaseShift, phaseShift);
		} else {
			iterPath->calculatePhase(PI / 2, PI / 2);
		}
		iterPath->calculateIr();
		this->ir[0] += iterPath->ir[0];
		this->ir[1] += iterPath->ir[1];
	}
	return true;
}
