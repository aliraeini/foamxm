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
    extrudeLayer

Description
    Creates a sheet of prismatic cells from the selected faces in
    the direction of the specified cell for each face

SourceFiles
    extrudeLayer.C

\*---------------------------------------------------------------------------*/

#ifndef extrudeLayer_H
#define extrudeLayer_H

#include "polyMeshGenModifier.H"
#include "VRWGraphList.H"
#include "labelPair.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


class extrudeLayer
{
    // Private data

        //- Reference to the mesh
        polyMeshGen& mesh_;

        //- thickness
        const scalar thickness_;

        //- number of points in the original mesh
        const label nOrigPoints_;

        //- number of faces in the original mesh
        const label nOrigFaces_;

        //- number of cells in the original mesh
        const label nOrigCells_;

        //- pairs of faces making the extruded front
        LongList<labelPair> extrudedFaces_;

        //- store the orientation of the extruded front
        //- true if the pair has the same orientation and false otherwise
        LongList<bool> pairOrientation_;

        //- original point label
        labelLongList origPointLabel_;

    // Private member functions
        //- duplicate faces which will be extruded
        void createDuplicateFrontFaces(const LongList<labelPair>&);

        //- create new vertices and open the mesh
        void createNewVertices();

        //- move points to make space for the new cells
        void movePoints();

        //- create layer cells
        void createLayerCells();

        //- create new faces at parallel boundaries
        void createNewFacesParallel();

        //- update boundary patches
        void updateBoundary();

    // Nested classes
        //- this class provides addressing data needed for generating
        //- cells emerging as a consequence of self-intersecting layers
        class addressingCalculator
        {
            // Private data
                //- const reference to mesh faces
                const faceListPMG& faces_;

                //- const reference to extruded face pairs
                const LongList<labelPair>& extrudedFaces_;

                //- const reference telling the orientation of each face pair
                LongList<bool> pairOrientation_;

                //- const reference to the extruded faces at points
                const VRWGraph& pointExtruded_;

            public:

            // Construct from faces, extruded face pairs and
            // point-extrudedfaces addressing
                addressingCalculator
                (
                    const faceListPMG& faces,
                    const LongList<labelPair>& extrudedFaces,
                    const LongList<bool>& pairOrientation,
                    const VRWGraph& pointFaces
                );

            // Destructor
                ~addressingCalculator();

            // Member functions
                //- return label of the original face for the given face
                inline label origFaceLabel(const label extrudedI) const;

                //- return position of point in extruded face
                inline label positionInFace
                (
                    const label extrudedI,
                    const label pointI
                ) const;

                //- return point label in the original face
                inline label origPointLabel
                (
                    const label extrudedI,
                    const label pos
                ) const;

                inline label origPoint
                (
                    const label extrudedI,
                    const label pointI
                ) const;

                //- find face sharing an edge with the given face
                inline label faceSharingEdge
                (
                    const label extrudedI,
                    const label eI
                ) const;

                //- find faces attached to both points
                inline void facesSharingEdge
                (
                    const label start,
                    const label end,
                    DynList<label>&
                ) const;
        };

    // Enumerators
        enum extrudeLayerTypes_
        {
            NONE = 0,
            FRONTVERTEX = 1,
            FRONTVERTEXPROCBND = 2
        };

        //- Disallow bitwise copy construct
        extrudeLayer(const extrudeLayer&);

        //- Disallow bitwise assignment
        void operator=(const extrudeLayer&);

    public:

        // Constructors

        //- Construct from mesh, extrusion faces, thickness and number of layers
        extrudeLayer
        (
            polyMeshGen& mesh,
            const LongList<labelPair>& extrusionFront,
            const scalar thickness = -1.0
        );

    // Destructor
        ~extrudeLayer();

    // Public member functions
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "extrudeLayerI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
