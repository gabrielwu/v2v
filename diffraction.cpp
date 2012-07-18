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
/* ����׼ȷ
void Diffraction::calculateDiffractP() {
	Edge edge = this->edge;

	// clearanceN��edge�Ĺ���������
	Direction dnEdge = edge.getD() ^ this->clearanceN ;
	// clearanceN��los�Ĺ���������
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
	// tx�����ε׵�ľ���
	double txP0 = getDistance(this->txp, edge.p0);
	// rx�����ε׵����
	double rxP0 = getDistance(this->rxp, edge.p0);
	// tx�����ε׵���߶������η�������ͶӰ����
	double relTxP0 = (this->txp - edge.p0) * edge.d;
	// rx�����ε׵���߶������η�������ͶӰ����
	double relRxP0 = (this->rxp - edge.p0) * edge.d;
	// tx�����εľ���
	double txToEdge = sqrt(pow(txP0, 2) - pow(relTxP0, 2));
	// rx�����εľ���
	double rxToEdge = sqrt(pow(rxP0, 2) - pow(relRxP0, 2));
	// ��ֱ��������ֱ�Ǳ߳���
	double rightAngleSideBig = relTxP0 - relRxP0;
    // Сֱ�������εױ߳���
	double rightAngleSideSma = rxToEdge / (rxToEdge + txToEdge) * rightAngleSideBig;
	// edge��������t�����������
	double t = (rightAngleSideSma + relRxP0) / edge.length;
	// ���������xyz
	Point diffP = (edge.p0 + edge.direct * t);
	this->diffractP = new Point(diffP);
	// ��ֱ��losDirect�ҹ�������ֱ�߷���ax+by+cz+d=0
	double d = -((*this->diffractP) * this->losDirect);
	// los��������tImage��������㾵����
    double tImage = (-d - (this->txp * this->losDirect)) / (this->losDirect * this->losDirect);
	// ����㾵������xyz
	Point diffPImage = (this->txp + this->losDirect * tImage);
	this->diffractPImage = new Point(diffPImage);
}

void Diffraction::calculateClearance() {
	this->clearance = getDistance(*(this->diffractP), *(this->diffractPImage)) * this->calculateClearanceSign();
	this->clearanceN = *(this->diffractP) - *(this->diffractPImage);
	/*
	Point innerP = this->edge.getInnerP();
	// ����㵽�����ڲ�һ�������
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
	// ���β����շ�������֮��
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
	// los�ķ��򲻺����ε���������ƽ��
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