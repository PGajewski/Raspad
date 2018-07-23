#pragma once
#include "Program.h"
<<<<<<< HEAD
#include "opencv2/opencv.hpp"
=======
#include "opencv3/opencv.hpp"
#include <gd.h>

>>>>>>> b88e7cbfbf7e59325106b6936c0bd3c3d1cc4a38


class VideoViewer : public Program
{
private:
	cv::VideoCapture cap;
	cv::Mat frame;

	gdi::Bitmap getBitMap(cv::Mat inputImage);

public:
	VideoViewer(std::string path);

	/*Functions to handle signals from operational system*/
	void OnLeftKeyPressed();
	void OnLeftKeyReleased();

	void OnRightKeyPressed();
	void OnRightKeyReleased();

	void OnUpKeyPressed();
	void OnUpKeyReleased();

	void OnDownKeyPressed();
	void OnDownKeyReleased();

	void OnPressKeyPressed();
	void OnPressKeyReleased();

	void OnKey1Pressed();
	void OnKey1Released();

	void OnKey2Pressed();
	void OnKey2Released();

	void OnKey3Pressed();
	void OnKey3Released();

	void OnExit();

	void OnSleep();

	/*Thread function - pure virtual*/
	void operator()();
};
