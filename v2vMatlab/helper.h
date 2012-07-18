#ifndef MODEL_H 
#define MODEL_H 
#include "model.h"
#endif 
#ifndef STADFX_H 
#define STADFX_H 
#include "stdafx.h"
#endif
 
// ��ȡ��������
double getDistance(const Point& p0, const Point& p1);

// ��ȡ��������
double getDistanceByDirection(const Direction& d0, const Direction& d1);

// ��ȡ��p������s�ĶԳƵ�pn
// @s:�����鷴����
// @pn:�������
Point* getSymmetricPoint (const Surface& s, const Point& p); 

// ��ȡ����pa��pb���߹���ƽ��s�Ľ���p 
// @s:������ƽ��
// @pa:��ʼ�㣨ʵ��Ӧ����ӦΪĳ�����s�ĶԳƵ㣩
// @pb:��ֹ��
// return:���н��㣬���ؽ��㣨����������㣩Point����
Point* getReflectPoint(const Surface& s, const Point& pa, const Point& pb);

// ��÷������
// @s:�����鷴����
// @pt:�����
// @pr:���յ�
// return:���������������Reflecttion���󣻷��򷵻�null
Reflection* getReflection(const Surface& s, const Point& pt, const Point& pr);

// ��η����е�һ��
Reflection* getFirstReflection(const Point& reflectPoint, const Point& pr, const Antenna& a);


// ����ֱ����ƽ��Ľ���
// @dLine:ֱ������
// @nPlane:ƽ�淨����
// @pLine:��ֱ�ߵ�һ����
// @pPlane:��ƽ���һ����
Point* calculateIntersectPoint(Direction& dLine, Direction& nPlane, Point& pLine, Point& pPlane);

// ��ȡ��λ��������
// @d:��������
// return:��λ��������
Direction getUnitDirection(const Direction& d);

// �������������н�
double getAngleByVectors(const Direction& d0, const Direction& d1);
// �����ȡ�����
double calculateReflectAngle(const Direction& d0, const Direction& d1);
// �����������
Direction getScalarProduct(const Direction& d0, const Direction& d1);


// ���������Ӱ���µ�Ƶ��
double getDopplerFrequency(double vDoppler, double frequency, double v);

