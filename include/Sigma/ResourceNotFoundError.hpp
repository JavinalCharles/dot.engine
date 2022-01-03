#pragma once

#include <stdexcept>

namespace Sigma
{

class ResourceNotFoundError : public std::runtime_error
{
public:
	ResourceNotFoundError(const std::string& what);
	ResourceNotFoundError(const char* what);
}; // class ResourceNotFoundError

}; // namespace Sigma