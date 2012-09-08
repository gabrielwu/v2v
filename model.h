#include <vector>
#include <list>
#include <iostream>
#ifndef MATH_H 
#define MATH_H 
#include "math.h"
#endif 
#ifndef BASE_H 
#define BASE_H 
#include "base.h"
#endif 
#ifndef DIFFRACTION_H 
#define DIFFRACTION_H 
#include "diffraction.h"
#endif 
#ifndef SCATTERING_H 
#define SCATTERING_H 
#include "scattering.h"
#endif 
#ifndef WEATHER_H 
#define WEATHER_H 
#include "weather.h"
#endif 
using namespace std;

// 汽车类
class Vehicle {
	friend class Model;
private:
    Direction direction; // 行进(速度)方向
    double velocity; // 速率
public:
    Point p; // 天线参考点
	Vehicle(const Point& p = Point(), const Direction& direction = Direction(), double velocity = 0):p(p),direction(direction),velocity(velocity) {};
	Point getP() const;
	Direction getDirection() const {
		return this->direction;
	};
	double getVelocity() {
		return this->velocity;
	};
	void displayVehichleExcel();
	void displayVehichle();
};

// 反射类
class Reflection {
	friend class Model;
	friend class Path;
	friend class MixPathSegment;
	friend class MixPath;
private:
    double length; // 注意是从反射点到终止点的长度
    Point reflectPoint; // 反射点
    Point startPoint; // 反射分段起始点
	Point endPoint; // 反射分段终止点
    Surface surface; // 反射面
    Direction direction; // 反射点到终止点点的方向
	Direction h; // 反射波平行于反射面内的振幅分量方向
	Direction v; // 反射波垂直于反射面内的振幅分量方向
	double hAmplitude; // 反射波平行于反射面的振幅大小
	double vAmplitude; // 反射波垂直于反射面的振幅大小
	Direction amplitudeDireciton; // 振幅方向
	double amplitude; // 振幅大小
	double reflectAngle; // 反射角大小
	double amplitudeFadeV; // 反射波垂直于反射面的振幅衰落百分比
	double amplitudeFadeH; // 反射波平行于反射面的振幅衰落百分比
	double vPhaseShift; // 反射波垂直于反射面的相移
	double hPhaseShift; // 反射波平行于反射面的相移
	double scatterFade; // 散射因子
	double hc; // 平整参考高度
public:
	Reflection(double length, 
		       const Point& reflectPoint, 
			   const Point& startPoint, 
			   const Point& endPoint, 
			   const Surface& surface, 
			   const Direction& direction);
	Reflection(double length, 
		       const Point& reflectPoint, 
			   const Point& endPoint, 
			   const Direction& direction);
    double getLength() const;
	Direction getDirection() const;
	Point getReflectPoint() const;
	Direction getV() const;
	Direction getH() const;
	Surface getSurface() const;
	bool calculateHc(double waveLength);
	bool calculateScatterFade(double waveLength);
	double getHAmplitude() {
		return this->hAmplitude;
	};
	double getVAmplitude() {
		return this->vAmplitude;
	};
	double getAmplitude() {
		return this->amplitude;
	};
	bool calculateVH();
	bool calculateAmplitudeFadeV();
	bool calculateAmplitudeFadeH();
	double getAmplitudeFadeH() {
		return this->amplitudeFadeH;
	};
	double getAmplitudeFadeV() {
		return this->amplitudeFadeV;
	};
	double getReflectAngle() {
		return this->reflectAngle;
	};
	void init();
	void setH(const Direction& h) {
		this->h = h;
	};
	void setV(const Direction& v) {
	    this->v = v;
	};
	void setHAmplitude(double hAmplitude) {
		this->hAmplitude = hAmplitude;
	};
	void setVAmplitude(double vAmplitude) {
		this->vAmplitude = vAmplitude;
	};
	void setAmplitudeDireciton(Direction amplitudeDirection) {
		this->amplitudeDireciton = amplitudeDirection;
	};
	void setAmplitude(double amplitude) {
		this->amplitude = amplitude;
	};
	void setReflectAngle(double reflectAngle) {
		this->reflectAngle = reflectAngle;
	};
	void setAmplitudeFadeV(double amplitudeFadeV) {
		this->amplitudeFadeV = amplitudeFadeV;
	};
	void setAmplitudeFadeH(double amplitudeFadeH) {
		this->amplitudeFadeH = amplitudeFadeH;
	};
	void setHPhaseShift(double hPhaseShift) {
		this->hPhaseShift = hPhaseShift;
	};
	void setVPhaseShift(double vPhaseShift) {
		this->vPhaseShift = vPhaseShift;
	};
	// 判断此段路径是否被其他面阻挡
	bool isBlocked(vector<Surface>& surface);
};


