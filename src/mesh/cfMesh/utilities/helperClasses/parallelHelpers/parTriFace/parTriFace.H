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
    parTriFace

Description
    Hold point labels and their coordinates. It is used for exchanging data
    over processors

SourceFiles

\*---------------------------------------------------------------------------*/

#ifndef parTriFace_H
#define parTriFace_H

#include "label.H"
#include "point.H"
#include "triangle.H"
#include "contiguous.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


class parTriFace
{
    // Private data
        label globalLabels_[3];

        triangle<point, point> triPoints_;

    public:

    // Constructors

        inline parTriFace()
        :
            triPoints_(vector::zero, vector::zero, vector::zero)
        {}

        explicit inline parTriFace
        (
            const label globalLabel0,
            const label globalLabel1,
            const label globalLabel2,
            const triangle<point, point>& pts
        )
        :
            triPoints_(pts)
        {
            globalLabels_[0] = globalLabel0;
            globalLabels_[1] = globalLabel1;
            globalLabels_[2] = globalLabel2;
        }

    // Destructor

        ~parTriFace()
        {}

    // Member functions

        inline label globalLabelOfPoint(const label i) const
        {
            return globalLabels_[i];
        }

        inline const triangle<point, point>& trianglePoints() const
        {
            return triPoints_;
        }

    // Member operators

        inline bool operator !=(const parTriFace& /*ptf*/) const
        {
            Serr << "parTriFace::operator!= Not implemented" << endl;
            ::exit(1);
        }

    // Friend operators

        inline friend Ostream& operator<<(Ostream& os, const parTriFace& ptf)
        {
            os << token::BEGIN_LIST;
            os << ptf.globalLabels_[0] << token::SPACE;
            os << ptf.globalLabels_[1] << token::SPACE;
            os << ptf.globalLabels_[2] << token::SPACE;
            os << ptf.triPoints_ << token::END_LIST;

            // Check state of Ostream
            os.check("operator<<(Ostream&, const parTriFace&");
            return os;
        }

        inline friend Istream& operator>>(Istream& is, parTriFace& ptf)
        {
            // Read beginning of parTriFace
            is.readBegin("parTriFace");

            is >> ptf.globalLabels_[0];
            is >> ptf.globalLabels_[1];
            is >> ptf.globalLabels_[2];
            is >> ptf.triPoints_;

            // Read end of parHelper
            is.readEnd("parTriFace");

            // Check state of Istream
            is.check("operator>>(Istream&, parTriFace");

            return is;
        }
};

//- Specify data associated with parTriFace type is contiguous
template<>
inline bool contiguous<parTriFace>() {return true;}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
