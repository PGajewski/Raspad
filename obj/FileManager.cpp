#include "FileManager.h"
#include "LCD_OS.h"
#include <iostream>

FileManager::FileManager(std::string start_path) : Program("FileManager", "pic/FileManager")
{
	//Split start path.
	mySplit<std::vector<std::string>>(start_path, pathVector, '/');

	//Delete empty strings.
	auto itr = std::find(pathVector.begin(), pathVector.end(), "");
	if (itr != pathVector.end()) pathVector.erase(itr);
}

std::string FileManager::getActualPath()
{
	std::stringstream ss;
	for (auto it = pathVector.begin(); it != pathVector.end(); ++it)
	{
		ss << "/" << *it;
	}
	return ss.str();
}

void FileManager::updateDirectoryContent()
{
	for (auto & p : fs::directory_iterator(this->getActualPath()))
	{
		directoryContent.push_back(p.path().string());
	}
}

void FileManager::printDirectoryContent()
{
	int actualPosY = DISPLAY_START_POS_Y;
	int i = 0;
	for (auto it = directoryContent.begin(); it != directoryContent.end(); ++it)
	{
		if (i == actualPosition)
		{
			//Print rectangle for actual position.
			LCD_OS::getLCDOperationSystem().OS_GUI_DrawRectangle(0, actualPosY, LCD_WIDTH, actualPosY + 2 * DISPLAY_INC_Y + FONT_SIZE, SELECTION_COLOR, DRAW_FULL, DOT_PIXEL_DFT);
		}
		LCD_OS::getLCDOperationSystem().OS_GUI_DisString_EN(DISPLAY_START_POS_X, actualPosY + DISPLAY_INC_Y, (*it).c_str(), FONT, BACKGROUND, FONT_COLOR);
		
		//Update position;
		if (actualPosY >= LCD_HEIGHT)
			actualPosY = DISPLAY_START_POS_Y;
		else
			actualPosY += 2 * DISPLAY_INC_Y + FONT_SIZE;
		++i;
	}
}

void FileManager::OnLeftKeyPressed()
{
	//Return to previous folder.
	pathVector.pop_back();
}
void FileManager::OnLeftKeyReleased()
{

}

void FileManager::OnRightKeyPressed()
{
	//Go to next folder.
	const std::string temp_file_path = getActualPath() + "/" + directoryContent[actualPosition.load()];
	const fs::path path(temp_file_path);
	std::error_code ec;
	//Check file is directory.
	if (fs::is_directory(path, ec))
	{
		pathVector.push_back(directoryContent[actualPosition.load()]);
	}
	if (ec) // Optional handling of possible errors.
	{
		std::cerr << "Error in is_directory: " << ec.message();
	}
}

void FileManager::OnRightKeyReleased()
{

}

void FileManager::OnUpKeyPressed()
{
	if (actualPosition.load() != 0)
	{
		--actualPosition;
	}
}
void FileManager::OnUpKeyReleased()
{

}

void FileManager::OnDownKeyPressed()
{
	if (actualPosition < directoryContent.size())
	{
		++actualPosition;
	}
}
void FileManager::OnDownKeyReleased()
{

}

void FileManager::OnPressKeyPressed()
{

}
void FileManager::OnPressKeyReleased()
{

}

void FileManager::OnKey1Pressed()
{

}
void FileManager::OnKey1Released()
{

}

/*
void FileManager::OnKey2Pressed()
{

}
*/
void FileManager::OnKey2Released()
{

}

void FileManager::OnKey3Pressed()
{

}
void FileManager::OnKey3Released()
{

}

void FileManager::OnExit()
{

}


void FileManager::operator()()
{
	/*Main loop of program*/
	while (true)
	{
		//Update actual directory content.
		updateDirectoryContent();

		//Print values.
		printDirectoryContent();
	}
}
