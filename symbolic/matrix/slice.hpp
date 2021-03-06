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

#ifndef SLICE_HPP
#define SLICE_HPP

#include <vector>
#include "../casadi_exception.hpp"
#include "../printable_object.hpp"
#include <limits>
#include <iostream>

namespace CasADi{
  
  /** \brief Class representing a Slice
   *
   * Note that Python or Octave do not need to use this class.
   * They can just use slicing utility from the host language ( M[0:6]  in Python, M(1:7) )
   */
  class Slice : public PrintableObject{
  public:
    /// Defailt constructor - all elements
    Slice();
    
    /// A single element
    Slice(int i);
    
    /// A slice
    Slice(int start, int stop, int step=1);
    
    /// Construct from an index vector (requires isSlice(v) to be true)
    explicit Slice(const std::vector<int>& v);

    /// Construct nested slices from an index vector (requires isSlice2(v) to be true)
    explicit Slice(const std::vector<int>& v, Slice& outer);

    /// Check if an index vector can be represented more efficiently as a slice
    static bool isSlice(const std::vector<int>& v);

    /// Check if an index vector can be represented more efficiently as two nested slices
    static bool isSlice2(const std::vector<int>& v);

    /// Get a vector of indices
    std::vector<int> getAll(int len) const;

    /// Get a vector of indices (nested slice)
    std::vector<int> getAll(const Slice& outer, int len) const;

    /// Check equality
    bool operator==(const Slice& other) const{ return start_==other.start_ && stop_==other.stop_ && step_==other.step_;}

    /// Check inequality
    bool operator!=(const Slice& other) const{ return !(*this == other);}

#ifndef SWIG
    /// Print a representation of the object to a stream
    virtual void print(std::ostream& stream=std::cout) const;
#endif // SWIG

    /// start value: negative values will get added to length
    int start_;
    /// stop value: use std::numeric_limits<int>::max() to indicate unboundedness
    int stop_; 
    int step_;
  };
  
#ifndef SWIG
  static Slice ALL;
#endif // SWIG
  
  /// \cond INTERNAL
  /**  Class representing a non-regular (and thus non-slice) index list 
   */
  class IndexList{
  private:
    
  public:
    enum Type {NILL, INT, SLICE, IVECTOR};
    /// Constructor
    IndexList();
    explicit IndexList(int i);
    explicit IndexList(const std::vector<int> &i);
    explicit IndexList(const Slice &i);
    
    /// Get a vector of indices
    std::vector<int> getAll(int len) const;
    
    /// Data members (all public)
    Slice slice;
    int i;
    std::vector<int> iv;
    Type type;
  };
  /// \endcond
  
} // namespace CasADi


#ifdef SWIG
%template(Pair_Slice_Int) std::pair<CasADi::Slice,int>;
%template(Pair_Int_Slice) std::pair<int,CasADi::Slice>;
%template(Pair_Slice_Slice) std::pair<CasADi::Slice,CasADi::Slice>;
#endif // SWIG

#endif // SLICE_HPP

