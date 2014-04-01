/**
 * @file tree.hpp
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

#ifndef HASHWORK_HPP
#define HASHWORK_HPP

#include <string>
#include <list>

using std::sting;
using std::list;

/** \brief exception class for trees
 * 
 * Usefull to manage errors and the unforeseen
 */
class TreeException : std::exception {
	private:
		char* _cause; /* store exception description */
	public:
		/** constructor
		 * called then TreeExceptions are threw
		 * @param[in] cause description of exception origin
		 */
		TreeException(char* cause):
			_cause(cause)
			{}
		
		/** destructor
		 * currently, do anything special
		 */
		virtual ~BagException() throw(){
			// do nothing
		}
		
		/** virtual fonction from superclass,
		 * usefull to get the exception description
		 */
		virtual const char* what()const throw(){
			return _cause;
		}
};

/** \brief Defines tree nodes.
 * 
 * Class for nodes of a tree.
 * A Knot store a tag and can have several children
 */
template <typename T = char>
class Node {
	
	private:
		/// letter stored into Knot, the tag
		T _tag;
		/// children of the Knot
		list<Knot<T>> _children;
	
	public:
		/** Copy constructor
		 * @param[in] other Node to copy
		 */
		Node<T>(const Node<T> &other) _tag(other._tag), _children(other._children)
		/** Simple constructor
		 * @param[in] data to store into the Node
		 */
		Node<T>(T data){
			// initialize the list
			_children = list<Node<T>>(Node<T>, sizeof(Node<T>>));
		}
		/** Destructor for Node
		 */
		~Node<T>(){
			// usefull ?
			delete _children;
		}
		
		/** assignment operator overload
		 * @param[in] other node to assign
		 * @param[out] assigned node
		 */
		Node<T>& operator =(Node<T> &other){
			// prevent objet copying itself
			if(this != &other){
				this->_tag = other._key;
				this.->_children = other._children;
			}
			return (*this); // allow a = b = c
		}
		
		/** equality operator
		 * @param[in] lhs left hand side, first node to compare
		 * @param[in] rhs right hand side, second node to compare
		 * @param[out] true if nodes have the same memory adress, else false
		 */
		operator ==(const Node<T> &lhs, const Node<T> &rhs){
			// same adress -> same item
			return &lhs == &rhs;
		}
		/** inequality operator
		 * @param[in] lhs first node to compare
		 * @param[in] rhs second node to compare
		 * @param[out] true if nodes have not the same memory adress, else false
		 */
		bool operator !=(const Node<T> &lhs, const Node<T> &rhs){
			return &lhs != &rhs;
			// return not(lhs == rhs);
		}
		/** Is the node a leaf ?
		 * @param[out] true, if no child, else false
		 */
		bool isLeaf(){
			return 0 == _children.size();
		}
		/** The height of the node
		 * @param[out] height of the node
		 */
		int height(){
			if(isLeaf()){
				return 0;
			}
			else {
				// start heights at zero
				// heights[0] : greatest height, heights[1] : computed height in the loop
				int heights[2] = {0,0};
				// for each child, using C++11 syntax
				//for(_children::iterator it=_children.begin(); it!=_children.end(); ++it){
				for(Node<T> child : _children){
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
		/** Hook up a new child to the node
		 * @param[in] n_data new data to store as a child of the node
		 */
		void append(<T> n_data){
			// add the value in chilmdren list as a new node
			_children.push_front(new Node<T>(n_data));
		}
		/** Remove a leaf from the node
		 * @param[in] data data of the node's tag to remove
		 */
		void remove(<T> data){
			// remove child with the right tag
			list<int>::iterator it=_children.begin();
			bool removed = false;
			while(it != it.end() and not removed){
				if(it->_tag == data and it->isLeaf()){
					removed = true;
					delete it;
				}
				++it;
			}
		}
		/// \brief get a representation of the node
		string toString();
};

/** \brief Tree is a recursive structure uses nodes.
 * 
 * A root value and subtrees of children, represented as a set of linked nodes.
 */
template <typename T = string>
class Tree {
	
	private:
		Node<T> _root;
	
	public:
		/// \brief copy constructor
		Tree(const Tree<T>&);
		/// \brief common constructor
		Tree();
		/// \brief destructor
		~Tree();
		/// \brief assignment operator
		Tree<T>& operator =(Tree<T>);
		/// \brief equal operator
		bool operator ==(const Tree<T>&, const Tree<T>&);
		/// \brief ne operator
		bool operator !=(const Tree<T>&, const Tree<T>&);
		/// \brief Is the element in the tree ?
		bool contains(T);
		/// \brief count among of appearances of a particular element
		int count(T);
		/// \brief the height of the tree
		int height();
		/// \brief add an element in the tree
		void add(T);
		/// \brief remove an element from the tree
		void remove(T);
		/// \brief get the whole list of elements in the tree
		T[] elements();
};



#endif // HASHWORK_HPP
