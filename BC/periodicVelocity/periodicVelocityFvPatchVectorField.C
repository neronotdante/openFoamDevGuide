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

#include "periodicVelocityFvPatchVectorField.H"
#include "addToRunTimeSelectionTable.H"
#include "fvPatchFieldMapper.H"
#include "volFields.H"
#include "surfaceFields.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

Foam::scalar Foam::periodicVelocityFvPatchVectorField::t() const
{
    return db().time().userTimeValue();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::periodicVelocityFvPatchVectorField::
periodicVelocityFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedValueFvPatchVectorField(p, iF),
    V_0_(Zero),
    V_p_(Zero)
{
}


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

    /*
    // Initialise with the value entry if evaluation is not possible
    fvPatchVectorField::operator=
    (
        vectorField("value", dict, p.size())
    );
    */
}


Foam::periodicVelocityFvPatchVectorField::
periodicVelocityFvPatchVectorField
(
    const periodicVelocityFvPatchVectorField& ptf,
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedValueFvPatchVectorField(ptf, p, iF, mapper),
    V_0_(ptf.V_0_),
    V_p_(ptf.V_p_)
{}


Foam::periodicVelocityFvPatchVectorField::
periodicVelocityFvPatchVectorField
(
    const periodicVelocityFvPatchVectorField& ptf,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedValueFvPatchVectorField(ptf, iF),
    V_0_(ptf.V_0_),
    V_p_(ptf.V_p_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::periodicVelocityFvPatchVectorField::autoMap
(
    const fvPatchFieldMapper& m
)
{
    fixedValueFvPatchVectorField::autoMap(m);
    m(fieldData_, fieldData_);
}


void Foam::periodicVelocityFvPatchVectorField::rmap
(
    const fvPatchVectorField& ptf,
    const labelList& addr
)
{
    fixedValueFvPatchVectorField::rmap(ptf, addr);

    const periodicVelocityFvPatchVectorField& tiptf =
        refCast<const periodicVelocityFvPatchVectorField>(ptf);

    fieldData_.rmap(tiptf.fieldData_, addr);
}


void Foam::periodicVelocityFvPatchVectorField::reset
(
    const fvPatchVectorField& ptf
)
{
    fixedValueFvPatchVectorField::reset(ptf);

    const periodicVelocityFvPatchVectorField& tiptf =
        refCast<const periodicVelocityFvPatchVectorField>(ptf);

    fieldData_.reset(tiptf.fieldData_);
}


void Foam::periodicVelocityFvPatchVectorField::updateCoeffs()
{
    if (updated())
    {
        return;
    }

    fixedValueFvPatchVectorField::operator==
    (
        V_0_+V_p_*cos(t()/0.1*2*Foam::constant::mathematical::pi)
    );


    fixedValueFvPatchVectorField::updateCoeffs();
}


void Foam::periodicVelocityFvPatchVectorField::write
(
    Ostream& os
) const
{
    fvPatchVectorField::write(os);
    writeEntry(os,"V0",V_0_);
    writeEntry(os,"Vp",V_p_);
    writeEntry(os, "fieldData", fieldData_);
    writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * Build Macro Function  * * * * * * * * * * * * //

namespace Foam
{
    makePatchTypeField
    (
        fvPatchVectorField,
        periodicVelocityFvPatchVectorField
    );
}

// ************************************************************************* //
