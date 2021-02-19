#ifndef BITFIELD_HPP
#define BITFIELD_HPP

#include <cstdint>

class Bitfield
{
  public:
    Bitfield();
    
    Bitfield(uint64_t num);

    virtual ~Bitfield(){}
    
    void set(const uint64_t num);
    
    void unset(const uint64_t num);
    
    int isSet(uint64_t num) const;
    
    void clear();
    
    void operator |= (const Bitfield &rhs);

    int operator == (const Bitfield &rhs) const;
    
    uint8_t getBitfieldSize() const;

  private:
    uint64_t data;
};

#endif /* BITFIELD_HPP */
