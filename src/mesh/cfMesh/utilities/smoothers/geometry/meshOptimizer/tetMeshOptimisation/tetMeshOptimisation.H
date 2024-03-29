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
    tetMeshOptimisation

Description
    Mesh smoothing without any topological changes

SourceFiles
    tetMeshOptimisation.C

\*---------------------------------------------------------------------------*/

#ifndef tetMeshOptimisation_H
#define tetMeshOptimisation_H

#include "DynList.H"
#include "parPartTet.H"
#include "boundBox.H"
#include "labelLongList.H"
#include "boolList.H"

#include <map>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declarations
class partTetMesh;
class meshSurfaceEngine;


class tetMeshOptimisation
{
    // Private data
        //- reference to the tet mesh
        partTetMesh& tetMesh_;

    // Private member functions needed for parallel runs
        //- make sure that all processors have the same points
        //- marked as negativeNode
        void unifyNegativePoints(boolList& negativeNode) const;

        //- exchange data with other processors
        void exchangeData
        (
            std::map<label, DynList<parPartTet> >& m,
            boolList* negativeNodePtr = nullptr
        );

        //- update buffer layer points
        void updateBufferLayerPoints();

        //- make sure that coordinates of moved points remain the same
        //- on all processor containing those points
        void unifyCoordinatesParallel(const boolList* negativeNodePtr = nullptr);

public:

    // Constructors

        //- Construct from tet mesh
        tetMeshOptimisation(partTetMesh& mesh);


    // Destructor

        ~tetMeshOptimisation();

    // Member Functions
        //- untangle mesh by using Patrik Knupp's simple metric
        void optimiseUsingKnuppMetric(const label nInterations = 5);

        //- smooth using mesh untangler
        void optimiseUsingMeshUntangler( const label nIerations = 5);

        //- smooth using volume optimizer
        void optimiseUsingVolumeOptimizer(const label nIterations = 10);

        //- smooth boundary using the volume optimizer
        void optimiseBoundaryVolumeOptimizer
        (
            const label nIterations = 3,
            const bool nonShrinking = false
        );

        //- smooth boundary using shrinking surface laplace
        void optimiseBoundarySurfaceLaplace(const label nIterations = 3);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
