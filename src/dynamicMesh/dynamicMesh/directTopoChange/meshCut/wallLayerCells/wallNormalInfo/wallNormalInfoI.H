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

// Update this with w2 if not yet set.
inline bool Foam::wallNormalInfo::update(const wallNormalInfo& w2)
{
	if (!w2.valid())
	{
		FatalErrorIn
		(
			"wallNormalInfo::update(const wallNormalInfo&)"
		) << "Problem: w2 is not valid" << abort(FatalError);

		return false;
	}
	else if (valid())
	{
		// our already set. Stop any transfer
		return false;
	}
	else
	{
		normal_ = w2.normal();

		return true;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Null constructor
inline Foam::wallNormalInfo::wallNormalInfo()
:
	normal_(greatVector)
{}


// Construct from normal
inline Foam::wallNormalInfo::wallNormalInfo(const vector& normal)
:
	normal_(normal)
{}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const Foam::vector& Foam::wallNormalInfo::normal() const
{
	return normal_;
}


inline bool Foam::wallNormalInfo::valid() const
{
	return normal_ != greatVector;
}


// No geometric data so never any problem on cyclics
inline bool Foam::wallNormalInfo::sameGeometry
(
	const polyMesh&,
	const wallNormalInfo& w2,
	const scalar tol
) const
{
	return true;
}


// No geometric data.
inline void Foam::wallNormalInfo::leaveDomain
(
	const polyMesh&,
	const polyPatch& patch,
	const label patchFaceI,
	const point& faceCentre
)
{}


// No geometric data.
inline void Foam::wallNormalInfo::transform
(
	const polyMesh&,
	const tensor& rotTensor
)
{}


// No geometric data.
inline void Foam::wallNormalInfo::enterDomain
(
	const polyMesh&,
	const polyPatch& patch,
	const label patchFaceI,
	const point& faceCentre
)
{}


// Update this with w2 if w2 nearer to pt.
inline bool Foam::wallNormalInfo::updateCell
(
	const polyMesh&,
	const label thisCellI,
	const label neighbourFaceI,
	const wallNormalInfo& neighbourWallInfo,
	const scalar tol
)
{
	return update(neighbourWallInfo);
}


// Update this with w2 if w2 nearer to pt.
inline bool Foam::wallNormalInfo::updateFace
(
	const polyMesh&,
	const label thisFaceI,
	const label neighbourCellI,
	const wallNormalInfo& neighbourWallInfo,
	const scalar tol
)
{
	return update(neighbourWallInfo);
}


// Update this with w2 if w2 nearer to pt.
inline bool Foam::wallNormalInfo::updateFace
(
	const polyMesh&,
	const label thisFaceI,
	const wallNormalInfo& neighbourWallInfo,
	const scalar tol
)
{
	return update(neighbourWallInfo);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool Foam::wallNormalInfo::operator==(const Foam::wallNormalInfo& rhs)
 const
{
	return normal() == rhs.normal();
}


inline bool Foam::wallNormalInfo::operator!=(const Foam::wallNormalInfo& rhs)
 const
{
	return !(*this == rhs);
}


// ************************************************************************* //
