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
    Foam::processorMeshesReconstructor

Description
    The processorMeshesReconstructor will take a list of meshes with
    matching processor boundaries and build a single combined mesh by
    matching processor patches to each other.

Author
    Hrvoje Jasak, Wikki Ltd.  All rights reserved.

SourceFiles
    processorMeshesReconstructor.C
    processorMeshesRebuild.C

\*---------------------------------------------------------------------------*/

#ifndef processorMeshesReconstructor_H
#define processorMeshesReconstructor_H

#include "PtrList.H"
#include "objectRegistry.H"
#include "foamTime.H"
#include "fvMesh.H"
#include "labelIOList.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of friend functions and operators

class processorPolyPatch;


class processorMeshesReconstructor
{
    // Private data

        //- Name of mesh region to reconstruct
        const word meshName_;

        //- List of processor meshes
        PtrList<fvMesh> meshes_;

        //- global point index per sub-mesh
        labelListList globalPointIndex_;

        //- List of processor point addressing lists
        PtrList<labelIOList> pointProcAddressing_;

        //- List of processor face addressing lists
        PtrList<labelIOList> faceProcAddressing_;

        //- List of processor cell addressing lists
        PtrList<labelIOList> cellProcAddressing_;

        //- List of processor boundary addressing lists
        PtrList<labelIOList> boundaryProcAddressing_;


    // Private Member Functions

        //- Disallow default bitwise copy construct
        processorMeshesReconstructor(const processorMeshesReconstructor&);

        //- Disallow default bitwise assignment
        void operator=(const processorMeshesReconstructor&);


        //- Read all meshes
        void readMeshes(PtrList<Time>& databases);

        //- Attempt to read mapping.  If not available, return false
        bool readMapping();

        //- Return first valid mesh index
        label firstValidMesh() const;

        //- Return neighbour processor patch
        const processorPolyPatch& neighbourProcPatch
        (
            const processorPolyPatch& procPatch
        ) const;

        //- Return neighbour processor patch
        labelList procPatchPointMapping
        (
            const processorPolyPatch& procPatch
        ) const;

        //- Clear reconstruction maps
        void clearMaps();


public:

    //- Declare name of the class and its debug switch
    ClassName("processorMeshesReconstructor");


    // Constructors

        //- Construct given name.  Set meshes later
        processorMeshesReconstructor(const word& meshName);

        //- Construct reading meshes from databases
        processorMeshesReconstructor
        (
            PtrList<Time>& databases,
            const word& meshName
        );


    // Destructor - default


    // Member Functions

        //- Update the meshes based on the mesh files saved in
        //  time directories
        fvMesh::readUpdateState readUpdate();

        //- Reconstruct mesh after topology change in parallel
        autoPtr<fvMesh> reconstructMesh(const Time& db);

        //- Reconstruct point position after motion in parallel
        void reconstructPoints(fvMesh& mesh) const;

        //- Return meshes
        const PtrList<fvMesh>& meshes() const
        {
            return meshes_;
        }

        //- Return access to meshes
        PtrList<fvMesh>& meshes()
        {
            return meshes_;
        }

        //- Return to global point index
        labelListList& globalPointIndex()
        {
            return globalPointIndex_;
        }

        //- Return point-processor addressing arrays
        const PtrList<labelIOList>& pointProcAddressing() const;

        //- Return face-processor addressing arrays
        const PtrList<labelIOList>& faceProcAddressing() const;

        //- Return cell-processor addressing arrays
        const PtrList<labelIOList>& cellProcAddressing() const;

        //- Return boundary-processor addressing arrays
        const PtrList<labelIOList>& boundaryProcAddressing() const;


        //- Write addressing
        void writeAddressing();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
