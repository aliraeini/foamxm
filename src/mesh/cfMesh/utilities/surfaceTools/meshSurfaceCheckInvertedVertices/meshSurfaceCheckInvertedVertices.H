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
    meshSurfaceCheckInvertedVertices

Description
    Checks if any of the surface is tangled at any of its vertices. This
    is performed by checking the dot product between the vertex normal and
    the normals of the faces attached to the vertex.

SourceFiles
    meshSurfaceCheckInvertedVertices.C

\*---------------------------------------------------------------------------*/

#ifndef meshSurfaceCheckInvertedVertices_H
#define meshSurfaceCheckInvertedVertices_H

#include "polyMeshGenModifier.H"
#include "HashSet.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declarations
class meshSurfacePartitioner;


class meshSurfaceCheckInvertedVertices
{
    // Private data
        //- mesh surface partitioner
        const meshSurfacePartitioner& surfacePartitioner_;

        //- active surface points
        const boolList* activePointsPtr_;

        //- set of inverted vertices
        labelHashSet invertedVertices_;

    // Private member functions
        //- check vertices by calculating dot products
        void checkVertices();

        //- Disallow default bitwise copy construct
        meshSurfaceCheckInvertedVertices
        (
            const meshSurfaceCheckInvertedVertices&
        );

        //- Disallow default bitwise assignment
        void operator=(const meshSurfaceCheckInvertedVertices&);

public:

    // Constructors

        //- Construct from meshSurfacePartitioner
        meshSurfaceCheckInvertedVertices
        (
            const meshSurfacePartitioner&
        );

        //- Construct from meshSurfacePartitioner and a list of active points
        meshSurfaceCheckInvertedVertices
        (
            const meshSurfacePartitioner&,
            const boolList& activePoints
        );

    // Destructor

        ~meshSurfaceCheckInvertedVertices();

    // Member Functions
        //- return the labels of inverted vertices
        inline const labelHashSet& invertedVertices() const
        {
            return invertedVertices_;
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