// 传播路径类
class Path {
	friend class Model;
	friend class MixPathSegment;
	friend class MixPath;
private:
    double totalLength;// 路径总长度
    int numOfReflect;// 反射次数
	double delayTime;// 传播时延
    vector<Reflection> reflections;// 反射对象向量
	Direction h;// 反射波平行于入（反）射面内的振幅分量方向
	Direction v;// 反射波垂直于入（反）射面内的振幅分量方向
	double initPhase[2];// 初始相位,垂直极化v，水平极化h[v,h]
	double hAmplitude;// 反射波平行于入（反）射面的振幅大小
	double vAmplitude;// 反射波垂直于入（反）射面的振幅大小
	double hPhaseShift;// 反射波平行于入（反）射面的相移
	double vPhaseShift;// 反射波垂直于入（反）射面的相移
	double relativeVelocity;// 接收车(镜像)和发射车的相对速度
	double relativeAngle;// 接收车(镜像)和发射车的相对速度方向与该路径传播方向的夹角
	Direction relVelDirect;// 接收车(镜像)和发射车的相对速度方向
	double vDoppler;// 接收车(镜像)和发射车的相对速度相对于传播路径的速度
	double frequency;// 频率
	double waveLength;// 波长
	double fDopplerShift;// 多普勒频移
	double vPhasereceive;// 垂直方向接收到的相位
	double hPhasereceive;// 水平方向接收到的相位
	double amplitudeReceive[2];// 接收设备收到的振幅,垂直极化,水平极化	
	double ir[2];// 冲击响应,v垂直极化，h水平极化
	double amplitudeFade; // 路损
	double stormFade; // 沙尘衰减
	double stormShift; // 沙尘相移
	double rainFade[2]; // 垂直水平极化降水衰减（垂直水平是相对的）
public:
	Path(double totalLength, int numOfReflect, const vector<Reflection>& reflections):
	  totalLength(totalLength), numOfReflect(numOfReflect), reflections(reflections) {
	    //this->delayTime = totalLength / C;
		this->hPhaseShift = 0;
		this->vPhaseShift = 0;
		this->stormFade = 1;
		this->stormShift = 0;
		this->rainFade[0] = 1;
		this->rainFade[1] = 1;
	};
	double getVir() {
		return this->ir[0];
	};
	double getHir() {
		return this->ir[1];
	};
    double getHAmplitude() {
		return this->hAmplitude;
	};
	double getVAmplitude() {
		return this->vAmplitude;
	};
	Direction getH() {
		return this->h;
	};
	Direction getV() {
		return this->v;
	};
	double getHPhaseShift() {
		return this->hPhaseShift;
	};
	double getVPhaseShift() {
		return this->vPhaseShift;
	};

