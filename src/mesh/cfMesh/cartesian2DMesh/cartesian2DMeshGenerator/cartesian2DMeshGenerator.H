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
    cartesian2DMeshGenerator

Description
    Creates a 2D cartesian mesh from the quadtree

SourceFiles
    cartesian2DMeshGenerator.C

\*---------------------------------------------------------------------------*/

#ifndef cartesian2DMeshGenerator_H
#define cartesian2DMeshGenerator_H

#include "polyMeshGen.H"
#include "IOdictionary.H"
#include "workflowControls.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declarations
class triSurf;
class meshOctree;
class Time;


class cartesian2DMeshGenerator
{
    // Private data
        //- reference to Time
        const Time& db_;

        //- pointer to the surface
        const triSurf* surfacePtr_;

        //- pointer to the modified surface mesh
        const triSurf* modSurfacePtr_;

        //- IOdictionary containing information about cell sizes, etc..
        IOdictionary meshDict_;

        //- pointer to the octree
        meshOctree* octreePtr_;

        //- mesh
        polyMeshGen mesh_;

        //- workflow controller
        workflowControls controller_;

    // Private member functions
        //- create cartesian mesh
        void createCartesianMesh();

        //- prepare mesh surface
        void surfacePreparation();

        //- map mesh to the surface and untangle surface
        void mapMeshToSurface();

        //- capture edges and corners
        void extractPatches();

        //- capture edges and corners
        void mapEdgesAndCorners();

        //- optimise surface mesh
        void optimiseMeshSurface();

        //- add boundary layers
        void generateBoundaryLayers();

        //- refine boundary layers
        void refBoundaryLayers();

        //- replace boundaries
        void replaceBoundaries();

        //- renumber the mesh
        void renumberMesh();

        //- generate mesh
        void generateMesh();

        //- Disallow default bitwise copy construct
        cartesian2DMeshGenerator(const cartesian2DMeshGenerator&);

        //- Disallow default bitwise assignment
        void operator=(const cartesian2DMeshGenerator&);

public:

    // Constructors

        //- Construct from time
        cartesian2DMeshGenerator(const Time&);

    // Destructor

        ~cartesian2DMeshGenerator();


    // Member Functions

        //- write the mesh
        void writeMesh() const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
