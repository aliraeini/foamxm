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
    meshOctreeInsideOutside
Description
    Creates inside/outside information for the octree

SourceFiles
    meshOctreeInsideOutside.C

\*---------------------------------------------------------------------------*/

#ifndef meshOctreeInsideOutside_H
#define meshOctreeInsideOutside_H

#include "meshOctreeModifier.H"
#include <map>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


class meshOctreeInsideOutside
{
    // Private data

        //- meshOctreeAddressing
        meshOctreeModifier octreeModifier_;

        //- group for a given leaf
        labelLongList cubeGroup_;

        //- cubes belonging to each group of octree boxes
        VRWGraph cubesInGroup_;

        //- type for a group
        std::map<label, direction> groupType_;

        //- boundary DATA boxes for a given group
        VRWGraph boundaryDATACubes_;

        //- flag for DATA boxes next to the OUTSIDE boxes
        boolList hasOutsideNeighbour_;

        //- label of cubes at processor boundaries
        labelLongList communicationCubes_;

        //- labels of cubes marked by different threads
        VRWGraph neighbouringGroups_;

    // Private member functions

        //- initialise octree boxes
        void initialiseBoxes();

        //- frontal marking algorithm
        void frontalMarking();

        //- mark OUTSIDE octree boxes
        void markOutsideCubes();

        //- revise DATA boxes
        void reviseDataBoxes();

        //- mark INSIDE octree boxes
        void markInsideCubes();

    public:

    // Constructor

        //- Construct from octree
        meshOctreeInsideOutside
        (
            meshOctree& octree
        );

    // Destructor

        ~meshOctreeInsideOutside();
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
