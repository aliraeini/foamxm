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
    decomposeCells

Description
    Decomposes selected cells into pyramids

SourceFiles


\*---------------------------------------------------------------------------*/

#ifndef decomposeCells_H
#define decomposeCells_H

#include "polyMeshGenModifier.H"
#include "VRWGraphList.H"
#include "DynList.H"

namespace Foam
{


class decomposeCells
{
    // private data
        //- reference to the mesh
        polyMeshGen& mesh_;

        //- new boundary faces
        wordList patchNames_;
        wordList patchTypes_;
        VRWGraph newBoundaryFaces_;
        labelLongList newBoundaryPatches_;

        VRWGraphList facesOfNewCells_;

    // Private member functions

        //- check if the valid pyramids are generated from the split cells
        //- this check splits faces which could
        //- result in multiple inbetween faces
        void checkFaceConnections(const boolList& decomposeCell);

        //- create addressing needed to decompose the cell
        void findAddressingForCell
        (
            const label cellI,
            DynList<label, 32>& vrt,
            DynList<edge, 64>& edges,
            DynList<DynList<label, 8> >& faceEdges,
            DynList<DynList<label, 2>, 64>& edgeFaces
        ) const;

        //- find the apex of the pyramids
        label findTopVertex
        (
            const label cellI,
            const DynList<label, 32>& vrt,
            const DynList<edge, 64>& edges,
            const DynList<DynList<label, 2>, 64>& edgeFaces
        );

        void decomposeCellIntoPyramids(const label cellI);

        void createPointsAndCellFaces(const boolList& decomposeCell);

        void storeBoundaryFaces(const boolList& decomposeCell);

        void removeDecomposedCells(const boolList& decomposeCell);

        void addNewCells();

        //- disallows bitwise construct
        void operator=(const decomposeCells&);

        //- copy constructor
        decomposeCells(const decomposeCells&);

public:

    // Constructors
        //- construct from polyMeshGen and a list containing patches
        //- for each point
        decomposeCells(polyMeshGen& mesh);

        //- Destructor
        ~decomposeCells();

    // Member functions

        //- perform decomposition of selected cell into pyramids
        void decomposeMesh(const boolList&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
