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

#ifndef CCS_SPARSITY_HPP
#define CCS_SPARSITY_HPP

#include "../shared_object.hpp"
#include <vector>
#include <list>
#include <limits>

// Cashing requires a multimap (preferably a hash map)
#ifdef USE_CXX11
// Using C++11 unordered_multimap (hash map)
#ifdef USE_TR1_HASHMAP
#include <tr1/unordered_map>
#define CACHING_MULTIMAP std::tr1::unordered_multimap
#else // USE_TR1_HASHMAP
#include <unordered_map>
#define CACHING_MULTIMAP std::unordered_multimap
#endif // USE_TR1_HASHMAP
#else // USE_CXX11
// Falling back to std::map (binary search tree)
#include <map>
#define CACHING_MULTIMAP std::multimap
#endif // USE_CXX11
#include "../weak_ref.hpp"

#ifdef SWIG
  %rename(getNZ_const) getNZ(int, int) const;
#endif

namespace CasADi{

  // Forward declaration
  class CCSSparsityInternal;
  
  /** \brief General sparsity class
   * 
   * The storage format is a compressed column storage (CCS) format.\n
   * 
   In this format, the structural non-zero elements are stored in column-major order, starting from 
   the upper left corner of the matrix and ending in the lower right corner.
  
   In addition to the dimension (size1(),size2()), (i.e. the number of rows and the number of columns
   respectively), there are also two vectors of integers:
  
   1. "colind" [length size2()+1], which contains the index to the first non-zero element on or after
   the corresponding col. All the non-zero elements of a particular i are thus the elements with 
   index el that fulfils: colind[i] <= el < colind[i+1].
     
   2. "row" [same length as the number of non-zero elements, size()] The rows for each of the
   structural non-zeros.
     
   Note that with this format, it is cheap to loop over all the non-zero elements of a particular column,
   at constant time per element, but expensive to jump to access a location (i,j).
  
   If the matrix is dense, i.e. length(row) == size1()*size2(), the format reduces to standard dense
   column major format, which allows access to an arbitrary element in constant time.
  
   Since the object is reference counted (it inherits from SharedObject), several matrices are allowed
   to share the same sparsity pattern.
  
   The implementations of some methods of this class has been taken from the CSparse package and modified
   to use STL and CasADi data structures.
  
   * \see Matrix
   *
   * \author Joel Andersson 
   * \date 2010
   */
  class CCSSparsity : public SharedObject{
  public:
  
    /// Default constructor
    explicit CCSSparsity(int dummy=0);
    
    /// Construct a sparsity pattern (sparse/dense)
    CCSSparsity(int nrow, int ncol, bool dense=false);

    /// Construct a sparsity pattern from vectors
    CCSSparsity(int nrow, int ncol, const std::vector<int>& colind, const std::vector<int>& row);

#ifndef SWIG
    /** \brief  Create from node */
    static CCSSparsity create(CCSSparsityInternal *node);
#endif

    /** \brief Check if there is an identical copy of the sparsity pattern in the cache, and if so, make a shallow copy of that one */
    void reCache();

    /** \brief Clear the cache */
    static void clearCache();

    /** \brief Check if the dimensions and colind, row vectors are compatible.
     * \param complete  set to true to also check elementwise
     * throws an error as possible result
     */
    void sanityCheck(bool complete=false) const;
    
    /// Create a diagonal matrix
    static CCSSparsity createDiagonal(int n);
    static CCSSparsity createDiagonal(int m, int n);
    
    /** Get the diagonal of the matrix/create a diagonal matrix (mapping will contain the nonzero mapping)
        When the input is square, the diagonal elements are returned.
        If the input is vector-like, a diagonal matrix is constructed with it.
    */
#ifndef SWIG
    CCSSparsity diag(std::vector<int>& mapping) const;
#else // SWIG
    CCSSparsity diag(std::vector<int>& OUTPUT) const;
#endif // SWIG
    
    /// Access a member function or object
    CCSSparsityInternal* operator->();

