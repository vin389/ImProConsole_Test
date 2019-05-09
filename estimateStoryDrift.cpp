#include <iostream>
#include <fstream>
#include <vector>

#include <opencv2/opencv.hpp>

using namespace std; 

/*
*/

int test_estimateStoryDrift() {







	return 0;
}

int estimateStoryDrift(
	cv::Mat cmat,			        // camera matrix 
	cv::Mat dvec,			        // distortion vector
	cv::Mat rvec,			        // rotational vector (3, 1, CV_64F)
	cv::Mat tvec,			        // translational vector (3, 1, CV_64F)
	cv::InputArray refPointsImage,  // reference points in image coord. Can be vector<cv::Point2f> or cv::Mat(N,1,CV_32FC2)
	cv::InputArray trkPointsImage,  // tracking points in image coord. Can be vector<cv::Point2f> or cv::Mat(N,1,CV_32FC2)
	cv::InputArray refPointsWorld,  // reference points in world coord. Can be vector<cv::Point3d> or cv::Mat(N,1,CV_64FC3)
	cv::InputArray trkPointsWorld,  // tracking points in world coord. Can be vector<cv::Point3d> or cv::Mat(N,1,CV_64FC3)
	cv::InputArray newRefPtsImage,  // moved reference points in image coord. vector<cv::Point2f> or cv::Mat(N,1,CV_32FC2)
	cv::InputArray newTrkPtsImage,  // moved tracking points in image coord. vector<cv::Point2f> or cv::Mat(N,1,CV_32FC2)
	cv::Point3d    tortionCenter,   // tortional center point in world coord. 
	cv::Mat & newRvec,              // moved rotational vector (3, 1, CV_64F)
	cv::Mat & newDisp,              // displacement of story (ux, uy, tortion) (3, 1, CV_64F) 
	cv::OutputArray refProjError,   // reference points projection error in image coord. Can be vector<cv::Point2f> or cv::Mat(N,1,CV_32FC2)
	cv::OutputArray trkProjError    // tracking points projection error in image coord. Can be vector<cv::Point2f> or cv::Mat(N,1,CV_32FC2)
)
{
	// check arguments types and sizes
	if (cmat.rows != 3 || cmat.cols != 3) {
		cerr << "Eroror: estimateStoryDrift(): cmat should be 3 by 3.\n";
		return -1;
	}
	if (!(dvec.rows >= 4 && dvec.cols == 1) && !(dvec.rows == 1 && dvec.cols >= 4)) {
		cerr << "Eroror: estimateStoryDrift(): dvec should be (>=4) by 1 or 1 by (>=4).\n";
		return -1;
	}
	if (rvec.rows == 3 && rvec.cols == 3)
	{
		cv::Mat rvec3(3, 1, rvec.type()); 
		cv::Rodrigues(rvec, rvec3); 
		rvec = rvec3.clone(); 
	}
	if (rvec.rows * rvec.cols != 3) 
	{
		cerr << "Eroror: estimateStoryDrift(): rvec should be 3x1 or 1x3 or 3x3.\n";
		return -1;
	}
	if (tvec.rows * tvec.cols != 3) {
		cerr << "Eroror: estimateStoryDrift(): tvec should be 3x1 or 1x3.\n";
		return -1;
	}

	// find theoretical projection points
	cv::Mat projRefPointsImage = refPointsImage.getMat().clone(); 
	cv::Mat projTrkPointsImage = trkPointsImage.getMat().clone();
	cv::projectPoints(refPointsWorld, rvec, tvec, cmat, dvec, projRefPointsImage); 

	cout << "Projection points: \n" << projRefPointsImage << endl;





	return 0;
}
