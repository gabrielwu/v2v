#include <iostream>
#include <sstream>
#ifndef MATH_H 
#define MATH_H 
#include "math.h"
#endif
#ifndef MODEL_H 
#define MODEL_H 
#include "model.h"
#endif 


using namespace std;

int main() { 
    const int sampleCount = 6;
	const double sampleInterval = 0.01;



    // 汽车
	Point pt(0,0,0);
	Direction dt(0.6, 0.8, 0);
	Vehicle tx(pt, dt, 10); 
	Point pr(0,300,0);
	Direction dr(0,1,0);
	Vehicle rx(pr, dr, 10);
	// 玻璃
	Material m1(1.5, "glass");
	// 钢
	Material m2(2.5, "steel");
	// 铝
	Material m3(1.4, "aluminum");
	// 水泥
	Material m4(1.6, "concrete");

	// 表面
	Point ps10(-10,0,20);
	Point ps11(-10,100,-1);
	Surface s1(ps10, ps11, m1);

	Point ps20(10,0,20);
	Point ps21(10,100,-1);
	Surface s2(ps20, ps21, m1);

	Point ps30(-10,110,10);
	Point ps31(-10,190,-1);
	Surface s3(ps30, ps31, m1);

	Point ps40(10,110,15);
    Point ps41(10,190,-1);
	Surface s4(ps40, ps41, m2);

	Point ps50(-10,200,10);
	Point ps51(-10,300,-1);
	Surface s5(ps50, ps51, m2);

	Point ps60(10,200,10);
	Point ps61(10,300,-1);
	Surface s6(ps60, ps61, m1);


	

	s1.init();
	s2.init();
	s3.init();
	s4.init();
	s5.init();
	s6.init();
	
	vector<Surface> surfaces;
	surfaces.push_back(s1);
	surfaces.push_back(s2);
	surfaces.push_back(s3);
	surfaces.push_back(s4);
	surfaces.push_back(s5);
	surfaces.push_back(s6);

	Direction tad(0,0,1);
	Direction tarp(0,0,0);
	Direction taPolar(sqrt(double(2))/2, 0, sqrt(double(2))/2);
	Antenna ta(tad, tarp, taPolar, 10);
	vector<Antenna> tas;
	tas.push_back(ta);

	Direction rad(0,0,1);
	Direction rarp(0,0,0);
	Direction raVPolar(1, 0, 0);
	Direction raHPolar(0, 0, 1);
	Antenna ra(rad, rarp, raVPolar, raHPolar);
	vector<Antenna> ras;
	ras.push_back(ra);


	vector<Edge> edges;
	Edge edge0(Point(1, 150, -1), Point(1, 150, 10), Point(1, 140, 10), Point(20, 150, 10));
	Edge edge1(Point(0, 130, -1), Point(0, 130, 10), Point(0, 130, 10), Point(20, 130, 10));
/*	Edge edge1(Point(-10, 60, 10), Point(-10, 60, -1), Point(-20, 60, 5));
	Edge edge2(Point(10, 110, 15), Point(10, 110, -1), Point(20, 110, 5));
	Edge edge3(Point(-10, 190, 10), Point(-10, 190, -1), Point(20, 190, 5));
	Edge edge4(Point(10, 190, 15), Point(10, 190, -1), Point(20, 190, 5));
*/
	edges.push_back(edge0);
	edges.push_back(edge1);
/*	edges.push_back(edge1);
	edges.push_back(edge2);
	edges.push_back(edge3);
	edges.push_back(edge4);
*/
	Model model(tx, rx, surfaces, tas, ras);
	model.setEdges(edges);
	model.calculateDiffractPaths();
	model.calculateStrongestPaths();
	model.calculateMixPaths();
	model.displayModelExcel();
	cout<<"sample interval\t"<<"sample times"<<endl;
	cout<<sampleInterval<<"s\t"<<sampleCount<<endl;
	cout<<"output"<<endl;
	int i;
	cout<<"LOS and reflect:"<<endl;
	cout<<"total length of each:"<<endl;
    model.displayPathsLength();
	cout<<"Vertical polarization IR"<<endl;

	for (i = 0; i < sampleCount; i++) {	    
		model.calculateImpulseResponse(i * sampleInterval);
		model.displayPathVIR();
	}
	cout<<"Horizontal polarization IR"<<endl;
	for (i = 0; i < sampleCount; i++) {	    
		model.calculateImpulseResponse(i * sampleInterval);
		model.displayPathHIR();
	}

  
	
	cout<<"Diffract:"<<endl;
	cout<<"Vertical polarization IR"<<endl;
	for (i = 0; i < sampleCount; i++) {	    
		model.calculateDiffractImpulseResponse(i * sampleInterval);
		model.displayDiffractPathVIR();
	}
	cout<<"Vertical polarization IR"<<endl;
	for (i = 0; i < sampleCount; i++) {	    
		model.calculateDiffractImpulseResponse(i * sampleInterval);
		model.displayDiffractPathHIR();
	}
    
	int flag;
	cin>>flag;
	return flag;
};