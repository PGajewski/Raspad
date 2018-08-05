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
	ss << "/";
	for (auto it = pathVector.begin(); it != pathVector.end(); ++it)
	{
		ss << *it << "/";
	}
	return ss.str();
}

void FileManager::updateDirectoryContent()
{
	//Clear old content.
	directoryContent.clear();

	//Add new.
	for (auto & p : fs::directory_iterator(this->getActualPath()))
	{
		std::vector<std::string> temp_vector;
		mySplit<std::vector<std::string>>(p.path().string(),temp_vector, '/');

		directoryContent.push_back(std::move(temp_vector.back()));
	}
	std::sort(directoryContent.begin(), directoryContent.end());
}

std::string FileManager::getNumberOfFilesInDirectory(std::string& path)
{
	std::stringstream command;
	command << "ls -a " << path << " | wc -l";
	return system(command.str());
}

std::string FileManager::getSizeOfFile(std::string& path) const
{
	std::stringstream command;
	command << "du - h " << path;
	return system(command.str());

}

std::string FileManager::getFileDescription(std::string& path) const
{
	std::stringstream command;
	command << "file " << path;
	return system(command.str());
}

void FileManager::printDirectoryContent()
{
	int actualPosY = DISPLAY_START_POS_Y;
	
	if(!directoryContent.size())
		return;

	//Count range of positions to display.
	int min = actualPosition - actualPosition%LINE_ON_PAGE;
	int max = min + LINE_ON_PAGE;
	for (int i = min; i < max; ++i)
	{
		int posOffset = 0;
		COLOR actual_background_color = BACKGROUND;
		COLOR actual_font_color;
		if (i == actualPosition)
		{
			actual_background_color = SELECTION_COLOR;

			//Print rectangle for actual position.
			LCD_OS::getLCDOperationSystem().OS_GUI_DrawRectangle(0, actualPosY + DISPLAY_INC_Y, LCD_WIDTH, actualPosY + 2 * DISPLAY_INC_Y + FONT_SIZE, SELECTION_COLOR, DRAW_FULL, DOT_PIXEL_DFT);
			posOffset = actualFirstCharIndex.load();
			actualFirstCharIndex.store((posOffset + 1) % (directoryContent[i].length() - DISPLAY_MAX_CHARS));
		}

		std::string temp_file_path = getActualPath() + directoryContent[i];
		fs::path path(temp_file_path);
       	std::error_code ec;

        //Check file is directory.
        if (fs::is_directory(path, ec))
			actual_font_color = DIR_FONT_COLOR;

		else
			actual_font_color = FILE_FONT_COLOR;

		LCD_OS::getLCDOperationSystem().OS_GUI_DisString_EN(DISPLAY_START_POS_X, actualPosY + DISPLAY_INC_Y, directoryContent[i].substr(posOffset, posOffset + DISPLAY_MAX_CHARS).c_str(), FONT, actual_background_color, actual_font_color);

		//Update position;
		if (actualPosY >= LCD_HEIGHT)
			actualPosY = DISPLAY_START_POS_Y;
		else
			actualPosY += 2 * DISPLAY_INC_Y + FONT_SIZE;
	}
}

void FileManager::OnLeftKeyPressed()
{
	if(pathVector.empty())
		return;

	//Return to previous folder.
	pathVector.pop_back();
	actualPosition.store(0);
	wasChange.store(true);
}
void FileManager::OnLeftKeyReleased()
{

}

void FileManager::OnRightKeyPressed()
{
	//Go to next folder.
	const std::string temp_file_path = getActualPath() + directoryContent[actualPosition.load()];
	const fs::path path(temp_file_path);
	std::error_code ec;
	//Check file is directory.
	if (fs::is_directory(path, ec))
	{
		pathVector.push_back(directoryContent[actualPosition.load()]);
		actualPosition.store(0);
		wasChange.store(true);
		return;
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
		wasChange.store(true);
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
		wasChange.store(true);
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
		if(wasChange.load())
		{
			LCD_OS::getLCDOperationSystem().OS_LCD_Clear(BACKGROUND);
			//Update actual directory content.
			updateDirectoryContent();

			//Print values.
			printDirectoryContent();

			wasChange.store(false);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
