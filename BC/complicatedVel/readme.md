## Description

We have created a refined version of the three unit test mesh, and a boundary contion which value 
will modify when time changes. So, this part will show you how to create a BC which value will change
when the time and location changes. Like this:

$$V = V_{loc}(x,y,z) + V_{time}(t)$$

## Tutorial
Create a new boundary condition class and walk into the folder.
```bash
foamNewBC -f -v complicatedVel
cd complicatedVel
```

We have already known that how to access the time by `t()` private memeber function in the `fvPatchField` class. So, we can use this function to get the time. And we can also get the location by `this->patch().Cf()`. So, we can get the location and time. 

The patch() function is defined in `FvPatch` class. It return a `polyPatch` class.The more information about this class can be found here [OpenFOAM Official Document](https://cpp.openfoam.org/v10/classFoam_1_1fvPatch.html).

There are other function in polyPatch class, like
```CPP

    //- Return face centres
    const vectorField& Cf() const;

    //- Return neighbour cell centres
    tmp<vectorField> Cn() const;

    //- Return face area vectors
    const vectorField& Sf() const;

    //- Return face area magnitudes
    const scalarField& magSf() const;

    //- Return face normals
    tmp<vectorField> nf() const;

    //- Return cell-centre to face-centre vector
    //  except for coupled patches for which the cell-centre
    //  to coupled-cell-centre vector is returned
    virtual tmp<vectorField> delta() const;
...
```
