/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | foam-extend: Open Source CFD
   \\    /   O peration     | Version:     4.1
    \\  /    A nd           | Web:         http://www.foam-extend.org
     \\/     M anipulation  | For copyright notice see file Copyright
-------------------------------------------------------------------------------
                     Author | F.Juretic (franjo.juretic@c-fields.com)
                  Copyright | Copyright (C) Creative Fields, Ltd.
-------------------------------------------------------------------------------
License
    This file is part of foam-extend.

    foam-extend is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 3 of the License, or (at your
    option) any later version.

    foam-extend is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with foam-extend.  If not, see <http://www.gnu.org/licenses/>.

Class
    coneRefinement

Description
    Refine boxes with centres contained inside the cone

SourceFiles
    coneRefinement.C

\*---------------------------------------------------------------------------*/

#ifndef coneRefinement_H
#define coneRefinement_H

#include "objectRefinement.H"
#include "point.H"
#include "typeInfo.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


class coneRefinement
:
    public objectRefinement
{
    // Private data
        //- start point and the radius
        point p0_;
        scalar r0_;

        //- end point and the radius
        point p1_;
        scalar r1_;

public:

    //- Runtime type information
    TypeName("cone");


    // Constructors

        //- Null construct
        coneRefinement();

        //- Construct from name, cell size, centre and radius
        coneRefinement
        (
            const word& name,
            const scalar cellSize,
            const direction additionalRefLevels,
            const point& p0,
            const scalar radius0,
            const point& p1,
            const scalar radius1
        );

        //- Construct from dictionary
        coneRefinement(const word& name, const dictionary& dict);

        //- Construct and return a clone
        virtual autoPtr<objectRefinement> clone
        (
            const coneRefinement& sr
        ) const
        {
            return autoPtr<objectRefinement>
            (
                new coneRefinement
                (
                    sr.name(),
                    sr.cellSize(),
                    sr.additionalRefinementLevels(),
                    sr.p0_,
                    sr.r0_,
                    sr.p1_,
                    sr.r1_
                )
            );
        }

    // Member Functions

        //- check if a boundBox intersects or is inside the object
        bool intersectsObject(const boundBox&) const;

    //- Return as dictionary of entries
        dictionary dict(bool ignoreType = false) const;

      // Write

        //- Write
        void write(Ostream&) const;

        //- Write dictionary
        void writeDict(Ostream&, bool subDict = true) const;

    // Member Operators

        //- assign from dictionary
        void operator=(const dictionary&);

    // IOstream Operators

        Ostream& operator<<(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
