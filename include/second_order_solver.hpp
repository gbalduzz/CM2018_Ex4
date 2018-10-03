#pragma once

#include <ostream>
#include <vector>

class SecondOrderSolver {
public:
  SecondOrderSolver(double x0, double v0, double g_over_l, double dt);

  void doStep();

  void printConfiguration(std::ostream &stream) const;

  int periods() const { return n_semi_periods_ / 2; }

  double get_average_period() const { return period_; }

  double get_amplitude_shift() const{ return std::abs(peak_x_[0]) - std::abs(peak_x_.back());}

private:
  double x_;
  double v_;
  const double g_over_l_;
  const double dt_;

  double t_;

  // metadata.
  double old_v_;
  double n_semi_periods_ = 0.;
  double period_ = 0;
  std::vector<double> peak_x_;
};
