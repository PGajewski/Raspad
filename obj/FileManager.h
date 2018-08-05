#pragma once
#include "Program.h"
#include <vector>
#include <sstream>
#include <iostream>
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
	std::string FileManager::getSizeOfFile(std::string& path) const;
	std::string getFileDescription(std::string& path) const;


	std::atomic_bool wasChange{true};

	//Position pointer.
	std::atomic_uint actualPosition{ 0 };
	std::atomic_uint actualFirstCharIndex{ 0 };

	/*Class parameters*/
	const int DISPLAY_MAX_CHARS = 16;
	const int DISPLAY_START_POS_X = 5;
	const int DISPLAY_START_POS_Y = 10;
	const int DISPLAY_INC_Y = 4;
	const int FONT_SIZE = 8;
	const int LINE_ON_PAGE = 8;
	sFONT* FONT = &Font12;
	const COLOR BACKGROUND = BLACK;
	const COLOR FILE_FONT_COLOR = WHITE;
	const COLOR DIR_FONT_COLOR = GREEN;
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
