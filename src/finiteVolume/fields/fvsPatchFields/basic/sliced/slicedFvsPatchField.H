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
	Foam::slicedFvsPatchField

Description
	Specialization of fvsPatchField which creates the underlying
	fvsPatchField as a slice of the given complete field.

	The destructor is wrapped to avoid deallocation of the storage of the
	complete fields when this is destroyed.

	Should only used as a template argument for SlicedGeometricField.

SourceFiles
	slicedFvsPatchField.C

\*---------------------------------------------------------------------------*/

#ifndef slicedFvsPatchField_H
#define slicedFvsPatchField_H

#include "fvsPatchField.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


template<class Type>
class slicedFvsPatchField
:
	public fvsPatchField<Type>
{

public:

	//- Runtime type information
	TypeName("sliced");


	// Constructors

		//- Construct from patch, internal field and field to slice
		slicedFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const Field<Type>&
		);

		//- Construct from patch and internal field
		slicedFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&
		);

		//- Construct from patch, internal field and dictionary
		slicedFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const dictionary&
		);

		//- Construct by mapping the given slicedFvsPatchField<Type>
		//  onto a new patch
		slicedFvsPatchField
		(
			const slicedFvsPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const fvPatchFieldMapper&
		);

		//- Construct as copy
		slicedFvsPatchField(const slicedFvsPatchField<Type>&);

		//- Construct and return a clone
		virtual tmp<fvsPatchField<Type> > clone() const;

		//- Construct as copy setting internal field reference
		slicedFvsPatchField
		(
			const slicedFvsPatchField<Type>&,
			const DimensionedField<Type, surfaceMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual tmp<fvsPatchField<Type> > clone
		(
			const DimensionedField<Type, surfaceMesh>& iF
		) const;


	// Destructor

		virtual ~slicedFvsPatchField();


	// Member functions

		// Access

			//- Return true if this patch field fixes a value.
			//  Needed to check if a level has to be specified while solving
			//  Poissons equations.
			virtual bool fixesValue() const
			{
				return true;
			}


		//- Write
		virtual void write(Ostream&) const;


	// Member operators

		virtual void operator=(const UList<Type>&) {}

		virtual void operator=(const fvsPatchField<Type>&) {}
		virtual void operator+=(const fvsPatchField<Type>&) {}
		virtual void operator-=(const fvsPatchField<Type>&) {}
		virtual void operator*=(const fvsPatchField<scalar>&) {}
		virtual void operator/=(const fvsPatchField<scalar>&) {}

		virtual void operator+=(const Field<Type>&) {}
		virtual void operator-=(const Field<Type>&) {}

		virtual void operator*=(const Field<scalar>&) {}
		virtual void operator/=(const Field<scalar>&) {}

		virtual void operator=(const Type&) {}
		virtual void operator+=(const Type&) {}
		virtual void operator-=(const Type&) {}
		virtual void operator*=(const scalar) {}
		virtual void operator/=(const scalar) {}
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#	include "slicedFvsPatchField.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
