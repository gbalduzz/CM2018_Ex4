#include <cmath>
#include <fstream>
#include <iostream>

#include "analytic_period.hpp"
#include "json11.hpp"
#include "second_order_solver.hpp"

int main() {
  auto parameters = json11::Json::parseFile(SOURCE_DIR "/input.json");

  const double g_over_l = 1.;
  const int n_periods = 3;

  const double x0 = parameters["x0"].number_value() * M_PI;
  const double v0 = parameters["v0"].number_value();
  const double dt = parameters["dt"].number_value();

  SecondOrderSolver solver(x0, v0, g_over_l, dt);

  std::ofstream out("second_order_ODE_solution.txt");
  out << "# time \t theta \t theta_dot\n";
  solver.printConfiguration(out);

  const int steps_per_sample = parameters["steps per sample"].int_value();

  while (solver.periods() < n_periods) {
    for (int i = 0; i < steps_per_sample; ++i)
      solver.doStep();
    solver.printConfiguration(out);
  }
  out.close();

  std::cout << "Average period: " << solver.averagePeriod()
            << "\nAnalytic period: " << analyticPeriod(x0, g_over_l)
            << "\nAmplitude shift: " << solver.maxAmplitudeShift()
            << "\nPeriod shift: " << solver.maxPeriodShift() << "\n"
            << std::endl;
}
