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

#ifndef STD_VECTOR_TOOLS_HPP
#define STD_VECTOR_TOOLS_HPP


#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <limits>
#include <algorithm>
#include <map>
#include "casadi_exception.hpp"
#include "casadi_types.hpp"

/** \brief Convenience tools for C++ Standard Library vectors
    \author Joel Andersson 
    \date 2010-2011
*/

namespace std{

#ifndef SWIG
  /// Enables flushing an std::vector to a stream (prints representation)
  template<typename T>
  ostream& operator<<(ostream &stream, const vector<T> &v);
  
  /// Enables flushing an std::pair to a stream (prints representation)
  template<typename T1, typename T2>
  ostream& operator<<(ostream &stream, const pair<T1,T2> &p);
  
  /// Enables flushing an std::map to a stream (prints representation)
  template<typename T1, typename T2>
  ostream& operator<<(ostream &stream, const std::map<T1,T2> &p);
  
#endif //SWIG
  
} // namespace std

namespace CasADi{

  #ifndef SWIG
  /** Range function
  * \param start
  * \param stop
  * \param step
  * \param len
  *
  * Consider a infinitely long list [start, start+step, start+2*step, ...]
  * Elements larger than or equal to stop are chopped off.
  *
  */
  std::vector<int> range(int start, int stop, int step=1, int len=std::numeric_limits<int>::max());

  /** Range function
  * \param stop
  *
  * \return list [0,1,2...stop-1]
  */
  std::vector<int> range(int stop);
  
  /// Print representation
  template<typename T>
  void repr(const std::vector<T> &v, std::ostream &stream=std::cout);
  
  /// Print description
  template<typename T>
  void print(const std::vector<T> &v, std::ostream &stream=std::cout);
  #endif // SWIG
  
  /// Check if for each element of v holds: v_i < upper
  template<typename T>
  bool inBounds(const std::vector<T> &v, int upper);
  
  /// Check if for each element of v holds: lower <= v_i < upper
  template<typename T>
  bool inBounds(const std::vector<T> &v, int lower, int upper);
  
  /** \brief Returns the list of all i in [0,size[ not found in supplied list
  * 
  * The supplied vector may contain duplicates and may be non-monotonous
  * The supplied vector will be checked for bounds
  * The result vector is guaranteed to be monotonously increasing
  */
  std::vector<int> complement(const std::vector<int> &v, int size);
  
  /** \brief Returns a vector for quickly looking up entries of supplied list
  *
  *  lookupvector[i]!=-1     <=>  v contains i
  *  v[lookupvector[i]] == i <=>  v contains i
  *
  *  Duplicates are treated by looking up last occurence
  */
  std::vector<int> lookupvector(const std::vector<int> &v, int size);
    
    
  /// \cond INTERNAL
  #ifndef SWIG
  /**
  Apply a function f to each element in a vector
  */
  template<class T>
  std::vector<T> applymap(T (*f)(const T& ),const std::vector<T>&);

  /**
  Apply a function f to each element in a vector
  */
  template<class T>
  void applymap(void (*f)(T&), std::vector<T>&);
  #endif // SWIG
  /// \endcond
  
  
  /// Check if the vector is strictly increasing
  template<typename T>
  bool isIncreasing(const std::vector<T> &v);
  
  /// Check if the vector is strictly decreasing
  template<typename T>
  bool isDecreasing(const std::vector<T> &v);
  
  /// Check if the vector is non-increasing
  template<typename T>
  bool isNonIncreasing(const std::vector<T> &v);
  
  /// Check if the vector is non-decreasing
  template<typename T>
  bool isNonDecreasing(const std::vector<T> &v);
  
  /// Check if the vector is monotone
  template<typename T>
  bool isMonotone(const std::vector<T> &v);

  /// Check if the vector is strictly monotone
  template<typename T>
  bool isStrictlyMonotone(const std::vector<T> &v);
  
#ifndef SWIG
  /// Print representation to string
  template<typename T>
  std::string getRepresentation(const std::vector<T> &v);
  
  /// Print description to string
  template<typename T>
  std::string getDescription(const std::vector<T> &v);
#endif //SWIG
  
