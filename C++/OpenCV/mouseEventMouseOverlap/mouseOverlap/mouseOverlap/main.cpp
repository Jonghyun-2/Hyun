#include "header.h"

cv::Mat pal(cv::Size(500, 500), CV_32FC3);
cv::Mat img;

int main() {
	
	cv::Rect box_size(100, 100, 200, 200);
	cv::rectangle(pal, box_size, (255, 255, 255), 3);
	cv::Point a(150, 150);
	cv::Point b(20, 20);
	if (box_size.contains(a)) {
		cout << "aa" << endl;
	}
	if (!box_size.contains(b)) {
		cout << "nn" << endl;
	}
	//cv::imshow("test",pal);
	//cv::setMouseCallback("test", onMouse);
	//cv::waitKey();
	//cv::destroyAllWindows();
	
	return 0;
}


void onMouse(int event, int x, int y, int flags, void*) {

	switch (event) {
	case cv::MouseEventTypes::EVENT_MOUSEMOVE:
		img = pal.clone();

		//이부분에 버튼안에 들어오면 색깔 바뀌도록
		if(x)
		

	default:
		break;

	}
	return;
}