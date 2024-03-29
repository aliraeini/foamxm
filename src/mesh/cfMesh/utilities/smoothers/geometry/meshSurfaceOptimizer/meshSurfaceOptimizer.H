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
    meshSurfaceOptimizer

Description
    Surface smoothing without any topological changes

SourceFiles
    meshSurfaceOptimizer.C

\*---------------------------------------------------------------------------*/

#ifndef meshSurfaceOptimizer_H
#define meshSurfaceOptimizer_H

#include "polyMeshGen.H"
#include "boolList.H"
#include "labelLongList.H"
#include "DynList.H"
#include "triFace.H"
#include "meshSurfaceEngine.H"
#include "parTriFace.H"
#include "meshSurfacePartitioner.H"
#include "partTriMesh.H"

#include <map>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declarations
class meshOctree;
class meshSurfaceMapper;
class plane;


class meshSurfaceOptimizer
{
    // Private data
        //- const reference to the mesh surface
        const meshSurfaceEngine& surfaceEngine_;

        //- type of surface vertex
        List<direction> vertexType_;

        //- locked faces which shall not be changed
        labelLongList lockedSurfaceFaces_;

        //- surface partitioner
        const meshSurfacePartitioner* partitionerPtr_;
        const bool deletePartitioner_;

        //- pointer to mesh octree
        const meshOctree* octreePtr_;

        //- mesh of surface triangles needed for some smoothers
        mutable partTriMesh* triMeshPtr_;

        //- enforce constraints
        bool enforceConstraints_;

        //- name of the subset contaning tangled points
        word badPointsSubsetName_;

    // Private member functions
        //- classify surface vertices as PARTITION, EDGE, CORNER
        void classifySurfaceVertices();

        //- calculate surface triangulation
        void calculateTrianglesAndAddressing() const;
        inline const partTriMesh& triMesh() const;
        inline void updateTriMesh(const labelLongList&);
        inline void updateTriMesh();

        //- find vertices which are inverted
        //- mark additional layers of vertices near the inverted ones
        label findInvertedVertices
        (
            boolList& smoothVertex,
            const label nAdditionalLayers = 2
        ) const;

        //- transform into a 2D space in plane
        inline bool transformIntoPlane
        (
            const label bpI,
            const plane& pl,
            vector& vecX,
            vector& vecY,
            DynList<point>& pts,
            DynList<triFace>& trias
        ) const;

        //- new position of a node after laplacian smoothing
        //- the position is the average of neighbouring vertex positions
        inline point newPositionLaplacian
        (
            const label bpI,
            const bool transformIntoPlane = true
        ) const;

        //- new position of a node after laplacian smoothing
        //- the position is the average of neighbouring face centres
        inline point newPositionLaplacianFC
        (
            const label bpI,
            const bool transformIntoPlane = true
        ) const;

        //- new position of a node after laplacian smoothing
        //- the position is the weighted average of neighbouring face centres
        //- the weights are the magnitudes of neighbouring face area vectors
        inline point newPositionLaplacianWFC
        (
            const label bpI,
            const bool transformIntoPlane = true
        ) const;

        //- new position of a node after using surfaceOptimizer
        inline point newPositionSurfaceOptimizer
        (
            const label bpI,
            const scalar tol = 0.001
        ) const;

        //- new position of edge vertex
        //- the position is the average of neighbouring edge vertices
        inline point newEdgePositionLaplacian(const label bpI) const;

        //- smooth the node using the laplacian smoother
        //- new position is the average of the neighbouring vertices
        void nodeDisplacementLaplacian
        (
            const label bpI,
            const bool transformIntoPlane = true
        ) const;

        //- smooth the node using the laplacian smoother
        //- new position is the average of the centres of faces attached
        //- to the vertex
        void nodeDisplacementLaplacianFC
        (
            const label bpI,
            const bool transformIntoPlane = true
        ) const;

