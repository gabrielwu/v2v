#include "math.h"
#ifndef BASE_H 
#define BASE_H 
#include "base.h"
#endif 
#ifndef DIFFRACTION_H 
#define DIFFRACTION_H 
#include "diffraction.h"
#endif 
using namespace std;
Point* calculateIntersectPoint(Direction& dLine, Direction& nPlane, Point& pLine, Point& pPlane) {
	double planeD = pPlane.calculateD(nPlane);
	double t = -(pLine * nPlane + planeD) / (dLine * nPlane);
	Point* ptr = new Point(pLine + dLine * t);
	return ptr;
}
void Edge::displayExcel() {
    this->p0.displayExcel();
	this->p1.displayExcel();
	this->pn0.displayExcel();
	this->pn1.displayExcel();
	cout<<endl;
}
void Diffraction::init() {
	this->losDirect = this->rxp - this->txp;
	this->calculateClearanceN();
	this->calculateDiffractP();
	this->calculateClearance();
	this->calculateDLength();
	this->calculateLength();
	this->calculateDirect();
	this->calculateV();
	this->calculateR();
	this->calculateH0();
	this->calculateType();
	this->calculateLoss();
	this->calculateAmplitudeFade();
	this->calculateTotalLength();
}
void Diffraction::calculate() {     

}
/* 不够准确
void Diffraction::calculateDiffractP() {
	Edge edge = this->edge;

	// clearanceN与edge的公共法向量
	Direction dnEdge = edge.getD() ^ this->clearanceN ;
	// clearanceN与los的公共法向量
	Direction dnLos = this->losDirect ^ this->clearanceN ;
	
	this->diffractP = calculateIntersectPoint(edge.getD(), dnLos, edge.getP0(), txp);
	this->diffractPImage = calculateIntersectPoint(losDirect, dnEdge, txp, edge.getP0());

}
void Diffraction::calculateClearance() {
	this->clearance = getDistance(*(this->diffractP), *(this->diffractPImage));
	this->clearanceN = *(this->diffractP) - *(this->diffractPImage);
	Point innerP = this->edge.getInnerP();
	Direction dPtoInnerP = *(this->diffractP) - innerP;
	if (innerP * dPtoInnerP < 0) {
		this->clearance = -this->clearance;
	}
}
void Diffraction::calculateClearanceN() {
	clearanceN = (edge.getD() ^ losDirect).getUnitDirection();
}
void Diffraction::calculateDLength() {
	d1 = getDistance(*(this->diffractPImage), txp);
	d2 = getDistance(*(this->diffractPImage), rxp);
}
void Diffraction::calculateLength() {
	inLength = getDistance(*(this->diffractP), txp);
	outLength = getDistance(*(this->diffractP), rxp);
}
*/
void Diffraction::calculateDiffractP() {
	Edge edge = this->edge;
	// tx到刃形底点的距离
	double txP0 = getDistance(this->txp, edge.p0);
	// rx到刃形底点距离
	double rxP0 = getDistance(this->rxp, edge.p0);
	// tx到刃形底点的线段在刃形法向量的投影长度
	double relTxP0 = (this->txp - edge.p0) * edge.d;
	// rx到刃形底点的线段在刃形法向量的投影长度
	double relRxP0 = (this->rxp - edge.p0) * edge.d;
	// tx到刃形的距离
	double txToEdge = sqrt(pow(txP0, 2) - pow(relTxP0, 2));
	// rx到刃形的距离
	double rxToEdge = sqrt(pow(rxP0, 2) - pow(relRxP0, 2));
	// 大直角三角形直角边长度
	double rightAngleSideBig = relTxP0 - relRxP0;
    // 小直角三角形底边长度
	double rightAngleSideSma = rxToEdge / (rxToEdge + txToEdge) * rightAngleSideBig;
	// edge参数方程t，求绕射点用
	double t = (rightAngleSideSma + relRxP0) / edge.length;
	// 绕射点坐标xyz
	Point diffP = (edge.p0 + edge.direct * t);
	this->diffractP = new Point(diffP);
	// 垂直于losDirect且过绕射点的直线方程ax+by+cz+d=0
	double d = -((*this->diffractP) * this->losDirect);
	// los参数方程tImage，求绕射点镜像用
    double tImage = (-d - (this->txp * this->losDirect)) / (this->losDirect * this->losDirect);
	// 绕射点镜像坐标xyz
	Point diffPImage = (this->txp + this->losDirect * tImage);
	this->diffractPImage = new Point(diffPImage);
}

