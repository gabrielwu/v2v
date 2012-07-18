#include <vector>
#include <iostream>
#ifndef MATH_H 
#define MATH_H 
#include "math.h"
#endif 
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




// 获取两点间距离
double getDistance(const Point& p0, const Point& p1);

// 获取两点间距离
double getDistanceByDirection(const Direction& d0, const Direction& d1);

// 获取点p关于面s的对称点pn
// @s:待检验反射面
// @pn:待检验点
Point* getSymmetricPoint (const Surface& s, const Point& p); 

// 获取两点pa、pb连线关于平面s的交点p 
// @s:待检验平面
// @pa:起始点（实际应用中应为某点关于s的对称点）
// @pb:终止点
// return:若有交点，返回交点（反射点或入射点）Point对象
Point* getReflectPoint(const Surface& s, const Point& pa, const Point& pb);

// 获得反射对象
// @s:待检验反射面
// @pt:出射点
// @pr:接收点
// return:若反射成立，返回Reflecttion对象；否则返回null
Reflection* getReflection(const Surface& s, const Point& pt, const Point& pr);

// 多段反射中第一段
Reflection* getFirstReflection(const Point& reflectPoint, const Point& pr, const Antenna& a);


// 计算直线与平面的交点
// @dLine:直线向量
// @nPlane:平面法向量
// @pLine:过直线的一个点
// @pPlane:过平面的一个点
Point* calculateIntersectPoint(Direction& dLine, Direction& nPlane, Point& pLine, Point& pPlane);

// 获取单位方向向量
// @d:方向向量
// return:单位方向向量
Direction getUnitDirection(const Direction& d);

// 计算获得两向量夹角
double getAngleByVectors(const Direction& d0, const Direction& d1);
// 计算获取发射角
double calculateReflectAngle(const Direction& d0, const Direction& d1);
// 计算向量点积
Direction getScalarProduct(const Direction& d0, const Direction& d1);


// 计算多普勒影响下的频率
double getDopplerFrequency(double vDoppler, double frequency, double v);



// 获取两点间距离
double getDistance(const Point& p0, const Point& p1) {
	return sqrt(pow((p0.x - p1.x), 2) + pow((p0.y - p1.y), 2) + pow((p0.z - p1.z), 2));
};
// 获取两点间距离
double getDistanceByDirection(const Direction& d0, const Direction& d1) {
	return sqrt(pow((d0.i - d1.i), 2) + pow((d0.j - d1.j), 2) + pow((d0.k - d1.k), 2));
};
// 获取点p关于面s的对称点pn
Point* getSymmetricPoint (const Surface& s, const Point& p) {
	double a = s.getA();
	double b = s.getB();
	double c = s.getC();
	double d = s.getD();
	
	if (a ==0 && b == 0 && c == 0 || s.isPointOn(p)) {
	    return NULL;
	} else {
		double x0 = p.x;
	    double y0 = p.y;
	    double z0 = p.z;
		double t = -(a * x0 + b* y0 + c * z0 + d) / (a * a + b * b + c * c);

		double x1 = a * t + x0;
		double y1 = b * t + y0;
		double z1 = c * t + z0;
		double x = 2 * x1 - x0;
		double y = 2 * y1 - y0;
		double z = 2 * z1 - z0;
		Point *ps = new Point(x, y, z);
		return ps;
	}
};
// 获取两点pa、pb连线关于平面s的交点p 
Point* getReflectPoint(const Surface& s, const Point& pa, const Point& pb) {
    double a = s.getA();
	double b = s.getB();
	double c = s.getC();
	double d = s.getD();

	if (a ==0 && b == 0 && c == 0) {
	    return NULL;
	} else {
		double x0 = pa.x;
    	double y0 = pa.y;
	    double z0 = pa.z;
		double x1 = pb.x;
		double y1 = pb.y;
		double z1 = pb.z;
		double i = x0 - x1;
		double j = y0 - y1;
		double k = z0 - z1;
		if (i * a + j * b + k * c == 0) {
		    return NULL;
		} else {
			double t = -(a * x0 + b * y0 + c * z0 + d) / (a * i + b * j + c * k);
		    double x = i * t + x0;
			double y = j * t + y0;
			double z = k * t + z0;
			Point *p = new Point(x, y, z);
			if (!s.isPointOn(*p)) {
				return NULL;
			} else {
	            return p;
			}
		}
	}
};
Reflection* getReflection(const Surface& s, const Point& pt, const Point& pr) {
	const Point* symmetricPoint = &pt;
	if (symmetricPoint != NULL) {
	    Point* reflectPoint = getReflectPoint(s, *symmetricPoint, pr);
		if (reflectPoint != NULL) {
			double length = getDistance(pr, *reflectPoint);
			Direction direction(pr.x - reflectPoint->x, pr.y - reflectPoint->y, pr.z - reflectPoint->z);
			direction = getUnitDirection(direction);
			Reflection* reflection = new Reflection(length, *reflectPoint, pt, pr, s, direction);
			reflection->init();
			return reflection;
		} else {
		    return NULL;
		}
	} else {
	    return NULL;
	}
};
// 多段反射中第一段
Reflection* getFirstReflection(const Point& reflectPoint, const Point& pr, const Antenna& a) {
		double length = getDistance(pr, reflectPoint);
		Direction direction(pr.x - reflectPoint.x, pr.y - reflectPoint.y, pr.z - reflectPoint.z);
		direction = getUnitDirection(direction);

		Direction aDirection = a.getDirection();
		double aAmplitude = a.getAmplitude();
		Direction aAmplitudeDirection = a.getAmplitudeDirection();
	//	Direction h = getScalarProduct(direction, aDirection); 
	//	Direction v = getScalarProduct(h, direction);
		Direction dan = getScalarProduct(aAmplitudeDirection, direction);
		Direction v = getScalarProduct(direction, dan);
		if (v * aAmplitudeDirection < 0) {
		    v = -v;
		}
		Direction h(1,0,0);
		// TODO:correct?
	//	double hAmplitude = h * aAmplitudeDirection * aAmplitude;
		double vAmplitude = v * aAmplitudeDirection * aAmplitude;

		Reflection* reflection = new Reflection(length, reflectPoint, pr, direction);
	//	reflection->setHAmplitude(hAmplitude);
		reflection->setHAmplitude(0);
		reflection->setVAmplitude(vAmplitude);
	//	reflection->setH(h);
		reflection->setH(h);
		reflection->setV(v);
		reflection->setReflectAngle(0);

		return reflection;
};

