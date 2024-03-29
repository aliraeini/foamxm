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
    Foam::indexedParticleCloud

Description
    A Cloud of particles carrying an additional index.

SourceFiles
    indexedParticleCloud.C

\*---------------------------------------------------------------------------*/

#ifndef indexedParticleCloud_H
#define indexedParticleCloud_H

#include "CloudTemplate.H"
#include "indexedParticle.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


class indexedParticleCloud
:
    public Cloud<indexedParticle>
{
    // Private Member Functions

        //- Disallow default bitwise copy construct
        indexedParticleCloud(const indexedParticleCloud&);

        //- Disallow default bitwise assignment
        void operator=(const indexedParticleCloud&);


public:

    // Constructors

        //- Construct given mesh
        indexedParticleCloud
        (
            const polyMesh&,
            const word& cloudName = "defaultCloud",
            bool readFields = true
        );
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
