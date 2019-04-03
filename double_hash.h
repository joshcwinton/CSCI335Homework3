#ifndef DOUBLE_PROBING_H
#define DOUBLE_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include "primehelpers.h"

// Double probing implementation.
template <typename HashedObj>
class HashTableDouble {
public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableDouble(size_t size = 101) : array_(NextPrime(size))
    { MakeEmpty();;}

  bool Contains(const HashedObj & x) {
    return IsActive(FindPos(x));
  }

  void MakeEmpty() {
    current_size_ = 0;
    collisions_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos)){
      return false;
    }

    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();
    return true;
  }

  bool Insert(HashedObj && x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos)){
      return false;
    }
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }

  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    current_size_--;
    return true;
  }

  int getNumberofElements(){
    return current_size_;
  }

  int getTableSize(){
    return array_.size();
  }

  double getLoadFactor(){
    double load_factor = (double)current_size_/(array_.size());
    return load_factor;
  }

  int getCollisions(){
    return collisions_;
  }

  double getAverageCollisions(){
    double averageCollisions = (double)collisions_/current_size_;
    return averageCollisions;
  }

  int getProbes(){
    return probes_;
  }

 private:
  struct HashEntry {
    HashedObj element_;
    EntryType info_;

    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }

    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };


  std::vector<HashEntry> array_;
  int current_size_;
  int collisions_;
  int table_size_;
  int probes_;

  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x) {
    size_t current_pos = InternalHash(x);
    size_t offset = InternalHash2(x);
    probes_ = 1;

    while (array_[current_pos].info_ != EMPTY &&
       array_[current_pos].element_ != x) {
      probes_++;
      collisions_++;
      current_pos += offset;  // Compute ith probe.
      if (current_pos >= array_.size())
    current_pos -= array_.size();
    }
    return current_pos;
  }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrime(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;

    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
    Insert(std::move(entry.element_));
  }

  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );
  }

  size_t InternalHash2(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return 97 - (hf(x) % 97);
  }
};

#endif  // DOUBLE_PROBING_H
