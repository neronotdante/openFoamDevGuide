
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

## More

We have already know that `fvm::d2t2(phi)` represent $\frac{\partial \phi^2}{\partial^2t}$ What will happend when we use `fvm::ddt`? The Control euqation will change like this:

$$\frac{\partial U}{\partial t} = C \nabla^2 U$$

where U is not a good symbol for scalar so we change it to $T$:

$$\frac{\partial T}{\partial t} = C \nabla^2 T$$

Tips: We have change the PDE type, so do not forget to change the unit of C in .H file and physicalPropertries File.

The formula above is a scalar transport equation without source term and conviction term. 

Compile it, run it and paraview it, in the testCase folder.

