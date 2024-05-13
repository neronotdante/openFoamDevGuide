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

### waveFoam

This part introduces how to solve a wave equation PDE. where the control euqation:


$$\frac{\partial^2u}{\partial t^2} = c^2 \nabla^2 u$$

$u$ : wave's amplitude

$c$ : wave's speed

$t$ : time

## Boundary Condition 

### timeDependentVelocity

The first boundary condition only use openfoam `newFoamBC` tool. This part will tell us how to create a new boundary condition libso file and how to use it in the case.

### periodicVelocity

A time dependent velocity boundary condition base on the `timeDependentVelocity`. This part will show you how to create a sin() like periodic boundary condition.

### complicatedVelocity

A boundary which is time and location dependent.

# My Enviorment

1.openfoam10

# Suggestion
I fully recommend everyone who is going to study the openfoam has the knowdgement about

1. OOP(Object-oriented programming);
2. N-S equation;
3. ....

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

## Openfoam Class
1. 

# Reference

1. 3 unit case *:https://zhuanlan.zhihu.com/p/409130279*
2. wave equation *https://github.com/UnnamedMoose/BasicOpenFOAMProgrammingTutorials*
3. CFD algorithm and CFD infomation *http://dyfluid.com/*
4. openfoam wiki *https://openfoamwiki.net/index.php/Main_Page*
5. openFOAM source code *https://openfoam.org/release/10/*