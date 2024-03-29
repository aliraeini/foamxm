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
	Foam::septernion

Description
	Septernion class used to perform translations and rotations in 3D space.

	It is composed of a translation vector and rotation quaternion and as
	such has seven components hence the name "septernion" from the Latin to
	be consistent with quaternion rather than "hepternion" derived from the
	Greek.

SourceFiles
	septernionI.H
	septernion.C

\*---------------------------------------------------------------------------*/

#ifndef septernion_H
#define septernion_H

#include "vector.H"
#include "quaternion.H"
#include "word.H"
#include "contiguous.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of friend functions and operators

class septernion;
Istream& operator>>(Istream& is, septernion&);
Ostream& operator<<(Ostream& os, const septernion& C);



class septernion
{
	// private data

		//- Translation vector
		vector t_;

		//- Rotation quaternion
		quaternion r_;


public:

	// Static data members

		static const char* const typeName;

		static const septernion zero;
		static const septernion I;


	// Constructors

		//- Construct null
		inline septernion();

		//- Construct given a translation vector and rotation quaternion
		inline septernion(const vector& t, const quaternion& r);

		//- Construct a pure translation septernion given a translation vector
		inline explicit septernion(const vector& t);

		//- Construct a pure rotation septernion given a rotation quaternion
		inline explicit septernion(const quaternion& r);

		//- Construct from Istream
		septernion(Istream&);


	// Member functions

		   // Access

			   inline const vector& t() const;
			   inline const quaternion& r() const;


		   // Edit

			   inline vector& t();
			   inline quaternion& r();


		   // Transform

			   //- Transform the given vector
			   inline vector transform(const vector& v) const;

			   //- Inverse transform the given vector
			   inline vector invTransform(const vector& v) const;


	// Member operators

		inline void operator*=(const septernion&);

		inline void operator=(const vector&);
		inline void operator+=(const vector&);
		inline void operator-=(const vector&);

		inline void operator=(const quaternion&);
		inline void operator*=(const quaternion&);
		inline void operator/=(const quaternion&);

		inline void operator*=(const scalar);
		inline void operator/=(const scalar);


	// IOstream operators

		friend Istream& operator>>(Istream& is, septernion&);
		friend Ostream& operator<<(Ostream& os, const septernion& C);
};


// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

//- Return the inverse of the given septernion
inline septernion inv(const septernion& tr);


//- Return a string representation of a septernion
word name(const septernion&);


//- Data associated with septernion type are contiguous
template<>
inline bool contiguous<septernion>() {return true;}


// * * * * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * //

inline bool operator==(const septernion& tr1, const septernion& tr2);
inline bool operator!=(const septernion& tr1, const septernion& tr2);
inline septernion operator+(const septernion& tr, const vector& t);
inline septernion operator+(const vector& t, const septernion& tr);
inline septernion operator+(const septernion& tr1, const septernion& tr2);
inline septernion operator-(const septernion& tr, const vector& t);
inline septernion operator-(const septernion& tr1, const septernion& tr2);
inline septernion operator*(const quaternion& r, const septernion& tr);
inline septernion operator*(const septernion& tr, const quaternion& r);
inline septernion operator/(const septernion& tr, const quaternion& r);
inline septernion operator*(const septernion& q1, const septernion& q2);
inline septernion operator/(const septernion& q1, const septernion& q2);
inline septernion operator*(const scalar s, const septernion& tr);
inline septernion operator*(const septernion& tr, const scalar s);
inline septernion operator/(const septernion& tr, const scalar s);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "septernionI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
