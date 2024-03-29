/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | foam-extend: Open Source CFD
   \\    /   O peration     | Version:     4.1
    \\  /    A nd           | Web:         http://www.foam-extend.org
     \\/     M anipulation  | For copyright notice see file Copyright
-------------------------------------------------------------------------------
License
    This file is part of foam-extend.

    foam-extend is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    foam-extend is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with foam-extend.  If not, see <http://www.gnu.org/licenses/>.

Class
    processorFaMeshes

Description
    Container for processor mesh addressing.

Author
    Zeljko Tukovic, FSB Zagreb.  All rights reserved

SourceFiles
    processorFaMeshes.C

\*---------------------------------------------------------------------------*/

#ifndef processorFaMeshes_H
#define processorFaMeshes_H

#include "PtrList.H"
#include "fvMesh.H"
#include "faMesh.H"
#include "IOobjectList.H"
#include "labelIOList.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{



class processorFaMeshes
{
    // Private data

        //- List of processor finite volume meshes
        const PtrList<fvMesh>& fvMeshes_;

        //- List of processor finite area meshes
        PtrList<faMesh> meshes_;

        //- List of processor point addressing lists
        PtrList<labelIOList> pointProcAddressing_;

        //- List of processor face addressing lists
        PtrList<labelIOList> edgeProcAddressing_;

        //- List of processor cell addressing lists
        PtrList<labelIOList> faceProcAddressing_;

        //- List of processor boundary addressing lists
        PtrList<labelIOList> boundaryProcAddressing_;


    // Private Member Functions

        //- Read all meshes
        void readMeshes();

        //- Return first valid mesh index
        label firstValidMesh() const;

        //- Disallow default bitwise copy construct
        processorFaMeshes(const processorFaMeshes&);

        //- Disallow default bitwise assignment
        void operator=(const processorFaMeshes&);


public:

    // Constructors

        //- Construct from components
        processorFaMeshes
        (
            const PtrList<fvMesh>& processorFvMeshes,
            const bool read
        );


    // Member Functions

        //- Return meshes
        const PtrList<faMesh>& meshes() const
        {
            return meshes_;
        }

        //- Return point addressing
        const PtrList<labelIOList>& pointProcAddressing() const
        {
            return pointProcAddressing_;
        }

        //- Return edge addressing
        PtrList<labelIOList>& edgeProcAddressing()
        {
            return edgeProcAddressing_;
        }

        //- Return face addressing
        const PtrList<labelIOList>& faceProcAddressing() const
        {
            return faceProcAddressing_;
        }

        //- Return boundary addressing
        const PtrList<labelIOList>& boundaryProcAddressing() const
        {
            return boundaryProcAddressing_;
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
