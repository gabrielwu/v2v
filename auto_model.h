#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#ifndef MODEL_H 
#define MODEL_H 
#include "model.h"
#endif
#define ANTENNA_HEIGHT 1.5
#define random(x) (rand()%x)
using namespace std;

double plusOrMinus();
// 产生随机模型1
// @length:道路长度
// @width:道路宽度
// @margin:路牙距离建筑物的范围
// @sMaxH:建筑物面最大高度
// @sMinH:建筑物面最小高度
// @sMaxW:建筑物面最大宽度
// @sMinW:建筑物面最小宽度
// @surfaceInterval:建筑物面的间隔
// @vRange:车速范围0~vRange
// @dFlag:两车方向标志 1、y+同向；2、y-同向；3、y+y-相向；4、y-y+相向；其他、随机
Model randomModel(double length, 
				  double width, 
				  double margin, 
				  double sMaxH,
				  double sMinH,
				  double sMaxW, 
				  double sMinW, 
				  double surfaceInterval, 
				  double vRange, 
				  int dFlag = 0);

// 产生随机模型2
// @length:道路长度范围
// @width:道路宽度范围
// @margin:路牙距离建筑物的范围
// @bH:建筑物面高度范围
// @bW:建筑物面宽度范围
// @bInterval:建筑物的间隔
// @vRange:车速范围0~vRange
// @dFlag:两车方向标志 1、y+同向；2、y-同向；3、y+y-相向；4、y-y+相向；其他、随机
Model randomModel(double length[2], 
				  double width[2], 
				  double margin[2], 
				  double bH[2],
				  double bW[2], 
				  double bInterval[2], 
				  double vRange[2], 
				  int dFlag = 0);
// 给定上界和下届，生产随机数
double randomNum(double range[2]);
Point randomPoint();
Direction randomDirection();
Vehicle randomVehicle(double distance, double width, double vRange);
Vehicle randomTx(double l, double w, double vRange[2], const Direction& d);
Vehicle randomRx(double l, double w, double vRange[2], const Direction& d);
vector<Material> materialList();
Surface randomSurface(const Point& p0, double width, vector<Material> materials);
Material autoMaterial();
class RandomModel {
private:
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
public:
	Model produce(double length[2], 
				  double width[2], 
				  double margin[2], 
				  double bH[2],
				  double bW[2], 
				  double bInterval[2], 
				  double vRange[2], 
				  int dFlag = 0);
	void vehicleDirect(int dFlag);
	void vehicleVelocity(double vRange[2]);
	void vehicleProduce(double vRange[2], int dFlag);
	void roadProduce(double length[2], double width[2], double margin[2]);
	double randomNum(double range[2]);
};


