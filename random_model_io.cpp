#include "random_model.h"
using namespace std;
bool RandomModel::inputConfig() {
    cout<<"ѡ�����뷽ʽ��1������̨���룻2��xml���룻3��Ĭ�������������"<<endl;
	cin>>this->inputType;
	cout<<"ѡ�񳡾����ͣ�1������Ͽ�ȣ�2��������·��3�����ٹ�·"<<endl;
    cin>>this->scenarioType;
	switch (this->inputType) {
	    case 1:
			this->consoleInput();
			break;
		default:
			break;
	}
	switch (this->scenarioType) {
	    case 1:
			this->scenarioTypeInfo = "����Ͽ��(urban canyon)";
			break;
		case 2:
			this->scenarioTypeInfo = "������·(suburban street)";
			break;
		case 3:
			this->scenarioTypeInfo = "���ٹ�·(express way)";
			break;
		default:
			this->scenarioTypeInfo = "����Ͽ��(urban canyon)";
			break;
	}
	return true;
}
bool RandomModel::outputConfig() {
	cout<<"��������scenario\t"<<this->scenarioTypeInfo.c_str()<<endl;
    cout<<"��items\t"<<"��Χrange\t"<<endl;
	cout<<"��·����length\t"<<"("<<lengthRange[0]<<" , "<<lengthRange[1]<<")"<<"\t"<<endl;
	cout<<"��·���width\t"<<"("<<widthRange[0]<<" , "<<widthRange[1]<<")"<<"\t"<<endl;
	switch (this->scenarioType) {
	    case 1: // ����Ͽ��
			cout<<"·���뽨����ĳ���margin\t"<<"("<<marginRange[0]<<" , "<<marginRange[1]<<")"<<"\t"<<endl;
			cout<<"������߶�building height\t"<<"("<<bHRange[0]<<" , "<<bHRange[1]<<")"<<"\t"<<endl;
			cout<<"�����ﳤ��building length\t"<<"("<<bLRange[0]<<" , "<<bLRange[1]<<")"<<"\t"<<endl;
			cout<<"������������buliding interval\t"<<"("<<bIntervalRange[0]<<" , "<<bIntervalRange[1]<<")"<<"\t"<<endl;
			break;
		case 2: // �����·
			cout<<"·���뽨����ĳ���margin\t"<<"("<<marginRange[0]<<" , "<<marginRange[1]<<")"<<"\t"<<endl;
			cout<<"������߶�building height\t"<<"("<<bHRange[0]<<" , "<<bHRange[1]<<")"<<"\t"<<endl;
			cout<<"�����ﳤ��building length\t"<<"("<<bLRange[0]<<" , "<<bLRange[1]<<")"<<"\t"<<endl;
			cout<<"������������buliding interval\t"<<"("<<bIntervalRange[0]<<" , "<<bIntervalRange[1]<<")"<<"\t"<<endl;
			break;
		case 3: // ���ٹ�·
			cout<<"���ٹ�·�������̻�������margin\t"<<"("<<marginRange[0]<<" , "<<marginRange[1]<<")"<<"\t"<<endl;
			break;
	}
	cout<<"����velocity\t"<<"("<<this->vRange[0]<<" , "<<this->vRange[1]<<")"<<endl;
	cout<<"��������direction\t"<<this->dFlagInfo.c_str()<<"\t"<<endl;
	return true;
}
bool RandomModel::consoleInput() {
	switch (this->scenarioType) {
		case 1: // ����Ͽ��
			cout<<"�������ȷ�Χ��";
			cin>>lengthRange[0]>>lengthRange[1];
			cout<<"������ȷ�Χ��";
			cin>>widthRange[0]>>widthRange[1];
			cout<<"·���ཨ�����ȷ�Χ��";
			cin>>marginRange[0]>>marginRange[1];
			cout<<"������߶ȷ�Χ��";
			cin>>bHRange[0]>>bHRange[1];
			cout<<"�����ﳤ�ȷ�Χ��";
			cin>>bLRange[0]>>bLRange[1];
			cout<<"����������Χ��";
			cin>>bIntervalRange[0]>>bIntervalRange[1];
			cout<<"���ٷ�Χ��";
			cin>>vRange[0]>>vRange[1];
			cout<<"���䳵�ͽ��ճ�����1��ͬ��������2��ͬ�򣨸�����3�����򣨷��䳵���򣩣�4�����򣨽��ճ����򣩣�5�����"<<endl;
			cin>>dFlag;
			break;
		case 2: // �����·
			cout<<"�������ȷ�Χ��";
			cin>>lengthRange[0]>>lengthRange[1];
			cout<<"������ȷ�Χ��";
			cin>>widthRange[0]>>widthRange[1];
			cout<<"·���ཨ�����ȷ�Χ��";
			cin>>marginRange[0]>>marginRange[1];
			cout<<"������߶ȷ�Χ��";
			cin>>bHRange[0]>>bHRange[1];
			cout<<"�����ﳤ�ȷ�Χ��";
			cin>>bLRange[0]>>bLRange[1];
			cout<<"����������Χ��";
			cin>>bIntervalRange[0]>>bIntervalRange[1];
			cout<<"���ٷ�Χ��";
			cin>>vRange[0]>>vRange[1];
			cout<<"���䳵�ͽ��ճ�����1��ͬ��������2��ͬ�򣨸�����3�����򣨷��䳵���򣩣�4�����򣨽��ճ����򣩣�5�����"<<endl;
			cin>>dFlag;
			break;
		case 3: // ���ٹ�·
			cout<<"�������ȷ�Χ��";
			cin>>lengthRange[0]>>lengthRange[1];
			cout<<"������ȷ�Χ��";
			cin>>widthRange[0]>>widthRange[1];
			cout<<"���ٹ�·�������̻������룺";
			cin>>marginRange[0]>>marginRange[1];
			cout<<"���ٷ�Χ��";
			cin>>vRange[0]>>vRange[1];
			cout<<"���䳵�ͽ��ճ�����1��ͬ��������2��ͬ�򣨸�����3�����򣨷��䳵���򣩣�4�����򣨽��ճ����򣩣�5�����"<<endl;
			cin>>dFlag;
			break;
		default:
			break;
		
	}
	return true;
}