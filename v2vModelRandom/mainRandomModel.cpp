#include <iostream>
#include <fstream>
#include <sstream>
#include "math.h"
#include "../v2vModelXmlInput/tinyxml.h"  
#ifndef XMLHELPER_H 
#define XMLHELPER_H 
#include "../v2vModelXmlInput/xmlHelper.h"
#endif

#include "../random_model.h"

using namespace std;

bool nextModel() {
    int flag = 2;
	cout<<"1���½�ģ�ͣ�2���˳���"<<endl;
	cin>>flag;
	switch (flag) {
	    case 1:
			return true;
		case 2:
			return false;
		default:
			return false;
	}
}
int main(int argc, char *argv[] ) { 
    while (nextModel()) {
		RandomModel randomModel;
		randomModel.inputConfig();
		Model model = randomModel.createModel();

		cout<<"����ļ�·����:";
		string outPutFilepath;
		cin>>outPutFilepath;
		// ����cout��������ָ��
		streambuf* coutBuf = cout.rdbuf();
		ofstream of(outPutFilepath.c_str());
		// ��ȡ�ļ�out.txt��������ָ��
		streambuf* fileBuf = of.rdbuf();   
		// ����cout��������ָ��Ϊout.txt����������ָ��
		cout.rdbuf(fileBuf);
    
		randomModel.outputConfig();

		model.setSampleInfo(6, 0.01);

		model.calculateDiffractPaths();
		model.calculateStrongestPaths();
		model.calculateSurfaceScatterPaths();
		model.calculateMixPaths();	
		model.calculateTreeScatterPaths();
		model.calculateLeafScatterPaths();
		model.displayModelExcel();

		cout<<"-----------------"<<endl;
		MergePathModel mergePathModel;
		mergePathModel.setSampleInfo(model.getSampleCount(), model.getSampleInterval());
		mergePathModel.mergeLeafScatterPath(model.getLeafScatterPaths());
		mergePathModel.displayLeafScatterMergePathsSampleIR();
        
		model.displayResult();

		of.flush();
		of.close();
		// �ָ�coutԭ������������ָ��
		cout.rdbuf(coutBuf);
		cout << "�����ϣ�" << endl;
	}
	return 0;
}

