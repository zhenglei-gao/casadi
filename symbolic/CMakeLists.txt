cmake_minimum_required(VERSION 2.6)

include_directories(${CMAKE_BINARY_DIR})

add_subdirectory(runtime)

SET(CASADI_SRCS
  # MISC
  casadi_limits.hpp
  casadi_types.hpp
  casadi_exception.hpp
  casadi_calculus.hpp
  casadi_math.hpp
  casadi_options.hpp          casadi_options.cpp
  casadi_meta.hpp             casadi_meta.cpp
  printable_object.hpp        printable_object.cpp      # Base class enabling printing a Python-style "description" as well as a shorter "representation" of a class
  shared_object.hpp           shared_object.cpp         # This base class implements the reference counting (garbage collection) framework used in CasADi
  weak_ref.hpp                weak_ref.cpp              # Provides weak reference functionality (non-owning smart pointers)
  generic_type.hpp            generic_type.cpp          # Generic type used for options and for compatibility with dynamically typed languages like Python
  generic_type_internal.hpp                             # Internal class for the same
  options_functionality.cpp   options_functionality.hpp # Functionality for getting and setting options of a derived class
  std_vector_tools.hpp        std_vector_tools.cpp      # Set of useful functions for the vector template class in STL
  profiling.hpp               profiling.cpp
  functor.hpp                 functor.cpp              # Classes for callbacks
  functor_internal.hpp        functor_internal.cpp     
  polynomial.hpp              polynomial.cpp            # Helper class for differentiating and integrating simple polynomials

  # Template class Matrix<>, implements a sparse Matrix with col compressed storage, designed to work well with symbolic data types (SX)
  matrix/generic_expression.hpp                         # Base class for SXElement MX and Matrix<>
  matrix/generic_expression_tools.hpp                   # Tools for SXElement MX and Matrix<>
  matrix/generic_matrix.hpp                             # Base class for Matrix<> and MX
  matrix/generic_matrix_tools.hpp                       # Tools for both Matrix<> and MX
  matrix/matrix.hpp           matrix/matrix_impl.hpp    # The Matrix template class
  matrix/sparsity.hpp     matrix/sparsity.cpp   matrix/sparsity_internal.hpp   matrix/sparsity_internal.cpp    # reference counted sparsity pattern
  matrix/slice.hpp            matrix/slice.cpp          # A "slice" in a language such as Python, A[start:stop:step], or Matlab, A(start:step:stop)
  matrix/submatrix.hpp                                  # A reference to a block of the matrix to allow operations such as A(:,3) = ...
  matrix/nonzeros.hpp                                   # A reference to a set of nonzeros of the matrix to allow operations such as A[3] = ...
  matrix/matrix_tools.hpp     matrix/matrix_tools.cpp   # Set of functions
  matrix/sparsity_tools.hpp   matrix/sparsity_tools.cpp # Set of functions for sparsity

  # Directed, acyclic graph representation with scalar expressions
  sx/sx_element.hpp          sx/sx_element.cpp          # Symbolic expression class (scalar-valued atomics)
  sx/sx_node.hpp             sx/sx_node.cpp             # Base class for all the nodes
  sx/symbolic_sx.hpp                                    # A symbolic SXElement variable 
  sx/constant_sx.hpp                                    # A constant SXElement node
  sx/unary_sx.hpp                                       # A unary operation
  sx/binary_sx.hpp                                      # A binary operation
  sx/sx_tools.cpp            sx/sx_tools.hpp            # Set of functions

  # More general graph representation with sparse matrix expressions and function evaluations
  mx/mx.hpp                  mx/mx.cpp                  # Symbolic expression class (matrix-valued atomics)
  mx/mx_node.hpp             mx/mx_node.cpp             # Base class for all the MX nodes
  mx/constant_mx.hpp         mx/constant_mx.cpp         # A constant MX node
  mx/symbolic_mx.hpp         mx/symbolic_mx.cpp         # A symbolic MX variable
  mx/unary_mx.hpp            mx/unary_mx.cpp            # Unary operation
  mx/binary_mx.hpp           mx/binary_mx_impl.hpp      # Binary operation
  mx/multiplication.hpp      mx/multiplication_impl.hpp # Matrix multiplication
  mx/solve.hpp               mx/solve_impl.hpp          # Solve linear system of equations
  mx/call_function.hpp       mx/call_function.cpp       # Function evaluation node
  mx/norm.hpp                mx/norm.cpp                # 1-norm, 2-norm and infinity-norm
  mx/transpose.hpp           mx/transpose.cpp           # Transpose
  mx/concat.hpp              mx/concat.cpp              # Concatenation
  mx/split.hpp               mx/split.cpp               # Split (inverse of concatenation)
  mx/reshape.hpp             mx/reshape.cpp             # Reshape
  mx/subref.hpp              mx/subref.cpp              # Submatrix reference
  mx/subassign.hpp           mx/subassign.cpp           # Submatrix assignment
  mx/getnonzeros.hpp         mx/getnonzeros.cpp         # Get the nonzeros of matrix
  mx/setnonzeros.hpp         mx/setnonzeros_impl.hpp    # Assign the nonzeros of a matrix to another matrix
  mx/set_sparse.hpp          mx/set_sparse.cpp          # Sparse copy
  mx/determinant.hpp         mx/determinant.cpp         # Determinant
  mx/inverse.hpp             mx/inverse.cpp             # Matrix inverse
  mx/inner_prod.hpp          mx/inner_prod.cpp          # Inner product
  mx/multiple_output.hpp     mx/multiple_output.cpp     # Base class for nodes with multiple outputs
  mx/assertion.hpp           mx/assertion.cpp           # Assertion
  mx/mx_tools.hpp            mx/mx_tools.cpp

  # A dynamically created function with AD capabilities
  function/io_interface.hpp                                   # Input/output interface for Function and FunctionInternal
  function/io_scheme.hpp           function/io_scheme.cpp           function/io_scheme_internal.hpp           function/io_scheme_internal.cpp 
  function/function.hpp                  function/function.cpp                  function/function_internal.hpp                  function/function_internal.cpp
  function/x_function_internal.hpp                            # Base class for SXFunction and MXFunction
  function/sx_function.hpp         function/sx_function.cpp         function/sx_function_internal.hpp         function/sx_function_internal.cpp
  function/mx_function.hpp         function/mx_function.cpp         function/mx_function_internal.hpp         function/mx_function_internal.cpp
  function/custom_function.hpp     function/custom_function.cpp     function/custom_function_internal.hpp     function/custom_function_internal.cpp
  function/external_function.hpp   function/external_function.cpp   function/external_function_internal.hpp   function/external_function_internal.cpp
  function/linear_solver.hpp       function/linear_solver.cpp       function/linear_solver_internal.hpp       function/linear_solver_internal.cpp
  function/symbolic_qr.hpp         function/symbolic_qr.cpp         function/symbolic_qr_internal.hpp         function/symbolic_qr_internal.cpp
  function/implicit_function.hpp   function/implicit_function.cpp   function/implicit_function_internal.hpp   function/implicit_function_internal.cpp
  function/integrator.hpp          function/integrator.cpp          function/integrator_internal.hpp          function/integrator_internal.cpp
  function/nlp_solver.hpp          function/nlp_solver.cpp          function/nlp_solver_internal.hpp          function/nlp_solver_internal.cpp
  function/homotopy_nlp_solver.hpp function/homotopy_nlp_solver.cpp function/homotopy_nlp_internal.hpp function/homotopy_nlp_internal.cpp
  function/simulator.hpp           function/simulator.cpp           function/simulator_internal.hpp           function/simulator_internal.cpp
  function/control_simulator.hpp   function/control_simulator.cpp   function/control_simulator_internal.hpp   function/control_simulator_internal.cpp
  function/parallelizer.hpp        function/parallelizer.cpp        function/parallelizer_internal.hpp        function/parallelizer_internal.cpp
  function/ocp_solver.hpp          function/ocp_solver.cpp          function/ocp_solver_internal.hpp          function/ocp_solver_internal.cpp
  function/qp_solver.hpp           function/qp_solver.cpp           function/qp_solver_internal.hpp           function/qp_solver_internal.cpp
  function/stabilized_qp_solver.hpp    function/stabilized_qp_solver.cpp    function/stabilized_qp_solver_internal.hpp function/stabilized_qp_solver_internal.cpp
  function/sdp_solver.hpp          function/sdp_solver.cpp          function/sdp_solver_internal.hpp          function/sdp_solver_internal.cpp
  function/sdqp_solver.hpp         function/sdqp_solver.cpp         function/sdqp_solver_internal.hpp         function/sdqp_solver_internal.cpp
  function/socp_solver.hpp         function/socp_solver.cpp         function/socp_solver_internal.hpp         function/socp_solver_internal.cpp
  function/qcqp_solver.hpp         function/qcqp_solver.cpp         function/qcqp_solver_internal.hpp         function/qcqp_solver_internal.cpp
  function/lp_solver.hpp           function/lp_solver.cpp           function/lp_internal.hpp                  function/lp_internal.cpp
  function/code_generator.hpp      function/code_generator.cpp
  function/nullspace.hpp           function/nullspace.cpp           function/nullspace_internal.hpp           function/nullspace_internal.cpp

  # User include class with the most essential includes
  casadi.hpp
  
  function/schemes_metadata.hpp function/schemes_metadata.cpp function/schemes_helpers.hpp
  
)

set_source_files_properties( ${RUNTIME_EMBEDDED_SRC} PROPERTIES GENERATED TRUE )

if(ENABLE_STATIC)
add_library(casadi STATIC ${CASADI_SRCS} ${RUNTIME_EMBEDDED_SRC})
endif(ENABLE_STATIC)
if(ENABLE_SHARED)
add_library(casadi SHARED ${CASADI_SRCS} ${RUNTIME_EMBEDDED_SRC})
endif(ENABLE_SHARED)

add_dependencies(casadi casadi_runtime_embedded)

install(TARGETS casadi
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
install(DIRECTORY ./                                                                                                                                                                                          
   DESTINATION include/casadi/symbolic                                                                                                                                                                          
   FILES_MATCHING PATTERN "*.hpp"                                                                                                                                                                             
   PATTERN ".svn" EXCLUDE                                                                                                                                                                                     
)                                                                                                                                                                                                             
                 
