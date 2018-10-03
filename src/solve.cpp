#include <cmath>
#include <fstream>
#include <iostream>

#include "second_order_solver.hpp"

int main() {
  const double x0 = 3. / 4. * M_PI;
  const double v0 = 0;
  const double g_over_l = 1.;
  const int n_periods = 3;

  SecondOrderSolver solver(x0, v0, g_over_l, 1e-6);

  std::ofstream out("second_order_ODE_solution.txt");
  out << "# time \t theta \t theta_dot\n";
  solver.printConfiguration(out);

  while (solver.periods() < n_periods) {
    for (int i = 0; i < 100; ++i)
      solver.doStep();
    solver.printConfiguration(out);
  }
  out.close();

  std::cout << "Average period: " << solver.get_average_period()
            << "\nAmplitude shift: " << solver.get_amplitude_shift() << std::endl;
}
