#include <opencv2/opencv.hpp>
//#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

/// 마우스 이벤트
//void onMouse(int, int, int, int, void*);

/// 트랙바 이벤트
//string title = "트랙바 이벤트";
//Mat image;
//
//void onChange(int value, void* userData)
//{
//	int add_value = value - 130;
//	cout << "추가 화소값" << add_value << endl;
//
//	Mat tmp = image + add_value;
//	imshow(title, tmp);
//}

/// 트랙바 이벤트 2
//string title = "밝기 변경";
//string bar_name = "밝기값";
//Mat image;
//void onChange(int value, void* userData)
//{
//	int add_value = value - 130;
//	cout << "추가 화소값" << add_value << endl;
//
//	Mat tmp = image + add_value;
//	imshow(title, tmp);
//}
//
//void onMouse(int event, int x, int y, int flags, void* param)
//{
//	if (event == EVENT_RBUTTONDOWN)
//	{
//		add(image, 10, image);
//	}
//	else if (event == EVENT_LBUTTONDOWN)
//	{
//		subtract(image, 10, image);
//	}
//	setTrackbarPos(bar_name, title, image.at<uchar>(0, 0));
//	imshow(title, image);
//}

/// Event Drawing
//string title = "Event Drawing";
//Mat image;
//
//void onMouse(int event, int x, int y, int flags, void* param)
//{
//	static Point pt(-1, -1);
//	switch (event)
//	{
//	case EVENT_LBUTTONDOWN:
//		if (pt.x < 0)
//			pt = Point(x, y);
//		else
//		{
//			rectangle(image, pt, Point(x, y), Scalar(50), 2);
//			imshow(title, image);
//			pt = Point(-1, -1);
//		}
//		break;
//	case EVENT_RBUTTONDOWN:
//		if (pt.x < 0)
//			pt = Point(x, y);
//		else
//		{
//			Point2d pt2 = pt - Point(x, y);
//			int radius = (int)sqrt(pt2.x * pt2.x + pt2.y * pt2.y);
//			circle(image, pt, radius, Scalar(150), 2);
//
//			imshow(title, image);
//			pt = Point(-1, -1);
//		}
//		break;
//	}
//}

/// print_matInfo
//void print_matInfo(string name, Mat m)
//{
//	String mat_type;
//	if (m.depth() == CV_8U)
//		mat_type = "CV_8U";
//	else if (m.depth() == CV_8S)
//		mat_type = "CV_8S";
//	else if (m.depth() == CV_16U)
//		mat_type = "CV_16U";
//	else if (m.depth() == CV_16S)
//		mat_type = "CV_16S";
//	else if (m.depth() == CV_32S)
//		mat_type = "CV_32S";
//	else if (m.depth() == CV_32F)
//		mat_type = "CV_32F";
//	else if (m.depth() == CV_64F)
//		mat_type = "CV_64F";
//
//	cout << name;
//	cout << format(": depth(%d) channels(%d) -> 자료형: ", m.depth(), m.channels());
//	cout << mat_type << "C" << m.channels() << endl;
//}

/// VideoCapture
void put_string(Mat& frame, string text, Point pt, int value)
{
	text += to_string(value);
	Point shade = pt + Point(2, 2);
	int font = FONT_HERSHEY_SIMPLEX;
	putText(frame, text, shade, font, 0.7, Scalar(0, 0, 0), 2);
	putText(frame, text, pt, font, 0.7, Scalar(120, 200, 90), 2);
}


