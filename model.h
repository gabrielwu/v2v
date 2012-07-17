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
using namespace std;
//11111111111111111111222222222222222222222
// ������
class Vehicle {
	friend class Model;
private:
    Direction direction; // �н�(�ٶ�)����
    double velocity; // ����
public:
    Point p; // ���߲ο���
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

// ������
class Reflection {
	friend class Model;
	friend class Path;
	friend class MixPathSegment;
	friend class MixPath;
private:
    double length; // ע���Ǵӷ����㵽��ֹ���ĳ���
    Point reflectPoint; // ������
    Point startPoint; // �����ֶ���ʼ��
	Point endPoint; // �����ֶ���ֹ��
    Surface surface; // ������
    Direction direction; // �����㵽��ֹ�����ķ���
	Direction h; // ���䲨ƽ���ڷ������ڵ�������������
	Direction v; // ���䲨��ֱ�ڷ������ڵ�������������
	double hAmplitude; // ���䲨ƽ���ڷ�������������С
	double vAmplitude; // ���䲨��ֱ�ڷ�������������С
	Direction amplitudeDireciton; // ��������
	double amplitude; // ������С
	double reflectAngle; // �����Ǵ�С
	double amplitudeFadeV; // ���䲨��ֱ�ڷ�����������˥���ٷֱ�
	double amplitudeFadeH; // ���䲨ƽ���ڷ�����������˥���ٷֱ�
	double vPhaseShift; // ���䲨��ֱ�ڷ�����������
	double hPhaseShift; // ���䲨ƽ���ڷ�����������
	double scatterFade; // ɢ������
	double hc; // ƽ���ο��߶�
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
	// �жϴ˶�·���Ƿ����������赲
	bool isBlocked(vector<Surface>& surface);
};


// ����·����
class Path {
	friend class Model;
	friend class MixPathSegment;
	friend class MixPath;
private:
    double totalLength;// ·���ܳ���
    int numOfReflect;// ��������
	double delayTime;// ����ʱ��
    vector<Reflection> reflections;// ������������
	Direction h;// ���䲨ƽ���ڷ������ڵ�������������
	Direction v;// ���䲨��ֱ�ڷ������ڵ�������������
	double initPhase[2];// ��ʼ��λ,��ֱ����v��ˮƽ����h[v,h]
	double hAmplitude;// ���䲨ƽ���ڷ�������������С
	double vAmplitude;// ���䲨��ֱ�ڷ�������������С
	double vPhaseShift;// ���䲨��ֱ�ڷ�����������
	double hPhaseShift;// ���䲨ƽ���ڷ�����������
	double relativeVelocity;// ���ճ�(����)�ͷ��䳵�������ٶ�
	double relativeAngle;// ���ճ�(����)�ͷ��䳵�������ٶȷ�������·�����������ļн�
	Direction relVelDirect;// ���ճ�(����)�ͷ��䳵�������ٶȷ���
	double vDoppler;// ���ճ�(����)�ͷ��䳵�������ٶ������ڴ���·�����ٶ�
	double frequency;// Ƶ��
	double waveLength;// ����
	double fDopplerShift;// ������Ƶ��
	double vPhasereceive;// ��ֱ�������յ�����λ
	double hPhasereceive;// ˮƽ�������յ�����λ
	double amplitudeReceive[2];// �����豸�յ�������,��ֱ����,ˮƽ����	
	double ir[2];// ������Ӧ,v��ֱ������hˮƽ����
	double amplitudeFade; // ·��
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

