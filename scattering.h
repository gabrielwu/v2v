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
// �������������
double randomDouble(double range[2]);
// �����������
int randomInt(int range[2]);

class TreeConfig {
	friend class TreeTrunkBranch;
	friend class GrowPoint;
	friend class Tree;
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
	int divideAmount; // ���������֧
	list<Leaf> leaves;
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
	list<Leaf> generateLeavesList();
	void displayLeaves();
	void displayBranches();
};
class LeafScatter {
	friend class LeafScatterPath;
	friend class Model;
private:
    Leaf leaf; // Ҷ��
    double length[2]; // ��㵽ɢ��㡢ɢ��㵽�յ�ĳ���
    Point points[3]; // ɢ����㡢ɢ��㡢�յ�
    Direction direction[2]; // ��㵽ɢ��㡢ɢ��㵽�յ�ķ���
	double angle[2]; // ����ǡ������
	Direction polarization[2]; // ɢ�䲨��ֱ��ˮƽ���������������
	double amplitude[2]; // ɢ�䲨��ֱ��ƽ�м����������С
	double amplitudeFade[2]; // ɢ�䲨��ֱ��ˮƽ�������˥��ٷֱ�
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
	Direction tDirection; // ���䷽��
	Direction rDirection; // ���շ���
	double totalLength; // ·���ܳ���	
	double delayTime; // ����ʱ��
	double frequency; // Ƶ��
	double fDopplerShift; // ������Ƶ��
	double waveLength; // ����
	double vDoppler; // �������ٶ�
	double amplitude[2]; // ��·���������������ϵ������v,h
	Direction polarization[2]; // ��·��������������v,h
	double amplitudeReceive[2]; // �����豸�յ������,��ֱ����,ˮƽ����
	double phase[2]; // ��λ����ֱ��ˮƽ
	double ir[2]; // �����Ӧ,v��ֱ������hˮƽ����
	double amplitudeFade; // ·��
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
	Direction tDirection; // ���䷽��
	Direction rDirection; // ���շ���
	
	double amplitude[2]; // ��·���������������ϵ������v,h
	Direction polarization[2]; // ��·��������������v,h
	double amplitudeReceive[2]; // �����豸�յ������,��ֱ����,ˮƽ����
	double phase[2]; // ��λ����ֱ��ˮƽ
	double ir[2]; // �����Ӧ,v��ֱ������hˮƽ����
	double amplitudeFade; // ·��
public:
	double totalLength; // ·���ܳ���	
	double delayTime; // ����ʱ��
	double frequency; // Ƶ��
	double fDopplerShift; // ������Ƶ��
	double waveLength; // ����
	double vDoppler; // �������ٶ�
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
	int sampleCount; // ��������
	double sampleInterval; // �������
    vector<LeafScatterMergePath> leafScatterMergePaths;
public:
	// ���ò�����Ϣ
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
	// ��ʾ·���Ĵ�ֱ���������������Ӧ
	void displayLeafScatterMergePathVIR();
	// ��ʾ·����ˮƽ���������������Ӧ
	void displayLeafScatterMergePathHIR();
	// ��ʾ�����ĳ����Ӧ
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
	void generateLeavesList(); // ������Ҷ����
	void displayExcel();
};

class TreeScatter {
	friend class TreeScatterPath;
	friend class Model;
private:
    Tree tree; // ��
    double length[2]; // ��㵽ɢ��㡢ɢ��㵽�յ�ĳ���
    Point points[3]; // ɢ����㡢ɢ��㡢�յ�
    Direction direction[2]; // ��㵽ɢ��㡢ɢ��㵽�յ�ķ���
	double angle[2]; // ����ǡ������
	Direction polarization[2]; // ɢ�䲨��ֱ��ˮƽ���������������
	double amplitude[2]; // ɢ�䲨��ֱ��ƽ�м����������С
	double amplitudeFade[2]; // ɢ�䲨��ֱ��ˮƽ�������˥��ٷֱ�
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
	double totalLength; // ·���ܳ���	
	double delayTime; // ����ʱ��
	double frequency; // Ƶ��
	double fDopplerShift; // ������Ƶ��
	double waveLength; // ����
	double vDoppler; // �������ٶ�
	double amplitude[2]; // ��·���������������ϵ������v,h
	Direction polarization[2]; // ��·��������������v,h
	double amplitudeReceive[2]; // �����豸�յ������,��ֱ����,ˮƽ����
	double phase[2]; // ��λ����ֱ��ˮƽ
	double ir[2]; // �����Ӧ,v��ֱ������hˮƽ����
	double amplitudeFade; // ·��
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