#pragma once

#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <utility>
#include <memory>

class Logger
{
public:
	explicit Logger(const std::string& title, const std::string& filename, bool verbose = true);
	explicit Logger(const std::string& title);
	~Logger();
	template<typename T>
	Logger& operator<<(const T &message);
	void set(bool active);
	
private:
	void writeHead(std::ostream& stream, bool colored, bool dated);

	std::ofstream file;
	std::string title;
	unsigned color;
	bool verbose;
	bool enabled;
};

#include "Logger.inl"
