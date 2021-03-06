cmake_minimum_required(VERSION 2.6)
project(casadi C CXX)
set(PACKAGE_NAME "CasADi")
set(PACKAGE_VERSION "1.9.0")
set(PACKAGE_DESCRIPTION "CasADi is a symbolic framework for automatic differentation and numeric optimization")
set(PACKAGE_AUTHOR "Joel Andersson")
set(PACKAGE_MAINTAINER "Joris Gillis")

# For systems with git installed, find out revsion and description.
execute_process(COMMAND git rev-parse HEAD
OUTPUT_VARIABLE git_revision
OUTPUT_STRIP_TRAILING_WHITESPACE
ERROR_QUIET
)

execute_process(COMMAND git describe HEAD
OUTPUT_VARIABLE git_describe
OUTPUT_STRIP_TRAILING_WHITESPACE
ERROR_QUIET
)

STRING(REPLACE "+-" "+" git_describe "${git_describe}")
STRING(REPLACE "-g" "." git_describe "${git_describe}")

#begin workaround for http://public.kitware.com/Bug/print_bug_page.php?bug_id=9220
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)
include(language_support)
workaround_9220(Fortran Fortran_language_works)
if(Fortran_language_works)
  enable_language(Fortran OPTIONAL)
endif()
#end workaround

include(embed_resources)

# find the macports python libs if they exist
if(APPLE)
  set(CMAKE_LIBRARY_PATH /opt/local/lib ${CMAKE_LIBRARY_PATH})
endif()

# Enforce cmake2.4+ style behaviour for mixed filename/full path linker directives
if(COMMAND cmake_policy)
cmake_policy(SET CMP0003 NEW)
endif()

# cmake_policy propagation rules
if(COMMAND cmake_policy)
if(POLICY CMP0011)
cmake_policy(SET CMP0011 OLD)
endif()
endif()

# cmake_policy avoid escaping in add_definitions
if(COMMAND cmake_policy)
cmake_policy(SET CMP0005 OLD)
endif()

# We use the FeatureSummary module to get a more readable CMake output
include(FeatureSummary)
if (NOT COMMAND add_feature_info)
  function(add_feature_info _name _enabled _description)
    message(STATUS "Detected: ${_name} ${_description}")
  endfunction()
  function(feature_summary)
  endfunction()
endif()

# Options:
option(ENABLE_STATIC "Compile static libraries (.a on Linux)" ON)
option(ENABLE_SHARED "Compile shared libraries (.so on Linux)" OFF)
if (WIN32)
 option(WITH_DL "Enable dynamic loading of functions" OFF)
else (WIN32)
 option(WITH_DL "Enable dynamic loading of functions" ON)
endif (WIN32)
option(WITH_DOC "Enable documentation generation" OFF)
option(WITH_PYTHON_INTERRUPTS "With interrupt handling inside python interface" OFF)
# option(WITH_GSL "Compile the GSL interface" ON)
option(WITH_OPENMP "Compile with parallelization support" OFF)
option(WITH_OOQP "Enable OOQP interface" ON)
option(WITH_SQIC "Enable SQIC interface" OFF)
option(WITH_SLICOT "Enable SLICOT interface" OFF)
option(WITH_SWIG_SPLIT "Split SWIG wrapper generation into multiple modules" OFF)
option(WITH_WORHP "Compile the WORHP interface" OFF)
option(WITH_SNOPT "Compile the SNOPT interface" OFF)
option(WITH_ACADO "Compile the interfaces to ACADO and qpOASES, if it can be found" OFF)
option(WITH_EIGEN3 "Use Eigen3 backend for matrix operations" OFF)
option(WITH_SUNDIALS "Compile the interface to Sundials (the source code for Sundials 2.5 is included)" ON)
option(WITH_QPOASES "Compile the interface to qpOASES (the source code for qpOASES 3.0beta is included)" ON)
option(WITH_DSDP "Compile the interface to DSDP (the source code for DSDP is included)" ON)
option(WITH_CSPARSE "Compile the interface to CSparse (the source code for CSparse is included)" ON)
option(WITH_IPOPT "Compile the interface to IPOPT" ON)
option(WITH_KNITRO "Compile the interface to KNITRO" ON)
option(WITH_CPLEX "Compile the interface to CPLEX" ON)
option(WITH_LAPACK "Compile the interface to LAPACK" ON)
option(WITH_OPENCL "Compile with OpenCL support" OFF)
option(WITH_PROFILING "Enable a built-in profiler to be switched used" OFF)
option(WITH_DEPRECATED "Allow usage of deprecated syntax" ON)
option(WITH_COVERAGE "Create coverage report" OFF)