	double getVDoppler() {
		return this->vDoppler;
	};
	double getRelativeVelocity() {
		return this->relativeVelocity;
	};
	double getRelativeAngle() {
		return this->relativeAngle;
	};
	Direction getRelVelDirect() {
		return this->relVelDirect;
	};
	double getFrequency() {
		return this->frequency;
	};
	double getWaveLength() {
		return this->waveLength;
	};
	double getFDopplerShift() {
		return this->fDopplerShift;
	};
	double getVPhaseReceive() {
		return this->vPhasereceive;
	};
	double getHPhaseReceive() {
		return this->hPhasereceive;
	};
	double* getAmplitudeReceive() {
		return this->amplitudeReceive;
	};
	double getVInitPhase() {
		return this->initPhase[0];
	};
	double getHInitPhase() {
		return this->initPhase[1];
	};
	void calculateIr() ;
	void setInitPhase(double v, double h) {
		this->initPhase[0] = v;
		this->initPhase[1] = h;
	};
	void setH(const Direction& h) {
		this->h = h;
	};
	void setV(const Direction& v) {
	    this->v = v;
	};
	void setHPhaseShift(double hPhaseShift) {
		this->hPhaseShift = hPhaseShift;
	};
	void setVPhaseShift(double vPhaseShift) {
		this->vPhaseShift = vPhaseShift;
	};
	void setHAmplitude(double hAmplitude) {
		this->hAmplitude = hAmplitude;
	};
	void setVAmplitude(double vAmplitude) {
		this->vAmplitude = vAmplitude;
	};
	void setVDoppler(double vDoppler) {
		this->vDoppler = vDoppler;
	};
	void setRelativeVelocity(double relativeVelocity) {
		this->relativeVelocity = relativeVelocity;
	};
	void setRelativeAnge(double relativeAngle) {
		this->relativeAngle = relativeAngle;
	};
	void setRelVelDirect(const Direction& relVelDirect) {
		this->relVelDirect = relVelDirect;
	};
	void setFrequency(double frequency) {
		this->frequency = frequency;
	};
	void setWaveLength(double waveLength) {
		this->waveLength = waveLength;
	};
	void setHPhaseReceive(double hPhaseReceive) {
		this->hPhasereceive = hPhaseReceive;
	};
	void setVPhaseReceive(double vPhaseReceive) {
		this->vPhasereceive = vPhaseReceive;
	};
	void setAmplitudeReceive(double v, double h) {
		this->amplitudeReceive[0] = v;
		this->amplitudeReceive[1] = h;

	};
	void calculateFDopplerShift() {
		this->fDopplerShift = this->frequency - F;
	};
	void init();
	// TODU:接受相位值
	void calculatePhaseReceive() {
		double hPhase = 2 * PI / this->waveLength * (- this->totalLength - this->hPhaseShift / (2 * PI) * this->waveLength);
		double vPhase = 2 * PI / this->waveLength * (- this->totalLength - this->vPhaseShift / (2 * PI) * this->waveLength);
		this->setHPhaseReceive(hPhase);
		this->setVPhaseReceive(vPhase);
	};
	void calculateAmplitudeReceive(const vector<Antenna>& ras);
	void displayVir() {
		cout<<pow(this->ir[0], 2)<<"\t";
	}
	void displayHir() {
		cout<<pow(this->ir[1], 2)<<"\t";
	}
	void displayPathTotalLength();
	void displayIR() {
		/*
		Direction h = this->h;
		double ha = this->hAmplitude;
		Direction v = this->v;
		double va = this->vAmplitude;
		cout<<"  h IR: ("<<h.i * ha<<","<<h.j * ha<<","<<h.k * ha<<")*e^("<<this->hPhasereceive<<"j)"<<endl;
		cout<<"  v IR: ("<<v.i * va<<","<<v.j * va<<","<<v.k * va<<")*e^("<<this->vPhasereceive<<"j)"<<endl;
		*/
		/*
		cout<<"  v IR: "<<this->amplitudeReceive[0]<<"*e^("<<this->getVPhaseShift()<<"j),"<<this->ir[0]<<endl;
		cout<<"  h IR: "<<this->amplitudeReceive[1]<<"*e^("<<this->getHPhaseShift()<<"j),"<<this->ir[1]<<endl;
		*/
		cout<<"  v IR: "<<pow(this->ir[0], 2)<<endl;
		cout<<"  h IR: "<<pow(this->ir[1], 2)<<endl;
	
	};

    // 获取路径总长度
    double getTotalLength() const;
	int getNumOfReflect() const;
	vector<Reflection> getReflections() ;
	double getDelayTime() {
		return this->delayTime;
	};
	void stormEffect(Storm& storm); // 沙尘影响
	void rainEffect(Rain& rain); // 降雨影响
};

