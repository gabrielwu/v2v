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
void Model::displayPathIR() {
	unsigned i;
	for(i = 0; i < this->strongestPaths.size(); i++) {	
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		Path path = this->strongestPaths.at(i);
		path.displayVir();
		
	}
	cout<<endl;
	for(i = 0; i < this->strongestPaths.size(); i++) {
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		Path path = this->strongestPaths.at(i);
		path.displayHir();
		
	}
	cout<<endl;
}

void Model::displayPathVIR() {
	for(unsigned i = 0; i < this->strongestPaths.size(); i++) {	
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		Path path = this->strongestPaths.at(i);
		path.displayVir();
	}
	cout<<endl;
}
void Model::displayPathHIR() {
	for(unsigned i = 0; i < this->strongestPaths.size(); i++) {	
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		Path path = this->strongestPaths.at(i);
		path.displayHir();
		
	}
	cout<<endl;
}

void Model::displaySurfaceScatterPathVIR() {
	for(unsigned i = 0; i < this->surfaceScatterPaths.size(); i++) {	
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		Path path = this->surfaceScatterPaths.at(i);
		path.displayVir();
	}
	cout<<endl;
}
void Model::displaySurfaceScatterPathHIR() {
	for(unsigned i = 0; i < this->surfaceScatterPaths.size(); i++) {	
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		Path path = this->surfaceScatterPaths.at(i);
		path.displayHir();
		
	}
	cout<<endl;
}
void Model::displayTreeScatterPathVIR() {
	cout.setf(ios::fixed);
	cout.precision(10);
	cout.unsetf(ios_base::fixed);
	for(unsigned i = 0; i < this->treeScatterPaths.size(); i++) {	
		TreeScatterPath path = this->treeScatterPaths.at(i);
		path.displayVir();
	}
	cout<<endl;
}
void Model::displayTreeScatterPathHIR() {
	for(unsigned i = 0; i < this->treeScatterPaths.size(); i++) {	
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		TreeScatterPath path = this->treeScatterPaths.at(i);
		path.displayHir();		
	}
	cout<<endl;
}
void Model::displayTreeScatterPathsAmplitude() {
    cout<<"V:\t";
	vector<TreeScatterPath>::iterator iter = this->treeScatterPaths.begin();
	for (; iter < this->treeScatterPaths.end(); iter++) {
		iter->displayAmplitudeV();
	}
	cout<<endl;
	cout<<"H:\t";
	iter = this->treeScatterPaths.begin();
	for (; iter < this->treeScatterPaths.end(); iter++) {
		iter->displayAmplitudeH();
	}
	cout<<endl;
}
void Model::displayDiffractPathVIR() {
	vector<DiffractPath>::iterator iterDiffractPaths = this->diffractPaths.begin();
	for (; iterDiffractPaths < this->diffractPaths.end(); iterDiffractPaths++) {
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		iterDiffractPaths->displayVir();
	}
	cout<<endl;
}
void Model::displayDiffractPathHIR() {
	vector<DiffractPath>::iterator iterDiffractPaths = this->diffractPaths.begin();
	for (; iterDiffractPaths < this->diffractPaths.end(); iterDiffractPaths++) {
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		iterDiffractPaths->displayHir();
	}
	cout<<endl;
}
void Model::displayMixPathVIR() {
	vector<MixPath>::iterator iterMixPath = this->mixPaths.begin();
	for (; iterMixPath < this->mixPaths.end(); iterMixPath++) {
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		iterMixPath->displayVir();
	}
	cout<<endl;
}
void Model::displayMixPathHIR() {
	vector<MixPath>::iterator iterMixPath = this->mixPaths.begin();
	for (; iterMixPath < this->mixPaths.end(); iterMixPath++) {
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		iterMixPath->displayHir();
	}
	cout<<endl;
}
void Model::displayPath() {
	cout<<"num of paths:"<<this->strongestPaths.size()<<endl;
	for(unsigned i = 0; i < this->strongestPaths.size(); i++) {
		Path path = this->strongestPaths.at(i);
		cout<<i+1<<"th path:"<<endl;
		cout.setf(ios::fixed);
		cout.precision(10);
		
	    cout<<"  total length:"<<this->strongestPaths.at(i).getTotalLength()<<endl;
		cout<<"  delay time:"<<this->strongestPaths.at(i).getDelayTime()<<endl;
		cout<<"  frequency:"<<path.getFrequency()<<endl;
		cout<<"  frequency shift:"<<path.getFDopplerShift()<<endl;
		cout<<"  wavelength:"<<path.getWaveLength()<<endl;
		
		cout.unsetf(ios_base::fixed);

		Direction tDirection = path.getReflections().begin()->getDirection();
		Direction rDirection = path.getReflections().at(path.getNumOfReflect()).getDirection();
		cout<<"  transmit direction:("<<tDirection.i<<","<<tDirection.j<<","<<tDirection.k<<")"<<endl;
		cout<<"  receive  direction:("<<rDirection.i<<","<<rDirection.j<<","<<rDirection.k<<")"<<endl;
		cout<<"  h:("<<path.getH().i<<","<<path.getH().j<<","<<path.getH().k<<")"<<path.getHAmplitude()<<endl;
		cout<<"  v:("<<path.getV().i<<","<<path.getV().j<<","<<path.getV().k<<")"<<path.getVAmplitude()<<endl;
		cout<<"  h shift:"<<path.getHPhaseShift()<<endl;
		cout<<"  v shift:"<<path.getVPhaseShift()<<endl;

		path.displayIR();

		cout<<"  num of reflect :"<<this->strongestPaths.at(i).getNumOfReflect()<<endl;
		cout<<"  reflections:"<<"num:"<<this->strongestPaths.at(i).getReflections().size()<<endl;
		
		for(unsigned j = 0; j <= this->strongestPaths.at(i).getReflections().size()-1 ; j++) {
			cout<<"   "<<(j + 1)<<"th reflection:"<<endl;
			Reflection r = this->strongestPaths.at(i).getReflections().at(j);
		    Direction d = r.getDirection();
			Point p = r.getReflectPoint();
			Surface s = r.getSurface();
			Direction nVector = s.getNVector();
			double length = r.getLength();
			cout<<"    direction: ("<<d.i<<","<<d.j<<","<<d.k<<")"<<endl;
			cout<<"    reflect point:("<<p.x<<","<<p.y<<","<<p.z<<")"<<endl;

			if (j != 0) {
				cout<<"    n:("<<nVector.i<<","<<nVector.j<<","<<nVector.k<<")"<<endl;
			}
			cout<<"    h:("<<r.getH().i<<","<<r.getH().j<<","<<r.getH().k<<")"<<r.getHAmplitude()<<endl;
			cout<<"    v:("<<r.getV().i<<","<<r.getV().j<<","<<r.getV().k<<")"<<r.getVAmplitude()<<endl;
			cout<<"    h fade:"<<r.getAmplitudeFadeH()<<endl;
			cout<<"    v fade:"<<r.getAmplitudeFadeV()<<endl;
			cout<<"    reflect angle:"<<r.getReflectAngle()<<endl;
			cout<<"    length:"<<length<<endl;
		}
		
	}
}
void Model::displayPathRainFade() {
    cout<<"降雨衰落(百分比，分贝)"<<endl;
	cout<<"垂直极化\t";
	vector<Path>::const_iterator iter = this->strongestPaths.begin();
	for (; iter < this->strongestPaths.end(); iter++) {
		cout<<iter->rainFade[0]<<","<<(10 * log10(iter->rainFade[0]))<<"dB\t";
	}
	cout<<endl<<"水平极化\t";
	iter = this->strongestPaths.begin();
	for (; iter < this->strongestPaths.end(); iter++) {
		cout<<iter->rainFade[1]<<","<<(10 * log10(iter->rainFade[1]))<<"dB\t";
	}	
	cout<<endl;
}