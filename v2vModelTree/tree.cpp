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
    cout<<"��ľ�������ò���"<<endl;
	cout<<"�ݹ����\t"<<this->depth<<endl;
	cout<<"������\t"; this->rootPosition.displayExcel();cout<<endl;
	cout<<"���ɷ���\t"; this->trunkDirect.displayExcel();cout<<endl;
	cout<<"���ɰ뾶\t"<<this->trunkRadius<<endl;
	cout<<"���ɳ���\t"<<this->trunkLength<<endl;
	cout<<"��һ��������λ��֦�����ȱȷ�Χ\t("<<this->branchFirstGrowPoint[0]<<","<<this->branchFirstGrowPoint[1]<<")"<<endl;
	cout<<"���һ��������λ��֦�����ȱȷ�Χ\t("<<this->branchLastGrowPoint[0]<<","<<this->branchLastGrowPoint[1]<<")"<<endl;
	cout<<"��ʼ�����������Χ\t("<<this->growPointAmount[0]<<","<<this->growPointAmount[1]<<")"<<endl;
	cout<<"�������֧������Χ\t("<<this->growPointDivide[0]<<","<<this->growPointDivide[1]<<")"<<endl;
	cout<<"��֦����ĸ֦�������������ֵ��Χ\t("<<this->growPointPercent[0]<<","<<this->growPointPercent[1]<<")"<<endl;
	cout<<"��֦����ĸ֦�������ɣ�ƫ�Ƿ�Χ\t("<<this->branchAngleDrift[0]<<","<<this->branchAngleDrift[1]<<")"<<endl;
	cout<<"��֦����ĸ֦�������ɣ����ȱ�ֵ��Χ\t("<<this->branchLengthPercent[0]<<","<<this->branchLengthPercent[1]<<")"<<endl;
	cout<<"��֦����ĸ֦�������ɣ��뾶��ֵ��Χ\t("<<this->branchRadiusPercent[0]<<","<<this->branchRadiusPercent[1]<<")"<<endl;
	cout<<"Ҷ����������\t"<<this->leafLevelDepth<<endl;
	cout<<"ĸ֦������֦����Ҷ����������ռ�����ı�ֵ��Χ\t("<<this->leafDepthPercent[0]<<","<<this->leafDepthPercent[1]<<")"<<endl;
	cout<<"ҶƬ�����Χ\t("<<this->leafArea[0]<<","<<this->leafArea[1]<<")"<<endl;
	cout<<"Ҷ�����ȷ�Χ\t("<<this->leafStalkLength[0]<<","<<this->leafStalkLength[1]<<")"<<endl;
	cout<<"���ⷽ��\t";this->sunshineDirect.displayExcel();cout<<endl;
}
bool TreeTrunkBranch::generateGrowPoints() {
	//this->display();
	list<GrowPoint> allGP;
	double firstPercent = randomDouble(this->config->branchFirstGrowPoint);
	double lastPercent = randomDouble(this->config->branchLastGrowPoint);
	// ��β��������������
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
            Point nP = firstP + distanceDirect * percentValue;// ��i������������
            GrowPoint nGP(nP, (this->depth - 1), randomInt(this->config->growPointDivide), this->config);
            allGP.push_back(nGP);
		}
	    allGP.push_back(firstGP);
	}
	int leafGP, branchGP;
    if (this->config->leafLevelDepth > this->depth) { // ȫ��Ϊ֦��������
	    leafGP = (int)(totalGP * pow(randomDouble(this->config->leafDepthPercent), this->depth));
        branchGP = totalGP - leafGP;
	} else {
		leafGP = 0;
	    branchGP = totalGP;
	}
	// ����ݹ���ȣ���ֹ�ݹ�
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
	if (fatherGrowDirect == refDirect) { // ĸ֦����ο�����һ��
		growDirect = oriGD;
	} else if (fatherGrowDirect == (-refDirect)) { // ĸ֦����ο������෴
        growDirect = -oriGD;
	} else { // һ�����
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
		// ������������
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
	cout<<"Ҷ��"<<endl;
	cout<<"Ҷ������\t"<<"Ҷ������\t"<<"Ҷ�ӷ�����\t"<<"ҶƬ���\t"<<endl;
	this->treeTrunk->displayLeaves();
}
void TreeModel::displayBranches() {
	cout<<"֦��"<<endl;
	cout<<"��ǰ֦���ݹ����\t"<<"�������\t"<<"�յ�����\t"<<"֦����������\t"<<"֦������\t"<<"֦���뾶\t"<<endl;
	this->treeTrunk->displayBranches();
}