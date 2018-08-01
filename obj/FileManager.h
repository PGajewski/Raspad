#pragma once
#include "Program.h"
#include <vector>
#include <sstream>
#include "../Fonts/fonts.h"
#include <atomic>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

class FileManager : public Program
{
private:
	std::vector<std::string> pathVector;
	std::vector<std::string> directoryContent;
	std::string getActualPath();
	void updateDirectoryContent();
	void printDirectoryContent();

	//Position pointer.
	std::atomic_uint actualPosition{ 0 };

	/*Class parameters*/
	const int DISPLAY_START_POS_X = 5;
	const int DISPLAY_START_POS_Y = 10;
	const int DISPLAY_INC_Y = 4;
	const int FONT_SIZE = 12;
	sFONT* FONT = &Font12;
	const COLOR BACKGROUND = WHITE;
	const COLOR FONT_COLOR = BLACK;
	const COLOR SELECTION_COLOR = RED;


public:
	FileManager(std::string start_path);
	FileManager() : Program("FileManager", "pic/FileManager") {}

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

	//void OnKey2Pressed();
	void OnKey2Released();

	void OnKey3Pressed();
	void OnKey3Released();

	void OnExit();

	/*Thread function - pure virtual*/
	void operator()();
};