  /// Print vector, matlab style
  template<typename T>
  void write_matlab(std::ostream &stream, const std::vector<T> &v);
  
  /// Print matrix, matlab style
  template<typename T>
  void write_matlab(std::ostream &stream, const std::vector<std::vector<T> > &v);

  /// Read vector, matlab style
  template<typename T>
  void read_matlab(std::istream &stream, std::vector<T> &v);

  /// Read matrix, matlab style
  template<typename T>
  void read_matlab(std::ifstream &file, std::vector<std::vector<T> > &v);

  #ifndef SWIG
  /// Matlab's linspace
  template<typename T, typename F, typename L>
  void linspace(std::vector<T> &v, const F& first, const L& last);

  /// \cond INTERNAL
  /// Get an pointer of sets of booleans from a double vector
  bvec_t* get_bvec_t(std::vector<double>& v);

  /// Get an pointer of sets of booleans from a double vector
  const bvec_t* get_bvec_t(const std::vector<double>& v);
  
  /// Get an pointer of sets of booleans from a double vector
  template<typename T>
  bvec_t* get_bvec_t(std::vector<T>& v){
    casadi_assert_message(0,"get_bvec_t only supported for double");
  }

  /// Get an pointer of sets of booleans from a double vector
  template<typename T>
  const bvec_t* get_bvec_t(const std::vector<T>& v){
    casadi_assert_message(0,"get_bvec_t only supported for double");
  }
  
  /// Get a pointer to the data contained in the vector
  template<typename T>
  T* getPtr(std::vector<T> &v);
  
  /// Get a pointer to the data contained in the vector
  template<typename T>
  const T* getPtr(const std::vector<T> &v);
  
  /// \endcond
  
  /** \brief Sort the data in a vector
  * 
  * \param[in]  values the vector that needs sorting
  * \param[out] sorted_values the sorted vector
  * \param[out] indices The indices such that 'sorted_values= values[indices]'
  * \param[in] invert_indices Output indices such that 'sorted_values[indices=values'
  **/
  template<typename T>
  void sort(const std::vector<T> &values,std::vector<T> &sorted_values,std::vector<int> &indices,bool invert_indices =false);
  #endif //SWIG
  
  /** \brief Make a vector of a certain length with its entries specified
  *  Usage C++: 
  *     makeVector<ClassName>(LENGTH, ENTRY_INDEX_1, ENTRY_VALUE_1, ENTRY_INDEX_2, ENTRY_VALUE_2, ...)
  *  Usage Python: 
  *     makeVector(ClassName,(LENGTH, ENTRY_INDEX_1, ENTRY_VALUE_1, ENTRY_INDEX_2, ENTRY_VALUE_2 ...)
  */
  #ifndef SWIG
  template<typename T>
  std::vector<T> makeVector(int size, 
                            int ind0=-1, const T& val0=T(),
                            int ind1=-1, const T& val1=T(),
                            int ind2=-1, const T& val2=T(),
                            int ind3=-1, const T& val3=T(),
                            int ind4=-1, const T& val4=T(),
                            int ind5=-1, const T& val5=T(),
                            int ind6=-1, const T& val6=T(),
                            int ind7=-1, const T& val7=T(),
                            int ind8=-1, const T& val8=T(),
                            int ind9=-1, const T& val9=T(),
                            int ind10=-1, const T& val10=T(),
                            int ind11=-1, const T& val11=T(),
                            int ind12=-1, const T& val12=T(),
                            int ind13=-1, const T& val13=T(),
                            int ind14=-1, const T& val14=T(),
                            int ind15=-1, const T& val15=T(),
                            int ind16=-1, const T& val16=T(),
                            int ind17=-1, const T& val17=T(),
                            int ind18=-1, const T& val18=T(),
                            int ind19=-1, const T& val19=T());
  #else // SWIG
  #ifdef SWIGPYTHON
%pythoncode %{
   def makeVector(T,size,*elems):
      assert len(elems) % 2 == 0, "The number of provided indices does not the number of provided values"
      num_elem = len(elems)/2
      ret = [T()]*size
      for i in range(num_elem):
        ind = elems[2*i]
        val = elems[2*i+1]
        ret[ind] = val
      return ret
%}
  #endif // SWIGPYTHON
  #endif // SWIG

#ifndef SWIG
  // Create a vector of length 1
  template<typename T>
  std::vector<T> toVector(const T& v0){ 
    return std::vector<T>(1,v0);
  }

