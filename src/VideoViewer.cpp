#include "VideoViewer.h"
#include "LCD_OS.h"

std::stringstream VideoViewer::getBitMap(cv::Mat inputImage)
{
	std::cout << "GetBitMap" << std::endl;
	std::stringstream stream;
	stream << inputImage;
	return stream;
}

void VideoViewer::showVideoFrame()
{
	std::cout << "showVideoFrame" << std::endl;
	this->getNextFrame();
	std::stringstream stream = getBitMap(this->frame);
	std::cout << "Project stream to file descriptor" << std::endl;
	FILE* fp = STDIOAdapter<std::stringstream>::yield(&stream);
	std::cout << "ShowBitmap" << std::endl;
	LCD_OS::getLCDOperationSystem().OS_LCD_ShowBmpFromStream(fp);
}

VideoViewer::VideoViewer(const std::string& path) : Program("VideoViewer", "pic/VideoViewer")
{
	cv::VideoCap new_cap(path);
	std::cout << "VideoViewer constructor." << std::endl;
	cap.open(path);
	if (!cap.isOpened())
		std::cerr << "Cannot find file!" << std::endl;

	//Set resolution
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 128);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 128);
}

VideoViewer::~VideoViewer()
{
	this->cap.release();
}

void VideoViewer::getNextFrame()
{
	std::cout << "GetNextFrame" << std::endl;
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
		showVideoFrame();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
