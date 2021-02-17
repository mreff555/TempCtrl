#ifndef BITFIELD_HPP
#define BITFIELD_HPP

#include <cstdint>

class Bitfield
{
  public:
    Bitfield() : data(0) {}

    virtual ~Bitfield(){}
    
    void set(const uint64_t num);
    
    void unset(const uint64_t num);
    
    int isSet(uint64_t num) const;
    
    void clear();
    
    void operator |= (const Bitfield &rhs);

    uint8_t getBitfieldSize() const;

  private:
    uint64_t data;
};

#endif /* BITFIELD_HPP */