    /// Const access a member function or object
    const CCSSparsityInternal* operator->() const;
  
    /// Check if the node is pointing to the right type of object
    virtual bool checkNode() const;

    /// \name Check if two sparsity patterns are identical
    /// @{
    bool isEqual(const CCSSparsity& y) const;
    bool isEqual(int nrow, int ncol, const std::vector<int>& colind, const std::vector<int>& row) const;
    bool operator==(const CCSSparsity& y) const{ return isEqual(y);}
    /// @}
    
    /// Check if two sparsity patterns are difference
    bool operator!=(const CCSSparsity& y) const{return !isEqual(y);}
    
    /// Take the union of two sparsity patterns
    CCSSparsity operator+(const CCSSparsity& b) const;

    /// Take the intersection of two sparsity patterns
    CCSSparsity operator*(const CCSSparsity& b) const;
    
    /// \name Size and element counting
    /// @{
    
    /// Get the number of cols
    int size2() const;
    
    /// Get the number of rows
    int size1() const;

    /** \brief The total number of elements, including structural zeros, i.e. size2()*size1()
        \see size()  */
    int numel() const;
    
    /// Check if the sparsity is empty, i.e. one of its dimensions is 0 
    bool empty() const;
    
    /// Check if the sparsity is null, i.e. dimension is 0-by-0
    bool null() const;
    
    /** \brief Get the number of (structural) non-zeros
        \see numel() */
    int size() const;

    /** \brief Number of non-zeros in the upper triangular half, i.e. the number of elements (i,j) with j>=i */
    int sizeL() const;

    /** \brief Number of non-zeros in the lower triangular half, i.e. the number of elements (i,j) with j<=i */
    int sizeU() const;

    /** \brief Number of non-zeros on the diagonal, i.e. the number of elements (i,j) with j==i */
    int sizeD() const;
    
#ifndef SWIG
    /** \brief  Get the shape */
    std::pair<int,int> shape() const;
#endif
    /// @}

    /** \brief Get a reference to row-vector, containing rows for all non-zero elements (see class description) */
    const std::vector<int>& row() const;
    
    /** \brief Get the row of a non-zero element */
    int row(int el) const;
    
    /** \brief Get a reference to the colindex of all column element (see class description) */
    const std::vector<int>& colind() const;

    /** \brief  Get a reference to the colindex of col i (see class description) */
    int colind(int i) const;

    /** \brief Get a reference to the rows of all non-zero element (copy if not unique!) */
    std::vector<int>& rowRef();
    
    /** \brief Get a reference to the colindex of all column element (copy if not unique!) */
    std::vector<int>& colindRef();
    
    /** \brief Get the column for each non-zero entry
        Together with the row-vector, this vector gives the sparsity of the matrix in
        sparse triplet format, i.e. the column and row for each non-zero elements  */
    std::vector<int> getCol() const;
    
    /// Resize
    void resize(int nrow, int ncol);
    
    /// Reshape a sparsity, order of nonzeros remains the same
    CCSSparsity reshape(int nrow, int ncol) const;
    
    /** \brief Get the index of a non-zero element
        Add the element if it does not exist and copy object if it's not unique */
    int getNZ(int rr, int cc);
    
    /** \brief Get the index of an existing non-zero element
        return -1 if the element does not exists */
    int getNZ(int rr, int cc) const;

    /// Returns true if the pattern has a non-zero at location rr,cc
    bool hasNZ(int rr, int cc) const;

    /** \brief Get a set of non-zero element
        return -1 if the element does not exists */
    std::vector<int> getNZ(const std::vector<int>& rr, const std::vector<int>& cc) const;

    /** \brief Get the nonzero index for a set of elements
        The index vector is used both for input and outputs and must be sorted by increasing
        nonzero index, i.e. column-wise.
        Elements not found in the sparsity pattern are set to -1.
    */
    void getNZInplace(std::vector<int>& indices) const;

