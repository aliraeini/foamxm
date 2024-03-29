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
	Foam::pointEdgePoint

Description
	Holds information regarding nearest wall point. Used in pointEdgeWave.
	(so not standard meshWave)
	To be used in wall distance calculation.

SourceFiles
	pointEdgePointI.H
	pointEdgePoint.C

\*---------------------------------------------------------------------------*/

#ifndef pointEdgePoint_H
#define pointEdgePoint_H

#include "point.H"
#include "label.H"
#include "scalar.H"
#include "tensor.H"
#include "pTraits.H"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of classes
class polyPatch;
class polyMesh;

// Forward declaration of friend functions and operators
class pointEdgePoint;

Ostream& operator<<(Ostream&, const pointEdgePoint&);
Istream& operator>>(Istream&, pointEdgePoint&);



class pointEdgePoint
{
	// Private data

		//- position of nearest wall center
		point origin_;

		//- normal distance (squared) from point to origin
		scalar distSqr_;

	// Private Member Functions

		//- Evaluate distance to point. Update distSqr, origin from whomever
		//  is nearer pt. Return true if w2 is closer to point,
		//  false otherwise.
		inline bool update
		(
			const point&,
			const pointEdgePoint& w2,
			const scalar tol
		);

		//- Combine current with w2. Update distSqr, origin if w2 has smaller
		//  quantities and returns true.
		inline bool update
		(
			const pointEdgePoint& w2,
			const scalar tol
		);

public:

	// Static data members

		//- initial point far away.
		static point greatPoint;

	// Constructors

		//- Construct null
		inline pointEdgePoint();

		//- Construct from origin, distance
		inline pointEdgePoint(const point& origin, const scalar distSqr);

	// Member Functions

		// Access

			inline const point& origin() const;

			inline scalar distSqr() const;


		// Needed by meshWave

			//- Check whether origin has been changed at all or
			//  still contains original (invalid) value.
			inline bool valid() const;

			//- Check for identical geometrical data. Used for cyclics checking.
			inline bool sameGeometry(const pointEdgePoint&, const scalar tol)
			 const;

			//- Convert origin to relative vector to leaving point
			//  (= point coordinate)
			inline void leaveDomain
			(
				const polyPatch& patch,
				const label patchPointI,
				const point& pos
			);

			//- Convert relative origin to absolute by adding entering point
			inline void enterDomain
			(
				const polyPatch& patch,
				const label patchPointI,
				const point& pos
			);

			//- Apply rotation matrix to origin
			inline void transform(const tensor& rotTensor);

			//- Influence of edge on point
			inline bool updatePoint
			(
				const polyMesh& mesh,
				const label pointI,
				const label edgeI,
				const pointEdgePoint& edgeInfo,
				const scalar tol
			);

			//- Influence of different value on same point.
			//  Merge new and old info.
			inline bool updatePoint
			(
				const polyMesh& mesh,
				const label pointI,
				const pointEdgePoint& newPointInfo,
				const scalar tol
			);

			//- Influence of different value on same point.
			//  No information about current position whatsoever.
			inline bool updatePoint
			(
				const pointEdgePoint& newPointInfo,
				const scalar tol
			);

			//- Influence of point on edge.
			inline bool updateEdge
			(
				const polyMesh& mesh,
				const label edgeI,
				const label pointI,
				const pointEdgePoint& pointInfo,
				const scalar tol
			);


	// Member Operators

		//Note: Used to determine whether to call update.
		inline bool operator==(const pointEdgePoint&) const;

		inline bool operator!=(const pointEdgePoint&) const;


	// IOstream Operators

		friend Ostream& operator<<(Ostream&, const pointEdgePoint&);
		friend Istream& operator>>(Istream&, pointEdgePoint&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "pointEdgePointI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
