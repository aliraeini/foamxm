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
    meshOctreeAutomaticRefinement

Description
    Automatic octree for mesh generation. This class checks if the current
    octree resolution is enough to resolve all surface features

SourceFiles
    meshOctreeAutomaticRefinement.C

\*---------------------------------------------------------------------------*/

#ifndef meshOctreeAutomaticRefinement_H
#define meshOctreeAutomaticRefinement_H

#include "meshOctreeModifier.H"
#include "IOdictionary.H"
//#include "volFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declarations
class triSurfaceCurvatureEstimator;
class triSurfacePartitioner;
class meshOctreeAddressing;


class meshOctreeAutomaticRefinement
{
    // Private data
        //- reference to meshOctree
        meshOctree& octree_;

        //- const reference to mesh dictionary
        const IOdictionary& meshDict_;

        //- use DATA boxes
        bool useDATABoxes_;

        //- a flag for activating paired refinement
        bool hexRefinement_;

    // Private member functions
        //- meshOctreeAddressing pointer
        mutable meshOctreeAddressing* octreeAddressingPtr_;

        //- calculate octree addresing
        void createOctreeAddressing() const;
        const meshOctreeAddressing& octreeAddressing() const;

        //- surface partitioner pointer
        mutable triSurfacePartitioner* partitionerPtr_;

        //- calculate partitionerPtr_
        void createSurfacePartitioner() const;
        const triSurfacePartitioner& partitioner() const;

        //- curvature estimator pointer
        mutable triSurfaceCurvatureEstimator* curvaturePtr_;

           //- calculate curvaturePtr_
        void createCurvatureEstimator() const;
        const triSurfaceCurvatureEstimator& curvature() const;

    // Functions and data performing automatic refinement
        //- maximum allowed refinement level
        direction maxRefLevel_;

        //- set maxRefLevel_
        void setMaxRefLevel();

        //- refine selected boxes
        void refineSelectedBoxes(labelList&, labelLongList&);

        //- refine DATA boxes based on curvature
        bool curvatureRefinement();
        bool refineBasedOnCurvature(labelList&, const labelLongList&);

        //- refine DATA boxes which contain two or more independent parts
        //- of the surface in their vicinity
        bool proximityRefinement();
        bool refineBasedOnProximityTests
        (
            labelList&,
            const labelLongList&
        );

        //- refine DATA boxes containing 2 or more corners, 2 or more distinct
        //- edges, etc.
        bool refineBasedOnContainedPartitions
        (
            labelList&,
            const labelLongList&
        );

        //- refine boxes based on the number of contained surface corners
        bool refineBasedOnContainedCorners
        (
            labelList&,
            const labelLongList&
        );

    // Private copy constructor
        //- Disallow default bitwise copy construct
        meshOctreeAutomaticRefinement(const meshOctreeAutomaticRefinement&);

        //- Disallow default bitwise assignment
        void operator=(const meshOctreeAutomaticRefinement&);

public:

    // Constructors

        //- Construct from meshOctree, dictionary and boolean
        meshOctreeAutomaticRefinement
        (
            meshOctree& mo,
            const IOdictionary& dict,
            bool useDATABoxes = false
        );

    // Destructor

        ~meshOctreeAutomaticRefinement();

    // Member Functions
        //- activate hex refinement
        void activateHexRefinement();

        //- refine octree boxes which are too coarse and cannot capture
        //- surface features
        void automaticRefinement();
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