# For code optimization
if(CMAKE_BUILD_TYPE)
else(CMAKE_BUILD_TYPE)
 set(CMAKE_BUILD_TYPE Release)
 #set(CMAKE_BUILD_TYPE Debug)
endif(CMAKE_BUILD_TYPE)
string (TOUPPER ${CMAKE_BUILD_TYPE} UPPER_CMAKE_BUILD_TYPE)

# Necessary for Visual C++
add_definitions(-D_USE_MATH_DEFINES)
add_definitions(-D_SCL_SECURE_NO_WARNINGS)

# Disallow Pre 1.9 syntax
if(NOT WITH_DEPRECATED)
  add_definitions(-DWITHOUT_PRE_1_9_X)
endif()

if(WITH_DL)
  add_definitions(-DWITH_DL)
endif()
add_feature_info(dynamic-loading WITH_DL "Compile with support for dynamic loading of generated functions (needed for ExternalFunction)")

if(WITH_PRINTME)
  add_definitions(-DWITH_PRINTME)
endif()

include_directories(.)


# Check if the compiler supports C++11
foreach(CXX11FLAG_TEST "" "-std=gnu++11" "-std=c++11" "-std=gnu++0x" "-std=c++0x" "-std=c++11 --DUSE_TR1_HASHMAP" "-std=c++0x -DUSE_TR1_HASHMAP")
  if(NOT USE_CXX11)
    # Try to compile test with the proposed flag
    try_compile(USE_CXX11
      ${CMAKE_BINARY_DIR}
      ${CMAKE_SOURCE_DIR}/cmake_modules/check_cxx11.cpp
      CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${CXX11FLAG_TEST}
      OUTPUT_VARIABLE OUTPUT)

    # Save flag, if successful
    if(USE_CXX11)
      set(CXX11FLAG ${CXX11FLAG_TEST} CACHE INTERNAL "C++11 compile flag")
    endif()
  endif()
endforeach()

# If found, set flag
if(USE_CXX11)
  if(CXX11FLAG)
    message(STATUS "Flag needed for enabling C++11 features: ${CXX11FLAG}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11FLAG}")
  else()
    message(STATUS "No flag needed for enabling C++11 features.")
  endif()
  add_definitions(-DUSE_CXX11)
endif()
add_feature_info(using-c++11 USE_CXX11 "Using C++11 features (improves efficiency and is required for some examples).")

if(CXX11FLAG)
  try_compile(HAS_COPYSIGN
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/cmake_modules/check_copysign.cpp
    CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${CXX11FLAG}
    OUTPUT_VARIABLE OUTPUT)
  if(HAS_COPYSIGN)
    add_definitions(-DHAS_COPYSIGN)
  endif()

  try_compile(HAS_ERF
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/cmake_modules/check_erf.cpp
    CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${CXX11FLAG}
    OUTPUT_VARIABLE OUTPUT)
  if(HAS_ERF)
    add_definitions(-DHAS_ERF)
  endif()

  try_compile(HAS_ERFINV
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/cmake_modules/check_erfinv.cpp
    CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${CXX11FLAG}
    OUTPUT_VARIABLE OUTPUT)
  if(HAS_ERFINV)
    add_definitions(-DHAS_ERFINV)
  endif()
endif()


# set(CMAKE_VERBOSE_MAKEFILE 0)