double getAngleByVectors(const Direction& d0, const Direction& d1) {
	Direction da = getUnitDirection(d0);
	Direction db = getUnitDirection(d1);
	double v = da.i * db.i + da.j * db.j + da.k * db.k;
    double angle = acos(v);
	return angle;
}
double calculateReflectAngle(const Direction& d0, const Direction& d1) {
	double v = d0.i * d1.i + d0.j * d1.j + d0.k * d1.k;
	double angle;
	if (v < 0) {
		Direction d2(-d0.i, -d0.j, -d0.k);
		angle = getAngleByVectors(d2, d1);
	} else {
	      angle = getAngleByVectors(d0, d1);
	}
    return angle;
}
Direction getScalarProduct(const Direction& d0, const Direction& d1) {
	double i = d0.j * d1.k - d0.k * d1.j;
	double j = d0.k * d1.i - d0.i * d1.k;
	double k = d0.i * d1.j - d0.j * d1.i;
	Direction d(i, j, k); 
	d = getUnitDirection(d);
	return d;
}

Point* calculateIntersectPoint(Direction& dLine, Direction& nPlane, Point& pLine, Point& pPlane) {
	double planeD = pPlane.calculateD(nPlane);
	double t = -(pLine * nPlane + planeD) / (dLine * nPlane);
	Point* ptr = new Point(pLine + dLine * t);
	return ptr;
}

// Point 
Point Point::getSymmetricPoint(const Surface& s) {
	double a = s.getA();
	double b = s.getB();
	double c = s.getC();
	double d = s.getD();
	Point p0(this->x, this->y, this->z);
	if (a ==0 && b == 0 && c == 0 || s.isPointOn(p0)) {
	    return Point(0, 0, 0);
	} else {
		double x0 = this->x;
	    double y0 = this->y;
	    double z0 = this->z;
		double t = -(a * x0 + b* y0 + c * z0 + d) / (a * a + b * b + c * c);

		double x1 = a * t + x0;
		double y1 = b * t + y0;
		double z1 = c * t + z0;
		double x = 2 * x1 - x0;
		double y = 2 * y1 - y0;
		double z = 2 * z1 - z0;
		Point p(x, y, z);
		return p;
	}
}
Direction Point::operator-(Point& p) {
	double i = this->x - p.x;
	double j = this->y - p.y;
	double k = this->z - p.z;
	return Direction(i, j, k);	
}
Direction Point::operator+(Point& p) {
	double i = this->x + p.x;
	double j = this->y + p.y;
	double k = this->z + p.z;
	return Direction(i, j, k);	
}
Point Point::operator+(Direction& d) {
	double x = this->x + d.i;
	double y = this->y + d.j;
	double z = this->z + d.k;
	return Point(x, y, z);	
}
double Point::operator*(Direction& d) {
	double x = this->x * d.i;
	double y = this->y * d.j;
	double z = this->z * d.k;
	return (x + y + z);	
}
Point Point::operator*(double m) {
	double x = this->x * m;
	double y = this->y * m;
	double z = this->z * m;
	return Point(x, y, z);	
}
double Point::calculateD(Direction& d) {
	return -(this->operator*(d));
}
// Direction
Direction Direction::operator+(Direction& d) {
	double i = this->i + d.i;
	double j = this->j + d.j;
	double k = this->k + d.k;
	return Direction(i, j, k);
}
Direction Direction::operator-(Direction& d) {
	double i = this->i - d.i;
	double j = this->j - d.j;
	double k = this->k - d.k;
	return Direction(i, j, k);	
}
Direction Direction::operator-() {
	double i = -this->i;
	double j = -this->j;
	double k = -this->k;
	return Direction(i, j, k);	
}
double Direction::operator*(Direction& d) {
	double i = this->i * d.i;
	double j = this->j * d.j;
	double k = this->k * d.k;
	return (i + j + k);
}
Direction Direction::operator*(double module) {
	double i = this->i * module;
	double j = this->j * module;
	double k = this->k * module;
	return Direction(i, j, k);
}
Direction Direction::operator^(Direction& d) {
	double i = this->j * d.k - this->k * d.j;
	double j = this->i * d.k - this->k * d.i;
	double k = this->i * d.j - this->j * d.i;
	return Direction(i, j, k);
}