    // ��ȡ·���ܳ���
    double getTotalLength() const;
	int getNumOfReflect() const;
	vector<Reflection> getReflections() ;
	double getDelayTime() {
		return this->delayTime;
	};
};

class DiffractPath {
	friend class Model;
	friend class MixPathSegment;
	friend class MixPath;
private:
	Reflection* reflection;
    double totalLength; // ·���ܳ���
	double delayTime; // ����ʱ��
	double frequency; // Ƶ��
	double waveLength; // ����
	double vDoppler; // �������ٶ�
	Direction aInDirection[2]; // ����ǰ�������򣬴�ֱ��ˮƽ
	Direction aOutDirection[2]; // �����󼫻����򣬴�ֱ��ˮƽ
	double aIn[2]; // ����ǰ��������ֱ��ˮƽ
	double aOut[2]; // ��������������ֱ��ˮƽ
	double aReceive[2]; // �����豸�յ�������,��ֱ����,ˮƽ����
	double phase[2]; // ��λ����ֱ��ˮƽ
	double ir[2]; // ������Ӧ,v��ֱ������hˮƽ����
	Diffraction diffraction; // ��������
	double amplitudeFade; // ��������������˥���ٷֱ�
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

// ����·����
class MixPathSegment{
	friend class MixPath;
private:
    Reflection* pReflect;// ������ֱ��·������ָ��
    Diffraction* pDiffract; // ����·������ָ��
	double length; // �ֶγ���
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
// ����·��
class MixPath{
	friend class Model;
private:
	Path* reflectPath; // δ������֤�ķ���·��
    vector<MixPathSegment> segments; // �ֶ�����������������·��
    double totalLength; // ·���ܳ���	
	double delayTime; // ����ʱ��
	double frequency; // Ƶ��
	double fDopplerShift; // ������Ƶ��
	double waveLength; // ����
	double vDoppler; // �������ٶ�
	double amplitude[2]; // ��·���������������ϵ�������v,h
	Direction polarization[2]; // ��·����������������v,h
	double amplitudeReceive[2]; // �����豸�յ�������,��ֱ����,ˮƽ����
	double phase[2]; // ��λ����ֱ��ˮƽ
	double ir[2]; // ������Ӧ,v��ֱ������hˮƽ����
	double amplitudeFade; // ·��
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

//����ģ����
class Model{
	friend class MergePathModel;
private:	
    Vehicle transmitter; // ���䳵Tx
    Vehicle receiver; // ���ճ�Rx
	vector<Antenna> tAntennas; // ����������
	vector<Antenna> rAntennas; // ����������
	vector<Path> strongestPaths; // ������ǿ��·��
	vector<Path> surfaceScatterPaths; // ƽ��ɢ��·��·����������ɢ����strongestPaths
	vector<DiffractPath> diffractPaths; // ����·������
	vector<TreeScatterPath> treeScatterPaths; // ��ľɢ��·�� 
	vector<LeafScatterPath> leafScatterPaths; // ��Ҷ��ɢ��·�� 
	vector<LeafScatterMergePath> leafScatterMergePaths; // ��Ҷ��ɢ���ϲ�·�� 
	vector<MixPath> mixPaths; // ����·������
    vector<Surface> surfaces; // ��������
    vector<Edge> edges; // ��������
	vector<Tree> trees; // ��ľ
	int sampleCount; // ��������
	double sampleInterval; // ��������
	// ����LOS
	bool calculateLOSPath();
	// ���㷴��·��
	bool calculateReflectPaths();
	// LOS���������ж�
	// return 
	// 1:ֱ�䣬�ռ����ɣ�
	// 2:���䣬�뿪��ʱ�ӡ������ա���λ����ֱ�������㣬���������߹��ʣ���ʧ������������
	// 3:���в�������������
	int isLOSExist();
	// Ӱ��los������·��
	// param: DiffractPath* ,����
	// return:
	// 1:ֱ�䣬�ռ����ɣ�
	// 2:���䣬�뿪��ʱ�ӡ������ա���λ����ֱ�������㣬���������߹��ʣ���ʧ������������
	// 3:���в�������������
	DiffractPath* diffractAffectLos(int& type);
public:
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
		  const vector<Surface>& surfaces, 
		  const vector<Edge>& edges,
		  const vector<Antenna>& tAntennas,
		  const vector<Antenna>& rAntennas):
	  transmitter(transmitter), 
	  receiver(receiver), 
	  surfaces(surfaces),
	  edges(edges),
	  tAntennas(tAntennas),
	  rAntennas(rAntennas){};
	Model(const Vehicle& transmitter, 
		  const Vehicle& receiver, 
		  const vector<Surface>& surfaces):
	  transmitter(transmitter), 
	  receiver(receiver), 
	  surfaces(surfaces){};
	Model(const Vehicle& transmitter, 
		  const Vehicle& receiver, 
		  const vector<Surface>& surfaces,
		  const vector<Edge>& edges):
	  transmitter(transmitter), 
	  receiver(receiver), 
	  surfaces(surfaces),
	  edges(edges){};
	void setTrees(const vector<Tree>& trees) {
		this->trees = trees;
	};
	// ���ò�����Ϣ
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
    // ��ʼ��
    void init();
	// ��ȡģ�������̵�7��·����ȷ�н�Ϊ������ǿ�ģ���һ��������
    // return: 
    bool calculateStrongestPaths();
	// ��������·��
	bool calculateDiffractPaths();

	// ����ƽ��ɢ��·������calculateStrongestPaths()�����ã�ֱ�Ӳ�����StrongestPaths����ͬ����������·���ļ���
	bool calculateSurfaceScatterPaths();

