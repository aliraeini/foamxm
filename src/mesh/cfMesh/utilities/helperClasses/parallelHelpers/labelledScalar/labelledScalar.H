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
    labelledScalar

Description
    A class containing point label and its coordinates. It is used for
    exchanging data over processors

SourceFiles

\*---------------------------------------------------------------------------*/

#ifndef labelledScalar_H
#define labelledScalar_H

#include "label.H"
#include "scalar.H"
#include "contiguous.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


class labelledScalar
{
    // Private data
        //- label
        label sLabel_;

        //- value
        scalar value_;

    public:

    // Constructors
        //- Null construct
        labelledScalar()
        :
            sLabel_(-1),
            value_(0.0)
        {}

        //- Construct from label and value
        labelledScalar(const label sl, const scalar s)
        :
            sLabel_(sl),
            value_(s)
        {}

    // Destructor
        ~labelledScalar()
        {}

    // Member functions
        //- return scalar label
        inline label scalarLabel() const
        {
            return sLabel_;
        }

        //- return the value
        inline const scalar& value() const
        {
            return value_;
        }

    // Member operators

        inline void operator=(const labelledScalar& ls)
        {
            sLabel_ = ls.sLabel_;
            value_ = ls.value_;
        }

        inline bool operator==(const labelledScalar& ls) const
        {
            if( sLabel_ == ls.sLabel_ )
                return true;

            return false;
        }

        inline bool operator<(const labelledScalar& ls) const
        {
            if( value_ < ls.value_ )
                return true;

            return false;
        }

        inline bool operator<=(const labelledScalar& ls) const
        {
            if( value_ <= ls.value_ )
                return true;

            return false;
        }

        inline bool operator>(const labelledScalar& ls) const
        {
            if( value_ > ls.value_ )
                return true;

            return false;
        }

        inline bool operator>=(const labelledScalar& ls) const
        {
            if( value_ >= ls.value_ )
                return true;

            return false;
        }

        inline bool operator!=(const labelledScalar& ls) const
        {
            return !this->operator==(ls);
        }

    // Friend operators
        friend Ostream& operator<<(Ostream& os, const labelledScalar& ls)
        {
            os << token::BEGIN_LIST;
            os << ls.sLabel_ << token::SPACE;
            os << ls.value_ << token::END_LIST;

            // Check state of Ostream
            os.check("operator<<(Ostream&, const labelledScalar&");

            return os;
        }

        friend Istream& operator>>(Istream& is, labelledScalar& ls)
        {
            // Read beginning of labelledScalar
            is.readBegin("labelledScalar");

            is >> ls.sLabel_;
            is >> ls.value_;

            // Read end of labelledScalar
            is.readEnd("labelledScalar");

            // Check state of Istream
            is.check("operator>>(Istream&, labelledScalar");

            return is;
        }
};

//- Specify data associated with labelledScalar type is contiguous
template<>
inline bool contiguous<labelledScalar>() {return true;}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
