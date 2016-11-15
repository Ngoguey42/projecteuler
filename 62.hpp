// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   62.hpp                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/11/15 21:47:25 by ngoguey           #+#    #+#             //
//   Updated: 2016/11/15 23:06:36 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef _62_HPP
# define _62_HPP

# include <vector>
# include <deque>
# include <unordered_set>
# include <unordered_map>

class Functor {

  using digit_vec = std::vector<uint8_t>;

  size_t _digit_count;
  std::unordered_map<size_t, std::deque<size_t>> _cubes_grouped;
  bool _found;

  digit_vec _digits;

  size_t _cube(int n);
  void _handle_digit_count();
  void _handle_cube(size_t cube);
  void _dump_cube_permutations(size_t cube);

  void _make_ordered_digit_vector_of_cube(size_t cube);
  size_t _number_of_digit_vector();

public:
  void operator ()();

};

#endif
