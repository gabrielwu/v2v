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
	cout<<"1、新建模型；2、退出；"<<endl;
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

		cout<<"输出文件路径名:";
		string outPutFilepath;
		cin>>outPutFilepath;
		// 保存cout流缓冲区指针
		streambuf* coutBuf = cout.rdbuf();
		ofstream of(outPutFilepath.c_str());
		// 获取文件out.txt流缓冲区指针
		streambuf* fileBuf = of.rdbuf();   
		// 设置cout流缓冲区指针为out.txt的流缓冲区指针
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
		// 恢复cout原来的流缓冲区指针
		cout.rdbuf(coutBuf);
		cout << "输出完毕！" << endl;
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
	

    cout<<"选择输入方式：1、控制台输入；2、xml输入；3、默认输入参数配置"<<endl;
	cout<<"选择场景类型：1、高速公路；2、城市峡谷；3、郊区道路"<<endl;
    int inputType, scenarioType;
	cin>>inputType>>scenarioType;
	switch (inputType) {
	case 1:
        cout<<"场景长度范围：";
		cin>>length[0]>>length[1];
		cout<<"场景宽度范围：";
		cin>>width[0]>>width[1];
		cout<<"路牙距建筑物宽度范围：";
		cin>>margin[0]>>margin[1];
		cout<<"建筑物高度范围：";
		cin>>bH[0]>>bH[1];
		cout<<"建筑物长度范围：";
		cin>>bL[0]>>bL[1];
		cout<<"建筑物间隔范围：";
		cin>>bInterval[0]>>bInterval[1];
		cout<<"车速范围：";
		cin>>vRange[0]>>vRange[1];
		break;
	case 2:{
		string inputFilePath;
		cout<<"输入参数xml文件路径："<<endl;
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

	cout<<"输出文件路径名:";
	string outPutFilepath;
	cin>>outPutFilepath;
    // 保存cout流缓冲区指针
	streambuf* coutBuf = cout.rdbuf();
	ofstream of(outPutFilepath.c_str());
    // 获取文件out.txt流缓冲区指针
	streambuf* fileBuf = of.rdbuf();   
	// 设置cout流缓冲区指针为out.txt的流缓冲区指针
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
	// 恢复cout原来的流缓冲区指针
	cout.rdbuf(coutBuf);
	cout << "Write Personal Information over..." << endl;

	int flag;
	cin>>flag;
	return flag;
}
*/