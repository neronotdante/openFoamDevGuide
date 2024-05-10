
# wave equation

$$\frac{ \partial^2 U }{ \partial^2 t } =c^2\nabla^2U$$

## decription
*The wave equation is a second-order linear partial differential equation for the description of waves or standing wave fields such as mechanical waves (e.g. water waves, sound waves and seismic waves) or electromagnetic waves (including light waves). It arises in fields like acoustics, electromagnetism, and fluid dynamics.*[wiki]

# waveFoam

First, we need to use `foamNewApp waveFoam` to create a new solver named `waveFoam`.

```bash
foamNewApp waveFoam
```


## createFields.H

Use IOobject to control read and write the fields value and coffes. 

## .C file

Add a runtime looping code in the `main` function.

```cpp
    while (runTime.loop())
    {
        // print solving time
        Info<< "Time = " << runTime.timeName() << nl << endl;
        runTime++;
    }
```

create a equation in runTime loop, solve and write it.
```cpp
...
        fvScalarMatrix uEqn
        (
            fvm::d2dt2(U)
            == fvm::laplacian(sqr(C), U)
        );

        uEqn.solve();

        runTime.write();
...
```

compile it and run in testCase folder
```shell
wmake
cd testCase
blockMesh
setFields
waveFoam
```