double Direction::getModule() {
	double module = sqrt(pow(this->i, 2) + pow(this->j, 2) + pow(this->k, 2));
	return module;
}
Direction Direction::getUnitDirection() {
	double l = sqrt(pow(this->i, 2) + pow(this->j, 2) + pow(this->k, 2));
	if (l != 0) {
	    Direction unitD(this->i/l, this->j/l, this->k/l);
	    return unitD;
	} else {
		Direction unitD(0, 0, 0);
	    return unitD;
	}
}
Direction Direction::getSymmDirect(const Surface& s) {
	Point p0(0, 0, 0);
	Point p1(this->i, this->j, this->k);
	Point ps0 = p0.getSymmetricPoint(s);
	Point ps1 = p1.getSymmetricPoint(s);
	Direction d = ps1 - ps0;
	return d;
}
Direction Direction::getRelDirectOnReflect(const vector<Surface>& surfaces) {
	Direction d(this->i, this->j, this->k);
	for (int n = surfaces.size() - 1; n >= 0 ; n--) {
		d = d.getSymmDirect(surfaces[n]);
	}
	return d;
}
Direction getUnitDirection(const Direction& d) {
	double l = sqrt(pow(d.i, 2) + pow(d.j, 2) + pow(d.k, 2));
	if (l != 0) {
		Direction unitD(d.i/l, d.j/l, d.k/l);
		return unitD;
	} else {
		Direction unitD(0, 0, 0);
		return unitD;
	}
}
// Surface
double Surface::getA() const {
	return this->a;
}
double Surface::getB() const {
	return this->b;
}
double Surface::getC() const {
	return this->c;
}
double Surface::getD() const {
	return this->d;
}
void Surface::calculateEquation() {
	Direction d10 = this->p1 - this->p0;
	Direction d12 = this->p1 - this->p2;
	Direction dn = d10 ^ d12;
	this->a = dn.i;
	this->b = dn.j;
	this->c = dn.k;
	this->d = -(this->p1 * dn);
	/*
	double x0 = this->p0.x;
	double y0 = this->p0.y;
	double z0 = this->p0.z;
	double x1 = this->p1.x;
	double y1 = this->p1.y;
	double z1 = this->p1.z;
	double x2 = this->p2.x;
	double y2 = this->p2.y;
	double z2 = this->p2.z;
	*/
	/* 平面垂直于xOy
	// 左手坐标系,建筑物垂直于xOz
	this->a = z1 - z0;
	this->b = 0;
	this->c = x0 - x1;
	this->d = z0 * (x1 - x0) - x0 * (z1 - z0);
	*/
	// 论文中的坐标系,建筑物垂直于xOy
	/*
	this->a = y1 - y0;
	this->b = x0 - x1;
	this->c = 0;
	this->d = y0 * (x1 - x0) - x0 * (y1 - y0);
	*/
}
void Surface::calculateVector() {
	Direction d(this->a, this->b, this->c);
	this->nVector = getUnitDirection(d);
}
void Surface::init() {
	this->calculateEquation();
	this->calculateVector();
} 
Direction Surface::getNVector() const {
	return this->nVector;
}
Material Surface::getMaterial() const {
	return this->material;
}
void Surface::display(int space) {
	cout<<"p0:";
	this->p0.display();
	cout<<"p1:";
	this->p1.display();
	cout<<"equation:"<<this->a<<"x+"<<this->b<<"y+"<<this->c<<"z+"<<this->d<<"=0"<<endl;
	this->material.display();
}
void Surface::displayExcel() {
	this->p0.displayExcel();
	this->p1.displayExcel();
	this->material.displayExcel();
	cout<<endl;
}
bool Surface::isPointOn(const Point& p) const{
	double x0 = p0.x;
	double y0 = p0.y;
	double z0 = p0.z;
	double x1 = p1.x;
	double y1 = p1.y;
	double z1 = p1.z;
	if ((p.x < x0 && p.x < x1) || (p.x > x0 && p.x > x1)) {
		return false;
	} else if ((p.z < z0 && p.z < z1) || (p.z > z0 && p.z > z1)) {
	    return false;
	} else if ((p.y < y0 && p.y < y1) || (p.y > y0 && p.y > y1)) {
		return false;
	} else {
	    return true;
	}
};
// Antenna
Direction Antenna::getDirection() const {
	return this->direction;
}
Direction Antenna::getRelativePosition() const {
	return this->relativePosition;
}
Direction Antenna::getAmplitudeDirection() const {
	return this->amplitudeDirection;
}
double Antenna::getAmplitude() const {
	return this->amplitude;
}
void Antenna::display(int space) {
	cout<<"direction:";
	this->direction.display();
	cout<<"relative position:";
	this->relativePosition.display();
	cout<<"amplitude:"<<this->amplitude;
	this->amplitudeDirection.display();
}
void Antenna::displayExcel() {
	this->direction.displayExcel();
	this->amplitudeDirection.displayExcel();
	this->relativePosition.displayExcel();
	cout<<this->amplitude<<"\t";
	cout<<endl;
}
// Vehicle


