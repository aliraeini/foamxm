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
    labelledMeshOctreeCubeCoordinates

Description
    A class containing point label and meshOctreeCubeCoordinates.
    It is used for exchanging data over processors

SourceFiles

\*---------------------------------------------------------------------------*/

#ifndef labelledMeshOctreeCubeCoordinates_H
#define labelledMeshOctreeCubeCoordinates_H

#include "label.H"
#include "meshOctreeCubeCoordinates.H"
#include "contiguous.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


class labelledMeshOctreeCubeCoordinates
{
    // Private data
        //- label
        label cLabel_;

        //- cube coordinates
        meshOctreeCubeCoordinates coordinates_;

    public:

    // Constructors
        //- Null construct
        labelledMeshOctreeCubeCoordinates()
        :
            cLabel_(-1),
            coordinates_()
        {}

        //- Construct from label and cube coordinates
        labelledMeshOctreeCubeCoordinates
        (
            const label cl,
            const meshOctreeCubeCoordinates& cc
        )
        :
            cLabel_(cl),
            coordinates_(cc)
        {}

    // Destructor
        ~labelledMeshOctreeCubeCoordinates()
        {}

    // Member functions
        //- return cube label
        inline label cubeLabel() const
        {
            return cLabel_;
        }

        //- return the value
        inline const meshOctreeCubeCoordinates& coordinates() const
        {
            return coordinates_;
        }

    // Member operators

        inline void operator=(const labelledMeshOctreeCubeCoordinates& lcc)
        {
            cLabel_ = lcc.cLabel_;
            coordinates_ = lcc.coordinates_;
        }

        inline bool operator==
        (
            const labelledMeshOctreeCubeCoordinates& lcc
        ) const
        {
            if( cLabel_ == lcc.cLabel_ )
                return true;

            return false;
        }

        inline bool operator!=
        (
            const labelledMeshOctreeCubeCoordinates& lcc
        ) const
        {
            return !this->operator==(lcc);
        }

    // Friend operators
        friend Ostream& operator<<
        (
            Ostream& os,
            const labelledMeshOctreeCubeCoordinates& lcc
        )
        {
            os << token::BEGIN_LIST;
            os << lcc.cLabel_ << token::SPACE;
            os << lcc.coordinates_ << token::END_LIST;

            // Check state of Ostream
            os.check
            (
                "operator<<(Ostream&, const labelledMeshOctreeCubeCoordinates&"
            );

            return os;
        }

        friend Istream& operator>>
        (
            Istream& is,
            labelledMeshOctreeCubeCoordinates& lcc
        )
        {
            // Read beginning of labelledMeshOctreeCubeCoordinates
            is.readBegin("labelledMeshOctreeCubeCoordinates");

            is >> lcc.cLabel_;
            is >> lcc.coordinates_;

            // Read end of labelledMeshOctreeCubeCoordinates
            is.readEnd("labelledMeshOctreeCubeCoordinates");

            // Check state of Istream
            is.check("operator>>(Istream&, labelledMeshOctreeCubeCoordinates");

            return is;
        }
};

//- Specify data associated with labelledMeshOctreeCubeCoordinates
//- type is contiguous
template<>
inline bool contiguous<labelledMeshOctreeCubeCoordinates>() {return true;}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
