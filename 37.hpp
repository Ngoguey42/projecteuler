// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   37.hpp                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/11/16 17:01:41 by ngoguey           #+#    #+#             //
//   Updated: 2016/11/16 17:15:35 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef _37_HPP
# define _37_HPP

# include <vector>
# include <cstddef>
# include <unordered_set>

class Primes {

  const std::vector<bool> _sieve;
  static std::vector<bool> _sieve_of_max(size_t max);

public:
  ~Primes() = default;
  Primes() = delete;
  Primes(size_t max);
  Primes(Primes const &) = delete;
  Primes &operator =(Primes const &) = delete;

  bool is_prime(size_t p) const;
  size_t next(size_t i) const;

};

class Functor {

  const Primes _pr;

  size_t _digit_count, _min_value, _max_value;

  void _handle_prime(size_t p);

  std::unordered_set<size_t> _truncable_primes;

public:
  Functor();

  void operator()();


};

#endif
