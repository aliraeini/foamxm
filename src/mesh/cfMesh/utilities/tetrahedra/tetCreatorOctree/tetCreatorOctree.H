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
    tetCreatorOctree

Description
    A class which creates tets from the octree structure

SourceFiles
    tetCreatorOctree.C

\*---------------------------------------------------------------------------*/

#ifndef tetCreatorOctree_H
#define tetCreatorOctree_H

#include "polyMeshGenModifier.H"
#include "partTet.H"
#include "meshOctreeAddressing.H"
#include "meshOctreeCubeCoordinates.H"
#include "VRWGraph.H"
#include "labelLongList.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


class tetCreatorOctree
{
    // Private data
        //- helper for searching coordinates of cubes around an edge
        static const meshOctreeCubeCoordinates edgeCoordinates_[12][4];

        //- helper for finding face centres of cubes sharing an edge
        static const label faceCentreHelper_[3][4];

        //- reference to the octree
        meshOctreeAddressing octreeCheck_;

        //- points of the tetrahedrisation
        LongList<point> tetPoints_;

        //- tetrahedra
        LongList<partTet> tets_;

        //- octree leaves sorted according to their level
        List<labelLongList> sortedLeaves_;

        //- node labels of vertices created inside split-hex boxes
        VRWGraph* subNodeLabelsPtr_;

        //- cube centre label
        labelList* cubeLabelPtr_;

        //- cube face label
        VRWGraph* faceCentreLabelPtr_;

        //- are tets created or not
        bool created_;

    // Private member functions
        //- deletes all pointer data
        void clearOut();

        //- find elements which will be used as mesh cells
        void selectElements();

    // Private member functions for creating tetrahedra
        //- create tetPoints_ and necessary addressing
        void createPointsAndAddressing();

        //- create faceCentreLabelPtr_
        void createFaceCentreLabels();

        //- create tetrahedra from faces, owner and neighbour
        void createTetsAroundEdges();

        //- create tetrahedra from split faces
        void createTetsFromSplitFaces();

        //- create tetrahedra from faces which share at least one edge
        //- with a refined cube
        void createTetsFromFacesWithCentreNode();

        //- create tetrahedra from faces with split edges
        void createTetsAroundSplitEdges();

        //- helper funtion which checks validity of a created tet and appends
        //- it if valid
        inline void checkAndAppendTet(const partTet);

        //- function containing the workflow
        void createTets();

    // Private copy constructor
        //- Disallow default bitwise copy construct
        tetCreatorOctree(const tetCreatorOctree&);

        //- Disallow default bitwise assignment
        void operator=(const tetCreatorOctree&);

public:

    // Constructors

        //- Construct from octree and IOdictionary
        tetCreatorOctree
        (
            const meshOctree& octree,
            const IOdictionary& meshDict
        );

    // Destructor

        ~tetCreatorOctree();


    // Member Functions
        const LongList<point>& tetPoints() const
        {
            if( !created_ )
                FatalErrorIn
                (
                    "const LongList<point>& tetPoints() const"
                ) << "Tets are not created!" << exit(FatalError);

            return tetPoints_;
        }

        const LongList<partTet>& tets() const
        {
            if( !created_ )
                FatalErrorIn
                (
                    "const LongList<point>& tets() const"
                ) << "Tets are not created!" << exit(FatalError);

            return tets_;
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "tetCreatorOctreeI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
