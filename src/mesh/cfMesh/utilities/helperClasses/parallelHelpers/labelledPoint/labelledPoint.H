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
    labelledPoint

Description
    A class containing point label and its coordinates. It is used for
    exchanging data over processors

SourceFiles

\*---------------------------------------------------------------------------*/

#ifndef labelledPoint_H
#define labelledPoint_H

#include "label.H"
#include "point.H"
#include "contiguous.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


class labelledPoint
{
    // Private data
        //- point label
        label pLabel_;

        //- point coordinates
        point coords_;

    public:

    // Constructors
        //- Null construct
        labelledPoint()
        :
            pLabel_(-1),
            coords_(vector::zero)
        {}

        //- Construct from point and label
        labelledPoint(const label pl, const point& p)
        :
            pLabel_(pl),
            coords_(p)
        {}

    // Destructor
        ~labelledPoint()
        {}

    // Member functions
        //- return point label
        inline label pointLabel() const
        {
            return pLabel_;
        }

        inline label& pointLabel()
        {
            return pLabel_;
        }

        //- return point coordinates
        inline const point& coordinates() const
        {
            return coords_;
        }

        inline point& coordinates()
        {
            return coords_;
        }

    // Member operators

        inline bool operator==(const labelledPoint& lp) const
        {
            if( pLabel_ == lp.pLabel_ )
                return true;

            return false;
        }

        inline bool operator!=(const labelledPoint& lp) const
        {
            return !this->operator==(lp);
        }

    // Friend operators
        friend Ostream& operator<<(Ostream& os, const labelledPoint& lp)
        {
            os << token::BEGIN_LIST;
            os << lp.pLabel_ << token::SPACE;
            os << lp.coords_ << token::END_LIST;

            // Check state of Ostream
            os.check("operator<<(Ostream&, const labelledPoint&");

            return os;
        }

        friend Istream& operator>>(Istream& is, labelledPoint& lp)
        {
            // Read beginning of labelledPoint
            is.readBegin("labelledPoint");

            is >> lp.pLabel_;
            is >> lp.coords_;

            // Read end of labelledPoint
            is.readEnd("labelledPoint");

            // Check state of Istream
            is.check("operator>>(Istream&, labelledPoint");

            return is;
        }
};

//- Specify data associated with labelledPoint type is contiguous
template<>
inline bool contiguous<labelledPoint>() {return true;}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
