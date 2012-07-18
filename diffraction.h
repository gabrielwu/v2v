#ifndef BASE_H 
#define BASE_H 
#include "base.h"
#endif 
using namespace std;

class MixPath;
class MixPathSegment;
class Edge {
	// p0��p1�������������,p0.z<p1.z
    Point p0;
	Point p1;
	// ��������Ķ��㣬��Ӧ������n0,n1
	Point pn0;
	Point pn1;
	Direction d; // ��ķ�����
	Direction direct; // ����������������ȣ�
	Point innerP; // ���ڲ�һ��
	double length; // ��ĳ���
	Direction n0; // �������ε�һ����ƽ�淨����
	Direction n1; // �������ε���һ��ƽ�淨����
public:
	friend class Diffraction;
	Edge(Point p0, Point p1, Point innerP):p0(p0),p1(p1), innerP(innerP) {
		this->direct = p1 - p0;
		this->d = this->direct.getUnitDirection();
        length = getDistance(p0, p1);
	};
	Edge(Point p0, Point p1, Point pn0, Point pn1):p0(p0),p1(p1),pn0(pn0),pn1(pn1) {
	    this->direct = p1 - p0;
		this->d = this->direct.getUnitDirection();
        length = getDistance(p0, p1);
		Direction d1 = (pn0 - p1) ^ (pn1 - p1);
		n0 = ((pn0 - p1) ^ d).getUnitDirection();
		n1 = (d ^ (pn1 - p1)).getUnitDirection();
		if (this->d * d1 < 0) {
		    n0 = -n0;
			n1 = -n1;
		}
	};
	Edge(Point p0, Point p1, Direction n0, Direction n1):p0(p0),p1(p1),n0(n0),n1(n1) {
	    this->direct = p1 - p0;
		this->d = this->direct.getUnitDirection();
        length = getDistance(p0, p1);
	};
	Direction getD() {
	    return d;
	};
	Point getP0() {
	    return p0;
	};
	Point getP1() {
	    return p1;
	};
	Point getInnerP() {
		return this->innerP;
	};
	void displayExcel();
};
class Diffraction {
	friend class DiffractPath;
	friend class Model;
	friend class MixPathSegment;
	friend class MixPath;
private:	
    double totalLength; // ����·�����ȣ�ע�����type����
    Point txp; // �����
	Point rxp; // ���ն�
	Direction losDirect; // LOS��������
	Edge edge; // �����������
	Point* diffractP; // �����
	Point* diffractPImage; // �����ľ�����los�ϣ�
	Direction inDirect; // ���䷽��
	Direction outDirect; // �����ܣ��䷽��
	double inLength; // �������
	double outLength; // ������� 
	double clearance; // ��϶
	Direction clearanceN; // los��edge�Ĺ���������
	double d1; // ����˾������Ծ���
	double d2; // �����ն˵���Ծ���
	double waveLength; // ����
	double v; // ��������������
	double loss; // ��ģ��ֱ���ʾ��
	double r; // ��һ�������������뾶
	double h0; // ��С��϶
	bool losInEdge; // ��϶Ϊ��ʱ,los�������ε������棿
	int type; // ��������1��ȫ����2���뿪��3���պ�
	double amplitudeFade; // ���˥�䣬ʣ��ٷֱ�
public:
	Diffraction(const Point& txp, const Point& rxp, const Edge& edge):txp(txp),rxp(rxp),edge(edge) {
		this->waveLength = WAVE_LENGTH;
		this->losDirect = this->rxp - this->txp;
		this->losInEdge = true;
	};
	// ��ʼ��
	void init();
	// ��������ģ�ͣ�ȷ����������
	void calculate();
	// �������������侵���
	void calculateDiffractP();
	// ������϶
	void calculateClearance();
	// ����los��edge�Ĺ���������
	void calculateClearanceN();
	// ����d1,d2
	void calculateDLength();
	// ����inLenth��outLength
	void calculateLength();
	// ����inDirect��outDirect
	void calculateDirect();	
	// ������������
	void calculateV();
	// �����������
	void calculateLoss();
	// �����������˥��ʣ��ٷֱ�
	void calculateAmplitudeFade();
	// �����һ�������뾶
	void calculateR();
	// ������С��϶
	void calculateH0();
	// �ж�LOS�Ƿ��赲����
	// return 1,ȫ���� 2���뿪��3���պ�
	int isLosBlocked();
	// ������϶����
	int calculateClearanceSign();
	// ������������
	void calculateType();
	// ��������·������
	void calculateTotalLength();
};

double dBamplitudeConvert(double loss);
