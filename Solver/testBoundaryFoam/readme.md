# An easy openFoam solver to test the boundary class

## Description 

*This foam is a solver that only contain a time loop and data write function which is the 
best choice to check the boundary class is useful or not.*

## How to use

1. walk in to the case folder 
```shell
cd cavity
```
2. run the solver
```shell
testBoundaryFoam
```
3. open paraview and load the data
```shell
touch .foam
# in wsl environment and ensure your windows has installed paraview
paraview.exe .foam
```

## core code 
1. .C file
```cpp

    while(runTime.loop())
    {
        U.correctBoundaryConditions();

        runTime.write();
    }
```

2. createFields.H file
```cpp

Info<< "Reading field p\n" << endl;
// scalar field declaration
volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

// vector field declaration
Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

```

### runTime.loop()

### U.correctBoundaryConditions()

### runTime.write()