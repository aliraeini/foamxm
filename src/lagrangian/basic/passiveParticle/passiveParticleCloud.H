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
    Foam::passiveParticleCloud

Description
    A Cloud of passive particles

SourceFiles
    passiveParticleCloud.C

\*---------------------------------------------------------------------------*/

#ifndef passiveParticleCloud_H
#define passiveParticleCloud_H

#include "CloudTemplate.H"
#include "passiveParticle.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


class passiveParticleCloud
:
    public Cloud<passiveParticle>
{
    // Private Member Functions

        //- Disallow default bitwise copy construct
        passiveParticleCloud(const passiveParticleCloud&);

        //- Disallow default bitwise assignment
        void operator=(const passiveParticleCloud&);


public:

    //- Type of parcel the cloud was instantiated for
    typedef passiveParticle parcelType;

    // Constructors

        //- Construct given mesh
        passiveParticleCloud
        (
            const polyMesh&,
            const word& cloudName = "defaultCloud",
            bool readFields = true
        );

        //- Construct from mesh, cloud name, and a list of particles
        passiveParticleCloud
        (
            const polyMesh& mesh,
            const word& cloudName,
            const IDLList<passiveParticle>& particles
        );
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
