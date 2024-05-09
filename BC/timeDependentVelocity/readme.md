*this is a temp guide for how to create a new boundary class, I shall replace this guide to obsdian note later.*
# foamNewBC

## use `foamNewBC` to create a BC class 
You could use  `foamNewBC -help`to get help from openfoam.
```
...
conditions:
-f | -fixedValue    | fixedValue
-m | -mixed         | mixed

<type> options:
-a | -all    | all  | template (creates a template class)
-s | -scalar | scalar
-v | -vector | vector
-t | -tensor | tensor
-symmTensor  | symmTensor
-sphericalTensor | sphericalTensor
...
```
Enter`foamNewBC -f -v timeDependentVelocity` in commend line  to create a new time dependent velocity boundary class.

Enter the folder which the command created, and compile the libso.
```shell
cd timeDependentVeolocity
wmake libso
```

Description in about the .H file:

*This boundary condition provides a timeDependentVelocity condition,*
*which calculated as:*
            $$Q = Q_{0} + Q_{p} + s Q(t)$$
*where:*

| symbol  | Description               |
| ------- | ------------------------- |
| $s$     | single scalar value       |
| $Q_{0}$ | single vector value       |
| $Q_{p}$ | vector field across patch |
| $Q(t)$  | vector function of time   |

example of the boundary condition in 0/U/inlet file:
```   
    <patchName>
    {
        type       timeDependentVelocity;
        scalarData -1;
        data       (1 0 0);
        fieldData  uniform (3 0 0);
        timeVsData table (
                             (0 (0 0 0))
                             (1 (2 0 0))
                          );
        wordName   anotherName;
        value      uniform (4 0 0); 
    }
```

Copy the test case and modify the 0/U/inlet content. 
And replace the \<pathch> string to the patch name you want to test.
```shell
cp -r ../../Case/3UnitTestCase .
code 3UnitTestCase/0/U
```
Remerber to add
`libs ("libtimeDependentVelocity.so");`
 to the system/controDict.
And switch to the working folder and run test application.

```shell
cd 3UnitTestCase
# build mesh
blockMesh
# run test Solver
testBoundaryFoam
```

## some infomation about the boundary condition class 

The declaration of the boundary condition class is in the .H file. 

### private data and private member function

`scalar scalarData_`
We could see all private data has been defined in the 0/U file. When the solver is running, Openfoam will read the data from dict file and assosiate the data from dict file to the private data by Boundary condition class's constructor function.

`scalar t() const`

This private function is help us to get the time value when runtime looping. The function return scalar type value, so it's easy to manipulate the time value with the other scalar value as we need.

### constructor function

`timeDependentVelocityFvPatchVectorField()`

There are several constructor functions in this class. we don't need pay too mucn attention to the constructor function. We should only know that when we create a new boundary condition class, we should define the constructor function in the .C file like the template do.

### public member function

`virtual void updateCoeffs();`


*updateCoeffs() Update the coefficients associated with the patch field*

you could see the specific implementation of the time-dependent boundary condition in the related .c file. Remember to call the `fixedValueFvPatchVectorField::updateCoeffs()` function in the .c file.