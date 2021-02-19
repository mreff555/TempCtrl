#include "bitfield.hpp"

Bitfield::Bitfield() : data(0) {}

Bitfield::Bitfield(uint64_t num)
{
  set(num);
}

void Bitfield::set(const uint64_t num)
{
  if(num < (8 * sizeof(data)) && num > 0)
    this->data |= (0x1ULL << (num - 1));
}
    
void Bitfield::unset(const uint64_t num)
{
  if(num <= (8 * sizeof(data)) && num > 0)
    this->data &= ~(0x1ULL << (num - 1));
}
   
int Bitfield::isSet(uint64_t num) const
{
  if(num <= (8 * sizeof(data)) && num > 0)
    return (0x1 & ((uint64_t)data >> (num - 1)));
  else
    return -1;
}
    
void Bitfield::clear()
{
  this->data = 0;
}
    
void Bitfield::operator |= (const Bitfield &rhs)
{
  this->data |= rhs.data;
}

int Bitfield::operator == (const Bitfield &rhs) const
{
  return (this->data == rhs.data);
}

uint8_t Bitfield::getBitfieldSize() const
{
  return 8 * sizeof(data);
}
