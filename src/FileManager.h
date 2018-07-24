#pragma once
#include "Program.h"
#include <vector>
#include <sstream>
#include <iostream>
#include "../Fonts/fonts.h"
#include <atomic>
#include <filesystem>
#include <algorithm>
#include "command_line.h"

namespace fs = std::filesystem;

enum FileManagerContent {
	VIEW, INFO, SLEEP
};

class FileManager : public Program
{
private:
	std::string startPath;
	std::vector<std::string> pathVector;
	std::vector<std::string> directoryContent;
	std::string getActualPath();
	void updateDirectoryContent(const unsigned int actualPosition);
	void printDirectoryContent(const unsigned int actualPosition);
	void updateActualChosenOption();
	void showFileInfo();
	void setPathVector(std::string start_path);
	std::string getSizeOfFile(const std::string& path) const;
	std::string getFileDescription(const std::string& path) const;
	std::string getNumberOfFilesInDirectory(const std::string& path) const;

	std::atomic_bool wasChange{true};

	//Position pointer.
	std::atomic_uint actualPosition{ 0 };
	std::atomic_int actualFirstCharIndex{ 0 };

	//Display screen pointer.
	std::atomic<FileManagerContent> content = VIEW;

	/*Class parameters*/
	const unsigned int DISPLAY_MAX_CHARS = 16;
	const unsigned int DISPLAY_START_POS_X = 5;
	const unsigned int DISPLAY_START_POS_Y = 10;
	const int unsigned DISPLAY_INC_Y = 4;
	const int unsigned FONT_SIZE = 8;
	const int unsigned LINE_ON_PAGE = 7;
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

	void OnKey2Pressed();
	void OnKey2Released();

	void OnKey3Pressed();
	void OnKey3Released();

	void OnExit();

	void OnSleep();

	/*Thread function - pure virtual*/
	void operator()();
};