	// ������ľɢ��·��
	bool calculateTreeScatterPaths();
	bool calculateTreeScatterPath(list<Tree> t);
	void insertTreeScatterPath(const TreeScatterPath& newPath);

	// ������Ҷ��ɢ��·��
	bool calculateLeafScatterPaths();
	bool calculateLeafScatterPath(list<Leaf> l);
	void insertLeafScatterPath(const LeafScatterPath& newPath);

	// ��������·��
	bool calculateMixPaths();

    // ���������������䴫��·��()
    // @pt:�������ߵ�
    // @pr:�������ߵ�
    // @surfaces:�ٶ��źŴ���·������������������
    // return: ������·������������Path���󣻷��򷵻�null
    bool getReflectPath(const Point& pt, const Point& pr, const vector<Surface>& surfaces);

	// ����·��������
    // @newPath:�¼����Ĵ���·��
    // @paths:ԭ�д���·����
    void insertPath(const Path& newPath);

	// ��������·��������
    // @newDiffractPath:�¼����Ĵ���·��
    void insertDiffractPath(const DiffractPath& newDiffractPath);
	
	// ��������˥��
	bool calculateAmplitude();

	// ��ȡ������ǿ��·������
	vector<Path> getStrongestPaths() const;

	// ����tʱ�̵��ŵ�������Ӧ
	bool calculateImpulseResponse(double t);
    
	// ����tʱ������·���ĵ��ŵ�������Ӧ
	bool calculateDiffractImpulseResponse(double t);

	// ����tʱ�̻���·���ĵ��ŵ�������Ӧ
	bool calculateMixImpulseResponse(double t);

	// ����tʱ��ƽ��ɢ��·���ĵ��ŵ�������Ӧ
	bool calculateSurfaceScatterImpulseResponse(double t);

	// ����tʱ����ľɢ��·���ĵ��ŵ�������Ӧ
	bool calculateTreeScatterImpulseResponse(double t);


	// ��ʾ·��
	void displayPath();

	// ��ʾ·����ˮƽ��ֱ����������������Ӧ
	void displayPathIR();

	// ��ʾ·���Ĵ�ֱ����������������Ӧ
	void displayPathVIR();
	// ��ʾ·����ˮƽ����������������Ӧ
	void displayPathHIR();
	// ��ʾ�����ĳ�����Ӧ
	void displayPathsSampleIR();

	// ��ʾ����·���Ĵ�ֱ����������������Ӧ
	void displayDiffractPathVIR();
	// ��ʾ����·����ˮƽ����������������Ӧ
	void displayDiffractPathHIR();
	// ��ʾ�����ĳ�����Ӧ
	void displayDiffractPathsSampleIR();

	// ��ʾ����·���Ĵ�ֱ����������������Ӧ
	void displayMixPathVIR();
	// ��ʾ����·����ˮƽ����������������Ӧ
	void displayMixPathHIR();
	// ��ʾ�����ĳ�����Ӧ
	void displayMixPathsSampleIR();

	// ��ʾƽ��ɢ��·���Ĵ�ֱ����������������Ӧ
	void displaySurfaceScatterPathVIR();
	// ��ʾƽ��ɢ��·����ˮƽ����������������Ӧ
	void displaySurfaceScatterPathHIR();
	// ��ʾ�����ĳ�����Ӧ
	void displaySurfaceScatterPathsSampleIR();

	// ��ʾ��ľɢ��·���Ĵ�ֱ����������������Ӧ
	void displayTreeScatterPathVIR();
	// ��ʾ��ľɢ��·����ˮƽ����������������Ӧ
	void displayTreeScatterPathHIR();
	// ��ʾ��ľɢ��·��������
	void displayTreeScatterPathsAmplitude();
	// ��ʾ�����ĳ�����Ӧ
	void displayTreeScatterPathsSampleIR();
	
	void displayResult();
	// ��ʾ�����ĳ�����Ӧ
	void displaySampleIR();
	// ��ʾ�ŵ�����
	void displayIR();

	// ��ʾ����ģ�Ͳ���
	void displayModel();

	// ������ʾ��excel�еĸ�ʽ
	void displayModelExcel();

	// ��ʾ���Σ�excel��ʽ
	void displayEdgesExcel();

	// ��ʾ��ľ��excel��ʽ
	void displayTreesExcel();
	
	// ��ʾ��·���ܳ�
	void displayPathsLength();


	// ��ʾ��ľɢ����·���ܳ�
	void displayTreeScatterPathsLength();

	vector<LeafScatterPath> getLeafScatterPaths() {
	    return this->leafScatterPaths;
	};
	// ��ʾ����ʱ��
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


