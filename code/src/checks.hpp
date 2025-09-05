#ifndef CHECKS_HPP
#define CHECKS_HPP

#include <optional>
#include <string>
#include <vector>

using std::string;
using std::vector;

typedef std::pair<int, int> range;
range make_range(int l, int r);

typedef std::optional<std::string> optstring;

constexpr size_t ASCII_SIZE = 1 << (8 * sizeof(char));

// May be inneficient if this search can be optimized in the case in which
// checking for many mcodes at the same time is more efficient than looking one
// by one, this is not the case if the complexity cannot be made less than
// O(m).
int is_substr(const string &seq, const string &sub);

range longest_palindromic_substr(const string &seq);

range longest_common_substr(const string &seq_a, const string &seq_b);

#endif // !CHECKS_HPP