  // Create a vector of length 2
  template<typename T>
  std::vector<T> toVector(const T& v0, const T& v1){ 
    std::vector<T> ret(2);
    ret[0] = v0;
    ret[1] = v1;
    return ret;
  }

  // Create a vector of length 3
  template<typename T>
  std::vector<T> toVector(const T& v0, const T& v1, const T& v2){ 
    std::vector<T> ret(3);
    ret[0] = v0;
    ret[1] = v1;
    ret[2] = v2;
    return ret;
  }
#endif // SWIG

  
  /// Checks if vector does not contain NaN or Inf
  template<typename T>
  bool isRegular(const std::vector<T> &v);
  
} // namespace CasADi

// Implementations
#ifndef SWIG
namespace std{

  /// Enables flushing an std::vector to a stream (prints representation)
  template<typename T>
  ostream& operator<<(ostream &stream, const vector<T> &v){
    CasADi::repr(v,stream);
    return stream;
  }
  
  template<typename T1, typename T2>
  ostream& operator<<(ostream &stream, const pair<T1,T2> &p){
    stream << "(" << p.first << "," << p.second << ")";
    return stream;
  }
  
  template<typename T1, typename T2>
  ostream& operator<<(ostream &stream, const std::map<T1,T2> &p){
    stream << "{";
    typedef typename std::map<T1,T2>::const_iterator it_type;
    int count = 0;
    for (it_type it = p.begin();it!=p.end();++it) {
      stream << it->first << ": " << it->second;
      if (count++ < p.size()-1) stream << ", ";
    }
    stream << "}";
    return stream;
  }
  
  template<typename T2>
  ostream& operator<<(ostream &stream, const std::map<std::string,T2> &p){
    stream << "{";
    typedef typename std::map<std::string,T2>::const_iterator it_type;
    int count = 0;
    for (it_type it = p.begin();it!=p.end();++it) {
      stream << '"' << it->first << '"' << ": " << it->second;
      if (count++ < p.size()-1) stream << ", ";
    }
    stream << "}";
    return stream;
  }
  
} // namespace std

namespace CasADi{
  
  template<typename T>
  void repr(const std::vector<T> &v, std::ostream &stream){
    if(v.empty()){
      stream << "[]";
    } else {
      // Print elements, python style
      stream << "[";
      stream << v.front();
      for(unsigned int i=1; i<v.size(); ++i)
        stream << "," << v[i];
      stream << "]";
    }
  }
  
  template<typename T>
  void print(const std::vector<T> &v, std::ostream &stream){
    // print vector style
    stream << "[" << v.size() << "]"; // Print dimension

    if(v.empty()){
      stream << "()";
    } else {
      // Print elements, ublas stype
      stream << "(";
      for(unsigned int i=0; i<v.size()-1; ++i)
        stream << v[i] << ",";
      if(!v.empty()) stream << v.back();
      stream << ")";
    }
  }
  
  #ifndef SWIG
  template<class T>
  std::vector<T> applymap(T (*f)(const T&) ,const std::vector<T>& comp) {
    std::vector<T> ret(comp.size());
    std::transform(comp.begin(),comp.end(),ret.begin(),f);
    return ret;
  }

  template<class T>
  void applymap(void (*f)(T &), std::vector<T>& comp) {
    std::for_each(comp.begin(),comp.end(),f);
  }
  #endif //SWIG
  
  template<typename T>
  bool inBounds(const std::vector<T> &v, int upper) {
    return inBounds(v,0,upper);
  }

  template<typename T>
  bool inBounds(const std::vector<T> &v, int lower, int upper) {
    if (v.size()==0) return true;
    int max = *std::max_element(v.begin(),v.end());
    if (max >= upper) return false;
    int min = *std::min_element(v.begin(),v.end());
    return (min >= lower);
  }

  template<typename T>
  bool isIncreasing(const std::vector<T> &v) {
    if (v.size()==0) return true;
    T el = v[0];
    for (int i=1;i<v.size();++i) {
      if (!(v[i] > el)) return false;
      el = v[i];
    }
    return el==el; // nan -> false
  }
  
