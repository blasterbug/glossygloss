/**
 * @file HashWord.tpp
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
 * $URL$ http://www.github.com/blasterbug
 */

#ifndef HASHWORK_TPP
#define HASHWORK_TPP

using std::sting;

/**
 *	CODE OF KNOT CLASS
 */
// copy constructor
<template T>
Knot::Knot<T>(const Knot<T> &other) _tag(other._tag), _children(other._children)
{}
// constructor
<template T>
Knot::Knot<T>(T tag) _tag(tag){
	// initialise the list
	_children = list<Knot<T>>(Knot<T>, sizeof(Knot<T>>));
}

// destructor
<template T>
Knot::~Knot<T>(){
	delete _children;
}

// assignment operator
<template T>
Knot<T>& Knot::operator =(Knot<T>){
	return Knot(this);
}

// equal operator
<template T>
bool Knot::operator ==(const Knot<T> &lhs, const Knot<T> &rhs){
	// same adress -> same item
	return &lhs == &rhs
}
// ne operator
<template T>
bool Knot::operator !=(const Knot<T> &lhs, const Knot<T> &rhs){
	return lhs != rhs;
}
// Is the knot a leaf ?
<template T>
bool Knot::isLeaf(){
	// leaf if no child
	return 0 == _children.size();
}
// the height of the knot
<template T>
int Knot::height(){
	if(isLeaf()){
		return 0;
	}
	else {
		// start heights at zero
		// heights[0] : greatest height, heights[1] : computed height in the loop
		int heights[2] = {0,0};
		// for each child, using C++11 syntax
		//for(_children::iterator it=_children.begin(); it!=_children.end(); ++it){
		for(Knot<T> child : _children){
			// compute child height and store it
			heights[1] = child.height();
			// if computed height is greater then the old one
			if(heights[0] < heights[1]){
				// store it as the new greate one
				heights[0] = heights[1];
			} // else, nothing
		}
		return heights[0];
	}
}

// Hook up a new child
<template T>
void Knot::append(<T> n_data){
	// add the value in chilmdren list as a new knot
	_children.push_front(new Knot<T>(n_data));
}
// remove a child, which MUST BE leaf
<template T>
void Knot::remove(<T> data){
	// remove child with the right tag
	list<int>::iterator it=_children.begin();
	bool removed = false;
	while(it != it.end() and not removed){
		if(it->_tag == data){
			removed = true;
			delete it;
		}
		++it;
	}
}
// get a representation of the knot
<template T>
string Knot::toString(){
	string repr = "";
	for(Knot child : _children
}

/**
 * CODE OF TREE CLASS
 */
// copy constructor
<template T>
Tree::Tree(const Tree<T>&);
// common constructor
<template T>
Tree::Tree();
// destructor
<template T>
Tree::~Tree();
// assignment operator
<template T>
Tree<T>& Tree::operator =(Tree<T>);
// equal operator
<template T>
bool Tree::operator ==(const Tree<T>&, const Tree<T>&);
// ne operator
<template T>
bool Tree::operator !=(const Tree<T>&, const Tree<T>&);
// Is the element in the tree ?
<template T>
bool Tree::contains(T);
// count among of appearances of a particular element
<template T>
int Tree::count(T);
// the height of the tree
<template T>
int Tree::height();
// add an element in the tree
<template T>
void Tree::add(T);
// remove an element from the tree
<template T>
void Tree::remove(T);
// get the whole list of elements in the tree
<template T>
T[] Tree::elements();


#include "HashWord.tpp"

#endif // HASHWORK_HPP
