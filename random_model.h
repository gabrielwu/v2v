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
	// �������뷽ʽ��1������̨���룻2��xml���룻3��Ĭ�������������
	int inputType;
	// ����ģ�����ͣ�1������Ͽ�ȣ�2�������·��3�����ٹ�·��
	int scenarioType;
    // �������
	double lengthRange[2];
	double widthRange[2];
	double marginRange[2];
	double bHRange[2];
	double bLRange[2];
	double bIntervalRange[2];
	double vRange[2];
    int dFlag;
	// �������ò���
	string dFlagInfo;
	string scenarioTypeInfo;

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
	
	vector<Tree> trees; // ��ľ
	vector<Material> materials; // ��������
    vector<Surface> surfaces; // ��������
    vector<Edge> edges; // ��������
	vector<Antenna> tAntennas; // ����������
	vector<Antenna> rAntennas; // ����������
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
	// �������ģ�ͣ��ֱ�������ͳ���
	Model createModel();
	// ���ɳ���Ͽ�ȳ���ģ��
	Model urbanCanyonModel();
	// ���ɽ�����·��ģ��
	Model suburbanStreetModel();
	// ���ɸ��ٹ�·����ģ��
	Model expresswayModel();
	// �������ģ��
	// @length:��·���ȷ�Χ
	// @width:��·��ȷ�Χ
	// @margin:·�����뽨����ķ�Χ
	// @bH:��������߶ȷ�Χ
	// @bL:���������ȷ�Χ
	// @bInterval:������ļ��
	// @vRange:���ٷ�Χ0~vRange
	// @dFlag:���������־ 1��y+ͬ��2��y-ͬ��3��y+y-����4��y-y+�������������
	Model produce(double length[2], 
				  double width[2], 
				  double margin[2], 
				  double bH[2],
				  double bL[2], 
				  double bInterval[2], 
				  double vRange[2], 
				  int dFlag = 0);

	
	// ����Tx��Rx�ķ���
	void vehicleDirect(int dFlag);
	// ����Tx��Rx���ٶ�
	void vehicleVelocity(double vRange[2]);
	// ����Tx��Rx��Ĭ���ڳ����е����ˣ�ֻ������ͬһ��·�е����
	void vehicleProduce(double vRange[2], int dFlag);
	// ���õ�·����
	void roadProduce(double length[2], double width[2], double margin[2]);
	// ���ɲ�������
	void materialsProduce();
	// ������ľ
	void treesProduce();
    // ���ɵ�������
    Surface surfaceProduce(const Point& p0, double length, vector<Material> materials);
    // ���ɵ�������
	Edge edgeProduce();
	// �������κͱ���
	void surfacesAndEdges(
		          double margin[2], 
				  double bH[2],
				  double bL[2], 
				  double bInterval[2]);
	// �������ߣ���ǰΪ�̶�ֵ
    void antennasProduce();
	// �������
	double plusOrMinus();
	// �����
	double randomNum(double range[2]);
	
	// �������ò���
	bool inputConfig();
    // ����̨���뷽ʽ
	bool consoleInput();
	// xml��ʽ
	bool xmlInput();
	// Ĭ�ϲ���
	bool defaultInput();

	// ������ò���
    bool outputConfig();
};