# add compiler warnings
if(    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"
    OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"
    OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel"
  )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter -Wno-sign-compare -Wno-delete-non-virtual-dtor")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # I don't know the MSVC warnings, so do nothing for now
endif()

# the following commands are needed to fix a problem with the libraries
# for linux 64 bits
if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
  message(STATUS "x86_64 architecture detected - setting flag -fPIC")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
  set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -fPIC")
endif("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")

if(WITH_COVERAGE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS  " -lgcov -fprofile-arcs --coverage ${CMAKE_EXE_LINKER_FLAGS}" )
endif()

if(MINGW)
  # Circumventing a bug in MinGW g++ v4.7.2, evoked by 752fa89355ffa
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-ipa-cp-clone")
endif()

# Use the included Sundials
if(WITH_SUNDIALS)
  set(SUNDIALS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external_packages/sundials-2.5mod)
  set(SUNDIALS_LIBRARIES casadi_sundials)
endif()
add_feature_info(sundials-interface WITH_SUNDIALS "Interface to the ODE/DAE integrator suite SUNDIALS.")

# Use the included csparse
if(WITH_CSPARSE)
  set(CSPARSE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external_packages/CSparse/Include)
  set(CSPARSE_LIBRARIES casadi_csparse)
endif()
add_feature_info(csparse-interface WITH_CSPARSE "Interface to the sparse direct linear solver CSparse.")

# TinyXML
set(TINYXML_LIBRARIES casadi_tinyxml)

# enabling openmp support if requesed
if(WITH_OPENMP)
  find_package (OpenMP)
  if(OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -DWITH_OPENMP")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS} -DWITH_OPENMP")
  endif()
endif()

#SET(LIBRARY_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/lib)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib/)

if(WITH_DL)
  # Core needs support for dynamic linking
  set(CASADI_DEPENDENCIES ${CMAKE_DL_LIBS})
else(WITH_DL)
  # No dependencies
  set(CASADI_DEPENDENCIES)
endif(WITH_DL)

# OpenCL
if(WITH_OPENCL)
  # Core depends on OpenCL for GPU calculations
  find_package(OpenCL REQUIRED)
  set(CASADI_DEPENDENCIES ${CASADI_DEPENDENCIES} ${OPENCL_LIBRARIES})
  add_definitions(-DWITH_OPENCL)
  include_directories(${OPENCL_INCLUDE_DIRS})
endif(WITH_OPENCL)
add_feature_info(opencl-support WITH_OPENCL "Enable just-in-time compiliation to CPUs and GPUs with OpenCL.")

# Optional auxillary dependencies
find_package(BLAS QUIET)
find_package(LibXml2)
if(WITH_LAPACK)
  find_package(LAPACK)
endif()
add_feature_info(lapack-interface LAPACK_FOUND "Interface to LAPACK.")

if(WITH_IPOPT)
  find_package(IPOPT)
endif()
add_feature_info(ipopt-interface IPOPT_FOUND "Interface to the NLP solver Ipopt.")

if(WITH_KNITRO)
  find_package(KNITRO)
endif(WITH_KNITRO)
add_feature_info(knitro-interface KNITRO_FOUND "Interface to the NLP solver KNITRO.")

if(WITH_CPLEX)
  find_package(CPLEX)
endif(WITH_CPLEX)
add_feature_info(cplex-interface CPLEX_FOUND "Interface to the QP solver CPLEX.")

if(WITH_SNOPT)
  find_package(SNOPT)
endif(WITH_SNOPT)
add_feature_info(snopt-interface SNOPT_FOUND "Interface to SNOPT.")

# if(WITH_GSL)
#   find_package (GSL)
# endif()

# Use the included qpOASES
if(WITH_QPOASES AND BLAS_FOUND AND LAPACK_FOUND)
  set(QPOASES_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external_packages/qpOASES/include)
  set(QPOASES_LIBRARIES casadi_qpoases)
  set(QPOASES_FOUND true)
endif()
add_feature_info(qpoases-interface QPOASES_FOUND "Interface to the active-set QP solver qpOASES.")

