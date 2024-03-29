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
	Foam::HashSet

Description
	A HashTable with keys but without contents.

Typedef
	Foam::wordHashSet
	Foam::labelHashSet

Description
	A HashSet with (the default) word keys.

Typedef
	Foam::HashSet

Description
	A HashSet with default word keys.

\*---------------------------------------------------------------------------*/

#ifndef HashSet_H
#define HashSet_H

#include "HashTable.H"
#include "nil.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


template<class Key=word, class Hash=string::hash>
class HashSet
:
	public HashTable<nil, Key, Hash>
{

public:

	typedef typename HashTable<nil, Key, Hash>::iterator iterator;
	typedef typename HashTable<nil, Key, Hash>::const_iterator const_iterator;


	// Constructors

		//- Construct given initial size
		explicit HashSet(const label size = 128)
		:
			HashTable<nil, Key, Hash>(size)
		{}

		//- Construct from Istream
		explicit HashSet(Istream& is)
		:
			HashTable<nil, Key, Hash>(is)
		{}

		//- Construct from UList of Key
		explicit HashSet(const UList<Key>& lst)
		:
			HashTable<nil, Key, Hash>(2*lst.size())
		{
			forAll(lst, i)
			{
				insert(lst[i]);
			}
		}

		//- Construct by transferring the parameter contents
		explicit HashSet(const Xfer<HashSet<Key, Hash> >& hs)
		:
			HashTable<nil, Key, Hash>(hs)
		{}

		//- Construct by transferring the parameter contents
		explicit HashSet(const Xfer<HashTable<nil, Key, Hash> >& hs)
		:
			HashTable<nil, Key, Hash>(hs)
		{}

		//- Construct from the keys of another HashTable,
		//  the type of values held is arbitrary.
		template<class AnyType, class AnyHash>
		HashSet(const HashTable<AnyType, Key, AnyHash>&);


	// Member Functions

		// Edit

		//- Insert a new entry
		bool insert(const Key& key)
		{
			return HashTable<nil, Key, Hash>::insert(key, nil());
		}

		//- Insert keys from a UList of Key
		//  Return the number of new elements inserted
		label insert(const UList<Key>&);

		//- Same as insert (cannot overwrite nil content)
		bool set(const Key& key)
		{
			return insert(key);
		}

		//- Same as insert (cannot overwrite nil content)
		label set(const UList<Key>& lst)
		{
			return insert(lst);
		}

		//- Unset the specified key - same as erase
		bool unset(const Key& key)
		{
			return HashTable<nil, Key, Hash>::erase(key);
		}


	// Member Operators

		//- Return true if the entry exists, same as found()
		inline bool operator[](const Key&) const;

		//- Equality. Two hashtables are equal when their contents are equal.
		//  Independent of table size or order.
		bool operator==(const HashSet<Key, Hash>&) const;

		//- The opposite of the equality operation.
		bool operator!=(const HashSet<Key, Hash>&) const;


		//- Combine entries from HashSets
		void operator|=(const HashSet<Key, Hash>&);

		//- Only retain entries found in both HashSets
		void operator&=(const HashSet<Key, Hash>&);

		//- Only retain unique entries (xor)
		void operator^=(const HashSet<Key, Hash>&);

		//- Add entries listed in the given HashSet to this HashSet
		inline void operator+=(const HashSet<Key, Hash>& rhs)
		{
			this->operator|=(rhs);
		}

		//- Remove entries listed in the given HashSet from this HashSet
		void operator-=(const HashSet<Key, Hash>&);
};


// Global Operators

//- Combine entries from HashSets
template<class Key, class Hash>
HashSet<Key,Hash> operator|
(
	const HashSet<Key,Hash>& hash1,
	const HashSet<Key,Hash>& hash2
);


//- Create a HashSet that only contains entries found in both HashSets
template<class Key, class Hash>
HashSet<Key,Hash> operator&
(
	const HashSet<Key,Hash>& hash1,
	const HashSet<Key,Hash>& hash2
);


//- Create a HashSet that only contains unique entries (xor)
template<class Key, class Hash>
HashSet<Key,Hash> operator^
(
	const HashSet<Key,Hash>& hash1,
	const HashSet<Key,Hash>& hash2
);


//- A HashSet with word keys.
typedef HashSet<> wordHashSet;

//- A HashSet with label keys.
typedef HashSet<label, Hash<label> > labelHashSet;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#	include "HashSet.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
