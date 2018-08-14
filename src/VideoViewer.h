#pragma once
#include "Program.h"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <sstream>
#include "STDIOAdapter.h"



class VideoViewer : public Program
{
private:
	cv::VideoCapture cap;
	cv::Mat frame;

	std::stringstream getBitMap(cv::Mat inputImage);
	void getNextFrame();
	void showVideoFrame();

public:
	VideoViewer(const std::string& path);
	~VideoViewer();
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
