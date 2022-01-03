#pragma once

#include "Sigma/C/Component.hpp"

namespace Sigma
{
class InstanceID : public Sigma::Component
{
public:
	InstanceID(Sigma::Entity* owner);

	unsigned long long get() const;
private:
	static unsigned long long count;
	unsigned long long m_id;

}; // class InstanceID
}; // namespace Sigma