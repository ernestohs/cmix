#ifndef PPM_H
#define PPM_H

#include "model.h"

#include <vector>
#include <array>

struct Table;

struct Entry {
  unsigned char count;
  unsigned char symbol;
  int link;
};

struct Table {
  Table() : entries(0, Entry()) {}
  std::vector<Entry> entries;
  int lower_table;
};

class PPM : public Model {
 public:
  PPM(unsigned int order, const unsigned int& bit_context,
      unsigned int max_size);
  float Predict();
  void Perceive(int bit);
  void ByteUpdate();

 private:
  int AddOrGetTable(int table_index, unsigned int depth, unsigned char byte);
  void UpdateTable(int table_index, unsigned int depth, unsigned char byte);
  void Reset();

  const unsigned int& byte_;
  std::vector<Table> tables_;
  unsigned int cur_;
  unsigned int cur_depth_;
  unsigned int max_order_;
  unsigned int max_size_;
  std::array<float, 256> probs_;
  int top_;
  int mid_;
  int bot_;
};

#endif