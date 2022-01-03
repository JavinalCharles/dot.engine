#include "Sigma/C/InstanceID.hpp"

using Sigma::InstanceID;
using Sigma::Component;

unsigned long long Sigma::InstanceID::count = 0u;

InstanceID::InstanceID(Sigma::Entity* owner)
	: Component(owner),
	m_id(++count)
{

}


unsigned long long InstanceID::get() const
{
	return m_id;
}