/// imshow
//#include <opencv2/highgui.hpp>
//
//int main(void)
//{
//	cv::Mat image(300, 400, CV_8UC1, cv::Scalar(200));
//	cv::imshow("���󺸱�", image);
//	cv::waitKey(0);
//
//	return 0;
//}
//

/// Point
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(void)
{
	//Point_ <int> pt1(100, 200);
	//Point_ <float> pt2(92.3f, 125.23f);
	//Point_ <double> pt3(100.2, 300.9);

	//Point2i pt4(120, 69);
	//Point2f pt5(0.3f, 0.f), pt6(0.f, 0.4f);
	//Point2d pt7(0.25, 0.6);

	//Point pt8 = pt1 + (Point)pt2;
	//Point2f pt9 = pt6 * 3.14f;	// ��Į���. ������ ���ҿ� ������.
	//Point2d pt10 = (pt3 + (Point2d)pt6) * 10;

	//cout << "pt8 = " << pt8.x << ", " << pt8.y << endl;
	//cout << "[pt9] = " << pt9 << endl;
	//cout << (pt2 == pt6) << endl;
	//cout << "pt7�� pt8�� ����: " << pt7.dot(pt8) << endl;


	/// Point 3����
	//Point3_ <int> pt1(100, 200, 300);
	//Point3_ <float> pt2(92.3f, 125.23f, 250.f);
	//Point3f pt3(0.3f, 0.f, 15.7f);
	//Point3d pt4(0.25, 0.6, 33.3);

	//Point3i pt5 = pt1 + (Point3i)pt2;
	//Point3f pt6 = pt2 * 3.14f;
	//Point3d pt7 = ((Point3d)pt3 + pt4) * 10.f;

	//cout << "�� ����(pt4, pt7)�� ���� " << pt4.dot(pt7) << endl;
	//cout << "pt5 = " << pt5.x << ", " << pt5.y << ", " << pt5.z << endl;
	//cout << "[pt6] = " << pt6 << endl;
	//cout << "[pt7] = " << pt7 << endl;

	/// Size
	//Size_ <int> sz1(100, 200);
	//Size_ <float> sz2(192.3f, 25.3f);
	//Size_ <double> sz3(100.2, 30.9);

	//Size sz4(120, 69);
	//Size2f sz5(0.3f, 0.f);
	//Size2d sz6(0.25, 0.6);

	//Point2d pt1(0.25, 0.6);
	//Size2i sz7 = sz1 + (Size2i)sz2;
	//Size2d sz8 = sz3 - (Size2d)sz4;
	//Size2d sz9 = sz5 + (Size2f)pt1;	// Point�� Size2f�� ���� ����ȯ ����. �̷� ���� ĳ������ ������ ���.

	//cout << "sz1.width = " << sz1.width;
	//cout << ", sz1.height = " << sz1.height << endl;
	//cout << "sz1 ���� " << sz1.area() << endl;
	//cout << "[sz7] = " << sz7 << endl;
	//cout << "[sz8] = " << sz8 << endl;
	//cout << "[sz9] = " << sz9 << endl;


	/// Rect
	Size2d sz(100.5, 60.6);
	Point2f pt1(20.f, 30.f), pt2(100.f, 200.f);

	Rect_<int> rect1(10, 10, 30, 50);	// x, y, width, height
	Rect_<float> rect2(pt1, pt2);		// Point�� ���� (left top, right bottom). (Point, Size)�� ��� x, y, width, height
	Rect_<double> rect3(Point2d(20.5, 10), sz);	// x, y, width, height

	Rect rect4 = rect1 + (Point)pt1;
	Rect2f rect5 = rect2 + (Size2f)sz;	// tl = (20, 30), br = (100, 200)�� rect (width = 80, height = 170)�� Size = (100.5, 60.6)�� ���� width = (180.5, 230.6) �� �ȴ�.
	Rect2d rect6 = rect1 & (Rect)rect2;			// and����(&) -> rect1�� rect2 ��ġ�� ����
												// or����(|) -> rect1, rect2 ��� �����ϴ� �� rect �׸�

	cout << "rect3 = " << rect3.x << ", " << rect3.y << ", ";		// 20.5, 10, 
	cout << rect3.width << "x" << rect3.height << endl;				// 100.5x60.6
	cout << "rect4 = " << rect4.tl() << " " << rect4.br() << endl;	// [30, 40] [60, 90]	// tl: left top,	br: right bottom   (10, 10), (40, 60) + (20, 30) = (30, 40), (60, 90)
	cout << "rect5 ũ�� = " << rect5.size() << endl;				// 180.5 x 230.6
	cout << "[rect6] = " << rect6 << endl;							// 20 x 30 from (20, 30)


	/// vector
	/// Saturation Arithmatic (��ȭ ��� ����): maximum�� �Ѿ�� maximum ����. minimum ���ϸ� mimimum ����.
	/// ���� �˰��� ������ �ʹ� ���� �� Ȥ�� �ʹ� ���� ���� ���� ���ϵ���.
	//Vec<int, 2> v1(5, 12);
	//Vec<double, 3> v2(40, 130.7, 125.6);
	//Vec2b v3(10, 10);
	//Vec6f v4(40.f, 230.25f, 525.6f);
	//Vec3i v5(200, 230, 240);

	//Vec3d v6 = v2 + (Vec3d)v5;
	//Vec2b v7 = (Vec2b)v1 + v3;
	//Vec6f v8 = v4 * 20.0f;

	//Point pt1 = v1 + (Vec2i)v7;
	//Point3_<int> pt2 = (Vec3i)v2;

	//cout << "[v3] = " << v3 << endl;				// [10, 10]
	//cout << "[v7] = " << v7 << endl;				// [15, 22]
	//cout << "[v3 * v7] = " << v3.mul(v7) << endl;	// [150, 220]	// ���ҳ��� ����
	//cout << "v8[0] = " << v8[0] << endl;			// 800
	//cout << "v8[1] = " << v8[1] << endl;			// 4605
	//cout << "v8[2] = " << v8[2] << endl;			// 10512
	//cout << "v8[3] = " << v8[3] << endl;			// 0		// �� �־��� ���� �ڵ����� 0
	//cout << "[v2] = " << v2 << endl;				// [40, 130.7, 125.6]
	//cout << "[pt2] = " << pt2 << endl;				// [40, 131, 126]


	/// Scalar (Vect<_Tp, 4>���� �Ļ��� Ŭ����)
	/* Blue, Green, Red, Alpha ���� �����ϱ� ���� �뵵
		typedef Scalar_ <double> Scalar;
		���� ��� �������� ������ 0���� �ʱ�ȭ
	*/

	//Scalar_<uchar> red(0, 0, 255);
	//Scalar_<int> blue(255, 0, 0);
	//Scalar_<double> color1(500);		// (500, 0, 0)
	//Scalar_<float> color2(100.f, 200.f, 125.9f);

	//Vec3d green(0, 0, 300.5);
	//Scalar green1 = color1 + (Scalar)green;
	//Scalar green2 = color2 + (Scalar_<float>)green;

	//cout << "blue = " << blue[0] << ", " << blue[1];		// 255, 0, 0
	//cout << ", " << blue[2] << endl;
	//cout << "red = " << red << endl;						// [0, 0, 255, 0]
	//cout << "green = " << green << endl << endl;			// [0, 0, 300.5]
	//cout << "(Scalar)green = " << (Scalar)green << endl;	// [0, 0, 300.5, 0]
	//cout << "green1 = " << green1 << endl;					// [500, 0, 300.5, 0]
	//cout << "green2 = " << green2 << endl;					// [100, 200, 426.4, 0]



	/// Matx<_Tp, int, int> ������� Ŭ����. ���� ��ĵ鸸.
	//Matx<int, 3, 3> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
	//Matx<float, 2, 3> m2(1, 2, 3, 4, 5, 6);
	//Matx<double, 3, 5> m3(3, 4, 5, 7);

	//Matx23d m4(3, 4, 5, 6, 7, 8);		 // 2�� 3��
	//Matx34d m5(1,2,3,10,11,12,13,14,15); // 3�� 4�� (��ĭ�� 0���� �ʱ�ȭ)
	//Matx66f m6(1,2,3,4,5,6,7,8,9,10);	 // 6�� 6��

	//cout << "m5(0, 0) = " << m5(0, 0) << " m5(1, 0) = " << m5(1, 0) << endl;	// 1, 11
	//cout << "m6(0, 1) = " << m6(0, 1) << " m6(1, 3) = " << m6(1, 3) << endl;	// 2, 10

	//cout << "[m1] = " << endl << m1 << endl;
	//cout << "[m2] = " << endl << m2 << endl;
	//cout << "[m3] = " << endl << m3 << endl;
	//cout << "[m4] = " << endl << m4 << endl;
	//cout << "[m5] = " << endl << m5 << endl;
	//cout << "[m6] = " << endl << m6 << endl << endl;


	/// Mat
	/* Mat - �������� �̹��� ����� (��Ľ����ν��� ��뵵 ����)
		�ϳ��� ��ü, Ŭ�����μ� ��ü������ �޸𸮰��� ����.
		����� ������ �����ͷ� �����Ǿ� �ִ�.
		���: �ڱ� �ڽſ� ����Ǿ� �ִ� �̹����� ���� ������ ��� ��.
		������ ������: �̹��� �ϳ��ϳ��� �ȼ��� ����ִ� �޸� �ּҿ� ���� ������ ������ �ִ� ��.
	*/
	float data[] = { 1.2f, 2.3f, 3.2f, 4.5f, 5.f, 6.5f };

	Mat m1(2, 3, CV_8U);	
	Mat m2(2, 3, CV_8U, Scalar(300));
	Mat m3(2, 3, CV_16S, Scalar(300));
	Mat m4(2, 3, CV_32F, Scalar(300));

	Size sz(2, 3);
	Mat m5(Size(2, 3), CV_64F);
	Mat m6(sz, CV_32F, data);

	cout << "[m1] = " << endl << m1 << endl;
	cout << "[m2] = " << endl << m2 << endl;	// 300���� ä������ CV_8U�� overflow. ���� �ִ밪�� 255�� ����.
	cout << "[m3] = " << endl << m3 << endl;
	cout << "[m4] = " << endl << m4 << endl << endl;
	cout << "[m5] = " << endl << m5 << endl;
	cout << "[m6] = " << endl << m6 << endl << endl;


	/// Mat CV_8UC1
	//Mat m1 = Mat::ones(3, 5, CV_8UC1);	// 1�� �ʱ�ȭ
	//Mat m2 = Mat::zeros(3, 5, CV_8UC1);
	//Mat m3 = Mat::eye(3, 3, CV_8UC1);	// �������

	//cout << "[m1] = " << endl << m1 << endl;
	//cout << "[m2] = " << endl << m2 << endl;
	//cout << "[m3] = " << endl << m3 << endl;


	/// Mat_ point
	//double a = 32.12345678, b = 2.7;
	//short c = 400;
	//float d = 10.f, e = 11.f, f = 13.f;

	//Mat_<int> m1(2, 4);
	//Mat_<uchar> m2(3, 4, 100);	// 100���� �ʱ�ȭ
	//Mat_<short> m3(4, 5, c);

	//m1 << 1, 2, 3, 4, 5, 6;
	//Mat m4 = (Mat_<double>(2, 3) << 1, 2, 3, 4, 5, 6);	// m4�� ���� �Ҵ�� ������ ����Ŵ. m4�� Mat �Ҹ��ڰ� �ڵ����� �� ���� �����͵� �Ҹ��Ŵ.
	//Mat m5 = (Mat_<float>(2, 3) << a, b, c, d, e, f);

	//cout << "[m1] = " << endl << m1 << endl;	// �� ĭ�� �����Ⱚ���� ä����
	//cout << "[m2] = " << endl << m2 << endl << endl;
	//cout << "[m3] = " << endl << m3 << endl << endl;
	//cout << "[m4] = " << endl << m4 << endl;
	//cout << "[m5] = " << endl << m5 << endl;


	/// Mat CV_32FC3
	Mat m1(4, 3, CV_32FC3);

	cout << "���� �� = " << m1.dims << endl;				// 2	// 2���� �迭.
	cout << "�� ���� = " << m1.rows << endl;				// 4
	cout << "�� ���� = " << m1.cols << endl;				// 3
	cout << "��� ũ�� = " << m1.size() << endl << endl;	// [3 x 4]	// width x height
	
	cout << "��ü ���� ���� = " << m1.total	() << endl;		// 12	// 3 x 4
	cout << "�� ������ ũ�� = " << m1.elemSize() << endl;	// 12	// 4byte�� 3���� ���(ä��)�� �����ϴϱ� 12
	cout << "ä�δ� �� ������ ũ�� = " << m1.elemSize1() << endl << endl;	// 4

	cout << "Ÿ�� = " << m1.type() << endl;		// 21	// 16 + 5 
	cout << "((m1.channels() -1) << 3) = " << ((m1.channels() - 1) << 3) << endl;	// 16	// 2�� 3bit ���� �����ϸ� 16�� ��.
	cout << "Ÿ�� (ä�� �� (3bit) | ���� (3bit)) = " << ((m1.channels() - 1) << 3) + m1.depth() << endl;	// 21
	cout << "���� = " << m1.depth() << endl;	// 5	// #define CV_32F 5
//#define CV_8U 0
//#define CV_8S 1
//#define CV_16U 2
//#define CV_16S 3
//#define CV_32S 4
//#define CV_32F 5
//#define CV_64F 6
//#define CV_USRTYPE1 7
	cout << "ä�� = " << m1.channels() << endl << endl;	// 3
	
	cout << "step = " << m1.step << endl;				// 36
	cout << "step1() = " << m1.step1() << endl;	// �� �࿡ �����Ͱ� 9��. �� ä��, �� �࿡ 3����. �� 3���� ä���̴ϱ� 9��




	return 0;
}