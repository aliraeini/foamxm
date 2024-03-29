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
    meshSurfaceEdgeExtractor2D

Description
    Stores boundary faces into patches and captures edges and corners

SourceFiles
    meshSurfaceEdgeExtractor2D.C

\*---------------------------------------------------------------------------*/

#ifndef meshSurfaceEdgeExtractor2D_H
#define meshSurfaceEdgeExtractor2D_H

#include "polyMeshGenModifier.H"
#include "boolList.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declarations
class meshOctree;
class meshSurfaceEngine;


class meshSurfaceEdgeExtractor2D
{
    // Private data
        //- mesh
        polyMeshGen& mesh_;

        //- octree
        const meshOctree& meshOctree_;

    // Private member functions

        //- Disallow default bitwise copy construct
        meshSurfaceEdgeExtractor2D(const meshSurfaceEdgeExtractor2D&);

        //- Disallow default bitwise assignment
        void operator=(const meshSurfaceEdgeExtractor2D&);

public:

    // Constructors

        //- Construct from mesh data
        meshSurfaceEdgeExtractor2D
        (
            polyMeshGen& mesh,
            const meshOctree& octree
        );

    // Destructor

        ~meshSurfaceEdgeExtractor2D();

    // Member Functions
        //- distribute boundary faces into patches
        void distributeBoundaryFaces();

        //- re-map points after edges have been extracted
        void remapBoundaryPoints();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
