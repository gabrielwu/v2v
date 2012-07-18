#include "random_model.h"
using namespace std;
bool RandomModel::inputConfig() {
    cout<<"选择输入方式：1、控制台输入；2、xml输入；3、默认输入参数配置"<<endl;
	cin>>this->inputType;
	cout<<"选择场景类型：1、城市峡谷；2、郊区道路；3、高速公路"<<endl;
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
			this->scenarioTypeInfo = "城市峡谷(urban canyon)";
			break;
		case 2:
			this->scenarioTypeInfo = "郊区道路(suburban street)";
			break;
		case 3:
			this->scenarioTypeInfo = "高速公路(express way)";
			break;
		default:
			this->scenarioTypeInfo = "城市峡谷(urban canyon)";
			break;
	}
	return true;
}
bool RandomModel::outputConfig() {
	cout<<"场景类型scenario\t"<<this->scenarioTypeInfo.c_str()<<endl;
    cout<<"项items\t"<<"范围range\t"<<endl;
	cout<<"道路长度length\t"<<"("<<lengthRange[0]<<" , "<<lengthRange[1]<<")"<<"\t"<<endl;
	cout<<"道路宽度width\t"<<"("<<widthRange[0]<<" , "<<widthRange[1]<<")"<<"\t"<<endl;
	switch (this->scenarioType) {
	    case 1: // 城市峡谷
			cout<<"路牙与建筑物的长度margin\t"<<"("<<marginRange[0]<<" , "<<marginRange[1]<<")"<<"\t"<<endl;
			cout<<"建筑物高度building height\t"<<"("<<bHRange[0]<<" , "<<bHRange[1]<<")"<<"\t"<<endl;
			cout<<"建筑物长度building length\t"<<"("<<bLRange[0]<<" , "<<bLRange[1]<<")"<<"\t"<<endl;
			cout<<"建筑物间隔距离buliding interval\t"<<"("<<bIntervalRange[0]<<" , "<<bIntervalRange[1]<<")"<<"\t"<<endl;
			break;
		case 2: // 郊外道路
			cout<<"路牙与建筑物的长度margin\t"<<"("<<marginRange[0]<<" , "<<marginRange[1]<<")"<<"\t"<<endl;
			cout<<"建筑物高度building height\t"<<"("<<bHRange[0]<<" , "<<bHRange[1]<<")"<<"\t"<<endl;
			cout<<"建筑物长度building length\t"<<"("<<bLRange[0]<<" , "<<bLRange[1]<<")"<<"\t"<<endl;
			cout<<"建筑物间隔距离buliding interval\t"<<"("<<bIntervalRange[0]<<" , "<<bIntervalRange[1]<<")"<<"\t"<<endl;
			break;
		case 3: // 高速公路
			cout<<"高速公路与两侧绿化带距离margin\t"<<"("<<marginRange[0]<<" , "<<marginRange[1]<<")"<<"\t"<<endl;
			break;
	}
	cout<<"车速velocity\t"<<"("<<this->vRange[0]<<" , "<<this->vRange[1]<<")"<<endl;
	cout<<"两车方向direction\t"<<this->dFlagInfo.c_str()<<"\t"<<endl;
	return true;
}
bool RandomModel::consoleInput() {
	switch (this->scenarioType) {
		case 1: // 城市峡谷
			cout<<"场景长度范围：";
			cin>>lengthRange[0]>>lengthRange[1];
			cout<<"场景宽度范围：";
			cin>>widthRange[0]>>widthRange[1];
			cout<<"路牙距建筑物宽度范围：";
			cin>>marginRange[0]>>marginRange[1];
			cout<<"建筑物高度范围：";
			cin>>bHRange[0]>>bHRange[1];
			cout<<"建筑物长度范围：";
			cin>>bLRange[0]>>bLRange[1];
			cout<<"建筑物间隔范围：";
			cin>>bIntervalRange[0]>>bIntervalRange[1];
			cout<<"车速范围：";
			cin>>vRange[0]>>vRange[1];
			cout<<"发射车和接收车方向：1、同向（正）；2、同向（负）；3、相向（发射车正向）；4、相向（接收车正向）；5、随机"<<endl;
			cin>>dFlag;
			break;
		case 2: // 郊外道路
			cout<<"场景长度范围：";
			cin>>lengthRange[0]>>lengthRange[1];
			cout<<"场景宽度范围：";
			cin>>widthRange[0]>>widthRange[1];
			cout<<"路牙距建筑物宽度范围：";
			cin>>marginRange[0]>>marginRange[1];
			cout<<"建筑物高度范围：";
			cin>>bHRange[0]>>bHRange[1];
			cout<<"建筑物长度范围：";
			cin>>bLRange[0]>>bLRange[1];
			cout<<"建筑物间隔范围：";
			cin>>bIntervalRange[0]>>bIntervalRange[1];
			cout<<"车速范围：";
			cin>>vRange[0]>>vRange[1];
			cout<<"发射车和接收车方向：1、同向（正）；2、同向（负）；3、相向（发射车正向）；4、相向（接收车正向）；5、随机"<<endl;
			cin>>dFlag;
			break;
		case 3: // 高速公路
			cout<<"场景长度范围：";
			cin>>lengthRange[0]>>lengthRange[1];
			cout<<"场景宽度范围：";
			cin>>widthRange[0]>>widthRange[1];
			cout<<"高速公路与两侧绿化带距离：";
			cin>>marginRange[0]>>marginRange[1];
			cout<<"车速范围：";
			cin>>vRange[0]>>vRange[1];
			cout<<"发射车和接收车方向：1、同向（正）；2、同向（负）；3、相向（发射车正向）；4、相向（接收车正向）；5、随机"<<endl;
			cin>>dFlag;
			break;
		default:
			break;
		
	}
	return true;
}