Point Vehicle::getP() const{
    return p;
}
void Vehicle::displayVehichle() {
	cout<<"  location:";
	this->p.display();
	cout<<"  velocity:"<<this->velocity;
	this->direction.display();
}
void Vehicle::displayVehichleExcel() {
	this->p.displayExcel();
	this->direction.displayExcel();
	cout<<this->velocity;
	cout<<endl;
}
// Path
double Path::getTotalLength() const{
	return this->totalLength;
}
void Path::calculateIr() {
	this->ir[0] = cos(this->vPhaseShift) * this->amplitudeReceive[0];
	this->ir[1] = cos(this->hPhaseShift) * this->amplitudeReceive[1];
}
void Path::init() {
	// 有待确认，百度百科电磁波的多普勒是这么计算的，但论文和书中都是用的第二种，暂用书中的方法

	// 第一种
	/*double v = this->relativeVelocity;
	double a = this->relativeAngle;
	this->frequency = sqrt((C + v) * (C - v) / pow((C - v * cos(a)), 2)) * F;
	this->waveLength = C / this->frequency;
	this->delayTime = this->totalLength / C;
	this->vDoppler = v * cos(a);
	*/
	// 第二种
	
	this->frequency = F + (double)this->vDoppler / C * F;
	this->waveLength = WAVE_LENGTH;
	this->delayTime = this->totalLength / (C + this->vDoppler);
	this->vPhaseShift = this->initPhase[0];
	this->hPhaseShift = this->initPhase[1];
}
// TODO:expect MIMO, SISO now
void Path::calculateAmplitudeReceive(const vector<Antenna>& ras) {
	Antenna a = ras[0];
	int size = this->reflections.size();
	Reflection r = this->reflections[size - 1];
	Direction h = r.getH();
	Direction v = r.getV();
	double hAmplitude = r.getHAmplitude();
	double vAmplitude = r.getVAmplitude();
	// TODO:相移
	double vAmplitudeReceive = (h * hAmplitude + v * vAmplitude) * a.getVDirection();
	double hAmplitudeReceive = (h * hAmplitude + v * vAmplitude) * a.getHDirection();
	this->setAmplitudeReceive(vAmplitudeReceive, hAmplitudeReceive);
}
int Path::getNumOfReflect() const {
	return this->numOfReflect;
}
vector<Reflection> Path::getReflections() {
	return this->reflections;
}
/*
// 获取两点间距离
double getDistance(const Point& p0, const Point& p1) {
	return sqrt(pow((p0.x - p1.x), 2) + pow((p0.y - p1.y), 2) + pow((p0.z - p1.z), 2));
};
// 获取两点间距离
double getDistanceByDirection(const Direction& d0, const Direction& d1) {
	return sqrt(pow((d0.i - d1.i), 2) + pow((d0.j - d1.j), 2) + pow((d0.k - d1.k), 2));
};

// 获取点p关于面s的对称点pn
Point* getSymmetricPoint (const Surface& s, const Point& p) {
	double a = s.getA();
	double b = s.getB();
	double c = s.getC();
	double d = s.getD();
	
	if (a ==0 && b == 0 && c == 0 || s.isPointOn(p)) {
	    return NULL;
	} else {
		double x0 = p.x;
	    double y0 = p.y;
	    double z0 = p.z;
		double t = -(a * x0 + b* y0 + c * z0 + d) / (a * a + b * b + c * c);

		double x1 = a * t + x0;
		double y1 = b * t + y0;
		double z1 = c * t + z0;
		double x = 2 * x1 - x0;
		double y = 2 * y1 - y0;
		double z = 2 * z1 - z0;
		Point *ps = new Point(x, y, z);
		return ps;
	}
};

// 获取两点pa、pb连线关于平面s的交点p 
Point* getReflectPoint(const Surface& s, const Point& pa, const Point& pb) {
    double a = s.getA();
	double b = s.getB();
	double c = s.getC();
	double d = s.getD();

	if (a ==0 && b == 0 && c == 0) {
	    return NULL;
	} else {
		double x0 = pa.x;
    	double y0 = pa.y;
	    double z0 = pa.z;
		double x1 = pb.x;
		double y1 = pb.y;
		double z1 = pb.z;
		double i = x0 - x1;
		double j = y0 - y1;
		double k = z0 - z1;
		if (i * a + j * b + k * c == 0) {
		    return NULL;
		} else {
			double t = -(a * x0 + b * y0 + c * z0 + d) / (a * i + b * j + c * k);
		    double x = i * t + x0;
			double y = j * t + y0;
			double z = k * t + z0;
			Point *p = new Point(x, y, z);
			if (!s.isPointOn(*p)) {
				return NULL;
			} else {
	            return p;
			}
		}
	}
};

Reflection* getReflection(const Surface& s, const Point& pt, const Point& pr) {
	const Point* symmetricPoint = &pt;
	if (symmetricPoint != NULL) {
	    Point* reflectPoint = getReflectPoint(s, *symmetricPoint, pr);
		if (reflectPoint != NULL) {
			double length = getDistance(pr, *reflectPoint);
			Direction direction(pr.x - reflectPoint->x, pr.y - reflectPoint->y, pr.z - reflectPoint->z);
			direction = getUnitDirection(direction);
			Reflection* reflection = new Reflection(length, *reflectPoint, pt, pr, s, direction);
			reflection->init();
			// cout<<"yes"<<endl;
			return reflection;
		} else {
		    return NULL;
		}
	} else {
	    return NULL;
	}
};

// 多段反射中第一段
Reflection* getFirstReflection(const Point& reflectPoint, const Point& pr, const Antenna& a) {
		double length = getDistance(pr, reflectPoint);
		Direction direction(pr.x - reflectPoint.x, pr.y - reflectPoint.y, pr.z - reflectPoint.z);
		direction = getUnitDirection(direction);

		Direction aDirection = a.getDirection();
		double aAmplitude = a.getAmplitude();
		Direction aAmplitudeDirection = a.getAmplitudeDirection();
		Direction h = getScalarProduct(direction, aDirection);
		Direction v = getScalarProduct(h, direction);
		double hAmplitude = h * aAmplitudeDirection * aAmplitude;
		double vAmplitude = v * aAmplitudeDirection * aAmplitude;

		Reflection* reflection = new Reflection(length, reflectPoint, pr, direction);
		reflection->setHAmplitude(hAmplitude);
		reflection->setVAmplitude(vAmplitude);
		reflection->setH(h);
		reflection->setV(v);
		reflection->setReflectAngle(0);

		return reflection;
};
*/

