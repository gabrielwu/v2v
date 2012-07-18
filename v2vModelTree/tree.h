#include <iostream>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "math.h"
#include "../base.h"
using namespace std;

// �������������
double randomDouble(double range[2]);
// �����������
int randomInt(int range[2]);

class TreeConfig {
	friend class TreeTrunkBranch;
	friend class GrowPoint;
	friend class TreeModel;
private:
	int depth; // �ݹ����
	Point rootPosition; // ��λ��
	Direction trunkDirect; // ������������
	double trunkRadius; // ���ɰ뾶                   
	double trunkLength; // ���ɳ��ȣ��߶ȣ�
	double branchFirstGrowPoint[2]; // ��һ��������λ��֦�����ȱȷ�Χ (0,1)
	double branchLastGrowPoint[2]; // ���һ��������λ��֦�����ȱȷ�Χ (0,1)
	int growPointAmount[2]; // ��ʼ�����ɣ������������Χ
	int growPointDivide[2]; // �������֧������Χ
    double growPointPercent[2]; // ��֦����ĸ֦�������������ֵ��Χ
    double branchAngleDrift[2]; // ��֦����ĸ֦�������ɣ�ƫ�Ƿ�Χ �Ƕ���
 	double branchLengthPercent[2]; // ��֦����ĸ֦�������ɣ����ȱ�ֵ��Χ (0,1)
	double branchRadiusPercent[2]; // ��֦����ĸ֦�������ɣ��뾶��ֵ��Χ (0,1)
	int leafLevelDepth; // Ҷ����������
	double leafDepthPercent[2]; // ĸ֦������֦����Ҷ����������ռ�����ı�ֵ��Χ����(60%,80%),
	                            // ���һ��֦��Ҷ��������ռ100%��������֦��Ҷ��������ռ(60%,80%) 
	double leafArea[2]; // ҶƬ�����Χ
	double leafStalkLength[2]; // Ҷ�����ȷ�Χ
	Direction sunshineDirect; // ���ⷽ��ҶƬ������Ӧ���������нǾ�����С��
	// TODO::Ҷ����״
    // TODO::��������������
public:
    TreeConfig(	int depth,
				Point rootPosition,
				Direction trunkDirect,
				double trunkRadius,
				double trunkLength,
				double branchFirstGrowPoint[2],
				double branchLastGrowPoint[2],
				int growPointAmount[2],
				int growPointDivide[2],
				double growPointPercent[2],
				double branchAngleDrift[2],
				double branchLengthPercent[2],
				double branchRadiusPercent[2],
				int leafLevelDepth,
				double leafDepthPercent[2],
				double leafArea[2],
				double leafStalkLength[2],
				Direction sunshineDirect
				) {
	    this->depth = depth;
	    this->rootPosition = rootPosition;
	    this->trunkDirect = trunkDirect;
	    this->trunkRadius = trunkRadius;
	    this->trunkLength = trunkLength;
	    this->branchFirstGrowPoint[0] = branchFirstGrowPoint[0];
		this->branchFirstGrowPoint[1] = branchFirstGrowPoint[1];
	    this->branchLastGrowPoint[0] = branchLastGrowPoint[0];
	    this->branchLastGrowPoint[1] = branchLastGrowPoint[1];
	    this->growPointAmount[0] = growPointAmount[0];
	    this->growPointAmount[1] = growPointAmount[1];
	    this->growPointDivide[0] = growPointDivide[0];
	    this->growPointDivide[1] = growPointDivide[1];
	    this->growPointPercent[0] = growPointPercent[0];
	    this->growPointPercent[1] = growPointPercent[1];
	    this->branchAngleDrift[0] = branchAngleDrift[0];
	    this->branchAngleDrift[1] = branchAngleDrift[1];
	    this->branchLengthPercent[0] = branchLengthPercent[0];
	    this->branchLengthPercent[1] = branchLengthPercent[1];
	    this->branchRadiusPercent[0] = branchRadiusPercent[0];
	    this->branchRadiusPercent[1] = branchRadiusPercent[1];
	    this->leafLevelDepth = leafLevelDepth;
	    this->leafDepthPercent[0] = leafDepthPercent[0];
		this->leafDepthPercent[1]= leafDepthPercent[1];
	    this->leafArea[0] = leafArea[0];
	    this->leafArea[1] = leafArea[1];
	    this->leafStalkLength[0] = leafStalkLength[0];
	    this->leafStalkLength[1] = leafStalkLength[1];
	    this->sunshineDirect = sunshineDirect;
	};
	