class DiffractPath {
	friend class Model;
	friend class MixPathSegment;
	friend class MixPath;
private:
	Reflection* reflection;
    double totalLength; // 路径总长度
	double delayTime; // 传播时延
	double frequency; // 频率
	double waveLength; // 波长
	double vDoppler; // 多普勒速度
	Direction aInDirection[2]; // 绕射前极化方向，垂直，水平
	Direction aOutDirection[2]; // 绕射后极化方向，垂直，水平
	double aIn[2]; // 绕射前振幅，垂直，水平
	double aOut[2]; // 绕射后振幅，垂直，水平
	double aReceive[2]; // 接收设备收到的振幅,垂直极化,水平极化
	double phase[2]; // 相位，垂直，水平
	double ir[2]; // 冲击响应,v垂直极化，h水平极化
	Diffraction diffraction; // 绕射对象
	double amplitudeFade; // 绕射引起的振幅衰落百分比
public:
    DiffractPath(const Diffraction& diffraction):diffraction(diffraction){};
	void init(Vehicle& tx, Vehicle& rx);
	int isLosBlocked();
	void setReflection(Reflection* reflection) {
	    this->reflection = reflection;
	};
	void calculateDiffractPath(
		  const Antenna& tAntenna,
		  const Antenna& rAntenna);
	void setPhase(double v, double h) {
		this->phase[0] = v;
		this->phase[1] = h;
	};
	void setAReceive(double v, double h) {
	    this->aReceive[0] = v;
		this->aReceive[1] = h;
	};
    void calculateIr();
	void displayVir() {
		cout<<pow(this->ir[0], 2)<<"\t";
	}
	void displayHir() {
		cout<<pow(this->ir[1], 2)<<"\t";
	}
};

// 混合路径段
class MixPathSegment{
	friend class MixPath;
private:
    Reflection* pReflect;// 反射或直射路径对象指针
    Diffraction* pDiffract; // 绕射路径对象指针
	double length; // 分段长度
public:
    MixPathSegment(Reflection* pReflect = NULL, Diffraction* pDiffract = NULL):pReflect(pReflect),pDiffract(pDiffract){
		if (pDiffract != NULL) {
		    this->length = this->pDiffract->totalLength;
		} else if (pReflect != NULL) {
		    this->length = this->pReflect->length;
		}
	};
	Reflection* getSegmentR() {
	    return this->pReflect;
	};
    Diffraction* getSegmentD() {
	    return this->pDiffract;
	};
};
// 混合路径
class MixPath{
	friend class Model;
private:
	Path* reflectPath; // 未进行验证的反射路径
    vector<MixPathSegment> segments; // 分段向量，构成完整的路径
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
public:
	MixPath(Path* reflectPath, const vector<MixPathSegment>& segments):reflectPath(reflectPath),segments(segments){
	    this->vDoppler = this->reflectPath->vDoppler;
	};
	void init();
	bool calculateAmplitudeFade();
	bool calculateAmplitude();
	bool calculateAmplitudeReceive(const vector<Antenna>& ras);
	bool calculateTotalLength();
	bool calculateDelay();
	bool calculateDoppler();
	void setAmplitude(double va, double ha) {
	    this->amplitude[0] = va;
		this->amplitude[1] = ha;
	};
	void setAmplitudeReceive(double va, double ha) {
	    this->amplitudeReceive[0] = va;
		this->amplitudeReceive[1] = ha;
	};
	void setPhase(double vp, double hp) {
	    this->phase[0] = vp;
		this->phase[1] = hp;
	};
	void setPolarization(const Direction& v, const Direction& h) {
	    this->polarization[0] = v;
		this->polarization[1] = h;
	};
	void calculateIr();
	void displayVir() {
	    cout<<pow(this->ir[0], 2)<<"\t";
	};
	void displayHir() {
	    cout<<pow(this->ir[1], 2)<<"\t";
	};
};

