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
 * $URL$
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
	_children = list<Knot<T>>(Knot<T>, sizeof(Knot<T>>));
}
// destructor
<template T>
Knot::~Knot<T>();
// assignment operator
<template T>
Knot<T>& Knot::operator =(Knot<T>);
// equal operator
<template T>
bool Knot::operator ==(const Knot<T>&, const Knot<T>&);
// ne operator
<template T>
bool Knot::operator !=(const Knot<T>&, const Knot<T>&);
// Is the knot a leaf ?
<template T>
bool Knot::isLeaf();
// the height of the knot
<template T>
int Knot::height();
// Hook up a new child
<template T>
void Knot::append(<T>);
// remove a child
<template T>
void Knot::remove(<T>);
// get a representation of the knot
<template T>
string Knot::toString();

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
