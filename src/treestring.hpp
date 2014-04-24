/**
 * @file treestring.hpp
 *
 * @section desc File description
 *
 * TreeString is a recursive structure using nodes.
 * a Node stores a letter and has several children
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
 * $Date$ 2014/04/5
 * $Rev$ 0.1
 * $Author$ Benjamin Sientzoff
 * $URL$ http://www.github.com/blasterbug
 */

#ifndef TREESTRING_HPP
#define TREESTRING_HPP

#include <cassert>
#include <string>
#include <forward_list>
#include <utility>
#include <sstream>

using std::string;
using std::forward_list;
using std::stringstream;
using std::pair;

/** \brief exception class for trees
 * 
 * Usefull to manage errors and the unforeseen
 */
class TreeStringException : std::exception {
	private:
		char* _cause; /** store exception description */
	public:
		/** constructor
		 * called then TreeExceptions are threw
		 * @param[in] cause description of exception origin
		 */
		TreeStringException(char* cause):
			_cause(cause)
			{}
		
		/** destructor
		 * currently, do anything special
		 */
		virtual ~TreeStringException() throw(){
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
 * Class for nodes of a TreeString.
 * A Node store a letter and can have several children.
 */
class Node {
	
	private:
		/// Number of children
		int _childNbr;
		/// the end of a word and his frequency
		/// if _wordFrequency > 0, it's a word end
		int _wordFrequency;
		/// letter stored into Node, the tag
		char _tag;
		/// children of the Node
		forward_list<Node*> _children;
	
	public:
		/** Copy constructor
		 * @param[in] other Node to copy
		 */
		Node(const Node &other):
			_childNbr(other._childNbr),
			_wordFrequency(other._wordFrequency),
			_tag(other._tag),
			_children(other._children)
			{}
			
		/** Simple constructor
		 * @param[in] data to store into the Node
		 * @param[in] end is it the last letter of a word ?
		 */
		Node(char data, int frequency):
		_childNbr(0),
		_wordFrequency(frequency),
		_tag(data)
		{
			// initialize the simply-linked list
			_children = forward_list<Node*>();
		}
		
		/** Empty constructor
		 */
		Node():
		_childNbr(0),
		_wordFrequency(0),
		_tag('@')
		{
			// initialize the simply-linked list
			_children = forward_list<Node*>();
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
		Node& operator=(const Node &other){
			// prevent objet copying itself
			if(this != &other){
				this->_childNbr = other._childNbr;
				this->_tag = other._tag;
				this->_wordFrequency = other._wordFrequency;
				this->_children = other._children;
			}
			return (*this); // allow a = b = c
		}
		
		/** equality operator
		 * @param[in] lhs left hand side, first node to compare
		 * @param[in] rhs right hand side, second node to compare
		 * @param[out] bool true if nodes have the same memory adress, else false
		 */
		bool operator==(const Node& rhs){
			// same adress ⇒ same item
			return this == &rhs;
		}
		
		/** inequality operator
		 * @param[in] lhs first node to compare
		 * @param[in] rhs second node to compare
		 * @param[out] bool true if nodes have not the same memory adress, else false
		 */
		bool operator!=(const Node &rhs){
			return this != &rhs;
			// return not(lhs == rhs);
		}
		
		/** Is the node a leaf ?
		 * @param[out] bool true, if no child, else false
		 */
		bool isLeaf(){
			return 0 == _childNbr;
			//return frenquency > 0;
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
				// for each child - using C++11 syntax
				for(Node* child : _children){
					// compute child height and store it
					heights[1] = 1 + child->height();
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
		 * @param[in] frequency if greater than 0, end of a word.
		 * @param[out] newchild return the adress of the new child created
		 */
		Node* append(const char n_data, int frequency){
			Node* tmp;
			bool undone = true;
			auto it = _children.begin();
			// while n_data is not added
			while(undone and it != _children.end()){
				if(n_data == (*it)->_tag){
					(*it)->_wordFrequency += frequency; // update word frenquency
					tmp = (*it);
					undone = !undone; // job is now done
				}
				++it;
			}
			// if letter is not present, add it
			if(undone){
				 tmp = new Node(n_data, frequency);
				_children.push_front(tmp);
				_childNbr++;
			}
			return tmp;
		}  
		
		/** What is the tag of the Node ?
		 * @param[out] tag The tag of the node
		 */
		char getTag(){ return _tag; }
		
		
		/** Get a string representation of the node and his child
		 * @param[out] desc Description of the node (and his child)
		 */
		string toString(){
			if(isLeaf()){
				return string(&_tag);
			}
			else {
				string desc = string(&_tag);
				for(Node* child: _children){
					desc += ", " + child->toString();
				}
				return desc;
			}
		}

		/** Put each words in a list
		 * @param[in] words List containing all words
		 * @param[in] string wordCom Word which is currently reconvene
		 */
		void toList(forward_list<string> &words, string word){
			'@' != _tag?word += _tag:word; // if it's not the root, add tag
			if(0 < _wordFrequency){
				words.push_front(word);
			}
			if(not isLeaf()){
				for(Node* child : _children){
					child->toList(words, word);
				}
			}
		}

		/** Put each word in a list
		 * @param[in] words List containing all words and his frequency in pairs
		 * @param[in] string wordCom Word which is currently reconvene
		 */
		void toFrequencedList(forward_list<pair<string,int>> &words, string word){
			// if it's not the root, add tag
			// avoid to prefix words with '@', the root char
			'@' != _tag?word += _tag:word;
			// if it's a word end
			if(0 < _wordFrequency){
				// add the word and his frequency in a pair and
				// add it to the list
				words.push_front(pair<string,int>(word, _wordFrequency));
			}
			// if it's not a leaf
			if(not isLeaf()){
				// for each child
				for(Node* child : _children){
					// get words in the subtree
					child->toFrequencedList(words, word);
				}
			}
		}

};

/** \brief Tree is a recursive structure using nodes.
 * 
 * A root value and subtrees of children, represented as a set of linked nodes.
 */
class TreeString {
	
	private:
		Node _root; /** First node of the tree */
	
	public:
		/** Default constructor
		 */
		TreeString():
			_root(Node())
			{}
			
		/** Copy constructor
		 */
		TreeString(const TreeString &other):
			_root(other._root)
			{}
		
		/** Destructor, destroy the whole tree
		 */
		~TreeString(){
			//delete &_root;
		}
		
		/** The height of the tree
		 * @param[out] hgt Height of the tree
		 */
		int height(){
			return _root.height();
		}
		
		/** Put a word in the tree
		 * @param[in] word New element to put into the tree
		 */
		void put(const string &word){
			// adress of the last added Node
			Node* lastInserted = &_root;
			int i;
			int i_end = word.size()-1;
			// from the first to the last-but-one char
			for(i=0; i<i_end; ++i){
				// add it to the tree
				lastInserted = lastInserted->append(word[i], 0);
			}
			// add the last char and the frequence of the word
			lastInserted->append(word[i], 1); // end of the word
		}

		/** Get a string representation of the Tree
		 * @param[out] desc A string reprensation of the Tree where
		 * each Node tag is separated by a comma
		 */
		string toString(){
			return _root.toString();
		}
		
		/** Get a list of all words stored in Tree and
		 * their frequencies, i.e. how times a word was added
		 * @param[out] desc Each word is separated by a comma
		 */
		string getWords(){
			stringstream sstm; // faster and easier way to convert int to char
			// get the list of all words stored
			forward_list<pair<string,int>> words;
			_root.toFrequencedList(words, string());
			sstm << words.front().second;
			// start the result string with the first one
			string toReturn = words.front().first + " : " + sstm.str();
			words.pop_front();
			// for each word in the list
			for(pair<string, int> word : words){
				sstm.str(""); // clear stringstream
				sstm << words.front().second;
				// add it and a comma to the result string
				toReturn += ", " + word.first + " : " + sstm.str();
			}
			return toReturn;
		}
};

#endif // TREESTRING_HPP
