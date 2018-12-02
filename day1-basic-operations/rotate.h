#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(void)
{
Mat source, M, result;

// Reading the image
source = cv::imread("sample.jpg",1);

Point2f center(source.cols/2, source.rows/2);
double rotationAngle=30;
double scale=1;

// Getting the matrix which will define the rotation
M = cv::getRotationMatrix2D(center, 
	rotationAngle, scale);

// Rotating the source and storing in result
cv::warpAffine(source, result, M, 
	Size(source.cols, source.rows));

// Create windows for display
namedWindow("Original Image", WINDOW_AUTOSIZE);
namedWindow("Rotated Image", WINDOW_AUTOSIZE);

// Display images
imshow("Original Image", source);
imshow("Rotated Image", result);

waitKey(0);

}
