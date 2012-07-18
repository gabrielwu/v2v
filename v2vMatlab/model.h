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
// ��
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
// ����
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
// ����
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
	// ��ȡ���߷���
	Direction getDirection() const;
	// ��ȡ����������꣨������������ߣ�
	Direction getRelativePosition() const;	
	// ��ȡ�������
	Direction getAmplitudeDirection() const;
	// ��ȡ�����С
	double getAmplitude() const;
	// ��ȡ��ֱ��������
	Direction getVDirection() const {
		return this->vDirection;
	};
	// ��ȡˮƽ��������
	Direction getHDirection() const {
		return this->hDirection;
	};
	// ��ʾ������Ϣ
	void display(int space = 0);
	// ��ʾ������Ϣexcel
	void displayExcel();
};
// ����
class Material {
	friend class Surface;
private:
	// ��������ڿ���������ϵ��
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
// ƽ����
class Surface {
	friend class Model;
	friend class Reflection;
private:
	// ƽ�涨λ�㣬����Ϊ���Ϻ�����
    Point p0, p1;
	// ��бƽ�棬����������,���º�����
	Point p2, p3;
    // ���ڱ�ʾƽ�淽��ax+by+cz+d=0
	double a,b,c,d; 
	// ƽ�淨����
	Direction nVector;
	// ���϶��󣬶������ȶ
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
	// ��ʼ������
	void init();
	// ����ƽ�淽��
    void calculateEquation(); 
	// ���㷨����
	void calculateVector();
	double getA() const;
	double getB() const;
	double getC() const;
	double getD() const;
	// �жϵ�p�Ƿ���ƽ�淶Χ
	bool isPointOn(const Point& p) const; 
	// ��÷�����
	Direction getNVector() const;
	// ��ȡ����
	Material getMaterial() const;
	// ��ʾƽ����Ϣ
	void display(int space = 0);
	// ��ʾƽ����Ϣ
	void displayExcel();
};
// ������
class Vehicle {
	friend class Model;
private:
	
	// �н�(�ٶ�)����
    Direction direction;
	// ����
    double velocity;
public:
	// ���߲ο���
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

// ������
class Reflection {
	friend class Model;
	friend class Path;
private:
	// ע���Ǵ���ʼ�㵽�����ĳ���
    double length; 
	// �����
    Point reflectPoint;
	// ����ֶ���ʼ��
    Point startPoint;
	// ����ֶ���ֹ��
	Point endPoint;
	// ������
    Surface surface;
	// ����㵽��ֹ���ķ���
    Direction direction; 
	// ���䲨ƽ���ڷ������ڵ������������
	Direction h;
	// ���䲨��ֱ�ڷ������ڵ������������
	Direction v;
	// ���䲨ƽ���ڷ�����������С
	double hAmplitude;
	// ���䲨��ֱ�ڷ�����������С
	double vAmplitude;
	// �������
	Direction amplitudeDireciton;
	// �����С
	double amplitude;
	// ����Ǵ�С
	double reflectAngle;
	// ���䲨��ֱ�ڷ���������˥��ٷֱ�
	double amplitudeFadeV;
	// ���䲨ƽ���ڷ���������˥��ٷֱ�
	double amplitudeFadeH;
	// ���䲨��ֱ�ڷ����������
	double vPhaseShift;
	// ���䲨ƽ���ڷ����������
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


// ����·����
class Path {
	friend class Model;
private:
	// ·���ܳ���
    double totalLength;
	// �������
    int numOfReflect;
	// ����ʱ��
	double delayTime;
	// �����������
    vector<Reflection> reflections;
	// ���䲨ƽ���ڷ������ڵ������������
	Direction h;
	// ���䲨��ֱ�ڷ������ڵ������������
	Direction v;
	// ��ʼ��λ,��ֱ����v��ˮƽ����h[v,h]
	double initPhase[2];
	// ���䲨ƽ���ڷ�����������С
	double hAmplitude;
	// ���䲨��ֱ�ڷ�����������С
	double vAmplitude;
	// ���䲨��ֱ�ڷ����������
	double vPhaseShift;
	// ���䲨ƽ���ڷ����������
	double hPhaseShift;
	// ���ճ�(����)�ͷ��䳵������ٶ�
	double relativeVelocity;
	// ���ճ�(����)�ͷ��䳵������ٶȷ������·����������ļн�
	double relativeAngle;
	// ���ճ�(����)�ͷ��䳵������ٶȷ���
	Direction relVelDirect;
	// ���ճ�(����)�ͷ��䳵������ٶ�����ڴ���·�����ٶ�
	double vDoppler;
	// Ƶ��
	double frequency;
	// ����
	double waveLength;
	// ������Ƶ��
	double fDopplerShift;
	// ��ֱ������յ�����λ
	double vPhasereceive;
	// ˮƽ������յ�����λ
	double hPhasereceive;
	// �����豸�յ������,��ֱ����,ˮƽ����
	double amplitudeReceive[2];
	// �����Ӧ,v��ֱ������hˮƽ����
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

    // ��ȡ·���ܳ���
    double getTotalLength() const;
	int getNumOfReflect() const;
	vector<Reflection> getReflections() ;
	double getDelayTime() {
		return this->delayTime;
	};
};

//����ģ����
class Model{
private:	
	// ���䳵Tx
    Vehicle transmitter;
	// ���ճ�Rx
    Vehicle receiver;
	// ������ǿ��·��
	vector<Path> strongestPaths;
	// ����������
	vector<Antenna> tAntennas;
	// ����������
	vector<Antenna> rAntennas;

	// ����LOS
	bool calculateLOSPath();

	// ���㷴��·��
	bool calculateReflectPaths();
public:
	// �������
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
    // ��ʼ��
    void init();
	// ��ȡģ������̵�7��·����ȷ�н�Ϊ������ǿ�ģ���һ��������
    // return: ���·��
    bool calculateStrongestPaths();

    // ���������������䴫��·��()
    // @pt:�������ߵ�
    // @pr:�������ߵ�
    // @surfaces:�ٶ��źŴ���·�����������������
    // return: ������·������������Path���󣻷��򷵻�null
    bool getReflectPath(const Point& pt, const Point& pr, const vector<Surface>& surfaces);

	// ����·��������
    // @newPath:�¼���Ĵ���·��
    // @paths:ԭ�д���·����
    void insertPath(const Path& newPath);
	
	// �������˥��
	bool calculateAmplitude();

	// ��ȡ������ǿ��·������
	vector<Path> getStrongestPaths() const;

	// ����tʱ�̵��ŵ������Ӧ
	bool calculateImpulseResponse(double t);


	// ��ʾ·��
	void displayPath();

	// ��ʾ·����ˮƽ��ֱ���������������Ӧ
	void displayPathIR();

	// ��ʾ·���Ĵ�ֱ���������������Ӧ
	void displayPathVIR();

	// ��ʾ·����ˮƽ���������������Ӧ
	void displayPathHIR();
	
	// ��ʾ�ŵ�����
	void displayIR();

	// ��ʾ����ģ�Ͳ���
	void displayModel();

	// �����ʾ��excel�еĸ�ʽ
	void displayModelExcel();

	// ��ʾ���ʱ��
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