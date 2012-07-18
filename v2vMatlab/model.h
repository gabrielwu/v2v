#include <vector>
#include <iostream>
#ifndef MATH_H 
#define MATH_H 
#include "math.h"
#endif 
#include "stdafx.h"

using namespace std;

const double C = 300000000;
const double F = 5900000000;
const double PI = 3.1415926;
const double E = 2.718281828;
const double WAVE_LENGTH = C / F;
const int NUM_OF_PATHS = 7;
const int NUM_OF_REFLECTS = 3;
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
	Direction operator -(Point& p);
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
	double operator *(Direction& d);
	Direction operator *(double module);
	Direction operator ^(Direction& d);
	Direction operator -(Direction& d);
	Direction operator -();
	
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
public:
	Surface(const Point& p0, 
		    const Point& p1, 
			const Material& material = Material(), 
			const Direction& nVector = Direction()):p0(p0),p1(p1),material(material),nVector(nVector){
				Point p2(p0.x, p0.y, p1.z);
				Point p3(p1.x, p1.y, p0.z);
				this->p2 = p2;
				this->p3 = p3;
	};
	Surface(const Point& p0, 
		    const Point& p1, 
			const Point& p2,
			const Point& p3,
			const Material& material, 
			const Direction& nVector = Direction()):p0(p0),p1(p1),p2(p2),p3(p3),material(material),nVector(nVector){};
	void setMaterial(const Material& m) {
		this->material = m;
	};
	// 初始化函数
	void init();
	// 计算平面方程
    void calculateEquation(); 
	// 计算法向量
	void calculateVector();
	double getA() const;
	double getB() const;
	double getC() const;
	double getD() const;
	// 判断点p是否在平面范围
	bool isPointOn(const Point& p) const; 
	// 获得法向量
	Direction getNVector() const;
	// 获取材料
	Material getMaterial() const;
	// 显示平面信息
	void display(int space = 0);
	// 显示平面信息
	void displayExcel();
};
// 汽车类
class Vehicle {
	friend class Model;
private:
	
	// 行进(速度)方向
    Direction direction;
	// 速率
    double velocity;
public:
	// 天线参考点
    Point p;
	Vehicle(const Point& p, const Direction& direction, double velocity):p(p),direction(direction),velocity(velocity) {};
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
private:
	// 注意是从起始点到反射点的长度
    double length; 
	// 反射点
    Point reflectPoint;
	// 反射分段起始点
    Point startPoint;
	// 反射分段终止点
	Point endPoint;
	// 反射面
    Surface surface;
	// 反射点到终止点点的方向
    Direction direction; 
	// 反射波平行于反射面内的振幅分量方向
	Direction h;
	// 反射波垂直于反射面内的振幅分量方向
	Direction v;
	// 反射波平行于反射面的振幅大小
	double hAmplitude;
	// 反射波垂直于反射面的振幅大小
	double vAmplitude;
	// 振幅方向
	Direction amplitudeDireciton;
	// 振幅大小
	double amplitude;
	// 反射角大小
	double reflectAngle;
	// 反射波垂直于反射面的振幅衰落百分比
	double amplitudeFadeV;
	// 反射波平行于反射面的振幅衰落百分比
	double amplitudeFadeH;
	// 反射波垂直于反射面的相移
	double vPhaseShift;
	// 反射波平行于反射面的相移
	double hPhaseShift;
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
};


// 传播路径类
class Path {
	friend class Model;
private:
	// 路径总长度
    double totalLength;
	// 反射次数
    int numOfReflect;
	// 传播时延
	double delayTime;
	// 反射对象向量
    vector<Reflection> reflections;
	// 反射波平行于反射面内的振幅分量方向
	Direction h;
	// 反射波垂直于反射面内的振幅分量方向
	Direction v;
	// 初始相位,垂直极化v，水平极化h[v,h]
	double initPhase[2];
	// 反射波平行于反射面的振幅大小
	double hAmplitude;
	// 反射波垂直于反射面的振幅大小
	double vAmplitude;
	// 反射波垂直于反射面的相移
	double vPhaseShift;
	// 反射波平行于反射面的相移
	double hPhaseShift;
	// 接收车(镜像)和发射车的相对速度
	double relativeVelocity;
	// 接收车(镜像)和发射车的相对速度方向与该路径传播方向的夹角
	double relativeAngle;
	// 接收车(镜像)和发射车的相对速度方向
	Direction relVelDirect;
	// 接收车(镜像)和发射车的相对速度相对于传播路径的速度
	double vDoppler;
	// 频率
	double frequency;
	// 波长
	double waveLength;
	// 多普勒频移
	double fDopplerShift;
	// 垂直方向接收到的相位
	double vPhasereceive;
	// 水平方向接收到的相位
	double hPhasereceive;
	// 接收设备收到的振幅,垂直极化,水平极化
	double amplitudeReceive[2];
	// 冲击响应,v垂直极化，h水平极化
	double ir[2];
public:
	Path(double totalLength, int numOfReflect, const vector<Reflection>& reflections):
	  totalLength(totalLength), numOfReflect(numOfReflect), reflections(reflections) {
	    //this->delayTime = totalLength / C;
		this->hPhaseShift = 0;
		this->vPhaseShift = 0;
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
};

//总体模型类
class Model{
private:	
	// 发射车Tx
    Vehicle transmitter;
	// 接收车Rx
    Vehicle receiver;
	// 能量最强的路径
	vector<Path> strongestPaths;
	// 发射天线阵
	vector<Antenna> tAntennas;
	// 接收天线阵
	vector<Antenna> rAntennas;

	// 计算LOS
	bool calculateLOSPath();

	// 计算反射路径
	bool calculateReflectPaths();
public:
	// 反射表面
    vector<Surface> surfaces;
	Model(const Vehicle& transmitter, 
		  const Vehicle& receiver, 
		  const vector<Surface>& surfaces, 
		  const vector<Antenna>& tAntennas,
		  const vector<Antenna>& rAntennas):
	  transmitter(transmitter), 
	  receiver(receiver), 
	  surfaces(surfaces), 
	  tAntennas(tAntennas),
	  rAntennas(rAntennas){};
	Model(const Vehicle& transmitter, 
		  const Vehicle& receiver, 
		  const vector<Surface>& surfaces):
	  transmitter(transmitter), 
	  receiver(receiver), 
	  surfaces(surfaces){};
    // 初始化
    void init();
	// 获取模型中最短的7条路径（确切讲为能量最强的，下一步工作）
    // return: 最短路径
    bool calculateStrongestPaths();

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
	
	// 计算振幅衰落
	bool calculateAmplitude();

	// 获取能量最强的路径向量
	vector<Path> getStrongestPaths() const;

	// 计算t时刻的信道冲击响应
	bool calculateImpulseResponse(double t);


	// 显示路径
	void displayPath();

	// 显示路径的水平垂直极化方向的脉冲响应
	void displayPathIR();

	// 显示路径的垂直极化方向的脉冲响应
	void displayPathVIR();

	// 显示路径的水平极化方向的脉冲响应
	void displayPathHIR();
	
	// 显示信道脉冲
	void displayIR();

	// 显示输入模型参数
	void displayModel();

	// 结果显示到excel中的格式
	void displayModelExcel();

	// 显示最大时延
	void displayMaxDelay();

	Vehicle getTransmitter() {
		return this->transmitter;
	};
	Vehicle getReceiver() {
		return this->receiver;
	};
	void setTransmitter(Vehicle transmitter) {
		this->transmitter = transmitter;
	};
	void setReceiver(Vehicle receiver) {
		this->receiver = receiver;
	};
};