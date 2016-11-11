
#include <unordered_set>
#include <iostream>
#include <vector>
#include <cassert>
#include <functional>

using nbr_t = std::vector<int>;

size_t num_bytes = 0;

class Term {

  static size_t _create_hash(nbr_t const &nbr) {
    size_t h;

    h = 0;
    for (int i: nbr)
      h ^= std::hash<int>{}(i);
    return h;
  }

public:
  const nbr_t nbr;
  size_t _hash;

  ~Term() = default;
  Term() = delete;
  Term(Term const &) = default;
  Term &operator =(Term const &) = default;

  Term(nbr_t const &nbr)
    : nbr(nbr)
    , _hash(_create_hash(this->nbr)) {
    num_bytes += this->nbr.capacity() * sizeof(int);
  }

  struct Hash {
    size_t operator()(Term const &t) const {
      return t._hash;
    }
  };

  bool operator ==(Term const &t) const {
    return this->nbr == t.nbr;
  }

};

void multiply(nbr_t &nbr, int factor) {
  int carry;

  carry = 0;
  for (int &digit: nbr) {
    carry += digit * factor;
    digit = carry % 10;
    carry /= 10;
  }
  while (carry != 0) {
    nbr.push_back(carry % 10);
    carry /= 10;
  }
  return ;
}

int main() {
  std::unordered_set<Term, Term::Hash> terms;
  nbr_t nbr;

  nbr.reserve(201);
  for (int a = 2; a <= 100; a++) {
    nbr.clear();
    nbr.push_back(a);
    for (int b = 2; b <= 100; b++) {
      multiply(nbr, a);
      terms.emplace(nbr);
    }
  }
  std::cout << terms.size() << std::endl;
  std::cout << nbr.capacity() << std::endl;
  std::cout << num_bytes << std::endl;
  return 0;
}
