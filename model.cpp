#include <iostream>
#include <vector>
#include "model.h"

using namespace std;

Reflection* getReflection(const Surface& s, const Point& pt, const Point& pr) {
	const Point* symmetricPoint = &pt;
	if (symmetricPoint != NULL) {
	    Point* reflectPoint = getReflectPoint(s, *symmetricPoint, pr);
		if (reflectPoint != NULL) {
			double length = getDistance(pr, *reflectPoint);
			Direction direction(pr.x - reflectPoint->x, pr.y - reflectPoint->y, pr.z - reflectPoint->z);
			direction = getUnitDirection(direction);
			Reflection* reflection = new Reflection(length, *reflectPoint, pt, pr, s, direction);
			reflection->init();
			return reflection;
		} else {
		    return NULL;
		}
	} else {
	    return NULL;
	}
};
// 多段反射中第一段
Reflection* getFirstReflection(const Point& reflectPoint, const Point& pr, const Antenna& a) {
		double length = getDistance(pr, reflectPoint);
		Direction direction(pr.x - reflectPoint.x, pr.y - reflectPoint.y, pr.z - reflectPoint.z);
		direction = getUnitDirection(direction);

		Direction aDirection = a.getDirection();
		double aAmplitude = a.getAmplitude();
		Direction aAmplitudeDirection = a.getAmplitudeDirection();
	//	Direction h = getScalarProduct(direction, aDirection); 
	//	Direction v = getScalarProduct(h, direction);
		Direction dan = getScalarProduct(aAmplitudeDirection, direction);
		Direction v = getScalarProduct(direction, dan);
		if (v * aAmplitudeDirection < 0) {
		    v = -v;
		}
		Direction h(1,0,0);
		// TODO:correct?
	//	double hAmplitude = h * aAmplitudeDirection * aAmplitude;
		double vAmplitude = v * aAmplitudeDirection * aAmplitude;
        //new Reflection(length, reflectPoint, pr, direction);
		Reflection* reflection = new Reflection(length, reflectPoint, pr, direction);
	//	reflection->setHAmplitude(hAmplitude);
		reflection->setHAmplitude(0);
		reflection->setVAmplitude(vAmplitude);
	//	reflection->setH(h);
		reflection->setH(h);
		reflection->setV(v);
		reflection->setReflectAngle(0);

		return reflection;
};






// Vehicle




Point Vehicle::getP() const{
    return p;
}
void Vehicle::displayVehichle() {
	cout<<"  location:";
	this->p.display();
	cout<<"  velocity:"<<this->velocity;
	this->direction.display();
}
void Vehicle::displayVehichleExcel() {
	this->p.displayExcel();
	this->direction.displayExcel();
	cout<<this->velocity;
	cout<<endl;
}
// Path
double Path::getTotalLength() const{
	return this->totalLength;
}
void Path::calculateIr() {
	this->ir[0] = cos(this->vPhaseShift) * this->amplitudeReceive[0];
	this->ir[1] = cos(this->hPhaseShift) * this->amplitudeReceive[1];
}
void Path::init() {
	// 有待确认，百度百科电磁波的多普勒是这么计算的，但论文和书中都是用的第二种，暂用书中的方法

	// 第一种
	/*double v = this->relativeVelocity;
	double a = this->relativeAngle;
	this->frequency = sqrt((C + v) * (C - v) / pow((C - v * cos(a)), 2)) * F;
	this->waveLength = C / this->frequency;
	this->delayTime = this->totalLength / C;
	this->vDoppler = v * cos(a);
	this->amplitudeFade = 1 / ((4 * PI * this->totalLength) / this->waveLength);
	*/
	// 第二种
	
	this->frequency = F + (double)this->vDoppler / C * F;
	this->waveLength = WAVE_LENGTH;
	this->delayTime = this->totalLength / (C + this->vDoppler);
	this->vPhaseShift = this->initPhase[0];
	this->hPhaseShift = this->initPhase[1];
	this->amplitudeFade = 1 / ((4 * PI * this->totalLength) / this->waveLength);
}
// TODO:expect MIMO, SISO now
void Path::calculateAmplitudeReceive(const vector<Antenna>& ras) {
	Antenna a = ras[0];
	int size = this->reflections.size();
	Reflection r = this->reflections[size - 1];
	Direction h = r.getH();
	Direction v = r.getV();
	double hAmplitude = r.getHAmplitude();
	double vAmplitude = r.getVAmplitude();
	// TODO:相移
	double vAmplitudeReceive = (h * hAmplitude + v * vAmplitude) * a.getVDirection() * this->amplitudeFade;
	double hAmplitudeReceive = (h * hAmplitude + v * vAmplitude) * a.getHDirection() * this->amplitudeFade;
	this->setAmplitudeReceive(vAmplitudeReceive, hAmplitudeReceive);
}
void Path::displayPathTotalLength() {
    cout<<this->totalLength;
}
int Path::getNumOfReflect() const {
	return this->numOfReflect;
}
vector<Reflection> Path::getReflections() {
	return this->reflections;
}
void Path::stormEffect(Storm& storm) {
    this->stormFade = storm.fadePercent(this->totalLength);
	this->stormShift = storm.shiftRad(this->totalLength);
	this->amplitudeReceive[0] *= this->stormFade;
	this->amplitudeReceive[1] *= this->stormFade;
	this->vAmplitude *= this->stormFade;
	this->hAmplitude *= this->stormFade;
}
void Path::rainEffect(Rain& rain) {

}