if(WITH_OOQP AND BLAS_FOUND)
  find_package (OOQP)
endif()
add_feature_info(ooqp-interface OOQP_FOUND "Interface to the QP solver OOQP (requires BLAS).")

if(Fortran_language_works AND WITH_SQIC)
  find_package (SQIC)
  set(CASADI_DEPENDENCIES ${CASADI_DEPENDENCIES} ${SQIC_LIBRARIES})
endif()
add_feature_info(sqic-interface SQIC_FOUND "Interface to the QP solver SQIC.")

if(Fortran_language_works AND WITH_SLICOT)
  find_package (SLICOT)
  set(CASADI_DEPENDENCIES ${CASADI_DEPENDENCIES} ${SLICOT_LIBRARIES})
endif()
add_feature_info(slicot-interface SLICOT_FOUND "Interface to the controls library SLICOT.")


if(WITH_WORHP AND LIBXML2_FOUND)
  find_package (WORHP)
endif()
add_feature_info(worhp-inteface WORHP_FOUND "Interface to the NLP solver Worhp (requires LibXml2 headers).")

# Use the included dsdp
if(WITH_DSDP AND BLAS_FOUND AND LAPACK_FOUND)
  set(DSDP_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external_packages/DSDP/include)
  set(DSDP_LIBRARIES casadi_dsdp)
  set(DSDP_FOUND true)
endif()
add_feature_info(dsdp-interface DSDP_FOUND "Interface to the interior point SDP solver DSDP (requires BLAS and LAPACK).")

if(WITH_PROFILING)
  find_library(RT rt)
  if(RT)
    list(APPEND CASADI_DEPENDENCIES ${RT})
  endif()
  add_definitions(-DWITH_PROFILING)
endif(WITH_PROFILING)

add_subdirectory(symbolic)  # needed by all except external_packages
add_subdirectory(external_packages)

add_subdirectory(interfaces)             # needs external_packages
add_subdirectory(nonlinear_programming)  # needs interfaces
add_subdirectory(convex_programming)     # needs interfaces
add_subdirectory(integration)
add_subdirectory(optimal_control)        # needs integration, external_packages
add_subdirectory(examples)
add_subdirectory(experimental/greg EXCLUDE_FROM_ALL)
add_subdirectory(experimental/joel EXCLUDE_FROM_ALL)
#add_subdirectory(experimental/andrew EXCLUDE_FROM_ALL)

add_subdirectory(control)

add_subdirectory(misc)

find_package(SWIG)
  if(SWIG_FOUND)
    add_subdirectory(swig EXCLUDE_FROM_ALL) # the swig interfaces are not compiled when typing "make"
    add_custom_target(python DEPENDS _python_modules )
    add_custom_target(octave DEPENDS _octave_modules )
    add_custom_target(haskell DEPENDS _haskell_modules )
endif(SWIG_FOUND)

if(WITH_DOC)
  set(DOXYFILE_LATEX "NO")
  set(DOXYFILE_IN_DIR ${CMAKE_SOURCE_DIR}/documentation/api-doc)
  set(DOXYFILE_OUTPUT_DIR  ${CMAKE_SOURCE_DIR}/documentation/api-doc)
  set(DOXYFILE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/symbolic)
  include(UseDoxygen OPTIONAL)
  add_subdirectory(documentation/tutorials EXCLUDE_FROM_ALL)
  add_custom_target(tutor)
endif()

add_subdirectory(documentation/examples/ctemplate)

# Print a summary
feature_summary(WHAT ALL)
feature_summary(WHAT ENABLED_FEATURES VAR feature_list)

STRING(REPLACE "\n" "\\n" feature_list "${feature_list}")

# Pass meta information
CONFIGURE_FILE(
  ${CMAKE_SOURCE_DIR}/symbolic/casadi_meta.cpp.cmake
  ${CMAKE_SOURCE_DIR}/symbolic/casadi_meta.cpp
  ESCAPE_QUOTES
)

if(EXTRA_CMAKE)
  include(${EXTRA_CMAKE})
endif()