//总体模型类
class Model {
	friend class MergePathModel;
private:	
    Vehicle transmitter; // 发射车Tx
    Vehicle receiver; // 接收车Rx
	vector<Antenna> tAntennas; // 发射天线阵
	vector<Antenna> rAntennas; // 接收天线阵
	vector<Path> strongestPaths; // 能量最强的路径
	vector<Path> surfaceScatterPaths; // 平面散射路径路径，考虑了散射的strongestPaths
	vector<DiffractPath> diffractPaths; // 绕射路径向量
	vector<TreeScatterPath> treeScatterPaths; // 树木散射路径 
	vector<LeafScatterPath> leafScatterPaths; // 树叶子散射路径 
	vector<LeafScatterMergePath> leafScatterMergePaths; // 树叶子散射合并路径 
	vector<MixPath> mixPaths; // 绕射路径向量
    vector<Surface> surfaces; // 反射表面
    vector<Edge> edges; // 刃形向量
	vector<Tree> trees; // 树木
    Storm* storm;
	Rain* rain;
	int sampleCount; // 采样次数
	double sampleInterval; // 采样间隔
	// 计算LOS
	bool calculateLOSPath();
	// 计算反射路径
	bool calculateReflectPaths();
	// LOS绕射条件判断
	// return 
	// 1:直射，空间自由；
	// 2:衍射，半开，时延、多普勒、相位都按直射来计算，振幅（或者功率）损失按照绕射来算
	// 3:所有参数按绕射计算
	int isLOSExist();
	// 影响los的绕射路径
	// param: DiffractPath* ,出参
	// return:
	// 1:直射，空间自由；
	// 2:衍射，半开，时延、多普勒、相位都按直射来计算，振幅（或者功率）损失按照绕射来算
	// 3:所有参数按绕射计算
	DiffractPath* diffractAffectLos(int& type);
public:
	Model(const Vehicle& transmitter, 
		  const Vehicle& receiver, 
		  const vector<Surface>& surfaces, 
		  const vector<Antenna>& tAntennas,
		  const vector<Antenna>& rAntennas,
		  Storm* storm = NULL,
		  Rain* rain = NULL):
	  transmitter(transmitter), receiver(receiver), surfaces(surfaces), tAntennas(tAntennas),rAntennas(rAntennas),storm(storm), rain(rain){};
	Model(const Vehicle& transmitter, 
		  const Vehicle& receiver, 
		  const vector<Surface>& surfaces, 
		  const vector<Edge>& edges,
		  const vector<Antenna>& tAntennas,
		  const vector<Antenna>& rAntennas,
		  Storm* storm = NULL,
		  Rain* rain = NULL):
	  transmitter(transmitter), 
	  receiver(receiver), 
	  surfaces(surfaces),
	  edges(edges),
	  tAntennas(tAntennas),
	  rAntennas(rAntennas),storm(storm), rain(rain){};
	Model(const Vehicle& transmitter, 
		  const Vehicle& receiver, 
		  const vector<Surface>& surfaces,
		  Storm* storm = NULL,
		  Rain* rain = NULL):
	  transmitter(transmitter), 
	  receiver(receiver), 
	  surfaces(surfaces),storm(storm), rain(rain){};
	Model(const Vehicle& transmitter, 
		  const Vehicle& receiver, 
		  const vector<Surface>& surfaces,
		  const vector<Edge>& edges,
		  Storm* storm = NULL,
		  Rain* rain = NULL):
	  transmitter(transmitter), 
	  receiver(receiver), 
	  surfaces(surfaces),
	  edges(edges),storm(storm), rain(rain){};
	void setTrees(const vector<Tree>& trees) {
		this->trees = trees;
	};
	void setWeather(Storm* storm, Rain* rain) {
		this->storm = storm;
		this->rain = rain;
	};
	// 设置采样信息
	void setSampleInfo(int sampleCount, double sampleInterval) {
	    this->sampleCount = sampleCount;
		this->sampleInterval = sampleInterval;
	};
	int getSampleCount() {
	    return this->sampleCount;
	};
	double getSampleInterval() {
	    return this->sampleInterval;
	};
    // 初始化
    void init();
	// 获取模型中最短的7条路径（确切讲为能量最强的，下一步工作）
    // return: 
    bool calculateStrongestPaths();
	// 计算绕射路径
	bool calculateDiffractPaths();

	// 计算平面散射路径，在calculateStrongestPaths()后调用，直接采用了StrongestPaths，不同于其他类型路径的计算
	bool calculateSurfaceScatterPaths();

	// 计算树木散射路径
	bool calculateTreeScatterPaths();
	bool calculateTreeScatterPath(list<Tree> t);
	void insertTreeScatterPath(const TreeScatterPath& newPath);

	// 计算树叶子散射路径
	bool calculateLeafScatterPaths();
	bool calculateLeafScatterPath(list<Leaf> l);
	void insertLeafScatterPath(const LeafScatterPath& newPath);

	// 计算混合路径
	bool calculateMixPaths();

	// 计算沙尘影响路径
	bool calculateStormPaths(); 
	// 计算降水影响路径
	bool calculateRainPaths(); 

    // 构建单条完整反射传播路径()
    // @pt:发射天线点
    // @pr:接收天线点
    // @surfaces:假定信号传播路径所经反射面的序列
    // return: 若传播路径成立，返回Path对象；否则返回null
    bool getReflectPath(const Point& pt, const Point& pr, const vector<Surface>& surfaces);