int Model::isLOSExist() {
    //vector<DiffractPath>::const_iterator iterDiffractPath = this->diffractPaths.begin();
	int losBlocked = 1;
	for (int i = 0; i < this->diffractPaths.size(); i++) {
        int currentFlag = this->diffractPaths[i].diffraction.type;
		if (currentFlag ==3) {
			losBlocked = currentFlag;
			return losBlocked;
		} else if (currentFlag == 2) {
            losBlocked = currentFlag;
		}
	}
	return losBlocked;
}
DiffractPath* Model::diffractAffectLos(int& type) {
    type = 1;
	double loss = 0;
	double lossTemp = 0;
	DiffractPath* diffractPath = NULL;
	for (int i = 0; i < this->diffractPaths.size(); i++) {
        int currentFlag = this->diffractPaths[i].diffraction.type;
		if (currentFlag == 3) {
			type = currentFlag;		
			lossTemp = this->diffractPaths[i].diffraction.loss;
			if (lossTemp < loss) {
				diffractPath = &this->diffractPaths[i];
			}
		} else if (currentFlag == 2 && type != 3) {
            type = currentFlag;		
			lossTemp = this->diffractPaths[i].diffraction.loss;
			if (lossTemp < loss) {
				diffractPath = new DiffractPath(this->diffractPaths[i]);
			}
		}
	}
	return diffractPath;
}
// 构建单条完整传播路径()
// @pt:发射天线点
// @pr:接收天线点
// @surfaces:假定信号传播路径所经反射面的序列
// return: 若传播路径成立，返回Path对象；否则返回null
// Model
bool Model::getReflectPath(const Point& pt, const Point& pr, const vector<Surface>& surfaces) {
	vector<Point> symmetricPoints;
	vector<Point> reflectPoints;
	vector<Reflection> reflections;
	vector<Surface>::const_iterator iterSurfaces = surfaces.begin();
    vector<Surface>::const_reverse_iterator rIterSurfaces = surfaces.rbegin();
//	vector<Point>::const_reverse_iterator rIterSymmPoint = symmetricPoints.rbegin();
	vector<Reflection>::iterator iterReflection;
	double totalLength = 0;
	// 迭代计算发射车的镜像（对称）点
	symmetricPoints.push_back(pt);
	for (; iterSurfaces < surfaces.end(); iterSurfaces++) {
		Point* p = getSymmetricPoint(*iterSurfaces, symmetricPoints.back());
	    if (p != NULL) {
	    	symmetricPoints.push_back(*p);
			//delete p;
	    } else {
			//delete p;
	        return false;
	    }
	}

	// 迭代计算反射（入射）点，同时建立反射对象
	reflectPoints.push_back(pr);
	for (int i = surfaces.size() - 1; i >= 0; i--) {
		Reflection* reflection = getReflection(surfaces[i], symmetricPoints[i+1], reflectPoints.back());
		if (reflection != NULL) {
			reflection->init();
			Point* reflectPoint = getReflectPoint(surfaces[i], symmetricPoints[i+1], reflectPoints.back());
			reflectPoints.push_back(*reflectPoint);
			iterReflection = reflections.begin();
			reflections.insert(iterReflection, *reflection);
			totalLength += reflection->getLength();
	    } else {
	        return false;
	    }
	}

	// 建立第一段反射对象
	Reflection* reflection = getFirstReflection(pt, reflectPoints.back(), this->tAntennas[0]);
	reflection->init();
	totalLength += reflection->getLength();
	iterReflection = reflections.begin();
	reflections.insert(iterReflection, *reflection);

	// 计算多普勒、振幅衰减 
	double vPhaseShift = 0;
	double hPhaseShift = 0;
	unsigned size = reflections.size();
	for (unsigned j = 1; j < size; j++) {
		// TODO:checking!!!!
	    Reflection r1 = reflections[j - 1];
		Reflection r2 = reflections[j];
		Direction rd1 = r1.getDirection();
		Direction rd2 = r2.getDirection();
		Direction rn2 = r2.getV();
		// 振幅衰落
		Direction v1 = r1.getV();
		Direction h1 = r1.getH();
		Direction v2 = r2.getV();
		Direction h2 = r2.getH();

		// 注意差别
		double vAmplitude = (h1 * r1.getHAmplitude() + v1 * r1.getVAmplitude()) * v2 * r2.getAmplitudeFadeV();
		// 相移,配合计算振幅
		double BrewsterAngle = r2.getSurface().getMaterial().getBrewsterAngle();
		
		reflections[j].setVPhaseShift(PI);
		vPhaseShift += PI;
		// 相移180度
		if (vAmplitude < 0) {
			vAmplitude = -vAmplitude;
			reflections[j].setV(-v2);
		}
		/*
		if (vAmplitude < 0) {
			//reflections[i].setV(-v2);
			vAmplitude = -vAmplitude;
			v2 = -v2;
		} else {
			reflections[j].setV(-v2);
		}
		*/
		h2 = rd2 ^ v2;
		h2 = h2.getUnitDirection();
		double hAmplitude = (h1 * r1.getHAmplitude() + v1 * r1.getVAmplitude()) * h2 * r2.getAmplitudeFadeH();
		if (hAmplitude < 0) {
			reflections[j].setH(-h2);
			hAmplitude = -hAmplitude;
		}
		/*
		if (reflections[j].getReflectAngle() > BrewsterAngle) {
		    reflections[j].setHPhaseShift(PI);
			hPhaseShift += PI;
			if (hAmplitude < 0) {
			    reflections[i].setH(-h2);
			    hAmplitude = -hAmplitude;
		    }
		} else if (hAmplitude < 0) {
			reflections[j].setH(h2);
			hAmplitude = -hAmplitude;
		}
		*/
		reflections[j].setHAmplitude(hAmplitude);
		reflections[j].setVAmplitude(vAmplitude);	
	}

	int numberOfReflect = surfaces.size();

	// 多普勒
	Vehicle tx = this->getTransmitter();
	Vehicle rx = this->getReceiver();
	Direction txDirection = tx.getDirection();
	Direction rxDirection = rx.getDirection();
	Direction v = txDirection * tx.getVelocity() - rxDirection.getRelDirectOnReflect(surfaces) * rx.getVelocity();
	Direction vUnit = v.getUnitDirection();
	double relativeAngle = getAngleByVectors(vUnit, reflections[0].getDirection());
	double vt = txDirection * reflections[0].getDirection() * tx.getVelocity();
	double vr = rxDirection * reflections[size - 1].getDirection() * rx.getVelocity();
	double vDoppler = vt - vr;

	// TODO:
	// 
	//double f = sqrt((1 + vDoppler / C) / (1 - vDoppler / C)) * F;
	//double waveLength = C / f;


	
	Path* path = new Path(totalLength, numberOfReflect, reflections);
	//path->setHPhaseShift(hPhaseShift);
	//path->setVPhaseShift(vPhaseShift);
	//path->setHAmplitude(reflections[size - 1].getHAmplitude());
	//path->setVAmplitude(reflections[size - 1].getVAmplitude());
	//path->setV(reflections[size - 1].getV());
	//path->setH(reflections[size - 1].getH());
	// 初始相位都为0，振幅极化方向已做调整
	path->setInitPhase(0, 0);
	path->setVDoppler(vDoppler);
	path->setRelativeAnge(relativeAngle);
	path->setRelativeVelocity(v.getModule());
	path->setRelVelDirect(vUnit);
	path->init();
	path->calculateAmplitudeReceive(this->rAntennas);
	//path->setFrequency(f);
	//path->setWaveLength(waveLength);
	path->calculateFDopplerShift();
	path->calculatePhaseReceive();

	if (path != NULL) {
		insertPath(*path);
		
		return true;
	}
	//delete path;
	return false;
	//
};
bool Model::calculateLOSPath() {
	int diffractAffectLosType;
	//int isLOSExist = this->isLOSExist();
	DiffractPath *diffractPath = this->diffractAffectLos(diffractAffectLosType);
	Reflection* reflection = getFirstReflection(this->transmitter.getP(), this->receiver.getP(), this->tAntennas[0]);
	reflection->init();	
    if (diffractAffectLosType == 1) {
		if (!reflection->isBlocked(this->surfaces)) {
			vector<Reflection> reflections;
			reflections.push_back(*reflection);

			Vehicle tx = this->getTransmitter();
			Vehicle rx = this->getReceiver();
			Direction txDirection = tx.getDirection();
			Direction rxDirection = rx.getDirection();
			Direction v = txDirection * tx.getVelocity() - rxDirection * rx.getVelocity();
			Direction vUnit = getUnitDirection(v);
			double relativeAngle = getAngleByVectors(vUnit, reflections[0].getDirection());
			double vt = tx.getDirection() * reflections[0].getDirection() * tx.getVelocity();
			double vr = rx.getDirection() * reflections[0].getDirection() * rx.getVelocity();
			double vDoppler = vt - vr;
        
			Path* path = new Path(reflection->getLength(), 0, reflections);
			path->setInitPhase(0, 0);
			path->setVDoppler(vDoppler);
			path->setRelativeAnge(relativeAngle);
			path->setRelativeVelocity(v.getModule());
			path->setRelVelDirect(vUnit);
			path->init();
			path->calculateFDopplerShift();
			path->calculatePhaseReceive();
			path->calculateAmplitudeReceive(this->rAntennas);

			this->insertPath(*path);
		}
	} else if (diffractAffectLosType == 2) {
		if (!reflection->isBlocked(this->surfaces)) {
			double amplitudeFade = diffractPath->amplitudeFade;
			double amplitudeH = amplitudeFade * reflection->getHAmplitude();
			double amplitudeV = amplitudeFade * reflection->getVAmplitude();

			reflection->setHAmplitude(amplitudeH);
			reflection->setVAmplitude(amplitudeV);
			vector<Reflection> reflections;
			reflections.push_back(*reflection);

			Vehicle tx = this->getTransmitter();
			Vehicle rx = this->getReceiver();
			Direction txDirection = tx.getDirection();
			Direction rxDirection = rx.getDirection();
			Direction v = txDirection * tx.getVelocity() - rxDirection * rx.getVelocity();
			Direction vUnit = getUnitDirection(v);
			double relativeAngle = getAngleByVectors(vUnit, reflections[0].getDirection());
			double vt = tx.getDirection() * reflections[0].getDirection() * tx.getVelocity();
			double vr = rx.getDirection() * reflections[0].getDirection() * rx.getVelocity();
			double vDoppler = vt - vr;
        
			Path* path = new Path(reflection->getLength(), 0, reflections);		
			path->setInitPhase(0, 0);
			path->setVDoppler(vDoppler);
			path->setRelativeAnge(relativeAngle);
			path->setRelativeVelocity(v.getModule());
			path->setRelVelDirect(vUnit);
			path->init();
			path->calculateFDopplerShift();
			path->calculatePhaseReceive();
            path->calculateAmplitudeReceive(this->rAntennas);
			this->insertPath(*path);
		}
	}
	//delete path;
	// TODO:return 
	return true;
}
bool Model::calculateReflectPaths() {
	unsigned i = 0;
	unsigned j = 0;
    unsigned k = 0;
	switch (NUM_OF_REFLECTS) {
	    case 1:
            for (i = 0; i < this->surfaces.size(); i++) {
	            vector<Surface> s;
		        s.push_back(this->surfaces[i]);
				getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
	        }
			break;
	    case 2:
			for (i = 0; i < this->surfaces.size(); i++) {
	            vector<Surface> s;
		        s.push_back(this->surfaces[i]);
		        getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
		        
	        }
			for (i = 0; i < this->surfaces.size(); i++) {
		        for (j = 0; j < this->surfaces.size(); j++) {
					if (i == j) {
					    continue;
					}
	                vector<Surface> s;
		            s.push_back(this->surfaces[i]);
			        s.push_back(this->surfaces[j]);
		            getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
					
		        }
	        }
			break;
	    case 3:
			for (i = 0; i < this->surfaces.size(); i++) {
	            vector<Surface> s;
		        s.push_back(this->surfaces[i]);
		        getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
		        
	        }
			for (i = 0; i < this->surfaces.size(); i++) {
		        for (j = 0; j < this->surfaces.size(); j++) {
					if (i == j) {
					    continue;
					}
	                vector<Surface> s;
		            s.push_back(this->surfaces[i]);
			        s.push_back(this->surfaces[j]);
		            getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
					
		        }
	        }
			for (i = 0; i < this->surfaces.size(); i++) {
		        for (j = 0; j < this->surfaces.size(); j++) {
					if (i == j) {
						continue;
					}
					for (k = 0; k < this->surfaces.size(); k++) {
						if (j == k) {
							continue;
						}
	                    vector<Surface> s;
		                s.push_back(this->surfaces[i]);
			            s.push_back(this->surfaces[j]);
						s.push_back(this->surfaces[k]);
		                getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
		                
					}
		        }
	        }
			break;
		default:
			for (i = 0; i < this->surfaces.size(); i++) {
	            vector<Surface> s;
		        s.push_back(this->surfaces[i]);
                getReflectPath(this->transmitter.getP(), this->receiver.getP(), s);
		        
	        }
			break;
	}
	// TODO:return 
	return true;
}
bool Model::calculateStrongestPaths() {
	this->calculateLOSPath();
	this->calculateReflectPaths();
	int size = this->strongestPaths.size();
	vector<Path> paths = this->strongestPaths;
	if (this->strongestPaths.size() > NUM_OF_PATHS) {
		this->strongestPaths.erase(strongestPaths.begin() + NUM_OF_PATHS, strongestPaths.end());
	} 
	// TODO:return 
	return true;
};
bool Model::calculateDiffractPaths() {
	vector<Edge>::const_iterator iterEdges = edges.begin();
	for (; iterEdges < edges.end(); iterEdges++) {
        Point txp = this->transmitter.getP();
		Point rxp = this->receiver.getP();
		Diffraction diffract(txp, rxp, *iterEdges);
		diffract.init();
		DiffractPath* diffractPath = new DiffractPath(diffract);
		diffractPath->init(this->transmitter, this->receiver);
		diffractPath->calculateDiffractPath(this->tAntennas[0], this->rAntennas[0]);
		if (diffractPath->diffraction.loss != 0) {
			this->insertDiffractPath(*diffractPath);
		}
	} 
	int i = this->diffractPaths.size();
	return true;
};
bool Model::calculateMixPaths() {
    vector<Path>::iterator iterPath = this->surfaceScatterPaths.begin();
	vector<Edge>::iterator iterEdges = edges.begin();
	int segmentSize = 0;
	// 遍历每条路径
    for (; iterPath < this->surfaceScatterPaths.end(); iterPath++) {
        segmentSize = iterPath->reflections.size();
		vector<MixPathSegment> segments;
		// 遍历一条路径的每个分段
		for (int i = 0; i < segmentSize; i++) {
            Point txp = iterPath->reflections[i].reflectPoint;
		    Point rxp = iterPath->reflections[i].endPoint;
			int edgeSize = this->edges.size();
			// 对于每个分段，遍历刃形进行绕射验证
			double loss = 0;
			Diffraction* pDiffract = NULL;
			Reflection* pReflect = NULL;
            for (; iterEdges < edges.end(); iterEdges++) {
				Diffraction diffract(txp, rxp, *iterEdges);
				diffract.init();
                if (diffract.loss < loss) {
				    loss = diffract.loss;
					pDiffract = new Diffraction(diffract);
				}
			}
			if (pDiffract == NULL) {
			    pReflect = new Reflection(iterPath->reflections[i]);
			}
			MixPathSegment segment(pReflect, pDiffract);
			segments.push_back(segment);
		}
		Path* pPath = new Path(*iterPath);
		MixPath mixPath(pPath, segments);
		mixPath.init();
		mixPath.calculateAmplitude();
		mixPath.calculateAmplitudeReceive(this->rAntennas);
		this->mixPaths.push_back(mixPath);
	}
	return true;
};
bool Model::calculateSurfaceScatterPaths() {
	this->surfaceScatterPaths = this->strongestPaths;
    vector<Path>::iterator iterPath = this->surfaceScatterPaths.begin();
	for (; iterPath < this->surfaceScatterPaths.end(); iterPath++) {
		unsigned size = iterPath->reflections.size();
		vector<Reflection>& reflections = iterPath->reflections;
	    for (unsigned j = 1; j < size; j++) {
			// TODO:checking!!!!
			Reflection& r1 = reflections[j - 1];
			Reflection& r2 = reflections[j];
			// 参考高度
			r2.calculateHc(iterPath->waveLength);
            if (r2.surface.maxProtuberH >= r2.hc) {
				r2.calculateScatterFade(iterPath->waveLength);
			}
			double vAmplitude = r2.vAmplitude * r2.scatterFade;
			double hAmplitude = r2.hAmplitude * r2.scatterFade;
            reflections[j].setHAmplitude(hAmplitude);
			reflections[j].setVAmplitude(vAmplitude);		
		}
		iterPath->calculateAmplitudeReceive(this->rAntennas);
	}
	return true;
};
bool Model::calculateLeafScatterPaths() {
	int i = 0;
	int j = 0;
	int k = 0;
	/*
	for (int a = 0; a < 2; a++){
		list<Leaf> leaves;
		Point p(10, 10, 1.5);
		Leaf leaf(p, 0.01);
		leaves.push_back(leaf);
		this->calculateLeafScatterPath(leaves);
	}	
	*/
			
	vector<Tree>::iterator tIter = this->trees.begin();
    switch (NUM_OF_SCATTER) {
	    case 1:
			for (; tIter < this->trees.end(); tIter++) {
				list<Leaf> currentLeaves = tIter->getLeaves();
				list<Leaf>::iterator lIter = currentLeaves.begin();
				for (; lIter != currentLeaves.end(); lIter++) {
	                list<Leaf> leaves;
					Leaf leaf(*lIter);
				    leaves.push_back(leaf);
				    this->calculateLeafScatterPath(leaves);
				}
			}
		    cout<<"";
			break;
    	case 2:
			break;
	    case 3:
			break;
		default:
			break;
	}
	
	return true;
};
bool Model::calculateLeafScatterPath(list<Leaf> l) {
	list<Leaf>::const_iterator iter = l.begin();
	list<LeafScatter> ls;
	vector<Point> points;
	
	points.push_back(this->transmitter.p);
	for (; iter != l.end(); iter++) {
		points.push_back(iter->getPosition());
	}
	points.push_back(this->receiver.p);
	vector<Point>::iterator iterPoints = points.begin();

	iter = l.begin();
	for (; iter != l.end(); iter++) {
		LeafScatter scatter(*iter);
		Point p0 = *iterPoints;
		iterPoints++;
		Point p1 = *iterPoints;
		iterPoints++;
		Point p2 = *iterPoints;
		scatter.points[0] = p0;
		scatter.points[1] = p1;
		scatter.points[2] = p2;
		scatter.init();
		ls.push_back(scatter);
		iterPoints--;
	}

	list<LeafScatter>::iterator iterScatter = ls.begin();

	// TODO::
	Antenna a = this->tAntennas[0];
	Direction aAmplitude = a.getAmplitudeDirection() * a.getAmplitude();
	Direction tempD = iterScatter->direction[0] * (aAmplitude * iterScatter->direction[0]);
	Direction initPolarA = aAmplitude - tempD;
	iterScatter->calculatePolarAmplitude(initPolarA, Direction(0, 0, 0));
	LeafScatter pre = *iterScatter;
	iterScatter++;
	for (; iterScatter != ls.end(); iterScatter++) {
	    iterScatter->calculatePolarAmplitude(pre);
		pre = *iterScatter;
	}
	LeafScatterPath path(ls);
	path.leafScatters = ls;

	Direction relV = (this->transmitter.direction * this->transmitter.velocity - this->receiver.direction * this->receiver.velocity);
	path.calculate(relV, this->rAntennas);
	this->insertLeafScatterPath(path);
	return true;
};
void Model::insertLeafScatterPath(const LeafScatterPath& newPath) {
	if (this->leafScatterPaths.empty()) { 
		leafScatterPaths.push_back(newPath);
	} else {
		vector<LeafScatterPath>::reverse_iterator rIter;
		bool flag = true;
		for (rIter = this->leafScatterPaths.rbegin(); rIter < this->leafScatterPaths.rend(); ++rIter) {
		//	rIter++;
			double t1 = rIter->totalLength;
			double t2 = newPath.totalLength;
			if (t1 < t2) {
				// TODO: 有错
				this->leafScatterPaths.insert(rIter.base(), newPath);
				flag = false;
				break;
			}
		}
		if (flag) {
		    this->leafScatterPaths.insert(rIter.base(), newPath);
		}
	}
};
bool Model::calculateTreeScatterPaths() {
	int i = 0;
	int j = 0;
	int k = 0;
    switch (NUM_OF_SCATTER) {
	    case 1:
			for (i = 0; i < this->trees.size(); i++) {
	            list<Tree> t;
				t.push_back(this->trees[i]);
				this->calculateTreeScatterPath(t);
	        }
			break;
    	case 2:
			break;
	    case 3:
			break;
		default:
			break;
	}
	return true;
};
bool Model::calculateTreeScatterPath(list<Tree> t) {
	list<Tree>::const_iterator iter = t.begin();
	list<TreeScatter> ts;
	list<Point> points;
	
	points.push_back(this->transmitter.p);
	for (; iter != t.end(); iter++) {
		points.push_back(iter->getLocation());
	}
	points.push_back(this->receiver.p);
	list<Point>::iterator iterPoints = points.begin();

	iter = t.begin();
	for (; iter != t.end(); iter++) {
		TreeScatter scatter(*iter);
		scatter.points[0] = *iterPoints;
        iterPoints++;
		scatter.points[1] = *iterPoints;
        iterPoints++;
		scatter.points[2] = *iterPoints;
		iterPoints--;
		scatter.init();
		ts.push_back(scatter);
	}

	list<TreeScatter>::iterator iterScatter = ts.begin();

	// TODO::
	Antenna a = this->tAntennas[0];
	Direction aAmplitude = a.getAmplitudeDirection() * a.getAmplitude();
	Direction tempD = iterScatter->direction[0] * (aAmplitude * iterScatter->direction[0]);
	Direction initPolarA = aAmplitude - tempD;
	iterScatter->calculatePolarAmplitude(initPolarA, Direction(0, 0, 0));
	TreeScatter pre = *iterScatter;
	iterScatter++;
	for (; iterScatter != ts.end(); iterScatter++) {
	    iterScatter->calculatePolarAmplitude(pre);
		pre = *iterScatter;
	}
	TreeScatterPath path(ts);

	Direction relV = (this->transmitter.direction * this->transmitter.velocity - this->receiver.direction * this->receiver.velocity);
	path.calculate(relV, this->rAntennas);
	this->insertTreeScatterPath(path);
	return true;
};
void Model::insertTreeScatterPath(const TreeScatterPath& newPath) {
	if (this->treeScatterPaths.empty()) { 
		treeScatterPaths.push_back(newPath);
	} else {
		vector<TreeScatterPath>::reverse_iterator rIter;
		bool flag = true;
		for (rIter = this->treeScatterPaths.rbegin(); rIter < this->treeScatterPaths.rend(); ++rIter) {
		//	rIter++;
			double t1 = rIter->totalLength;
			double t2 = newPath.totalLength;
			if (t1 < t2) {
				// TODO: 有错
				this->treeScatterPaths.insert(rIter.base(), newPath);
				flag = false;
				break;
			}
		}
		if (flag) {
		    this->treeScatterPaths.insert(rIter.base(), newPath);
		}
	}
};
void Model::insertPath(const Path& newPath) {
	if (strongestPaths.empty()) { 
		strongestPaths.push_back(newPath);
	} else {
		vector<Path>::reverse_iterator rIter;
		bool flag = true;
		for (rIter = strongestPaths.rbegin(); rIter < strongestPaths.rend(); ++rIter) {
		//	rIter++;
			double t1 = rIter->getTotalLength();
			double t2 = newPath.getTotalLength();
			if (t1 < t2) {
				// TODO: 有错
				strongestPaths.insert(rIter.base(), newPath);
				flag = false;
				break;
			}
		}
		if (flag) {
		    strongestPaths.insert(rIter.base(), newPath);
		}
	}
};
void Model::insertDiffractPath(const DiffractPath& newDiffractPath) {
	if (this->diffractPaths.empty()) { 
		diffractPaths.push_back(newDiffractPath);
	} else {
		vector<DiffractPath>::reverse_iterator rIter;
		vector<DiffractPath>::reverse_iterator rIter2;
		bool flag = true;
		rIter = diffractPaths.rbegin();
		rIter2 = diffractPaths.rbegin();
		for (; rIter < diffractPaths.rend(); rIter++, rIter2++) {
			if (rIter->totalLength < newDiffractPath.totalLength) {
				diffractPaths.insert(rIter2.base(), newDiffractPath);
				flag = false;
				break;
			}
		}
		if (flag) {
		    diffractPaths.insert(rIter.base(), newDiffractPath);
		}
	}
};
bool Model::calculateStormPaths() {
    vector<Path>::iterator iter = this->strongestPaths.begin();
	for (; iter < this->strongestPaths.end(); iter++) {
	    iter->stormEffect(*(this->storm));
	}
	return true;
}
bool Model::calculateImpulseResponse(double t) {
	vector<Path>::iterator iterPath = this->strongestPaths.begin();
	double baseTao = iterPath->getDelayTime();
	for (; iterPath < this->strongestPaths.end(); iterPath++) {
		//iterPath->calculateIr();
		
		double tao = iterPath->getDelayTime();
		double tt = t - (tao - baseTao);
		// 两倍波长
		//double time = 1 / F * 200000000000000000000 + (tao - baseTao);
		//if (tt >= 0 && time >= tt) {
		if (tt >= 0) {
			// TODO:not sure
			double phaseShift = 2 * PI / iterPath->getWaveLength() * C * tt;
			phaseShift += 2 * PI / iterPath->getWaveLength() * iterPath->getVDoppler() * tt;
			// TODO:相移往哪方向移动
			phaseShift += iterPath->stormShift; 
			//double vInitPhase = iterPath->getVInitPhase();
			//double hInitPhase = iterPath->getHInitPhase();
			iterPath->setVPhaseShift(phaseShift);
			iterPath->setHPhaseShift(phaseShift);
		} else {
			iterPath->setVPhaseShift(PI / 2);
			iterPath->setHPhaseShift(PI / 2);
		   
		}
		iterPath->calculateIr();
	}
	// TODO: return
	return true;
}
bool Model::calculateDiffractImpulseResponse(double t) {
	if (this->diffractPaths.size() == 0) {
		return false;
	}
	vector<DiffractPath>::iterator iterPath = this->diffractPaths.begin();
	double baseTao = iterPath->delayTime;
	for (; iterPath < this->diffractPaths.end(); iterPath++) {
		//iterPath->calculateIr();
		
		double tao = iterPath->delayTime;
		double tt = t - (tao - baseTao);
		// 两倍波长
		//double time = 1 / F * 200000000000000000000 + (tao - baseTao);
		//if (tt >= 0 && time >= tt) {
		if (tt >= 0) {
			// TODO:not sure
			double phaseShift = 2 * PI / iterPath->waveLength * C * tt;
			phaseShift += 2 * PI / iterPath->waveLength * iterPath->vDoppler * tt;
			//double vInitPhase = iterPath->getVInitPhase();
			//double hInitPhase = iterPath->getHInitPhase();
			iterPath->setPhase(phaseShift, phaseShift);
		} else {
			iterPath->setPhase(PI / 2, PI / 2);
		   
		}
		iterPath->calculateIr();
	}
	// TODO: return
	return true;
}
bool Model::calculateMixImpulseResponse(double t) {
	if (this->mixPaths.size() == 0) {
		return false;
	}
	vector<MixPath>::iterator iterPath = this->mixPaths.begin();
	double baseTao = iterPath->delayTime;
	for (; iterPath < this->mixPaths.end(); iterPath++) {
		//iterPath->calculateIr();
		
		double tao = iterPath->delayTime;
		double tt = t - (tao - baseTao);
		// 两倍波长
		//double time = 1 / F * 200000000000000000000 + (tao - baseTao);
		//if (tt >= 0 && time >= tt) {
		if (tt >= 0) {
			// TODO:not sure
			double phaseShift = 2 * PI / iterPath->waveLength * C * tt;
			phaseShift += 2 * PI / iterPath->waveLength * iterPath->vDoppler * tt;
			//double vInitPhase = iterPath->getVInitPhase();
			//double hInitPhase = iterPath->getHInitPhase();
			iterPath->setPhase(phaseShift, phaseShift);
		} else {
			iterPath->setPhase(PI / 2, PI / 2);
		   
		}
		iterPath->calculateIr();
	}
	// TODO: return
	return true;
}
bool Model::calculateSurfaceScatterImpulseResponse(double t) {
	if (this->surfaceScatterPaths.size() == 0) {
		return false;
	}
	vector<Path>::iterator iterPath = this->surfaceScatterPaths.begin();
	double baseTao = iterPath->delayTime;
	for (; iterPath < this->surfaceScatterPaths.end(); iterPath++) {
		//iterPath->calculateIr();
		
		double tao = iterPath->delayTime;
		double tt = t - (tao - baseTao);
		// 两倍波长
		//double time = 1 / F * 200000000000000000000 + (tao - baseTao);
		//if (tt >= 0 && time >= tt) {
		if (tt >= 0) {
			// TODO:not sure
			double phaseShift = 2 * PI / iterPath->waveLength * C * tt;
			phaseShift += 2 * PI / iterPath->waveLength * iterPath->vDoppler * tt;
			//double vInitPhase = iterPath->getVInitPhase();
			//double hInitPhase = iterPath->getHInitPhase();
			iterPath->setVPhaseShift(phaseShift);
			iterPath->setHPhaseShift(phaseShift);
		} else {
			iterPath->setVPhaseShift(PI / 2);
			iterPath->setHPhaseShift(PI / 2);
		}
		iterPath->calculateIr();
	}
	// TODO: return
	return true;
}
bool Model::calculateTreeScatterImpulseResponse(double t) {
	if (this->treeScatterPaths.size() == 0) {
		return false;
	}
	vector<TreeScatterPath>::iterator iterPath = this->treeScatterPaths.begin();
	double baseTao = iterPath->delayTime;
	for (; iterPath < this->treeScatterPaths.end(); iterPath++) {
		//iterPath->calculateIr();
		
		double tao = iterPath->delayTime;
		double tt = t - (tao - baseTao);
		// 两倍波长
		//double time = 1 / F * 200000000000000000000 + (tao - baseTao);
		//if (tt >= 0 && time >= tt) {
		if (tt >= 0) {
			// TODO:not sure
			double phaseShift = 2 * PI / iterPath->waveLength * C * tt;
			phaseShift += 2 * PI / iterPath->waveLength * iterPath->vDoppler * tt;
			//double vInitPhase = iterPath->getVInitPhase();
			//double hInitPhase = iterPath->getHInitPhase();
			iterPath->calculatePhase(phaseShift, phaseShift);
		} else {
			iterPath->calculatePhase(PI / 2, PI / 2);
		}
		iterPath->calculateIr();
	}
	// TODO: return
	return true;
}
// TODO:unsed, solved in getReflectPath()
bool Model::calculateAmplitude() {
	
	vector<Path>::iterator iterPaths = this->strongestPaths.begin();
	for (unsigned i = 0; i < this->strongestPaths.size(); i++) {	

		for(unsigned j = 1; j < this->strongestPaths[i].getReflections().size(); j++) {
			Reflection r1 = this->strongestPaths[i].getReflections()[j - 1];
			Reflection r2 = this->strongestPaths[i].getReflections()[j];
			double hAmplitude = r1.getH() * r2.getH() * r1.getHAmplitude() * r2.getAmplitudeFadeH();
			double vAmplitude = r1.getV() * r2.getV() * r1.getVAmplitude() * r2.getAmplitudeFadeV();
			this->strongestPaths[i].getReflections()[j].setHAmplitude(hAmplitude);
			this->strongestPaths[i].getReflections()[j].setVAmplitude(vAmplitude);
			//this->strongestPaths[i].getReflections()[j].calculateAmplitudeFadeH();
			//this->strongestPaths[i].getReflections()[j].calculateAmplitudeFadeV();
		}
	}
	return true;
}
vector<Path> Model::getStrongestPaths() const{
	return this->strongestPaths;
}

