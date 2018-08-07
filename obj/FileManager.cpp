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

std::string FileManager::getNumberOfFilesInDirectory(std::string& path) const
{
	std::stringstream command;
	command << "ls -a " << path << " | wc -l";
	return exec(command.str().c_str());
}

std::string FileManager::getSizeOfFile(std::string& path) const
{
	std::stringstream command;
	command << "du - h " << path;
	return exec(command.str().c_str());

}

void FileManager::updateActualChosenOption()
{
	int posOffset = actualFirstCharIndex.load();

	//Count actual position.
	int actualPosY = DISPLAY_START_POS_Y + actualPosition * (2 * DISPLAY_INC_Y + FONT_SIZE);


	actualFirstCharIndex.store((posOffset + 1) % (directoryContent[actualPosition].length() - DISPLAY_MAX_CHARS));

	std::string temp_file_path = getActualPath() + directoryContent[actualPosition];
	fs::path path(temp_file_path);
	std::error_code ec;

	COLOR actual_font_color;

	//Check file is directory.
	if (fs::is_directory(path, ec))
		actual_font_color = DIR_FONT_COLOR;

	else
		actual_font_color = FILE_FONT_COLOR;

	LCD_OS::getLCDOperationSystem().OS_GUI_DrawRectangle(0, actualPosY + DISPLAY_INC_Y, LCD_WIDTH, actualPosY + 2 * DISPLAY_INC_Y + FONT_SIZE, SELECTION_COLOR, DRAW_FULL, DOT_PIXEL_DFT);

	LCD_OS::getLCDOperationSystem().OS_GUI_DisString_EN(DISPLAY_START_POS_X, actualPosY + DISPLAY_INC_Y, directoryContent[actualPosition].substr(posOffset,DISPLAY_MAX_CHARS - 1).c_str(), FONT, SELECTION_COLOR, actual_font_color);


}

std::string FileManager::getFileDescription(std::string& path) const
{
	std::stringstream command;
	command << "file " << path;
	return exec(command.str().c_str());
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
		}

		if (directoryContent[i].length() > DISPLAY_MAX_CHARS)
		{
			actualFirstCharIndex.store(1);
		}
		else
		{
			actualFirstCharIndex.store(-1);
		}

		std::string temp_file_path = getActualPath() + directoryContent[i];
		fs::path path(temp_file_path);
       	std::error_code ec;

        //Check file is directory.
        if (fs::is_directory(path, ec))
			actual_font_color = DIR_FONT_COLOR;

		else
			actual_font_color = FILE_FONT_COLOR;

		//Analize size of actual string to display.
		if (directoryContent[i].length() > DISPLAY_MAX_CHARS)
		{
			LCD_OS::getLCDOperationSystem().OS_GUI_DisString_EN(DISPLAY_START_POS_X, actualPosY + DISPLAY_INC_Y, directoryContent[i].substr(0, DISPLAY_MAX_CHARS - 1).c_str(), FONT, actual_background_color, actual_font_color);
		}
		else
			LCD_OS::getLCDOperationSystem().OS_GUI_DisString_EN(DISPLAY_START_POS_X, actualPosY + DISPLAY_INC_Y, directoryContent[i].c_str(), FONT, actual_background_color, actual_font_color);

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
	actualFirstCharIndex.store(0);
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
		actualFirstCharIndex.store(0);
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
		actualFirstCharIndex.store(0);
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
		actualFirstCharIndex.store(0);
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
		else if(!(actualFirstCharIndex.load() < 0))
		{
			updateActualChosenOption();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