/*
int main(int argc, char *argv[] ) { 
	RandomModel r;
    double length[2] = {500, 600};
	double width[2] = {10, 12};
	double margin[2] = {5, 10};
	double bH[2] = {20, 30};
	double bL[2] = {50, 100};
	double bInterval[2] = {0, 0};
	double vRange[2] = {6, 10};
	

    cout<<"ѡ�����뷽ʽ��1������̨���룻2��xml���룻3��Ĭ�������������"<<endl;
	cout<<"ѡ�񳡾����ͣ�1�����ٹ�·��2������Ͽ�ȣ�3��������·"<<endl;
    int inputType, scenarioType;
	cin>>inputType>>scenarioType;
	switch (inputType) {
	case 1:
        cout<<"�������ȷ�Χ��";
		cin>>length[0]>>length[1];
		cout<<"������ȷ�Χ��";
		cin>>width[0]>>width[1];
		cout<<"·���ཨ�����ȷ�Χ��";
		cin>>margin[0]>>margin[1];
		cout<<"������߶ȷ�Χ��";
		cin>>bH[0]>>bH[1];
		cout<<"�����ﳤ�ȷ�Χ��";
		cin>>bL[0]>>bL[1];
		cout<<"����������Χ��";
		cin>>bInterval[0]>>bInterval[1];
		cout<<"���ٷ�Χ��";
		cin>>vRange[0]>>vRange[1];
		break;
	case 2:{
		string inputFilePath;
		cout<<"�������xml�ļ�·����"<<endl;
		cin>>inputFilePath;  
        TiXmlDocument xmlDoc(inputFilePath.c_str());  
        bool loadOkay = xmlDoc.LoadFile();    
	    if (!loadOkay) {      
	 		printf( "Could not load test file %s. Error='%s'. Exiting.\n", inputFilePath.c_str(),xmlDoc.ErrorDesc() );  
            exit( 1 );  
		} 
		TiXmlElement* xmlModel = xmlDoc.RootElement();
		TiXmlElement* xmlLength = xmlModel->FirstChildElement("length");
		TiXmlElement* xmlWidth = xmlModel->FirstChildElement("width");
		TiXmlElement* xmlMargin = xmlModel->FirstChildElement("margin");
		TiXmlElement* xmlBH = xmlModel->FirstChildElement("bH");
		TiXmlElement* xmlBL = xmlModel->FirstChildElement("bL");
		TiXmlElement* xmlBInterval = xmlModel->FirstChildElement("bInterval");
		TiXmlElement* xmlVRange = xmlModel->FirstChildElement("vRange");
		TiXmlAttribute* xmlAttribute;

		string min, max;
		xmlAttribute = xmlLength->FirstAttribute();
		min =  xmlAttribute->Value();
		xmlAttribute = xmlAttribute->Next();
		max = xmlAttribute->Value();
		length[0] = parseDouble(min);
		length[1] = parseDouble(max);

		xmlAttribute = xmlWidth->FirstAttribute();
		min =  xmlAttribute->Value();
		xmlAttribute = xmlAttribute->Next();
		max = xmlAttribute->Value();
		width[0] = parseDouble(min);
		width[1] = parseDouble(max);

		xmlAttribute = xmlMargin->FirstAttribute();
		min =  xmlAttribute->Value();
		xmlAttribute = xmlAttribute->Next();
	    max = xmlAttribute->Value();
		margin[0] = parseDouble(min);
		margin[1] = parseDouble(max);

		xmlAttribute = xmlBH->FirstAttribute();
		min =  xmlAttribute->Value();
		xmlAttribute = xmlAttribute->Next();
		max = xmlAttribute->Value();
		bH[0] = parseDouble(min);
		bH[1] = parseDouble(max);

		xmlAttribute = xmlBL->FirstAttribute();
		min =  xmlAttribute->Value();
		xmlAttribute = xmlAttribute->Next();
		max = xmlAttribute->Value();
		bL[0] = parseDouble(min);
		bL[1] = parseDouble(max);

		xmlAttribute = xmlBInterval->FirstAttribute();
		min =  xmlAttribute->Value();
		xmlAttribute = xmlAttribute->Next();
		max = xmlAttribute->Value();
		bInterval[0] = parseDouble(min);
		bInterval[1] = parseDouble(max);

		xmlAttribute = xmlVRange->FirstAttribute();
		min =  xmlAttribute->Value();
		xmlAttribute = xmlAttribute->Next();
	    max = xmlAttribute->Value();
		vRange[0] = parseDouble(min);
		vRange[1] = parseDouble(max);
		break;
		   }
	case 3:
		break;
	default:
		break;
	}
	Model model(r.produce(length, width, margin, bH, bL, bInterval, vRange, 1));

	cout<<"����ļ�·����:";
	string outPutFilepath;
	cin>>outPutFilepath;
    // ����cout��������ָ��
	streambuf* coutBuf = cout.rdbuf();
	ofstream of(outPutFilepath.c_str());
    // ��ȡ�ļ�out.txt��������ָ��
	streambuf* fileBuf = of.rdbuf();   
	// ����cout��������ָ��Ϊout.txt����������ָ��
	cout.rdbuf(fileBuf);

	model.calculateDiffractPaths();
	model.calculateStrongestPaths();
	model.calculateMixPaths();
	model.calculateSurfaceScatterPaths();
	model.displayModelExcel();
	cout<<"sample interval\t"<<"sample times"<<endl;
	cout<<sampleInterval<<"s\t"<<sampleCount<<endl;
	cout<<endl;
	cout<<"output"<<endl;
	int i;
	cout<<endl;
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

	cout<<endl;
    cout<<"Mix:"<<endl;
	cout<<"Vertical polarization IR"<<endl;
	for (i = 0; i < sampleCount; i++) {	    
		model.calculateMixImpulseResponse(i * sampleInterval);
		model.displayMixPathVIR();
	}
	cout<<"Vertical polarization IR"<<endl;
	for (i = 0; i < sampleCount; i++) {	    
		model.calculateMixImpulseResponse(i * sampleInterval);
		model.displayMixPathHIR();
	}
	
	cout<<endl;
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

	cout<<endl;
	cout<<"Scatter(related to reflect on building surfaces):"<<endl;
	cout<<"Vertical polarization IR"<<endl;
	for (i = 0; i < sampleCount; i++) {	    
		model.calculateSurfaceScatterImpulseResponse(i * sampleInterval);
		model.displaySurfaceScatterPathVIR();
	}
	cout<<"Vertical polarization IR"<<endl;
	for (i = 0; i < sampleCount; i++) {	    
		model.calculateSurfaceScatterImpulseResponse(i * sampleInterval);
		model.displaySurfaceScatterPathHIR();
	}
    
	of.flush();
	of.close();
	// �ָ�coutԭ������������ָ��
	cout.rdbuf(coutBuf);
	cout << "Write Personal Information over..." << endl;

	int flag;
	cin>>flag;
	return flag;
}
*/