void Model::displayPathIR() {
	unsigned i;
	for(i = 0; i < this->strongestPaths.size(); i++) {	
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		Path path = this->strongestPaths.at(i);
		path.displayVir();
		
	}
	cout<<endl;
	for(i = 0; i < this->strongestPaths.size(); i++) {
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		Path path = this->strongestPaths.at(i);
		path.displayHir();
		
	}
	cout<<endl;
}

void Model::displayPathVIR() {
	for(unsigned i = 0; i < this->strongestPaths.size(); i++) {	
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		Path path = this->strongestPaths.at(i);
		path.displayVir();
	}
	cout<<endl;
}
void Model::displayPathHIR() {
	for(unsigned i = 0; i < this->strongestPaths.size(); i++) {	
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		Path path = this->strongestPaths.at(i);
		path.displayHir();
		
	}
	cout<<endl;
}

void Model::displaySurfaceScatterPathVIR() {
	for(unsigned i = 0; i < this->surfaceScatterPaths.size(); i++) {	
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		Path path = this->surfaceScatterPaths.at(i);
		path.displayVir();
	}
	cout<<endl;
}
void Model::displaySurfaceScatterPathHIR() {
	for(unsigned i = 0; i < this->surfaceScatterPaths.size(); i++) {	
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		Path path = this->surfaceScatterPaths.at(i);
		path.displayHir();
		
	}
	cout<<endl;
}
void Model::displayTreeScatterPathVIR() {
	cout.setf(ios::fixed);
	cout.precision(10);
	cout.unsetf(ios_base::fixed);
	for(unsigned i = 0; i < this->treeScatterPaths.size(); i++) {	
		TreeScatterPath path = this->treeScatterPaths.at(i);
		path.displayVir();
	}
	cout<<endl;
}
void Model::displayTreeScatterPathHIR() {
	for(unsigned i = 0; i < this->treeScatterPaths.size(); i++) {	
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		TreeScatterPath path = this->treeScatterPaths.at(i);
		path.displayHir();		
	}
	cout<<endl;
}
void Model::displayTreeScatterPathsAmplitude() {
    cout<<"V:\t";
	vector<TreeScatterPath>::iterator iter = this->treeScatterPaths.begin();
	for (; iter < this->treeScatterPaths.end(); iter++) {
		iter->displayAmplitudeV();
	}
	cout<<endl;
	cout<<"H:\t";
	iter = this->treeScatterPaths.begin();
	for (; iter < this->treeScatterPaths.end(); iter++) {
		iter->displayAmplitudeH();
	}
	cout<<endl;
}
void Model::displayDiffractPathVIR() {
	vector<DiffractPath>::iterator iterDiffractPaths = this->diffractPaths.begin();
	for (; iterDiffractPaths < this->diffractPaths.end(); iterDiffractPaths++) {
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		iterDiffractPaths->displayVir();
	}
	cout<<endl;
}
void Model::displayDiffractPathHIR() {
	vector<DiffractPath>::iterator iterDiffractPaths = this->diffractPaths.begin();
	for (; iterDiffractPaths < this->diffractPaths.end(); iterDiffractPaths++) {
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		iterDiffractPaths->displayHir();
	}
	cout<<endl;
}
void Model::displayMixPathVIR() {
	vector<MixPath>::iterator iterMixPath = this->mixPaths.begin();
	for (; iterMixPath < this->mixPaths.end(); iterMixPath++) {
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		iterMixPath->displayVir();
	}
	cout<<endl;
}
void Model::displayMixPathHIR() {
	vector<MixPath>::iterator iterMixPath = this->mixPaths.begin();
	for (; iterMixPath < this->mixPaths.end(); iterMixPath++) {
		cout.setf(ios::fixed);
		cout.precision(10);
		cout.unsetf(ios_base::fixed);
		iterMixPath->displayHir();
	}
	cout<<endl;
}
void Model::displayPath() {
	cout<<"num of paths:"<<this->strongestPaths.size()<<endl;
	for(unsigned i = 0; i < this->strongestPaths.size(); i++) {
		Path path = this->strongestPaths.at(i);
		cout<<i+1<<"th path:"<<endl;
		cout.setf(ios::fixed);
		cout.precision(10);
		
	    cout<<"  total length:"<<this->strongestPaths.at(i).getTotalLength()<<endl;
		cout<<"  delay time:"<<this->strongestPaths.at(i).getDelayTime()<<endl;
		cout<<"  frequency:"<<path.getFrequency()<<endl;
		cout<<"  frequency shift:"<<path.getFDopplerShift()<<endl;
		cout<<"  wavelength:"<<path.getWaveLength()<<endl;
		
		cout.unsetf(ios_base::fixed);

		Direction tDirection = path.getReflections().begin()->getDirection();
		Direction rDirection = path.getReflections().at(path.getNumOfReflect()).getDirection();
		cout<<"  transmit direction:("<<tDirection.i<<","<<tDirection.j<<","<<tDirection.k<<")"<<endl;
		cout<<"  receive  direction:("<<rDirection.i<<","<<rDirection.j<<","<<rDirection.k<<")"<<endl;
		cout<<"  h:("<<path.getH().i<<","<<path.getH().j<<","<<path.getH().k<<")"<<path.getHAmplitude()<<endl;
		cout<<"  v:("<<path.getV().i<<","<<path.getV().j<<","<<path.getV().k<<")"<<path.getVAmplitude()<<endl;
		cout<<"  h shift:"<<path.getHPhaseShift()<<endl;
		cout<<"  v shift:"<<path.getVPhaseShift()<<endl;

		path.displayIR();

		cout<<"  num of reflect :"<<this->strongestPaths.at(i).getNumOfReflect()<<endl;
		cout<<"  reflections:"<<"num:"<<this->strongestPaths.at(i).getReflections().size()<<endl;
		
		for(unsigned j = 0; j <= this->strongestPaths.at(i).getReflections().size()-1 ; j++) {
			cout<<"   "<<(j + 1)<<"th reflection:"<<endl;
			Reflection r = this->strongestPaths.at(i).getReflections().at(j);
		    Direction d = r.getDirection();
			Point p = r.getReflectPoint();
			Surface s = r.getSurface();
			Direction nVector = s.getNVector();
			double length = r.getLength();
			cout<<"    direction: ("<<d.i<<","<<d.j<<","<<d.k<<")"<<endl;
			cout<<"    reflect point:("<<p.x<<","<<p.y<<","<<p.z<<")"<<endl;

			if (j != 0) {
				cout<<"    n:("<<nVector.i<<","<<nVector.j<<","<<nVector.k<<")"<<endl;
			}
			cout<<"    h:("<<r.getH().i<<","<<r.getH().j<<","<<r.getH().k<<")"<<r.getHAmplitude()<<endl;
			cout<<"    v:("<<r.getV().i<<","<<r.getV().j<<","<<r.getV().k<<")"<<r.getVAmplitude()<<endl;
			cout<<"    h fade:"<<r.getAmplitudeFadeH()<<endl;
			cout<<"    v fade:"<<r.getAmplitudeFadeV()<<endl;
			cout<<"    reflect angle:"<<r.getReflectAngle()<<endl;
			cout<<"    length:"<<length<<endl;
		}
		
	}
}
double Reflection::getLength() const {
	return this->length;
};
Point Reflection::getReflectPoint() const {
	return this->reflectPoint;
};
Direction Reflection::getH() const {
	return this->h; 
}
Direction Reflection::getV() const {
	return this->v; 
}
Surface Reflection::getSurface() const {
	return this->surface;
}
Reflection::Reflection(double length, 
		       const Point& reflectPoint, 
			   const Point& startPoint, 
			   const Point& endPoint, 
			   const Surface& surface, 
			   const Direction& direction):
	           length(length),
			   reflectPoint(reflectPoint),
			   startPoint(startPoint),
			   endPoint(endPoint),
			   surface(surface),
			   direction(direction) {
	this->v = getScalarProduct(surface.getNVector(), direction);
	this->h = getScalarProduct(direction, this->v);
	this->reflectAngle = calculateReflectAngle(surface.getNVector(), direction);
	    this->vPhaseShift = 0;
	    this->hPhaseShift = 0;
}
Reflection::Reflection(double length, 
	       const Point& reflectPoint, 
		   const Point& endPoint, 
		   const Direction& direction):
           length(length),
		   reflectPoint(reflectPoint),
		   startPoint(startPoint),
		   endPoint(endPoint),
		   surface(surface),
		   direction(direction) {
			   this->amplitudeFadeV = 1;
			   this->amplitudeFadeH = 1;
			   this->vPhaseShift = 0;
			   this->hPhaseShift = 0;
}
bool Reflection::calculateVH() {
	this->v = getScalarProduct(this->direction, this->surface.getNVector());
	this->h = getScalarProduct(this->direction, this->v);
	return true;
}
bool Reflection::calculateAmplitudeFadeV() {
	double n = this->surface.getMaterial().getN();
	double x = this->reflectAngle;
	double b = sqrt(pow(n, 2) - pow(sin(x), 2));
	double a = cos(x);
	this->amplitudeFadeV = (a - b) / (a + b);
	return false;
}
bool Reflection::calculateAmplitudeFadeH() {
	double n = this->surface.getMaterial().getN();
	double x = this->reflectAngle;
	double b = sqrt(n * n - sin(x) * sin(x));
	double a = cos(x) * pow(n, 2);
	this->amplitudeFadeH =  (a - b) / (a + b);
	return true;
}
void Reflection::init() {
	this->calculateVH();
	this->calculateAmplitudeFadeH();
	this->calculateAmplitudeFadeV();
	this->scatterFade = 1;
	//this->calculateHc();
}
bool Reflection::calculateHc(double waveLength) {
    // 入射角的定义，移动通信中的和几何光学中不一致，cos
    this->hc = waveLength / (8 * cos(this->reflectAngle));
	return true;
}
bool Reflection::calculateScatterFade(double waveLength) {
    double a = PI * this->surface.protuberHStandDeviat;
	double b = a * sin(this->reflectAngle);
	double c = b / waveLength;
	double n = c * c;
	// 入射角的定义，移动通信中的和几何光学中不一致，cos
    double exponent = -8 * pow((PI * this->surface.protuberHStandDeviat * cos(this->reflectAngle) / waveLength), 2);
	this->scatterFade = pow(E, exponent);
	return true;
}
Direction Reflection::getDirection() const {
	return this->direction;
}
bool Reflection::isBlocked(vector<Surface>& surfaces) {
    vector<Surface>::iterator iterSurface = surfaces.begin();
	for (; iterSurface < surfaces.end(); iterSurface++) {
		if (iterSurface->isOutLine(this->endPoint, this->reflectPoint)) {
		    continue;
		} else if (this->direction * iterSurface->getNVector() != 0) {
			Point p0(this->reflectPoint);
			Point p1(this->endPoint);
			if (iterSurface->isIntersectPointThrough(p0, p1)) {
			    return true;
			}
		}
	}
	return false;
}
void DiffractPath::init(Vehicle& tx, Vehicle& rx) {
    this->totalLength = this->diffraction.inLength + this->diffraction.outLength;
	// 有待确认，百度百科电磁波的多普勒是这么计算的，但论文和书中都是用的第二种，暂用书中的方法

	// 第一种
	/*double v = this->relativeVelocity;
	double a = this->relativeAngle;
	this->frequency = sqrt((C + v) * (C - v) / pow((C - v * cos(a)), 2)) * F;
	this->waveLength = C / this->frequency;
	this->delayTime = this->totalLength / C;
	this->vDoppler = v * cos(a);
	*/
	// 第二种
	this->vDoppler = tx.getDirection() * this->diffraction.inDirect * tx.getVelocity() - rx.getDirection() * this->diffraction.outDirect * rx.getVelocity();
	this->frequency = F + (double)this->vDoppler / C * F;
	this->waveLength = WAVE_LENGTH;
	this->delayTime = this->totalLength / (C + this->vDoppler);
	if (this->diffraction.loss == 0) {
	    this->amplitudeFade = 0;
	} else {
	    this->amplitudeFade = pow(10, (this->diffraction.loss / 20));
        this->amplitudeFade *= 1 / ((4 * PI * this->totalLength) / this->waveLength);
	}

}
void DiffractPath::calculateIr() {
	this->ir[0] = cos(this->phase[0]) * this->aReceive[0];
	this->ir[1] = cos(this->phase[1]) * this->aReceive[1];
}
double dBamplitudeConvert(double loss) {
	double a = pow(10, (loss/20));
	return a;
}
int DiffractPath::isLosBlocked() {
    return this->diffraction.isLosBlocked();
}
void DiffractPath::calculateDiffractPath(
		  const Antenna& tAntenna,
		  const Antenna& rAntenna) {  
		double aAmplitude = tAntenna.getAmplitude();
		Direction aAmplitudeDirection = tAntenna.getAmplitudeDirection();
		if (this->diffraction.inDirect == this->diffraction.outDirect) {
			Direction dan = getScalarProduct(aAmplitudeDirection, this->diffraction.inDirect);
			Direction v = getScalarProduct(this->diffraction.inDirect, dan);
			if (v * aAmplitudeDirection < 0) {
			    v = -v;
			}
			Direction h(1,0,0);
			double vAmplitude = v * aAmplitudeDirection * aAmplitude;
			double hAmplitude = 0;
	        this->aInDirection[0] = v;
			this->aInDirection[1] = h;
			this->aIn[0] = vAmplitude;
			this->aIn[1] = hAmplitude;
		    this->aOutDirection[0] = v;
			this->aOutDirection[1] = h;
			// todo:
			this->aOut[0] = vAmplitude * this->amplitudeFade;
			this->aOut[1] = hAmplitude * this->amplitudeFade;
		} else {
			Direction outV = this->diffraction.inDirect ^ this->diffraction.outDirect;
			outV = outV.getUnitDirection();
            double vAmplitude = outV * aAmplitudeDirection * aAmplitude;
			if (vAmplitude < 0) {
			    outV = -outV;
				vAmplitude = -vAmplitude;
			}
			Direction outH0 = this->diffraction.inDirect ^ outV;
			outH0 = outH0.getUnitDirection();
            Direction outH1 = this->diffraction.outDirect ^ outV;
			outH1 = outH1.getUnitDirection();
			double hAmplitude = outH0 * aAmplitudeDirection * aAmplitude;
			if (hAmplitude < 0) {
			    outH1 = -outH1;
				hAmplitude = -hAmplitude;
			}
	        this->aInDirection[0] = outV;
			this->aInDirection[1] = outH0;
			this->aIn[0] = vAmplitude;
			this->aIn[1] = hAmplitude;
		    this->aOutDirection[0] = outV;
			this->aOutDirection[1] = outH1;
			// todo:
			this->aOut[0] = vAmplitude * this->amplitudeFade;
			this->aOut[1] = hAmplitude * this->amplitudeFade;
		}
	    Direction mergeAmplitude = this->aOutDirection[0] * this->aOut[0] + this->aOutDirection[1] * this->aOut[1];
    	double vAmplitudeReceive = (mergeAmplitude) * rAntenna.getVDirection();
	    double hAmplitudeReceive = (mergeAmplitude) * rAntenna.getHDirection();
    	this->setAReceive(vAmplitudeReceive, hAmplitudeReceive);

}
void MixPath::init() {
	this->calculateTotalLength();
	this->calculateDoppler();
	this->calculateDelay();
	this->calculateAmplitudeFade();
}
bool MixPath::calculateAmplitude() {
	vector<Reflection> reflections = this->reflectPath->reflections;
	int size = reflections.size();
	if (this->segments[0].pReflect == NULL) {
	    reflections[0].vAmplitude = reflections[0].vAmplitude * this->segments[0].pDiffract->amplitudeFade;
		reflections[0].hAmplitude = reflections[0].hAmplitude * this->segments[0].pDiffract->amplitudeFade;
	}
	for (unsigned j = 1; j < size; j++) {
	    Reflection r1 = reflections[j - 1];
		Reflection r2 = reflections[j];
		
		if (this->segments[j].pReflect == NULL) {
		    r2.hAmplitude *= this->segments[j].pDiffract->amplitudeFade;
            r2.vAmplitude *= this->segments[j].pDiffract->amplitudeFade;
		}

		reflections[j].setHAmplitude(r2.hAmplitude);
		reflections[j].setVAmplitude(r2.vAmplitude);
	}
	Reflection lastR  = reflections[size - 1];
	this->setAmplitude(lastR.vAmplitude, lastR.hAmplitude);
	this->setPolarization(lastR.v, lastR.h);
	return true;
}
bool MixPath::calculateAmplitudeReceive(const vector<Antenna>& ras) {
    Antenna a = ras[0];
	double vAmplitude = this->amplitude[0];
	double hAmplitude = this->amplitude[1];
	Direction v = this->polarization[0];
	Direction h = this->polarization[1];
	double vAmplitudeReceive = (h * hAmplitude + v * vAmplitude) * a.getVDirection() * this->amplitudeFade;
	double hAmplitudeReceive = (h * hAmplitude + v * vAmplitude) * a.getHDirection() * this->amplitudeFade;
	this->setAmplitudeReceive(vAmplitudeReceive, hAmplitudeReceive);
	return true;
}
bool MixPath::calculateAmplitudeFade() {
    this->amplitudeFade = 1 / ((4 * PI * this->totalLength) / this->waveLength);
	return true;
}
bool MixPath::calculateTotalLength() {
    vector<MixPathSegment>::iterator iterSegment = this->segments.begin();
	double totalLength = 0;
	for (; iterSegment < this->segments.end(); iterSegment++) {
		totalLength += iterSegment->length;
	}
	this->totalLength = totalLength;
    return true;
}
bool MixPath::calculateDelay() {
	// 有待确认，百度百科电磁波的多普勒是这么计算的，但论文和书中都是用的第二种，暂用书中的方法

	// 第一种
	// 第二种
	this->waveLength = WAVE_LENGTH;
	this->delayTime = this->totalLength / (C + this->vDoppler);
    return true;
}
bool MixPath::calculateDoppler() {
	// 有待确认，百度百科电磁波的多普勒是这么计算的，但论文和书中都是用的第二种，暂用书中的方法
	this->fDopplerShift = (double)this->vDoppler / C * F;
    this->frequency = F + (double)this->vDoppler / C * F;
    return true;
}
void MixPath::calculateIr() {
	this->ir[0] = cos(this->phase[0]) * this->amplitudeReceive[0];
	this->ir[1] = cos(this->phase[1]) * this->amplitudeReceive[1];
}