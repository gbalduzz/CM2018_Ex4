#include "second_order_solver.hpp"

#include <cmath>

SecondOrderSolver::SecondOrderSolver(double x0, double v0, double g_over_l,
                                     double dt)
    : x_(x0), v_(v0), g_over_l_(g_over_l), dt_(dt), t_(0), n_semi_periods_(0) {}

void SecondOrderSolver::doStep() {
  old_v_ = v_;

  // take g/l = 1.
  const double a = -std::sin(x_);
  v_ += a * dt_;
  x_ += v_ * dt_;
  t_ += dt_;

  if (v_ * old_v_ < 0)
    ++n_semi_periods_;
}

void SecondOrderSolver::printConfiguration(std::ostream &stream) const {
  stream << t_ << "\t" << x_ << "\t" << v_ << "\n";
}
