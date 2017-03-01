#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	Mat video_frame, camera_frame, edge_frame;
	Mat gray_camera, edges, ROI;
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

		cvtColor(camera_frame, gray_camera, CV_BGR2GRAY);
		blur(gray_camera, edges, Size(3, 3));
		Canny(gray_camera, edges, 100, 200);
		edge_frame = Scalar::all(0);
		gray_camera.copyTo(edge_frame, edges);
		cvtColor(edge_frame, edge_frame, CV_GRAY2BGR);

		addWeighted(camera_frame, 0.5, edge_frame, 0.5, 0, camera_frame);
		ROI = video_frame(Rect(0, 0, camera_frame.cols, camera_frame.rows));

		addWeighted(ROI, 0, camera_frame, 1, 0, ROI);

		//if (video_frame.rows > 0)
		imshow("OpenCV Practice", video_frame);
		//else
		//	break;


		if(waitKey(30)>=0) break;
	}
	return 0;
}