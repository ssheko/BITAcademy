#include <opencv2/highgui.hpp>

int main(void)
{
	cv::Mat image(300, 400, CV_8UC1, cv::Scalar(200));
	cv::imshow("���󺸱�", image);
	cv::waitKey(0);

	return 0;
}