#include <iostream>
#include <vector>
#include "model.h"

using namespace std;

// TODO:unsed
void Model::displayIR() {
}
void Model::displayModel() {
	cout<<"Tx:"<<endl;
	this->transmitter.displayVehichle();
	cout<<"Rx:"<<endl;
	this->receiver.displayVehichle();
    cout<<"Surfaces:"<<this->surfaces.size()<<endl;
	for (unsigned i = 0; i < this->surfaces.size(); i++) {
		cout<<"  "<<(i + 1)<<"th surface:"<<endl;
		this->surfaces[i].display(4);
	}
	cout<<"transmit antennas:"<<this->tAntennas.size()<<endl;
	for (unsigned j = 0; j < this->tAntennas.size(); j++) {
		cout<<"  "<<(j + 1)<<"th atenna element:"<<endl;
		this->tAntennas[j].display(4);
	}
} 
void Model::displayModelExcel() {
	int i;
	cout<<"Input"<<endl;

	cout<<"Vehicles\t"<<"location\t"<<"direction\t"<<"velocity\t"<<endl;
	cout<<"Tx\t";
	this->transmitter.displayVehichleExcel();
	cout<<"Rx\t";
	this->receiver.displayVehichleExcel();

	cout<<"transmit antennas\t"<<"direction\t"<<"polarization\t"<<"relative location\t"<<"amplitude(power related)\t"<<endl;
	for (i = 0; i < this->tAntennas.size(); i++) {
		cout<<"ta"<<(i + 1)<<"\t";
		this->tAntennas[i].displayExcel();
	}
	cout<<"recieve antennas\t"<<"direction\t"<<"polarization\t"<<"relative location\t"<<"amplitude(power related)\t"<<endl;
	for (i = 0; i < this->rAntennas.size(); i++) {
		cout<<"ra"<<(i + 1)<<"\t";
		this->rAntennas[i].displayExcel();
	}
    cout<<"reflect related:"<<endl;
	cout<<"Surfaces\t"<<"p0\t"<<"p1\t"<<"material\t"<<"refractive index\t"<<"max protubertance height\t"<<"protuber Height Standard Deviation\t"<<endl;
	for (i = 0; i < this->surfaces.size(); i++) {
		cout<<"s"<<(i + 1)<<"\t";
		this->surfaces[i].displayExcel();
	}

	displayEdgesExcel();
	displayTreesExcel();
	displayWeather();
} 
void Model::displayWeather() {
    if (this->storm) {
	    this->storm->display();
	}
	if (this->rain) {
		this->rain->display();
	}
}
void Model::displayEdgesExcel() {
	cout<<"diffract related:"<<endl;
	cout<<"Edges\t"<<"p0\t"<<"p1\t"<<"pn0\t"<<"pn1\t"<<endl;
	vector<Edge>::iterator iterEdges = this->edges.begin();
	int i = 1;
	for (; iterEdges < this->edges.end(); iterEdges++) {
		cout<<"e"<<i++<<"\t";
		iterEdges->displayExcel();
	}
} 
void Model::displayTreesExcel() {
	cout<<"scatter related:"<<endl;
	cout<<"Trees\t"<<"location\t"<<endl;
	vector<Tree>::iterator iterTree = this->trees.begin();
	int i = 1;
	for (; iterTree < this->trees.end(); iterTree++) {
		cout<<""<<i++<<"\t";
		iterTree->displayExcel();
	}
} 
void Model::displayMaxDelay() {
	cout<<"Vehicles\t"<<"location\t"<<"direction\t"<<"velocity\t"<<endl;
	cout<<"Tx\t";
	this->transmitter.displayVehichleExcel();
	cout<<"Rx\t";
	this->receiver.displayVehichleExcel();

    cout<<"Surfaces\t"<<"p0\t"<<"p1\t"<<"material\t"<<"refractive index\t"<<endl;
	for (unsigned i = 0; i < this->surfaces.size(); i++) {
		cout<<"s"<<(i + 1)<<"\t";
		this->surfaces[i].displayExcel();
	}
	cout<<"max delay:\t";
	int size = this->strongestPaths.size();
	double firstDelay = this->strongestPaths[0].getDelayTime();
	double lastDelay = this->strongestPaths[size - 1].getDelayTime();
	double maxDelay = lastDelay - firstDelay ;
	cout<<maxDelay<<"s\t";
	cout<<endl;
}
void Model::displayPathsLength() {
    vector<Path>::iterator iterPaths = this->strongestPaths.begin();
	for (; iterPaths < this->strongestPaths.end(); iterPaths++) {
	    iterPaths->displayPathTotalLength();
		cout<<"\t";
	}
	cout<<endl;
}
void Model::displayTreeScatterPathsLength() {
    vector<TreeScatterPath>::iterator iterPaths = this->treeScatterPaths.begin();
	for (; iterPaths < this->treeScatterPaths.end(); iterPaths++) {
	    iterPaths->displayPathTotalLength();
	}
	cout<<endl;
}
void Model::displayResult() {
	this->displaySampleInfo();
	this->displaySampleIR();
}
void Model::displaySampleInfo() {
    cout<<"sample interval\t"<<"sample times"<<endl;
	cout<<sampleInterval<<"s\t"<<sampleCount<<endl;
}
void Model::displaySampleIR() {
	cout<<"output"<<endl;
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