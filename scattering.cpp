#include <list>
#include "scattering.h" 
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
		Leaf leaf(position, stalkPosition, area, nVector, this->config);
		//leaf->display();
		leaves.push_back(leaf);
	}
    return true;
}
void GrowPoint::displayLeaves() {
	list<Leaf>::iterator iterLeaf = this->leaves.begin();
	for (; iterLeaf != this->leaves.end(); iterLeaf++) {
		(iterLeaf)->display();
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
list<Leaf> GrowPoint::generateLeavesList() {
	list<Leaf> leavesList = this->leaves;
	list<TreeTrunkBranch*>::iterator iterBranch = this->branches.begin();
	for (; iterBranch != this->branches.end(); iterBranch++ ) {
		leavesList.splice(leavesList.begin(), (*iterBranch)->generateLeavesList());
	}
	return leavesList;
}
list<Leaf> TreeTrunkBranch::generateLeavesList() {
	list<Leaf> leavesList;
	list<GrowPoint*>::iterator iterGPLeaf = this->growPointsLeaf.begin();
	for (; iterGPLeaf != this->growPointsLeaf.end(); iterGPLeaf++) {
		leavesList.splice(leavesList.begin(), (*iterGPLeaf)->generateLeavesList());
	}
	list<GrowPoint*>::iterator iterGPBranch = this->growPointsBranch.begin();
	for (; iterGPBranch != this->growPointsBranch.end(); iterGPBranch++) {
		leavesList.splice(leavesList.begin(), (*iterGPBranch)->generateLeavesList());
	}
	return leavesList;
}
bool Tree::generate() {
	this->treeTrunk->generateGrowPoints();
	return true;
}
void Tree::displayConfig() {
    this->config->display();
}
void Tree::displayLeaves() {
	cout<<"叶子"<<endl;
	cout<<"叶柄坐标\t"<<"叶子坐标\t"<<"叶子法向量\t"<<"叶片面积\t"<<endl;
	this->treeTrunk->displayLeaves();
}
void Tree::displayBranches() {
	cout<<"枝条"<<endl;
	cout<<"当前枝条递归层数\t"<<"起点坐标\t"<<"终点坐标\t"<<"枝条生长方向\t"<<"枝条长度\t"<<"枝条半径\t"<<endl;
	this->treeTrunk->displayBranches();
}
bool LeafScatter::init() {
    this->direction[0] = (this->points[1] - this->points[0]).getUnitDirection();
	this->direction[1] = (this->points[2] - this->points[1]).getUnitDirection();
	this->length[0] = (this->points[1] - this->points[0]).getModule();
	this->length[1] = (this->points[2] - this->points[1]).getModule();
    this->calculateAmplitudeFade();
	return true;
}
bool LeafScatter::calculatePolarAmplitude(Direction& inV, Direction& inH) {
	Direction in = inH + inV;
	Direction polarV0 = (this->direction[0] ^ this->direction[1]).getUnitDirection();
	Direction polarH0 = (polarV0 ^ this->direction[0]).getUnitDirection();
	Direction polarV1 = polarV0;
	Direction polarH1 = (this->direction[1] ^ polarV1).getUnitDirection();
	double amplitudeV0 = in * polarV0;
	double amplitudeH0 = in * polarH0;
	if (amplitudeV0 < 0) {
		polarV0 = -polarV0;
	    polarV1 = -polarV1;
		amplitudeV0 = -amplitudeV0;
	}
	if (amplitudeH0 < 0) {
		polarH0 = -polarH0;
	    polarH1 = -polarH1;
		amplitudeH0 = -amplitudeH0;
	}
	double crossSectionSqrt = sqrt(this->leaf.area);
	double amplitudeV1 = amplitudeV0 * this->amplitudeFade[0] * crossSectionSqrt;
	double amplitudeH1 = amplitudeH0 * this->amplitudeFade[1] * crossSectionSqrt;
	this->setAmplitude(amplitudeV1, amplitudeH1);
	this->setPolarization(polarV1, polarH1);
    return true;
}
bool LeafScatter::calculatePolarAmplitude(LeafScatter& pre) {
	Direction inV = pre.polarization[0] * pre.amplitude[0];
	Direction inH = pre.polarization[1] * pre.amplitude[1];
	this->calculatePolarAmplitude(inV, inH);
    return true;
}
void LeafScatter::setAmplitude(double v, double h) {
    this->amplitude[0] = v;
	this->amplitude[1] = h;
}
void LeafScatter::setPolarization(const Direction& vp, const Direction& hp) {
	this->polarization[0] = vp;
	this->polarization[1] = hp;
}
bool LeafScatter::calculateAmplitudeFade() {
    // TODO::
	this->amplitudeFade[0] = 1;
	this->amplitudeFade[1] = 1;
	return true;
}
bool LeafScatterPath::calculate(Direction& relativeV, const vector<Antenna>& ras) {
	this->calculateDirection();
	this->calculateVDoppler(relativeV);
	this->calculateFDopplerShift();
	this->calculateFrequency();
	this->calculateWaveLength();
	this->calculateLength();
	this->calculateDelayTime();
	this->calculateAmplitudeFade();
	this->calculateAmplitude();
	this->calculatePolarization();
	this->calculateAmplitudeReceive(ras);
	return true;
}
bool LeafScatterPath::calculateDirection() {
    LeafScatter first = this->leafScatters.front();
	LeafScatter last = this->leafScatters.back();
	this->tDirection = first.direction[0];
	this->rDirection = first.direction[1];
	return true;
}
bool LeafScatterPath::calculateVDoppler(Direction& relativeV) {
    list<LeafScatter>::iterator iter = this->leafScatters.begin();
	this->vDoppler = relativeV * iter->direction[0];
	for (; iter != this->leafScatters.end(); iter++) {
        this->vDoppler += relativeV * iter->direction[1];
	}
	return true;
}
bool LeafScatterPath::calculateFDopplerShift() {
    this->fDopplerShift = (double)this->vDoppler / C * F;
	return true;
}
bool LeafScatterPath::calculateFrequency() {
    this->frequency = (double)this->vDoppler / C * F + F;
	return true;
}
bool LeafScatterPath::calculateWaveLength() {
    this->waveLength = WAVE_LENGTH;
	return true;
}
bool LeafScatterPath::calculateAmplitude() {
	LeafScatter last = this->leafScatters.back();
    this->amplitude[0] = last.amplitude[0];
	this->amplitude[1] = last.amplitude[1];
	return true;
}

bool LeafScatterPath::calculateAmplitudeFade() {
    list<LeafScatter>::iterator iter = this->leafScatters.begin();
	this->amplitudeFade = 1 / ((4 * PI * iter->length[0]) / this->waveLength);
	for (; iter != this->leafScatters.end(); iter++) {
        this->amplitudeFade *= 1 / ((4 * PI * iter->length[0]) / this->waveLength);
	}
	return true;
}

bool LeafScatterPath::calculateAmplitudeReceive(const vector<Antenna>& ras) {
	Antenna a = ras[0];
	Direction amplitude = this->polarization[0] * this->amplitude[0] + this->polarization[1] * this->amplitude[1];
	amplitude = amplitude * this->amplitudeFade;
	this->amplitudeReceive[0] = amplitude * a.getVDirection();
	this->amplitudeReceive[1] = amplitude * a.getHDirection();
	return true;
}

bool LeafScatterPath::calculateDelayTime() {
    this->delayTime = this->totalLength / (C + this->vDoppler);
	return true;
}

bool LeafScatterPath::calculateLength() {
	list<LeafScatter>::iterator iter = this->leafScatters.begin();
	this->totalLength = iter->length[0];
	for (; iter != this->leafScatters.end(); iter++) {
        this->totalLength += iter->length[1];
	}
	return true;
}

bool LeafScatterPath::calculatePhase(double v, double h) {
	this->phase[0] = v;
	this->phase[1] = h;
	return true;
}

bool LeafScatterPath::calculatePolarization() {
	LeafScatter last = this->leafScatters.back();
    this->polarization[0] = last.polarization[0];
	this->polarization[1] = last.polarization[1];
	return true;
}
bool LeafScatterPath::calculateIr() {
	this->ir[0] = cos(this->phase[0]) * this->amplitudeReceive[0];
	this->ir[1] = cos(this->phase[1]) * this->amplitudeReceive[1];
	return true;
}
void LeafScatterPath::displayIr() {
}
void LeafScatterPath::displayVir() {
	cout<<pow(this->ir[0], 2)<<"\t";
}
void LeafScatterPath::displayHir() {
	cout<<pow(this->ir[1], 2)<<"\t";
}
void LeafScatterPath::displayPathTotalLength() {
    cout<<this->totalLength<<"\t";
}
void LeafScatterPath::displayAmplitudeV() {
    cout<<this->amplitudeReceive[0]<<"\t";
}
void LeafScatterPath::displayAmplitudeH() {
    cout<<this->amplitudeReceive[1]<<"\t";
}

bool MergePathModel::canMergeLeafScatterPath(LeafScatterPath& path1, LeafScatterPath& path2) {
    // TODO:
	if (path1.rDirection * path2.rDirection >= MERGE_DIRECTION_PROJECTION &&
		abs(path1.delayTime - path2.delayTime) <= MERGE_DELAY) {
	    return true;
	} else {
	    return false;
	}
}
bool MergePathModel::mergeLeafScatterPath(vector<LeafScatterPath> allPath) {
    cout<<"size of leaf scatter path:"<<allPath.size()<<endl;
	vector<LeafScatterPath>::iterator iter, iter2;
    iter = allPath.begin();
	for (; iter < allPath.end(); iter++) {
		if (!iter->isMerged()) {
			list<LeafScatterPath> leafScatterPaths;
			leafScatterPaths.push_back(*iter);
			for (iter2 = iter + 1; iter2 < allPath.end(); iter2++) {
				if (!iter2->isMerged()) {
					if (this->canMergeLeafScatterPath(*iter, *iter2)) {
						leafScatterPaths.push_back(*iter2);
						iter2->setMerged();
					}
				}
			}
			iter->setMerged();
			LeafScatterMergePath mergePath(leafScatterPaths);
			mergePath.calculate();
			this->leafScatterMergePaths.push_back(mergePath);
		}
	}
    cout<<"merged paths size:"<<this->leafScatterMergePaths.size()<<endl;
	return true;
	
}
bool LeafScatterMergePath::calculate() {
	this->calculateDirection();
	this->calculateVDoppler();
	this->calculateFDopplerShift();
	this->calculateFrequency();
	this->calculateWaveLength();
	this->calculateLength();
	this->calculateDelayTime();
	this->calculateAmplitudeFade();
	this->calculateAmplitudePolarization();
	this->calculateAmplitudeReceive();
	return true;
	return true;
}
bool LeafScatterMergePath::calculateDirection() {
	this->tDirection = this->refPath->tDirection;
	this->rDirection = this->refPath->rDirection;
	return true;
}
bool LeafScatterMergePath::calculateWaveLength() {
	this->waveLength = this->refPath->waveLength;
	return true;
}
bool LeafScatterMergePath::calculateVDoppler() {
	this->vDoppler = this->refPath->vDoppler;
	return true;
}
bool LeafScatterMergePath::calculateFDopplerShift() {
	this->fDopplerShift = this->refPath->fDopplerShift;
	return true;
}
bool LeafScatterMergePath::calculateFrequency() {
	this->fDopplerShift = this->refPath->frequency;
	return true;
}
bool LeafScatterMergePath::calculateLength() {
	this->totalLength = this->refPath->totalLength;
	return true;
}
bool LeafScatterMergePath::calculateDelayTime() {
	this->delayTime = this->refPath->delayTime;
	return true;
}

bool LeafScatterMergePath::calculateAmplitudePolarization() {
	Direction v(0,0,0), h(0,0,0);
	list<LeafScatterPath>::iterator iter = this->leafScatterPaths.begin();
    for (; iter != this->leafScatterPaths.end(); iter++) {
	    v += (iter->polarization[0] * iter->amplitude[0]);
	    h += (iter->polarization[1] * iter->amplitude[1]);
	}
	this->polarization[0] = v.getUnitDirection();
	this->polarization[1] = h.getUnitDirection();
	this->amplitude[0] = v.getModule();
	this->amplitude[1] = h.getModule();
	return true;
}
bool LeafScatterMergePath::calculateAmplitudeFade() {
	this->amplitudeFade = this->refPath->amplitudeFade;
	return true;
}
bool LeafScatterMergePath::calculateAmplitudeReceive() {
	double va = 0;
	double ha = 0;
	list<LeafScatterPath>::iterator iter = this->leafScatterPaths.begin();
    for (; iter != this->leafScatterPaths.end(); iter++) {
	    va += iter->amplitudeReceive[0];
	    ha += iter->amplitudeReceive[1];
	}
	this->amplitudeReceive[0] = va;
	this->amplitudeReceive[1] = ha;
	return true;
}
bool LeafScatterMergePath::calculatePhase(double v, double h) {
	this->phase[0] = v;
	this->phase[1] = h;
	return true;
}
bool LeafScatterMergePath::calculateIr() {
	this->ir[0] = cos(this->phase[0]) * this->amplitudeReceive[0];
	this->ir[1] = cos(this->phase[1]) * this->amplitudeReceive[1];
	return true;
}
void LeafScatterMergePath::displayIr() {
}
void LeafScatterMergePath::displayVir() {
	cout<<pow(this->ir[0], 2)<<"\t";
}
void LeafScatterMergePath::displayHir() {
	cout<<pow(this->ir[1], 2)<<"\t";
}
void LeafScatterMergePath::displayPathTotalLength() {
}
void LeafScatterMergePath::displayAmplitudeV() {
}
void LeafScatterMergePath::displayAmplitudeH() {
}
void MergePathModel::displayLeafScatterMergePathsSampleIR() {
	int i;
	cout<<endl;
	cout<<"Vertical polarization IR"<<endl;
	for (i = 0; i < sampleCount; i++) {	    
		this->calculateLeafScatterMergeImpulseResponse(i * sampleInterval);
		cout<<"t"<<(i + 1)<<"\t";
		this->displayLeafScatterMergePathVIR();
	}
		
	cout<<"Vertical polarization IR"<<endl;
	for (i = 0; i < sampleCount; i++) {	    
		this->calculateLeafScatterMergeImpulseResponse(i * sampleInterval);
		cout<<"t"<<(i + 1)<<"\t";
		this->displayLeafScatterMergePathHIR();
	}
}
void MergePathModel::displayLeafScatterMergePathHIR() {
	vector<LeafScatterMergePath>::iterator iterPath = this->leafScatterMergePaths.begin();
	for (; iterPath < this->leafScatterMergePaths.end(); iterPath++) {
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		iterPath->displayHir();
	}
	cout<<endl;
}
void MergePathModel::displayLeafScatterMergePathVIR() {
	vector<LeafScatterMergePath>::iterator iterPath = this->leafScatterMergePaths.begin();
	for (; iterPath < this->leafScatterMergePaths.end(); iterPath++) {
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		iterPath->displayVir();
	}
	cout<<endl;
}
bool MergePathModel::calculateLeafScatterMergeImpulseResponse(double t) {
	if (this->leafScatterMergePaths.size() == 0) {
		return false;
	}
	vector<LeafScatterMergePath>::iterator iterPath = this->leafScatterMergePaths.begin();
	double baseTao = iterPath->delayTime;
	for (; iterPath < this->leafScatterMergePaths.end(); iterPath++) {
		double tao = iterPath->delayTime;
		double tt = t - (tao - baseTao);
		// 两倍波长
		//double time = 1 / F * 200000000000000000000 + (tao - baseTao);
		//if (tt >= 0 && time >= tt) {
		if (tt >= 0) {
			// TODO:not sure
			double phaseShift = 2 * PI / iterPath->waveLength * C * tt;
			phaseShift += 2 * PI / iterPath->waveLength * iterPath->vDoppler * tt;
			iterPath->calculatePhase(phaseShift, phaseShift);
		} else {
			iterPath->calculatePhase(PI / 2, PI / 2);
		   
		}
		iterPath->calculateIr();
	}
	// TODO: return
	return true;
}
// 
void Tree::generateLeavesList() {
    this->leaves = this->treeTrunk->generateLeavesList();
	/*
    double xOri = this->location.x;
	double yOri = this->location.y;
	double zOri = this->location.z;
	double xInit = xOri - 0.5;
	double yInit = yOri - 0.5;
	double zInit = zOri - 0.5;
	double x, y, z;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				x = i * 0.1 + xInit;
				y = j * 0.1 + yInit;
				z = k * 0.1 + zInit;
			    Point p(x, y, z);
				double area = 0.01;
				Leaf leaf(p, area);
				this->leaves.push_back(leaf);
			}
		}
	}
	*/
}
void Tree::displayExcel() {
    this->location.displayExcel();
	cout<<endl;
}
bool TreeScatter::init() {
    this->direction[0] = (this->points[1] - this->points[0]).getUnitDirection();
	this->direction[1] = (this->points[2] - this->points[1]).getUnitDirection();
	this->length[0] = (this->points[1] - this->points[0]).getModule();
	this->length[1] = (this->points[2] - this->points[1]).getModule();
    this->calculateAmplitudeFade();
	return true;
}
bool TreeScatter::calculatePolarAmplitude(Direction& inV, Direction& inH) {
	Direction in = inH + inV;
	Direction polarV0 = (this->direction[0] ^ this->direction[1]).getUnitDirection();
	Direction polarH0 = (polarV0 ^ this->direction[0]).getUnitDirection();
	Direction polarV1 = polarV0;
	Direction polarH1 = (this->direction[1] ^ polarV1).getUnitDirection();
	double amplitudeV0 = in * polarV0;
	double amplitudeH0 = in * polarH0;
	if (amplitudeV0 < 0) {
		polarV0 = -polarV0;
	    polarV1 = -polarV1;
		amplitudeV0 = -amplitudeV0;
	}
	if (amplitudeH0 < 0) {
		polarH0 = -polarH0;
	    polarH1 = -polarH1;
		amplitudeH0 = -amplitudeH0;
	}
	double amplitudeV1 = amplitudeV0 * this->amplitudeFade[0];
	double amplitudeH1 = amplitudeH0 * this->amplitudeFade[1];
	this->setAmplitude(amplitudeV1, amplitudeH1);
	this->setPolarization(polarV1, polarH1);
    return true;
}
bool TreeScatter::calculatePolarAmplitude(TreeScatter& pre) {
	Direction inV = pre.polarization[0] * pre.amplitude[0];
	Direction inH = pre.polarization[1] * pre.amplitude[1];
	this->calculatePolarAmplitude(inV, inH);
    return true;
}
void TreeScatter::setAmplitude(double v, double h) {
    this->amplitude[0] = v;
	this->amplitude[1] = h;
}
void TreeScatter::setPolarization(const Direction& vp, const Direction& hp) {
	this->polarization[0] = vp;
	this->polarization[1] = hp;
}
bool TreeScatter::calculateAmplitudeFade() {
    // TODO::
	this->amplitudeFade[0] = 1;
	this->amplitudeFade[1] = 1;
	return true;
}
bool TreeScatterPath::calculate(Direction& relativeV, const vector<Antenna>& ras) {
	this->calculateVDoppler(relativeV);
	this->calculateFDopplerShift();
	this->calculateFrequency();
	this->calculateWaveLength();
	this->calculateLength();
	this->calculateDelayTime();
	this->calculateAmplitudeFade();
	this->calculateAmplitude();
	this->calculatepolarization();
	this->calculateAmplitudeReceive(ras);
	return true;
}

bool TreeScatterPath::calculateVDoppler(Direction& relativeV) {
    list<TreeScatter>::iterator iter = this->treeScatters.begin();
	this->vDoppler = relativeV * iter->direction[0];
	for (; iter != this->treeScatters.end(); iter++) {
        this->vDoppler += relativeV * iter->direction[1];
	}
	return true;
}
bool TreeScatterPath::calculateFDopplerShift() {
    this->fDopplerShift = (double)this->vDoppler / C * F;
	return true;
}
bool TreeScatterPath::calculateFrequency() {
    this->frequency = (double)this->vDoppler / C * F + F;
	return true;
}
bool TreeScatterPath::calculateWaveLength() {
    this->waveLength = WAVE_LENGTH;
	return true;
}
bool TreeScatterPath::calculateAmplitude() {
	TreeScatter last = this->treeScatters.back();
    this->amplitude[0] = last.amplitude[0];
	this->amplitude[1] = last.amplitude[1];
	return true;
}

bool TreeScatterPath::calculateAmplitudeFade() {
    list<TreeScatter>::iterator iter = this->treeScatters.begin();
	this->amplitudeFade = 1 / ((4 * PI * iter->length[0]) / this->waveLength);
	for (; iter != this->treeScatters.end(); iter++) {
        this->amplitudeFade *= 1 / ((4 * PI * iter->length[0]) / this->waveLength);
	}
	return true;
}

bool TreeScatterPath::calculateAmplitudeReceive(const vector<Antenna>& ras) {
	Antenna a = ras[0];
	Direction amplitude = this->polarization[0] * this->amplitude[0] + this->polarization[1] * this->amplitude[1];
	amplitude = amplitude * this->amplitudeFade;
	this->amplitudeReceive[0] = amplitude * a.getVDirection();
	this->amplitudeReceive[1] = amplitude * a.getHDirection();
	return true;
}

bool TreeScatterPath::calculateDelayTime() {
    this->delayTime = this->totalLength / (C + this->vDoppler);
	return true;
}

bool TreeScatterPath::calculateLength() {
	list<TreeScatter>::iterator iter = this->treeScatters.begin();
	this->totalLength = iter->length[0];
	for (; iter != this->treeScatters.end(); iter++) {
        this->totalLength += iter->length[1];
	}
	return true;
}

bool TreeScatterPath::calculatePhase(double v, double h) {
	this->phase[0] = v;
	this->phase[1] = h;
	return true;
}

bool TreeScatterPath::calculatepolarization() {
	TreeScatter last = this->treeScatters.back();
    this->polarization[0] = last.polarization[0];
	this->polarization[1] = last.polarization[1];
	return true;
}
bool TreeScatterPath::calculateIr() {
	this->ir[0] = cos(this->phase[0]) * this->amplitudeReceive[0];
	this->ir[1] = cos(this->phase[1]) * this->amplitudeReceive[1];
	return true;
}
void TreeScatterPath::displayIr() {
}
void TreeScatterPath::displayVir() {
	cout<<pow(this->ir[0], 2)<<"\t";
}
void TreeScatterPath::displayHir() {
	cout<<pow(this->ir[1], 2)<<"\t";
}
void TreeScatterPath::displayPathTotalLength() {
    cout<<this->totalLength<<"\t";
}
void TreeScatterPath::displayAmplitudeV() {
    cout<<this->amplitudeReceive[0]<<"\t";
}
void TreeScatterPath::displayAmplitudeH() {
    cout<<this->amplitudeReceive[1]<<"\t";
}