#pragma once

#include "dot/C/Component.hpp"

namespace dot
{
class InstanceID : public dot::Component
{
public:
	InstanceID(dot::Entity* owner);

	unsigned long long get() const;
private:
	static unsigned long long count;
	unsigned long long m_id;

}; // class InstanceID
}; // namespace dot