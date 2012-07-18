#include <iostream>
#include <vector>
#include "model.h"

using namespace std;
void Model::displayResult() {
	cout<<"sample interval\t"<<"sample times"<<endl;
	cout<<sampleInterval<<"s\t"<<sampleCount<<endl;
	cout<<endl;
	cout<<"output"<<endl;
	this->displaySampleIR();
}
void Model::displaySampleIR() {
    this->displayPathsSampleIR();
    this->displayDiffractPathsSampleIR();
    this->displaySurfaceScatterPathsSampleIR();
    this->displayMixPathsSampleIR();
    this->displayTreeScatterPathsSampleIR();

};
void Model::displayPathsSampleIR() {
	int i;
	cout<<endl;
	cout<<"LOS and reflect:"<<endl;
	cout<<"total length of each:\t";
	this->displayPathsLength();
	cout<<"Vertical polarization IR"<<endl;

	for (i = 0; i < sampleCount; i++) {	    
		this->calculateImpulseResponse(i * sampleInterval);
		cout<<"t"<<(i + 1)<<"\t";
		this->displayPathVIR();
	}
	cout<<"Horizontal polarization IR"<<endl;
	for (i = 0; i < sampleCount; i++) {	    
		this->calculateImpulseResponse(i * sampleInterval);
		cout<<"t"<<(i + 1)<<"\t";
		this->displayPathHIR();
	}
}
void Model::displayDiffractPathsSampleIR() {
	int i;
	cout<<endl;
	cout<<"Diffract:"<<endl;
	cout<<"Vertical polarization IR"<<endl;
	for (i = 0; i < sampleCount; i++) {	    
		this->calculateDiffractImpulseResponse(i * sampleInterval);
		cout<<"t"<<(i + 1)<<"\t";
		this->displayDiffractPathVIR();
	}
		
	cout<<"Vertical polarization IR"<<endl;
	for (i = 0; i < sampleCount; i++) {	    
		this->calculateDiffractImpulseResponse(i * sampleInterval);
		cout<<"t"<<(i + 1)<<"\t";
		this->displayDiffractPathHIR();
	}
}
void Model::displayMixPathsSampleIR() {
    int i;
	cout<<endl;
	cout<<"Mix:"<<endl;
	cout<<"Vertical polarization IR"<<endl;
	for (i = 0; i < sampleCount; i++) {	    
		this->calculateMixImpulseResponse(i * sampleInterval);
		cout<<"t"<<(i + 1)<<"\t";
		this->displayMixPathVIR();
	}
	cout<<"Vertical polarization IR"<<endl;
	for (i = 0; i < sampleCount; i++) {	    
		this->calculateMixImpulseResponse(i * sampleInterval);
		cout<<"t"<<(i + 1)<<"\t";
		this->displayMixPathHIR();
	}		
}
void Model::displaySurfaceScatterPathsSampleIR() {
	int i;
	cout<<endl;
	cout<<"Scatter(related to reflect on building surfaces):"<<endl;
	cout<<"Vertical polarization IR"<<endl;
	for (i = 0; i < sampleCount; i++) {	    
		this->calculateSurfaceScatterImpulseResponse(i * sampleInterval);
		cout<<"t"<<(i + 1)<<"\t";
		this->displaySurfaceScatterPathVIR();
	}
	cout<<"Vertical polarization IR"<<endl;
	for (i = 0; i < sampleCount; i++) {	    
		this->calculateSurfaceScatterImpulseResponse(i * sampleInterval);
		cout<<"t"<<(i + 1)<<"\t";
		this->displaySurfaceScatterPathHIR();
	}
    
}
void Model::displayTreeScatterPathsSampleIR() {
    int i;
	cout<<endl;
	cout<<"Scatter(related to trees):"<<endl;
	cout<<"length\t";
	this->displayTreeScatterPathsLength();
	this->displayTreeScatterPathsAmplitude();
	cout<<"Vertical polarization IR"<<endl;
	for (i = 0; i < sampleCount; i++) {	    
		this->calculateTreeScatterImpulseResponse(i * sampleInterval);
		cout<<"t"<<(i + 1)<<"\t";
		this->displayTreeScatterPathVIR();
	}
	cout<<"Vertical polarization IR"<<endl;
	for (i = 0; i < sampleCount; i++) {	    
		this->calculateTreeScatterImpulseResponse(i * sampleInterval);
		cout<<"t"<<(i + 1)<<"\t";
		this->displayTreeScatterPathHIR();
	}

	
}