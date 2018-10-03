#include "analytic_period.hpp"

#include <cassert>
#include <cmath>
#include <unordered_map>

ulong factorial(int n);

double analyticPeriod(const double theta_0, const double g_over_l) {
//  constexpr int n_terms = 15;

  double result = 1, contrib;
  int n(1);
  do {
    contrib =
        std::pow(factorial(2 * n) / std::pow(std::pow(2, n) * factorial(n), 2),
                 2) *
        std::pow(std::sin(theta_0 / 2.), 2 * n);
    result += contrib;
    ++n;
  } while (std::abs(contrib) > 1e-8);

  return std::sqrt(g_over_l) * 2 * M_PI * result;
}

ulong factorial(const int n) {
  static std::unordered_map<int, int> cache;

  assert(n >= 0);
  if (n == 1 || n == 0)
    return 1;
  else if (cache.find(n) != cache.end())
    return cache[n];
  else
    return cache[n] = n * factorial(n - 1);
}
