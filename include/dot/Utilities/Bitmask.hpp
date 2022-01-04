#pragma once

#include <cstdint>

namespace dot
{
class Bitmask
{
public:
	Bitmask();
	Bitmask(uint64_t bits);

	/**
	 * Bitmask::setMask(other)
	 * - Overrides the currently stored bitmask
	 * */
	void setMask(const Bitmask& other);

	/**
	 * Bitmask::getMask()
	 * - Returns a binary representation of bitmask
	 * */
	uint64_t getMask() const;

	/**
	 * Bitmask::getBit()
	 * - returns true if bit at pos = 1, else false
	 * */
	bool getBit(int pos) const;

	/**
	 * Bitmask::setBit(pos, on)
	 * - Sets bit at specified pos to 1 or 0.
	 * */
	void setBit(int pos, bool on);

	/**
	 * Bitmask::setBit(pos)
	 * - Sets bit at pos to 1
	 * */
	void setBit(int pos);

	/**
	 * Bitmask::clearBit(pos)
	 * - Sets bit at pos to 0
	 * */
	void clearBit(int pos);

	/**
	 * Bitmas::clear()
	 * - Sets all bits to 0
	 * */
	void clear();
private:
	uint64_t m_bits;

}; // class Bitmask

}; // namespace dot