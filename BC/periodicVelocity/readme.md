## periodicVelocity

We are going to craete a periodic velocity boundary which calculate as:
$$V = V_{0} + sin(t) \cdot V_{p}$$
where:
V: periodic velocity
V_{0}: initial velocity
V_{p}: velocity amplitude
t: time

### Create a new periodic velocity boundary condition

```shell
foamNewBC -f -v periodicVelocity
```

convert the equantion variables to the code variables:
$V_{0}$ -> `vector V_0`
$V_{p}$ -> `vector V_p`
Modify the private data members in the periodicVelocity.H file:
```cpp
    //- Private data members
    vector V_0_;
    vector V_p_;

    vectorField fieldData_;

```cpp

the constructor should be changed to adapte the new varibles:
for example:

```
Foam::periodicVelocityFvPatchVectorField::
periodicVelocityFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const dictionary& dict
)
:
    fixedValueFvPatchVectorField(p, iF),
    V_0_(dict.lookup<vector>("V0")),
    V_p_(dict.lookup<vector>("Vp"))
{


    fixedValueFvPatchVectorField::evaluate();
    (
        vectorField("value", dict, p.size())
    );
}

```

We have made all the necessary pre-changes. Then the updateCoeffs() function should be modified to calculate the periodic velocity:
```cpp
void Foam::periodicVelocityFvPatchVectorField::updateCoeffs()
{
    if (updated())
    {
        return;
    }

    fixedValueFvPatchVectorField::operator==
    (
        V_0_+V_p_*sin(2.0*Foam::constant::mathematical::pi*t())
    );


    fixedValueFvPatchVectorField::updateCoeffs();
}
```        

```
wmake libso
```

change the 0/U file
```
    inlet
    {
        type       periodicVelocity;
        V0       (0 0 0);
        Vp       (1 0 0);
    }
```

add libso to system/controlDict
```
libs
(
    "libperiodicVelocity.so"
);
```

run test solver
```
testBoundaryFoam
```
