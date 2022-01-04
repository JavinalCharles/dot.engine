#pragma once

#include <stdexcept>

namespace dot
{

class ResourceNotFoundError : public std::runtime_error
{
public:
	ResourceNotFoundError(const std::string& what);
	ResourceNotFoundError(const char* what);
}; // class ResourceNotFoundError

}; // namespace dot