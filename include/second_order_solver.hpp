#pragma once

#include <ostream>

class SecondOrderSolver {
public:
  SecondOrderSolver(double x0, double v0, double g_over_l, double dt);

  void doStep();

  void printConfiguration(std::ostream &stream) const;

  int periods() const { return n_semi_periods_ / 2; }

private:
  double x_;
  double v_;
  const double g_over_l_;
  const double dt_;

  double t_;
  double old_v_;
  int n_semi_periods_;
};
