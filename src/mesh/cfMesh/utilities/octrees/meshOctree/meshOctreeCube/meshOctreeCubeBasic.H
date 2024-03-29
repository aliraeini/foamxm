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
    meshOctreeCubeBasic

Description
    A cube stores information needed for mesh generation

SourceFiles
    meshOctreeCubeBasic.C

\*---------------------------------------------------------------------------*/

#ifndef meshOctreeCubeBasic_H
#define meshOctreeCubeBasic_H

#include "meshOctreeCubeCoordinates.H"
#include "contiguous.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


class meshOctreeCubeBasic
: public meshOctreeCubeCoordinates
{
    // Private data
        //- cube type
        direction cubeType_;

        //- processor to which the cube belongs to
        short procNo_;

public:

    // Constructors
        //- Null constructor
        inline meshOctreeCubeBasic();

        //- Construct from coordinates
        explicit inline meshOctreeCubeBasic
        (
            const meshOctreeCubeCoordinates&
        );

        //- Construct from coordinates and cube type
        inline meshOctreeCubeBasic
        (
            const meshOctreeCubeCoordinates& cc,
            const direction cubeType,
            const short procNo = ALLPROCS
        );

    // Destructor

        ~meshOctreeCubeBasic()
        {}

    // Enumerators

        enum typesOfCubes
        {
            UNKNOWN = 1,
            OUTSIDE = 2,
            DATA = 4,
            INSIDE = 8,
            ALLPROCS = -2,
            OTHERPROC = -3
        };

    // Member functions
        //- return type
        inline direction cubeType() const;

        //- set cube type
        inline void setCubeType(const direction);

        //- return processor number
        inline short procNo() const;

        //- set processor number
        inline void setProcNo(const short);

        //- return coordinates in the octree
        inline const meshOctreeCubeCoordinates& coordinates() const;

        // Member operators

        // Friend operators

        friend inline Ostream& operator<<
        (
            Ostream&,
            const meshOctreeCubeBasic&
        );

        friend inline Istream& operator>>
        (
            Istream&,
            meshOctreeCubeBasic&
        );
};

//- Specify data associated with meshOctreeCubeBasic type is contiguous
template<>
inline bool contiguous<meshOctreeCubeBasic>() {
    return true;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "meshOctreeCubeBasicI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
