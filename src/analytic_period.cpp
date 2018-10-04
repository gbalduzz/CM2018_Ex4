#include "analytic_period.hpp"

#include <cassert>
#include <cmath>
#include <unordered_map>

// Returns the factorial as a floating point number to better deal with large
// values.
double factorial(int n);

double analyticPeriod(const double theta_0, const double g_over_l) {

  double result = 1, contrib;
  int n(1);
  do {
    contrib =
        std::pow(factorial(2 * n) / std::pow(std::pow(2, n) * factorial(n), 2),
                 2) *
        std::pow(std::sin(theta_0 / 2.), 2 * n);
    // Check for nan.
    if (contrib != contrib)
      break;
    result += contrib;
    ++n;
  } while (std::abs(contrib) > 1e-8);

  return std::sqrt(g_over_l) * 2 * M_PI * result;
}

double factorial(const int n) {
  static std::unordered_map<int, double> cache;

  assert(n >= 0);
  if (n == 1. || n == 0.)
    return 1.;
  else if (cache.find(n) != cache.end())
    return cache[n];
  else
    return cache[n] = n * factorial(n - 1);
}
