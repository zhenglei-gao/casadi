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

#ifndef NULLSPACE_HPP
#define NULLSPACE_HPP

#include "function.hpp"

/** \defgroup Nullspace_doc
   
      Constructs a basis for the null-space of a fat matrix A.
      i.e. finds Z such that AZ = 0 holds.

      The nullspace is also known as the orthogonal complement of the rowspace of a matrix.
      
      It is assumed that the matrix A is of full rank.
      
      Implementations are not required to construct an orthogonal or orthonormal basis
    
*/

namespace CasADi{

  // Forward declaration of internal class
  class NullspaceInternal;

  /** \brief Base class for nullspace construction
  
      @copydoc Nullspace_doc
      \author Joris Gillis 
      \date 2014
  */

  class Nullspace : public Function{
  public:

    /// Default constructor 
    Nullspace();
  
    /// Access functions of the node.
    NullspaceInternal* operator->();

    /// Const access functions of the node.
    const NullspaceInternal* operator->() const;

    /// Check if the node is pointing to the right type of object
    virtual bool checkNode() const;
         
  };
  
} // namespace CasADi

#endif //NULLSPACE_HPP
