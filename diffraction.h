#ifndef BASE_H 
#define BASE_H 
#include "base.h"
#endif 
using namespace std;

class MixPath;
class MixPathSegment;
class Edge {
	// p0、p1：棱的两个顶点,p0.z<p1.z
    Point p0;
	Point p1;
	// 两个侧面的顶点，对应法向量n0,n1
	Point pn0;
	Point pn1;
	Direction d; // 棱的法向量
	Direction direct; // 棱的向量（包括长度）
	Point innerP; // 棱内部一点
	double length; // 棱的长度
	Direction n0; // 构成刃形的一个侧平面法向量
	Direction n1; // 构成刃形的另一个平面法向量
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
    double totalLength; // 绕射路径长度，注意配合type计算
    Point txp; // 发射端
	Point rxp; // 接收端
	Direction losDirect; // LOS方向向量
	Edge edge; // 发生衍射的棱
	Point* diffractP; // 绕射点
	Point* diffractPImage; // 绕射点的镜像（在los上）
	Direction inDirect; // 入射方向
	Direction outDirect; // 出（衍）射方向
	double inLength; // 入射距离
	double outLength; // 出射距离 
	double clearance; // 余隙
	Direction clearanceN; // los和edge的公共法向量
	double d1; // 发射端距棱的相对距离
	double d2; // 棱距接收端的相对距离
	double waveLength; // 波长
	double v; // 菲涅尔绕射因子
	double loss; // 损耗（分贝表示）
	double r; // 第一菲涅尔绕射区半径
	double h0; // 最小余隙
	bool losInEdge; // 余隙为正时,los穿过刃形的两侧面？
	int type; // 绕射类型1：全开；2：半开；3：闭合
	double amplitudeFade; // 振幅衰落，剩余百分比
public:
	Diffraction(const Point& txp, const Point& rxp, const Edge& edge):txp(txp),rxp(rxp),edge(edge) {
		this->waveLength = WAVE_LENGTH;
		this->losDirect = this->rxp - this->txp;
		this->losInEdge = true;
	};
	// 初始化
	void init();
	// 计算衍射模型，确定各个参数
	void calculate();
	// 计算绕射点和绕射镜像点
	void calculateDiffractP();
	// 计算余隙
	void calculateClearance();
	// 计算los和edge的公共法向量
	void calculateClearanceN();
	// 计算d1,d2
	void calculateDLength();
	// 计算inLenth、outLength
	void calculateLength();
	// 计算inDirect、outDirect
	void calculateDirect();	
	// 计算绕射因子
	void calculateV();
	// 计算绕射损耗
	void calculateLoss();
	// 计算绕射振幅衰落剩余百分比
	void calculateAmplitudeFade();
	// 计算第一绕射区半径
	void calculateR();
	// 计算最小余隙
	void calculateH0();
	// 判断LOS是否被阻挡存在
	// return 1,全开； 2，半开；3，闭合
	int isLosBlocked();
	// 计算余隙正负
	int calculateClearanceSign();
	// 计算绕射类型
	void calculateType();
	// 计算绕射路径长度
	void calculateTotalLength();
};

double dBamplitudeConvert(double loss);