    /// Get the sparsity in CCS format
#ifndef SWIG
    void getSparsityCCS(std::vector<int>& colind, std::vector<int>& row) const;
#else // SWIG
    void getSparsityCCS(std::vector<int>& OUTPUT, std::vector<int>& OUTPUT) const;
#endif // SWIG

    /// Get the sparsity in CCS format
#ifndef SWIG
    void getSparsityCRS(std::vector<int>& rowind, std::vector<int>& col) const;
#else // SWIG
    void getSparsityCRS(std::vector<int>& OUTPUT, std::vector<int>& OUTPUT) const;
#endif // SWIG

    /// Get the sparsity in sparse triplet format
#ifndef SWIG
    void getSparsity(std::vector<int>& row, std::vector<int>& col) const;
#else // SWIG
    void getSparsity(std::vector<int>& OUTPUT, std::vector<int>& OUTPUT) const;
#endif // SWIG

    /** \brief Get a submatrix
     *
     * Returns the sparsity of the submatrix, with a mapping such that
     *   submatrix[k] = originalmatrix[mapping[k]]
     */
    CCSSparsity sub(const std::vector<int>& jj, const std::vector<int>& ii, std::vector<int>& mapping) const;
    
    /// Transpose the matrix
    CCSSparsity transpose() const;

    /// Transpose the matrix and get the reordering of the non-zero entries, i.e. the non-zeros of the original matrix for each non-zero of the new matrix
    CCSSparsity transpose(std::vector<int>& mapping, bool invert_mapping=false) const;
        
    /// Check if the sparsity is the transpose of another
    bool isTranspose(const CCSSparsity& y) const;

    /// @{
    /** \brief Combine two sparsity patterns
        Returns the new sparsity pattern as well as a mapping with the same length as the number of non-zero elements
        The mapping matrix contains the arguments for each nonzero, the first bit indicates if the first argument is nonzero,
        the second bit indicates if the second argument is nonzero (note that none of, one of or both of the arguments can be nonzero) */
    CCSSparsity patternCombine(const CCSSparsity& y, bool f0x_is_zero, bool fx0_is_zero, std::vector<unsigned char>& mapping) const;
    CCSSparsity patternCombine(const CCSSparsity& y, bool f0x_is_zero, bool fx0_is_zero) const;
    /// @}

    /// @{
    /** \brief Union of two sparsity patterns */
    CCSSparsity patternUnion(const CCSSparsity& y, std::vector<unsigned char>& mapping) const;
    CCSSparsity patternUnion(const CCSSparsity& y) const;
    /// @}
    
    /// @{
    /** \brief Intersection of two sparsity patterns
        Returns the new sparsity pattern as well as a mapping with the same length as the number of non-zero elements
        The value is 1 if the non-zero comes from the first (i.e. this) object, 2 if it is from the second and 3 (i.e. 1 | 2) if from both */
    CCSSparsity patternIntersection(const CCSSparsity& y, std::vector<unsigned char>& mapping) const;
    CCSSparsity patternIntersection(const CCSSparsity& y) const;
    /// @}

    /// @{
    /** \brief Sparsity pattern for a matrix-matrix product, with the first factor transposed
        Returns the new sparsity pattern as well as a mapping with the same length as the number of non-zero elements
        The mapping contains a vector of the index pairs that makes up the scalar products for each non-zero */
    CCSSparsity patternProduct(const CCSSparsity& y, std::vector< std::vector< std::pair<int,int> > >& mapping) const;
    CCSSparsity patternProduct(const CCSSparsity& y) const;
    /// @}

    /// Take the inverse of a sparsity pattern; flip zeros and non-zeros
    CCSSparsity patternInverse() const;
    
    /** \brief Enlarge matrix
        Make the matrix larger by inserting empty rows and columns, keeping the existing non-zeros 
    
        For the matrices A to B
        A(m,n)
        length(jj)=m , length(ii)=n
        B(nrow,ncol)
    
        A=enlarge(m,n,ii,jj) makes sure that
    
        B[jj,ii] == A 
    */
    void enlarge(int nrow, int ncol, const std::vector<int>& jj, const std::vector<int>& ii);

