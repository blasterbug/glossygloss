/**
 * @file HashWord.hpp
 *
 * @section desc File description
 *
 * Implémentation d'un arbre pour stocker des mots.
 * Chaque noeud stocke une lettre.
 *
 * @section copyright Copyright
 *
 * This source code is protected by the French intellectual property law.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2
 * of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @section infos File informations
 *
 * $Date$ 2014/03/27
 * $Rev$ 0.1
 * $Author$ Benjamin Sientzoff
 * $URL$
 */

#ifndef HASHWORK_HPP
#define HASHWORK_HPP

#include <string>
#include <list>
#include "Alist.hpp"

using std::sting;
using std::list;

// class for knots of a tree
<template T = char>
class Knot {
	
	private:
		// letter stored into knot, the tag
		T _tag;
		// children of the knot
		list<Knot<T>> _children;
	
	public:
		// copy constructor
		Knot<T>(const Knot<T>&);
		// constructor
		Knot<T>(T);
		// destructor
		~Knot<T>();
		// assignment operator
		Knot<T>& operator =(Knot<T>);
		// equal operator
		bool operator ==(const Knot<T>&, const Knot<T>&);
		// ne operator
		bool operator !=(const Knot<T>&, const Knot<T>&);
		// Is the knot a leaf ?
		bool isLeaf();
		// the height of the knot
		int height();
		// Hook up a new child
		void append(<T>);
		// remove a child
		void remove(<T>);
		// get a representation of the knot
		string toString();
}

// class for the tree, use Knot
<template T = string>
class Tree {
	
	private:
		Knot<T> _root;
	
	public:
		// copy constructor
		Tree(const Tree<T>&);
		// common constructor
		Tree();
		// destructor
		~Tree();
		// assignment operator
		Tree<T>& operator =(Tree<T>);
		// equal operator
		bool operator ==(const Tree<T>&, const Tree<T>&);
		// ne operator
		bool operator !=(const Tree<T>&, const Tree<T>&);
		// Is the element in the tree ?
		bool contains(T);
		// count among of appearances of a particular element
		int count(T);
		// the height of the tree
		int height();
		// add an element in the tree
		void add(T);
		// remove an element from the tree
		void remove(T);
		// get the whole list of elements in the tree
		T[] elements();
}


#include "HashWord.tpp"

#endif // HASHWORK_HPP
