#pragma once
#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace dot
{

class WorkingDirectory
{
public:
	WorkingDirectory();

	std::string get() const;
private:
	fs::path m_path;
}; // class WorkingDirectory
}; // namespace dot