    /** \brief Enlarge the matrix along the first dimension (i.e. insert rows) */
    void enlargeRows(int nrow, const std::vector<int>& jj);

    /** \brief Enlarge the matrix along the second dimension (i.e. insert columns) */
    void enlargeColumns(int ncol, const std::vector<int>& ii);
    
    /** \brief Make a patten dense */
    CCSSparsity makeDense(std::vector<int>& mapping) const;

    /** \brief Erase rows and/or columns of a matrix */
    std::vector<int> erase(const std::vector<int>& jj, const std::vector<int>& ii);

    /// Append another sparsity patten vertically (NOTE: only efficient if vector)
    void append(const CCSSparsity& sp);

    /// Append another sparsity patten horizontally
    void appendColumns(const CCSSparsity& sp);

    /// Reserve space
    void reserve(int nnz, int ncol);

    /// Is scalar?
    bool scalar(bool scalar_and_dense=false) const;
    
    /// Is dense?
    bool dense() const;
    
    /// Is vector (i.e. size2()==1)
    bool vector() const{ return size2()==1; }

    /// Is diagonal?
    bool diagonal() const;
    
    /// Is square?
    bool square() const;

    /// Is symmetric?
    bool symmetric() const;

    /// Is lower triangular?
    bool tril() const;

    /// Is upper triangular?
    bool triu() const;

    /// Get lower triangular part
    CCSSparsity lower(bool includeDiagonal=true) const;

    /// Get lower triangular part
    CCSSparsity upper(bool includeDiagonal=true) const;

    /// Get nonzeros in lower triangular part
    std::vector<int> lowerNZ() const;

    /// Get nonzeros in upper triangular part
    std::vector<int> upperNZ() const;

    /// Do the rows appear sequentially on each column (if strictly==true, then do not allow multiple entries)
    bool rowsSequential(bool strictly=true) const;

    /// Remove duplicate entries: The same indices will be removed from the mapping vector, which must have the same length as the number of nonzeros
    void removeDuplicates(std::vector<int>& mapping);
    
#ifndef SWIG
    typedef CACHING_MULTIMAP<std::size_t,WeakRef> CachingMap;

    /// Cached sparsity patterns
    static CachingMap& getCache();

    /// (Dense) scalar
    static const CCSSparsity& getScalar();

    /// (Sparse) scalar
    static const CCSSparsity& getScalarSparse();
    
    /// Empty zero-by-zero
    static const CCSSparsity& getEmpty();

#endif //SWIG
    
    /** \brief Calculate the elimination tree
        See Direct Methods for Sparse Linear Systems by Davis (2006).
        If the parameter ata is false, the algorithm is equivalent to Matlab's etree(A), except that
        the indices are zero-based. If ata is true, the algorithm is equivalent to Matlab's etree(A,'row').
    */
    std::vector<int> eliminationTree(bool ata=false) const;
    
    /** \brief Depth-first search on the adjacency graph of the sparsity
        See Direct Methods for Sparse Linear Systems by Davis (2006).
    */
    int depthFirstSearch(int j, int top, std::vector<int>& xi, std::vector<int>& pstack, const std::vector<int>& pinv, std::vector<bool>& marked) const;
    
    /** \brief Find the strongly connected components of the bigraph defined by the sparsity pattern of a square matrix
        See Direct Methods for Sparse Linear Systems by Davis (2006).
        Returns:
        - Number of components
        - Offset for each components (length: 1 + number of components) 
        - Indices for each components, component i has indices index[offset[i]], ..., index[offset[i+1]]
      
        In the case that the matrix is symmetric, the result has a particular interpretation:
        Given a symmetric matrix A and
        n = A.stronglyConnectedComponents(p,r)
       
        => A[p,p] will appear block-diagonal with n blocks and
        with the indices of the block boundaries to be found in r. 
      
    */
#ifndef SWIG
    int stronglyConnectedComponents(std::vector<int>& index, std::vector<int>& offset) const;
#else // SWIG
    int stronglyConnectedComponents(std::vector<int>& OUTPUT, std::vector<int>& OUTPUT) const;
#endif // SWIG
    
