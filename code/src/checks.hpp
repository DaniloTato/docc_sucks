#ifndef CHECKS_HPP
#define CHECKS_HPP

#include <cstddef>
#include <string>

using std::string;
typedef std::pair<size_t, size_t> range;

// May be inneficient if this search can be optimized in the case in which
// checking for many mcodes at the same time is more efficient than looking one
// by one, this is not the case if the complexity cannot be made less than
// O(m).
size_t substr(string seq, string sub);

range longest_palindrome_substr(string seq);

range longest_common_substr(string seq_a, string seq_b);

#endif // !CHECKS_HPP
