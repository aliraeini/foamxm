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
    Foam::indexedParticle

Description

SourceFiles
    indexedParticleI.H
    indexedParticle.C
    indexedParticleIO.C

\*---------------------------------------------------------------------------*/

#ifndef indexedParticle_H
#define indexedParticle_H

#include "Particle.H"
#include "IOstream.H"
#include "autoPtr.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


class indexedParticle
:
    public Particle<indexedParticle>
{
    // Private data

        label index_;


public:

    // Constructors

        //- Construct from components
        indexedParticle
        (
            const Cloud<indexedParticle>& c,
            const vector& position,
            const label celli,
            const label index = 0
        )
        :
            Particle<indexedParticle>(c, position, celli),
            index_(index)
        {}

        //- Construct from Istream
        indexedParticle
        (
            const Cloud<indexedParticle>& c,
            Istream& is,
            bool readFields = true
        )
        :
            Particle<indexedParticle>(c, is, readFields)
        {}

        //- Construct as a copy
        indexedParticle(const indexedParticle& p)
        :
            Particle<indexedParticle>(p)
        {}

        //- Construct and return a clone
        autoPtr<indexedParticle> clone() const
        {
            return autoPtr<indexedParticle>(new indexedParticle(*this));
        }


    // Member functions

        label index() const
        {
            return index_;
        }

        label& index()
        {
            return index_;
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
