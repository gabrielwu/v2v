#include "auto_model.h"

double plusOrMinus() {
	double y;
    srand((int)time(0));
	if (random(1) < 0.5) {
	    y = -1;
	} else {
	    y = 1;
	}
	return y;
}
Vehicle randomVehicle(double distance, double width, const Direction& d, double vRange) {
    srand((int)time(0));
	double x = random((int)width) - (width / 2);
	double y = 0 + distance;
	double z = ANTENNA_HEIGHT;
	Point p(x, y, z);
	double v = random((int)vRange);
	Vehicle vehicle(p, d, v);
	return vehicle;
}
vector<Material> materialList() {
    // 玻璃
	Material m1(1.5, "glass");
	// 钢
	Material m2(2.5, "steel");
	// 铝
	Material m3(1.4, "aluminum");
	// 水泥
	Material m4(1.6, "concrete");

	vector<Material> materials;
	materials.push_back(m1);
	materials.push_back(m2);
	materials.push_back(m3);
	materials.push_back(m4);
	return materials;
}
Surface randomSurface(const Point& p0, 
					  double width, 
					  vector<Material> materials) {
	double x1 = p0.x;
	double y1 = p0.y + width;
	double z1 = 0;
	Point p1(x1, y1, z1);
	time_t t;
	srand((int)time(&t));
	int mSize = materials.size();
	
	int mIndex = (int)random(mSize);
	Material m = materials[mIndex];

	Surface s(p0, p1, m);
	s.init();
	return s;
}
double randomNum(double range[2]) {
	double min = range[0];
    double max = range[1];
	if (range[0] > range[1]) {
	    max = range[0];
		min = range[1];
	}
	int rangeInt = (int)(max - min);
	double num = min + rand()%rangeInt;
	return num;
}
// 随机模型1
Model randomModel(double length, 
				  double width, 
				  double margin, 
				  double sMaxH,
				  double sMinH,
				  double sMaxW, 
				  double sMinW, 
				  double surfaceInterval, 
				  double vRange, 
				  int dFlag) {
	Direction* tdp;
	Direction* rdp;
    switch(dFlag) {
	case 1:
		tdp = new Direction(0, 1, 0);
		rdp = new Direction(0, 1, 0);
		break;
	case 2:
		tdp = new Direction(0, -1, 0);
		rdp = new Direction(0, -1, 0);
		break;
	case 3:
		tdp = new Direction(0, 1, 0);
		rdp = new Direction(0, -1, 0);
		break;
	case 4:
		tdp = new Direction(0, -1, 0);
		rdp = new Direction(0, 1, 0);
		break;
	default:
		double ty = plusOrMinus();
		double ry = plusOrMinus();
		Direction td(0, ty, 0);
		Direction rd(0, ry, 0);
		break;
	}

	Vehicle tx = randomVehicle(0, width, *tdp, vRange);
	Vehicle rx = randomVehicle(length, width, *rdp, vRange);

	vector<Material> materials = materialList();
	vector<Surface> surfaces;
	double totalLength = 0;
	srand((int)time(0));
	while (totalLength <= length) {
	    double x0 = (width / 2) + random((int)margin);
	    double y0 = totalLength;
	    double z0 = sMinH + random(int(sMaxH - sMinH));
	    Point p0(x0, y0, z0);

	    double sWidth = sMinW + random((int)(sMaxW - sMinW));
		double x1 = x0;
		double y1 = y0 + sWidth;
		double z1 = 0;
		Point p1(x1, y1, z1);

	    Surface s(p0, p1);
	    surfaces.push_back(s);

		totalLength = y0 + sWidth + random((int)surfaceInterval);
	}
	totalLength = 0;
	while (totalLength <= length) {
	    double x0 = -((width / 2) + random((int)margin));
	    double y0 = totalLength;
	    double z0 = sMinH + random(int(sMaxH - sMinH));
	    Point p0(x0, y0, z0);

	    double sWidth = sMinW + random((int)(sMaxW - sMinW));
		double x1 = x0;
		double y1 = y0 + sWidth;
		double z1 = 0;
		Point p1(x1, y1, z1);

	    Surface s(p0, p1);
	    surfaces.push_back(s);

		totalLength = y0 + sWidth + random((int)surfaceInterval);
	}

	int sizeM = materials.size();
	for (int i = 0; i < (int)surfaces.size(); i++) {
	    int indexM = random(sizeM);
		surfaces[i].setMaterial(materials[indexM]);
		surfaces[i].init();
	}

	Direction tad(0,0,1);
	Direction tarp(0,0,0);
	Direction taPolar(sqrt(double(2))/2, 0, sqrt(double(2))/2);
	Antenna ta(tad, tarp, taPolar, 10);
	vector<Antenna> tas;
	tas.push_back(ta);

	Direction rad(0,0,1);
	Direction rarp(0,0,0);
	Direction raVPolar(1, 0, 0);
	Direction raHPolar(0, 0, 1);
	Antenna ra(rad, rarp, raVPolar, raHPolar);
	vector<Antenna> ras;
	ras.push_back(ra);

	Model model(tx, rx, surfaces, tas, ras);
	return model;
}
				  /*
Model RandomModel::produce(double length[2], 
						   double width[2], 
						   double margin[2], 
						   double bH[2],
						   double bW[2], 
						   double bInterval[2], 
						   double vRange[2], 
						   int dFlag) {
    srand((int)time(0));
	this->roadProduce(length, width, margin);
	this->vehicleProduce(vRange, dFlag);
	
}*/
void RandomModel::roadProduce(double length[2], double width[2], double margin[2]) {
    this->length = this->randomNum(length);
    this->width = this->randomNum(width);
	this->margin = this->randomNum(margin);
}
void RandomModel::vehicleProduce(double vRange[2], int dFlag) {
    this->vehicleDirect(dFlag);
	this->vehicleVelocity(vRange);
    double halfWidth = this->width;
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
		tdp = new Direction(0, 1, 0);
		rdp = new Direction(0, 1, 0);
		break;
	case 2:
		tdp = new Direction(0, -1, 0);
		rdp = new Direction(0, -1, 0);
		break;
	case 3:
		tdp = new Direction(0, 1, 0);
		rdp = new Direction(0, -1, 0);
		break;
	case 4:
		tdp = new Direction(0, -1, 0);
		rdp = new Direction(0, 1, 0);
		break;
	default:
		double ty = plusOrMinus();
		double ry = plusOrMinus();
		tdp = new Direction(0, ty, 0);
		rdp = new Direction(0, ry, 0);
		break;
	}
	this->dTx = *tdp;
	this->dRx = *rdp;
}
double RandomModel::randomNum(double range[2]) {
	double min = range[0];
    double max = range[1];
	if (range[0] > range[1]) {
	    max = range[0];
		min = range[1];
	}
	int rangeInt = (int)(max - min);
	double num = min + rand()%rangeInt;
	return num;
}
void RandomModel::vehicleVelocity(double vRange[2]) {
    this->vTx = this->randomNum(vRange);
	this->vRx = this->randomNum(vRange);
}
// 随机模型2
/*
Model randomModel(double length[2], 
				  double width[2], 
				  double margin[2], 
				  double bH[2],
				  double bW[2], 
				  double bInterval[2], 
				  double vRange[2], 
				  int dFlag) {
    srand((int)time(0));
    Model model();
	return model;
}
*/