#include <iostream>
#include <sstream>
#include "tinyxml.h"  
#ifndef MODEL_H 
#define MODEL_H 
#include "../model.h"
#endif 
#ifndef XMLHELPER_H 
#define XMLHELPER_H 
#include "xmlHelper.h"
#endif

using namespace std;
const int sampleCount = 6;
const double sampleInterval = 0.01;

int main(int argc, char *argv[] ) { 


	//const char* filepath = argv[1];
	const char* filepath = "D:\\input.xml";   
    TiXmlDocument xmlDoc(filepath);  
    bool loadOkay = xmlDoc.LoadFile();    
	if (!loadOkay) {      
        printf( "Could not load test file %s. Error='%s'. Exiting.\n", filepath,xmlDoc.ErrorDesc() );  
        exit( 1 );  
	} 
	TiXmlElement* xmlModel = xmlDoc.RootElement();
	TiXmlElement* xmlTx = xmlModel->FirstChildElement("tx");
	TiXmlElement* xmlRx = xmlModel->FirstChildElement("rx");
	TiXmlElement* xmlSurfaces = xmlModel->FirstChildElement("surfaces");
	TiXmlElement* xmlEdges = xmlModel->FirstChildElement("edges");
	TiXmlAttribute* xmlAttribute;

	xmlAttribute = xmlTx->FirstAttribute();
	string txpStr =  xmlAttribute->Value();
	xmlAttribute = xmlAttribute->Next();
	string txdStr = xmlAttribute->Value();
	xmlAttribute = xmlAttribute->Next();
	string txvStr = xmlAttribute->Value();
	Direction td = parseDirection(txdStr);
	Point tp = parsePoint(txpStr);
    double tv= parseDouble(txvStr);
	Vehicle tx(tp, td, tv);

	xmlAttribute = xmlRx->FirstAttribute();
	string rxpStr =  xmlAttribute->Value();
	xmlAttribute = xmlAttribute->Next();
	string rxdStr = xmlAttribute->Value();
	xmlAttribute = xmlAttribute->Next();
	string rxvStr = xmlAttribute->Value();
	Direction rd = parseDirection(rxdStr);
	Point rp = parsePoint(rxpStr);
    double rv= parseDouble(rxvStr);
	Vehicle rx(rp, rd, rv);

	TiXmlElement* xmlSurface = xmlSurfaces->FirstChildElement("surface");
	vector<Surface> surfaces;
	while (xmlSurface) {
		xmlAttribute = xmlSurface->FirstAttribute();
		string p0Str = xmlAttribute->Value();
		xmlAttribute = xmlAttribute->Next();
		string p1Str = xmlAttribute->Value();
		xmlAttribute = xmlAttribute->Next();
		/*
		string p2Str = xmlAttribute->Value();
		xmlAttribute = xmlAttribute->Next();
		string p3Str = xmlAttribute->Value();
		xmlAttribute = xmlAttribute->Next();
		*/
		Point p0 = parsePoint(p0Str);
		Point p1 = parsePoint(p1Str);
		/*
		Point p2 = parsePoint(p2Str);
		Point p3 = parsePoint(p3Str);
		*/
		TiXmlElement* xmlMaterial = xmlSurface->FirstChildElement("material");
		xmlAttribute = xmlMaterial->FirstAttribute();
		string nameStr = xmlAttribute->Value();
		xmlAttribute = xmlAttribute->Next();
		string nStr = xmlAttribute->Value();
		double n = parseDouble(nStr);
		Material m(n, nameStr);
		Surface s(p0, p1, m);
		s.init();
		surfaces.push_back(s);
		xmlSurface = xmlSurface->NextSiblingElement();		
	}


	TiXmlElement* xmlEdge = xmlEdges->FirstChildElement("edge");
	vector<Edge> edges;
	while (xmlEdge) {
		xmlAttribute = xmlEdge->FirstAttribute();
		string p0Str = xmlAttribute->Value();
		xmlAttribute = xmlAttribute->Next();
		string p1Str = xmlAttribute->Value();
		xmlAttribute = xmlAttribute->Next();
		string pn0Str = xmlAttribute->Value();
		xmlAttribute = xmlAttribute->Next();
		string pn1Str = xmlAttribute->Value();
		xmlAttribute = xmlAttribute->Next();
		Point p0 = parsePoint(p0Str);
		Point p1 = parsePoint(p1Str);
		Point pn0 = parsePoint(pn0Str);
		Point pn1 = parsePoint(pn1Str);
		Edge e(p0, p1, pn0, pn1);
		edges.push_back(e);
		xmlEdge = xmlEdge->NextSiblingElement();
	}

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

	Model model(tx, rx, surfaces, tas, ras);
	model.setEdges(edges);
	model.calculateDiffractPaths();
	model.calculateStrongestPaths();
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