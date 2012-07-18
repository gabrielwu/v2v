//#include <iostream>
//#ifndef MODEL_H 
//#define MODEL_H 
//#include "model.h"
//#endif 
//using namespace std;
//
//int main(int argc, char *argv[] ) { 
//	// ²£Á§
//	Material m1(1.5, "glass");
//	// ¸Ö
//	Material m2(2.5, "steel");
//	// ÂÁ
//	Material m3(1.4, "aluminum");
//	// Ë®Äà
//	Material m4(1.6, "concrete");
//
//
//	Point pt(0,0,0);
//	Direction dt(0.6, 0.8, 0);
//	Vehicle tx(pt, dt, 10); 
//	Point pr(0,300,0);
//	Direction dr(0,1,0);
//	Vehicle rx(pr, dr, 10);
//
//	// ±íÃæ
//	/*
//	Point ps10(-10,0,20);
//	Point ps11(-10,50,-1);
//	Surface s1(ps10, ps11, m1);
//
//	Point ps20(10,0,20);
//	Point ps21(10,50,-1);
//	Surface s2(ps20, ps21, m1);
//
//	Point ps30(-10,60,10);
//	Point ps31(-10,100,-1);
//	Surface s3(ps30, ps31, m1);
//
//	Point ps40(10,110,15);
//	Point ps41(10,170,-1);
//	Surface s4(ps40, ps41, m2);
//
//	Point ps50(-10,200,10);
//	Point ps51(-10,300,-1);
//	Surface s5(ps50, ps51, m2);
//
//	Point ps60(10,200,10);
//	Point ps61(10,300,-1);
//	Surface s6(ps60, ps61, m1);
//	*/
//
//	Point ps10(-10,0,20);
//	Point ps11(-10,90,-1);
//	Surface s1(ps10, ps11, m1);
//
//	Point ps20(10,0,20);
//	Point ps21(10,90,-1);
//	Surface s2(ps20, ps21, m2);
//
//	Point ps30(-10,100,10);
//	Point ps31(-10,190,-1);
//	Surface s3(ps30, ps31, m4);
//
//	Point ps40(10,100,15);
//	Point ps41(10,190,-1);
//	Surface s4(ps40, ps41, m1);
//
//	Point ps50(-10,200,10);
//	Point ps51(-10,300,-1);
//	Surface s5(ps50, ps51, m3);
//
//	Point ps60(10,200,10);
//	Point ps61(10,300,-1);
//	Surface s6(ps60, ps61, m4);
//	/*
//	Point ps10(-10,0,20);
//	Point ps11(-10,300,-1);
//	Surface s1(ps10, ps11, m1);
//	Point ps20(10,0,20);
//	Point ps21(10,300,-1);
//	Surface s2(ps20, ps21, m1);
//	*/
//	s1.init();
//	s2.init();
//	s3.init();
//	s4.init();
//	s5.init();
//	s6.init();
//	
//	vector<Surface> surfaces;
//	surfaces.push_back(s1);
//	surfaces.push_back(s2);
//	surfaces.push_back(s3);
//	surfaces.push_back(s4);
//	surfaces.push_back(s5);
//	surfaces.push_back(s6);
//
//	Direction tad(0,0,1);
//	Direction tarp(0,0,0);
//	Direction taPolar(sqrt(double(2))/2, 0, sqrt(double(2))/2);
//	Antenna ta(tad, tarp, taPolar, 10);
//	vector<Antenna> tas;
//	tas.push_back(ta);
//
//	Direction rad(0,0,1);
//	Direction rarp(0,0,0);
//	Direction raVPolar(1, 0, 0);
//	Direction raHPolar(0, 0, 1);
//	Antenna ra(rad, rarp, raVPolar, raHPolar);
//	vector<Antenna> ras;
//	ras.push_back(ra);
//
//	Model model(tx, rx, surfaces, tas, ras);
//    model.calculateStrongestPaths();
//	model.displayModelExcel();
//
//	/*
//	for (int i = 0; i <= 5; i++) {	    
//		//model.calculateImpulseResponse(i * 1 / F * 2 / 6);
//		model.calculateImpulseResponse(i * 0.01);
//		model.displayPathIR();
//	}
//	*/
//	//model.displayPath();
//	cout<<"display"<<endl;
//	for (int i = 0; i <= 5; i++) {	    
//		model.calculateImpulseResponse(i * 0.01);
//		model.displayPathVIR();
//	}
//	for (int i = 0; i <= 5; i++) {	    
//		model.calculateImpulseResponse(i * 0.01);
//		model.displayPathHIR();
//	}
//	
//
//	/*for (int i = 0; i <= 5; i++) {
//		Direction ptd =  tx.getDirection() * tx.getVelocity() * (0.1 * i);
//		Point pt1 = pt + ptd;
//		Vehicle tx1(pt1, dt, 10);
//
//		Direction prd =  rx.getDirection() * rx.getVelocity() * (0.1 * i);
//		Point pr1 = pr + prd;
//		Vehicle rx1(pr1, dr, 10);
//
//		Model model(tx1, rx1, surfaces, tas, ras);
//
//	    model.calculateStrongestPaths();
//	    model.displayModel();
//		model.calculateImpulseResponse(0);
//		model.displayPath();
//	}	*/
//	int flag;
//	cin>>flag;
//};