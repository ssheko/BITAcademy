#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/// ������ ó�� (geometry)
/*
	������ ������ ó���� ũ�� 3����.

	1. Mapping
		ȭ�ҵ��� ���ġ
		�Է�ȭ�� -> Mapping -> ��ġ ���ġ

		1) ������ ���� (forward mapping)
			���� ������ ��ǥ�� �߽����� ���������� ��ǥ�� ���
			���� ����� ��ǥ������ ũ�Ⱑ �ٸ��� hole �Ǵ� overlap �߻�
			hole: �ַ� ������ Ȯ���� �� �߻�
			overlap: �ַ� ������ ����� �� �߻�

		2) ������ ���� (reverse mapping)
			���� ������ ��ǥ�� �߽����� ����ȯ ����� ����, �Է¿��� ��ǥ���� ȭ�Ұ��� ������
			���� ������ �� ���� ȭ�Ұ� ��ǥ������ �������� ȭ�ҷ� ���� ���ε� �� ���� (���� ǰ�� ����)

	2. ũ�⺯��
		- ������ �̿��� ���
			x2 = x * ratioX
			y2 = y * ratioY
		- �Է¿���� ��ǥ������ ũ������ ������ �̿��ϴ� ���
			ratioX = dst-width / src-width
			ratioY = dst-height / src-height

		- �ֱ��� ������(nearest neighbor interpolation)
			hole�� �߻��ϸ� ���� ����� ȭ���� ���� ������
			����ȭ���� ��ǥ�� �ݿø��ϴ� ������ �˰������� ����
			Ȯ������� Ŀ���� ���� ��輱�̳� �𼭸��� ��������� ��Ÿ�� �� ����

			������ ������ ���� ����
			x = x2 / ratioX
			y = y2 / ratioY

	3. ���� �̵�
		- ȭ���� �»���� ����
		- ������ ����
			x2 = x + dx
			y2 = y + dy

		- ������ ����
			x = x2 - dx
			y = y2 - dy

			***
			*/


/// ������ ������ �̿��� ����ũ�� Ȯ�� ���� (hole �Ǵ� overlap �߻�)
void scaling(Mat img, Mat& dst, Size size)
{
	dst = Mat(size, img.type(), Scalar(0));
	double ratioY = (double)size.height / img.rows;
	double ratioX = (double)size.width / img.cols;

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			int x = (int)(j * ratioX);
			int y = (int)(i * ratioY);
			dst.at<uchar>(y, x) = img.at<uchar>(i, j);
		}
	}
}

/// �ֱ��� ������
void scaling_nearest(Mat img, Mat& dst, Size size)
{
	dst = Mat(size, CV_8U, Scalar(0));
	double ratioY = (double)size.height / img.rows;
	double ratioX = (double)size.width / img.cols;

	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			int x = (int)cvRound(j / ratioX);
			int y = (int)cvRound(i / ratioY);
			dst.at<uchar>(i, j) = img.at<uchar>(y, x);
		}
	}
}

/// ���� �̵�
void translation(Mat img, Mat& dst, Point pt)
{
	Rect rect(Point(0, 0), img.size());
	dst = Mat(img.size(), img.type(), Scalar(0));

	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			Point dst_pt(j, i);
			Point img_pt = dst_pt - pt;
			if (rect.contains(img_pt))
				dst.at<uchar>(dst_pt) = img.at<uchar>(img_pt);

		}
	}
}
int main()
{
	/// ������ ������ �̿��� ����ũ�� Ȯ�� ���� (hole �Ǵ� overlap �߻�)
	//Mat image = imread("image/scaling_test.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//Mat dst1, dst2;
	//scaling(image, dst1, Size(150, 150));
	//scaling(image, dst2, Size(400, 400));

	//imshow("image", image);
	//imshow("dst1-���", dst1);
	//imshow("dst2-Ȯ��", dst2);
	//resizeWindow("dst1-���", 200, 150);
	//waitKey();

	/// �ֱ��� ������
	//Mat image = imread("image/scaling_test.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//Mat dst1, dst2;
	//scaling(image, dst1, Size(550,550));
	//scaling_nearest(image, dst2, Size(550,550));

	//imshow("image", image);
	//imshow("dst1-���������", dst1);
	//imshow("dst2-�ֱ���������", dst2);
	//waitKey();


	/// �缱�� ������ (�ֱ��� ���������� ȭ�� ����)
	//Mat image = imread("image/scaling_test.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//Mat dst1, dst2;
	//resize(image, dst1, Size(550,550), 0, 0, INTER_LINEAR);
	//resize(image, dst2, Size(550,550), 0, 0, INTER_NEAREST);

	//imshow("image", image);
	//imshow("dst1-�缱��", dst1);
	//imshow("dst2-�ֱ���", dst2);
	//waitKey();

	/// ���� �̵�
	Mat image = imread("image/add1.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	Mat dst1, dst2;
	translation(image, dst1, Point(30, 80));
	translation(image, dst2, Point(-80, -50));

	imshow("image", image);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	waitKey();

	return 0;
}