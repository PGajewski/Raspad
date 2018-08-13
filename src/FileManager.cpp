#include "FileManager.h"
#include "LCD_OS.h"
#include <iostream>

FileManager::FileManager(std::string start_path) : Program("FileManager", "pic/FileManager"), startPath(start_path)
{
	//Split start path.
	this->setPathVector(startPath);
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

void FileManager::setPathVector(std::string start_path)
{
	//Restore basic path.
	pathVector.clear();
	//Split start path.
	mySplit<std::vector<std::string>>(start_path, pathVector, '/');
	//Delete empty strings.
	auto itr = std::find(pathVector.begin(), pathVector.end(), "");
	if (itr != pathVector.end()) pathVector.erase(itr);
}

void FileManager::updateDirectoryContent(const int actualPosition)
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

std::string FileManager::getNumberOfFilesInDirectory(const std::string& path) const
{
	std::stringstream command;
	command << "ls -a \"" << path << "\" | wc -l";
	return exec(command.str().c_str());
}

std::string FileManager::getSizeOfFile(const std::string& path) const
{
	std::stringstream command;
	command << "du -sh \"" << path << "\" | awk '{print $1;}'";
	return exec(command.str().c_str());

}

void FileManager::updateActualChosenOption()
{
	int posOffset = actualFirstCharIndex.load();

	//Count actual position.
	int actualPosY = DISPLAY_START_POS_Y + actualPosition * (2 * DISPLAY_INC_Y + FONT_SIZE);


	actualFirstCharIndex.store((posOffset + 1) % (directoryContent[actualPosition].length() - DISPLAY_MAX_CHARS + 2));

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

	LCD_OS::getLCDOperationSystem().OS_GUI_DisString_EN(DISPLAY_START_POS_X, actualPosY + DISPLAY_INC_Y, directoryContent[actualPosition].substr(posOffset,DISPLAY_MAX_CHARS-1).c_str(), FONT, SELECTION_COLOR, actual_font_color);


}

std::string FileManager::getFileDescription(const std::string& path) const
{
	std::stringstream command;
	command << "file -F '' \"" << path << "\" | sed s:\"" << path << "\"::";
	return exec(command.str().c_str());
}

void FileManager::printDirectoryContent(const int actualPosition)
{
	int actualPosY = DISPLAY_START_POS_Y;
	
	if(!directoryContent.size())
		return;

	//Count range of positions to display.
	int min = actualPosition - actualPosition%LINE_ON_PAGE;
	int max;
	if (min + LINE_ON_PAGE < directoryContent.size())
	{
		max = min + LINE_ON_PAGE;
	}
	else
	{
		max = directoryContent.size();
	}

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

			if (directoryContent[i].length() > DISPLAY_MAX_CHARS)
			{
				actualFirstCharIndex.store(0);
			}
			else
			{
				actualFirstCharIndex.store(-1);
			}
		
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

void FileManager::showFileInfo()
{
	LCD_OS::getLCDOperationSystem().OS_LCD_Clear(BACKGROUND);

	//Check is directory.
	const std::string temp_file = directoryContent[actualPosition];
	const std::string temp_file_path = getActualPath() + temp_file;
	const fs::path path(temp_file_path);
	std::error_code ec;
	const std::string size = getSizeOfFile(temp_file_path);
	const std::string description = getFileDescription(temp_file_path);

	LCD_OS::getLCDOperationSystem().OS_GUI_DisString_EN(DISPLAY_START_POS_X, DISPLAY_INC_Y, (std::string("Size: ") + size).c_str(), FONT, BACKGROUND, FILE_FONT_COLOR);

	//Check file is directory.
	if (fs::is_directory(path, ec))
	{
		const std::string number = getNumberOfFilesInDirectory(temp_file_path);
		LCD_OS::getLCDOperationSystem().OS_GUI_DisString_EN(DISPLAY_START_POS_X, DISPLAY_INC_Y * 2 + FONT_SIZE, (std::string("Files: ") + number).c_str(), FONT, BACKGROUND, FILE_FONT_COLOR);
		LCD_OS::getLCDOperationSystem().OS_GUI_DisString_EN(DISPLAY_START_POS_X, DISPLAY_INC_Y * 3 + 2 * FONT_SIZE, "Description:", FONT, BACKGROUND, FILE_FONT_COLOR);
		LCD_OS::getLCDOperationSystem().OS_GUI_DisString_EN(DISPLAY_START_POS_X, DISPLAY_INC_Y * 4 + 3 * FONT_SIZE, description.c_str(), FONT, BACKGROUND, FILE_FONT_COLOR);

	}
	else
	{
		LCD_OS::getLCDOperationSystem().OS_GUI_DisString_EN(DISPLAY_START_POS_X, DISPLAY_INC_Y * 2 + FONT_SIZE, "Description:", FONT, BACKGROUND, FILE_FONT_COLOR);
		LCD_OS::getLCDOperationSystem().OS_GUI_DisString_EN(DISPLAY_START_POS_X, DISPLAY_INC_Y * 3 + 2 * FONT_SIZE, description.c_str(), FONT, BACKGROUND, FILE_FONT_COLOR);
	}
	if (ec) // Optional handling of possible errors.
	{
		std::cerr << "Error in is_directory: " << ec.message();
	}
}

void FileManager::OnLeftKeyPressed()
{
	switch (content.load())
	{
	case INFO:
		//Do nothing.
		break;
	case VIEW:
		if (pathVector.empty())
			return;

		//Return to previous folder.
		pathVector.pop_back();
		actualPosition.store(0);
		wasChange.store(true);
		break;
	case SLEEP:
		//Wake up.
		wasChange.store(true);
		content.store(VIEW);
		break;
	}
}
void FileManager::OnLeftKeyReleased()
{

}

void FileManager::OnRightKeyPressed()
{
	switch (content.load())
	{
	case INFO:
		{
			//Do nothing.
			break;
		}
	case VIEW:
		{
			//Go to next folder.
			const std::string temp_file = directoryContent[actualPosition.load()];
			const std::string temp_file_path = getActualPath() + temp_file;
			const fs::path path(temp_file_path);
			std::error_code ec;
			//Check file is directory.
			if (fs::is_directory(path, ec))
			{
				pathVector.push_back(temp_file);
				actualPosition.store(0);
				wasChange.store(true);
				return;
			}
			if (ec) // Optional handling of possible errors.
			{
				std::cerr << "Error in is_directory: " << ec.message();
			}
			break;
		}
	case SLEEP:
		{
			//Wake up.
		wasChange.store(true);
		content.store(VIEW);
			break;
		}
	}
}

void FileManager::OnRightKeyReleased()
{

}

void FileManager::OnUpKeyPressed()
{
	switch (content.load())
	{
	case INFO:
		//Do nothing.
		break;
	case VIEW:
		if (actualPosition.load() != 0)
		{
			--actualPosition;
			wasChange.store(true);
		}
		break;
	case SLEEP:
		//Wake up.
		wasChange.store(true);
		content.store(VIEW);
		break;
	}
}
void FileManager::OnUpKeyReleased()
{

}

void FileManager::OnDownKeyPressed()
{
	switch (content.load())
	{
	case INFO:
		//Do nothing.
		break;
	case VIEW:
		if (actualPosition.load() < directoryContent.size() - 1)
		{
			++actualPosition;
			wasChange.store(true);
		}
		break;
	case SLEEP:
		//Wake up.
		wasChange.store(true);
		content.store(VIEW);
		break;
	}
}
void FileManager::OnDownKeyReleased()
{

}

void FileManager::OnPressKeyPressed()
{
	switch (content.load())
	{
	case INFO:
		//Do nothing.
		break;
	case VIEW:
		//Do nothing.
		break;
	case SLEEP:
		//Wake up.
		wasChange.store(true);
		content.store(VIEW);
		break;
	}
}
void FileManager::OnPressKeyReleased()
{

}

void FileManager::OnKey1Pressed()
{
	switch (content.load())
	{
	case INFO:
		//Do nothing.
		break;
	case VIEW:
		wasChange.store(true);
		content.store(INFO);
		break;
	case SLEEP:
		//Wake up.
		wasChange.store(true);
		content.store(VIEW);
		break;
	}
}
void FileManager::OnKey1Released()
{
	switch (content.load())
	{
	case INFO:
		wasChange.store(true);
		content.store(VIEW);
		break;
	case VIEW:
		//Do nothing.
		break;
	case SLEEP:
		//Wake up.
		wasChange.store(true);
		content.store(VIEW);
		break;
	}
}


void FileManager::OnKey2Pressed()
{
	switch (content.load())
	{
	case INFO:
		//Do nothing.
		break;
	case VIEW:
		//Do nothing.
		break;
	case SLEEP:
		//Wake up.
		wasChange.store(true);
		content.store(VIEW);
		break;
	}
}

void FileManager::OnKey2Released()
{

}

void FileManager::OnKey3Pressed()
{
	switch (content.load())
	{
	case INFO:
		//Do nothing.
		break;
	case VIEW:
		this->setPathVector(startPath);
		break;
	case SLEEP:
		//Wake up.
		wasChange.store(true);
		content.store(VIEW);
		break;
	}
}
void FileManager::OnKey3Released()
{

}

void FileManager::OnExit()
{

}

void FileManager::OnSleep()
{
	content.store(SLEEP);
}

void FileManager::operator()()
{
	/*Main loop of program*/
	while (true)
	{
		switch (content.load())
		{
			case VIEW:
				if (wasChange.load())
				{
					const int actualPosition = this->actualPosition.load();
					LCD_OS::getLCDOperationSystem().OS_LCD_Clear(BACKGROUND);
					//Update actual directory content.
					updateDirectoryContent(actualPosition);

					//Print values.
					printDirectoryContent(actualPosition);

					wasChange.store(false);
				}
				else if (!(actualFirstCharIndex.load() < 0))
				{
					updateActualChosenOption();
				}
				break;
			case INFO:
				if (wasChange.load())
				{
					showFileInfo();
					wasChange.store(false);
				}
				break;
			case SLEEP:
				//Do nothing.
				break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
