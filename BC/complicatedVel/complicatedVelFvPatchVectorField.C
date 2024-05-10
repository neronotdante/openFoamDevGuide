/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2024 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "complicatedVelFvPatchVectorField.H"
#include "addToRunTimeSelectionTable.H"
#include "fvPatchFieldMapper.H"
#include "volFields.H"
#include "surfaceFields.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

Foam::scalar Foam::complicatedVelFvPatchVectorField::t() const
{
    return db().time().userTimeValue();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::complicatedVelFvPatchVectorField::
complicatedVelFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedValueFvPatchVectorField(p, iF),
    scalarData_(0.0),
    vectorData_(Zero)
{
}


Foam::complicatedVelFvPatchVectorField::
complicatedVelFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const dictionary& dict
)
:
    fixedValueFvPatchVectorField(p, iF),
    scalarData_(dict.lookup<scalar>("scalarData")),
    vectorData_(dict.lookup<vector>("vectorData"))
{

    Foam::Info<<scalarData_<<endl;
    Foam::Info<<vectorData_<<endl;
    fixedValueFvPatchVectorField::evaluate();

    /*
    // Initialise with the value entry if evaluation is not possible
    fvPatchVectorField::operator=
    (
        vectorField("value", dict, p.size())
    );
    */
}


Foam::complicatedVelFvPatchVectorField::
complicatedVelFvPatchVectorField
(
    const complicatedVelFvPatchVectorField& ptf,
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedValueFvPatchVectorField(ptf, p, iF, mapper),
    scalarData_(ptf.scalarData_),
    vectorData_(ptf.vectorData_)
{}


Foam::complicatedVelFvPatchVectorField::
complicatedVelFvPatchVectorField
(
    const complicatedVelFvPatchVectorField& ptf,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedValueFvPatchVectorField(ptf, iF),
    scalarData_(ptf.scalarData_),
    vectorData_(ptf.vectorData_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::complicatedVelFvPatchVectorField::autoMap
(
    const fvPatchFieldMapper& m
)
{
    fixedValueFvPatchVectorField::autoMap(m);
    m(fieldData_, fieldData_);
}


void Foam::complicatedVelFvPatchVectorField::rmap
(
    const fvPatchVectorField& ptf,
    const labelList& addr
)
{
    fixedValueFvPatchVectorField::rmap(ptf, addr);

    const complicatedVelFvPatchVectorField& tiptf =
        refCast<const complicatedVelFvPatchVectorField>(ptf);

    fieldData_.rmap(tiptf.fieldData_, addr);
}


void Foam::complicatedVelFvPatchVectorField::reset
(
    const fvPatchVectorField& ptf
)
{
    fixedValueFvPatchVectorField::reset(ptf);

    const complicatedVelFvPatchVectorField& tiptf =
        refCast<const complicatedVelFvPatchVectorField>(ptf);

    fieldData_.reset(tiptf.fieldData_);
}


void Foam::complicatedVelFvPatchVectorField::updateCoeffs()
{
    if (updated())
    {
        return;
    }

    vectorField U = patch().Sf() * (-1);

    Foam::Info<< U<< endl;

    forAll(patch().Cf(),faceIndex)
    {
        vector patchCenter = patch().Cf()[faceIndex];
        scalar y = patchCenter.y(); 
        
        vector timeDepnet = vectorData_ * t();
        if(y < 0.5)
        {
            U[faceIndex] *= 0;
            Info << U[faceIndex]<<endl;
        }
        else
        {
            U[faceIndex]  = timeDepnet;
            Info << U[faceIndex]<<endl;
        }

    }

        fixedValueFvPatchVectorField::operator==
        (
            U
        );


    fixedValueFvPatchVectorField::updateCoeffs();
}


void Foam::complicatedVelFvPatchVectorField::write
(
    Ostream& os
) const
{
    fvPatchVectorField::write(os);
    writeEntry(os, "scalarData", scalarData_);
    writeEntry(os,"vectorData",vectorData_);
    writeEntry(os, "fieldData", fieldData_);
}


// * * * * * * * * * * * * * * Build Macro Function  * * * * * * * * * * * * //

namespace Foam
{
    makePatchTypeField
    (
        fvPatchVectorField,
        complicatedVelFvPatchVectorField
    );
}

// ************************************************************************* //