int main()
{
	/// namedWindow
	//Mat image1(300, 400, CV_8U, Scalar(255));
	//Mat image2(300, 400, CV_8U, Scalar(200));

	//string title1 = "white window";
	//string title2 = "gray window";

	//namedWindow(title1, WINDOW_AUTOSIZE);
	//namedWindow(title2, WINDOW_NORMAL);

	//moveWindow(title1, 100, 200);
	//moveWindow(title2, 300, 200);

	//imshow(title1, image1);
	//imshow(title2, image2);

	//waitKey();

	//destroyAllWindows();


	/// namedWindow AUTOSIZE, NORMAL
	//Mat image(300, 400, CV_8U, Scalar(255));

	//string title1 = "AUTOSIZE";
	//string title2 = "NORMAL";

	//namedWindow(title1, WINDOW_AUTOSIZE);
	//namedWindow(title2, WINDOW_NORMAL);

	//moveWindow(title1, 500, 200);
	//moveWindow(title2, 500, 200);

	//imshow(title1, image);
	//imshow(title2, image);

	//waitKey();


	/// 키보드 이벤트
	/*
		int waitKey(int delay = 0)
		int waitKeyEx(int delay = 0): 키 이벤트 발생시 해당 키 값 반환

		delay <= 0 : 무한 대기
		delay > 0 : 지연시간동안 대기(ms), 지연시간 내 키 이벤트 없으면 -1 반환
	*/
	//Mat image(200, 300, CV_8U, Scalar(255));

	//namedWindow("키보드 이벤트", WINDOW_AUTOSIZE);

	//imshow("키보드 이벤트", image);

	//while (1)
	//{
	//	int key = waitKeyEx(20);
	//	if (key == 27)	// ESC
	//		break;

	//	switch (key)
	//	{
	//	case 'a': cout << "a 입력" << endl;
	//		break;
	//	case 'b': cout << "b 입력" << endl;
	//		break;
	//	case 0x41: cout << "A 입력" << endl;
	//		break;
	//	case 66: cout << "B 입력" << endl;
	//		break;
	//	case 2424832: cout << "왼쪽 화살표 입력" << endl;
	//		break;
	//	case 2490368: cout << "위쪽 화살표 입력" << endl;
	//		break;
	//	case 2555904: cout << "오른쪽 화살표 입력" << endl;
	//		break;
	//	case 2621440: cout << "아래쪽 화살표 입력" << endl;
	//		break;
	//	}
	//}


	/// 마우스 이벤트
	/*
		setMouseCallback(const String& winname, MouseCallback onMouse, void* userdata = 0);

	*/
	//Mat image(200, 300, CV_8U);
	//image.setTo(255);

	//imshow("마우스 이벤트1", image);
	//imshow("마우스 이벤트2", image);
	//int a = 10;

	//setMouseCallback("마우스 이벤트1", onMouse, &a);
	//waitKeyEx(0);


	/// 트랙바 이벤트
	//int value = 128;
	//image = Mat(300, 400, CV_8UC1, Scalar(120));

	//namedWindow(title, WINDOW_AUTOSIZE);
	//createTrackbar("밝기값", title, &value, 255, onChange);

	//imshow(title, image);
	//waitKey(0);

	/// 트랙바 이벤트 2
	//int value = 130;
	//image = Mat(300, 500, CV_8UC1, Scalar(120));

	//namedWindow(title, WINDOW_AUTOSIZE);
	//createTrackbar("밝기값", title, &value, 255, onChange);
	//setMouseCallback(title, onMouse, 0);

	//imshow(title, image);
	//waitKey(0);


	/// drawing (rectangle, line)
	//Scalar blue(255, 0, 0), red(0, 0, 255), green(0, 255, 0);
	//Scalar white(255, 255, 255);
	//Scalar yellow(0, 255, 255);

	//Mat image(400, 600, CV_8UC3, white);
	//Point pt1(50, 130), pt2(200, 300), pt3(300, 150), pt4(400, 50);
	//Rect rect(pt3, Size(200, 150));

	//line(image, pt1, pt2, red);
	//line(image, pt3, pt4, green, 2, LINE_AA);
	//line(image, pt3, pt4, green, 3, LINE_8, 1);	// 좌표값 1 쉬프트 = 값 / 2

	//rectangle(image, rect, blue, 2);
	//rectangle(image, rect, blue, FILLED, LINE_4, 1);
	//rectangle(image, pt1, pt2, red, 3);


	//imshow("직선 사각형", image);
	//waitKey(0);

	/// putText
	//Scalar olive(128, 128, 0), violet(221, 160, 221), brown(42, 42, 165);
	//Point pt1(20, 100), pt2(20, 200), pt3(20, 250);

	//Mat image(300, 500, CV_8UC3, Scalar(255, 255, 255));

	//putText(image, "SIMPLEX", Point(20, 30), FONT_HERSHEY_SIMPLEX, 1, brown);	// putText 후 Mat data가 변경됨.
	//putText(image, "DUPLEX", pt1, FONT_HERSHEY_DUPLEX, 2, olive);
	//putText(image, "TRILEX", pt2, FONT_HERSHEY_TRIPLEX, 2, violet);
	//putText(image, "ITALIC", pt3, FONT_HERSHEY_PLAIN | FONT_ITALIC, 2, violet);

	//imshow("putText", image);
	//waitKey(0);

	/// putText
	//Scalar orange(0, 165, 255), blue(255, 0, 0), magenta(255, 0, 255);
	//Mat image(300, 500, CV_8UC3, Scalar(255, 255, 255));

	//Point center = (Point)image.size() / 2;
	//Point pt1(70, 50), pt2(350, 220);

	//circle(image, center, 100, blue);
	//circle(image, pt1, 80, orange, 2);
	//circle(image, pt2, 60, magenta, -1);

	//int font = FONT_HERSHEY_COMPLEX;
	//putText(image, "center_blue", center, font, 1.2, blue);
	//putText(image, "pt1_orange", pt1, font, 0.8, orange);
	//putText(image, "pt2_magenta", pt2 + Point(2, 2), font, 0.5, Scalar(0, 0, 0), 2);
	//putText(image, "pt2_magenta", pt2, font, 0.5, magenta, 1);

	//imshow("원", image);
	//waitKey(0);

	/// RotatedRect
	//Mat image(300, 500, CV_8UC1, Scalar(255));
	//Point2f center(250, 150), pts[4];
	//Size2f size(300, 100);

	//RotatedRect rot_rect(center, size, 20);

	//Rect bound_rect = rot_rect.boundingRect();
	//rectangle(image, bound_rect, Scalar(0), 1);
	//circle(image, rot_rect.center, 1, Scalar(0), 2);
	//rot_rect.points(pts);	// The order is bottomLeft, topLeft, topRight, bottomRight
	//for (int i = 0; i < 4; i++)
	//{
	//	circle(image, pts[i], 4, Scalar(0), 1);
	//	line(image, pts[i], pts[(i + 1) % 4], Scalar(0), 2);
	//}

	//imshow("RotatedRect", image);
	//waitKey(0);

	/// ellipse
	//Scalar orange(0, 165, 255), blue(255, 0, 0), magenta(255, 0, 255);
	//Mat image(300, 700, CV_8UC3, Scalar(255, 255, 255));

	//Point pt1(120, 150), pt2(550, 150);
	//circle(image, pt1, 1, Scalar(0), 1);
	//circle(image, pt2, 1, Scalar(0), 1);

	//ellipse(image, pt1, Size(100, 60), 0, 0, 360, orange, 2);
	//ellipse(image, pt1, Size(100, 60), 0, 30, 270, blue, 4);

	//ellipse(image, pt2, Size(100, 60), 30, 0, 360, orange, 2);
	//ellipse(image, pt2, Size(100, 60), 30, -30, 160, blue, 4);		// start > end : 반시계방향으로.
	////ellipse(image, pt2, Size(100, 60), 30, 330, 160, blue, 4);	// start < end : 시계방향으로 돌림. 

	//imshow("타원", image);
	//waitKey(0);


	/// Event Drawing
	//image = Mat(300, 500, CV_8UC1, Scalar(255));
	//imshow(title, image);
	//setMouseCallback(title, onMouse, 0);

	//waitKey(0);

	/// print_matInfo (gray)
	//string filename = "image/ryan.jpg";
	//Mat gray2gray = imread(filename, IMREAD_GRAYSCALE);
	//Mat gray2color = imread(filename, IMREAD_COLOR);
	//CV_Assert(gray2gray.data&& gray2color.data);	// 이미지를 읽어와 Mat에 넣음. data값이 있으면 주소를 갖고 있는 것.
	//// 둘 중 하나라도 0일 경우, 이미지 값이 없는 것이므로 assert error가 발생해 시스템이 종료된다.

	//Rect roi(100, 100, 1, 1);
	//cout << "행렬 좌표(100, 100) 화소값 " << endl;
	//cout << "gray2gray" << gray2gray(roi) << endl;
	//cout << "gray2color" << gray2color(roi) << endl;

	//print_matInfo("gray2gray", gray2gray);
	//print_matInfo("gray2color", gray2color);

	//imshow("gray2gray", gray2gray);
	//imshow("gray2color", gray2color);

	//waitKey(0);


	/// print_matInfo (color)
	//string filename = "image/bit.bmp";
	//Mat color2gray = imread(filename, IMREAD_GRAYSCALE);
	//Mat color2color = imread(filename, IMREAD_COLOR);
	//CV_Assert(color2gray.data&& color2color.data);	// 이미지를 읽어와 Mat에 넣음. data값이 있으면 주소를 갖고 있는 것.
	//// 둘 중 하나라도 0일 경우, 이미지 값이 없는 것이므로 assert error가 발생해 시스템이 종료된다.

	//Rect roi(100, 100, 1, 1);
	//cout << "행렬 좌표(100, 100) 화소값 " << endl;
	//cout << "color2gray" << color2gray(roi) << endl;
	//cout << "color2color" << color2color(roi) << endl;

	//print_matInfo("color2gray", color2gray);
	//print_matInfo("color2color", color2color);

	//imshow("color2gray", color2gray);
	//imshow("color2color", color2color);

	//waitKey(0);

	/// tiff
	//string filename1 = "image/example_16.tif";
	//string filename2 = "image/example_32.tif";
	//Mat color2unchanged1 = imread(filename1, IMREAD_UNCHANGED);
	//Mat color2unchanged2 = imread(filename2, IMREAD_UNCHANGED);
	//CV_Assert(color2unchanged1.data);
	//CV_Assert(color2unchanged2.data);

	//Rect roi(100, 100, 1, 1);
	//cout << "행렬 좌표(100, 100) 화소값 " << endl;
	//cout << "color2unchanged1" << color2unchanged1(roi) << endl;
	//cout << "color2unchanged2" << color2unchanged2(roi) << endl;

	//print_matInfo("color2unchanged1", color2unchanged1);
	//print_matInfo("color2unchanged2", color2unchanged2);

	//imshow("color2unchanged1", color2unchanged1);
	//imshow("color2unchanged2", color2unchanged2);

	//waitKey(0);


	/// IMWRITE_PNG_COMPRESSION
	//Mat image = imread("image/jpgimg.jpg", IMREAD_COLOR);
	//CV_Assert(image.data);

	//vector<int> params_jpg, params_png;

	//// 항상 아래와 같이 항목, 값 순서로 묶어서 설정해줘야 한다.
	//params_jpg.push_back(IMWRITE_JPEG_QUALITY);
	//params_jpg.push_back(50);

	//params_png.push_back(IMWRITE_PNG_COMPRESSION);
	//params_png.push_back(9);	// 압축률을 9로 설정

	//imwrite("image/write_test1.jpg", image);
	//imwrite("image/write_test2.jpg", image, params_jpg);

	//imwrite("image/write_test.png", image, params_jpg);
	//imwrite("image/write_test.bmp", image);

	/// tif 변환
	//Mat img8 = imread("image/jpgimg.jpg", IMREAD_COLOR);
	//CV_Assert(img8.data);

	//Mat img16, img32;
	//img8.convertTo(img16, CV_16U, 65535 / 255.0);
	//img8.convertTo(img32, CV_32F, 1 / 255.0f);	// 0~1 사이로 만들어주기 위해.

	//Rect roi(10, 10, 3, 3);
	//cout << "img8 행렬의 일부 " << endl << img8(roi) << endl << endl;
	//cout << "img16 행렬의 일부 " << endl << img16(roi) << endl << endl;
	//cout << "img32 행렬의 일부 " << endl << img32(roi) << endl << endl;

	//imwrite("image/write_test_16.tif", img16);
	//imwrite("image/write_test_32.tif", img32);

	//imshow("img16", img16);
	//imshow("img32", img32);
	//waitKey(0);


	/// VideoCapture
	//VideoCapture capture(0);
	//if (!capture.isOpened())
	//{
	//	cout << "카메라가 연결되지 않았습니다." << endl;
	//	exit(1);
	//}

	//cout << "너비 " << capture.get(CAP_PROP_FRAME_WIDTH) << endl;
	//cout << "높이 " << capture.get(CAP_PROP_FRAME_HEIGHT) << endl;
	//cout << "노출 " << capture.get(CAP_PROP_EXPOSURE) << endl;
	//cout << "밝기 " << capture.get(CAP_PROP_BRIGHTNESS) << endl;

	//while (true)
	//{
	//	Mat frame;
	//	capture.read(frame);

	//	put_string(frame, "EXPOS: ", Point(10, 40), capture.get(CAP_PROP_EXPOSURE));
	//	imshow("카메라 영상", frame);
	//	if (waitKey(30) >= 0)
	//		break;
	//}

	/// 영상
	VideoCapture capture(0);
	capture.open("image/video-sample.avi");
	CV_Assert(capture.isOpened());

	double fps = capture.get(CV_CAP_PROP_FPS);
	int delay = 1000 / fps;
	int frame_cnt = 0;
	Mat frame;

	while (capture.read(frame))
	{
		if (waitKey(delay) >= 0)
			break;

		frame_cnt = capture.get(CV_CAP_PROP_POS_FRAMES);
		if (frame_cnt < 100)
			;

		else if (frame_cnt < 200)
			frame -= Scalar(0, 0, 100);	// Red 100 감소
		
		else if (frame_cnt < 300)
			frame += Scalar(100, 0, 0);	// Blue 100 증가
		else if (frame_cnt < 400)
			frame = frame * 1.5;	// 밝기 1.5배
		else if (frame_cnt < 500)
			frame = frame * 0.5;	// 밝기 0.5배

		put_string(frame, "frame_cnt", Point(20, 50), frame_cnt);

		imshow("동영상", frame);
	}

	return 0;
}


/// 마우스 이벤트
//void onMouse(int event, int x, int y, int flags, void* param)
//{
//	switch (event)
//	{
//	case EVENT_LBUTTONDOWN:
//		cout << "마우스 왼쪽버튼 누르기--" << *(int*)param << endl;
//		break;
//	case EVENT_RBUTTONDOWN:
//		cout << "마우스 오른쪽버튼 누르기" << endl;
//		break;
//	case EVENT_RBUTTONUP:
//		cout << "마우스 오른쪽버튼 떼기" << endl;
//		break;
//	case EVENT_LBUTTONDBLCLK:
//		cout << "마우스 왼쪽버튼 더블클릭" << endl;
//		break;
//	}
//}