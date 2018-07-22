#pragma once
#include <thread>

abstract class Program : public std::thread
{
private:
	std::string name;
	std::string icone_path;
public:
	Program(std::string name_s, std::path) : name(name_s), icone_path(path);
	inline std::string getName() { return this.name; }
	inline std::string getIcone() { return this.icone_path; }

	/*Thread function - pure virtual*/
	void operator()() = 0;
};