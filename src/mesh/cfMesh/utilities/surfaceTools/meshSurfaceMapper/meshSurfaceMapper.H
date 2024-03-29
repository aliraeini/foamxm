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
    meshSurfaceMapper

Description
    Maps vertices to the nearest point on the geometry surface

SourceFiles
    meshSurfaceMapper.C

\*---------------------------------------------------------------------------*/

#ifndef meshSurfaceMapper_H
#define meshSurfaceMapper_H

#include "labelList.H"
#include "pointField.H"
#include "labelLongList.H"
#include "parMapperHelper.H"

#include <map>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declarations
class meshOctree;
class meshSurfaceEngine;
class meshSurfacePartitioner;
class triSurfacePartitioner;


class meshSurfaceMapper
{
    // Private data
        //- mesh surface
        const meshSurfaceEngine& surfaceEngine_;

        //- reference to the octree
        const meshOctree& meshOctree_;

        //- mesh surface partitioner
        mutable const meshSurfacePartitioner* surfaceEnginePartitionerPtr_;
        const bool deletePartitioner_;

        //- triSurface partitioner
        mutable triSurfacePartitioner* surfPartitionerPtr_;

    // Private member functions
        //- create and return mesh surface partitioner
        void createMeshSurfacePartitioner() const;
        inline const meshSurfacePartitioner& meshPartitioner() const
        {
            if( !surfaceEnginePartitionerPtr_ )
                createMeshSurfacePartitioner();

            return *surfaceEnginePartitionerPtr_;
        }

        //- create and return triSurfacePartitioner
        void createTriSurfacePartitioner() const;
        inline const triSurfacePartitioner& surfacePartitioner() const
        {
            if( !surfPartitionerPtr_ )
                createTriSurfacePartitioner();

            return *surfPartitionerPtr_;
        }

        //- delete surfaceEnginePartitionerPtr_ and surfPartitionerPtr_
        void clearOut();

    // Private member functions
        //- map corner nodes to the boundary
        void mapCorners(const labelLongList& nodesToMap);

        //- find mapping distance for selected points
        void findMappingDistance
        (
            const labelLongList& nodesToMap,
            scalarList & mappingDistance
        ) const;

        //- calculate face metric
        scalar faceMetricInPatch(const label bfI, const label patchI) const;

    // Private member functions needed for parallel execution

        //- check if nodes at parallel boundaries are selected at all processors
        void selectNodesAtParallelBnd(const labelLongList&);

        //- map to the smallest distance
        //- makes sense for parallel calculations, only
        void mapToSmallestDistance(LongList<parMapperHelper>&);

        //- Disallow default bitwise copy construct
        meshSurfaceMapper(const meshSurfaceMapper&);

        //- Disallow default bitwise assignment
        void operator=(const meshSurfaceMapper&);

public:

    // Constructors

        //- Construct from meshSurfaceEngine and octree
        meshSurfaceMapper(const meshSurfaceEngine&, const meshOctree&);

        //- Construct from meshSurfacePartitioner and octree
        meshSurfaceMapper(const meshSurfacePartitioner&, const meshOctree&);

    // Destructor

        ~meshSurfaceMapper();

    // Member Functions
        //- map the given surface node on the selected patch
        //- this does not make sense for vertices at parallel boundaries
        void mapNodeToPatch(const label bpI, const label patchI = -1);

        //- projects surface vertices onto their nearest location
        //- on the surface mesh
        void mapVerticesOntoSurface();

        //- projects selected surface vertices to their nearest location
        //- on the surface mesh
        void mapVerticesOntoSurface(const labelLongList& nodesToMap);

        //- projects corner and edge vertices onto their nearest location
        //- on the surface mesh
        void mapCornersAndEdges();

        //- projects selected edge vertices onto their nearest
        //- locations on the surface mesh
        void mapEdgeNodes(const labelLongList& nodesToMap);

        //- projects surface vertices onto the surface with respect
        //- to the surface patch they belong to. Edges and corner are respected
        void mapVerticesOntoSurfacePatches();

        //- projects selected surface vertices onto the surface with respect
        //- to the surface patch they belong to. Edges and corner are respected
        void mapVerticesOntoSurfacePatches(const labelLongList& nodesToMap);

        //- a combination of mapping and smoothing intended for better
        //- feature capturing
        void preMapVertices(const label nIterations = 3);
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