// 构建单条完整传播路径()
// @pt:发射天线点
// @pr:接收天线点
// @surfaces:假定信号传播路径所经反射面的序列
// return: 若传播路径成立，返回Path对象；否则返回null
// Model
bool Model::getReflectPath(const Point& pt, const Point& pr, const vector<Surface>& surfaces) {
	
	vector<Point> symmetricPoints;
	vector<Point> reflectPoints;
	vector<Reflection> reflections;
	vector<Surface>::const_iterator iterSurfaces = surfaces.begin();
    vector<Surface>::const_reverse_iterator rIterSurfaces = surfaces.rbegin();
//	vector<Point>::const_reverse_iterator rIterSymmPoint = symmetricPoints.rbegin();
	vector<Reflection>::iterator iterReflection;
	double totalLength = 0;
	// 迭代计算发射车的镜像（对称）点
	symmetricPoints.push_back(pt);
	for (; iterSurfaces < surfaces.end(); iterSurfaces++) {
		Point* p = getSymmetricPoint(*iterSurfaces, symmetricPoints.back());
	    if (p != NULL) {
	    	symmetricPoints.push_back(*p);
			delete p;
	    } else {
			delete p;
	        return false;
	    }
	}

	// 迭代计算反射（入射）点，同时建立反射对象
	reflectPoints.push_back(pr);
	for (int i = surfaces.size() - 1; i >= 0; i--) {
		Reflection* reflection = getReflection(surfaces[i], symmetricPoints[i+1], reflectPoints.back());
		if (reflection != NULL) {
			Point* reflectPoint = getReflectPoint(surfaces[i], symmetricPoints[i+1], reflectPoints.back());
			reflectPoints.push_back(*reflectPoint);
			iterReflection = reflections.begin();
			reflections.insert(iterReflection, *reflection);
			totalLength += reflection->getLength();
	    } else {
	        return NULL;
	    }
	}

	// 建立第一段反射对象
	Reflection* reflection = getFirstReflection(pt, reflectPoints.back(), this->tAntennas[0]);
	totalLength += reflection->getLength();
	iterReflection = reflections.begin();
	reflections.insert(iterReflection, *reflection);

	// 计算多普勒、振幅衰减
	double vPhaseShift = 0;
	double hPhaseShift = 0;
	unsigned size = reflections.size();
	for (unsigned j = 1; j < size; j++) {
	    Reflection r1 = reflections[j - 1];
		Reflection r2 = reflections[j];
		Direction rd1 = r1.getDirection();
		Direction rn2 = r2.getV();
		// 振幅衰落
		Direction v1 = r1.getV();
		Direction h1 = r1.getH();
		Direction v2 = r2.getV();
		Direction h2 = r2.getH();
		h1 * h2;
		//double hAmplitude = (r1.getH() * h + r1.getV() * h) * r1.getHAmplitude() * r2.getAmplitudeFadeH();
		//double vAmplitude = (r1.getV() * r2.getV() + r1.getH() * r2.getV()) * r1.getVAmplitude() * r2.getAmplitudeFadeV();
		double hAmplitude = (h1 * r1.getHAmplitude() + v1 * r1.getVAmplitude()) * h2 * r2.getAmplitudeFadeH();
		// 注意差别
		double vAmplitude = (h1 * r1.getHAmplitude() + v1 * r1.getVAmplitude()) * (rn2 ^ rd1) * r2.getAmplitudeFadeV();
		// 相移,配合计算振幅
		double BrewsterAngle = r2.getSurface().getMaterial().getBrewsterAngle();
		
		reflections[j].setVPhaseShift(PI);
		vPhaseShift += PI;
		if (vAmplitude < 0) {
			//reflections[i].setV(-v2);
			vAmplitude = -vAmplitude;
		} else {
			reflections[j].setV(-v2);
		}
		if (reflections[j].getReflectAngle() > BrewsterAngle) {
		    reflections[j].setHPhaseShift(PI);
			hPhaseShift += PI;
			if (hAmplitude < 0) {
			    //reflections[i].setH(-h2);
			    hAmplitude = -hAmplitude;
		    }
		} else if (hAmplitude < 0) {
			reflections[j].setH(-h2);
			hAmplitude = -hAmplitude;
		}
		reflections[j].setHAmplitude(hAmplitude);
		reflections[j].setVAmplitude(vAmplitude);	
	}

	int numberOfReflect = surfaces.size();

	// 多普勒
	Vehicle tx = this->getTransmitter();
	Vehicle rx = this->getReceiver();
	Direction txDirection = tx.getDirection();
	Direction rxDirection = rx.getDirection();
	Direction v = txDirection * tx.getVelocity() - rxDirection.getRelDirectOnReflect(surfaces) * rx.getVelocity();
	Direction vUnit = v.getUnitDirection();
	double relativeAngle = getAngleByVectors(vUnit, reflections[0].getDirection());
	double vt = txDirection * reflections[0].getDirection() * tx.getVelocity();
	double vr = rxDirection * reflections[size - 1].getDirection() * rx.getVelocity();
	double vDoppler = vt - vr;

	// TODO:
	// 
	//double f = sqrt((1 + vDoppler / C) / (1 - vDoppler / C)) * F;
	//double waveLength = C / f;


	
	Path* path = new Path(totalLength, numberOfReflect, reflections);
	//path->setHPhaseShift(hPhaseShift);
	//path->setVPhaseShift(vPhaseShift);
	path->calculateAmplitudeReceive(this->rAntennas);
	//path->setHAmplitude(reflections[size - 1].getHAmplitude());
	//path->setVAmplitude(reflections[size - 1].getVAmplitude());
	//path->setV(reflections[size - 1].getV());
	//path->setH(reflections[size - 1].getH());
	// 初始相位都为0，振幅极化方向已做调整
	path->setInitPhase(0, 0);
	path->setVDoppler(vDoppler);
	path->setRelativeAnge(relativeAngle);
	path->setRelativeVelocity(v.getModule());
	path->setRelVelDirect(vUnit);
	path->init();
	//path->setFrequency(f);
	//path->setWaveLength(waveLength);
	path->calculateFDopplerShift();
	path->calculatePhaseReceive();

	if (path != NULL) {
		insertPath(*path);
		delete path;
		return true;
	}
	
	return false;
	//
};
bool Model::calculateLOSPath() {
	Reflection* reflection = getFirstReflection(this->transmitter.getP(), this->receiver.getP(), this->tAntennas[0]);
	vector<Reflection> reflections;
	reflections.push_back(*reflection);

	Vehicle tx = this->getTransmitter();
	Vehicle rx = this->getReceiver();
	Direction txDirection = tx.getDirection();
	Direction rxDirection = rx.getDirection();
	Direction v = txDirection * tx.getVelocity() - rxDirection * rx.getVelocity();
	Direction vUnit = getUnitDirection(v);
	double relativeAngle = getAngleByVectors(vUnit, reflections[0].getDirection());
	double vt = tx.getDirection() * reflections[0].getDirection() * tx.getVelocity();
	double vr = rx.getDirection() * reflections[0].getDirection() * rx.getVelocity();
	double vDoppler = vt - vr;

	//TODO:
	//double f = sqrt((1 + vDoppler / C) / (1 - vDoppler / C)) * F;
	//double waveLength = C / f;

	Path* path = new Path(reflection->getLength(), 0, reflections);
	path->calculateAmplitudeReceive(this->rAntennas);
	//path->setHAmplitude(reflections[0].getHAmplitude());
	//path->setVAmplitude(reflections[0].getVAmplitude());
	//path->setV(reflections[0].getV());
	//path->setH(reflections[0].getH());
	path->setInitPhase(0, 0);
	path->setVDoppler(vDoppler);
	path->setRelativeAnge(relativeAngle);
	path->setRelativeVelocity(v.getModule());
	path->setRelVelDirect(vUnit);
	path->init();
	//path->setFrequency(f);
	//path->setWaveLength(waveLength);
	path->calculateFDopplerShift();
	path->calculatePhaseReceive();
	insertPath(*path);
	delete path;
	// TODO:return 
	return true;
}
bool Model::calculateReflectPaths() {
	unsigned i = 0;
	unsigned j = 0;
    unsigned k = 0;
	switch (NUM_OF_REFLECTS) {
	    case 1:
            for (i = 0; i < this->surfaces.size(); i++) {
	            vector<Surface> s;
		        s.push_back(this->surfaces[i]);
				getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
	        }
			break;
	    case 2:
			for (i = 0; i < this->surfaces.size(); i++) {
	            vector<Surface> s;
		        s.push_back(this->surfaces[i]);
		        getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
		        
	        }
			for (i = 0; i < this->surfaces.size(); i++) {
		        for (j = 0; j < this->surfaces.size(); j++) {
					if (i == j) {
					    continue;
					}
	                vector<Surface> s;
		            s.push_back(this->surfaces[i]);
			        s.push_back(this->surfaces[j]);
		            getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
					
		        }
	        }
			break;
	    case 3:
			for (i = 0; i < this->surfaces.size(); i++) {
	            vector<Surface> s;
		        s.push_back(this->surfaces[i]);
		        getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
		        
	        }
			for (i = 0; i < this->surfaces.size(); i++) {
		        for (j = 0; j < this->surfaces.size(); j++) {
					if (i == j) {
					    continue;
					}
	                vector<Surface> s;
		            s.push_back(this->surfaces[i]);
			        s.push_back(this->surfaces[j]);
		            getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
					
		        }
	        }
			for (i = 0; i < this->surfaces.size(); i++) {
		        for (j = 0; j < this->surfaces.size(); j++) {
					if (i == j) {
						continue;
					}
					for (unsigned k = 0; k < this->surfaces.size(); k++) {
						if (j == k) {
							continue;
						}
	                    vector<Surface> s;
		                s.push_back(this->surfaces[i]);
			            s.push_back(this->surfaces[j]);
						s.push_back(this->surfaces[k]);
		                getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
		                
					}
		        }
	        }
			break;
		default:
			for (i = 0; i < this->surfaces.size(); i++) {
	            vector<Surface> s;
		        s.push_back(this->surfaces[i]);
                getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
		        
	        }
			break;
	}
	// TODO:return 
	return true;
}
bool Model::calculateStrongestPaths() {
	this->calculateLOSPath();
	this->calculateReflectPaths();
	vector<Path> paths = this->strongestPaths;
	if (this->strongestPaths.size() > NUM_OF_PATHS) {
		this->strongestPaths.erase(strongestPaths.begin() + NUM_OF_PATHS, strongestPaths.end());
	} 
	// TODO:return 
	return true;
};
void Model::insertPath(const Path& newPath) {
	if (strongestPaths.empty()) { 
		strongestPaths.push_back(newPath);
	} else {
		vector<Path>::reverse_iterator rIter;
		for (rIter = strongestPaths.rbegin(); rIter < strongestPaths.rend(); ++rIter) {
			if (rIter->getTotalLength() < newPath.getTotalLength()) {
				strongestPaths.insert(rIter.base(), newPath);
				break;
			}
		}		
	}
};
bool Model::calculateImpulseResponse(double t) {
	vector<Path>::iterator iterPath = this->strongestPaths.begin();
	double baseTao = iterPath->getDelayTime();
	for (; iterPath < this->strongestPaths.end(); iterPath++) {
		//iterPath->calculateIr();
		
		double tao = iterPath->getDelayTime();
		double tt = t - (tao - baseTao);
		// 两倍波长
		//double time = 1 / F * 200000000000000000000 + (tao - baseTao);
		//if (tt >= 0 && time >= tt) {
		if (tt >= 0) {
			// TODO:not sure
			double phaseShift = 2 * PI / iterPath->getWaveLength() * C * tt;
			phaseShift += 2 * PI / iterPath->getWaveLength() * iterPath->getVDoppler() * tt;
			//double vInitPhase = iterPath->getVInitPhase();
			//double hInitPhase = iterPath->getHInitPhase();
			iterPath->setVPhaseShift(phaseShift);
			iterPath->setHPhaseShift(phaseShift);
		} else {
			iterPath->setVPhaseShift(PI / 2);
			iterPath->setHPhaseShift(PI / 2);
		   
		}
		iterPath->calculateIr();
	}
	// TODO: return
	return true;
}
// TODO:unsed, solved in getReflectPath()
bool Model::calculateAmplitude() {
	
	vector<Path>::iterator iterPaths = this->strongestPaths.begin();
	for (unsigned i = 0; i < this->strongestPaths.size(); i++) {	

		for(unsigned j = 1; j < this->strongestPaths[i].getReflections().size(); j++) {
			Reflection r1 = this->strongestPaths[i].getReflections()[j - 1];
			Reflection r2 = this->strongestPaths[i].getReflections()[j];
			double hAmplitude = r1.getH() * r2.getH() * r1.getHAmplitude() * r2.getAmplitudeFadeH();
			double vAmplitude = r1.getV() * r2.getV() * r1.getVAmplitude() * r2.getAmplitudeFadeV();
			this->strongestPaths[i].getReflections()[j].setHAmplitude(hAmplitude);
			this->strongestPaths[i].getReflections()[j].setVAmplitude(vAmplitude);
			//this->strongestPaths[i].getReflections()[j].calculateAmplitudeFadeH();
			//this->strongestPaths[i].getReflections()[j].calculateAmplitudeFadeV();
		}
	}
	return true;
}
vector<Path> Model::getStrongestPaths() const{
	return this->strongestPaths;
}