        //- smooth the node using surface optimizer
        void nodeDisplacementSurfaceOptimizer
        (
            const label bpI,
            const scalar tol = 1.0
        );

        //- smooth edge node
        void edgeNodeDisplacement(const label bpI) const;

        //- smooth selected edge points
        void smoothEdgePoints
        (
            const labelLongList& edgePoints,
            const labelLongList& procEdgePoints
        );

        //- smooth selected points using laplaceFC
        void smoothLaplacianFC
        (
            const labelLongList& selectedPoints,
            const labelLongList& selectedProcPoints,
            const bool transform = true
        );

        //- smooth selected points using surface optimizer
        void smoothSurfaceOptimizer
        (
            const labelLongList& selectedPoints,
            const labelLongList& selectedProcPoints
        );

    // Functions needed for parallel runs

        //- transfer data between processors
        void exchangeData
        (
            const labelLongList& nodesToSmooth,
            std::map<label, DynList<parTriFace> >& m
        ) const;

        //- laplacian smoothing of points at processor boundaries
        //- new position is the average of the neighbouring vertices
        void nodeDisplacementLaplacianParallel
        (
            const labelLongList& nodesToSmooth,
            const bool transformIntoPlane = true
        );

        //- laplacian smoothing of points at processor boundaries
        void nodeDisplacementLaplacianFCParallel
        (
            const labelLongList& nodesToSmooth,
            const bool transformIntoPlane = true
        );

        //- smooth edge nodes at processor boundaries
        void edgeNodeDisplacementParallel
        (
            const labelLongList& nodesToSmooth
        );

        //- Disallow default bitwise copy construct
        meshSurfaceOptimizer(const meshSurfaceOptimizer&);

        //- Disallow default bitwise assignment
        void operator=(const meshSurfaceOptimizer&);

    // Enumerators
        enum vertexTypes
        {
            PARTITION = 1,
            EDGE = 2,
            CORNER = 4,
            PROCBND = 8,
            LOCKED = 16
        };

public:

    // Constructors

        //- Construct from mesh surface
        meshSurfaceOptimizer(const meshSurfaceEngine&);

        //- Construct from partitioner
        meshSurfaceOptimizer(const meshSurfacePartitioner&);

        //- Construct from mesh surface and octree
        meshSurfaceOptimizer(const meshSurfaceEngine&, const meshOctree&);

        //- Construct from partitioner and octree
        meshSurfaceOptimizer
        (
            const meshSurfacePartitioner&,
            const meshOctree&
        );


    // Destructor

        ~meshSurfaceOptimizer();

    // Member Functions
        //- lock the boundary faces which shall not be modified
        template<class labelListType>
        inline void lockBoundaryFaces(const labelListType&);

        //- lock boundary points. They are not be moved.
        template<class labelListType>
        inline void lockBoundaryPoints(const labelListType&);

        //- lock edge points
        inline void lockFeatureEdges();

        //- reset to default constraints
        void removeUserConstraints();

        //- Flag stopping the meshing process if it is not possible
        //- to untangle the surface without sacrificing geometry constraints
        //- Points which must be moved away from the required position are
        //- stored into a point subset
        void enforceConstraints(const word subsetName="badPoints");

        //- runs a surface smoother on the selected boundary points
        bool untangleSurface
        (
            const labelLongList& activeBoundaryPoints,
            const label nAdditionalLayers = 0
        );

        //- checks for invertex surface elements and tries to untangle them
        //- it tries to keep the points on the surface for a couple
        //- of iteration and gives up the final iterations
        //- by default, it smooths two additional layers of elements
        //- around the inverted ones
        bool untangleSurface(const label nAdditionalLayers = 2);

        //- optimize boundary nodes after boundary regions are created
        void optimizeSurface(const label nIterations = 5);

        //- optimize the surface of a 2D mesh
        void optimizeSurface2D(const label nIterations = 5);

        //- untangle the surface of a 2D mesh
        void untangleSurface2D();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "meshSurfaceOptimizerI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
