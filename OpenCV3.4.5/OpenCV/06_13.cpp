#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/// Roberts mask
//void differential(Mat image, Mat& dst, float data1[], float data2[])
//{
//	Mat dst1, dst2;
//	Mat mask1(3, 3, CV_32F, data1);
//	Mat mask2(3, 3, CV_32F, data2);
//
//	//filter(image, dst1, mask1);
//	//filter(image, dst2, mask2);
//	filter2D(image, dst1, CV_32F, mask1);
//	filter2D(image, dst2, CV_32F, mask2);
//
//	magnitude(dst1, dst2, dst);
//
//	dst1 = abs(dst1);
//	dst2 = abs(dst2);
//	dst.convertTo(dst, CV_8U);
//	dst1.convertTo(dst1, CV_8U);
//	dst2.convertTo(dst2, CV_8U);
//
//	imshow("dst1", dst1);
//	imshow("dst2", dst2);
//		
//}

/// Prewitt mask
/// Sobel mask
void differential(Mat image, Mat& dst, float data1[], float data2[])
{
	Mat dst1, dst2;
	Mat mask1(3, 3, CV_32F, data1);
	Mat mask2(3, 3, CV_32F, data2);

	//filter(image, dst1, mask1);
	//filter(image, dst2, mask2);
	filter2D(image, dst1, CV_32F, mask1);
	filter2D(image, dst2, CV_32F, mask2);

	magnitude(dst1, dst2, dst);
/*
	dst1 = abs(dst1);
	dst2 = abs(dst2);*/
	dst.convertTo(dst, CV_8U);

	// src를 target으로 변환하는데, abs() 적용 + 수식 alpha*dst1 + beta(alpha, beta를 인수로 넣음, alpha = 1, beta = 0이 디폴트) + CV_8U로 설정
	convertScaleAbs(dst1, dst1);	// abs() 후 convertTo()를 한 번에 해줌.
	convertScaleAbs(dst2, dst2);

	//dst1.convertTo(dst1, CV_8U);
	//dst2.convertTo(dst2, CV_8U);

	imshow("dst1-수직마스크", dst1);
	imshow("dst2-수평마스크", dst2);
		
}


