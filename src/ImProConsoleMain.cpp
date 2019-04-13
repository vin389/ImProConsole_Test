#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>

#include "improConsole.h"
#include "CamMoveCorrector.h"

// arguments about general files
//  -iflist=file, path and file name of list of input photos
//  -oflist=file, path and file name of list of output photos
//  -ifvideo=file, path and file name of input video
//  -ofvideo=file, path and file name of output video
//  -ifimgpts=file, path and file name of input image points history data
//  -ofimgpts=file, path and file name of output image points history data
//  -if3dpts=file, path and file name of input 3-dimension points history data
//  -of3dpts=file, path and file name of output 3-dimension points history data
//  -califlist1=file1, path and file name of list of calibration photos of camera 1 (left)
//  -califlist2=file2, path and file name of list of calibration photos of camera 2 (right)
//  -califintr1=file1, path and file name intr/extr parameters of camera 1 
//  -califintr2=file2, path and file name intr/extr parameters of camera 2

// arguments about calibration
//  -calbtype=1, 1:chessboard,2:sym.grid,3:unsym.grid.
//  -calbnx=7, number of corners along board x 
//  -calbny=7, number of corners along board y 
//  -calbsx=57.15 mm, distance between corners along x, unit: user defined (be consistent) 
//  -calbsy=57.15 mm, distance between corners along y, unit: user defined (be consistent) 
//  -calintrlvl=-1, 0:auto, 1:fx(=fy),k1, 2:fx,fy,k1, 3:fx,fy,cx,cy,k1, 4:fx,fy,cx,cy,k1,p1,p2, 5:fx,fy,cx,cy,k1,k2,p1,p2.


int FuncCalibStereoOnSite(int, char**); 
int FuncCalibInLabOnSite(int, char**);
int FuncCalibOnSiteUserPoints(int, char**);
int FuncCalibOnlyExtrinsic(int, char**); 

int FuncVideo2Pics(int argc, char** argv);
int FuncPics2Video(int argc, char** argv);
int FuncVideo2PicsResize(int argc, char** argv);
int FuncPics2VideoResize(int argc, char** argv);

int FuncTemplatesPicking(int argc, char** argv);
int FuncQ4TemplatesPicking(int argc, char** argv);

int FuncCamMoveCorrection(int argc, char** argv);

int FuncTrackingPointsEcc(int argc, char** argv);
int FuncTrackingPyrTmpltMatch(int argc, char** argv);

int FuncSyncTwoCams(int argc, char** argv);

int FuncTriangulationAllSteps(int argc, char** argv);

int FuncDrawHouse(int argc, char ** argv); 

int FuncOptflowSeq(int argc, char ** argv); 

int FuncWallDisp(int argc, char ** argv);    // made for SPD test 2019
int FuncWallDispCam(int argc, char ** argv); // made for SPD test 2019

int FuncTryCamFocusExposure(int argc, char ** argv);

int main(int argc, char ** argv)
{

	Submenu s(argc, argv);
	s.addItem("calsite",    "Calibration: Stereo calibration on site               ", FuncCalibStereoOnSite); 
	s.addItem("callabsite", "Calibration: Intrinsic in Lab. Extrinsic on site      ", FuncCalibInLabOnSite);
	s.addItem("calupoints", "Calibration: Intrinsic/Extrisic on site by user points", FuncCalibOnSiteUserPoints);
	s.addItem("calexonly",  "Calibration: Given intrinsic data and run extrinsic calibration", FuncCalibOnlyExtrinsic); 

	s.addItem("v2p",        "Conversion: Convert video to pictures", FuncVideo2Pics);
	s.addItem("p2v",        "Conversion: Convert pictures to video", FuncPics2Video);
	s.addItem("v2pResize",  "Conversion: Convert video to pictures with resizing", FuncVideo2PicsResize);
	s.addItem("p2vResize",  "Conversion: Convert pictures to video with resizing", FuncPics2VideoResize);

	s.addItem("picktm",     "Picking: Templates Picking",     FuncTemplatesPicking);
	s.addItem("picktmq4",   "picking: Generating quadrilateral mesh of templates by picking four corners.", FuncQ4TemplatesPicking); 

	s.addItem("cammov",     "Cam correction: Camera movement correction (pic 2 pic, ref. points tracked) ", FuncCamMoveCorrection);

	s.addItem("ecc",        "Tracking: Track Points Using ECC method",                FuncTrackingPointsEcc);
	s.addItem("tmatch",     "Tracking: Track by pyramid template match",              FuncTrackingPyrTmpltMatch);

	s.addItem("syncC2",     "Synchronize Camera 2 to match Camera 1",                 FuncSyncTwoCams);

	s.addItem("trianga",    "Triangulation (all steps a file)",                       FuncTriangulationAllSteps);

	s.addItem("drawhouse", "Draw a house allowing tuning intrinsic p.",               FuncDrawHouse); 

	s.addItem("optflow", "Dense (Farneback) optical flow analysis", FuncOptflowSeq); 

	s.addItem("wallDisp", "Plane wall displacement analysis (online)", FuncWallDisp); 
	s.addItem("wallDispCam", "Plane wall displacement analysis (online, webcam)", FuncWallDispCam);

	s.addItem("tryCam", "Try the best camera settings of focus and exposure", FuncTryCamFocusExposure); 
	s.run();

	return 0;
}