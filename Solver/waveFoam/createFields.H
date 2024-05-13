
Info<< "Reading field U\n" << endl;

volScalarField U
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


Info<< "Reading physicalProperties\n" << endl;

IOdictionary physicalProperties
(
    IOobject
    (
        "physicalProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);


Info<< "C\n" << endl;

dimensionedScalar C
(
    "C",
    // dimensionSet(0, 1,-1,0,0,0,0),
    dimensionSet(0, 2,-1,0,0,0,0),
    physicalProperties.lookup("C")
);


