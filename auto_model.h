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
// �������ģ��1
// @length:��·����
// @width:��·���
// @margin:·�����뽨����ķ�Χ
// @sMaxH:�����������߶�
// @sMinH:����������С�߶�
// @sMaxW:�������������
// @sMinW:����������С���
// @surfaceInterval:��������ļ��
// @vRange:���ٷ�Χ0~vRange
// @dFlag:���������־ 1��y+ͬ��2��y-ͬ��3��y+y-����4��y-y+�������������
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

// �������ģ��2
// @length:��·���ȷ�Χ
// @width:��·��ȷ�Χ
// @margin:·�����뽨����ķ�Χ
// @bH:��������߶ȷ�Χ
// @bW:���������ȷ�Χ
// @bInterval:������ļ��
// @vRange:���ٷ�Χ0~vRange
// @dFlag:���������־ 1��y+ͬ��2��y-ͬ��3��y+y-����4��y-y+�������������
Model randomModel(double length[2], 
				  double width[2], 
				  double margin[2], 
				  double bH[2],
				  double bW[2], 
				  double bInterval[2], 
				  double vRange[2], 
				  int dFlag = 0);
// �����Ͻ���½죬���������
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
	// ��������
	Vehicle tx; // ���䳵Tx
    Vehicle rx; // ���ճ�Rx
	Direction dTx;
	Direction dRx;
	double vTx;
	double vRx;
	// ��·����
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


