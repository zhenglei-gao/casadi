#
#     This file is part of CasADi.
# 
#     CasADi -- A symbolic framework for dynamic optimization.
#     Copyright (C) 2010 by Joel Andersson, Moritz Diehl, K.U.Leuven. All rights reserved.
# 
#     CasADi is free software; you can redistribute it and/or
#     modify it under the terms of the GNU Lesser General Public
#     License as published by the Free Software Foundation; either
#     version 3 of the License, or (at your option) any later version.
# 
#     CasADi is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#     Lesser General Public License for more details.
# 
#     You should have received a copy of the GNU Lesser General Public
#     License along with CasADi; if not, write to the Free Software
#     Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
# 
# 
# -*- coding: utf-8 -*-
from casadi import *

# Declare variables
x = SX.sym("x",2)

# Form the NLP
nlp = SXFunction([x,[]],[
        x[0]**2 + x[1]**2, # objective
        x[0]+x[1]-10      # constraint
      ])


# Pick an NLP solver
MySolver = IpoptSolver
#MySolver = WorhpSolver
#MySolver = SQPMethod

# Allocate a solver
solver = MySolver(nlp)
if MySolver==SQPMethod:
  solver.setOption("qp_solver",QPOasesSolver)
  solver.setOption("qp_solver_options",{"printLevel":"none"})
solver.init()

# Set constraint bounds
solver.setInput(0.,"lbg")

# Solve the NLP
solver.evaluate()

# Print solution
print "-----"
print "objective at solution = ", solver.getOutput("f")
print "primal solution = ", solver.getOutput("x")
print "dual solution (x) = ", solver.getOutput("lam_x")
print "dual solution (g) = ", solver.getOutput("lam_g")
