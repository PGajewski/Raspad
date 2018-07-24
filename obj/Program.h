#pragma once
#include <thread>

class Program : public std::thread
{
private:
	std::string name;
	std::string icone_path;
public:
	Program(std::string name_s, std::string path) : name(name_s), icone_path(path) {}
	inline std::string getName() { return this->name; }
	inline std::string getIcone() { return this->icone_path; }

	/*Functions to handle signals from operational system*/
	virtual void OnLeftKeyPresseed() = 0;
	virtual void OnLeftKeyReleased() = 0;

	virtual void OnRightKeyPressed() = 0;
	virtual void OnRightKeyReleased() = 0;

	virtual void OnUpKeyPressed() = 0;
	virtual void OnUpKeyReleased() = 0;

	virtual void OnDownKeyPressed() = 0;
	virtual void OnDownKeyReleased() = 0;

	virtual void OnPressKeyPressed() = 0;
	virtual void OnPressKeyReleased() = 0;

	virtual void OnKey1Pressed() = 0;
	virtual void OnKey1Released() = 0;

	virtual void OnKey2Pressed() = 0;
	virtual void OnKey2Released() = 0;

	virtual void OnKey3Pressed() = 0;
	virtual void OnKey3Released() = 0;

	virtual void OnExit() = 0;

	/*Thread function - pure virtual*/
	virtual void operator()() = 0;
};