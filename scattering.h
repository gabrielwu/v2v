#include <list>
#ifndef BASE_H 
#define BASE_H 
#include "base.h"
#endif 
#ifndef GEOMETRY_H 
#define GEOMETRY_H 
#include "geometry.h"
#endif 
using namespace std;

const double MERGE_DELAY = 1e-7;
const double MERGE_DIRECTION_PROJECTION = 0.99; 
class Model;
// 生成随机浮点数
double randomDouble(double range[2]);
// 生成随机整数
int randomInt(int range[2]);

class TreeConfig {
	friend class TreeTrunkBranch;
	friend class GrowPoint;
	friend class Tree;
private:
	int depth; // 递归深度
	Point rootPosition; // 根位置
	Direction trunkDirect; // 主干生长方向
	double trunkRadius; // 主干半径                   
	double trunkLength; // 主干长度（高度）
	double branchFirstGrowPoint[2]; // 第一个生长点位于枝条长度比范围 (0,1)
	double branchLastGrowPoint[2]; // 最后一个生长点位于枝条长度比范围 (0,1)
	int growPointAmount[2]; // 初始（主干）生长点个数范围
	int growPointDivide[2]; // 生长点分支个数范围
    double growPointPercent[2]; // 子枝条与母枝条生长点个数比值范围
    double branchAngleDrift[2]; // 子枝条与母枝条（主干）偏角范围 角度制
 	double branchLengthPercent[2]; // 子枝条与母枝条（主干）长度比值范围 (0,1)
	double branchRadiusPercent[2]; // 子枝条与母枝条（主干）半径比值范围 (0,1)
	int leafLevelDepth; // 叶子生长级数
	double leafDepthPercent[2]; // 母枝条与子枝条的叶子生长点所占比例的比值范围，如(60%,80%),
	                            // 最后一级枝条叶子生长点占100%，则它子枝条叶子生长点占(60%,80%) 
	double leafArea[2]; // 叶片面积范围
	double leafStalkLength[2]; // 叶柄长度范围
	Direction sunshineDirect; // 阳光方向（叶片法向量应与这个方向夹角尽可能小）
	// TODO::叶子形状
    // TODO::树冠轮廓几何体
	Geometry* crown;
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
		this->crown = NULL;
	};
	
    TreeConfig(int depth = 3, Point p = Point(0, 0, 1)) {
	    this->depth = 3;
	    this->rootPosition = p;
	    this->trunkDirect = Direction(0, 0, 1);
	    this->trunkRadius = 0.1;
	    this->trunkLength = 10;
	    this->branchFirstGrowPoint[0] = 0.6;
		this->branchFirstGrowPoint[1] = 0.7;
	    this->branchLastGrowPoint[0] = 0.9;
	    this->branchLastGrowPoint[1] = 1;
	    this->growPointAmount[0] = 3;
	    this->growPointAmount[1] = 3;
	    this->growPointDivide[0] = 3;
	    this->growPointDivide[1] = 3;
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
		this->crown = NULL;
	};
	void display();
	void setCrown(Geometry* c) {
	    this->crown = c;
	};
	
};
class Scattering {
private:
	Point location;
public:
	Scattering(const Point& location):location(location){};
	Point getLocation() const;
};

class Leaf {
	friend class Tree;
	friend class LeafScatter;
private:
	Point position;
	double area;
	Point stalkPosition;
	Direction growDirect;
	double stalkLength;
	Direction nVector;
	TreeConfig* config;
public:
	Leaf(const Point& position):position(position){};
	Leaf(const Point& position, double area):position(position),area(area){};
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
	Point getPosition() const {
	    return this->position;
	};
};

class GrowPoint;
class TreeTrunkBranch {
private:
    TreeConfig* config;
	int depth; // 当前递归深度（级数）
	Point points[2]; // 主干（枝条）首尾两端点
	Direction growDirect; // 生长方向，通过points计算
	double length; // 枝条长度，通过points计算
	double radius; // 枝条半径
	list<GrowPoint*> growPointsBranch; // 枝条生长点
	list<GrowPoint*> growPointsLeaf; // 叶子生长点
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
	// 生成生长点（分别枝条和叶子）
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
	list<Leaf> generateLeavesList();
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
	int divideAmount; // 该生长点分支
	list<Leaf> leaves;
	list<TreeTrunkBranch*> branches;
	Direction randomGrowDirect(Direction fatherGrowDirect);
	Direction leafNVector(Direction growDirect, Direction fatherDirect);
public:
	GrowPoint(Point position, int depth, int divideAmount, TreeConfig* config):
	  position(position), depth(depth), divideAmount(divideAmount), config(config){};
	
