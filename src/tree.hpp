/**
 * @file tree.hpp
 *
 * @section desc File description
 *
 * Tree is a recursive structure using nodes.
 * Node stores a value (tag) and has several children
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
 * $Rev$ 0.3
 * $Author$ Benjamin Sientzoff
 * $URL$ http://www.github.com/blasterbug
 */

#ifndef TREE_HPP
#define TREE_HPP

#include <cassert>
#include <string>
//#include <list> // less efficiant
#include <forward_list>

using std::string;
using std::forward_list;

/** \brief exception class for trees
 * 
 * Usefull to manage errors and the unforeseen
 */
class TreeException : std::exception {
	private:
		char* _cause; /** store exception description */
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
		virtual ~TreeException() throw(){
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
 * A Node store a tag and can have several children
 */
template <typename T = char>
class Node {
	
	private:
		/// Number of children
		int _childNbr;
		/// letter stored into Node, the tag
		T _tag;
		/// children of the Node
		forward_list<Node<T>> _children;
	
	public:
		/** Copy constructor
		 * @param[in] other Node to copy
		 */
		Node(const Node<T> &other):
			_childNbr(other._childNbr),
			_tag(other._tag),
			_children(other._children)
			{}
			
		/** Simple constructor
		 * @param[in] data to store into the Node
		 */
		Node(T data):
		_childNbr(0),
		_tag(data)
		{
			// initialize the simply-linked list
			_children = forward_list<Node<T>>();
		}
		
		/** Destructor for Node
		 */
		~Node(){
			// usefull ?
			//delete &_children;
			//delete &_tag;
		}
		
		/** assignment operator overload
		 * @param[in] other node to assign
		 * @param[out] note assigned node
		 */
		Node<T>& operator=(Node<T> &other){
			// prevent objet copying itself
			if(this != &other){
				this->_childNbr = other._childNbr;
				this->_tag = other._key;
				this->_children = other._children;
			}
			return (*this); // allow a = b = c
		}
		
		/** equality operator
		 * @param[in] lhs left hand side, first node to compare
		 * @param[in] rhs right hand side, second node to compare
		 * @param[out] bool true if nodes have the same memory adress, else false
		 */
		bool operator==(const Node<T>& rhs){
			// same adress ⇒ same item
			return &this == &rhs;
		}
		
		/** inequality operator
		 * @param[in] lhs first node to compare
		 * @param[in] rhs second node to compare
		 * @param[out] bool true if nodes have not the same memory adress, else false
		 */
		bool operator!=(const Node<T>& rhs){
			return &this != &rhs;
			// return not(lhs == rhs);
		}
		
		/** Is the node a leaf ?
		 * @param[out] bool true, if no child, else false
		 */
		bool isLeaf(){
			return 0 == _childNbr;
		}
		
		/** The height of the node
		 * @param[out] hgt height of the node
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
		void append(T n_data){
			if(isLeaf()){
				// add the value in children list as a new node
				_children.push_front(Node<T>(n_data));
				_childNbr++;
			}
			else {
				bool undone = true;
				auto it = _children.begin();
				while(it != _children.end() and undone){
					if(it->_tag<n_data){
						it->append(n_data);
						undone = false;
					}
					else{
						++it;
					}
				}
			}
		}
		
		/** Remove a leaf from the node
		 * @param[in] data data of the node's tag to remove
		 * @exception TreeException Threw if data is not removed
		 */
		void remove(T data){
			// remove child with the right tag
			bool undone = true;
			auto it=_children.begin();
			while(it != it.end() and undone){
				if(it->_tag == data and it->isLeaf()){
					undone = false;
					delete it;
				}
				++it;
			}
			if(undone){
				throw TreeException("Element was not removed");
			}
		}
		
		/** What is the tag of the Node ?
		 * @param[out] tag The tag of the node
		 */
		T getTag(){ return _tag; }
		
		/** Do the tag is element or one of his children ?
		 * @param[in] element Element to look for
		 * @param[out] bool True if node or one of his child has the right tag,
		 * else false.
		 */
		bool contains(T element){
			if(isLeaf()){
				return element == _tag;
			}
			else {
				// browse children
				bool here = false;
				auto it = _children.begin();
				while(not here and not it.end()){
					here = it.contains(element);
					++it;
				}
				return here;
			}
		}
		/** Get a string representation of the node and his child
		 * @param[out] desc Description of the node (and his child)
		 */
		string toString(){
			if(isLeaf()){
				return string(_tag);
			}
			else {
				string desc = string(_tag);
				for(Node<T> child: _children){
					desc += ", " + child.toString();
				}
				return desc;
			}
		}
};

/** \brief Tree is a recursive structure using nodes.
 * 
 * A root value and subtrees of children, represented as a set of linked nodes.
 */
template <typename T = string>
class Tree {
	
	private:
		Node<T> _root; /** First node of the tree */
	
	public:
		/** Default constructor
		 */
		Tree():
			_root(nullptr)
			{}
			
		/** Copy constructor
		 */
		Tree(const Tree<T> &other):
			_root(other._root)
			{}
		
		/** Common constructor,
		 * create an tree
		 * @param[in] element Root of the tree
		 */
		Tree(T element): 
			_root(Node<T>(element))
			{}
			//_root = Node<T>(element);
		
		/** Destructor, destroy the whole tree
		 */
		~Tree(){
			//delete &_root;
		}
		
		/** Is the element in the tree ?
		 * @param[in] element Search the element in the Tree
		 * @param[out] bool True if element is here, else false.
		 */
		bool contains(T element){
			return _root->contains(element);
		}
		
		/** The height of the tree
		 * @param[out] hgt Height of the tree
		 */
		int height(){
			return _root.height();
		}
		
		/** Put an element in the tree
		 * @param[in] element New element to put into the tree
		 */
		void put(T element){
			_root.append(element);
		}
		
		/** Remove an element from the tree
		 * @param[in] data Element to remove
		 */
		void remove(T element){
			try{
				_root.remove(element);
			} catch(TreeException ex){
				// ?
			}
		}
		
		/** Get a string representation of the Tree
		 * @param[out] desc String representation of the tree
		 */
		string toString(){
			return _root.toString();
		}
};

#endif // TREE_HPP
