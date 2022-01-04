#include "dot/ResourceNotFoundError.hpp"

using dot::ResourceNotFoundError;

ResourceNotFoundError::ResourceNotFoundError(const std::string& what)
	: std::runtime_error("Resource not found: " + what)
{

}

ResourceNotFoundError::ResourceNotFoundError(const char* what)
	: std::runtime_error(what)
{

}