	// 加入路径并排序
    // @newPath:新加入的传播路径
    // @paths:原有传播路径集
    void insertPath(const Path& newPath);

	// 加入绕射路径并排序
    // @newDiffractPath:新加入的传播路径
    void insertDiffractPath(const DiffractPath& newDiffractPath);
	
	// 计算振幅衰落
	bool calculateAmplitude();

	// 获取能量最强的路径向量
	vector<Path> getStrongestPaths() const;

	// 计算t时刻的信道冲击响应
	bool calculateImpulseResponse(double t);
    
	// 计算t时刻绕射路径的的信道冲击响应
	bool calculateDiffractImpulseResponse(double t);

	// 计算t时刻混合路径的的信道冲击响应
	bool calculateMixImpulseResponse(double t);

	// 计算t时刻平面散射路径的的信道冲击响应
	bool calculateSurfaceScatterImpulseResponse(double t);

	// 计算t时刻树木散射路径的的信道冲击响应
	bool calculateTreeScatterImpulseResponse(double t);


	// 显示路径
	void displayPath();
	void displayPathRainFade(); //显示降雨对于每条路径上两种极化的衰落

	// 显示路径的水平垂直极化方向的脉冲响应
	void displayPathIR();

	// 显示路径的垂直极化方向的脉冲响应
	void displayPathVIR();
	// 显示路径的水平极化方向的脉冲响应
	void displayPathHIR();
	// 显示采样的冲击响应
	void displayPathsSampleIR();

	// 显示绕射路径的垂直极化方向的脉冲响应
	void displayDiffractPathVIR();
	// 显示绕射路径的水平极化方向的脉冲响应
	void displayDiffractPathHIR();
	// 显示采样的冲击响应
	void displayDiffractPathsSampleIR();

	// 显示混合路径的垂直极化方向的脉冲响应
	void displayMixPathVIR();
	// 显示混合路径的水平极化方向的脉冲响应
	void displayMixPathHIR();
	// 显示采样的冲击响应
	void displayMixPathsSampleIR();

	// 显示平面散射路径的垂直极化方向的脉冲响应
	void displaySurfaceScatterPathVIR();
	// 显示平面散射路径的水平极化方向的脉冲响应
	void displaySurfaceScatterPathHIR();
	// 显示采样的冲击响应
	void displaySurfaceScatterPathsSampleIR();

	// 显示树木散射路径的垂直极化方向的脉冲响应
	void displayTreeScatterPathVIR();
	// 显示树木散射路径的水平极化方向的脉冲响应
	void displayTreeScatterPathHIR();
	// 显示树木散射路径的振幅
	void displayTreeScatterPathsAmplitude();
	// 显示采样的冲击响应
	void displayTreeScatterPathsSampleIR();
	
	void displayResult();
	void displaySampleInfo(); // 显示采样信息，次数和间隔
	// 显示采样的冲击响应
	void displaySampleIR();
	// 显示信道脉冲
	void displayIR();

	// 显示输入模型参数
	void displayModel();

	// 结果显示到excel中的格式
	void displayModelExcel();

	// 显示刃形，excel格式
	void displayEdgesExcel();

	// 显示树木，excel格式
	void displayTreesExcel();

	// 显示天气情况
	void displayWeather();
	
	// 显示各路径总长
	void displayPathsLength();


	// 显示树木散射各路径总长
	void displayTreeScatterPathsLength();

	vector<LeafScatterPath> getLeafScatterPaths() {
	    return this->leafScatterPaths;
	};
	// 显示最大时延
	void displayMaxDelay();

	Vehicle getTransmitter() {
		return this->transmitter;
	};
	Vehicle getReceiver() {
		return this->receiver;
	};
	vector<DiffractPath> getDiffractPaths() const{
	    return this->diffractPaths;
	};
	vector<Edge> getEdges() const {
	    return this->edges;
	};
	void setTransmitter(Vehicle transmitter) {
		this->transmitter = transmitter;
	};
	void setReceiver(Vehicle receiver) {
		this->receiver = receiver;
	};
	void setDiffractPaths(const vector<DiffractPath>& diffractPaths) {
	    this->diffractPaths = diffractPaths;
	};
	void setEdges(const vector<Edge>& edges) {
	    this->edges = edges;
	};

};


