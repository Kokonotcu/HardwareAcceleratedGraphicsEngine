#include "WindException.h"
#include <sstream>

WndException::WndException(int line=0, const char* file="") noexcept
	:
	line(line),file(file)
{
}

const char* WndException::what() const noexcept
{
	std::stringstream ss;
	ss << GetType()<< std::endl
		<<GetOriginString();
	whatBuffer = ss.str();
	return whatBuffer.c_str();
}

const char* WndException::GetType() const noexcept
{
	return "Wnd Standart Exception";
}

int WndException::GetLine() const noexcept
{
	return line;
}

const std::string& WndException::GetFile() const noexcept
{
	return file;
}

std::string WndException::GetOriginString() const noexcept
{
	std::stringstream ss;
	ss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return ss.str();
}
