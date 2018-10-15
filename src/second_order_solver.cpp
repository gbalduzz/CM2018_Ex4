#include "second_order_solver.hpp"

#include <cmath>

SecondOrderSolver::SecondOrderSolver(
    double x0, double v0, double dt,
    const std::function<double(double)>& acceleration)
    : acceleration_(acceleration), x_(x0), v_(v0), dt_(dt) {
  if (v0 == 0) {
    peak_x_.push_back(x_);
    peak_t_.push_back(t_);
  }
  // Start the velocity at 0.5 * dt.
  v_ += 0.5 * dt * acceleration_(x_);
}

void SecondOrderSolver::doStep() {
  old_v_ = v_;

  // use leapfrog algorithm.
  x_ += v_ * dt_;
  v_ += dt_ * acceleration_(x_);

  t_ += dt_;

  if (v_ * old_v_ < 0) {
    ++n_semi_periods_;
    peak_x_.push_back(x_);
    peak_t_.push_back(t_);
  }
}

void SecondOrderSolver::printConfiguration(std::ostream &stream) const {
  // Synchronize v:
  const double v_step = v_ - 0.5 * dt_ * acceleration_(x_);
  stream << t_ << "\t" << x_ << "\t" << v_step << "\n";
}

double SecondOrderSolver::averagePeriod() const {
  return 2 * (peak_t_.back() - peak_t_.front()) / (peak_t_.size() - 1);
}

namespace {
double computeMaxShift(const std::vector<double> &v) {
  double shift = 0;
  for (int i = 0; i < v.size(); ++i)
    for (int j = i; j < v.size(); ++j)
      shift = std::max(shift, std::abs(std::abs(v[i]) - std::abs(v[j])));
  return shift;
}
}

double SecondOrderSolver::maxAmplitudeShift() const {
  return computeMaxShift(peak_x_);
}

double SecondOrderSolver::maxPeriodShift() const {
  std::vector<double> delta_t(peak_t_.size() - 1);
  for (int i = 0; i < delta_t.size(); ++i)
    delta_t[i] = peak_t_[i + 1] - peak_t_[i];

  return computeMaxShift(delta_t) * 2.;
}
