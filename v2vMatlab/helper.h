#ifndef MODEL_H 
#define MODEL_H 
#include "model.h"
#endif 
#ifndef STADFX_H 
#define STADFX_H 
#include "stdafx.h"
#endif
 
// 获取两点间距离
double getDistance(const Point& p0, const Point& p1);

// 获取两点间距离
double getDistanceByDirection(const Direction& d0, const Direction& d1);

// 获取点p关于面s的对称点pn
// @s:待检验反射面
// @pn:待检验点
Point* getSymmetricPoint (const Surface& s, const Point& p); 

// 获取两点pa、pb连线关于平面s的交点p 
// @s:待检验平面
// @pa:起始点（实际应用中应为某点关于s的对称点）
// @pb:终止点
// return:若有交点，返回交点（反射点或入射点）Point对象
Point* getReflectPoint(const Surface& s, const Point& pa, const Point& pb);

// 获得反射对象
// @s:待检验反射面
// @pt:出射点
// @pr:接收点
// return:若反射成立，返回Reflecttion对象；否则返回null
Reflection* getReflection(const Surface& s, const Point& pt, const Point& pr);

// 多段反射中第一段
Reflection* getFirstReflection(const Point& reflectPoint, const Point& pr, const Antenna& a);


// 计算直线与平面的交点
// @dLine:直线向量
// @nPlane:平面法向量
// @pLine:过直线的一个点
// @pPlane:过平面的一个点
Point* calculateIntersectPoint(Direction& dLine, Direction& nPlane, Point& pLine, Point& pPlane);

// 获取单位方向向量
// @d:方向向量
// return:单位方向向量
Direction getUnitDirection(const Direction& d);

// 计算获得两向量夹角
double getAngleByVectors(const Direction& d0, const Direction& d1);
// 计算获取发射角
double calculateReflectAngle(const Direction& d0, const Direction& d1);
// 计算向量点积
Direction getScalarProduct(const Direction& d0, const Direction& d1);


// 计算多普勒影响下的频率
double getDopplerFrequency(double vDoppler, double frequency, double v);

