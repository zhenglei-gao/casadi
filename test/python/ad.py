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
from casadi import *
import casadi as c
from numpy import *
import unittest
from types import *
from helpers import *
import itertools

class ADtests(casadiTestCase):

  def setUp(self):
    x=SX("x")
    y=SX("y")
    z=SX("z")
    w=SX("w")
    
    out=SXMatrix.sparse(1,6)
    out[0,0]=x
    out[2,0]=x+2*y**2
    out[4,0]=x+2*y**3+3*z**4
    out[5,0]=w

    inp=SXMatrix.sparse(1,6)
    inp[0,0]=x
    inp[2,0]=y
    inp[4,0]=z
    inp[5,0]=w
    
    sp = CCSSparsity(1,6,[0, 1, 1, 2, 2, 3, 4],[0, 0, 0, 0])
    spT = CCSSparsity(6,1,[0, 4],[0, 2, 4, 5])
    
    self.sxinputs = {
       "row" : {
            "dense": [horzcat([x,y,z,w])],
            "sparse": [inp] }
        , "col": {
            "dense":  [SXMatrix([x,y,z,w]).T],
            "sparse": [inp.T]
       }, "matrix": {
          "dense": [c.reshape(SXMatrix([x,y,z,w]),2,2)],
          "sparse": [c.reshape(inp,3,2)]
        }
    }

    self.mxinputs = {
       "row" : {
            "dense": [msym("xyzw",1,4)],
            "sparse": [msym("xyzw",sp)]
        },
        "col" : {
            "dense": [msym("xyzw",4,1)],
            "sparse": [msym("xyzw",spT)]
        },
        "matrix": {
            "dense": [msym("xyzw",2,2)],
            "sparse": [msym("xyzw",c.reshape(inp,3,2).sparsity())]
        }
    }
    
    def temp1(xyz):
      X=MX.sparse(1,6)
      X[0,0]=xyz[0]
      X[2,0]=xyz[0]+2*xyz[1]**2
      X[4,0]=xyz[0]+2*xyz[1]**3+3*xyz[2]**4
      X[5,0]=xyz[3]
      return [X]
    
    def temp2(xyz):
      X=MX.sparse(6,1)
      X[0,0]=xyz[0]
      X[0,2]=xyz[0]+2*xyz[1]**2
      X[0,4]=xyz[0]+2*xyz[1]**3+3*xyz[2]**4
      X[0,5]=xyz[3]
      return [X]

    def testje(xyz):
      print horzcat([xyz[0],xyz[0]+2*xyz[1]**2,xyz[0]+2*xyz[1]**3+3*xyz[2]**4,xyz[3]]).shapeQQQ
      
    self.mxoutputs = {
       "row": {
        "dense":  lambda xyz: [horzcat([xyz[0],xyz[0]+2*xyz[1]**2,xyz[0]+2*xyz[1]**3+3*xyz[2]**4,xyz[3]])],
        "sparse": temp1
        }, "col": {
        "dense": lambda xyz: [vertcat([xyz[0],xyz[0]+2*xyz[1]**2,xyz[0]+2*xyz[1]**3+3*xyz[2]**4,xyz[3]])],
        "sparse": temp2
       },
       "matrix": {
          "dense": lambda xyz: [c.reshape(horzcat([xyz[0],xyz[0]+2*xyz[1]**2,xyz[0]+2*xyz[1]**3+3*xyz[2]**4,xyz[3]]),(2,2))],
          "sparse": lambda xyz: [c.reshape(temp1(xyz)[0],(3,2))]
       }
    }


    self.sxoutputs = {
       "row": {
        "dense": [horzcat([x,x+2*y**2,x+2*y**3+3*z**4,w])],
        "sparse": [out]
        }, "col": {
          "dense":  [SXMatrix([x,x+2*y**2,x+2*y**3+3*z**4,w]).T],
          "sparse": [out.T]
      }, "matrix" : {
          "dense":  [c.reshape(SXMatrix([x,x+2*y**2,x+2*y**3+3*z**4,w]),2,2)],
          "sparse": [c.reshape(out,3,2)]
      }
    }
    
    self.jacobians = {
      "dense" : {
        "dense" : lambda x,y,z,w: array([[1,0,0,0],[1,4*y,0,0],[1,6*y**2,12*z**3,0],[0,0,0,1]]),
        "sparse" : lambda x,y,z,w: array([[1,0,0,0],[0,0,0,0],[1,4*y,0,0],[0,0,0,0],[1,6*y**2,12*z**3,0],[0,0,0,1]])
        }
      ,
      "sparse" : {
        "dense" : lambda x,y,z,w: array([[1,0,0,0,0,0],[1,0,4*y,0,0,0],[1,0,6*y**2,0,12*z**3,0],[0,0,0,0,0,1]]),
        "sparse" : lambda x,y,z,w:  array([[1,0,0,0,0,0],[0,0,0,0,0,0],[1,0,4*y,0,0,0],[0,0,0,0,0,0],[1,0,6*y**2,0,12*z**3,0],[0,0,0,0,0,1]])
      }
    }
                
  def test_SXevalSX(self):
    n=array([1.2,2.3,7,1.4])
    for inputshape in ["row","col","matrix"]:
      for outputshape in ["row","col","matrix"]:
        for inputtype in ["dense","sparse"]:
          for outputtype in ["dense","sparse"]:
            self.message("evalSX on SX. Input %s %s, Output %s %s" % (inputtype,inputshape,outputtype,outputshape) )
            f=SXFunction(self.sxinputs[inputshape][inputtype],self.sxoutputs[outputshape][outputtype])
            f.init()
            f.setInput(n)
            f.evaluate()
            r = f.getOutput()
            J = self.jacobians[inputtype][outputtype](*n)
            
            seeds = [[1,0,0,0],[0,2,0,0],[1.2,4.8,7.9,4.6]]
            
            y = ssym("y",f.input().sparsity())
            
            fseeds = map(lambda x: DMatrix(f.input().sparsity(),x), seeds)
            aseeds = map(lambda x: DMatrix(f.output().sparsity(),x), seeds)
            res,fwdsens,adjsens = f.evalSX([y],map(lambda x: [x],fseeds),map(lambda x: [x],aseeds))
            fwdsens = map(lambda x: x[0],fwdsens)
            adjsens = map(lambda x: x[0],adjsens)
            
            fe = SXFunction([y],res)
            fe.init()
            
            fe.setInput(n)
            fe.evaluate()
            
            self.checkarray(r,fe.getOutput())
            
            for sens,seed in zip(fwdsens,fseeds):
              fe = SXFunction([y],[sens])
              fe.init()
              fe.setInput(n)
              fe.evaluate()
              self.checkarray(c.vec(fe.getOutput()),mul(c.vec(seed),J),"AD") 

            for sens,seed in zip(adjsens,aseeds):
              fe = SXFunction([y],[sens])
              fe.init()
              fe.setInput(n)
              fe.evaluate()
              self.checkarray(c.vec(fe.getOutput()),mul(c.vec(seed),J.T),"AD") 
              
  def test_MXevalMX(self):
    n=array([1.2,2.3,7,1.4])
    for inputshape in ["row","col","matrix"]:
      for outputshape in ["row","col","matrix"]:
        for inputtype in ["dense","sparse"]:
          for outputtype in ["dense","sparse"]:
            self.message("evalMX on MX. Input %s %s, Output %s %s" % (inputtype,inputshape,outputtype,outputshape) )
            f=MXFunction(self.mxinputs[inputshape][inputtype],self.mxoutputs[outputshape][outputtype](self.mxinputs[inputshape][inputtype][0]))
            f.init()
            f.setInput(n)
            f.evaluate()
            r = f.getOutput()
            J = self.jacobians[inputtype][outputtype](*n)
            
            seeds = [[1,0,0,0],[0,2,0,0],[1.2,4.8,7.9,4.6]]
            
            y = msym("y",f.input().sparsity())
            
            fseeds = map(lambda x: DMatrix(f.input().sparsity(),x), seeds)
            aseeds = map(lambda x: DMatrix(f.output().sparsity(),x), seeds)
            res,fwdsens,adjsens = f.evalMX([y],map(lambda x: [x],fseeds),map(lambda x: [x],aseeds))
            fwdsens = map(lambda x: x[0],fwdsens)
            adjsens = map(lambda x: x[0],adjsens)
            
            fe = MXFunction([y],res)
            fe.init()
            
            fe.setInput(n)
            fe.evaluate()
            
            self.checkarray(r,fe.getOutput())
            
            for sens,seed in zip(fwdsens,fseeds):
              fe = MXFunction([y],[sens])
              fe.init()
              fe.setInput(n)
              fe.evaluate()
              self.checkarray(c.vec(fe.getOutput()),mul(c.vec(seed),J),"AD") 

            for sens,seed in zip(adjsens,aseeds):
              fe = MXFunction([y],[sens])
              fe.init()
              fe.setInput(n)
              fe.evaluate()
              self.checkarray(c.vec(fe.getOutput()),mul(c.vec(seed),J.T),"AD") 

  @known_bug()  # Not implemented
  def test_MXevalSX(self):
    n=array([1.2,2.3,7,1.4])
    for inputshape in ["row","col","matrix"]:
      for outputshape in ["row","col","matrix"]:
        for inputtype in ["dense","sparse"]:
          for outputtype in ["dense","sparse"]:
            self.message("evalSX on MX. Input %s %s, Output %s %s" % (inputtype,inputshape,outputtype,outputshape) )
            f=MXFunction(self.mxinputs[inputshape][inputtype],self.mxoutputs[outputshape][outputtype](self.mxinputs[inputshape][inputtype][0]))
            f.init()
            f.setInput(n)
            f.evaluate()
            r = f.getOutput()
            J = self.jacobians[inputtype][outputtype](*n)
            
            seeds = [[1,0,0,0],[0,2,0,0],[1.2,4.8,7.9,4.6]]
            
            y = ssym("y",f.input().sparsity())
            
            fseeds = map(lambda x: DMatrix(f.input().sparsity(),x), seeds)
            aseeds = map(lambda x: DMatrix(f.output().sparsity(),x), seeds)
            res,fwdsens,adjsens = f.evalSX([y],map(lambda x: [x],fseeds),map(lambda x: [x],aseeds))
            fwdsens = map(lambda x: x[0],fwdsens)
            adjsens = map(lambda x: x[0],adjsens)
            
            fe = SXFunction([y],res)
            fe.init()
            
            fe.setInput(n)
            fe.evaluate()
            
            self.checkarray(r,fe.getOutput())
            
            for sens,seed in zip(fwdsens,fseeds):
              fe = SXFunction([y],[sens])
              fe.init()
              fe.setInput(n)
              fe.evaluate()
              self.checkarray(c.vec(fe.getOutput()),mul(c.vec(seed),J),"AD") 

            for sens,seed in zip(adjsens,aseeds):
              fe = SXFunction([y],[sens])
              fe.init()
              fe.setInput(n)
              fe.evaluate()
              self.checkarray(c.vec(fe.getOutput()),mul(c.vec(seed),J.T),"AD")

  def test_MXevalSX_reduced(self):
    n=array([1.2,2.3,7,1.4])
    for inputshape in ["row","col","matrix"]:
      for outputshape in ["row","col","matrix"]:
        for inputtype in ["dense","sparse"]:
          for outputtype in ["dense","sparse"]:
            self.message("evalSX on MX. Input %s %s, Output %s %s" % (inputtype,inputshape,outputtype,outputshape) )
            f=MXFunction(self.mxinputs[inputshape][inputtype],self.mxoutputs[outputshape][outputtype](self.mxinputs[inputshape][inputtype][0]))
            f.init()
            f.setInput(n)
            f.evaluate()
            r = f.getOutput()
  
            y = ssym("y",f.input().sparsity())
            
      
            res,fwdsens,adjsens = f.evalSX([y],[],[])
            
            fe = SXFunction([y],res)
            fe.init()
            
            fe.setInput(n)
            fe.evaluate()
            
            self.checkarray(r,fe.getOutput())
                
  def test_Jacobian(self):
    n=array([1.2,2.3,7,4.6])
    for inputshape in ["row","col","matrix"]:
      for outputshape in ["row","col","matrix"]:
        for inputtype in ["dense","sparse"]:
          for outputtype in ["dense","sparse"]:
            for mode in ["forward","reverse"]:
              self.message(" %s Jacobian on SX. Input %s %s, Output %s %s" % (mode,inputtype,inputshape,outputtype,outputshape) )
              f=SXFunction(self.sxinputs[inputshape][inputtype],self.sxoutputs[outputshape][outputtype])
              f.setOption("ad_mode",mode)
              f.init()
              Jf=f.jacobian(0,0)
              Jf.init()
              Jf.setInput(n)
              Jf.evaluate()
              J = self.jacobians[inputtype][outputtype](*n)
              self.checkarray(array(Jf.getOutput()),J,"Jacobian\n Mode: %s\n Input: %s %s\n Output: %s %s"% (mode, inputshape, inputtype, outputshape, outputtype))
              
  def test_jacobianSX(self):
    n=array([1.2,2.3,7,4.6])
    for inputshape in ["row","col","matrix"]:
      for outputshape in ["row","col","matrix"]:
        for inputtype in ["dense","sparse"]:
          for outputtype in ["dense","sparse"]:
            self.message("jacobian on SX (SCT). Input %s %s, Output %s %s" % (inputtype,inputshape,outputtype,outputshape) )
            Jf=SXFunction(
              self.sxinputs[inputshape][inputtype],
              [
                  jacobian(
                    SXMatrix(self.sxoutputs[outputshape][outputtype][0]),
                    SXMatrix(self.sxinputs[inputshape][inputtype][0])
                  )
              ]
            )
            Jf.init()
            Jf.setInput(n)
            Jf.evaluate()
            J = self.jacobians[inputtype][outputtype](*n)
            self.checkarray(array(Jf.getOutput()),J,"jacobian")
                          
  def test_jacsparsity(self):
    n=array([1.2,2.3,7,4.6])
    for inputshape in ["row","col","matrix"]:
      for outputshape in ["row","col","matrix"]:
        for inputtype in ["dense","sparse"]:
          for outputtype in ["dense","sparse"]:
            self.message("jacsparsity on SX. Input %s %s, Output %s %s" % (inputtype,inputshape,outputtype,outputshape) )
            f=SXFunction(self.sxinputs[inputshape][inputtype],self.sxoutputs[outputshape][outputtype])
            f.init()
            J = self.jacobians[inputtype][outputtype](*n)
            self.checkarray(DMatrix(f.jacSparsity(),1),array(J!=0,int),"jacsparsity")
              
  def test_JacobianMX(self):
    n=array([1.2,2.3,7,4.6])
    for inputshape in ["row","col","matrix"]:
      for outputshape in ["row","col","matrix"]:
        for inputtype in ["dense","sparse"]:
          for outputtype in ["dense","sparse"]:
            for mode in ["forward","reverse"]:
              self.message("adj AD on MX. Input %s %s, Output %s %s" % (inputtype,inputshape,outputtype,outputshape) )
              f=MXFunction(self.mxinputs[inputshape][inputtype],self.mxoutputs[outputshape][outputtype](self.mxinputs[inputshape][inputtype][0]))
              f.setOption("ad_mode",mode)
              f.init()
              Jf=f.jacobian(0,0)
              Jf.init()
              Jf.setInput(n)
              Jf.evaluate()
              J = self.jacobians[inputtype][outputtype](*n)
              self.checkarray(Jf.getOutput(),J,"Jacobian\n Mode: %s\n Input: %s %s\n Output: %s %s"% (mode, inputshape, inputtype, outputshape, outputtype))
                   
  def test_jacsparsityMX(self):
    n=array([1.2,2.3,7,4.6])
    for inputshape in ["row","col","matrix"]:
      for outputshape in ["row","col","matrix"]:
        for inputtype in ["dense","sparse"]:
          for outputtype in ["dense","sparse"]:
            for mode in ["forward","reverse"]:
              self.message(" %s jacobian on MX (SCT). Input %s %s, Output %s %s" % (mode,inputtype,inputshape,outputtype,outputshape) )
              f=MXFunction(self.mxinputs[inputshape][inputtype],self.mxoutputs[outputshape][outputtype](self.mxinputs[inputshape][inputtype][0]))
              f.setOption("ad_mode",mode)
              f.init()
              Jf=f.jacobian(0,0)
              Jf.init()
              Jf.setInput(n)
              Jf.evaluate()
              J = self.jacobians[inputtype][outputtype](*n)
              self.checkarray(array(Jf.getOutput()),J,"jacobian")
              self.checkarray(array(DMatrix(f.jacSparsity(),1)),array(J!=0,int),"jacsparsity")
              
     
              
  def test_hessian(self):
    self.message("Jacobian chaining")
    x=ssym("x")
    y=ssym("y")
    z=ssym("z")
    n=array([1.2,2.3,7])
    f=SXFunction([horzcat([x,y,z])],[horzcat([x+2*y**3+3*z**4])])
    f.init()
    J=f.jacobian(0,0)
    J.init()
    m=msym("m",1,3)
    JT,_ = J.call([m])
    JT = MXFunction([m],[JT.T])
    JT.init()
    JT.setInput(n)
    JT.evaluate()
    H = JT.jacobian(0,0)
    H.init()
    H.setInput(n)
    #H.evaluate()
    
    #print array(JT.getOutput())
    #print array(H.getOutput())
    
  def test_bugshape(self):
    self.message("shape bug")
    x=ssym("x")
    y=ssym("y")

    inp=SXMatrix.sparse(1,5)
    inp[0,0]=x
    inp[3,0]=y

    f=SXFunction([inp],[horzcat([x+y,x,y])])
    #f.setOption("ad_mode","forward")
    f.init()
    J=f.jacobian(0,0)
    J.init()
    J.setInput([2,7])
    J.evaluate()

    self.assertEqual(f.output().size2(),3,"Jacobian shape bug")
    self.assertEqual(f.output().size1(),1,"Jacobian shape bug")

    
  def test_bugglibc(self):
    self.message("Code that used to throw a glibc error")
    x=SX("x")
    y=SX("y")

    inp=SXMatrix.sparse(1,5)
    inp[0,0]=x
    inp[3,0]=y

    f=SXFunction([inp],[horzcat([x+y,x,y])])
    #f.setOption("ad_mode","forward")
    f.init()
    J=f.jacobian(0,0)
    J.init()
    J.setInput([2,7])
    J.evaluate()

    f=SXFunction([inp],[horzcat([x+y,x,y])])
    f.init()
    print f.input().shapeQQQ
    J=f.jacobian(0,0)
    
    
  def test_MX(self):
    # commented out, uses directional derivatives #884
    return

    x = msym("x",1,2)
    y = msym("y",2,2)
    
    f1 = MXFunction([x,y],[x+y[0],mul(x,y)])
    f1.init()
    
    f2 = MXFunction([x,y],[mul(x,MX.zeros(2,0))])
    f2.init()

    f3 = MXFunction([x,y],[MX.zeros(0,0),mul(x,y)])
    f3.init()
    
    f4 = MXFunction([x,y],[MX.zeros(2,0),mul(x,y)])
    f4.init()
    
    ndir = 2
    
    in1 = [x,y]
    v1 = [DMatrix([1.1,1.3]),DMatrix([[0.7,1.5],[2.1,0.9]])]
    
    w=x[:]
    w[1]*=2

    w2=x[:]
    w2[1]*=x[0]
    
    ww=x[:]
    ww[[0,1]]*=x

    wwf=x[:]
    wwf[[1,0]]*=x
    
    wwr=x[:]
    wwr[[0,0,1,1]]*=2
    
    yy=y[:,:]
    
    yy[:,0] = x

    yy2=y[:,:]
    
    yy2[:,0] = x**2
    
    yyy=y[:,:]
    
    yyy[[1,0],0] = x

    yyy2=y[:,:]
    
    yyy2[[1,0],0] = x**2
    

    def remove00(x):
      ret = DMatrix(x)
      if ret.numel()>0:
        ret[0,0] = DMatrix.sparse(1,1)
      return ret
      
    spmods = [lambda x: x , remove00]
    
    # TODO: sparse seeding
    
    for inputs,values,out, jac in [
          (in1,v1,x,DMatrix.eye(2)),
          (in1,v1,x.T,DMatrix.eye(2)),
          (in1,v1,x**2,2*c.diag(x)),
          (in1,v1,(x**2).attachAssert(True),2*c.diag(x)),
          (in1,v1,(x**2).T,2*c.diag(x)),
          (in1,v1,c.reshape(x,(1,2)),DMatrix.eye(2)),
          (in1,v1,c.reshape(x**2,(1,2)),2*c.diag(x)),
          (in1,v1,x+y[0],DMatrix.eye(2)),
          (in1,v1,x+x,2*DMatrix.eye(2)),
          (in1,v1,x**2+x,2*c.diag(x)+DMatrix.eye(2)),
          (in1,v1,x*x,2*c.diag(x)),
          (in1,v1,x*y[0],DMatrix.eye(2)*y[0]),
          (in1,v1,x[0],DMatrix.eye(2)[0,:]),
          (in1,v1,(x**2)[0],vertcat([2*x[0],MX.sparse(1,1)])),
          (in1,v1,x[0]+x[1],DMatrix.ones(2,1)),
          (in1,v1,horzcat([x[1],x[0]]),sparse(DMatrix([[0,1],[1,0]]))),
          #(in1,v1,horzsplit(x,[0,1,2])[1],sparse(DMatrix([[0,1]]))),
          (in1,v1,horzcat([x[1]**2,x[0]**2]),blockcat([[MX.sparse(1,1),2*x[1]],[2*x[0],MX.sparse(1,1)]])),
          #(in1,v1,horzsplit(x**2,[0,1,2])[1],blockcat([[MX.sparse(1,1),2*x[1]]])),
          (in1,v1,vertcat([x[1],x[0]]).T,sparse(DMatrix([[0,1],[1,0]]))),
          (in1,v1,vertcat([x[1]**2,x[0]**2]).T,blockcat([[MX.sparse(1,1),2*x[1]],[2*x[0],MX.sparse(1,1)]])),
          (in1,v1,x[[0,1]],sparse(DMatrix([[1,0],[0,1]]))),
          (in1,v1,(x**2)[[0,1]],2*c.diag(x)),
          (in1,v1,x[[0,0,1,1]],sparse(DMatrix([[1,0],[1,0],[0,1],[0,1]]))),
          (in1,v1,(x**2)[[0,0,1,1]],blockcat([[2*x[0],MX.sparse(1,1)],[2*x[0],MX.sparse(1,1)],[MX.sparse(1,1),2*x[1]],[MX.sparse(1,1),2*x[1]]])),
          (in1,v1,wwr,sparse(DMatrix([[2,0],[0,2]]))),
          (in1,v1,x[[1,0]],sparse(DMatrix([[0,1],[1,0]]))), 
          (in1,v1,x[[1,0],0],sparse(DMatrix([[0,1],[1,0]]))),
          (in1,v1,w,sparse(DMatrix([[1,0],[0,2]]))),
          (in1,v1,w2,blockcat([[1,MX.sparse(1,1)],[x[1],x[0]]])),
          (in1,v1,ww,2*c.diag(x)),
          (in1,v1,wwf,horzcat([x[[1,0]].T,x[[1,0]].T])),
          (in1,v1,yy[:,0],DMatrix.eye(2)),
          (in1,v1,yy2[:,0],2*c.diag(x)),
          (in1,v1,yyy[:,0],sparse(DMatrix([[0,1],[1,0]]))),
          (in1,v1,mul(x,y),y),
          (in1,v1,mul(y.T,x.T),y),
          (in1,v1,mul(x,y,sp_triplet(2,1,[1],[0])),y[sp_triplet(2,2,[1,1],[0,1])]),
          (in1,v1,mul(y.T,x.T,sp_triplet(2,1,[1],[0]).T),y[sp_triplet(2,2,[1,1],[0,1])]),
          (in1,v1,mul(x,y[sp_triplet(2,2,[0,1,1],[0,0,1])]),y[sp_triplet(2,2,[0,1,1],[0,0,1])]),
          (in1,v1,mul(y[sp_triplet(2,2,[0,1,1],[0,0,1])].T,x.T),y[sp_triplet(2,2,[0,1,1],[0,0,1])]),
          (in1,v1,mul(x**2,y),y*2*horzcat([x.T,x.T])),
          (in1,v1,sin(x),c.diag(cos(x))),
          (in1,v1,sin(x**2),c.diag(cos(x**2)*2*x)),
          (in1,v1,x*y[:,0],c.diag(y[:,0])),
          (in1,v1,x*y[[0,1]],c.diag(y[[0,1]])),
          (in1,v1,x*y[[1,0]],c.diag(y[[1,0]])),
          (in1,v1,x*y[[0,1],0],c.diag(y[[0,1],0])),
          (in1,v1,inner_prod(x,x),(2*x).T),
          (in1,v1,inner_prod(x**2,x),(3*x**2).T),
          #(in1,v1,c.det(vertcat([x,DMatrix([1,2])])),DMatrix([-1,2])), not implemented
          (in1,v1,f1.call(in1)[1],y),
          (in1,v1,f1.call([x**2,y])[1],y*2*horzcat([x.T,x.T])),
          (in1,v1,f2.call(in1)[0],DMatrix.zeros(2,0)),
          (in1,v1,f2.call([x**2,y])[0],DMatrix.zeros(2,0)),
          (in1,v1,f3.call(in1)[0],DMatrix.zeros(2,0)),
          (in1,v1,f3.call([x**2,y])[0],DMatrix.zeros(2,0)),
          (in1,v1,f4.call(in1)[0],DMatrix.zeros(2,0)),
          (in1,v1,f4.call([x**2,y])[0],DMatrix.zeros(2,0)),
          #(in1,v1,f1.call([x**2,[]])[1],DMatrix.zeros(3,2)),
          #(in1,v1,f1.call([[],y])[1],DMatrix.zeros(2,2)),
          (in1,v1,horzcat([x,DMatrix(0,1)]),DMatrix.eye(2)),
          (in1,v1,(x**2).setSparse(sparse(DMatrix([0,1])).sparsity()),blockcat([[MX.sparse(1,1),MX.sparse(1,1)],[MX.sparse(1,1),2*x[1]]])),
     ]:
      print out
      fun = MXFunction(inputs,[out,jac])
      fun.init()
      
      funsx = fun.expand()
      funsx.init()
      
      for i,v in enumerate(values):
        fun.setInput(v,i)
        funsx.setInput(v,i)
        
      fun.evaluate()
      funsx.evaluate()
      self.checkarray(fun.getOutput(0),funsx.getOutput(0))
      self.checkarray(fun.getOutput(1),funsx.getOutput(1))
      
      J_ = fun.getOutput(1)
      
      def vec(l):
        ret = []
        for i in l:
          ret.extend(i)
        return ret

      storage2 = {}
      storage = {}
      
      vf_mx = None
              
      for f in [fun,fun.expand()]:
        f.setOption("number_of_adj_dir",ndir)
        f.setOption("number_of_fwd_dir",ndir)
        f.init()

        # Fwd and Adjoint AD
        for i,v in enumerate(values):
          f.setInput(v,i)
        
        
        for d in range(ndir):
          f.setFwdSeed(DMatrix(inputs[0].sparsity(),random.random(inputs[0].size())),0,d)
          f.setAdjSeed(DMatrix(out.sparsity(),random.random(out.size())),0,d)
          f.setFwdSeed(0,1,d)
          f.setAdjSeed(0,1,d)
          
        f.evaluate(ndir,ndir)
        for d in range(ndir):
          seed = array(f.getFwdSeed(0,d)).ravel()
          sens = array(f.getFwdSens(0,d)).ravel()
          self.checkarray(sens,mul(seed,J_),"Fwd %d %s" % (d,str(type(f))))

          seed = array(f.getAdjSeed(0,d)).ravel()
          sens = array(f.getAdjSens(0,d)).ravel()
          self.checkarray(sens,mul(seed,J_.T),"Adj %d" %d)
          
        
        # evalThings
        for sym, Function in [(msym,MXFunction),(ssym,SXFunction)]:
          if isinstance(f, MXFunction) and Function is SXFunction: continue
          if isinstance(f, SXFunction) and Function is MXFunction: continue
          
          

          # dense
          for spmod,spmod2 in itertools.product(spmods,repeat=2):
            fseeds = [[sym("f",spmod(f.getInput(i)).sparsity()) for i in range(f.getNumInputs())]  for d in range(ndir)]
            aseeds = [[sym("a",spmod2(f.getOutput(i)).sparsity())  for i in range(f.getNumOutputs())] for d in range(ndir)]
            inputss = [sym("i",f.input(i).sparsity()) for i in range(f.getNumInputs())]
        
            res,fwdsens,adjsens = f.eval(inputss,fseeds,aseeds)
            
            fseed = [DMatrix(fseeds[d][0].sparsity(),random.random(fseeds[d][0].size())) for d in range(ndir) ]
            aseed = [DMatrix(aseeds[d][0].sparsity(),random.random(aseeds[d][0].size())) for d in range(ndir) ]
            vf = Function(inputss+vec([fseeds[i]+aseeds[i] for i in range(ndir)]),list(res) + vec([list(fwdsens[i])+list(adjsens[i]) for i in range(ndir)]))
            
            vf.init()
            
            for i,v in enumerate(values):
              vf.setInput(v,i)
            offset = len(inputss)
              
            for d in range(ndir):
              vf.setInput(fseed[d],offset+0)
              for i in range(len(values)-1):
                vf.setInput(0,offset+i+1)
                
              offset += len(inputss)

              vf.setInput(aseed[d],offset+0)
              vf.setInput(0,offset+1)
              offset+=2
              
            assert(offset==vf.getNumInputs())
            
            vf.evaluate()
              
            offset = len(res)
            for d in range(ndir):
              seed = array(fseed[d]).ravel()
              sens = array(vf.getOutput(offset+0)).ravel()
              offset+=len(inputss)
              self.checkarray(sens,mul(seed,J_),"eval Fwd %d %s" % (d,str(type(f))+str(sym)))

              seed = array(aseed[d]).ravel()
              sens = array(vf.getOutput(offset+0)).ravel()
              offset+=len(inputss)
              
              self.checkarray(sens,mul(seed,J_.T),"eval Adj %d %s" % (d,str([vf.getOutput(i) for i in range(vf.getNumOutputs())])))
          
          
            assert(offset==vf.getNumOutputs())
          
            # Complete random seeding
            random.seed(1)
            for i in range(vf.getNumInputs()):
              vf.setInput(DMatrix(vf.input(i).sparsity(),random.random(vf.input(i).size())),i)
            
            vf.evaluate()
            storagekey = (spmod,spmod2)
            if not(storagekey in storage):
              storage[storagekey] = []
            storage[storagekey].append([vf.getOutput(i) for i in range(vf.getNumOutputs())])
            
            # Added to make sure that the same seeds are used for SX and MX
            if Function is MXFunction:
              vf_mx = vf

          # Second order sensitivities
          for sym2, Function2 in [(msym,MXFunction),(ssym,SXFunction)]:
          
            if isinstance(vf, MXFunction) and Function2 is SXFunction: continue
            if isinstance(vf, SXFunction) and Function2 is MXFunction: continue
            

            for spmod_2,spmod2_2 in itertools.product(spmods,repeat=2):
              fseeds2 = [[sym2("f",vf_mx.input(i).sparsity()) for i in range(vf.getNumInputs())] for d in range(ndir)]
              aseeds2 = [[sym2("a",vf_mx.output(i).sparsity())  for i in range(vf.getNumOutputs()) ] for d in range(ndir)]
              inputss2 = [sym2("i",vf_mx.input(i).sparsity()) for i in range(vf.getNumInputs())]
           
              res2,fwdsens2,adjsens2 = vf.eval(inputss2,fseeds2,aseeds2)

              vf2 = Function2(inputss2+vec([fseeds2[i]+aseeds2[i] for i in range(ndir)]),list(res2) + vec([list(fwdsens2[i])+list(adjsens2[i]) for i in range(ndir)]))
              vf2.init()
                
              random.seed(1)
              for i in range(vf2.getNumInputs()):
                vf2.setInput(DMatrix(vf2.input(i).sparsity(),random.random(vf2.input(i).size())),i)
              
              vf2.evaluate()
              storagekey = (spmod,spmod2)
              if not(storagekey in storage2):
                storage2[storagekey] = []
              storage2[storagekey].append([vf2.getOutput(i) for i in range(vf2.getNumOutputs())])

      # Remainder of eval testing
      for store,order in [(storage,"first-order"),(storage2,"second-order")]:
        for stk,st in store.items():
          for i in range(len(st)-1):
            for k,(a,b) in enumerate(zip(st[0],st[i+1])):
              if b.numel()==0 and sparse(a).size()==0: continue
              if a.numel()==0 and sparse(b).size()==0: continue
              self.checkarray(sparse(a),sparse(b),("%s, output(%d)" % (order,k))+str(vf2.getInput(0)))
              
      for f in [fun.expand(),fun]:
        #  jacobian()
        for mode in ["forward","reverse"]:
          f.setOption("ad_mode",mode)
          f.init()
          Jf=f.jacobian(0,0)
          Jf.init()
          for i,v in enumerate(values):
            Jf.setInput(v,i)
          Jf.evaluate()
          self.checkarray(Jf.getOutput(),J_)
          self.checkarray(DMatrix(Jf.output().sparsity(),1),DMatrix(J_.sparsity(),1),str(out)+str(mode))
          self.checkarray(DMatrix(f.jacSparsity(),1),DMatrix(J_.sparsity(),1))
                
      # Scalarized
      if out.empty(): continue
      s_i  = out.sparsity().getCol()[0]
      s_j  = out.sparsity().row()[0]
      s_k = s_i*out.size1()+s_j
      fun = MXFunction(inputs,[out[s_i,s_j],jac[s_k,:].T])
      fun.init()
        
      for i,v in enumerate(values):
        fun.setInput(v,i)
        
        
      fun.evaluate()
      J_ = fun.getOutput(1)
      
      for f in [fun,fun.expand()]:
        #  gradient()
        for mode in ["forward","reverse"]:
          f.setOption("ad_mode",mode)
          f.init()
          Gf=f.gradient(0,0)
          Gf.init()
          for i,v in enumerate(values):
            Gf.setInput(v,i)
          Gf.evaluate()
          self.checkarray(Gf.getOutput(),J_,failmessage=("mode: %s" % mode))
          #self.checkarray(DMatrix(Gf.output().sparsity(),1),DMatrix(J_.sparsity(),1),str(mode)+str(out)+str(type(fun)))

      H_ = None
      
      for f in [fun,fun.expand()]:
        #  hessian()
        for mode in ["forward","reverse"]:
          f.setOption("ad_mode",mode)
          f.init()
          Hf=f.hessian(0,0)
          Hf.init()
          for i,v in enumerate(values):
            Hf.setInput(v,i)
          Hf.evaluate()
          if H_ is None:
            H_ = Hf.getOutput()
          self.checkarray(Hf.getOutput(),H_,failmessage=("mode: %s" % mode))
          #self.checkarray(DMatrix(Gf.output().sparsity(),1),DMatrix(J_.sparsity(),1),str(mode)+str(out)+str(type(fun)))
    
if __name__ == '__main__':
    unittest.main()

