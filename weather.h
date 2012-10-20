#include <list>
#ifndef BASE_H 
#define BASE_H 
#include "base.h"
#endif 

using namespace std;
const double RAINDROP_MERGE_MULTIPLE_R = 3; // 两雨滴合并条件 球心距 半径倍数

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
	friend class MergedRainDrop;
private:
	Point p;
	double r; // 半径，mm
	Direction d;
	double v;
	double sCrossSection; // 散射截面积
	bool merged; // 是否合并过
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
	bool canMerge(RainDrop rd); // 判断两个雨滴是否能合并
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

	long amount; // 雨滴总数
	double unitL; // 立方体边长
	long a;
	long b;
	long c;
public:
	Rain2(Rain2Config c):config(c){};
	void initRainDrops();
	void addOneRainDrop(long i);
	void mergeRainDrops();
	void traceRainDrops(double t); // 考察t时刻的雨滴分布，注意t为0时刻后的间隔，和计算脉冲的t有所区分
};

// 合并雨滴的散射
class Rain2Scatter {
	friend class Rain2ScatterPath;
	friend class Model;
private:
    MergedRainDrop mergedRainDrop; // 合并雨滴
    double length[2]; // 起点到散射点、散射点到终点的长度
    Point points[3]; // 散射起点、散射点、终点
    Direction direction[2]; // 起点到散射点、散射点到终点的方向
	double angle[2]; // 入射角、出射角
	Direction polarization[2]; // 散射波垂直、水平极化振幅分量方向
	double amplitude[2]; // 散射波垂直、平行极化的振幅大小
	double amplitudeFade[2]; // 散射波垂直、水平极化振幅衰落百分比
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

// 合并雨滴的散射路径
class Rain2ScatterPath {
    friend class Model;
	friend class Rain2Scatter;
	friend class Rain2ScatterPathMergehModel;
private:
	bool merged;
	Direction tDirection; // 出射方向
	Direction rDirection; // 接收方向
	double totalLength; // 路径总长度	
	double delayTime; // 传播时延
	double frequency; // 频率
	double fDopplerShift; // 多普勒频移
	double waveLength; // 波长
	double vDoppler; // 多普勒速度
	double amplitude[2]; // 该路径两个极化方向上的振幅，v,h
	Direction polarization[2]; // 该路径两个极化方向，v,h
	double amplitudeReceive[2]; // 接收设备收到的振幅,垂直极化,水平极化
	double phase[2]; // 相位，垂直，水平
	double ir[2]; // 冲击响应,v垂直极化，h水平极化
	double amplitudeFade; // 路损
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
// 雨滴散射路径合并模型 
// 注意和叶子散射路径区别
class Rain2ScatterPathMergehModel {
private:
	int sampleCount; // 采样次数
	double sampleInterval; // 采样间隔
    list<Rain2ScatterPath> paths; 
	double ir[2]; // 脉冲响应
public:
	Rain2ScatterPathMergehModel(list<Rain2ScatterPath> paths):paths(paths){};
	// 设置采样信息
	void setSampleInfo(int sampleCount, double sampleInterval) {
	    this->sampleCount = sampleCount;
		this->sampleInterval = sampleInterval;
	};
	bool calculateImpulseResponse(double t);
	bool mergePath();
	list<Rain2ScatterPath> getPaths() {
	    return this->paths;
	};
	// 显示路径的垂直极化方向的脉冲响应
	void displayVIR();
	// 显示路径的水平极化方向的脉冲响应
	void displayHIR();
	// 显示采样的冲击响应
	void displaySampleIR();
};

