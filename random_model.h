#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#ifndef MODEL_H 
#define MODEL_H 
#include "model.h"
#endif
#ifndef BASE_H 
#define BASE_H 
#include "base.h"
#endif
#ifndef DIFFRACTION_H 
#define DIFFRACTION_H 
#include "diffraction.h"
#endif
#ifndef SCATTERING_H 
#define DIFFRACTION_H 
#include "scattering.h"
#endif
using namespace std;

const double ANTENNA_HEIGHT = 1.5;
const double TREE_HEIGHT = 1.5;
const double BUILDING_WIDTH = 20;
class RandomModel {
private:
	// 场景输入方式：1、控制台输入；2、xml输入；3、默认输入参数配置
	int inputType;
	// 场景模型类型：1、城市峡谷；2、郊外道路；3、高速公路；
	int scenarioType;
    // 输入参数
	double lengthRange[2];
	double widthRange[2];
	double marginRange[2];
	double bHRange[2];
	double bLRange[2];
	double bIntervalRange[2];
	double vRange[2];
    int dFlag;
	// 派生配置参数
	string dFlagInfo;
	string scenarioTypeInfo;

	// 汽车参数
	Vehicle tx; // 发射车Tx
    Vehicle rx; // 接收车Rx
	Direction dTx;
	Direction dRx;
	double vTx;
	double vRx;
	// 道路参数
	double length;
	double width;
	double margin;
	
	vector<Tree> trees; // 树木
	vector<Material> materials; // 材料向量
    vector<Surface> surfaces; // 表面向量
    vector<Edge> edges; // 刃形向量
	vector<Antenna> tAntennas; // 发射天线阵
	vector<Antenna> rAntennas; // 接收天线阵
public:
    RandomModel(){};
	RandomModel(int scenarioType):scenarioType(scenarioType){
        lengthRange[0] = 500;
		lengthRange[1] = 600;
		widthRange[0] = 10;
		widthRange[1] = 12;
        marginRange[0] = 5;
		marginRange[1] = 10;
		bHRange[0] = 20;
        bHRange[1] = 30;
		bLRange[0] = 50;
		bLRange[1] = 100;
		bIntervalRange[0] = 10;
		bIntervalRange[1] = 10;
		vRange[0] = 10;
		vRange[1] = 10;
	};
	// 生成随机模型，分别处理多类型场景
	Model createModel();
	// 生成城市峡谷场景模型
	Model urbanCanyonModel();
	// 生成郊区道路景模型
	Model suburbanStreetModel();
	// 生成高速公路场景模型
	Model expresswayModel();
	// 生成随机模型
	// @length:道路长度范围
	// @width:道路宽度范围
	// @margin:路牙距离建筑物的范围
	// @bH:建筑物面高度范围
	// @bL:建筑物面宽度范围
	// @bInterval:建筑物的间隔
	// @vRange:车速范围0~vRange
	// @dFlag:两车方向标志 1、y+同向；2、y-同向；3、y+y-相向；4、y-y+相向；其他、随机
	Model produce(double length[2], 
				  double width[2], 
				  double margin[2], 
				  double bH[2],
				  double bL[2], 
				  double bInterval[2], 
				  double vRange[2], 
				  int dFlag = 0);

	
	// 设置Tx、Rx的方向
	void vehicleDirect(int dFlag);
	// 设置Tx、Rx的速度
	void vehicleVelocity(double vRange[2]);
	// 生成Tx、Rx，默认在场景中的两端，只考虑在同一道路中的情况
	void vehicleProduce(double vRange[2], int dFlag);
	// 设置道路参数
	void roadProduce(double length[2], double width[2], double margin[2]);
	// 生成材料链表
	void materialsProduce();
	// 生成树木
	void treesProduce();
    // 生成单个表面
    Surface surfaceProduce(const Point& p0, double length, vector<Material> materials);
    // 生成单个刃形
	Edge edgeProduce();
	// 生成刃形和表面
	void surfacesAndEdges(
		          double margin[2], 
				  double bH[2],
				  double bL[2], 
				  double bInterval[2]);
	// 生成天线，当前为固定值
    void antennasProduce();
	// 随机正负
	double plusOrMinus();
	// 随机数
	double randomNum(double range[2]);
	
	// 输入配置参数
	bool inputConfig();
    // 控制台输入方式
	bool consoleInput();
	// xml方式
	bool xmlInput();
	// 默认参数
	bool defaultInput();

	// 输出配置参数
    bool outputConfig();
};