    TreeConfig() {
	    this->depth = 3;
	    this->rootPosition = Point(0, 0, 0);
	    this->trunkDirect = Direction(0, 0, 1);
	    this->trunkRadius = 0.1;
	    this->trunkLength = 10;
	    this->branchFirstGrowPoint[0] = 0.6;
		this->branchFirstGrowPoint[1] = 0.7;
	    this->branchLastGrowPoint[0] = 0.9;
	    this->branchLastGrowPoint[1] = 1;
	    this->growPointAmount[0] = 5;
	    this->growPointAmount[1] = 15;
	    this->growPointDivide[0] = 1;
	    this->growPointDivide[1] = 1;
	    this->growPointPercent[0] = 0.6;
	    this->growPointPercent[1] = 0.8;
	    this->branchAngleDrift[0] = 60;
	    this->branchAngleDrift[1] = 90;
	    this->branchLengthPercent[0] = 0.6;
	    this->branchLengthPercent[1] = 0.8;
	    this->branchRadiusPercent[0] = 0.1;
	    this->branchRadiusPercent[1] = 0.3;
	    this->leafLevelDepth = 1;
	    this->leafDepthPercent[0] = 0.5;
		this->leafDepthPercent[1]= 0.8;
	    this->leafArea[0] = 0.01;
	    this->leafArea[1] = 0.02;
	    this->leafStalkLength[0] = 0.05;
	    this->leafStalkLength[1] = 0.1;
	    this->sunshineDirect = Direction(0, 0, 1);
	};
	void display();
	
};

class Leaf {
private:
	Point position;
	double area;
	Point stalkPosition;
	Direction growDirect;
	double stalkLength;
	Direction nVector;
	TreeConfig* config;
public:
	Leaf(Point position, Point stalkPosition, double area, Direction nVector, TreeConfig* config){
	    this->position = position;
		this->stalkPosition = stalkPosition;
		this->area = area;
		this->nVector = nVector;
		this->config = config;
		this->growDirect = (position - stalkPosition).getUnitDirection();
		this->stalkLength = (position - stalkPosition).getModule();
	};
	bool display() {
		this->stalkPosition.displayExcel();
		this->position.displayExcel();
		this->nVector.displayExcel();
		cout<<this->area;
		cout<<endl;
		return true;
	};
};
class GrowPoint;
class TreeTrunkBranch {
private:
    TreeConfig* config;
	int depth; // ��ǰ�ݹ���ȣ�������
	Point points[2]; // ���ɣ�֦������β���˵�
	Direction growDirect; // ��������ͨ��points����
	double length; // ֦�����ȣ�ͨ��points����
	double radius; // ֦���뾶
	list<GrowPoint*> growPointsBranch; // ֦��������
	list<GrowPoint*> growPointsLeaf; // Ҷ��������
public:
	TreeTrunkBranch(Point p0, Point p1, int depth, double radius, TreeConfig* config) {
	    this->points[0] = p0;
		this->points[1] = p1;
		this->growDirect = (p1 - p0).getUnitDirection();
		this->length = (p1 - p0).getModule();
		this->depth = depth;
		this->radius = radius;
		this->config = config;
	};
	// ���������㣨�ֱ�֦����Ҷ�ӣ�
	bool generateGrowPoints();
	bool display() {
		cout<<this->depth<<"\t";
		this->points[0].displayExcel();
		this->points[1].displayExcel();
		this->growDirect.displayExcel();
		cout<<this->length<<"\t";
		cout<<this->radius<<"\t";
		cout<<endl;
		return true;
	};
	bool displayGrowPoints();
	void displayLeaves();
	void displayBranches();
};
class TreeTrunk: public TreeTrunkBranch{
};
class TreeBranch: public TreeTrunkBranch{
};
class GrowPoint {
	friend class TreeTrunkBranch;
private:
    TreeConfig* config;
	Point position;
	int depth;
	int divideAmount; // ���������֧
	list<Leaf*> leaves;
	list<TreeTrunkBranch*> branches;
	Direction randomGrowDirect(Direction fatherGrowDirect);
	Direction leafNVector(Direction growDirect, Direction fatherDirect);
public:
	GrowPoint(Point position, int depth, int divideAmount, TreeConfig* config):
	  position(position), depth(depth), divideAmount(divideAmount), config(config){};
	
	// ����֦��
	bool generateBranches(Direction fatherGrowDirect, double fatherLength, double fatherRadius);
	// ����Ҷ��
	bool generateLeaves(Direction fatherGrowDirect);
	Point getPosition() {
	    return this->position;
	};
	int getDivideAmount() {
	    return this->divideAmount;
	};
	bool display() {
		this->position.displayExcel();
		cout<<this->divideAmount<<"\t";
		cout<<this->depth<<"\t";
		cout<<endl;
		return true;
	};
	void displayLeaves();
	void displayBranches();
};
class TreeModel {
private:
    TreeTrunkBranch* treeTrunk;
	TreeConfig* config;
public:
	TreeModel(TreeConfig* config) {
		this->config = config;
	    Point p0 = this->config->rootPosition;
		Point p1 = p0 + this->config->trunkDirect * this->config->trunkLength;
		int depth = this->config->depth;
		double trunkRadius = this->config->trunkRadius;
		this->treeTrunk =  new TreeTrunkBranch(p0, p1, depth, trunkRadius, this->config);
	};
	bool generate();
	void displayLeaves();
	void displayBranches();
	void displayConfig();
};