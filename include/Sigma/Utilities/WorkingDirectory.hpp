#pragma once
#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace Sigma
{

class WorkingDirectory
{
public:
	WorkingDirectory();

	std::string get() const;
private:
	fs::path m_path;
}; // class WorkingDirectory
}; // namespace Sigma