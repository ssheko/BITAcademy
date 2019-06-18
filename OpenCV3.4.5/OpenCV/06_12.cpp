#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


/// HSI �÷�����
//void bgr2hsi(Mat img, Mat& hsi)
//{
//	hsi = Mat(img.size(), CV_32FC3);
//	for (int i = 0; i < img.rows; i++)
//	{
//		for (int j = 0; j < img.cols; j++)
//		{
//			float B = img.at<Vec3b>(i, j)[0];
//			float G = img.at<Vec3b>(i, j)[1];
//			float R = img.at<Vec3b>(i, j)[2];
//
//			float s = 1 - 3 * min(R, min(G, B)) / (R + G + B);
//			float v = (R + G + B) / 3.0f;
//
//			float tmp1 = ((R - G) + (R - B)) * 0.5f;
//			float tmp2 = sqrt((R - G) * (R - B) + (G - B) * (G - B));
//			float angle = acos(tmp1 / tmp2) * (180.f / CV_PI);
//			float h = (B <= G) ? angle : 360 - angle;
//
//			hsi.at<Vec3f>(i, j) = Vec3f(h / 2, s * 255, v);
//		}
//	}
//	hsi.convertTo(hsi, CV_8U);
//}


/// ���� ó��
//void filter(Mat img, Mat& dst, Mat mask)
//{
//	dst = Mat(img.size(), CV_32F, Scalar(0));
//	Point h_m = mask.size() / 2;
//	for (int i = h_m.y; i < img.rows - h_m.y; i++)
//	{
//		for (int j = h_m.x; j < img.cols - h_m.x; j++)
//		{
//			float sum = 0;
//			for (int k = 0; k < mask.rows; k++)
//			{
//				for (int t = 0; t < mask.cols; t++)
//				{
//					int y = i + k - h_m.y;
//					int x = j + t - h_m.x;
//					sum += mask.at<float>(k, t) * img.at<uchar>(y, x);
//				}
//			}
//			dst.at<float>(i,j) = sum;	// �յ� ���
//		}
//	}
//}


	/// Edge ���� (���� ������ ���)
void homogenOp(Mat img, Mat& dst, int mask_size)
{
	dst = Mat(img.size(), CV_8U, Scalar(0));
	Point h_m(mask_size / 2, mask_size / 2);

	for (int i = h_m.y; i < img.rows - h_m.y; i++)
	{
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			float max = 0;
			for (int k = 0; k < mask_size; k++)
			{
				for (int t = 0; t < mask_size; t++)
				{
					int y = i + k - h_m.y;
					int x = j + t - h_m.x;

					float difference = abs(img.at<uchar>(i, j) - img.at<uchar>(y, x));
					if (difference > max)
						max = difference;
				}
			}
			dst.at<uchar>(i, j) = max;
		}
	}
}

/// Edge ���� 2 (�� ������ ���)
void differOp(Mat img, Mat& dst, int mask_size)
{
	dst = Mat(img.size(), CV_8U, Scalar(0));
	Point h_m(mask_size / 2, mask_size / 2);
	int mask_length = mask_size * mask_size;
	for (int i = h_m.y; i < img.rows - h_m.y; i++)
	{
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			vector<uchar> mask(mask_length, 0);
			for (int k = 0, s = 0; k < mask_size; k++)
			{
				for (int t = 0; t < mask_size; t++, s++)
				{
					int y = i + k - h_m.y;
					int x = j + t - h_m.x;

					mask[s] = img.at<uchar>(y, x);
				}
			}
			uchar max = 0;
			for (int k = 0; k < mask_length / 2; k++)
			{
				int start = mask[k];
				int end = mask[mask_length - k - 1];

				uchar difference = abs(start - end);
				if (difference > max)
					max = difference;
			}
			dst.at<uchar>(i, j) = max;
		}
	}
}