  template<typename T>
  bool isDecreasing(const std::vector<T> &v) {
    if (v.size()==0) return true;
    T el = v[0];
    for (int i=1;i<v.size();++i) {
      if (!(v[i] < el)) return false;
      el = v[i];
    }
    return el==el; // nan -> false
  }
  
  template<typename T>
  bool isNonIncreasing(const std::vector<T> &v) {
    if (v.size()==0) return true;
    T el = v[0];
    for (int i=1;i<v.size();++i) {
      if (!(v[i] <= el)) return false;
      el = v[i];
    }
    return el==el; // nan -> false
  }
  
  template<typename T>
  bool isNonDecreasing(const std::vector<T> &v) {
    if (v.size()==0) return true;
    T el = v[0];
    for (int i=1;i<v.size();++i) {
      if (!(v[i] >= el)) return false;
      el = v[i];
    }
    return el==el; // nan -> false
  }
  
  template<typename T>
  bool isMonotone(const std::vector<T> &v) {
    return isNonDecreasing(v) || isNonIncreasing(v);
  }
  
  template<typename T>
  bool isStrictlyMonotone(const std::vector<T> &v) {
    return isDecreasing(v) || isIncreasing(v);
  }

  template<typename T>
  std::string getRepresentation(const std::vector<T> &v){
    std::stringstream ss;
    repr(v,ss);
    return ss.str();
  }
  
  template<typename T>
  std::string getDescription(const std::vector<T> &v){
    std::stringstream ss;
    print(v,ss);
    return ss.str();
  }

