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
    surfaceMeshGeometryModification

Description
    Modifies geometry of surface meshes according to the anisotropic sources
    given by the user

SourceFiles
    surfaceMeshGeometryModification.C

\*---------------------------------------------------------------------------*/

#ifndef surfaceMeshGeometryModification_H
#define surfaceMeshGeometryModification_H

#include "coordinateModification.H"
#include "point.H"
#include "typeInfo.H"
#include "coordinateModifier.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class triSurf;
class dictionary;


class surfaceMeshGeometryModification
{
    // Private data
        //- reference to triSurf
        const triSurf& surf_;

        //- length of box sides
        const dictionary& meshDict_;

        //- contruct coordinate modification
        coordinateModifier* coordinateModifierPtr_;

        //- is mofdification active
        bool modificationActive_;


    // Private member functions
        //- check existence of geometry modifiers
        void checkModification();

        //- disallow bitwise copy construct
        surfaceMeshGeometryModification(const surfaceMeshGeometryModification&);

        //- disallow bitwise assignment
        void operator=(const surfaceMeshGeometryModification&);

public:

    // Constructors

        //- Construct from triSurf and dictionary
        surfaceMeshGeometryModification(const triSurf&, const dictionary&);

    // Destructor
        ~surfaceMeshGeometryModification();

    // Member Functions

        //- is geometry modification active
        bool activeModification() const;

        //- modify coordinates
        const triSurf* modifyGeometry() const;

        //- revert geometry modification
        const triSurf* revertGeometryModification() const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