    /** \brief Compute the Dulmage-Mendelsohn decomposition 
        See Direct Methods for Sparse Linear Systems by Davis (2006).
       
        Dulmage-Mendelsohn will try to bring your matrix into lower block-triangular (LBT) form.
        It will not care about the distance of off-diagonal elements to the diagonal:
        there is no guarantee you will get a block-diagonal matrix if you supply a randomly permuted block-diagonal matrix.
      
        If your matrix is symmetrical, this method is of limited use; permutation can make it non-symmetric.
      
        \sa stronglyConnectedComponents

    */
#ifndef SWIG
    int dulmageMendelsohn(std::vector<int>& rowperm, std::vector<int>& colperm, std::vector<int>& rowblock, std::vector<int>& colblock, std::vector<int>& coarse_rowblock, std::vector<int>& coarse_colblock, int seed=0) const;
#else // SWIG
    int dulmageMendelsohn(std::vector<int>& OUTPUT, std::vector<int>& OUTPUT, std::vector<int>& OUTPUT, std::vector<int>& OUTPUT, std::vector<int>& OUTPUT, std::vector<int>& OUTPUT, int seed=0) const;
#endif // SWIG
    /// Get the location of all nonzero elements
    std::vector<int> getElements(bool col_major=true) const;
    
    /// Get the location of all nonzero elements (inplace version)
    void getElements(std::vector<int>& loc, bool col_major=true) const;
    
    /** \brief Perform a unidirectional coloring: A greedy distance-2 coloring algorithm (Algorithm 3.1 in A. H. GEBREMEDHIN, F. MANNE, A. POTHEN) */
    CCSSparsity unidirectionalColoring(const CCSSparsity& AT=CCSSparsity(), int cutoff = std::numeric_limits<int>::max()) const;

    /** \brief Perform a star coloring of a symmetric matrix:
        A greedy distance-2 coloring algorithm (Algorithm 4.1 in A. H. GEBREMEDHIN, F. MANNE, A. POTHEN) 
        Ordering options: None (0), largest first (1)
    */
    CCSSparsity starColoring(int ordering = 1, int cutoff = std::numeric_limits<int>::max()) const;

    /** \brief Perform a star coloring of a symmetric matrix:
        A new greedy distance-2 coloring algorithm (Algorithm 4.1 in A. H. GEBREMEDHIN, A. TARAFDAR, F. MANNE, A. POTHEN) 
        Ordering options: None (0), largest first (1)
    */
    CCSSparsity starColoring2(int ordering = 1, int cutoff = std::numeric_limits<int>::max()) const;
    
    /** \brief Order the cols by decreasing degree */
    std::vector<int> largestFirstOrdering() const;
    
    /** \brief Permute rows and/or columns
        Multiply the sparsity with a permutation matrix from the left and/or from the right
        P * A * trans(P), A * trans(P) or A * trans(P) with P defined by an index vector 
        containing the row for each col. As an alternative, P can be transposed (inverted).
    */
    CCSSparsity pmult(const std::vector<int>& p, bool permute_rows=true, bool permute_cols=true, bool invert_permutation=false) const;
      
    /// Get the dimension as a string
    std::string dimString() const;
    
    /** \brief Print a textual representation of sparsity
     */
    void spy(std::ostream &stream=std::cout) const;

    /** \brief Generate a script for Matlab or Octave which visualizes the sparsity using the spy command
     */
    void spyMatlab(const std::string& mfile) const;

    // Hash the sparsity pattern
    std::size_t hash() const;
  
#ifndef SWIG
    /** \brief Assign the nonzero entries of one sparsity pattern to the nonzero entries of another sparsity pattern */
    template<typename T>
    void set(T* data, const T* val_data, const CCSSparsity& val_sp) const;

