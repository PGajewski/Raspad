#pragma once
#include <thread>
#include <atomic>
#include <chrono>

class Program
{
protected:
	std::string name;
	std::string icone_path;
public:
	Program(std::string name_s, std::string path) : name(name_s), icone_path(path) {}
	inline std::string getName() { return this->name; }
	inline std::string getIcone() { return this->icone_path; }

	std::atomic_bool running{ true };

	/*Functions to handle signals from operational system*/
	virtual void OnLeftKeyPressed();
	virtual void OnLeftKeyReleased();

	virtual void OnRightKeyPressed();
	virtual void OnRightKeyReleased();

	virtual void OnUpKeyPressed();
	virtual void OnUpKeyReleased();

	virtual void OnDownKeyPressed();
	virtual void OnDownKeyReleased();

	virtual void OnPressKeyPressed();
	virtual void OnPressKeyReleased();

	virtual void OnKey1Pressed();
	virtual void OnKey1Released();

	virtual void OnKey2Pressed();
	virtual void OnKey2Released();

	virtual void OnKey3Pressed();
	virtual void OnKey3Released();

	virtual void OnExit();

	/*Thread function - pure virtual*/
	virtual void operator()();
};
