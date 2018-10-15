#pragma once

#include <functional>
#include <ostream>
#include <vector>

class SecondOrderSolver {
public:
  SecondOrderSolver(double x0, double v0, double dt,
                    const std::function<double(double)>& acceleration);

  void doStep();

  void printConfiguration(std::ostream &stream) const;

  int periods() const { return n_semi_periods_ / 2; }

  double averagePeriod() const;

  double maxAmplitudeShift() const;
  double maxPeriodShift() const;

private:
  const std::function<double(double)> acceleration_;

  double x_;
  double v_;
  const double dt_;

  double t_ = 0;

  // metadata.
  double old_v_;
  double n_semi_periods_ = 0.;
  std::vector<double> peak_x_;
  std::vector<double> peak_t_;
};
