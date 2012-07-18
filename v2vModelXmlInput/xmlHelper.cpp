#include "xmlHelper.h"
#ifndef MATH_H 
#define MATH_H 
#include "math.h"
#endif 


double parseDouble(string s) {
    double num;
	stringstream ss(s);
	ss>>num;
	return num;
}
Direction parseDirection(string s) {
    stringstream ss(s);
    string subStr;
	double value[3];
    for (int i = 0; getline(ss, subStr, ','); i++) {
		value[i] = parseDouble(subStr);
	}
	Direction d(value[0], value[1], value[2]);
	return d;
}
Point parsePoint(string s) {
    stringstream ss(s);
    string subStr;
	double value[3];
    for (int i = 0; getline(ss, subStr, ','); i++) {
		value[i] = parseDouble(subStr);
	}
	Point p(value[0], value[1], value[2]);
	return p;
}