/// imshow
//#include <opencv2/highgui.hpp>
//
//int main(void)
//{
//	cv::Mat image(300, 400, CV_8UC1, cv::Scalar(200));
//	cv::imshow("영상보기", image);
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
	//Point2f pt9 = pt6 * 3.14f;	// 스칼라곱. 각각의 원소에 곱해짐.
	//Point2d pt10 = (pt3 + (Point2d)pt6) * 10;

	//cout << "pt8 = " << pt8.x << ", " << pt8.y << endl;
	//cout << "[pt9] = " << pt9 << endl;
	//cout << (pt2 == pt6) << endl;
	//cout << "pt7과 pt8의 내적: " << pt7.dot(pt8) << endl;


	/// Point 3차원
	//Point3_ <int> pt1(100, 200, 300);
	//Point3_ <float> pt2(92.3f, 125.23f, 250.f);
	//Point3f pt3(0.3f, 0.f, 15.7f);
	//Point3d pt4(0.25, 0.6, 33.3);

	//Point3i pt5 = pt1 + (Point3i)pt2;
	//Point3f pt6 = pt2 * 3.14f;
	//Point3d pt7 = ((Point3d)pt3 + pt4) * 10.f;

	//cout << "두 벡터(pt4, pt7)의 내적 " << pt4.dot(pt7) << endl;
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
	//Size2d sz9 = sz5 + (Size2f)pt1;	// Point를 Size2f로 강제 형변환 가능. 이런 식의 캐스팅이 굉장히 빈번.

	//cout << "sz1.width = " << sz1.width;
	//cout << ", sz1.height = " << sz1.height << endl;
	//cout << "sz1 넓이 " << sz1.area() << endl;
	//cout << "[sz7] = " << sz7 << endl;
	//cout << "[sz8] = " << sz8 << endl;
	//cout << "[sz9] = " << sz9 << endl;


	/// Rect
	Size2d sz(100.5, 60.6);
	Point2f pt1(20.f, 30.f), pt2(100.f, 200.f);

	Rect_<int> rect1(10, 10, 30, 50);	// x, y, width, height
	Rect_<float> rect2(pt1, pt2);		// Point가 들어가면 (left top, right bottom). (Point, Size)일 경우 x, y, width, height
	Rect_<double> rect3(Point2d(20.5, 10), sz);	// x, y, width, height

	Rect rect4 = rect1 + (Point)pt1;
	Rect2f rect5 = rect2 + (Size2f)sz;	// tl = (20, 30), br = (100, 200)인 rect (width = 80, height = 170)에 Size = (100.5, 60.6)를 더해 width = (180.5, 230.6) 이 된다.
	Rect2d rect6 = rect1 & (Rect)rect2;			// and연산(&) -> rect1과 rect2 겹치는 영역
												// or연산(|) -> rect1, rect2 모두 포함하는 새 rect 그림

	cout << "rect3 = " << rect3.x << ", " << rect3.y << ", ";		// 20.5, 10, 
	cout << rect3.width << "x" << rect3.height << endl;				// 100.5x60.6
	cout << "rect4 = " << rect4.tl() << " " << rect4.br() << endl;	// [30, 40] [60, 90]	// tl: left top,	br: right bottom   (10, 10), (40, 60) + (20, 30) = (30, 40), (60, 90)
	cout << "rect5 크기 = " << rect5.size() << endl;				// 180.5 x 230.6
	cout << "[rect6] = " << rect6 << endl;							// 20 x 30 from (20, 30)


	/// vector
	/// Saturation Arithmatic (포화 산술 연산): maximum을 넘어서면 maximum 값을. minimum 이하면 mimimum 값을.
	/// 영상 알고리즘 때문에 너무 높은 값 혹은 너무 적은 값을 갖지 못하도록.
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
	//cout << "[v3 * v7] = " << v3.mul(v7) << endl;	// [150, 220]	// 원소끼리 곱셈
	//cout << "v8[0] = " << v8[0] << endl;			// 800
	//cout << "v8[1] = " << v8[1] << endl;			// 4605
	//cout << "v8[2] = " << v8[2] << endl;			// 10512
	//cout << "v8[3] = " << v8[3] << endl;			// 0		// 안 넣어준 값은 자동으로 0
	//cout << "[v2] = " << v2 << endl;				// [40, 130.7, 125.6]
	//cout << "[pt2] = " << pt2 << endl;				// [40, 131, 126]


	/// Scalar (Vect<_Tp, 4>에서 파생된 클래스)
	/* Blue, Green, Red, Alpha 값을 저장하기 위한 용도
		typedef Scalar_ <double> Scalar;
		값을 모두 지정하지 않으면 0으로 초기화
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



	/// Matx<_Tp, int, int> 고정행렬 클래스. 작은 행렬들만.
	//Matx<int, 3, 3> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
	//Matx<float, 2, 3> m2(1, 2, 3, 4, 5, 6);
	//Matx<double, 3, 5> m3(3, 4, 5, 7);

	//Matx23d m4(3, 4, 5, 6, 7, 8);		 // 2행 3열
	//Matx34d m5(1,2,3,10,11,12,13,14,15); // 3행 4열 (빈칸은 0으로 초기화)
	//Matx66f m6(1,2,3,4,5,6,7,8,9,10);	 // 6행 6열

	//cout << "m5(0, 0) = " << m5(0, 0) << " m5(1, 0) = " << m5(1, 0) << endl;	// 1, 11
	//cout << "m6(0, 1) = " << m6(0, 1) << " m6(1, 3) = " << m6(1, 3) << endl;	// 2, 10

	//cout << "[m1] = " << endl << m1 << endl;
	//cout << "[m2] = " << endl << m2 << endl;
	//cout << "[m3] = " << endl << m3 << endl;
	//cout << "[m4] = " << endl << m4 << endl;
	//cout << "[m5] = " << endl << m5 << endl;
	//cout << "[m6] = " << endl << m6 << endl << endl;


	/// Mat
	/* Mat - 기초적인 이미지 저장소 (행렬식으로써의 사용도 가능)
		하나의 객체, 클래스로서 자체적으로 메모리관리 가능.
		헤더와 데이터 포인터로 구성되어 있다.
		헤더: 자기 자신에 저장되어 있는 이미지에 대한 정보를 담는 곳.
		데이터 포인터: 이미지 하나하나의 픽셀이 담겨있는 메모리 주소에 대한 정보를 가지고 있는 곳.
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
	cout << "[m2] = " << endl << m2 << endl;	// 300으로 채웠지만 CV_8U라 overflow. 따라서 최대값인 255로 넣음.
	cout << "[m3] = " << endl << m3 << endl;
	cout << "[m4] = " << endl << m4 << endl << endl;
	cout << "[m5] = " << endl << m5 << endl;
	cout << "[m6] = " << endl << m6 << endl << endl;


	/// Mat CV_8UC1
	//Mat m1 = Mat::ones(3, 5, CV_8UC1);	// 1로 초기화
	//Mat m2 = Mat::zeros(3, 5, CV_8UC1);
	//Mat m3 = Mat::eye(3, 3, CV_8UC1);	// 단위행렬

	//cout << "[m1] = " << endl << m1 << endl;
	//cout << "[m2] = " << endl << m2 << endl;
	//cout << "[m3] = " << endl << m3 << endl;


	/// Mat_ point
	//double a = 32.12345678, b = 2.7;
	//short c = 400;
	//float d = 10.f, e = 11.f, f = 13.f;

	//Mat_<int> m1(2, 4);
	//Mat_<uchar> m2(3, 4, 100);	// 100으로 초기화
	//Mat_<short> m3(4, 5, c);

	//m1 << 1, 2, 3, 4, 5, 6;
	//Mat m4 = (Mat_<double>(2, 3) << 1, 2, 3, 4, 5, 6);	// m4가 힙에 할당된 데이터 가리킴. m4의 Mat 소멸자가 자동으로 힙 영역 데이터도 소멸시킴.
	//Mat m5 = (Mat_<float>(2, 3) << a, b, c, d, e, f);

	//cout << "[m1] = " << endl << m1 << endl;	// 빈 칸은 쓰레기값으로 채워짐
	//cout << "[m2] = " << endl << m2 << endl << endl;
	//cout << "[m3] = " << endl << m3 << endl << endl;
	//cout << "[m4] = " << endl << m4 << endl;
	//cout << "[m5] = " << endl << m5 << endl;


	/// Mat CV_32FC3
	Mat m1(4, 3, CV_32FC3);

	cout << "차원 수 = " << m1.dims << endl;				// 2	// 2차원 배열.
	cout << "행 개수 = " << m1.rows << endl;				// 4
	cout << "열 개수 = " << m1.cols << endl;				// 3
	cout << "행렬 크기 = " << m1.size() << endl << endl;	// [3 x 4]	// width x height
	
	cout << "전체 원소 개수 = " << m1.total	() << endl;		// 12	// 3 x 4
	cout << "한 원소의 크기 = " << m1.elemSize() << endl;	// 12	// 4byte씩 3개의 행렬(채널)이 존재하니까 12
	cout << "채널당 한 원소의 크기 = " << m1.elemSize1() << endl << endl;	// 4

	cout << "타입 = " << m1.type() << endl;		// 21	// 16 + 5 
	cout << "((m1.channels() -1) << 3) = " << ((m1.channels() - 1) << 3) << endl;	// 16	// 2를 3bit 왼쪽 연산하면 16이 됨.
	cout << "타입 (채널 수 (3bit) | 깊이 (3bit)) = " << ((m1.channels() - 1) << 3) + m1.depth() << endl;	// 21
	cout << "깊이 = " << m1.depth() << endl;	// 5	// #define CV_32F 5
//#define CV_8U 0
//#define CV_8S 1
//#define CV_16U 2
//#define CV_16S 3
//#define CV_32S 4
//#define CV_32F 5
//#define CV_64F 6
//#define CV_USRTYPE1 7
	cout << "채널 = " << m1.channels() << endl << endl;	// 3
	
	cout << "step = " << m1.step << endl;				// 36
	cout << "step1() = " << m1.step1() << endl;	// 한 행에 데이터가 9개. 한 채널, 한 행에 3개씩. 총 3개의 채널이니까 9개




	return 0;
}