void Diffraction::calculateClearance() {
	this->clearance = getDistance(*(this->diffractP), *(this->diffractPImage)) * this->calculateClearanceSign();
	this->clearanceN = *(this->diffractP) - *(this->diffractPImage);
	/*
	Point innerP = this->edge.getInnerP();
	// 绕射点到刃形内部一点的向量
	Direction dPtoInnerP = *(this->diffractP) - innerP;
	// not sure
	if (innerP * dPtoInnerP < 0) {
		this->clearance = -this->clearance;
	}
	*/
}
void Diffraction::calculateClearanceN() {
	clearanceN = (edge.getD() ^ losDirect).getUnitDirection();
}
void Diffraction::calculateDLength() {
	d1 = getDistance(*(this->diffractPImage), txp);
	d2 = getDistance(*(this->diffractPImage), rxp);
}
void Diffraction::calculateLength() {
	inLength = getDistance(*(this->diffractP), txp);
	outLength = getDistance(*(this->diffractP), rxp);
}

void Diffraction::calculateDirect() {
	inDirect = (*(this->diffractP) - txp).getUnitDirection();
	outDirect = (rxp - *(this->diffractP)).getUnitDirection();
}
void Diffraction::calculateV() {
	// 刃形不在收发端连线之间
	if (this->d1 + this->d2 > getDistance(this->txp, this->rxp)) {
	    v = -1;   
	} else {
		double temp = 2 * (d1 + d2) / (waveLength * d1 * d2);
	    v = clearance * sqrt(temp);
	}
}
void Diffraction::calculateR() {
    this->r = sqrt(this->waveLength * this->d1 * this->d2 / (this->d1 + this->d2));
}
void Diffraction::calculateH0() {
    this->h0 = -0.577 * this->r;
}
int Diffraction::isLosBlocked() {
    return this->type;
}
int Diffraction::calculateClearanceSign() {
	// los的方向不和刃形的两个侧面平行
    if (losDirect * edge.n0 != 0 && losDirect * edge.n1 != 0) {
        double dn0 = -(edge.pn0 * edge.n0);
		double dn1 = -(edge.pn1 * edge.n1);
		double t0 = -(dn0 + txp * edge.n0) / (edge.n0 * losDirect);
		double t1 = -(dn1 + txp * edge.n1) / (edge.n1 * losDirect);
		Point losP0(txp + losDirect * t0);
		Point losP1(txp + losDirect * t1);
		if ((edge.pn0 - edge.p1) * (losP0 - edge.pn0) > 0 && (edge.pn1 - edge.p1) * (losP1 - edge.pn1) > 0) {
		    this->losInEdge = false;
			return 1;
		} else {
		    return -1;
		}
	} else {
		if (losDirect * edge.n0 == 0) {
			double dn1 = -(edge.pn1 * edge.n1);
			double t1 = -(dn1 + txp * edge.n1) / (edge.n1 * losDirect);
			Point losP1(txp + losDirect * t1);
			if ((edge.pn1 - edge.p1) * (losP1 - edge.pn1) > 0) {
				this->losInEdge = false;
				return 1;
			} else {
			    return -1;
			}
		} else {
			double dn0 = -(edge.pn0 * edge.n0);
			double t0 = -(dn0 + txp * edge.n0) / (edge.n0 * losDirect);
			Point losP0(txp + losDirect * t0);
			if ((edge.pn0 - edge.p1) * (losP0 - edge.pn0) > 0) {
				this->losInEdge = false;
				return 1;
			} else {
			    return -1;
			}
		}
	}
}
void Diffraction::calculateType() {
	if (this->clearance <= this->h0 || ((this->losInEdge == false) && this->clearance > 0)) {
		type = 1;
	} else if (this->clearance <= 0 && this->clearance > this->h0) {
		type = 2;
	} else {
		type = 3;
	}
}
void Diffraction::calculateLoss() {
	if (v <= -1) {
		loss = 0;
	} else if (v <= 0 && v > -1) {
		double n = log10(0.5 - 0.6 * v);
		loss = 20 * n;
	} else if (v <= 1 && v > 0) {
		loss = 20 * log10(0.5 * pow(E, (-0.95 * v)));
	} else if (v <= 2.4 && v > 1) {
		loss = 20 * log10(0.4 - sqrt(0.1184 - pow((0.38 - 0.1 * v), 2)));
	} else if (v > 2.4) {
		loss = 20 * log10(0.225 / v);
	}
	if (this->type == 1) {
	    loss = 0;
	}
}
void Diffraction::calculateAmplitudeFade() {
    if (this->loss == 0) {
	    this->amplitudeFade = 0;
	} else {
	    this->amplitudeFade = pow(10, (this->loss / 20));
	}
}
void Diffraction::calculateTotalLength() {
    if (this->type == 1 || this->type == 2) {
	    this->totalLength = this->d1 + this->d2;
	} else if (this->type == 3) {
	    this->totalLength = this->inLength + this->outLength;
	}
}