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

	// src�� target���� ��ȯ�ϴµ�, abs() ���� + ���� alpha*dst1 + beta(alpha, beta�� �μ��� ����, alpha = 1, beta = 0�� ����Ʈ) + CV_8U�� ����
	convertScaleAbs(dst1, dst1);	// abs() �� convertTo()�� �� ���� ����.
	convertScaleAbs(dst2, dst2);

	//dst1.convertTo(dst1, CV_8U);
	//dst2.convertTo(dst2, CV_8U);

	imshow("dst1-��������ũ", dst1);
	imshow("dst2-���򸶽�ũ", dst2);
		
}


int main()
{
	///// Roberts mask
	//Mat image = imread("image/edge_test.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//float data1[] = {	// �� ���� ����. (�� ���⵵ ����)
	//	-1, 0, 0,
	//	0, 1, 0,
	//	0, 0, 0
	//};
	//
	//float data2[] = {	// �� ���� ����. (�� ���⵵ ����)
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

	//float data1[] = {	// ���� ���� ����. (���� ���� ���� ���� x)
	//	-1, 0, 1,
	//	-1, 1, 1,
	//	-1, 0, 1
	//};

	//float data2[] = {	// ���� ���� ����
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

	//float data1[] = {	// ���� ���� ����. (���� ���� ���� ���� x)
	//	-1, -2, -1,
	//	0,0,0,
	//	1,2,1
	//};

	//float data2[] = {	// ���� ���� ����
	//	1,0,-1,
	//	2,0,-2,
	//	1,0,-1
	//};

	//Mat dst, dst3, dst4, dst5;
	//differential(image, dst, data1, data2); 

	//// OpenCV ���� Sobel
	//Sobel(image, dst3, CV_32F, 1, 0, 3);	// dx, dy, size // depth CV_32F�� dx = 1�� ����(dx ���� ȭ�� �ϳ� ��. x �������� �ٷ� �� ȭ�ҿ� ��.), dy=0
	//Sobel(image, dst4, CV_32F, 0, 1, 3);
	//magnitude(dst3, dst4, dst5);
	//dst5.convertTo(dst5, CV_8U);
	//convertScaleAbs(dst3, dst3);
	//convertScaleAbs(dst4, dst4);

	//imshow("image", image);
	//imshow("Sobel", dst);

	//imshow("dst3-OpenCV���� ��������ũ", dst3);
	//imshow("dst4-OpenCV���� ���򸶽�ũ", dst4);
	//imshow("dst5-OpenCV���� Sobel", dst5);
	//waitKey();


	/*
		4. �������� (Morphology)
			������ (Shape)

			1) ħ�Ŀ��� (Erosion operation)	// openCV���� �����ϴ� ���� ���� ȿ���� �ƴ�. ���� ���� ȿ���� �ִٴ� �� ��.
				��ü�� ũ��� ���, ����� Ȯ��
				���� �� ���� ũ���� ���� ���� ȿ��
				��ü�� ����� ���ҷ� ���� ��� ��ü�� �и�ȿ��

				�Է¿���
					0 1 1 1 0
					0 1 1 1 0
					1 1 1 0 1
					0 1 1 1 1
					0 0 1 1 1

				3*3 ħ�� ����ũ
					0 1 0
					1 1 1
					0 1 0

				1�� �̻� ����ġ => 0
				��� ��ġ => 1


			2) ��â ���� (Dilation operation)
				��ü�� ũ��� ��â, ����� ���
				��ü ���ο� �� ������ ä����

				3*3 ��â ����ũ
					0 1 0
					1 1 1 
					0 1 0

				��� ����ġ => 0
				1�� �̻� ��ġ => 1

			3) ���� ����, ���� ����
				���� ���� (Opening operation)
					ħ�� ���� => ��â ����
					ħ�� �������� ��ü�� ���, ��� �κ��� �̼��� ���� ����
					��â �������� ���� ũ�� ����

				���� ���� (Closing operation)
					��â ���� => ħ�� ����
					��â �������� ��ü Ȯ��, ��ü ���� �� ���� ä��
					ħ�� �������� ���� ũ�� ����
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
	//imshow("���� ����", th_img);
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
//	//imshow("���� ����", th_img);
//	imshow("Dilation", dst);
//	waitKey();

	/// ���� ����, ���� ����
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
	//imshow("���� ����", th_img);
	imshow("Opening", dst1);
	imshow("Closing", dst2);
	waitKey();

	return 0;
}