    /** \brief Add the nonzero entries of one sparsity pattern to the nonzero entries of another sparsity pattern */
    template<typename T>
    void add(T* data, const T* val_data, const CCSSparsity& val_sp) const;

    /** \brief Bitwise or of the nonzero entries of one sparsity pattern and the nonzero entries of another sparsity pattern */
    template<typename T>
    void bor(T* data, const T* val_data, const CCSSparsity& val_sp) const;


  private:
    /// Construct a sparsity pattern from vectors, reuse cached pattern if possible
    void assignCached(int nrow, int ncol, const std::vector<int>& colind, const std::vector<int>& row);

#endif //SWIG
  };

  // Template instantiations
#ifndef SWIG
  template<typename T>
  void CCSSparsity::set(T* data, const T* val_data, const CCSSparsity& val_sp) const{
    // Get dimensions of this
    const int sz = size();
    const int sz1 = size1();
    const int sz2 = size2();
    const int nel = sz1*sz2;

    // Get dimensions of assigning matrix
    const int val_sz = val_sp.size();
    const int val_sz1 = val_sp.size1();
    const int val_sz2 = val_sp.size2();
    const int val_nel = val_sz1*val_sz2;

    // Check if sparsity matches
    if(val_sp==*this){
      std::copy(val_data,val_data+sz,data);
    } else if (this->empty()) {
      // Quick return
      return;
    } else if (val_sp.empty()) {
      // Quick return
      return;
    } else if(val_nel==1){ // if scalar
      std::fill(data,data+sz,val_sz==0 ? T(0) : val_data[0]);
    } else {
      // Quick return if empty
      if(nel==0 && val_nel==0) return;
    
      // Make sure that dimension matches
      casadi_assert_message(sz2==val_sz2 && sz1==val_sz1,"CCSSparsity::set<T>: shape mismatch. lhs is matrix of shape " << dimString() << ", while rhs is shape " << val_sp.dimString() << ".");
    
      // Sparsity
      const std::vector<int>& c = row();
      const std::vector<int>& rind = colind();
      const std::vector<int>& v_c = val_sp.row();
      const std::vector<int>& v_rind = val_sp.colind();
    
      // For all cols
      for(int i=0; i<sz2; ++i){
      
        // Nonzero of the assigning matrix
        int v_el = v_rind[i];
      
        // First nonzero of the following col
        int v_el_end = v_rind[i+1];
      
        // Next row of the assigning matrix
        int v_j = v_el<v_el_end ? v_c[v_el] : sz1;
      
        // Assign all nonzeros
        for(int el=rind[i]; el!=rind[i+1]; ++el){
        
          //  Get row
          int j=c[el];
        
          // Forward the assigning nonzero
          while(v_j<j){
            v_el++;
            v_j = v_el<v_el_end ? v_c[v_el] : sz1;
          }

          // Assign nonzero
          if(v_j==j){
            data[el] = val_data[v_el++];
            v_j = v_el<v_el_end ? v_c[v_el] : sz1;
          } else {
            data[el] = 0;
          }
        }
      }
    }
  }