	// 生成枝条
	bool generateBranches(Direction fatherGrowDirect, double fatherLength, double fatherRadius);
	// 生成叶子
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
	list<Leaf> generateLeavesList();
	void displayLeaves();
	void displayBranches();
};
class LeafScatter {
	friend class LeafScatterPath;
	friend class Model;
private:
    Leaf leaf; // 叶子
    double length[2]; // 起点到散射点、散射点到终点的长度
    Point points[3]; // 散射起点、散射点、终点
    Direction direction[2]; // 起点到散射点、散射点到终点的方向
	double angle[2]; // 入射角、出射角
	Direction polarization[2]; // 散射波垂直、水平极化振幅分量方向
	double amplitude[2]; // 散射波垂直、平行极化的振幅大小
	double amplitudeFade[2]; // 散射波垂直、水平极化振幅衰落百分比
public:
	LeafScatter(const Leaf& leaf):leaf(leaf){
		Point p(0, 0 ,0);
	    this->points[0] = p;
	    this->points[1] = p;
	    this->points[2] = p;
	};
	bool init();
	bool calculatePolarAmplitude(Direction& inV, Direction& inH);
	bool calculatePolarAmplitude(LeafScatter& pre);
	bool calculateAmplitudeFade();
	void setPolarization(const Direction& vp, const Direction& hp);
	void setAmplitude(double v, double h);
};

class LeafScatterPath {
    friend class Model;
	friend class LeafScatter;
	friend class LeafScatterMergePath;
	friend class MergePathModel;
private:
	bool merged;
	Direction tDirection; // 出射方向
	Direction rDirection; // 接收方向
	double totalLength; // 路径总长度	
	double delayTime; // 传播时延
	double frequency; // 频率
	double fDopplerShift; // 多普勒频移
	double waveLength; // 波长
	double vDoppler; // 多普勒速度
	double amplitude[2]; // 该路径两个极化方向上的振幅，v,h
	Direction polarization[2]; // 该路径两个极化方向，v,h
	double amplitudeReceive[2]; // 接收设备收到的振幅,垂直极化,水平极化
	double phase[2]; // 相位，垂直，水平
	double ir[2]; // 冲击响应,v垂直极化，h水平极化
	double amplitudeFade; // 路损
public:
	list<LeafScatter> leafScatters;
	LeafScatterPath(const list<LeafScatter> LeafScatters):leafScatters(leafScatters){
	    this->merged = false;
	};
	void setLeafScatters(const list<LeafScatter>& LeafScatters) {
	    this->leafScatters = leafScatters;
	};
	void setMerged(bool merged = true) {
	    this->merged = merged;
	};
	bool isMerged() {
	    return this->merged;
	};
	Direction getTDirection() const {
	    return this->tDirection;
	};
	Direction getRDirection() const {
	    return this->rDirection;
	};
    bool calculate(Direction& relativeV, const vector<Antenna>& ras);
	bool calculateDirection();
	bool calculateWaveLength();
	bool calculateVDoppler(Direction& relativeV);
	bool calculateFDopplerShift();
	bool calculateFrequency();
	bool calculateLength();
	bool calculateDelayTime();
	bool calculateAmplitude();
	bool calculatePolarization();
	bool calculateAmplitudeFade();
	bool calculateAmplitudeReceive(const vector<Antenna>& ras);
	bool calculatePhase(double v, double h);
	bool calculateIr();
	void displayIr();
	void displayVir();
	void displayHir();
	void displayPathTotalLength();
	void displayAmplitudeV();
	void displayAmplitudeH();
};
class LeafScatterMergePath {
    friend class Model;
	friend class LeafScatter;
private:
	//list<LeafScatter> leafScatters;
	list<LeafScatterPath> leafScatterPaths;
	int mergePathSize;
	LeafScatterPath *refPath;
	Direction tDirection; // 出射方向
	Direction rDirection; // 接收方向
	
