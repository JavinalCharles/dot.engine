#include "dot/C/InstanceID.hpp"

using dot::InstanceID;
using dot::Component;

unsigned long long dot::InstanceID::count = 0u;

InstanceID::InstanceID(dot::Entity* owner)
	: Component(owner),
	m_id(++count)
{

}


unsigned long long InstanceID::get() const
{
	return m_id;
}