void Model::displayPathIR() {
	unsigned i;
	for(i = 0; i < this->strongestPaths.size(); i++) {	
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		Path path = this->strongestPaths.at(i);
		path.displayVir();
		
	}
	cout<<endl;
	for(i = 0; i < this->strongestPaths.size(); i++) {
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		Path path = this->strongestPaths.at(i);
		path.displayHir();
		
	}
	cout<<endl;
}

void Model::displayPathVIR() {
	for(unsigned i = 0; i < this->strongestPaths.size(); i++) {	
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		Path path = this->strongestPaths.at(i);
		path.displayVir();
	}
	cout<<endl;
}
void Model::displayPathHIR() {
	for(unsigned i = 0; i < this->strongestPaths.size(); i++) {	
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		Path path = this->strongestPaths.at(i);
		path.displayHir();
		
	}
	cout<<endl;
}
void Model::displayPath() {
	cout<<"num of paths:"<<this->strongestPaths.size()<<endl;
	for(unsigned i = 0; i < this->strongestPaths.size(); i++) {
		Path path = this->strongestPaths.at(i);
		cout<<i+1<<"th path:"<<endl;
		cout.setf(ios::fixed);
		cout.precision(10);
		
	    cout<<"  total length:"<<this->strongestPaths.at(i).getTotalLength()<<endl;
		cout<<"  delay time:"<<this->strongestPaths.at(i).getDelayTime()<<endl;
		cout<<"  frequency:"<<path.getFrequency()<<endl;
		cout<<"  frequency shift:"<<path.getFDopplerShift()<<endl;
		cout<<"  wavelength:"<<path.getWaveLength()<<endl;
		
		cout.unsetf(ios_base::fixed);

		Direction tDirection = path.getReflections().begin()->getDirection();
		Direction rDirection = path.getReflections().at(path.getNumOfReflect()).getDirection();
		cout<<"  transmit direction:("<<tDirection.i<<","<<tDirection.j<<","<<tDirection.k<<")"<<endl;
		cout<<"  receive  direction:("<<rDirection.i<<","<<rDirection.j<<","<<rDirection.k<<")"<<endl;
		cout<<"  h:("<<path.getH().i<<","<<path.getH().j<<","<<path.getH().k<<")"<<path.getHAmplitude()<<endl;
		cout<<"  v:("<<path.getV().i<<","<<path.getV().j<<","<<path.getV().k<<")"<<path.getVAmplitude()<<endl;
		cout<<"  h shift:"<<path.getHPhaseShift()<<endl;
		cout<<"  v shift:"<<path.getVPhaseShift()<<endl;

		path.displayIR();

		cout<<"  num of reflect :"<<this->strongestPaths.at(i).getNumOfReflect()<<endl;
		cout<<"  reflections:"<<"num:"<<this->strongestPaths.at(i).getReflections().size()<<endl;
		
		for(unsigned j = 0; j <= this->strongestPaths.at(i).getReflections().size()-1 ; j++) {
			cout<<"   "<<(j + 1)<<"th reflection:"<<endl;
			Reflection r = this->strongestPaths.at(i).getReflections().at(j);
		    Direction d = r.getDirection();
			Point p = r.getReflectPoint();
			Surface s = r.getSurface();
			Direction nVector = s.getNVector();
			double length = r.getLength();
			cout<<"    direction: ("<<d.i<<","<<d.j<<","<<d.k<<")"<<endl;
			cout<<"    reflect point:("<<p.x<<","<<p.y<<","<<p.z<<")"<<endl;

			if (j != 0) {
				cout<<"    n:("<<nVector.i<<","<<nVector.j<<","<<nVector.k<<")"<<endl;
			}
			cout<<"    h:("<<r.getH().i<<","<<r.getH().j<<","<<r.getH().k<<")"<<r.getHAmplitude()<<endl;
			cout<<"    v:("<<r.getV().i<<","<<r.getV().j<<","<<r.getV().k<<")"<<r.getVAmplitude()<<endl;
			cout<<"    h fade:"<<r.getAmplitudeFadeH()<<endl;
			cout<<"    v fade:"<<r.getAmplitudeFadeV()<<endl;
			cout<<"    reflect angle:"<<r.getReflectAngle()<<endl;
			cout<<"    length:"<<length<<endl;
		}
		
	}
}
// TODO:unsed
void Model::displayIR() {
}
void Model::displayModel() {
	cout<<"Tx:"<<endl;
	this->transmitter.displayVehichle();
	cout<<"Rx:"<<endl;
	this->receiver.displayVehichle();
    cout<<"Surfaces:"<<this->surfaces.size()<<endl;
	for (unsigned i = 0; i < this->surfaces.size(); i++) {
		cout<<"  "<<(i + 1)<<"th surface:"<<endl;
		this->surfaces[i].display(4);
	}
	cout<<"transmit antennas:"<<this->tAntennas.size()<<endl;
	for (unsigned j = 0; j < this->tAntennas.size(); j++) {
		cout<<"  "<<(j + 1)<<"th atenna element:"<<endl;
		this->tAntennas[j].display(4);
	}
} 
void Model::displayModelExcel() {
	cout<<"Input"<<endl;

	cout<<"Vehicles\t"<<"location\t"<<"direction\t"<<"velocity\t"<<endl;
	cout<<"Tx\t";
	this->transmitter.displayVehichleExcel();
	cout<<"Rx\t";
	this->receiver.displayVehichleExcel();

    cout<<"Surfaces\t"<<"p0\t"<<"p1\t"<<"material\t"<<"refractive index\t"<<endl;
	for (unsigned i = 0; i < this->surfaces.size(); i++) {
		cout<<"s"<<(i + 1)<<"\t";
		this->surfaces[i].displayExcel();
	}

	cout<<"transmit antennas\t"<<"direction\t"<<"polarization\t"<<"relative location\t"<<"amplitude(power related)\t"<<endl;
	for (i = 0; i < this->tAntennas.size(); i++) {
		cout<<"ta"<<(i + 1)<<"\t";
		this->tAntennas[i].displayExcel();
	}
	cout<<"recieve antennas\t"<<"direction\t"<<"polarization\t"<<"relative location\t"<<"amplitude(power related)\t"<<endl;
	for (i = 0; i < this->rAntennas.size(); i++) {
		cout<<"ra"<<(i + 1)<<"\t";
		this->rAntennas[i].displayExcel();
	}
} 
void Model::displayMaxDelay() {
	cout<<"Vehicles\t"<<"location\t"<<"direction\t"<<"velocity\t"<<endl;
	cout<<"Tx\t";
	this->transmitter.displayVehichleExcel();
	cout<<"Rx\t";
	this->receiver.displayVehichleExcel();

    cout<<"Surfaces\t"<<"p0\t"<<"p1\t"<<"material\t"<<"refractive index\t"<<endl;
	for (unsigned i = 0; i < this->surfaces.size(); i++) {
		cout<<"s"<<(i + 1)<<"\t";
		this->surfaces[i].displayExcel();
	}
	cout<<"max delay:\t";
	int size = this->strongestPaths.size();
	double firstDelay = this->strongestPaths[0].getDelayTime();
	double lastDelay = this->strongestPaths[size - 1].getDelayTime();
	double maxDelay = lastDelay - firstDelay ;
	cout<<maxDelay<<"s\t";
	cout<<endl;
}

