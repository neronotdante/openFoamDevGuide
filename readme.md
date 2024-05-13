# Info
This repository is used to record the learning process of openfoam. Mainly focus on
how a beginner use the openfoam to create a CFD case, a unique solver and a user define 
boundary condition. This learning guide cover 3 parts:

## Case

### 3 unit test case

## Solver

### testBoundaryFoam

`testBoundaryFoam` is the first solver we are going to create. It is a simple solver that don't do any 
calculate but just upgrate the boundary value when the time step is updated.

### waveEquationFoam

This part introduces how to solve a wave equation PDE. where the control function:


$$\frac{\partial^2u}{\partial t^2} = c^2 \nabla^2 u$$

## BC(Boundary Condition)

### timeDependentVelocity

The first boundary condition only use openfoam `newFoamBC` tool. This part will tell us how to create a new boundary condition libso file and how to use it in the case.

### periodicVelocity

A time dependent velocity boundary condition base on the `timeDependentVelocity`. This part will show you how to create a sin() like periodic boundary condition.

### complicatedVelocity

A boundary which is time and location dependent.

# My Enviorment

1.linux(wsl2)
2.openfoam10

# Suggestion
I fully recommend everyone who is going to study the openfoam has the knowdgement about

1. OOP(Object-oriented programming);
2. N-S equation;

# Update Schedule

## Solvers
    1. How to use openfoam framework solve a easy patical differential equation like;
        a. wave equation
        b. scalar transform equation

    2. `icoFoam` and `simpleFoam` source code and algorithm;

    3. ...

## Boundary Conditon
    1. How to create a time and location dependent velocity boundary condition;

    2. Analyze the boundary class source code.

# Reference

1.3 unit case*ref :https://zhuanlan.zhihu.com/p/409130279*
2. wave equation*ref https://github.com/UnnamedMoose/BasicOpenFOAMProgrammingTutorials*
3. CFD algorithm and CFD infomation *http://dyfluid.com/*