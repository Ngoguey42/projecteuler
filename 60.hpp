// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   60.hpp                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/11/15 16:23:19 by ngoguey           #+#    #+#             //
//   Updated: 2016/11/15 19:46:20 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef _60_HPP
# define _60_HPP

# include <vector>
# include <deque>
# include <unordered_map>

using primeint = unsigned int;

class Primes {

  static std::vector<bool> _sieve_of_max(primeint max);

  const std::vector<bool> _sieve;

public:
  ~Primes() = default;
  Primes() = delete;
  Primes(primeint max);
  Primes(Primes const &) = delete;
  Primes &operator =(Primes const &) = delete;

  bool is_prime(primeint p) const;
  primeint next(primeint p) const;

};

class Functor {

  static const primeint _min_value_of_digit_count[10];
  Primes _pr;
  std::size_t _num_digit, _prefix_size, _suffix_size;

  std::unordered_map<primeint, std::vector<primeint>> _prime_presuf;

  void _decompose_prime(primeint p);
  void _handle_prime_decomposition(primeint lhs, primeint rhs);
  void _register_a_with_b(primeint a, primeint b);

  std::pair<primeint, primeint> _cut_prime(primeint p);
  bool _rhs_has_leading_zero(primeint rhs);
  size_t _family_size(primeint a, primeint b);

  void _narrow_family(std::deque<primeint> &pretendings);

public:
  ~Functor() = default;
  Functor();
  Functor(Functor const &) = delete;
  Functor &operator =(Functor const &) = delete;

  void operator ()();

};

#endif
