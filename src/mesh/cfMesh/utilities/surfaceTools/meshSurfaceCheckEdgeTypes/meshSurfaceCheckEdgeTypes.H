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
    meshSurfaceCheckEdgeTypes

Description
    Checks if any of the surface is tangled at any of its vertices. This
    is performed by checking the dot product between the vertex normal and
    the normals of the faces attached to the vertex.

SourceFiles
    meshSurfaceCheckEdgeTypes.C

\*---------------------------------------------------------------------------*/

#ifndef meshSurfaceCheckEdgeTypes_H
#define meshSurfaceCheckEdgeTypes_H

#include "polyMeshGenModifier.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declarations
class meshSurfaceEngine;


class meshSurfaceCheckEdgeTypes
{
    // Private data
        //- mesh surface
        const meshSurfaceEngine& surfaceEngine_;

        //- a list which classifies each edge
        List<direction> edgeType_;

    // Private member functions
        //- check feature edges and classify them
        void classifyEdges();

        //- Disallow default bitwise copy construct
        meshSurfaceCheckEdgeTypes
        (
            const meshSurfaceCheckEdgeTypes&
        );

        //- Disallow default bitwise assignment
        void operator=(const meshSurfaceCheckEdgeTypes&);

public:

    // Enumerators

        enum edgeTypes_
        {
            NONE = 0,
            PATCHEDGE = 1,
            FEATUREEDGE = 2,
            CONVEXEDGE = 4,
            CONCAVEEDGE = 8,
            UNDETERMINED = 16
        };

    // Constructors

        //- Construct from meshSurfaceEngine
        meshSurfaceCheckEdgeTypes(const meshSurfaceEngine&);

    // Destructor

        ~meshSurfaceCheckEdgeTypes();

    // Member Functions
        //- return the information about classified edges
        const List<direction>& edgeTypes() const
        {
            return edgeType_;
        }

        //- return indices of convex edges
        void convexEdges(labelLongList& convexEdges) const;

        //- return indices of concave edges
        void concaveEdges(labelLongList& concaveEdges) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