  template<typename T>
  void CCSSparsity::add(T* data, const T* val_data, const CCSSparsity& val_sp) const{
    // Get dimensions of this
    const int sz = size();
    const int sz1 = size1();
    const int sz2 = size2();
    const int nel = sz1*sz2;

    // Get dimensions of assigning matrix
    const int val_sz = val_sp.size();
    const int val_sz1 = val_sp.size1();
    const int val_sz2 = val_sp.size2();
    const int val_nel = val_sz1*val_sz2;

    // Check if sparsity matches
    if(val_sp==*this){
      for(int k=0; k<sz; ++k){
        data[k] += val_data[k];
      }
    } else if (this->empty()) {
      // Quick return
      return;
    } else if (val_sp.empty()) {
      // Quick return
      return;
    }  else if(val_nel==1){ // if scalar
      if(val_sz!=0){
        for(int k=0; k<sz; ++k){
          data[k] += val_data[0];
        }
      }
    } else {
      // Quick return if empty
      if(nel==0 && val_nel==0) return;
    
      // Make sure that dimension matches
      casadi_assert_message(sz2==val_sz2 && sz1==val_sz1,"CCSSparsity::add<T>: shape mismatch. lhs is matrix of shape " << dimString() << ", while rhs is shape " << val_sp.dimString() << ".");
    
      // Sparsity
      const std::vector<int>& c = row();
      const std::vector<int>& rind = colind();
      const std::vector<int>& v_c = val_sp.row();
      const std::vector<int>& v_rind = val_sp.colind();
    
      // For all cols
      for(int i=0; i<sz2; ++i){
      
        // Nonzero of the assigning matrix
        int v_el = v_rind[i];
      
        // First nonzero of the following column
        int v_el_end = v_rind[i+1];
      
        // Next row of the assigning matrix
        int v_j = v_el<v_el_end ? v_c[v_el] : sz1;
      
        // Assign all nonzeros
        for(int el=rind[i]; el!=rind[i+1]; ++el){
        
          //  Get row
          int j=c[el];
        
          // Forward the assigning nonzero
          while(v_j<j){
            v_el++;
            v_j = v_el<v_el_end ? v_c[v_el] : sz1;
          }

          // Assign nonzero
          if(v_j==j){
            data[el] += val_data[v_el++];
            v_j = v_el<v_el_end ? v_c[v_el] : sz1;
          }
        }
      }
    }
  }

  template<typename T>
  void CCSSparsity::bor(T* data, const T* val_data, const CCSSparsity& val_sp) const{
    // Get dimensions of this
    const int sz = size();
    const int sz1 = size1();
    const int sz2 = size2();
    const int nel = sz1*sz2;

    // Get dimensions of assigning matrix
    const int val_sz = val_sp.size();
    const int val_sz1 = val_sp.size1();
    const int val_sz2 = val_sp.size2();
    const int val_nel = val_sz1*val_sz2;

    // Check if sparsity matches
    if(val_sp==*this){
      for(int k=0; k<sz; ++k){
        data[k] |= val_data[k];
      }
    } else if (this->empty()) {
      // Quick return
      return;
    } else if (val_sp.empty()) {
      // Quick return
      return;
    }  else if(val_nel==1){ // if scalar
      if(val_sz!=0){
        for(int k=0; k<sz; ++k){
          data[k] |= val_data[0];
        }
      }
    } else {
      // Quick return if empty
      if(nel==0 && val_nel==0) return;
    
      // Make sure that dimension matches
      casadi_assert_message(sz2==val_sz2 && sz1==val_sz1,"CCSSparsity::add<T>: shape mismatch. lhs is matrix of shape " << dimString() << ", while rhs is shape " << val_sp.dimString() << ".");
    
      // Sparsity
      const std::vector<int>& c = row();
      const std::vector<int>& rind = colind();
      const std::vector<int>& v_c = val_sp.row();
      const std::vector<int>& v_rind = val_sp.colind();
    
      // For all columns
      for(int i=0; i<sz2; ++i){
      
        // Nonzero of the assigning matrix
        int v_el = v_rind[i];
      
        // First nonzero of the following column
        int v_el_end = v_rind[i+1];
      
        // Next row of the assigning matrix
        int v_j = v_el<v_el_end ? v_c[v_el] : sz1;
      
        // Assign all nonzeros
        for(int el=rind[i]; el!=rind[i+1]; ++el){
        
          //  Get row
          int j=c[el];
        
          // Forward the assigning nonzero
          while(v_j<j){
            v_el++;
            v_j = v_el<v_el_end ? v_c[v_el] : sz1;
          }

          // Assign nonzero
          if(v_j==j){
            data[el] |= val_data[v_el++];
            v_j = v_el<v_el_end ? v_c[v_el] : sz1;
          }
        }
      }
    }
  }

#endif //SWIG

} // namespace CasADi

#endif // CCS_SPARSITY_HPP