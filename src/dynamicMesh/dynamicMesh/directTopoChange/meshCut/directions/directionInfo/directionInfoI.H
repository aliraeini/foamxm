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

\*---------------------------------------------------------------------------*/

#include "polyMesh.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Null constructor
inline Foam::directionInfo::directionInfo()
:
	index_(-3),
	n_(vector::zero)
{}


// Construct from components
inline Foam::directionInfo::directionInfo
(
	const label index,
	const vector& n
)
:
	index_(index),
	n_(n)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline bool Foam::directionInfo::valid() const
{
	return index_ != -3;
}


// No geometric data so never any problem on cyclics
inline bool Foam::directionInfo::sameGeometry
(
	const polyMesh&,
	const directionInfo& w2,
	const scalar tol
)
 const
{
	return true;
}


// index_ is already offset in face
inline void Foam::directionInfo::leaveDomain
(
	const polyMesh&,
	const polyPatch& patch,
	const label patchFaceI,
	const point& faceCentre
)
{}


// index_ is offset in face on other side. So reverse it here.
// (Note: f[0] on other domain is connected to f[0] in this domain,
//		f[1]	  ,,						 f[size-1]   ,,
// etc.)
inline void Foam::directionInfo::enterDomain
(
	const polyMesh&,
	const polyPatch& patch,
	const label patchFaceI,
	const point& faceCentre
)
{
	if (index_ >= 0)
	{
		const face& f = patch[patchFaceI];

		index_ = (f.size() - index_) % f.size();
	}
}


// No geometric data.
inline void Foam::directionInfo::transform
(
	const polyMesh&,
	const tensor& rotTensor
)
{}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool Foam::directionInfo::operator==(const Foam::directionInfo& rhs)
 const
{
	return  index() == rhs.index() && n() == rhs.n();
}


inline bool Foam::directionInfo::operator!=(const Foam::directionInfo& rhs)
 const
{
	return !(*this == rhs);
}


// ************************************************************************* //