int main()
{
	/// matrix transform
	//vector<Point> rect_pt1, rect_pt2;
	//rect_pt1.push_back(Point(200, 50));
	//rect_pt1.push_back(Point(400, 50));
	//rect_pt1.push_back(Point(400, 250));
	//rect_pt1.push_back(Point(200, 250));

	//float theta = 20 * CV_PI / 180;
	//Matx22f m(cos(theta), -sin(theta), sin(theta), cos(theta));
	//transform(rect_pt1, rect_pt2, m);	// matrix�� �̿��� transform ������.

	//Mat image(400, 500, CV_8UC3, Scalar(255, 255, 255));

	//for (int i = 0; i < 4; i++)
	//{
	//	line(image, rect_pt1[i], rect_pt1[(i + 1) % 4], Scalar(0, 0, 0), 1);
	//	line(image, rect_pt2[i], rect_pt2[(i + 1) % 4], Scalar(255, 0, 0), 2);
	//	cout << "rect_pt1[" << to_string(i) + "] = " << rect_pt1[i] << "\t";
	//	cout << "rect_pt2[" << to_string(i) + "] = " << rect_pt2[i] << endl;
	//}
	//imshow("image", image);
	//waitKey();

	/// ȭ�� ó��
	//Mat image1(50, 512, CV_8UC1, Scalar(0));
	//Mat image2(50, 512, CV_8UC1, Scalar(0));
	//
	//for (int i = 0; i < image1.rows; i++)
	//{
	//	for (int j = 0; j < image1.cols; j++)
	//	{
	//		image1.at<uchar>(i, j) = j / 2;	// �ε巴�� fade out
	//		image2.at<uchar>(i, j) = (j / 20) * 10;
	//	}
	//}
	//imshow("image1", image1);
	//imshow("image2", image2);
	//waitKey();


	/// Ư�� ���� ȭ�� �� Ȯ��
	//Mat image = imread("image/pixel_test.jpg", IMREAD_GRAYSCALE);
	//if (image.empty())	// CV_Assert ��� ��� ����.
	//{
	//	cout << "���� �б� ����" << endl;
	//	exit(1);
	//}
	//Rect roi(500, 313, 20, 15);
	//Mat roi_img = image(roi);
	//cout << "[roi_img] = " << endl;
	//for (int i = 0; i < roi_img.rows; i++)
	//{
	//	for (int j = 0; j < roi_img.cols; j++)
	//	{
	//		cout.width(5);
	//		cout << (int)roi_img.at<uchar>(i, j);
	//	}
	//	cout << endl;
	//}
	//rectangle(image, roi, Scalar(255), 1);
	//imshow("image", image);
	//waitKey();

	///
	//Mat image = imread("image/bright.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(!image.empty());

	//Mat dst1 = image + 100;
	//Mat dst2 = image - 100;
	//Mat dst3 = 255 - image;	// ����

	//Mat dst4(image.size(), image.type());
	//Mat dst5(image.size(), image.type());
	//for (int i = 0; i < image.rows; i++)
	//{
	//	for (int j = 0; j < image.cols; j++)
	//	{
	//		//dst4.at<uchar>(i, j) = saturate_case<uchar>(image.at<uchar>(i, j) + );
	//		dst4.at<uchar>(i, j) = image.at<uchar>(i, j) + 100;	// overflow, underflow �߻����� ����
	//		dst5.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);
	//	}
	//}
	//imshow("Original", image);
	//imshow("dst1 - ���", dst1);
	//imshow("dst2 - ��Ӱ�", dst2);
	//imshow("dst3 - ����", dst3);
	//imshow("dst4 - ���", dst4);
	//imshow("dst5 - ����", dst5);
	//waitKey();

	/// ���� �ռ�
	/* �ΰ��� ��� �� ����� saturate_cast�� ���� 255�� �Ѿ�� ���� ��� ������� ��Ÿ��
	* �� ������ �ռ��� ����� ������� ����. �̸� �ذ��ϴ� ����� ������ ����
	* 1) dst(y, x) = image(y, x) *0.5 + image2(y, x) *0.5
	* 2) dst(y, x) = image1(y,) * alpha + image2(y, x) * (1-alpha)
	* 3) dst(y, x) = image1(y, x) * alpha + image2(y, x) * beta
	*
	*/
	//Mat image1 = imread("image/add1.jpg", IMREAD_GRAYSCALE);
	//Mat image2 = imread("image/add2.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(!(image1.empty() || image2.empty()));

	//double alpha = 0.6, beta = 0.7;
	//Mat add_img1 = image1 + image2;
	//Mat add_img2 = image1 * 0.5 + image2 * 0.5;
	//Mat add_img3 = image1 * alpha + image2 * (1-alpha);
	//Mat add_img4;
	//addWeighted(image1, alpha, image2, beta, 0, add_img4);

	//imshow("image1", image1);
	//imshow("add_img1", add_img1);
	//imshow("add_img2", add_img2);
	//imshow("add_img3", add_img3);
	//imshow("add_img4", add_img4);
	//waitKey();


	/// ��� ���
	//Mat image = imread("image/contrast_test.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//Scalar avg = mean(image) / 2.0;
	//Mat dst1 = image * 0.5;
	//Mat dst2 = image * 2.0;
	//Mat dst3 = image * 0.5 + avg[0];
	//Mat dst4 = image * 2.0 - avg[0];

	//imshow("image", image);
	//imshow("dst1-��񰨼�", dst1);
	//imshow("dst2-�������", dst2);
	//imshow("dst3-����̿� ��񰨼�", dst3);
	//imshow("dst4-����̿� �������", dst4);

	//waitKey();


	/*
		1. RGB �÷� ����
		- ���� �����
		- ���� ȥ��, �⺻ �÷� ����
		- ����Ϳ��� �÷��� ǥ���ϱ� ���� ���

		2. CMY(K) �÷� ����
		- �μ��⸦ �̿��� ���̿� ����ϱ� ���� �÷� ����
		- ���� ȥ�� (���� �������� ��ο���), ���� �����
		- ���� ������� ��������
			Cyan, Magenta, Yellow

		3. RGB, CMY ��ȣ��ȯ
			C = 255 - R
			M = 255 - G
			Y = 255 - B

			R = 255 - C
			G = 255 - M
			B = 255 - Y

			���� ������� ��� ���ص� ��ũ�� �Ҽ��� ���� �������� ������ �������� ��������� ����
			�̷��� ������ �������� �߰��� CMYK �÷� ������ �Ϲ������� �����.

		4. CMY to CMYK
			black = min(Cyan, magenta, Yellow)
			Cyan = Cyan - black
			Magenta = Magenta - black
			Yellow = Yellow - black

		5. HSI �÷�����
			�ΰ��� �÷������� �����ϴ� ���
			����(Hue), ä��(Saturation), ��(Intensity)

		6. ��Ÿ �÷�����
			YCrCb
			YUV
			YUV420
			BayerRGB
			La*b*
	*/

	//Mat BGR_img = imread("image/color_model.jpg", IMREAD_COLOR);
	//CV_Assert(BGR_img.data);

	//Scalar white(255, 255, 255);
	//Mat CMY_img = white - BGR_img;
	//Mat CMY_arr[3];
	//split(CMY_img, CMY_arr);

	//imshow("BGR_img", BGR_img);
	//imshow("CMY_img", CMY_img);
	//imshow("Yellow", CMY_arr[0]);
	//imshow("Magenta", CMY_arr[1]);
	//imshow("Cyan", CMY_arr[2]);
	//waitKey();
	//

/// CMY
	//Mat BGR_img = imread("image/color_model.jpg", IMREAD_COLOR);
	//CV_Assert(BGR_img.data);

	//Scalar white(255, 255, 255);
	//Mat CMY_img = white - BGR_img;
	//Mat CMY_arr[3];
	//split(CMY_img, CMY_arr);

	//Mat black;
	//min(CMY_arr[0], CMY_arr[1], black);
	//min(black, CMY_arr[2], black);

	//CMY_arr[0] = CMY_arr[0] - black;
	//CMY_arr[1] = CMY_arr[1] - black;
	//CMY_arr[2] = CMY_arr[2] - black;

	//imshow("black", black);
	//imshow("Yellow", CMY_arr[0]);
	//imshow("Magenta", CMY_arr[1]);
	//imshow("Cyan", CMY_arr[2]);
	//waitKey();

	/// HSI �÷�����
	//Mat BGR_img = imread("image/color_space.jpg", IMREAD_COLOR);
	//CV_Assert(BGR_img.data);

	//Mat HSI_img, HSV_img, hsi[3], hsv[3];

	//bgr2hsi(BGR_img, HSI_img);
	//cvtColor(BGR_img, HSV_img, CV_BGR2HSV);
	//split(HSI_img, hsi);
	//split(HSV_img, hsv);

	//imshow("BGR_img", BGR_img);
	//imshow("Hue", hsi[0]);
	//imshow("Saturation", hsi[1]);
	//imshow("Intensity", hsi[2]);
	//imshow("OpenCV_Hue", hsv[0]);
	//imshow("OpenCV_Saturation", hsv[1]);
	//imshow("OpenCV_Intensity", hsv[2]);
	//waitKey();


	/// ���� ó��
	/*
		* ����(domain) ó�� - Convolution

			spatial domain, area based processing
			������ ȭ��ó���� ȭ�Ұ� ������ ���� ���� ����
			area based processing�� mask�� ������� ������ ���� ���� ����

		����ũ ��� ����ó�� (mask matrix �� ������ ���� 1�̾�� ��. ex: 3*3 ũ�� mask�� �� ��� �� = 1/9)
			����ũ ���� ���Ұ��� ���� ������ �ִ� �Է� ������ ȭ�Ұ����� �����ǰ� ���Ͽ� ��� ȭ�Ұ��� ���
			�̷��� ó���� �ϴ� ������ ��� ���ȭ�Ұ��� ���� �̵��ϸ鼭 �����ϴ� ���� Convolution�̶� ��.
			�� �� �Է¿��� �������� �� ����ũ�� Ŀ��(kernel), ������(window), ����(filter) ���� ���ε� ����

		1. ����(blurring)
			������ ��� �����ϸ鼭 �ణ �帮�� ó���ϴ� ���
			���󿡼� ȭ�Ұ��� �ް��ϰ� ���ϴ� �κе��� ���ҽ��� ���������� ���ϰ� ��
			��ü������ �ε巯�� ������ ���� ����

		2. ������(Sharpening)

		3. Edge ����
			����ó������ ������ ����: ȭ�Ұ��� �ް��ϰ� ���ϴ� �κ�
			�������� ���
				���� ����: �̿��ϴ� ȭ���� ������ Ư�� �Ӱ谪 �̻��� ���� ã��
				1�� �Ǵ� 2�� �̺� ����ũ ���

			���� ������ ���
				���� �ܼ��� ���� ���� ���.
				ȭ�Ҹ� ������ ������ �ִ밪�� �����Ͽ� ������ ����
				���������� ���� �� ����ǹǷ� ��� �ð��� ���� �ҿ��.

			�� ������ ���
				���� �������� ��� �ð��� ���� �ɸ��� ������ ������ �ִ� ���
				���� ������ ���� �� �ʿ��� ���� �����ڿʹ� �޸� ȭ�Ҵ� �� ���� ���Ǿ� ���� �ð��� ����.

	*/
	/// blur	
	//Mat image = imread("image/bright.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//float data[] =
	//{
	//	1 / 9.f, 1 / 9.f, 1 / 9.f,
	//	1 / 9.f, 1 / 9.f, 1 / 9.f,
	//	1 / 9.f, 1 / 9.f, 1 / 9.f
	//};

	//Mat mask(3, 3, CV_32F, data);
	//Mat blur;
	//filter(image, blur, mask);
	//blur.convertTo(blur, CV_8U);



	//imshow("image", image);
	//imshow("blur", blur);
	//waitKey();

	/// sharpen
	//Mat image = imread("image/blur.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//float data1[] = {
	//	0, -1, 0,
	//	-1, 5, -1,
	//	0, -1, 0
	//};

	//float data2[] = {
	//	-1, -1, -1,
	//	-1, 9, -1,
	//	-1, -1, -1,
	//};

	//Mat mask1(3, 3, CV_32F, data1);
	//Mat mask2(3, 3, CV_32F, data2);
	//Mat sharpen1, sharpen2;

	//filter(image, sharpen1, mask1);
	//filter(image, sharpen2, mask2);

	//sharpen1.convertTo(sharpen1, CV_8U);
	//sharpen2.convertTo(sharpen2, CV_8U);

	//imshow("image", image);
	//imshow("sharpen1", sharpen1);
	//imshow("sharpen2", sharpen2);
	//waitKey();


	/// Edge ���� (���� ������ ���)
	//Mat image = imread("image/edge_test.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//Mat edge;
	//homogenOp(image, edge, 3);

	//imshow("image", image);
	//imshow("edge", edge);
	//waitKey();

	/// Edge ���� 2 (�� ������ ���)
	//Mat image = imread("image/edge_test.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//Mat edge;
	//differOp(image, edge, 3);

	//imshow("image", image);
	//imshow("edge", edge);
	//waitKey();


	return 0;
}