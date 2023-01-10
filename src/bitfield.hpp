/**
 * @file bitfield.hpp
 * @author Dan Feerst(feerstd@gmail.com)
 * @brief This class creates a 64-bit object with convienient
 * methods for performing bitwise operations.  This is far more
 * memory efficient then a boolean array, and in most cases it
 * will be significantly faster.
 * @version 0.1
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef BITFIELD_HPP
#define BITFIELD_HPP

#include <cstdint>

class Bitfield
{
public:
  /**
   * @brief Construct a new Bitfield object
   * initialized to 0x0
   *
   */
  Bitfield();

  /**
   * @brief Construct a new Bitfield object
   * initialized to num
   *
   * @param num
   */
  Bitfield(uint64_t num);

  /**
   * @brief Destroy the Bitfield object
   *
   */
  virtual ~Bitfield() = default;

  /**
   * @brief Set the specified bit [0 - 63]
   *
   * @param num
   */
  void set(const uint64_t num);

  /**
   * @brief Unset the specified bit [0 - 63]
   *
   * @param num
   */
  void unset(const uint64_t num);

  /**
   * @brief Returns the status of the specified bit
   *
   * @param num
   * @return int Returns 1 for set, 0 for unset, and -1 for range error.
   */
  int isSet(uint64_t num) const;

  /**
   * @brief Clear the bitfield
   *
   */
  void clear();

  /**
   * @brief Merges two bitfields
   *
   * @param rhs right bitfield
   */
  void operator|=(const Bitfield &rhs);

  /**
   * @brief Compare two bitfields
   *
   * @param rhs right bitfield
   * @return int Returns true if fields match
   */
  int operator==(const Bitfield &rhs) const;

  /**
   * @brief Get the Bitfield size
   *
   * @return uint8_t
   */
  uint8_t getBitfieldSize() const;

private:
  uint64_t data;
};

#endif /* BITFIELD_HPP */
