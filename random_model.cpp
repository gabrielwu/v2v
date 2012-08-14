#include "random_model.h"

double RandomModel::randomNum(double range[2]) {
	double min = range[0];
    double max = range[1];
	if (range[0] > range[1]) {
	    max = range[0];
		min = range[1];
	}
	int rangeInt = (int)(max - min);
	double num;
	if (rangeInt == 0) {
	    num = min;
	} else {
	    num = min + rand()%rangeInt;
	}
	return num;
}
double RandomModel::plusOrMinus() {
	double y;
	if (rand()%1 < 0.5) {
	    y = -1;
	} else {
	    y = 1;
	}
	return y;
}
Model RandomModel::createModel() {
    switch (this->scenarioType) {
	    case 1: // 城市峡谷
			return this->urbanCanyonModel();
			break;
		case 2: // 郊外道路
			return this->suburbanStreetModel();
			break;
		case 3: // 高速公路
			return this->expresswayModel();
			break;
		default: // 默认城市峡谷
			return this->urbanCanyonModel();
			break;
	}
}
Model RandomModel::produce(double length[2], 
						   double width[2], 
						   double margin[2], 
						   double bH[2],
						   double bL[2], 
						   double bInterval[2], 
						   double vRange[2], 
						   int dFlag) {
    srand((int)time(0));
	this->roadProduce(length, width, margin);
	this->vehicleProduce(vRange, dFlag);
	this->materialsProduce();
	this->surfacesAndEdges(margin, bH, bL, bInterval);
	this->antennasProduce();
	this->treesProduce();
	this->WeatherProduce();
	Model model(this->tx, this->rx, this->surfaces, this->edges, this->tAntennas, this->rAntennas);
	model.setTrees(this->trees);
	model.setWeather(this->storm, this->rain);
	return model;
}
Model RandomModel::urbanCanyonModel() {
    srand((int)time(0));
	this->roadProduce(lengthRange, widthRange, marginRange);
	this->vehicleProduce(vRange, dFlag);
	this->materialsProduce();
	this->surfacesAndEdges(marginRange, bHRange, bLRange, bIntervalRange);
	this->antennasProduce();
	this->treesProduce();
	this->WeatherProduce();
	Model model(this->tx, this->rx, this->surfaces, this->edges, this->tAntennas, this->rAntennas);
	model.setTrees(this->trees);
	model.setWeather(this->storm, this->rain);
	return model;
}
Model RandomModel::suburbanStreetModel() {
    srand((int)time(0));
	this->roadProduce(lengthRange, widthRange, marginRange);
	this->vehicleProduce(vRange, dFlag);
	this->materialsProduce();
	this->surfacesAndEdges(marginRange, bHRange, bLRange, bIntervalRange);
	this->antennasProduce();
	this->treesProduce();
	this->WeatherProduce();
	Model model(this->tx, this->rx, this->surfaces, this->edges, this->tAntennas, this->rAntennas);
	model.setTrees(this->trees);
	model.setWeather(this->storm, this->rain);
	return model;
}
Model RandomModel::expresswayModel() {
    srand((int)time(0));
	this->roadProduce(lengthRange, widthRange, marginRange);
	this->vehicleProduce(vRange, dFlag);
	this->antennasProduce();
	this->treesProduce();
	this->WeatherProduce();
	Model model(this->tx, this->rx, this->surfaces, this->edges, this->tAntennas, this->rAntennas);
	model.setTrees(this->trees);
	model.setWeather(this->storm, this->rain);
	return model;
}
void RandomModel::roadProduce(double length[2], double width[2], double margin[2]) {
    this->length = this->randomNum(length);
    this->width = this->randomNum(width);
	this->margin = this->randomNum(margin);
}
void RandomModel::vehicleProduce(double vRange[2], int dFlag) {
    this->vehicleDirect(dFlag);
	this->vehicleVelocity(vRange);
    double halfWidth = this->width / 2;
	double widthRange[2] = {-halfWidth, halfWidth};
	
	double xt = this->randomNum(widthRange);
	double yt = 0;
	double zt = ANTENNA_HEIGHT;
	Point pt(xt, yt, zt);
    Vehicle* txp = new Vehicle(pt, this->dTx, this->vTx);

	double xr = this->randomNum(widthRange);
	double yr = 0 + this->length;
	double zr = ANTENNA_HEIGHT;
	Point pr(xr, yr, zr);
    Vehicle* rxp = new Vehicle(pr, this->dRx, this->vRx);

	this->tx = *txp;
	this->rx = *rxp;
}
void RandomModel::vehicleDirect(int dFlag) {
    Direction* tdp;
	Direction* rdp;
    switch(dFlag) {
	case 1:
		this->dFlagInfo = "同向，正(same,plus)";
		tdp = new Direction(0, 1, 0);
		rdp = new Direction(0, 1, 0);
		break;
	case 2:
		this->dFlagInfo = "同向，负(same,minus)";
		tdp = new Direction(0, -1, 0);
		rdp = new Direction(0, -1, 0);
		break;
	case 3:
		this->dFlagInfo = "相向，发射车正(opposite,Tx plus)";
		tdp = new Direction(0, 1, 0);
		rdp = new Direction(0, -1, 0);
		break;
	case 4:
		this->dFlagInfo = "相向，接收车正(opposite,Rx plus)";
		tdp = new Direction(0, -1, 0);
		rdp = new Direction(0, 1, 0);
		break;
	default:
		this->dFlagInfo = "随机";
		double ty = this->plusOrMinus();
		double ry = this->plusOrMinus();
		tdp = new Direction(0, ty, 0);
		rdp = new Direction(0, ry, 0);
		break;
	}
	this->dTx = *tdp;
	this->dRx = *rdp;
}

