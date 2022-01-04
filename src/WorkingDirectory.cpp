#include "dot/Utilities/WorkingDirectory.hpp"

namespace fs = std::experimental::filesystem;
using dot::WorkingDirectory;

WorkingDirectory::WorkingDirectory()
	: m_path(fs::current_path())
{

}

std::string WorkingDirectory::get() const
{
	return m_path.string();
}