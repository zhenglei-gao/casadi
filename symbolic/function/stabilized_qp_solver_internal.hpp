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

#ifndef STABILIZED_QP_INTERNAL_HPP
#define STABILIZED_QP_INTERNAL_HPP

#include "stabilized_qp_solver.hpp"
#include "function_internal.hpp"


/// \cond INTERNAL
namespace CasADi{

/// Internal class
class StabilizedQPSolverInternal : public FunctionInternal{
  public:

    // Constructor
    StabilizedQPSolverInternal(const std::vector<Sparsity> &st);
    
    // Destructor
    virtual ~StabilizedQPSolverInternal() = 0;
    
    // Initialize
    virtual void init();
    
    // Solve the system of equations
    virtual void evaluate();
    
    // Solve the system of equations
    virtual void solve();
    
    /// Set options that make the QP solver more suitable for solving LPs
    virtual void setLPOptions() { };
    
    /// \brief Check if the numerical values of the supplied bounds make sense
    virtual void checkInputs() const;
    
    /** Generate native code in the interfaced language for debugging */
    virtual void generateNativeCode(std::ostream& file) const {};
    
  protected:

    /// Problem structure
    std::vector<Sparsity> st_;
    
    /// Number of decision variables
    int n_;
    
    /// The number of constraints (counting both equality and inequality) == A.size1()
    int nc_; 
};


} // namespace CasADi


/// \endcond
#endif //STABILIZED_QP_INTERNAL_HPP