double Reflection::getLength() const {
	return this->length;
};
Point Reflection::getReflectPoint() const {
	return this->reflectPoint;
};
Direction Reflection::getH() const {
	return this->h; 
}
Direction Reflection::getV() const {
	return this->v; 
}
Surface Reflection::getSurface() const {
	return this->surface;
}
Reflection::Reflection(double length, 
		       const Point& reflectPoint, 
			   const Point& startPoint, 
			   const Point& endPoint, 
			   const Surface& surface, 
			   const Direction& direction):
	           length(length),
			   reflectPoint(reflectPoint),
			   startPoint(startPoint),
			   endPoint(endPoint),
			   surface(surface),
			   direction(direction) {
	this->v = getScalarProduct(surface.getNVector(), direction);
	this->h = getScalarProduct(direction, this->v);
	this->reflectAngle = calculateReflectAngle(surface.getNVector(), direction);
	    this->vPhaseShift = 0;
	    this->hPhaseShift = 0;
}
Reflection::Reflection(double length, 
	       const Point& reflectPoint, 
		   const Point& endPoint, 
		   const Direction& direction):
           length(length),
		   reflectPoint(reflectPoint),
		   startPoint(startPoint),
		   endPoint(endPoint),
		   surface(surface),
		   direction(direction) {
			   this->amplitudeFadeV = 1;
			   this->amplitudeFadeH = 1;
			   this->vPhaseShift = 0;
			   this->hPhaseShift = 0;
}
bool Reflection::calculateVH() {
	this->v = getScalarProduct(this->direction, this->surface.getNVector());
	this->h = getScalarProduct(this->direction, this->v);
	return true;
}
bool Reflection::calculateAmplitudeFadeV() {
	double n = this->surface.getMaterial().getN();
	double x = this->reflectAngle;
	double b = sqrt(pow(n, 2) - pow(sin(x), 2));
	double a = cos(x);
	this->amplitudeFadeV = (a - b) / (a + b);
	return false;
}
bool Reflection::calculateAmplitudeFadeH() {
	double n = this->surface.getMaterial().getN();
	double x = this->reflectAngle;
	double b = sqrt(n * n - sin(x) * sin(x));
	double a = cos(x) * pow(n, 2);
	this->amplitudeFadeH =  (a - b) / (a + b);
	return true;
}
void Reflection::init() {
	this->calculateVH();
	this->calculateAmplitudeFadeH();
	this->calculateAmplitudeFadeV();
}
Direction Reflection::getDirection() const {
	return this->direction;
};