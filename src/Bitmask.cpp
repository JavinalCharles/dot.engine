#include "Sigma/Utilities/Bitmask.hpp"

using Sigma::Bitmask;

Bitmask::Bitmask()
	: m_bits(0)
{

}

Bitmask::Bitmask(uint64_t bits)
	: m_bits(bits)
{

}

void Bitmask::setMask(const Bitmask& other)
{
	this->m_bits = other.m_bits;
}

uint64_t Bitmask::getMask() const
{
	return m_bits;
}

bool Bitmask::getBit(int pos) const
{
	return (m_bits & (1 << pos)) != 0;
}

void Bitmask::setBit(int pos, bool on)
{
	if (on)
	{
		setBit(pos);
	}
	else
	{
		clearBit(pos);
	}
}

void Bitmask::setBit(int pos)
{
	m_bits = m_bits | (1 << pos);
}

void Bitmask::clearBit(int pos)
{
	m_bits = m_bits & ~(1 << pos);
}

void Bitmask::clear()
{
	m_bits = 0;
}