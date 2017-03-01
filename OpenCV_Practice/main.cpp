#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat video_frame, camera_frame, edge_frame;
Mat gray_camera, edges, ROI;
int slider_value;

void on_trackbar(int, void*) {
	double alpha = (double)slider_value / 100.0;
	double beta = (1.0 - alpha);
	addWeighted(camera_frame, beta, edge_frame, alpha, 0.0, camera_frame);
}

int main() {	
	VideoCapture video("input/jaguar.mp4");
	VideoCapture camera(0);

	if (!video.isOpened() || !camera.isOpened()) {
		cout << "Cannot open the video" << endl;
		return -1;
	}

	namedWindow("OpenCV Practice", 1);

	slider_value = 0;
	createTrackbar("Ratio", "OpenCV Practice", &slider_value, 100, on_trackbar);

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

		on_trackbar(slider_value, 0);

		ROI = video_frame(Rect(0, 0, camera_frame.cols, camera_frame.rows));

		addWeighted(ROI, 0, camera_frame, 1, 0, ROI);

		if (video.get(CV_CAP_PROP_FRAME_COUNT) - video.get(CV_CAP_PROP_POS_FRAMES) > 0)
			imshow("OpenCV Practice", video_frame);
		else
			video.set(CV_CAP_PROP_POS_FRAMES, 0);


		if(waitKey(30)>=0) break;
	}
	return 0;
}