void RandomModel::vehicleVelocity(double vRange[2]) {
    this->vTx = this->randomNum(vRange);
	this->vRx = this->randomNum(vRange);
}
void RandomModel::treesProduce() {
	/*
	double y = this->length / 10;
	double ty = y;
	double ry = 9 * y; 
	Point tp0(- this->width / 2, ty, TREE_HEIGHT);
	Point tp1(this->width / 2, ty, TREE_HEIGHT);
	Point tp2(- this->width / 2, ry, TREE_HEIGHT);
	Point tp3(this->width / 2, ry, TREE_HEIGHT);
	Tree t0(tp0);
    Tree t1(tp1);
    Tree t2(tp2);
    Tree t3(tp3);
	*/
	double x = this->width / 2;
	double y = this->length / 10;
	double z = 0;

	
    TreeConfig *tConfig0 = new TreeConfig(3, Point(x, y, z));
    Geometry *crown = NULL;
	///crown  = new Ball(Point(x, y, z+5), 8);
	//crown  = new BallPart(Point(x, y, z+5), 8, Point(x, y, z+3));
	//crown  = new Cylinder(Point(x, y, z+15), Point(x, y, z+5), 7);
	//crown  = new Cone(Point(x, y, z+25), Point(x, y, z+5), 10);
	//crown  = new Ellipse(Point(x, y, z+13), Point(x, y, z+1), 10, 8);
	//crown  = new EllipsePart(Point(x, y, z+13), Point(x, y, z+1), 10, 8, Point(x, y, z+8), true);
	crown  = new Cuboid(Direction(12,0,0), Direction(0,12,0), Direction(0,0,12), Point(x-3, y-4, z+5));
    tConfig0->setCrown(crown);
	/*
	TreeConfig *tConfig1 = new TreeConfig(3, Point(-x, y, z));
    TreeConfig *tConfig2 = new TreeConfig(3, Point(x,this->length - y, z));
    TreeConfig *tConfig3 = new TreeConfig(3, Point(-x, this->length - y, z));
	*/
	Tree t0(tConfig0);
	t0.generate();
	t0.generateLeavesList();
    /*
	Tree t1(tConfig1);	
	t1.generate();
	t1.generateLeavesList();
    Tree t2(tConfig2);
	t2.generate();
	t2.generateLeavesList();
    Tree t3(tConfig3);
	t3.generate();
	t3.generateLeavesList();
	*/
    this->trees.push_back(t0);

	/*
	this->trees.push_back(t1);
	this->trees.push_back(t2);
	this->trees.push_back(t3);
	*/
}
void RandomModel::materialsProduce() {
	Material m1(1.5, "glass"); // 玻璃	
	Material m2(2.5, "steel"); // 钢
	Material m3(1.4, "aluminum"); // 铝
	Material m4(1.6, "concrete"); // 水泥

	this->materials.push_back(m1);
    this->materials.push_back(m2);
	this->materials.push_back(m3);
	this->materials.push_back(m4);
}
Surface RandomModel::surfaceProduce(const Point& p0, double length, vector<Material> materials) {
    double x1 = p0.x;
	double y1 = p0.y + length;
	double z1 = 0;
	Point p1(x1, y1, z1);

	int mSize = materials.size();
	int mIndex = (int)rand()%(mSize);
	Material m = materials[mIndex];
	// 表面高度标准差和最大突起高度，毫米换算为米
	double protuberHStandDeviat = (rand()%(50))/1000.0;
	double maxProtuberH = (rand()%(200))/1000.0;
	Surface s(p0, p1, m, Direction(), maxProtuberH, protuberHStandDeviat);
	s.init();
	return s;
}
void RandomModel::WeatherProduce() {
	this->storm = new Storm(F/(1e9), (1.63e5), 20, 0.01, -9.718, 0.405);
	this->storm->init();
	this->rain = new Rain(F/(1e9), 1);
	this->rain->init();
}
void RandomModel::surfacesAndEdges(double margin[2], 
								   double bH[2],
								   double bL[2], 
								   double bInterval[2]) {
    double totalLength = -bInterval[1];
	// 道路右侧情况，x>0
	while (totalLength <= this->length) {
	    double x0 = (width / 2) + this->randomNum(margin);
	    double y0 = totalLength + this->randomNum(bInterval);
	    double z0 = this->randomNum(bH);
	    Point p0(x0, y0, z0);
        
		// 面
		double length = this->randomNum(bL);
		Surface s = this->surfaceProduce(p0, length, this->materials);
		s.init();
	    this->surfaces.push_back(s);

        // 刃形，p2p0,p1p3
		Point p1 = s.getP1();
		Point p2 = s.getP2();
		Point p3 = s.getP3();
        Point pb0(p0.x + BUILDING_WIDTH, p0.y, p0.z);
		Point pb1(p3.x + BUILDING_WIDTH, p3.y, p3.z);

		Edge e0(p2, p0, pb0, p3);
		Edge e1(p1, p3, pb1, p0);
		this->edges.push_back(e0);
		this->edges.push_back(e1);
		totalLength = y0 + length ;
	}
	// 道路左侧情况，x<0
	totalLength = -bInterval[1];
	while (totalLength <= this->length) {
	    double x0 = -((width / 2) + this->randomNum(margin));
	    double y0 = totalLength + this->randomNum(bInterval);
	    double z0 = this->randomNum(bH);
	    Point p0(x0, y0, z0);
        
		// 面
		double length = this->randomNum(bL);
		Surface s = this->surfaceProduce(p0, length, this->materials);
		s.init();
	    this->surfaces.push_back(s);

        // 刃形，p2p0,p1p3
		Point p1 = s.getP1();
		Point p2 = s.getP2();
		Point p3 = s.getP3();
        Point pb0(p0.x - BUILDING_WIDTH, p0.y, p0.z);
		Point pb1(p3.x - BUILDING_WIDTH, p3.y, p3.z);

		Edge e0(p2, p0, pb0, p3);
		Edge e1(p1, p3, pb1, p0);
		this->edges.push_back(e0);
		this->edges.push_back(e1);
		totalLength = y0 + length;
	}
}
void RandomModel::antennasProduce() {
    Direction tad(0,0,1);
	Direction tarp(0,0,0);
	Direction taPolar(sqrt(double(2))/2, 0, sqrt(double(2))/2);
	Antenna ta(tad, tarp, taPolar, 10);
	this->tAntennas.push_back(ta);

	Direction rad(0,0,1);
	Direction rarp(0,0,0);
	Direction raVPolar(1, 0, 0);
	Direction raHPolar(0, 0, 1);
	Antenna ra(rad, rarp, raVPolar, raHPolar);
	this->rAntennas.push_back(ra);
}