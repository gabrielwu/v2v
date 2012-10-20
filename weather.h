#include <list>
#ifndef BASE_H 
#define BASE_H 
#include "base.h"
#endif 

using namespace std;
const double RAINDROP_MERGE_MULTIPLE_R = 3; // ����κϲ����� ���ľ� �뾶����

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
	friend class MergedRainDrop;
private:
	Point p;
	double r; // �뾶��mm
	Direction d;
	double v;
	double sCrossSection; // ɢ������
	bool merged; // �Ƿ�ϲ���
public:
	RainDrop(Point p = Point(0,0,0), double r = 1,Direction d = Direction(0,0,-1), double v = 10){
	    this->p = p;
		this->r = r;
		this->d = d;
		this->v = v;
		this->sCrossSection = PI * pow((r/1000), 2);
		this->merged = false;
	};
	Point getP() {
	    return this->p;
	};
	bool canMerge(RainDrop rd); // �ж���������Ƿ��ܺϲ�
};
class MergedRainDrop {
	friend class Rain2Scatter;
private:
	list<RainDrop> rainDrops;
	double sCrossSection;
	Point position;
public:
	MergedRainDrop(list<RainDrop> rainDrops):rainDrops(rainDrops) {};
	void init();
	Point getPosition() {
	    return this->rainDrops.front().getP();
	};
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
	Rain2Config(){
	    this->rRange[0] = 2;
	    this->rRange[1] = 4;
	    this->vRange[0] = 8;
	    this->vRange[1] = 9;
		this->dWind = Direction(0,0,0);
		this->vWind = 0;
		this->length = 100;
		this->width = 0.012;
		this->height = 0.012;
		this->density = 8000;
	};
	void display();
};
class Rain2 {
	friend class Model;
private:
	Rain2Config config;
	list<RainDrop> rainDrops;
	list<MergedRainDrop> mergedRainDrops;

	long amount; // �������
	double unitL; // ������߳�
	long a;
	long b;
	long c;
public:
	Rain2(Rain2Config c):config(c){};
	void initRainDrops();
	void addOneRainDrop(long i);
	void mergeRainDrops();
	void traceRainDrops(double t); // ����tʱ�̵���ηֲ���ע��tΪ0ʱ�̺�ļ�����ͼ��������t��������
};

// �ϲ���ε�ɢ��
class Rain2Scatter {
	friend class Rain2ScatterPath;
	friend class Model;
private:
    MergedRainDrop mergedRainDrop; // �ϲ����
    double length[2]; // ��㵽ɢ��㡢ɢ��㵽�յ�ĳ���
    Point points[3]; // ɢ����㡢ɢ��㡢�յ�
    Direction direction[2]; // ��㵽ɢ��㡢ɢ��㵽�յ�ķ���
	double angle[2]; // ����ǡ������
	Direction polarization[2]; // ɢ�䲨��ֱ��ˮƽ���������������
	double amplitude[2]; // ɢ�䲨��ֱ��ƽ�м����������С
	double amplitudeFade[2]; // ɢ�䲨��ֱ��ˮƽ�������˥��ٷֱ�
public:
	Rain2Scatter(const MergedRainDrop& mergedRainDrop):mergedRainDrop(mergedRainDrop){
		Point p(0, 0 ,0);
	    this->points[0] = p;
	    this->points[1] = p;
	    this->points[2] = p;
	};
	bool init();
	bool calculatePolarAmplitude(Direction& inV, Direction& inH);
	bool calculatePolarAmplitude(Rain2Scatter& pre);
	bool calculateAmplitudeFade();
	void setPolarization(const Direction& vp, const Direction& hp);
	void setAmplitude(double v, double h);
};

// �ϲ���ε�ɢ��·��
class Rain2ScatterPath {
    friend class Model;
	friend class Rain2Scatter;
	friend class Rain2ScatterPathMergehModel;
private:
	bool merged;
	Direction tDirection; // ���䷽��
	Direction rDirection; // ���շ���
	double totalLength; // ·���ܳ���	
	double delayTime; // ����ʱ��
	double frequency; // Ƶ��
	double fDopplerShift; // ������Ƶ��
	double waveLength; // ����
	double vDoppler; // �������ٶ�
	double amplitude[2]; // ��·���������������ϵ������v,h
	Direction polarization[2]; // ��·��������������v,h
	double amplitudeReceive[2]; // �����豸�յ������,��ֱ����,ˮƽ����
	double phase[2]; // ��λ����ֱ��ˮƽ
	double ir[2]; // �����Ӧ,v��ֱ������hˮƽ����
	double amplitudeFade; // ·��
	list<Rain2Scatter> scatters;
public:
	Rain2ScatterPath(const list<Rain2Scatter> scatters):scatters(scatters){
	    this->merged = false;
	};
	void setScatters(const list<Rain2Scatter>& scatters) {
	    this->scatters = scatters;
	};
	void setMerged(bool merged = true) {
	    this->merged = merged;
	};
	bool isMerged() {
	    return this->merged;
	};
	Direction getTDirection() const {
	    return this->tDirection;
	};
	Direction getRDirection() const {
	    return this->rDirection;
	};
    bool calculate(Direction& relativeV, const vector<Antenna>& ras);
	bool calculateDirection();
	bool calculateWaveLength();
	bool calculateVDoppler(Direction& relativeV);
	bool calculateFDopplerShift();
	bool calculateFrequency();
	bool calculateLength();
	bool calculateDelayTime();
	bool calculateAmplitude();
	bool calculatePolarization();
	bool calculateAmplitudeFade();
	bool calculateAmplitudeReceive(const vector<Antenna>& ras);
	bool calculatePhase(double v, double h);
	bool calculateIr();
	void displayIr();
	void displayVir();
	void displayHir();
	void displayPathTotalLength();
	void displayAmplitudeV();
	void displayAmplitudeH();
};
// ���ɢ��·���ϲ�ģ�� 
// ע���Ҷ��ɢ��·������
class Rain2ScatterPathMergehModel {
private:
	int sampleCount; // ��������
	double sampleInterval; // �������
    list<Rain2ScatterPath> paths; 
	double ir[2]; // ������Ӧ
public:
	Rain2ScatterPathMergehModel(list<Rain2ScatterPath> paths):paths(paths){};
	// ���ò�����Ϣ
	void setSampleInfo(int sampleCount, double sampleInterval) {
	    this->sampleCount = sampleCount;
		this->sampleInterval = sampleInterval;
	};
	bool calculateImpulseResponse(double t);
	bool mergePath();
	list<Rain2ScatterPath> getPaths() {
	    return this->paths;
	};
	// ��ʾ·���Ĵ�ֱ���������������Ӧ
	void displayVIR();
	// ��ʾ·����ˮƽ���������������Ӧ
	void displayHIR();
	// ��ʾ�����ĳ����Ӧ
	void displaySampleIR();
};

