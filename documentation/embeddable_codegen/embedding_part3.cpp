/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010 by Joel Andersson, Moritz Diehl, K.U.Leuven. All rights reserved.
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <symbolic/casadi.hpp>
#include <interfaces/ipopt/ipopt_solver.hpp>
#include <symbolic/std_vector_tools.hpp>

using namespace CasADi;
using namespace std;
/**
 *  Solve an NLP using codegen  
 *  Part 2: solution
 *  Joel Andersson, K.U. Leuven 2013
 */

int main(){
    
  // Load the generated functions
  ExternalFunction nlp("./nlp.casadi");
  ExternalFunction grad_f("./grad_f.casadi");
  ExternalFunction jac_g("./jac_g.casadi");
  ExternalFunction hess_lag("./hess_lag.casadi");

  // Create an NLP solver passing derivative information
  IpoptSolver solver(nlp);
  solver.setOption("grad_f",grad_f);
  solver.setOption("jac_g",jac_g);
  solver.setOption("hess_lag",hess_lag);
  solver.init();

  // Set constraint bounds
  solver.setInput(0.,"lbg");

  // Solve the NLP
  solver.evaluate();

  // Print solution
  cout << "-----" << endl;
  cout << "objective at solution = " << solver.output("f") << endl;
  cout << "primal solution = " << solver.output("x") << endl;
  cout << "dual solution (x) = " << solver.output("lam_x") << endl;
  cout << "dual solution (g) = " << solver.output("lam_g") << endl;
  
  return 0;
}

