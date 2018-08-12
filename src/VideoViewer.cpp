#include "VideoViewer.h"

gdiplus::Bitmap VideoViewer::getBitMap(cv::Mat inputImage)
{
	cv::Size size = inputImage.size();
	gdiplus::Bitmap bitmap(size.width, size.height, inputImage.step1(), PixelFormat24bppRGB, inputImage.data);
	return bitmap;
}

VideoViewer::VideoViewer(std::string path) : Program("VideoViewer", "pic/VideoViewer"), cap(cv::VideoCapture::cap(path))
{
	if (!cap.isOpened())
		std::cerr << "Cannot find file!" << std::endl;

	//Set resolution
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 128);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 128);
}

void VideoViewer::getNextFrame()
{
	cap >> frame;
}

void VideoViewer::OnLeftKeyPressed()
{

}
void VideoViewer::OnLeftKeyReleased()
{

}

void VideoViewer::OnRightKeyPressed()
{

}

void VideoViewer::OnRightKeyReleased()
{

}

void VideoViewer::OnUpKeyPressed()
{

}
void VideoViewer::OnUpKeyReleased()
{

}

void VideoViewer::OnDownKeyPressed()
{

}
void VideoViewer::OnDownKeyReleased()
{

}

void VideoViewer::OnPressKeyPressed()
{

}
void VideoViewer::OnPressKeyReleased()
{

}

void VideoViewer::OnKey1Pressed()
{

}
void VideoViewer::OnKey1Released()
{

}


void VideoViewer::OnKey2Pressed()
{

}

void VideoViewer::OnKey2Released()
{

}

void VideoViewer::OnKey3Pressed()
{

}
void VideoViewer::OnKey3Released()
{

}

void VideoViewer::OnExit()
{

}

void VideoViewer::OnSleep()
{

}

void VideoViewer::operator()()
{
	/*Main loop of program*/
	while (true)
	{
	
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
