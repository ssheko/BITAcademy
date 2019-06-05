
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


/// reshape
/* reshape(int cn, int rows) // 채널 개수, row 개수
	변경 전, 후 행렬 전체 원소 수가 맞아야 함

	create(int rows, int cols, int type, int ndims, int* sizes)
	기존에 존재하는 행렬의 차원, 행, 열, 자료형을 변경하여 다시 생성
	기존 행렬과 크기와 자료형이 다르면 기존 메모리를 해제하고 새로운 데이터를 생성
	*/
//void print_matInfo(String m_name, Mat m)
//{
//	cout << "[" << m_name << "행렬]" << endl;
//	cout << " 채널 수 = " << m.channels() << endl;
//	cout << " 행 X 열 = " << m.rows << " X " << m.cols << endl << endl;
//
//}

/// vector 2
void print_vectorInfo(string v_name, vector<int> v)
{
	cout << "[" << v_name << "] = ";
	if (v.empty())
		cout << "벡터가 비어있습니다." << endl;
	else
		cout << ((Mat)v).reshape(1,1) << endl;

	cout << ".size() = " << v.size() << endl;
}

/// ROI: Region of Interest (관심영역)
void print_locateROI(String str, Mat m)
{
	Size size;
	Point pt;	// 시작 위치. (부모 기준)
	m.locateROI(size, pt);

	cout << "부모크기 " << size << ", ";	// m이 속한 부모 크기
	cout << "[" << str << "] = ";
	cout << m.size() << " from " << pt << endl;
}

/// mat type
/// mat release
/* 
	Mat::release() 메소드는 행렬 데이터와 관련된 참조 카운터를 감소시킴.
	참조 카운터가 0에 도달하면 행렬 데이터를 해제하고,
	행렬 데이터와 참조 카운터의 포인터는 모두 NULL로 설정하여 메모리를 해제
	일반적으로 Mat 클래스의 destructor()에 의해 자동으로 호출되기 때문에 
	명시적으로 호출하는 경우는 드물다.
*/

void print_matInfo(String name, Mat m)
{
	String mat_type;
	if (m.depth() == CV_8U)
		mat_type = "CV_8U";
	else if (m.depth() == CV_8S)
		mat_type = "CV_8S";
	else if (m.depth() == CV_16U)
		mat_type = "CV_16U";
	else if (m.depth() == CV_16S)
		mat_type = "CV_16S";
	else if (m.depth() == CV_32S)
		mat_type = "CV_32S";
	else if (m.depth() == CV_32F)
		mat_type = "CV_32F";
	else if (m.depth() == CV_64F)
		mat_type = "CV_64F";

	cout << name << " 크기 " << m.size() << ", ";
	cout << " 자료형 " << mat_type << "C" << m.channels() << endl;
	cout << m << endl << endl;

}

