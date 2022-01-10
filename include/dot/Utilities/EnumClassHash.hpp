#pragma once

namespace dot
{

class EnumClassHash
{
public:
	template <typename T>
	std::size_t operator()(T t) const
	{
		return static_cast<std::size_t>(t);
	}
}; // class EnumClassHash

}; // namespace dot