	double amplitude[2]; // 该路径两个极化方向上的振幅，v,h
	Direction polarization[2]; // 该路径两个极化方向，v,h
	double amplitudeReceive[2]; // 接收设备收到的振幅,垂直极化,水平极化
	double phase[2]; // 相位，垂直，水平
	double ir[2]; // 冲击响应,v垂直极化，h水平极化
	double amplitudeFade; // 路损
public:
	double totalLength; // 路径总长度	
	double delayTime; // 传播时延
	double frequency; // 频率
	double fDopplerShift; // 多普勒频移
	double waveLength; // 波长
	double vDoppler; // 多普勒速度
    LeafScatterMergePath(const list<LeafScatterPath>& leafScatterPaths):leafScatterPaths(leafScatterPaths){
	    this->refPath = &this->leafScatterPaths.front();
		this->mergePathSize = this->leafScatterPaths.size();
	};
	bool calculate();
	bool calculateDirection();
	bool calculateWaveLength();
	bool calculateVDoppler();
	bool calculateFDopplerShift();
	bool calculateFrequency();
	bool calculateLength();
	bool calculateDelayTime();
	bool calculateAmplitudePolarization();
	bool calculateAmplitudeFade();
	bool calculateAmplitudeReceive();
	bool calculatePhase(double v, double h);
	bool calculateIr();
	void displayIr();
	void displayVir();
	void displayHir();
	void displayPathTotalLength();
	void displayAmplitudeV();
	void displayAmplitudeH();
};
class MergePathModel {
private:
	int sampleCount; // 采样次数
	double sampleInterval; // 采样间隔
    vector<LeafScatterMergePath> leafScatterMergePaths;
public:
	// 设置采样信息
	void setSampleInfo(int sampleCount, double sampleInterval) {
	    this->sampleCount = sampleCount;
		this->sampleInterval = sampleInterval;
	};
	bool calculateLeafScatterMergeImpulseResponse(double t);
	void leafScatterMergePathsSampleIR();
	bool mergeLeafScatterPath(vector<LeafScatterPath> allPath);
	bool canMergeLeafScatterPath(LeafScatterPath& path1, LeafScatterPath& path2);
	vector<LeafScatterMergePath> getLeafScatterMergePaths() {
	    return this->leafScatterMergePaths;
	};
	// 显示路径的垂直极化方向的脉冲响应
	void displayLeafScatterMergePathVIR();
	// 显示路径的水平极化方向的脉冲响应
	void displayLeafScatterMergePathHIR();
	// 显示采样的冲击响应
	void displayLeafScatterMergePathsSampleIR();
};

class Tree {
	friend class TreeScatter;
private:
	Point location;
	list<Leaf> leaves;	
    TreeTrunkBranch* treeTrunk;
	TreeConfig* config;
public:

	Tree(const Point& location):location(location){};
	Tree(TreeConfig* config) {
		this->config = config;
	    Point p0 = this->config->rootPosition;
		Point p1 = p0 + this->config->trunkDirect * this->config->trunkLength;
		this->location = this->config->rootPosition;
		int depth = this->config->depth;
		double trunkRadius = this->config->trunkRadius;
		this->treeTrunk =  new TreeTrunkBranch(p0, p1, depth, trunkRadius, this->config);
	};
	bool generate();
	void displayLeaves();
	void displayBranches();
	void displayConfig();
	Point getLocation() const {
	    return this->location;
	};	
	list<Leaf> getLeaves() const {
	    return this->leaves;
	};
	void generateLeavesList(); // 生成树叶链表
	void displayExcel();
};

class TreeScatter {
	friend class TreeScatterPath;
	friend class Model;
private:
    Tree tree; // 树
    double length[2]; // 起点到散射点、散射点到终点的长度
    Point points[3]; // 散射起点、散射点、终点
    Direction direction[2]; // 起点到散射点、散射点到终点的方向
	double angle[2]; // 入射角、出射角
	Direction polarization[2]; // 散射波垂直、水平极化振幅分量方向
	double amplitude[2]; // 散射波垂直、平行极化的振幅大小
	double amplitudeFade[2]; // 散射波垂直、水平极化振幅衰落百分比
public:
	TreeScatter(const Tree& tree):tree(tree){};
	bool init();
	bool calculatePolarAmplitude(Direction& inV, Direction& inH);
	bool calculatePolarAmplitude(TreeScatter& pre);
	bool calculateAmplitudeFade();
	void setPolarization(const Direction& vp, const Direction& hp);
	void setAmplitude(double v, double h);
};

class TreeScatterPath {
    friend class Model;
private:
	list<TreeScatter> treeScatters;
	double totalLength; // 路径总长度	
	double delayTime; // 传播时延
	double frequency; // 频率
	double fDopplerShift; // 多普勒频移
	double waveLength; // 波长
	double vDoppler; // 多普勒速度
	double amplitude[2]; // 该路径两个极化方向上的振幅，v,h
	Direction polarization[2]; // 该路径两个极化方向，v,h
	double amplitudeReceive[2]; // 接收设备收到的振幅,垂直极化,水平极化
	double phase[2]; // 相位，垂直，水平
	double ir[2]; // 冲击响应,v垂直极化，h水平极化
	double amplitudeFade; // 路损
public:
	TreeScatterPath(const list<TreeScatter>& treeScatters):treeScatters(treeScatters){};
    bool calculate(Direction& relativeV, const vector<Antenna>& ras);
	bool calculateWaveLength();
	bool calculateVDoppler(Direction& relativeV);
	bool calculateFDopplerShift();
	bool calculateFrequency();
	bool calculateLength();
	bool calculateDelayTime();
	bool calculateAmplitude();
	bool calculatepolarization();
	bool calculateAmplitudeFade();
	bool calculateAmplitudeReceive(const vector<Antenna>& ras);
	bool calculatePhase(double v, double h);
	bool calculateIr();
	void displayIr();
	void displayVir();
	void displayHir();
	void displayPathTotalLength();
	void displayAmplitudeV();
	void displayAmplitudeH();
};