int main(void)
{
	/// Mat
	// 행렬 값 자체는 heap에 존재. Mat 변수(헤더)는 heap에 존재하는 값을 포인트하는 형식. (C++ smart point)
	//Mat m1(2, 3, CV_8U, 2);				// 2*3 배열 2로 전체 초기화
	//Mat m2(2, 3, CV_8U, Scalar(10));	// 2*3 배열 10으로 전체 초기화

	//Mat m3 = m1 + m2;					// 2*3 배열 2+10
	//Mat m4 = m2 - 6;					// 10-6
	//Mat m5 = m1;						// 두 Mat이 동일한 값 reference. m5, m1 헤더는 둘 다 heap에 존재하는 같은 값을 포인트.

	//cout << "[m1] = " << endl << m1 << endl;
	//cout << "[m2] = " << endl << m2 << endl;
	//cout << "[m3] = " << endl << m3 << endl;
	//cout << "[m4] = " << endl << m4 << endl << endl;

	//cout << "[m1] = " << endl << m1 << endl;
	//cout << "[m5] = " << endl << m5 << endl << endl;

	//m5 = 100;
	//cout << "[m1] = " << endl << m1 << endl;
	//cout << "[m5] = " << endl << m5 << endl << endl;
	//

	/// resize
	/* resize(size_t sz, Scalar &s)
		기존 행렬의 행의 수보다 작으면 자르고, 많으면 행 추가
	*/
	//Mat m = (Mat_<uchar>(2, 4) << 1, 2, 3, 4, 5, 6, 7, 8);
	//cout << "[m] = " << endl << m << endl << endl;

	//m.resize(1);
	//cout << "m.resize(1) = " << endl << m << endl;
	//m.resize(3);
	//cout << "m.resize(3) = " << endl << m << endl << endl;
	//m.resize(5, Scalar(50));
	//cout << "m.resize(5) = " << endl << m << endl;


	/// reshape
	//Mat m1(2, 6, CV_8U);
	//Mat m2 = m1.reshape(2);	// row는 항상 기준이니까 row =2를 기준으로 채널을 하나 더 만드니까 2*6 -> 2*3 배열로.
	//Mat m3 = m1.reshape(3, 2);

	//print_matInfo("m1(2, 6)", m1);
	//print_matInfo("m2 = m1.reshape(2)", m2);
	//print_matInfo("m3 = m1.reshape(3,2)", m3);

	//m1.create(3, 5, CV_16S);
	//print_matInfo("m1.create(3, 5, CV_16S)", m1);



	/// Mat clone
	/* Mat clone() 기존 행렬 데이터 값을 복사해서 새로운 행렬 생성
		void CopyTo() 행렬 데이터를 인자로 입력된 mat 행렬에 복사
		void converTo(Mat mat, int type, double alpha, double beta)
		행렬 원소의 데이터 타입을 변경하여 생성한 행렬을 mat에 반환
	*/
	//double data[] = { 1.1, 2.2, 3.3, 4.4,
	//				5.5, 6.6, 7.7, 8.9,	// 부동 소수점 표기법 때문에 8.8000000 으로 출력됨. 
	//				9.9, 10, 11, 12 };
	//Mat m1(3, 4, CV_64F, data);
	//Mat m2 = m1.clone();
	//Mat m3, m4;
	//m1.copyTo(m3);
	//m1.convertTo(m4, CV_8U);

	//cout << "m1 = " << m1 << endl << endl;
	//cout << "m2 = " << m2 << endl << endl;
	//cout << "m3 = " << m3 << endl << endl;
	//cout << "m4 = " << m4 << endl << endl;


	/// MatConstIterator
	//Mat m = Mat::eye(10, 10, CV_32FC1);	// 10*10 짜리 단위 행렬 생성
	//cout << "Element (3, 3) is " << m.at<float>(3, 3) << endl;

	//Mat m2 = Mat::eye(10, 10, CV_32FC2);	// 채널 두개 생성 (첫 번째 채널만 단위행렬. 두 번째 채널은 전부 0으로 채워짐)
	//cout << "Element (3, 3) is (" << m2.at<Vec2f>(3, 3)[0]	// 앞 채널
	//	<< ", " << m2.at<Vec2f>(3, 3)[1] << ")" << endl;	// 뒷 채널

	//Mat m3 = Mat::eye(10, 10, traits::Type<Complex<float>>::value);	// Complex: 복소수. (실수부 + 허수부)
	//cout << "Element (3, 3) is (" << m3.at<Complexf>(3, 3).re		// re: 실수
	//	<< " + " << m3.at<Complexf>(3, 3).im << "i)" << endl;				// im: 허수

	//cout << "=================================================================" << endl;
	//int sz[3] = { 4,4,4 };
	//Mat m4(3, sz, CV_32FC3);	// 크기가 4x4x4인 3차원 배열. 배열 원소 하나에 채널 3개가 존재.
	//randu(m4, -1.0f, 1.0f);		// -1.0 ~ 1.0 사이 난수 채우기
	////cout << "[m4] = " << endl << m4 << endl << endl;	// 3차원부터는 << 연산자 오버로딩 사용할 수 없음.


	//float max = 0.0f;
	//MatConstIterator_<Vec3f> it = m4.begin<Vec3f>();
	//float len2;
	////int count = 0;
	//while (it != m4.end<Vec3f>()) {
	//	cout << (*it)[0] << ", " << (*it)[1] << ", " << (*it)[2] << endl;
	//	len2 = (*it)[0] * (*it)[0] + (*it)[1] * (*it)[1] + (*it)[2] * (*it)[2];
	//	if (len2 > max)
	//		max = len2;
	//	it++;
	//	//count++;
	//}

	////cout << "count = " << count << endl;
	//cout << "max = " << max << endl;


	/// vector
	//vector<Point> v1;
	//v1.push_back(Point(10, 20));
	//v1.push_back(Point(20, 30));
	//v1.push_back(Point(50, 60));

	//vector<float> v2(3, 9.25);
	//Size arr_size[] = { Size(2, 2), Size(3, 3), Size(4, 4) };
	//int arr_int[] = { 10, 20, 30, 40, 50 };

	//vector<Size> v3(arr_size, arr_size + sizeof(arr_size) / sizeof(Size));
	//vector<int> v4(arr_int + 2, arr_int + sizeof(arr_int) / sizeof(int));	// 0번쨰, 1번째를 제외하고 배열 다시 만듬.

	//cout << "[v1] " << (Mat)v1 << endl << endl;
	//cout << "[v2] " << ((Mat)v2).reshape(1,1) << endl;
	//cout << "[v3] " << ((Mat)v3).reshape(1,1) << endl;
	//cout << "[v4] " << ((Mat)v4).reshape(1,1) << endl;	// 1*1 행렬로 만듬
	//cout << "[v4] " << (Mat)v4 << endl << endl;			// 3*1 행렬


	/// vector 2
//// 벡터를 선언하고 중간에 값을 넣게 되면 재할당이 이루어져 메모리 효율성이 떨어진다.
//	int arr[] = { 10, 20, 30, 40, 50 };
//	vector<int> v1(arr, arr + sizeof(arr) / sizeof(int));
//
//	print_vectorInfo("v1", v1);
//
//	v1.insert(v1.begin() + 2, 100);
//	print_vectorInfo("v1, insert(2)", v1);	// size = 6	// 현재 들어가 있는 원소 갯수
//	cout << ".capacity() = " << v1.capacity() << endl << endl;	// capacity = 7	// capacity는 원소 하나당 2개씩 늘어남.	// 배열의 전체 갯수
//
//	v1.erase(v1.begin() + 3);
//	print_vectorInfo("v1, erase(3)", v1);	// size = 5
//	cout << ".capacity() = " << v1.capacity() << endl << endl;	// capacity = 7	// 지워도 capacity는 남아있음.
//	
//
//	v1.clear();
//	print_vectorInfo("v1, clear()", v1);
//	cout << ".capacity() = " << v1.capacity() << endl << endl;	// capacity = 7	

	/// vector reserve
	//vector<double> v1, v2;
	//v1.reserve(10000000);	// 미리 용량을 할당해 놓음.

	//double start_time = clock();
	//for (int i = 0; i < v1.capacity(); i++)
	//{
	//	v1.push_back(i);
	//}
	//printf("reserve() 사용 %5.2f ms\n", (clock() - start_time));

	//start_time = clock();
	//for (int i = 0; i < v1.capacity(); i++)
	//{
	//	v2.push_back(i);
	//}

	//printf("reserve() 미사용 %5.2f ms\n", (clock() - start_time));

	/// range
	/* Range 클래스
		Range(int start, int end)
		start <= 범위 < end
		int size() : sub sequence의 크기 반환
		bool empty(): is sub sequence empty?
		Range all() : 전체 시퀀스나 Range를 반환

		Range 클래스로 범위를 지정하고 Mat 클래스의 () 연산자 함수를 통해서 행렬을 참조하면,
		부모 행렬의 특정 부분을 공유하는 행렬을 생성할 수 있다.
		*/
	//Range r1(0, 3), r2(3, 7);
	//int data[] = {
	//	10, 11, 12, 13, 14, 15, 16,
	//	20, 21, 22, 23, 24, 25, 26,
	//	30, 31, 32, 33, 34, 35, 36,
	//	40, 41, 42, 43, 44, 45, 46
	//};

	//Mat m1, m2;
	//m1 = Mat(4, 7, CV_32S, data);
	//m2 = m1(r1, r2);

	//cout << "[m1의 2번 행] = " << m1.row(2) << endl;
	//cout << "[m1의 1번 행] = " << endl << m1.col(1) << endl;
	//cout << "[m1의 (0~2행 모두)] = " << endl << m1.rowRange(r1) << endl;

	//cout << "[m1] = " << endl << m1 << endl;
	//cout << "[m2 (0~2행 3~6열) 참조] = " << endl << m2 << endl << endl;

	//m2.setTo(50);
	//cout << "[m2] = " << endl << m2 << endl;
	//cout << "[m1] = " << endl << m1 << endl << endl;

	/// ROI
	//Range r1(0, 3), r2(3, 7);
	//int data[] = {
	//	10, 11, 12, 13, 14, 15, 16,
	//	20, 21, 22, 23, 24, 25, 26,
	//	30, 31, 32, 33, 34, 35, 36,
	//	40, 41, 42, 43, 44, 45, 46
	//};

	//Mat m1, m2;
	//m1 = Mat(5, 7, CV_32S, data);	// 5행 7열
	//m2 = m1(r1, r2);
	//Mat m3 = m1(r1, r1);

	//print_locateROI("m2", m2);
	//print_locateROI("m3", m3);

	//m2.adjustROI(-1, 1, 2, -1);	// top, bottom, left, right
	//m3.adjustROI(0, -1, -2, 2);

	//cout << endl << "<관심영역 변경 후>" << endl;
	//print_locateROI("m2", m2);
	//print_locateROI("m3", m3);
	//cout << endl;
	//cout << "[변경 m2] = " << endl << m2 << endl;
	//cout << "[변경 m3] = " << endl << m3 << endl;


	/// mat type
	//Mat m1, m2, m3;
	//Mat m4 = Mat::zeros(2, 6, CV_8UC1);
	//Mat add1(2, 3, CV_8UC1, Scalar(100));
	//Mat add2 = (Mat)Mat::eye(4, 3, CV_8UC1);

	//m1.push_back(100);
	//m1.push_back(200);
	//m2.push_back(100.5);
	//m2.push_back(200.6);
	//m3.push_back(add1);
	//m3.push_back(add2);

	//m4.push_back(add1.reshape(1, 1));
	//m4.push_back(add2.reshape(1, 2));

	//print_matInfo("m1", m1);
	//print_matInfo("m2", m2);
	//print_matInfo("m3", m3);
	//print_matInfo("m4", m4);

	//m1.pop_back(1);	// row 1개 pop
	//m2.pop_back(2);	// row 2개 pop
	//m3.pop_back(3);	// row 3개 pop

	//cout << "m1" << endl << m1 << endl;
	//cout << "m2" << endl << m2 << endl;
	//cout << "m3" << endl << m3 << endl;


	/// mat release
	//Mat m1(2, 6, CV_8UC1, Scalar(100));
	//Mat m2(3, 3, CV_32S);
	//Range r1(0, 2), r2(0, 2);
	//Mat m3 = m1(r1, r2);

	//print_matInfo("m1", m1);
	//print_matInfo("m2", m2);	// 초기화 값이 없으니까 쓰레기값으로 초기화
	//print_matInfo("m3", m3);

	//m2.release();
	//m3.release();
	//print_matInfo("m2", m2);
	//print_matInfo("m3", m3);
	//print_matInfo("m1", m1);

	//m1.release();
	//print_matInfo("m1", m1);


	/// inv, t
	/*
		cross: 외적
		dot: 내적
		inv: 역행렬
		mul: 두 행렬 원소 간 곱셈
		t: 전치행렬
	*/
	/*float data[] = {
		1, 0, 2,
		-3, 2, 6,
		-1, -2, 3
	};

	Mat m1(3, 3, CV_32F, data);
	Mat m2(Matx13f(6, 30, 8));
	Mat m2_t = m2.t();

	Mat m1_inv = m1.inv(DECOMP_LU);
	Mat x = m1_inv * m2_t;

	cout << "[m1] = " << endl << m1 << endl << endl;
	cout << "[m1_inv] = " << endl << m1_inv << endl << endl;
	cout << "[m2] = " << endl << m2 << endl << endl;

	cout << "연립방정식의 해 x1, x2, x3 = " << x.t()<< endl << endl;
	
*/

	/// saturate_cast<_Tp>()
	/* 
		1. saturate_cast<_Tp>()
		
		영상 데이터의 컬러 공간변환, 밝기 / 대조 조정, 샤프닝, 보간법 등의 다양한 연산결과가
		8bit 범위를 벗어나는 결과를 가질 수 있음. (반드시 8bit가 아니라 예시일 뿐)
		이러한 결과를 오류없이 8bit로 수용하기 위해 포화산술(saturation arithmetics) 연산을 사용.
		연산결과가 8bit 범위 초과시 0 또는 255 중 가까운 값으로 저장
		OpenCV는 행렬 연산에 대해서 포화 산술 연산을 사용
		기본 자료형에 대해서는 포화 산술이 가능하도록 saturate_cast<_Tp>()
		템플릿 메소드를 제공
	*/

	//Matx<uchar, 2, 2> m1;
	//Matx<ushort, 2, 2> m2;

	//m1(0, 0) = -50;
	//m1(0, 1) = 300;
	//m1(1, 0) = saturate_cast<uchar>(-50);
	//m1(1, 1) = saturate_cast<uchar>(300);

	//m2(0, 0) = -50;
	//m2(0, 1) = 80000;
	//m2(1, 0) = saturate_cast<unsigned short>(-50);
	//m2(1, 1) = saturate_cast<unsigned short>(80000);

	//cout << "[m1] = " << endl << m1 << endl;
	//cout << "[m2] = " << endl << m2 << endl;


	/// CV_Error
	String msg1 = "a is one";
	String msg2 = "a is two";
	String msg3 = "a is three";
	int a;

	while (true)
	{
		cout << "input a : ";
		cin >> a;

		try {
			if (a == 0) CV_Error(Error::StsDivByZero, "a is zero");
			if (a == 1) CV_Error(Error::StsBadSize, msg1);
			if (a == 2) CV_Error_(Error::StsOutOfRange, ("%s : %d", msg2.c_str(), a));	// CV_ERROR_: 두 번째 인자값에 string format 사용 가능.
			if (a == 3) CV_Error_(Error::StsBadArg, ("%s : %d", msg3.c_str(), a));
			CV_Assert(a != 4);
		}
		catch (cv::Exception& e)
		{
			cout << "Exception code (" << e.code << "):" << e.what();
			cout << endl;
			if (e.code == Error::StsAssert)
				break;
		}
	}


	return 0;
}