int main()
{
	///// Roberts mask
	//Mat image = imread("image/edge_test.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//float data1[] = {	// 행 검출 위주. (열 검출도 가능)
	//	-1, 0, 0,
	//	0, 1, 0,
	//	0, 0, 0
	//};
	//
	//float data2[] = {	// 열 검출 위주. (행 검출도 가능)
	//	0, 0, -1,
	//	0, 1, 0,
	//	0, 0, 0
	//};

	//Mat dst;
	//differential(image, dst, data1, data2);

	//imshow("image", image);
	//imshow("Robets", dst);
	//	
	//waitKey();

	/// Prewitt
	//Mat image = imread("image/edge_test.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//float data1[] = {	// 세로 엣지 검출. (가로 엣지 거의 검출 x)
	//	-1, 0, 1,
	//	-1, 1, 1,
	//	-1, 0, 1
	//};

	//float data2[] = {	// 가로 엣지 검출
	//	-1,-1,-1,
	//	0, 0, 0,
	//	1,1,1
	//};

	//Mat dst;
	//differential(image, dst, data1, data2); 

	//imshow("image", image);
	//imshow("Prewitt", dst);
	//waitKey();


	/// Sobel mask
	//Mat image = imread("image/edge_test.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//float data1[] = {	// 세로 엣지 검출. (가로 엣지 거의 검출 x)
	//	-1, -2, -1,
	//	0,0,0,
	//	1,2,1
	//};

	//float data2[] = {	// 가로 엣지 검출
	//	1,0,-1,
	//	2,0,-2,
	//	1,0,-1
	//};

	//Mat dst, dst3, dst4, dst5;
	//differential(image, dst, data1, data2); 

	//// OpenCV 제공 Sobel
	//Sobel(image, dst3, CV_32F, 1, 0, 3);	// dx, dy, size // depth CV_32F를 dx = 1로 설정(dx 텀을 화소 하나 당. x 기준으로 바로 옆 화소와 비교.), dy=0
	//Sobel(image, dst4, CV_32F, 0, 1, 3);
	//magnitude(dst3, dst4, dst5);
	//dst5.convertTo(dst5, CV_8U);
	//convertScaleAbs(dst3, dst3);
	//convertScaleAbs(dst4, dst4);

	//imshow("image", image);
	//imshow("Sobel", dst);

	//imshow("dst3-OpenCV제공 수직마스크", dst3);
	//imshow("dst4-OpenCV제공 수평마스크", dst4);
	//imshow("dst5-OpenCV제공 Sobel", dst5);
	//waitKey();


	/*
		4. 모폴로지 (Morphology)
			형태학 (Shape)

			1) 침식연산 (Erosion operation)	// openCV에서 제공하는 잡음 제거 효과가 아님. 잡음 제거 효과가 있다는 것 뿐.
				객체의 크기는 축소, 배경은 확대
				영상 내 작은 크기의 잡음 제거 효과
				객체의 돌출부 감소로 서로 닿는 물체의 분리효과

				입력영상
					0 1 1 1 0
					0 1 1 1 0
					1 1 1 0 1
					0 1 1 1 1
					0 0 1 1 1

				3*3 침식 마스크
					0 1 0
					1 1 1
					0 1 0

				1개 이상 불일치 => 0
				모두 일치 => 1


			2) 팽창 연산 (Dilation operation)
				객체의 크기는 팽창, 배경은 축소
				객체 내부에 빈 공간이 채워짐

				3*3 팽창 마스크
					0 1 0
					1 1 1 
					0 1 0

				모두 불일치 => 0
				1개 이상 일치 => 1

			3) 열림 연산, 닫힘 연산
				열림 연산 (Opening operation)
					침식 연산 => 팽창 연산
					침식 연산으로 객체는 축소, 배경 부분의 미세한 잡음 제거
					팽창 연산으로 원래 크기 복귀

				닫힘 연산 (Closing operation)
					팽창 연산 => 침식 연산
					팽창 연산으로 객체 확장, 객체 내부 빈 공간 채움
					침식 연산으로 원래 크기 복귀
	*/
	/// Morphology - erosion
	//Mat image = imread("image/erosion.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//Mat th_img, dst;
	//threshold(image, th_img, 128, 255, THRESH_BINARY);

	//uchar data[] = {
	//	0, 1, 0,
	//	1, 1, 1,
	//	0, 1, 0
	//};

	//Mat mask(3, 3, CV_8UC1, data);
	//morphologyEx(th_img, dst, MORPH_ERODE, mask);

	//imshow("image", image);
	//imshow("이진 영상", th_img);
	//imshow("Erosion", dst);
	//waitKey();	
	
	/// dilation
//	Mat image = imread("image/dilation.jpg", IMREAD_GRAYSCALE);
//	CV_Assert(image.data);
//
//	Mat th_img, dst;
//	threshold(image, th_img, 128, 255, THRESH_BINARY);
//
//	Matx <uchar, 3, 3> mask;
//	mask << 0, 1, 0,
//		1, 1, 1,
//		0, 1, 0;
///*
//	uchar data[] = {
//		0, 1, 0,
//		1, 1, 1,
//		0, 1, 0
//	};
//
//	Mat mask(3, 3, CV_8UC1, data);*/
//	morphologyEx(th_img, dst, MORPH_DILATE, mask);
//
//	imshow("image", image);
//	//imshow("이진 영상", th_img);
//	imshow("Dilation", dst);
//	waitKey();

	/// 열림 연산, 닫힘 연산
	Mat image = imread("image/morphology.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	Mat th_img, dst1, dst2;
	threshold(image, th_img, 128, 255, THRESH_BINARY);

	Matx <uchar, 3, 3> mask;
	mask << 0, 1, 0,
		1, 1, 1,
		0, 1, 0;
	/*
		uchar data[] = {
			0, 1, 0,
			1, 1, 1,
			0, 1, 0
		};

		Mat mask(3, 3, CV_8UC1, data);*/
	morphologyEx(th_img, dst1, MORPH_OPEN, mask);
	morphologyEx(th_img, dst2, MORPH_CLOSE, mask);

	imshow("image", image);
	//imshow("이진 영상", th_img);
	imshow("Opening", dst1);
	imshow("Closing", dst2);
	waitKey();

	return 0;
}