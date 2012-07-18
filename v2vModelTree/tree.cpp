#include "tree.h"
using namespace std;

double randomDouble(double range[2]) {
	double min = range[0];
    double max = range[1];
	if (range[0] > range[1]) {
	    max = range[0];
		min = range[1];
	}
	double num;
	if ((max - min) == 0) {
	    num = min;
	} else {
		double r = (double)rand() / RAND_MAX;
		r *=  (max - min);
	    num = min + r;
	}
	return num;
}
int randomInt(int range[2]) {
	int min = range[0];
    int max = range[1];
	if (range[0] > range[1]) {
	    max = range[0];
		min = range[1];
	}
	int rangeInt = max - min;
	int num;
	if (rangeInt == 1) {
        double r = (double)rand() / RAND_MAX;
		if (r < 0.5) {
			num = min;
		} else {
		    num = max;
		}
	} else if (rangeInt == 0) {
	    num = min;
	} else {
	    num = min + (int)(rand()%rangeInt);
	}
	return num;
}
void TreeConfig::display() {
    cout<<"树木生长配置参数"<<endl;
	cout<<"递归深度\t"<<this->depth<<endl;
	cout<<"根坐标\t"; this->rootPosition.displayExcel();cout<<endl;
	cout<<"主干方向\t"; this->trunkDirect.displayExcel();cout<<endl;
	cout<<"主干半径\t"<<this->trunkRadius<<endl;
	cout<<"主干长度\t"<<this->trunkLength<<endl;
	cout<<"第一个生长点位于枝条长度比范围\t("<<this->branchFirstGrowPoint[0]<<","<<this->branchFirstGrowPoint[1]<<")"<<endl;
	cout<<"最后一个生长点位于枝条长度比范围\t("<<this->branchLastGrowPoint[0]<<","<<this->branchLastGrowPoint[1]<<")"<<endl;
	cout<<"初始生长点个数范围\t("<<this->growPointAmount[0]<<","<<this->growPointAmount[1]<<")"<<endl;
	cout<<"生长点分支个数范围\t("<<this->growPointDivide[0]<<","<<this->growPointDivide[1]<<")"<<endl;
	cout<<"子枝条与母枝条生长点个数比值范围\t("<<this->growPointPercent[0]<<","<<this->growPointPercent[1]<<")"<<endl;
	cout<<"子枝条与母枝条（主干）偏角范围\t("<<this->branchAngleDrift[0]<<","<<this->branchAngleDrift[1]<<")"<<endl;
	cout<<"子枝条与母枝条（主干）长度比值范围\t("<<this->branchLengthPercent[0]<<","<<this->branchLengthPercent[1]<<")"<<endl;
	cout<<"子枝条与母枝条（主干）半径比值范围\t("<<this->branchRadiusPercent[0]<<","<<this->branchRadiusPercent[1]<<")"<<endl;
	cout<<"叶子生长级数\t"<<this->leafLevelDepth<<endl;
	cout<<"母枝条与子枝条的叶子生长点所占比例的比值范围\t("<<this->leafDepthPercent[0]<<","<<this->leafDepthPercent[1]<<")"<<endl;
	cout<<"叶片面积范围\t("<<this->leafArea[0]<<","<<this->leafArea[1]<<")"<<endl;
	cout<<"叶柄长度范围\t("<<this->leafStalkLength[0]<<","<<this->leafStalkLength[1]<<")"<<endl;
	cout<<"阳光方向\t";this->sunshineDirect.displayExcel();cout<<endl;
}
bool TreeTrunkBranch::generateGrowPoints() {
	//this->display();
	list<GrowPoint> allGP;
	double firstPercent = randomDouble(this->config->branchFirstGrowPoint);
	double lastPercent = randomDouble(this->config->branchLastGrowPoint);
	// 首尾两个生长点坐标
	Point firstP = this->points[0] + this->growDirect * this->length * firstPercent;
	Point lastP = this->points[0] + this->growDirect * this->length * lastPercent;
	GrowPoint firstGP(firstP, (this->depth - 1), randomInt(this->config->growPointDivide), this->config);
	GrowPoint lastGP(lastP, (this->depth - 1), randomInt(this->config->growPointDivide), this->config);
	int totalGP = randomInt(this->config->growPointAmount); 
	if (totalGP == 1) {
		allGP.push_back(firstGP);
	} else {
		allGP.push_back(lastGP);
		Direction distanceDirect = lastP - firstP;
		for (int i = 1; i < (totalGP - 1); i++) {
			double percentValue =  (double)rand()/RAND_MAX;
            Point nP = firstP + distanceDirect * percentValue;// 第i个生长点坐标
            GrowPoint nGP(nP, (this->depth - 1), randomInt(this->config->growPointDivide), this->config);
            allGP.push_back(nGP);
		}
	    allGP.push_back(firstGP);
	}
	int leafGP, branchGP;
    if (this->config->leafLevelDepth > this->depth) { // 全部为枝条生长点
	    leafGP = (int)(totalGP * pow(randomDouble(this->config->leafDepthPercent), this->depth));
        branchGP = totalGP - leafGP;
	} else {
		leafGP = 0;
	    branchGP = totalGP;
	}
	// 到达递归深度，终止递归
	if (this->depth <= -1) {
	    return false;
	}
	for (int i = 0; i < branchGP; i++) {
		GrowPoint *gpp = new GrowPoint(allGP.back()); 
		gpp->generateBranches(this->growDirect, this->length, this->radius);
		this->growPointsBranch.push_back(gpp);
		allGP.pop_back();
	}
	for (int j = 0; j < leafGP; j++) {
		GrowPoint *gpp = new GrowPoint(allGP.back());
		gpp->generateLeaves(this->growDirect);
		allGP.pop_back();
		this->growPointsLeaf.push_back(gpp);
	}
	return true;
}
bool TreeTrunkBranch::displayGrowPoints() {
	list<GrowPoint*>::iterator iterBranch = this->growPointsBranch.begin();
	list<GrowPoint*>::iterator iterLeaf = this->growPointsLeaf.begin();
	for (; iterBranch != this->growPointsBranch.end(); iterBranch++) {
	    (*iterBranch)->display();
	}
	for (; iterLeaf != this->growPointsLeaf.end(); iterLeaf++) {
	    (*iterLeaf)->display();
	}
    return true;
}
void TreeTrunkBranch::displayLeaves() {
	list<GrowPoint*>::iterator iterGPLeaf = this->growPointsLeaf.begin();
	for (; iterGPLeaf != this->growPointsLeaf.end(); iterGPLeaf++) {
		(*iterGPLeaf)->displayLeaves();
	}
	list<GrowPoint*>::iterator iterGPBranch = this->growPointsBranch.begin();
	for (; iterGPBranch != this->growPointsBranch.end(); iterGPBranch++) {
		(*iterGPBranch)->displayLeaves();
	}
}
void TreeTrunkBranch::displayBranches() {
	this->display();
	list<GrowPoint*>::iterator iterGPBranch = this->growPointsBranch.begin();
	for (; iterGPBranch != this->growPointsBranch.end(); iterGPBranch++) {
		(*iterGPBranch)->displayBranches();
	}
}
Direction GrowPoint::randomGrowDirect(Direction fatherGrowDirect) {
	double angleShift = randomDouble(this->config->branchAngleDrift);
	angleShift = angleShift / 360 * 2 * PI;
	double angles[2] = {0, 2 * PI};
	double angleXY = randomDouble(angles);
	double rXY = sin(angleShift);
	double oriZ = cos(angleShift);
	double oriX = cos(angleXY) * rXY;
	double oriY = sin(angleXY) * rXY;
	Direction oriGD(oriX, oriY, oriZ);
	Direction refDirect(0, 0, 1);
	Direction growDirect;
	if (fatherGrowDirect == refDirect) { // 母枝条与参考向量一致
		growDirect = oriGD;
	} else if (fatherGrowDirect == (-refDirect)) { // 母枝条与参考向量相反
        growDirect = -oriGD;
	} else { // 一般情况
		Direction crossDirect = fatherGrowDirect ^ refDirect;
        crossDirect = crossDirect.getUnitDirection();
		double cosZ = crossDirect.i;
		double sinZ = -crossDirect.j;
	    double cosX = fatherGrowDirect * refDirect;
		double sinX = sqrt(1-pow(cosX, 2));
		if (fatherGrowDirect.k > 0) {
		    sinX = -sinX;
		}
		double a = cosZ;
		double b = sinZ;
		double c = cosX;
		double d = sinX;
		Direction vectorX(a*a + b*b*c, a*b*c-a*b, -b*d);
		Direction vectorY(a*b*c-a*b, b*b+a*a*c, -a*d);
		Direction vectorZ(b*d, -b*d, c);
		double xShift = vectorX * oriGD;
		double yShift = vectorY * oriGD;
		double zShift = vectorZ * oriGD;
		growDirect.i = xShift;
		growDirect.j = yShift;
		growDirect.k = zShift;
	}
	return growDirect;
}
Direction GrowPoint::leafNVector(Direction growDirect, Direction fatherDirect) {
	Direction nVector;
	if (growDirect == this->config->sunshineDirect || 
		growDirect == -this->config->sunshineDirect) {
	    nVector = fatherDirect ^ growDirect;
	} else {
	    Direction cross = this->config->sunshineDirect ^ growDirect;
		nVector = growDirect ^ cross; 
	}
	return nVector;
}
bool GrowPoint::generateBranches(Direction fatherGrowDirect, double fatherLength, double fatherRadius) {
	// test
	// this->display();
    for (int i = 0; i < this->divideAmount; i++) {
		double length = fatherLength * randomDouble(this->config->branchLengthPercent);
		// 生成生长方向
		double radius = fatherRadius * randomDouble(this->config->branchRadiusPercent);
		Direction growDirect = this->randomGrowDirect(fatherGrowDirect);
		Point p0 = this->position;
		Point p1 = this->position + growDirect * length;
		TreeTrunkBranch *tb = new TreeTrunkBranch(p0, p1, this->depth, radius, this->config); 
		tb->generateGrowPoints();
		branches.push_back(tb);
	}
	return true;
}
bool GrowPoint::generateLeaves(Direction fatherGrowDirect) {
	for (int i = 0; i < this->divideAmount; i++) {
		Direction  growDirect = this->randomGrowDirect(fatherGrowDirect);
		Point stalkPosition = this->position;
		Point position = this->position + growDirect * randomDouble(this->config->leafStalkLength);
		double area = randomDouble(this->config->leafArea);
		Direction nVector = this->leafNVector(growDirect, fatherGrowDirect);
		Leaf *leaf = new Leaf(position, stalkPosition, area, nVector, this->config);
		//leaf->display();
		leaves.push_back(leaf);
	}
    return true;
}
void GrowPoint::displayLeaves() {
	list<Leaf*>::iterator iterLeaf = this->leaves.begin();
	for (; iterLeaf != this->leaves.end(); iterLeaf++) {
		(*iterLeaf)->display();
	}
	list<TreeTrunkBranch*>::iterator iterBranch = this->branches.begin();
	for (; iterBranch != this->branches.end(); iterBranch++ ) {
		(*iterBranch)->displayLeaves();
	}
}
void GrowPoint::displayBranches() {
	list<TreeTrunkBranch*>::iterator iterBranch = this->branches.begin();
	for (; iterBranch != this->branches.end(); iterBranch++) {
		(*iterBranch)->displayBranches();
	}
}
bool TreeModel::generate() {
	this->treeTrunk->generateGrowPoints();
	return true;
}
void TreeModel::displayConfig() {
    this->config->display();
}
void TreeModel::displayLeaves() {
	cout<<"叶子"<<endl;
	cout<<"叶柄坐标\t"<<"叶子坐标\t"<<"叶子法向量\t"<<"叶片面积\t"<<endl;
	this->treeTrunk->displayLeaves();
}
void TreeModel::displayBranches() {
	cout<<"枝条"<<endl;
	cout<<"当前枝条递归层数\t"<<"起点坐标\t"<<"终点坐标\t"<<"枝条生长方向\t"<<"枝条长度\t"<<"枝条半径\t"<<endl;
	this->treeTrunk->displayBranches();
}