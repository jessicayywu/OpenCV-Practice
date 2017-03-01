#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	Mat video_frame, camera_frame, dst_frame;
	VideoCapture video("input/jaguar.mp4");
	VideoCapture camera(0);

	if (!video.isOpened() || !camera.isOpened()) {
		cout << "Cannot open the video" << endl;
		return -1;
	}

	namedWindow("OpenCV Practice", 1);

	while (1) {
		video >> video_frame;
		camera >> camera_frame;

		resize(camera_frame, camera_frame, Size(camera_frame.cols / 3, camera_frame.rows / 3));
		
		Mat dst_frame = video_frame(Rect(0, 0, camera_frame.cols, camera_frame.rows));
		
		addWeighted(dst_frame, 0, camera_frame, 1, 0, dst_frame);

		//if (video_frame.rows > 0)
		imshow("OpenCV Practice", video_frame);
		//else
		//	break;


		if(waitKey(30)>=0) break;
	}
	return 0;
}