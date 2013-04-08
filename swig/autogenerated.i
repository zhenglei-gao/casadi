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

/** All edits to this file will be lost - autogenerated by misc/autogencode.py */
%include "symbolic/autogenerated.hpp"
#ifdef SWIGPYTHON
%pythoncode %{

def IOSchemeVector(arg,io_scheme):
  try:
    return IOSchemeVectorCRSSparsity(arg,io_scheme)
  except:
    pass
  try:
    return IOSchemeVectorSXMatrix(arg,io_scheme)
  except:
    pass
  try:
    return IOSchemeVectorMX(arg,io_scheme)
  except:
    pass
%}
#endif //SWIGPYTHON
#ifdef SWIGPYTHON
%pythoncode %{
def acadoIn(*dummy,**kwargs):
  """
  Helper function for 'ACADO_Input'

  Input arguments of an ACADO OCP solver
  
  Keyword arguments:
    x_guess -- Initial guess for x (default: 0) [ACADO_X_GUESS]
    u_guess -- Initial guess for u (default: 0) [ACADO_U_GUESS]
    p_guess -- Initial guess for p (default: 0) [ACADO_P_GUESS]
    lbx     -- Lower bound on x (default:  -infinity) [ACADO_LBX]
    ubx     -- Upper bound on x (default:  infinity) [ACADO_UBX]
    lbx0    -- Lower bound on x0 (default:  -infinity) [ACADO_LBX0]
    ubx0    -- Upper bound on x0 (default:  infinity) [ACADO_UBX0]
    lbxf    -- Lower bound on xf (default:  -infinity) [ACADO_LBXF]
    ubxf    -- Upper bound on xf (default:  infinity) [ACADO_UBXF]
    lbu     -- Lower bound on u (default:  -infinity) [ACADO_LBU]
    ubu     -- Upper bound on u (default:  infinity) [ACADO_UBU]
    lbp     -- Lower bound on p (default:  -infinity) [ACADO_LBP]
    ubp     -- Upper bound on p (default:  infinity) [ACADO_UBP]
    lbc     -- Lower bound on the path constraint function (default:  -infinity) [ACADO_LBC]
    ubc     -- Upper bound on the path constraint function (default:  infinity) [ACADO_UBC]
    lbr     -- Lower bound on the initial constraint function (default:  0) [ACADO_LBR]
    ubr     -- Upper bound on the initial constraint function (default:  0) [ACADO_UBR]
  """
  if(len(dummy)>0): raise Exception("Error in acadoIn: syntax has become more strict. You must use keyword arguments now, for your own safety.\n acadoIn(my_x_guess, my_u_guess, my_p_guess, my_lbx, my_ubx, my_lbx0, my_ubx0, my_lbxf, my_ubxf, my_lbu, my_ubu, my_lbp, my_ubp, my_lbc, my_ubc, my_lbr, my_ubr)\nmust be written\n acadoIn(x_guess=my_x_guess, u_guess=my_u_guess, p_guess=my_p_guess, lbx=my_lbx, ubx=my_ubx, lbx0=my_lbx0, ubx0=my_ubx0, lbxf=my_lbxf, ubxf=my_ubxf, lbu=my_lbu, ubu=my_ubu, lbp=my_lbp, ubp=my_ubp, lbc=my_lbc, ubc=my_ubc, lbr=my_lbr, ubr=my_ubr)\nwhere any keyword is optional.")
  x_guess = []
  if 'x_guess' in kwargs:
    x_guess = kwargs['x_guess']
  u_guess = []
  if 'u_guess' in kwargs:
    u_guess = kwargs['u_guess']
  p_guess = []
  if 'p_guess' in kwargs:
    p_guess = kwargs['p_guess']
  lbx = []
  if 'lbx' in kwargs:
    lbx = kwargs['lbx']
  ubx = []
  if 'ubx' in kwargs:
    ubx = kwargs['ubx']
  lbx0 = []
  if 'lbx0' in kwargs:
    lbx0 = kwargs['lbx0']
  ubx0 = []
  if 'ubx0' in kwargs:
    ubx0 = kwargs['ubx0']
  lbxf = []
  if 'lbxf' in kwargs:
    lbxf = kwargs['lbxf']
  ubxf = []
  if 'ubxf' in kwargs:
    ubxf = kwargs['ubxf']
  lbu = []
  if 'lbu' in kwargs:
    lbu = kwargs['lbu']
  ubu = []
  if 'ubu' in kwargs:
    ubu = kwargs['ubu']
  lbp = []
  if 'lbp' in kwargs:
    lbp = kwargs['lbp']
  ubp = []
  if 'ubp' in kwargs:
    ubp = kwargs['ubp']
  lbc = []
  if 'lbc' in kwargs:
    lbc = kwargs['lbc']
  ubc = []
  if 'ubc' in kwargs:
    ubc = kwargs['ubc']
  lbr = []
  if 'lbr' in kwargs:
    lbr = kwargs['lbr']
  ubr = []
  if 'ubr' in kwargs:
    ubr = kwargs['ubr']
  for k in kwargs.keys():
    if not(k in ['x_guess','u_guess','p_guess','lbx','ubx','lbx0','ubx0','lbxf','ubxf','lbu','ubu','lbp','ubp','lbc','ubc','lbr','ubr']):
      raise Exception("Keyword error in acadoIn: '%s' is not recognized. Available keywords are: x_guess, u_guess, p_guess, lbx, ubx, lbx0, ubx0, lbxf, ubxf, lbu, ubu, lbp, ubp, lbc, ubc, lbr, ubr" % k )
  return IOSchemeVector([x_guess,u_guess,p_guess,lbx,ubx,lbx0,ubx0,lbxf,ubxf,lbu,ubu,lbp,ubp,lbc,ubc,lbr,ubr], SCHEME_ACADO_Input)
%}
#endif //SWIGPYTHON
#ifndef SWIGPYTHON
namespace CasADi {
%template(acadoIn) acadoIn<SXMatrix>;
%template(acadoIn) acadoIn<MX>;
}
#endif //SWIGPYTHON
#ifdef SWIGPYTHON
%pythoncode %{
def acadoOut(*dummy,**kwargs):
  """
  Helper function for 'ACADO_Output'

  Output arguments of an ACADO OCP solver
  
  Keyword arguments:
    x_opt -- Optimal states [ACADO_X_OPT]
    u_opt -- Optimal control inputs [ACADO_U_OPT]
    p_opt -- Optimal parameters [ACADO_P_OPT]
    cost  -- Optimal cost [ACADO_COST]
  """
  if(len(dummy)>0): raise Exception("Error in acadoOut: syntax has become more strict. You must use keyword arguments now, for your own safety.\n acadoOut(my_x_opt, my_u_opt, my_p_opt, my_cost)\nmust be written\n acadoOut(x_opt=my_x_opt, u_opt=my_u_opt, p_opt=my_p_opt, cost=my_cost)\nwhere any keyword is optional.")
  x_opt = []
  if 'x_opt' in kwargs:
    x_opt = kwargs['x_opt']
  u_opt = []
  if 'u_opt' in kwargs:
    u_opt = kwargs['u_opt']
  p_opt = []
  if 'p_opt' in kwargs:
    p_opt = kwargs['p_opt']
  cost = []
  if 'cost' in kwargs:
    cost = kwargs['cost']
  for k in kwargs.keys():
    if not(k in ['x_opt','u_opt','p_opt','cost']):
      raise Exception("Keyword error in acadoOut: '%s' is not recognized. Available keywords are: x_opt, u_opt, p_opt, cost" % k )
  return IOSchemeVector([x_opt,u_opt,p_opt,cost], SCHEME_ACADO_Output)
%}
#endif //SWIGPYTHON
#ifndef SWIGPYTHON
namespace CasADi {
%template(acadoOut) acadoOut<SXMatrix>;
%template(acadoOut) acadoOut<MX>;
}
#endif //SWIGPYTHON
#ifdef SWIGPYTHON
%pythoncode %{
def acadofcnIn(*dummy,**kwargs):
  """
  Helper function for 'ACADO_FCN_Input'

  Input arguments of an ACADO function
  
  Keyword arguments:
    t    -- Time [ACADO_FCN_T]
    xd   -- Differential state [ACADO_FCN_XD]
    xa   -- Algebraic state [ACADO_FCN_XA]
    u    -- Control input [ACADO_FCN_U]
    p    -- Parameter [ACADO_FCN_P]
    xdot -- Differential state derivative [ACADO_FCN_XDOT]
  """
  if(len(dummy)>0): raise Exception("Error in acadofcnIn: syntax has become more strict. You must use keyword arguments now, for your own safety.\n acadofcnIn(my_t, my_xd, my_xa, my_u, my_p, my_xdot)\nmust be written\n acadofcnIn(t=my_t, xd=my_xd, xa=my_xa, u=my_u, p=my_p, xdot=my_xdot)\nwhere any keyword is optional.")
  t = []
  if 't' in kwargs:
    t = kwargs['t']
  xd = []
  if 'xd' in kwargs:
    xd = kwargs['xd']
  xa = []
  if 'xa' in kwargs:
    xa = kwargs['xa']
  u = []
  if 'u' in kwargs:
    u = kwargs['u']
  p = []
  if 'p' in kwargs:
    p = kwargs['p']
  xdot = []
  if 'xdot' in kwargs:
    xdot = kwargs['xdot']
  for k in kwargs.keys():
    if not(k in ['t','xd','xa','u','p','xdot']):
      raise Exception("Keyword error in acadofcnIn: '%s' is not recognized. Available keywords are: t, xd, xa, u, p, xdot" % k )
  return IOSchemeVector([t,xd,xa,u,p,xdot], SCHEME_ACADO_FCN_Input)
%}
#endif //SWIGPYTHON
#ifndef SWIGPYTHON
namespace CasADi {
%template(acadofcnIn) acadofcnIn<SXMatrix>;
%template(acadofcnIn) acadofcnIn<MX>;
}
#endif //SWIGPYTHON
#ifdef SWIGPYTHON
%pythoncode %{
def controldaeIn(*dummy,**kwargs):
  """
  Helper function for 'ControlledDAEInput'

  Input arguments of an ODE/DAE function
  
  Keyword arguments:
    t        -- Global physical time. (1-by-1) [CONTROL_DAE_T]
    x        -- State vector (dimension nx-by-1). Should have same amount of non-zeros as DAEOutput:DAE_RES [CONTROL_DAE_X]
    z        -- Algebraic state vector (dimension np-by-1). [CONTROL_DAE_Z]
    p        -- Parameter vector (dimension np-by-1). [CONTROL_DAE_P]
    u        -- Control vector (dimension nu-by-1). [CONTROL_DAE_U]
    u_interp -- Control vector, linearly interpolated (dimension nu-by-1). [CONTROL_DAE_U_INTERP]
    x_major  -- State vector (dimension nx-by-1) at the last major time-step [CONTROL_DAE_X_MAJOR]
    t0       -- Time at start of control interval (1-by-1) [CONTROL_DAE_T0]
    tf       -- Time at end of control interval (1-by-1) [CONTROL_DAE_TF]
  """
  if(len(dummy)>0): raise Exception("Error in controldaeIn: syntax has become more strict. You must use keyword arguments now, for your own safety.\n controldaeIn(my_t, my_x, my_z, my_p, my_u, my_u_interp, my_x_major, my_t0, my_tf)\nmust be written\n controldaeIn(t=my_t, x=my_x, z=my_z, p=my_p, u=my_u, u_interp=my_u_interp, x_major=my_x_major, t0=my_t0, tf=my_tf)\nwhere any keyword is optional.")
  t = []
  if 't' in kwargs:
    t = kwargs['t']
  x = []
  if 'x' in kwargs:
    x = kwargs['x']
  z = []
  if 'z' in kwargs:
    z = kwargs['z']
  p = []
  if 'p' in kwargs:
    p = kwargs['p']
  u = []
  if 'u' in kwargs:
    u = kwargs['u']
  u_interp = []
  if 'u_interp' in kwargs:
    u_interp = kwargs['u_interp']
  x_major = []
  if 'x_major' in kwargs:
    x_major = kwargs['x_major']
  t0 = []
  if 't0' in kwargs:
    t0 = kwargs['t0']
  tf = []
  if 'tf' in kwargs:
    tf = kwargs['tf']
  for k in kwargs.keys():
    if not(k in ['t','x','z','p','u','u_interp','x_major','t0','tf']):
      raise Exception("Keyword error in controldaeIn: '%s' is not recognized. Available keywords are: t, x, z, p, u, u_interp, x_major, t0, tf" % k )
  return IOSchemeVector([t,x,z,p,u,u_interp,x_major,t0,tf], SCHEME_ControlledDAEInput)
%}
#endif //SWIGPYTHON
#ifndef SWIGPYTHON
namespace CasADi {
%template(controldaeIn) controldaeIn<SXMatrix>;
%template(controldaeIn) controldaeIn<MX>;
}
#endif //SWIGPYTHON
#ifdef SWIGPYTHON
%pythoncode %{
def controlsimulatorIn(*dummy,**kwargs):
  """
  Helper function for 'ControlSimulatorInput'

  Input arguments of a control simulator
  
  Keyword arguments:
    x0 -- Differential or algebraic state at t0  (dimension nx-by-1) [CONTROLSIMULATOR_X0]
    p  -- Parameters that are fixed over the entire horizon  (dimension np-by-1) [CONTROLSIMULATOR_P]
    u  -- Parameters that change over the integration intervals (dimension (ns-1)-by-nu) [CONTROLSIMULATOR_U]
  """
  if(len(dummy)>0): raise Exception("Error in controlsimulatorIn: syntax has become more strict. You must use keyword arguments now, for your own safety.\n controlsimulatorIn(my_x0, my_p, my_u)\nmust be written\n controlsimulatorIn(x0=my_x0, p=my_p, u=my_u)\nwhere any keyword is optional.")
  x0 = []
  if 'x0' in kwargs:
    x0 = kwargs['x0']
  p = []
  if 'p' in kwargs:
    p = kwargs['p']
  u = []
  if 'u' in kwargs:
    u = kwargs['u']
  for k in kwargs.keys():
    if not(k in ['x0','p','u']):
      raise Exception("Keyword error in controlsimulatorIn: '%s' is not recognized. Available keywords are: x0, p, u" % k )
  return IOSchemeVector([x0,p,u], SCHEME_ControlSimulatorInput)
%}
#endif //SWIGPYTHON
#ifndef SWIGPYTHON
namespace CasADi {
%template(controlsimulatorIn) controlsimulatorIn<SXMatrix>;
%template(controlsimulatorIn) controlsimulatorIn<MX>;
}
#endif //SWIGPYTHON
#ifdef SWIGPYTHON
%pythoncode %{
def daeIn(*dummy,**kwargs):
  """
  Helper function for 'DAEInput'

  Input arguments of an ODE/DAE function
  
  Keyword arguments:
    x -- Differential state [DAE_X]
    z -- Algebraic state [DAE_Z]
    p -- Parameter [DAE_P]
    t -- Explicit time dependence [DAE_T]
  """
  if(len(dummy)>0): raise Exception("Error in daeIn: syntax has become more strict. You must use keyword arguments now, for your own safety.\n daeIn(my_x, my_z, my_p, my_t)\nmust be written\n daeIn(x=my_x, z=my_z, p=my_p, t=my_t)\nwhere any keyword is optional.")
  x = []
  if 'x' in kwargs:
    x = kwargs['x']
  z = []
  if 'z' in kwargs:
    z = kwargs['z']
  p = []
  if 'p' in kwargs:
    p = kwargs['p']
  t = []
  if 't' in kwargs:
    t = kwargs['t']
  for k in kwargs.keys():
    if not(k in ['x','z','p','t']):
      raise Exception("Keyword error in daeIn: '%s' is not recognized. Available keywords are: x, z, p, t" % k )
  return IOSchemeVector([x,z,p,t], SCHEME_DAEInput)
%}
#endif //SWIGPYTHON
#ifndef SWIGPYTHON
namespace CasADi {
%template(daeIn) daeIn<SXMatrix>;
%template(daeIn) daeIn<MX>;
}
#endif //SWIGPYTHON
#ifdef SWIGPYTHON
%pythoncode %{
def daeOut(*dummy,**kwargs):
  """
  Helper function for 'DAEOutput'

  Output arguments of an DAE function
  
  Keyword arguments:
    ode  -- Right hand side of the implicit ODE [DAE_ODE]
    alg  -- Right hand side of algebraic equations [DAE_ALG]
    quad -- Right hand side of quadratures equations [DAE_QUAD]
  """
  if(len(dummy)>0): raise Exception("Error in daeOut: syntax has become more strict. You must use keyword arguments now, for your own safety.\n daeOut(my_ode, my_alg, my_quad)\nmust be written\n daeOut(ode=my_ode, alg=my_alg, quad=my_quad)\nwhere any keyword is optional.")
  ode = []
  if 'ode' in kwargs:
    ode = kwargs['ode']
  alg = []
  if 'alg' in kwargs:
    alg = kwargs['alg']
  quad = []
  if 'quad' in kwargs:
    quad = kwargs['quad']
  for k in kwargs.keys():
    if not(k in ['ode','alg','quad']):
      raise Exception("Keyword error in daeOut: '%s' is not recognized. Available keywords are: ode, alg, quad" % k )
  return IOSchemeVector([ode,alg,quad], SCHEME_DAEOutput)
%}
#endif //SWIGPYTHON
#ifndef SWIGPYTHON
namespace CasADi {
%template(daeOut) daeOut<SXMatrix>;
%template(daeOut) daeOut<MX>;
}
#endif //SWIGPYTHON
#ifdef SWIGPYTHON
%pythoncode %{
def rdaeIn(*dummy,**kwargs):
  """
  Helper function for 'RDAEInput'

  Input arguments of an ODE/DAE backward integration function
  
  Keyword arguments:
    rx -- Backward differential state [RDAE_RX]
    rz -- Backward algebraic state [RDAE_RZ]
    rp -- Backward  parameter vector [RDAE_RP]
    x  -- Forward differential state [RDAE_X]
    z  -- Forward algebraic state [RDAE_Z]
    p  -- Parameter vector [RDAE_P]
    t  -- Explicit time dependence [RDAE_T]
  """
  if(len(dummy)>0): raise Exception("Error in rdaeIn: syntax has become more strict. You must use keyword arguments now, for your own safety.\n rdaeIn(my_rx, my_rz, my_rp, my_x, my_z, my_p, my_t)\nmust be written\n rdaeIn(rx=my_rx, rz=my_rz, rp=my_rp, x=my_x, z=my_z, p=my_p, t=my_t)\nwhere any keyword is optional.")
  rx = []
  if 'rx' in kwargs:
    rx = kwargs['rx']
  rz = []
  if 'rz' in kwargs:
    rz = kwargs['rz']
  rp = []
  if 'rp' in kwargs:
    rp = kwargs['rp']
  x = []
  if 'x' in kwargs:
    x = kwargs['x']
  z = []
  if 'z' in kwargs:
    z = kwargs['z']
  p = []
  if 'p' in kwargs:
    p = kwargs['p']
  t = []
  if 't' in kwargs:
    t = kwargs['t']
  for k in kwargs.keys():
    if not(k in ['rx','rz','rp','x','z','p','t']):
      raise Exception("Keyword error in rdaeIn: '%s' is not recognized. Available keywords are: rx, rz, rp, x, z, p, t" % k )
  return IOSchemeVector([rx,rz,rp,x,z,p,t], SCHEME_RDAEInput)
%}
#endif //SWIGPYTHON
#ifndef SWIGPYTHON
namespace CasADi {
%template(rdaeIn) rdaeIn<SXMatrix>;
%template(rdaeIn) rdaeIn<MX>;
}
#endif //SWIGPYTHON
#ifdef SWIGPYTHON
%pythoncode %{
def rdaeOut(*dummy,**kwargs):
  """
  Helper function for 'RDAEOutput'

  Output arguments of an ODE/DAE backward integration function
  
  Keyword arguments:
    ode  -- Right hand side of ODE. [RDAE_ODE]
    alg  -- Right hand side of algebraic equations. [RDAE_ALG]
    quad -- Right hand side of quadratures. [RDAE_QUAD]
  """
  if(len(dummy)>0): raise Exception("Error in rdaeOut: syntax has become more strict. You must use keyword arguments now, for your own safety.\n rdaeOut(my_ode, my_alg, my_quad)\nmust be written\n rdaeOut(ode=my_ode, alg=my_alg, quad=my_quad)\nwhere any keyword is optional.")
  ode = []
  if 'ode' in kwargs:
    ode = kwargs['ode']
  alg = []
  if 'alg' in kwargs:
    alg = kwargs['alg']
  quad = []
  if 'quad' in kwargs:
    quad = kwargs['quad']
  for k in kwargs.keys():
    if not(k in ['ode','alg','quad']):
      raise Exception("Keyword error in rdaeOut: '%s' is not recognized. Available keywords are: ode, alg, quad" % k )
  return IOSchemeVector([ode,alg,quad], SCHEME_RDAEOutput)
%}
#endif //SWIGPYTHON
#ifndef SWIGPYTHON
namespace CasADi {
%template(rdaeOut) rdaeOut<SXMatrix>;
%template(rdaeOut) rdaeOut<MX>;
}
#endif //SWIGPYTHON
#ifdef SWIGPYTHON
%pythoncode %{
def integratorIn(*dummy,**kwargs):
  """
  Helper function for 'IntegratorInput'

  Input arguments of an integrator
  
  Keyword arguments:
    x0  -- Differential state at the initial time [INTEGRATOR_X0]
    p   -- Parameters [INTEGRATOR_P]
    rx0 -- Backward differential state at the final time [INTEGRATOR_RX0]
    rp  -- Backward parameter vector [INTEGRATOR_RP]
  """
  if(len(dummy)>0): raise Exception("Error in integratorIn: syntax has become more strict. You must use keyword arguments now, for your own safety.\n integratorIn(my_x0, my_p, my_rx0, my_rp)\nmust be written\n integratorIn(x0=my_x0, p=my_p, rx0=my_rx0, rp=my_rp)\nwhere any keyword is optional.")
  x0 = []
  if 'x0' in kwargs:
    x0 = kwargs['x0']
  p = []
  if 'p' in kwargs:
    p = kwargs['p']
  rx0 = []
  if 'rx0' in kwargs:
    rx0 = kwargs['rx0']
  rp = []
  if 'rp' in kwargs:
    rp = kwargs['rp']
  for k in kwargs.keys():
    if not(k in ['x0','p','rx0','rp']):
      raise Exception("Keyword error in integratorIn: '%s' is not recognized. Available keywords are: x0, p, rx0, rp" % k )
  return IOSchemeVector([x0,p,rx0,rp], SCHEME_IntegratorInput)
%}
#endif //SWIGPYTHON
#ifndef SWIGPYTHON
namespace CasADi {
%template(integratorIn) integratorIn<SXMatrix>;
%template(integratorIn) integratorIn<MX>;
}
#endif //SWIGPYTHON
#ifdef SWIGPYTHON
%pythoncode %{
def integratorOut(*dummy,**kwargs):
  """
  Helper function for 'IntegratorOutput'

  Output arguments of an integrator
  
  Keyword arguments:
    xf  -- Differential state at the final time [INTEGRATOR_XF]
    qf  -- Quadrature state at the final time [INTEGRATOR_QF]
    rxf -- Backward differential state at the initial time [INTEGRATOR_RXF]
    rqf -- Backward quadrature state at the initial time [INTEGRATOR_RQF]
  """
  if(len(dummy)>0): raise Exception("Error in integratorOut: syntax has become more strict. You must use keyword arguments now, for your own safety.\n integratorOut(my_xf, my_qf, my_rxf, my_rqf)\nmust be written\n integratorOut(xf=my_xf, qf=my_qf, rxf=my_rxf, rqf=my_rqf)\nwhere any keyword is optional.")
  xf = []
  if 'xf' in kwargs:
    xf = kwargs['xf']
  qf = []
  if 'qf' in kwargs:
    qf = kwargs['qf']
  rxf = []
  if 'rxf' in kwargs:
    rxf = kwargs['rxf']
  rqf = []
  if 'rqf' in kwargs:
    rqf = kwargs['rqf']
  for k in kwargs.keys():
    if not(k in ['xf','qf','rxf','rqf']):
      raise Exception("Keyword error in integratorOut: '%s' is not recognized. Available keywords are: xf, qf, rxf, rqf" % k )
  return IOSchemeVector([xf,qf,rxf,rqf], SCHEME_IntegratorOutput)
%}
#endif //SWIGPYTHON
#ifndef SWIGPYTHON
namespace CasADi {
%template(integratorOut) integratorOut<SXMatrix>;
%template(integratorOut) integratorOut<MX>;
}
#endif //SWIGPYTHON
#ifdef SWIGPYTHON
%pythoncode %{
def nlpsolverIn(*dummy,**kwargs):
  """
  Helper function for 'NLPInput'

  Input arguments of an NLP Solver
  
  Keyword arguments:
    x_init      -- Decision variables initial guess (nx x 1)  [NLP_X_INIT]
    lbx         -- Decision variables lower bound (nx x 1), default -inf [NLP_LBX]
    ubx         -- Decision variables upper bound (nx x 1), default +inf [NLP_UBX]
    lbg         -- Constraints lower bound (ng x 1), default -inf [NLP_LBG]
    ubg         -- Constraints upper bound (ng x 1), default +inf [NLP_UBG]
    lambda_init -- Lagrange multipliers associated with G, initial guess (ng x 1) [NLP_LAMBDA_INIT]
    p           -- Parameters on which the objective and constraints might depend (np x 1) [NLP_P]
  """
  if(len(dummy)>0): raise Exception("Error in nlpsolverIn: syntax has become more strict. You must use keyword arguments now, for your own safety.\n nlpsolverIn(my_x_init, my_lbx, my_ubx, my_lbg, my_ubg, my_lambda_init, my_p)\nmust be written\n nlpsolverIn(x_init=my_x_init, lbx=my_lbx, ubx=my_ubx, lbg=my_lbg, ubg=my_ubg, lambda_init=my_lambda_init, p=my_p)\nwhere any keyword is optional.")
  x_init = []
  if 'x_init' in kwargs:
    x_init = kwargs['x_init']
  lbx = []
  if 'lbx' in kwargs:
    lbx = kwargs['lbx']
  ubx = []
  if 'ubx' in kwargs:
    ubx = kwargs['ubx']
  lbg = []
  if 'lbg' in kwargs:
    lbg = kwargs['lbg']
  ubg = []
  if 'ubg' in kwargs:
    ubg = kwargs['ubg']
  lambda_init = []
  if 'lambda_init' in kwargs:
    lambda_init = kwargs['lambda_init']
  p = []
  if 'p' in kwargs:
    p = kwargs['p']
  for k in kwargs.keys():
    if not(k in ['x_init','lbx','ubx','lbg','ubg','lambda_init','p']):
      raise Exception("Keyword error in nlpsolverIn: '%s' is not recognized. Available keywords are: x_init, lbx, ubx, lbg, ubg, lambda_init, p" % k )
  return IOSchemeVector([x_init,lbx,ubx,lbg,ubg,lambda_init,p], SCHEME_NLPInput)
%}
#endif //SWIGPYTHON
#ifndef SWIGPYTHON
namespace CasADi {
%template(nlpsolverIn) nlpsolverIn<SXMatrix>;
%template(nlpsolverIn) nlpsolverIn<MX>;
}
#endif //SWIGPYTHON
#ifdef SWIGPYTHON
%pythoncode %{
def nlpsolverOut(*dummy,**kwargs):
  """
  Helper function for 'NLPOutput'

  Output arguments of an NLP Solver
  
  Keyword arguments:
    x_opt    -- Decision variables for optimal solution (nx x 1) [NLP_X_OPT]
    cost     -- Objective/cost function for optimal solution (1 x 1) [NLP_COST]
    lambda_g -- Lagrange multipliers associated with G at the solution (ng x 1) [NLP_LAMBDA_G]
    lambda_x -- Lagrange multipliers associated with bounds on X at the solution (nx x 1) [NLP_LAMBDA_X]
    lambda_p -- Lagrange multipliers associated with the parameters (np x 1) [NLP_LAMBDA_P]
    g        -- The constraints evaluated at the optimal solution (ng x 1) [NLP_G]
  """
  if(len(dummy)>0): raise Exception("Error in nlpsolverOut: syntax has become more strict. You must use keyword arguments now, for your own safety.\n nlpsolverOut(my_x_opt, my_cost, my_lambda_g, my_lambda_x, my_lambda_p, my_g)\nmust be written\n nlpsolverOut(x_opt=my_x_opt, cost=my_cost, lambda_g=my_lambda_g, lambda_x=my_lambda_x, lambda_p=my_lambda_p, g=my_g)\nwhere any keyword is optional.")
  x_opt = []
  if 'x_opt' in kwargs:
    x_opt = kwargs['x_opt']
  cost = []
  if 'cost' in kwargs:
    cost = kwargs['cost']
  lambda_g = []
  if 'lambda_g' in kwargs:
    lambda_g = kwargs['lambda_g']
  lambda_x = []
  if 'lambda_x' in kwargs:
    lambda_x = kwargs['lambda_x']
  lambda_p = []
  if 'lambda_p' in kwargs:
    lambda_p = kwargs['lambda_p']
  g = []
  if 'g' in kwargs:
    g = kwargs['g']
  for k in kwargs.keys():
    if not(k in ['x_opt','cost','lambda_g','lambda_x','lambda_p','g']):
      raise Exception("Keyword error in nlpsolverOut: '%s' is not recognized. Available keywords are: x_opt, cost, lambda_g, lambda_x, lambda_p, g" % k )
  return IOSchemeVector([x_opt,cost,lambda_g,lambda_x,lambda_p,g], SCHEME_NLPOutput)
%}
#endif //SWIGPYTHON
#ifndef SWIGPYTHON
namespace CasADi {
%template(nlpsolverOut) nlpsolverOut<SXMatrix>;
%template(nlpsolverOut) nlpsolverOut<MX>;
}
#endif //SWIGPYTHON
#ifdef SWIGPYTHON
%pythoncode %{
def mayerIn(*dummy,**kwargs):
  """
  Helper function for 'MayerInput'

  Input arguments of a Mayer Term
  nx: Number of states: from ffcn.input(INTEGRATOR_X0).size()
  np: Number of parameters: from option number_of_parameters
  
  Keyword arguments:
    x -- States at the end of integration (nx x 1) [MAYER_X]
    p -- Problem parameters (np x 1) [MAYER_P]
  """
  if(len(dummy)>0): raise Exception("Error in mayerIn: syntax has become more strict. You must use keyword arguments now, for your own safety.\n mayerIn(my_x, my_p)\nmust be written\n mayerIn(x=my_x, p=my_p)\nwhere any keyword is optional.")
  x = []
  if 'x' in kwargs:
    x = kwargs['x']
  p = []
  if 'p' in kwargs:
    p = kwargs['p']
  for k in kwargs.keys():
    if not(k in ['x','p']):
      raise Exception("Keyword error in mayerIn: '%s' is not recognized. Available keywords are: x, p" % k )
  return IOSchemeVector([x,p], SCHEME_MayerInput)
%}
#endif //SWIGPYTHON
#ifndef SWIGPYTHON
namespace CasADi {
%template(mayerIn) mayerIn<SXMatrix>;
%template(mayerIn) mayerIn<MX>;
}
#endif //SWIGPYTHON
#ifdef SWIGPYTHON
%pythoncode %{
def ocpIn(*dummy,**kwargs):
  """
  Helper function for 'OCPInput'

  Input arguments of an OCP Solver
  ns: Number of shooting nodes: from option number_of_grid_points
  nx: Number of states: from ffcn.input(INTEGRATOR_X0).size()
  nc: Number of constants duting intergation: ffcn.input(INTEGRATOR_P).size()
  nu: Number of controls: from nc - np
  np: Number of parameters: from option number_of_parameters
  nh: Number of point constraints: from cfcn.input(0).size()
  
  Keyword arguments:
    lbx    -- States lower bounds (nx x (ns+1)) [OCP_LBX]
    ubx    -- States upper bounds (nx x (ns+1)) [OCP_UBX]
    x_init -- States initial guess (nx x (ns+1)) [OCP_X_INIT]
    lbu    -- Controls lower bounds (nu x ns) [OCP_LBU]
    ubu    -- Controls upper bounds (nu x ns) [OCP_UBU]
    u_init -- Controls initial guess (nu x ns) [OCP_U_INIT]
    lbp    -- Parameters lower bounds (np x 1) [OCP_LBP]
    ubp    -- Parameters upper bounds (np x 1) [OCP_UBP]
    p_init -- Parameters initial guess (np x 1) [OCP_P_INIT]
    lbh    -- Point constraint lower bound (nh x (ns+1)) [OCP_LBH]
    ubh    -- Point constraint upper bound (nh x (ns+1)) [OCP_UBH]
    lbg    -- Lower bound for the coupling constraints [OCP_LBG]
    ubg    -- Upper bound for the coupling constraints [OCP_UBG]
  """
  if(len(dummy)>0): raise Exception("Error in ocpIn: syntax has become more strict. You must use keyword arguments now, for your own safety.\n ocpIn(my_lbx, my_ubx, my_x_init, my_lbu, my_ubu, my_u_init, my_lbp, my_ubp, my_p_init, my_lbh, my_ubh, my_lbg, my_ubg)\nmust be written\n ocpIn(lbx=my_lbx, ubx=my_ubx, x_init=my_x_init, lbu=my_lbu, ubu=my_ubu, u_init=my_u_init, lbp=my_lbp, ubp=my_ubp, p_init=my_p_init, lbh=my_lbh, ubh=my_ubh, lbg=my_lbg, ubg=my_ubg)\nwhere any keyword is optional.")
  lbx = []
  if 'lbx' in kwargs:
    lbx = kwargs['lbx']
  ubx = []
  if 'ubx' in kwargs:
    ubx = kwargs['ubx']
  x_init = []
  if 'x_init' in kwargs:
    x_init = kwargs['x_init']
  lbu = []
  if 'lbu' in kwargs:
    lbu = kwargs['lbu']
  ubu = []
  if 'ubu' in kwargs:
    ubu = kwargs['ubu']
  u_init = []
  if 'u_init' in kwargs:
    u_init = kwargs['u_init']
  lbp = []
  if 'lbp' in kwargs:
    lbp = kwargs['lbp']
  ubp = []
  if 'ubp' in kwargs:
    ubp = kwargs['ubp']
  p_init = []
  if 'p_init' in kwargs:
    p_init = kwargs['p_init']
  lbh = []
  if 'lbh' in kwargs:
    lbh = kwargs['lbh']
  ubh = []
  if 'ubh' in kwargs:
    ubh = kwargs['ubh']
  lbg = []
  if 'lbg' in kwargs:
    lbg = kwargs['lbg']
  ubg = []
  if 'ubg' in kwargs:
    ubg = kwargs['ubg']
  for k in kwargs.keys():
    if not(k in ['lbx','ubx','x_init','lbu','ubu','u_init','lbp','ubp','p_init','lbh','ubh','lbg','ubg']):
      raise Exception("Keyword error in ocpIn: '%s' is not recognized. Available keywords are: lbx, ubx, x_init, lbu, ubu, u_init, lbp, ubp, p_init, lbh, ubh, lbg, ubg" % k )
  return IOSchemeVector([lbx,ubx,x_init,lbu,ubu,u_init,lbp,ubp,p_init,lbh,ubh,lbg,ubg], SCHEME_OCPInput)
%}
#endif //SWIGPYTHON
#ifndef SWIGPYTHON
namespace CasADi {
%template(ocpIn) ocpIn<SXMatrix>;
%template(ocpIn) ocpIn<MX>;
}
#endif //SWIGPYTHON
#ifdef SWIGPYTHON
%pythoncode %{
def ocpOut(*dummy,**kwargs):
  """
  Helper function for 'OCPOutput'

  Output arguments of an OCP Solver
  
  Keyword arguments:
    x_opt -- Optimal state trajectory [OCP_X_OPT]
    u_opt -- Optimal control trajectory [OCP_U_OPT]
    p_opt -- Optimal parameters [OCP_P_OPT]
    cost  -- Objective/cost function for optimal solution (1 x 1) [OCP_COST]
  """
  if(len(dummy)>0): raise Exception("Error in ocpOut: syntax has become more strict. You must use keyword arguments now, for your own safety.\n ocpOut(my_x_opt, my_u_opt, my_p_opt, my_cost)\nmust be written\n ocpOut(x_opt=my_x_opt, u_opt=my_u_opt, p_opt=my_p_opt, cost=my_cost)\nwhere any keyword is optional.")
  x_opt = []
  if 'x_opt' in kwargs:
    x_opt = kwargs['x_opt']
  u_opt = []
  if 'u_opt' in kwargs:
    u_opt = kwargs['u_opt']
  p_opt = []
  if 'p_opt' in kwargs:
    p_opt = kwargs['p_opt']
  cost = []
  if 'cost' in kwargs:
    cost = kwargs['cost']
  for k in kwargs.keys():
    if not(k in ['x_opt','u_opt','p_opt','cost']):
      raise Exception("Keyword error in ocpOut: '%s' is not recognized. Available keywords are: x_opt, u_opt, p_opt, cost" % k )
  return IOSchemeVector([x_opt,u_opt,p_opt,cost], SCHEME_OCPOutput)
%}
#endif //SWIGPYTHON
#ifndef SWIGPYTHON
namespace CasADi {
%template(ocpOut) ocpOut<SXMatrix>;
%template(ocpOut) ocpOut<MX>;
}
#endif //SWIGPYTHON
#ifdef SWIGPYTHON
%pythoncode %{
def qpIn(*dummy,**kwargs):
  """
  Helper function for 'QPInput'

  Input arguments of a QP problem
  
  Keyword arguments:
    h           -- The square matrix H: sparse, (nx x nx). Only the lower triangular part is actually used. The matrix is assumed to be symmetrical. [QP_H]
    g           -- The vector G: dense,  (nx x 1) [QP_G]
    a           -- The matrix A: sparse, (nc x nx) - product with x must be dense. [QP_A]
    lba         -- dense, (nc x 1) [QP_LBA]
    uba         -- dense, (nc x 1) [QP_UBA]
    lbx         -- dense, (nx x 1) [QP_LBX]
    ubx         -- dense, (nx x 1) [QP_UBX]
    x_init      -- dense, (nx x 1) [QP_X_INIT]
    lambda_init -- dense [QP_LAMBDA_INIT]
  """
  if(len(dummy)>0): raise Exception("Error in qpIn: syntax has become more strict. You must use keyword arguments now, for your own safety.\n qpIn(my_h, my_g, my_a, my_lba, my_uba, my_lbx, my_ubx, my_x_init, my_lambda_init)\nmust be written\n qpIn(h=my_h, g=my_g, a=my_a, lba=my_lba, uba=my_uba, lbx=my_lbx, ubx=my_ubx, x_init=my_x_init, lambda_init=my_lambda_init)\nwhere any keyword is optional.")
  h = []
  if 'h' in kwargs:
    h = kwargs['h']
  g = []
  if 'g' in kwargs:
    g = kwargs['g']
  a = []
  if 'a' in kwargs:
    a = kwargs['a']
  lba = []
  if 'lba' in kwargs:
    lba = kwargs['lba']
  uba = []
  if 'uba' in kwargs:
    uba = kwargs['uba']
  lbx = []
  if 'lbx' in kwargs:
    lbx = kwargs['lbx']
  ubx = []
  if 'ubx' in kwargs:
    ubx = kwargs['ubx']
  x_init = []
  if 'x_init' in kwargs:
    x_init = kwargs['x_init']
  lambda_init = []
  if 'lambda_init' in kwargs:
    lambda_init = kwargs['lambda_init']
  for k in kwargs.keys():
    if not(k in ['h','g','a','lba','uba','lbx','ubx','x_init','lambda_init']):
      raise Exception("Keyword error in qpIn: '%s' is not recognized. Available keywords are: h, g, a, lba, uba, lbx, ubx, x_init, lambda_init" % k )
  return IOSchemeVector([h,g,a,lba,uba,lbx,ubx,x_init,lambda_init], SCHEME_QPInput)
%}
#endif //SWIGPYTHON
#ifndef SWIGPYTHON
namespace CasADi {
%template(qpIn) qpIn<SXMatrix>;
%template(qpIn) qpIn<MX>;
}
#endif //SWIGPYTHON
#ifdef SWIGPYTHON
%pythoncode %{
def qpOut(*dummy,**kwargs):
  """
  Helper function for 'QPOutput'

  Output arguments of an QP Solver
  
  Keyword arguments:
    primal   -- The primal solution [QP_PRIMAL]
    cost     -- The optimal cost [QP_COST]
    lambda_a -- The dual solution corresponding to linear bounds [QP_LAMBDA_A]
    lambda_x -- The dual solution corresponding to simple bounds [QP_LAMBDA_X]
  """
  if(len(dummy)>0): raise Exception("Error in qpOut: syntax has become more strict. You must use keyword arguments now, for your own safety.\n qpOut(my_primal, my_cost, my_lambda_a, my_lambda_x)\nmust be written\n qpOut(primal=my_primal, cost=my_cost, lambda_a=my_lambda_a, lambda_x=my_lambda_x)\nwhere any keyword is optional.")
  primal = []
  if 'primal' in kwargs:
    primal = kwargs['primal']
  cost = []
  if 'cost' in kwargs:
    cost = kwargs['cost']
  lambda_a = []
  if 'lambda_a' in kwargs:
    lambda_a = kwargs['lambda_a']
  lambda_x = []
  if 'lambda_x' in kwargs:
    lambda_x = kwargs['lambda_x']
  for k in kwargs.keys():
    if not(k in ['primal','cost','lambda_a','lambda_x']):
      raise Exception("Keyword error in qpOut: '%s' is not recognized. Available keywords are: primal, cost, lambda_a, lambda_x" % k )
  return IOSchemeVector([primal,cost,lambda_a,lambda_x], SCHEME_QPOutput)
%}
#endif //SWIGPYTHON
#ifndef SWIGPYTHON
namespace CasADi {
%template(qpOut) qpOut<SXMatrix>;
%template(qpOut) qpOut<MX>;
}
#endif //SWIGPYTHON
#ifdef SWIGPYTHON
%pythoncode %{
def sdpIn(*dummy,**kwargs):
  """
  Helper function for 'SDPInput'

  Input arguments of a SDP problem
  
  Keyword arguments:
    a -- The vertical stack of all matrices A_i: ( nm x n) [SDP_A]
    b -- The vector b: ( m x 1) [SDP_B]
    c -- The matrix C: ( n x n) [SDP_C]
  """
  if(len(dummy)>0): raise Exception("Error in sdpIn: syntax has become more strict. You must use keyword arguments now, for your own safety.\n sdpIn(my_a, my_b, my_c)\nmust be written\n sdpIn(a=my_a, b=my_b, c=my_c)\nwhere any keyword is optional.")
  a = []
  if 'a' in kwargs:
    a = kwargs['a']
  b = []
  if 'b' in kwargs:
    b = kwargs['b']
  c = []
  if 'c' in kwargs:
    c = kwargs['c']
  for k in kwargs.keys():
    if not(k in ['a','b','c']):
      raise Exception("Keyword error in sdpIn: '%s' is not recognized. Available keywords are: a, b, c" % k )
  return IOSchemeVector([a,b,c], SCHEME_SDPInput)
%}
#endif //SWIGPYTHON
#ifndef SWIGPYTHON
namespace CasADi {
%template(sdpIn) sdpIn<SXMatrix>;
%template(sdpIn) sdpIn<MX>;
}
#endif //SWIGPYTHON
#ifdef SWIGPYTHON
%pythoncode %{
def sdpOut(*dummy,**kwargs):
  """
  Helper function for 'SDPOutput'

  Output arguments of an SDP Solver
  
  Keyword arguments:
    primal      -- The primal solution (m x 1) - may be used as initial guess [SDP_PRIMAL]
    p           -- The solution P (n x n) - may be used as initial guess [SDP_PRIMAL_P]
    dual        -- The dual solution (n x n) - may be used as initial guess [SDP_DUAL]
    primal_cost -- The primal optimal cost (1 x 1) [SDP_PRIMAL_COST]
    dual_cost   -- The dual optimal cost (1 x 1) [SDP_DUAL_COST]
  """
  if(len(dummy)>0): raise Exception("Error in sdpOut: syntax has become more strict. You must use keyword arguments now, for your own safety.\n sdpOut(my_primal, my_p, my_dual, my_primal_cost, my_dual_cost)\nmust be written\n sdpOut(primal=my_primal, p=my_p, dual=my_dual, primal_cost=my_primal_cost, dual_cost=my_dual_cost)\nwhere any keyword is optional.")
  primal = []
  if 'primal' in kwargs:
    primal = kwargs['primal']
  p = []
  if 'p' in kwargs:
    p = kwargs['p']
  dual = []
  if 'dual' in kwargs:
    dual = kwargs['dual']
  primal_cost = []
  if 'primal_cost' in kwargs:
    primal_cost = kwargs['primal_cost']
  dual_cost = []
  if 'dual_cost' in kwargs:
    dual_cost = kwargs['dual_cost']
  for k in kwargs.keys():
    if not(k in ['primal','p','dual','primal_cost','dual_cost']):
      raise Exception("Keyword error in sdpOut: '%s' is not recognized. Available keywords are: primal, p, dual, primal_cost, dual_cost" % k )
  return IOSchemeVector([primal,p,dual,primal_cost,dual_cost], SCHEME_SDPOutput)
%}
#endif //SWIGPYTHON
#ifndef SWIGPYTHON
namespace CasADi {
%template(sdpOut) sdpOut<SXMatrix>;
%template(sdpOut) sdpOut<MX>;
}
#endif //SWIGPYTHON