  template<typename T>
  void write_matlab(std::ostream &stream, const std::vector<T> &v){
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(stream, " "));
  }
  
  template<typename T>
  void write_matlab(std::ostream &stream, const std::vector<std::vector<T> > &v){
    for(unsigned int i=0; i<v.size(); ++i){    
      std::copy(v[i].begin(), v[i].end(), std::ostream_iterator<T>(stream, " "));
      stream << std::endl;
    }
  }
  
  template<typename T>
  void read_matlab(std::istream &stream, std::vector<T> &v){
    v.clear();
  
    while(!stream.eof()) {
      T val;
      stream >> val;
      if(stream.fail()){
        stream.clear();
        std::string s;
        stream >> s;
        if(s.compare("inf") == 0)
          val = std::numeric_limits<T>::infinity();
        else
          break;
      }
      v.push_back(val);
    }
  }
  
  template<typename T>
  void read_matlab(std::ifstream &file, std::vector<std::vector<T> > &v){
    v.clear();
    std::string line;
    while(!getline(file, line, '\n').eof()) {
      std::istringstream reader(line);
      std::vector<T> lineData;
      
      while(!reader.eof()) {
        T val;
        reader >> val;
        if(reader.fail()){
          reader.clear();
          std::string s;
          reader >> s;
          if(s.compare("inf") == 0)
            val = std::numeric_limits<T>::infinity();
          else
            break;
        }
        lineData.push_back(val);
      }
      v.push_back(lineData);
    }
  }

  template<typename T, typename F, typename L>
  void linspace(std::vector<T> &v, const F& first, const L& last){
    if(v.size()<2) throw CasadiException("std::linspace: vector must contain at least two elements");
    
    // Increment
    T increment = (last-first)/T(v.size()-1);
    
    v[0] = first;
    for(unsigned i=1; i<v.size()-1; ++i)
      v[i] = v[i-1] + increment;
    v[v.size()-1] = last;
  }

  template<typename T>
  T* getPtr(std::vector<T> &v){
    if(v.empty())
      return 0;
    else
      return &v.front();
  }
  
  template<typename T>
  const T* getPtr(const std::vector<T> &v){
    if(v.empty())
      return 0;
    else
      return &v.front();
  }
  
  template<typename T>
  void sort(const std::vector<T> &values, std::vector<T> &sorted_values, std::vector<int> &indices,  bool invert_indices) {
  
    // Create a list of (value,index) pairs
    std::vector< std::pair<T,int> > pvalues(values.size());
    
    for (int i=0;i<values.size();++i) {
      pvalues[i].first  = values[i];
      pvalues[i].second = i;
    }
    
    // Sort this list by the values
    std::sort(pvalues.begin(),pvalues.end());
    
    // Read out the results
    sorted_values.resize(values.size());
    indices.resize(values.size());
    if (invert_indices) {
      for (int i=0;i<values.size();++i) {
        sorted_values[i] = pvalues[i].first;
        indices[pvalues[i].second]       =  i;
      }
    } else {
      for (int i=0;i<values.size();++i) {
        sorted_values[i] = pvalues[i].first;
        indices[i]       =  pvalues[i].second;
      }
    }
    
    
    
  }

  template<typename T>
  std::vector<T> makeVector(int size, 
                            int ind0, const T& val0,
                            int ind1, const T& val1,
                            int ind2, const T& val2,
                            int ind3, const T& val3,
                            int ind4, const T& val4,
                            int ind5, const T& val5,
                            int ind6, const T& val6,
                            int ind7, const T& val7,
                            int ind8, const T& val8,
                            int ind9, const T& val9,
                            int ind10, const T& val10,
                            int ind11, const T& val11,
                            int ind12, const T& val12,
                            int ind13, const T& val13,
                            int ind14, const T& val14,
                            int ind15, const T& val15,
                            int ind16, const T& val16,
                            int ind17, const T& val17,
                            int ind18, const T& val18,
                            int ind19, const T& val19){
    
    // Maximum size supported
    const int max_size = 20;
                              
    // Collect all arguments                          
    int ind[max_size] = {ind0,ind1,ind2,ind3,ind4,ind5,ind6,ind7,ind8,ind9,ind10,ind11,ind12,ind13,ind14,ind15,ind16,ind17,ind18,ind19};
    int val[max_size] = {val0,val1,val2,val3,val4,val5,val6,val7,val8,val9,val10,val11,val12,val13,val14,val15,val16,val17,val18,val19};
    
    // Return value
    std::vector<T> ret(size);
    
    // Assign all values
    for(int i=0; i<max_size; ++i){
      // Break if not assigned
      if(ind[i]<0) break;
      
      // Assign value
      ret.at(ind[i]) = val[i];
    }
    
    return ret;
  }
  
  
  template<typename T>
  bool isRegular(const std::vector<T> &v) {
    for (int k=0;k<v.size();++k) {
      if (v[k]!=v[k] || v[k]==std::numeric_limits<T>::infinity() || v[k]==-std::numeric_limits<T>::infinity() ) return false;
    }
    return true;
  }
  
  template<typename T>
  T inner_prod(const std::vector<T>& a, const std::vector<T>& b){
    T ret = 0;
    for(int k=0; k<a.size(); ++k){
      ret += a[k]*b[k];
    }
    return ret;
  }
  
  template<typename T>
  T norm_inf(const std::vector<T>& x){
    T ret = 0;
    for(int k=0; k<x.size(); ++k){
      ret = fmax(ret,fabs(x[k]));
    }
    return ret;
  }
  
  template<typename T>
  T norm_1(const std::vector<T>& x){
    T ret = 0;
    for(int k=0; k<x.size(); ++k){
      ret += fabs(x[k]);
    }
    return ret;
  }

  template<typename T>
  T norm_2(const std::vector<T>& x){
    T ret = 0;
    for(int k=0; k<x.size(); ++k){
      ret += x[k]*x[k];
    }
    return sqrt(ret);
  }
  
} // namespace CasADi

#endif // SWIG

#ifdef SWIG

// map the template name to the instantiated name
#define VTT_INST(T,function_name) \
%template(function_name) CasADi::function_name<T>;

// Define template instanciations
#define VECTOR_TOOLS_TEMPLATES(T) \
VTT_INST(T,isIncreasing) \
VTT_INST(T,isDecreasing) \
VTT_INST(T,isNonIncreasing) \
VTT_INST(T,isNonDecreasing) \
VTT_INST(T,isMonotone) \
VTT_INST(T,isStrictlyMonotone) \
VTT_INST(T,isRegular) \

#endif //SWIG

#endif // STD_VECTOR_TOOLS_HPP
