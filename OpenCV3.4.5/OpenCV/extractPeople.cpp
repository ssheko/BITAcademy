#include <opencv\cv.h>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include <string.h>

using namespace cv;
using namespace std;

int components = 0;
void countConnectedComponent(Mat* frame, int** isVisited);
void isConnectedComponent(Mat* frame, int** isVisited, int components, int x, int y);
int x, y;

int main()
{
	Mat frame, out, background;

	vector<Mat> channels(3);

	int thresh = 40;
	int max_thresh = 255;

	int n = 3;
	int element_shape = MORPH_RECT;
	Mat element = getStructuringElement(element_shape, Size(n, n));
	Mat structuring_element(20, 20, CV_8U, Scalar(1));

	int MAX_KERNEL_LENGTH = 20;

	double intensity = 0.0;
	double tmp = 0.0;
	float c = 0.4;

	VideoCapture capture;
	capture.open("extract_in.avi");


	/* 결과 영상 저장 */
	double fps = 15;
	int fourcc = CV_FOURCC('X', 'V', 'I', 'D'); // codec

	bool isColor = true;
	VideoWriter *video = new VideoWriter;

	if (!video->open("result.avi", fourcc, fps, /*Size(360, 288)*/Size(426, 240), isColor)){

		delete video;

		return 0;

	}

	while (1){
		if (!capture.isOpened())
		{
			cout << "Video not read \n";
			return 1;
		}

		capture.read(frame);
		if (frame.rows == 0)
			break;
		resize(frame, frame, Size(frame.cols / 3, frame.rows / 3));

		// 일단 처음에 읽어 들인 영상 프레임을 배경으로 지정.
		frame.copyTo(background);

		for (;;)
		{
			int count = 0;
			capture.read(frame);

			if (frame.rows == 0)
				break;
			resize(frame, frame, Size(frame.cols / 3, frame.rows / 3));


			int** isVisited = (int**)malloc(frame.rows*sizeof(int*));
			for (int index = 0; index < frame.rows; ++index){
				isVisited[index] = (int*)malloc(frame.cols * sizeof(int));
				memset(isVisited[index], 0, sizeof(int)*frame.cols);
			}

			
			if (frame.rows > 0)
				absdiff(frame, background, out);
			else
				break;


			// threshold
			cvtColor(out, out, CV_BGR2GRAY);
			blur(out, out, Size(3, 3));

			threshold(out, out, thresh, max_thresh, THRESH_BINARY);

			// closing
			morphologyEx(out, out, MORPH_CLOSE, structuring_element);
			erode(out, out, element);


			countConnectedComponent(&out, isVisited);


			putText(frame, to_string(components), Point(out.rows - 30, 30), 2, 1.2, Scalar::all(255));

			*video << frame;

			for (int i = 0; i < frame.rows; ++i){
				delete[] isVisited[i];
			}


			delete[] isVisited;

			imshow("Video", frame);
			imshow("Difference", out);

			char c = (char)waitKey(1);
			if (c == 27)
				break;
		}

	}

	delete video;
	destroyAllWindows();
	capture.release();
	return 0;
}

void countConnectedComponent(Mat* frame, int** isVisited)
{
	components = 0;
	for (x = 0; x < frame->rows; x++){
		for (y = 0; y < frame->cols; y++){
			if (frame->at<uchar>(x, y) == 0) continue;
			if (isVisited[x][y] != 0) continue;

			components++;
			isConnectedComponent(frame, isVisited, components, x, y);

		}
	}

}

void isConnectedComponent(Mat* frame, int** isVisited, int components, int x, int y)
{
	if (frame->at<uchar>(x, y) == 0) return;
	if (isVisited[x][y] != 0) return;
	isVisited[x][y] = components;

	if (x > 0 && y > 0) isConnectedComponent(frame, isVisited, components, x - 1, y - 1);
	if (y > 0) isConnectedComponent(frame, isVisited, components, x, y - 1);
	if (x < frame->rows - 1 && y > 0) isConnectedComponent(frame, isVisited, components, x + 1, y - 1);
	if (x > 0) isConnectedComponent(frame, isVisited, components, x - 1, y);
	if (x < frame->rows - 1) isConnectedComponent(frame, isVisited, components, x + 1, y);
	if (x > 0 && y < frame->cols - 1) isConnectedComponent(frame, isVisited, components, x - 1, y + 1);
	if (y < frame->cols - 1) isConnectedComponent(frame, isVisited, components, x, y + 1);
	if (x < frame->rows - 1 && y < frame->cols - 1) isConnectedComponent(frame, isVisited, components, x + 1, y + 1);

}

