// v2vMatlab.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "v2vMatlab.h"
#include "mex.h"

#ifndef MODEL_H 
#define MODEL_H 
#include "model.h"
#endif 
#ifndef HELPER_H 
#define HELPER_H 
#include "helper.h"
#endif 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CV2vMatlabApp

BEGIN_MESSAGE_MAP(CV2vMatlabApp, CWinApp)
	//{{AFX_MSG_MAP(CV2vMatlabApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CV2vMatlabApp construction

CV2vMatlabApp::CV2vMatlabApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CV2vMatlabApp object

CV2vMatlabApp theApp;


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
	double* paramTx = (double*)mxGetPr(prhs[0]);
	double* paramRx = (double*)mxGetPr(prhs[1]);
	double* paramSs = (double*)mxGetPr(prhs[2]);

	// 汽车参数
	Point txp(paramTx[0], paramTx[3], paramTx[6]);
	Point rxp(paramRx[0], paramRx[3], paramRx[6]);
	Direction rxd(paramRx[1], paramRx[4], paramRx[7]); 
	Direction txd(paramTx[1], paramTx[4], paramTx[7]); 
	double txv = paramTx[2];
	double rxv = paramRx[2];
	Vehicle tx(txp, txd, txv);
	Vehicle rx(rxp, rxd, rxv);

	// 建筑物表面参数
	Point p0(paramSs[0], paramSs[3], paramSs[6]);
	Point p1(paramSs[1], paramSs[4], paramSs[7]);
	double mn = paramSs[2];
	Material m(mn);
	Surface s(p0, p1, m);
	s.init();
	vector<Surface> surfaces;
	surfaces.push_back(s);

	// 天线参数，待定，未从外界输入
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
	model.calculateStrongestPaths();

	Path path = model.getStrongestPaths()[1];
	Surface sss = model.surfaces[0];
	
	unsigned size = model.getStrongestPaths().size();
	double delayTime0 = path.getDelayTime();
	double totalLength0 = path.getTotalLength();
	double waveLength0 = path.getWaveLength();
	plhs[0] = mxCreateDoubleMatrix(30, 1, mxREAL);
	
	double* outParam = (double*)mxGetPr(plhs[0]);
	outParam[0] = size;
	outParam[1] = totalLength0;
	outParam[2] = waveLength0;
	outParam[3] = sss.getA();
	outParam[4] = sss.getB();
	outParam[5] = sss.getC();
	outParam[6] = sss.getD();



	//outParam[0] = model.transmitter.p.x;
	//outParam[1] =  model.transmitter.p.y;

	mexPrintf("Tx:\n"); 
	mexPrintf(" location:%f,%f,%f\n", paramTx[0],paramTx[3],paramTx[6]);
	mexPrintf(" direction:%f,%f,%f\n", paramTx[1],paramTx[4],paramTx[7]);
	mexPrintf(" velocity:%f\n", paramTx[2]);
	mexPrintf("%f\n", paramRx[0]);
	//mexPrintf("%f\n", paramSurfaces[0]);
}
