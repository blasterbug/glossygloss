/**
 * @file hashtable.hpp
 *
 * @section desc File description
 *
 * data structure to store pairs in a table
 * a hashcode is compute with k to evaluate the suitable place to store the pair
 * 
 * !! WARNING: int hashCode(K key) must be implemented !!
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
 
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/// macro to define end of alveole chains
#ifndef END
#define END 0
#endif

/// macro to define size of hash arrays
#ifndef ARRAYSIZE
#define ARRAYSIZE 50
#endif

// section of included files
#include <string>

/**
 * Fonction you must define
 * @param[in] element element to compute hashcode from
 * @param[out] the hashcode of element, an unsigned integer 
 */
template <typename K>
int computehash(K element);

using std::string;

/**
 * \brief Exception class to manage hashtable errors
 */
class HashException : std::exception {
	private:
		char* _cause; /* store exception description */
	public:
		/** constructor
		 * called then HashExceptions are threw
		 * @param[in] cause description of exception origin
		 */
		HashException(char* cause):
			_cause(cause)
			{}
		
		/** destructor
		 * currently, do anything special
		 */
		virtual ~HashException() throw(){
			// do nothing
		}
		
		/** virtual fonction from superclass,
		 * usefull to get the exception description
		 */
		virtual const char* what()const throw(){
			return _cause;
		}
};

/** \brief Class to define hashtable alveoles.
 * 
 * Alveole class embodies a hashtable's alveole. An alveole store a pair <k,v>.
 * Alveoles are simply-linked elements.
 */
// TODO: implement iterator to browse within alveoles very quickly and easely
template <typename K, typename V>
class Alveole{
	private:
		K _key; /* key of the pair */
		V _value; /* value of the pair */
		Alveole<K,V>* _next; /* next aveole */
	public:
		/**
		 * Copy constructor
		 * @param[in] other the alveole to copy
		 */
		Alveole(const Alveole<K,V> &other):
			_key(other._key),
			_value(other._value)
			{
				// if there are elements coming next
				if(END != other._next){
					_next = new Alveole(other._next);
				}
				else { _next = END; }
		}
		
		/** Pair constructor
		 * @param[in] key key of the pair
		 * @param[in] value value of the pair
		 */
		Alveole(K key, V value) :
			_key(key), _value(value),
			_next(END)
			{}
			
		/** Empty constructor
		 * create a 'empty' alveole
		 */
		Alveole(){};
		
		/** Complex constructor
		 * @param[in] key key of the pair
		 * @param[in] value value of the pair
		 * @param[in] next adresse to the next alveole
		 */
		Alveole(K key, V value, Alveole<K,V>* next):
			_key(key),
			_value(value),
			_next(next)
			{}
		
		/** Get the key of an alveole
		 * @param[out] key stored into the alveole
		 */
		 K getKey(){ return _key; }
		 
		/** Get the value stored into an alveole
		 * @param[out] value of the alveole
		 */
		V getValue(){ return _value; }
		
		/** Which alveole coming next ?
		 * @param[out] memory adres of the next alveole
		 */
		Alveole<K,V>* getNext(){
			return _next;
		}
		 
		 /** Set the value stored into an alveole
		  * @param[in] n_value The new value of the pair
		  */
		void setValue(V n_value){ _value = n_value; }
		
		/** Set the next adress of the next alveole
		 * @param[in] n_next adress of the new next alveole
		 */
		void setNext(Alveole<K,V>* n_next){
			_next = n_next;
		}
		
		/** Return a string descriptionof the pair stored into the alveole
		 * @param[out] a string represention of the alveole
		 */
		string toString(){
			string desc = ("{" + _key + ", " + _value + "}");
			if(END == _next){
				return desc;
			} else {
				return _next->toString() + ", " + desc;
			}
		}
};

/** \brief Maps a key to a value.
 * 
 * 
 */
template <typename K, typename V>
class Hashtable {
	
	private:
		Alveole<K,V>** _table; /* array of alveoles */
		
	public:
		/** Simple constructor
		 */
		Hashtable(){
			_table = new Alveole<K,V>*[ARRAYSIZE];
			for(int i = 0; i<ARRAYSIZE; ++i){
				_table[i] = END;
			}
		}
		
		/** Destructor
		 */
		~Hashtable(){
			delete[] _table;
		}
		
		/** Do table contains key ?
		 * @param[in] key key to find
		 * @param[out] True if the key is here, else false
		 */
		bool contains(const K &key){
			bool here = false;
			int index = computehash(key)%ARRAYSIZE;
			Alveole<K,V>* browser = _table[index];
			while(not here and END != browser){
				if(key == browser->getKey()){
					here = true;
				}
				browser = browser->getNext();
			}
			return here;
		}
		
		/** Return the value associated with the specified key
		 * @aparam[in] key a key in the hashtable
		 * @param[out] value associated with the key
		 * @exception HashException threw if key is not in the hashtable
		 */
		V get(const K &key){
			int index = computehash(key)%ARRAYSIZE;
			Alveole<K,V>* browser = _table[index];
			bool undone = true;
			while(undone and END != browser){
				if(key == browser->getKey()){
					undone = false;
				}
				browser = browser->getNext();
			}
			if(undone){
				throw HashException("The key is not associated with a value !");
			} else {
				return browser->getValue();
			}
			// undone?HashException("The key is not associated with a value !"):return browser->getValue();
		}
		
		/** Tests if this hashtable maps no keys to values.
		 * @param[out] true if no elements in the hashtable, else false;
		 */
		bool isEmpty(){
			bool empty = true;
			int i = 0;
			while(empty and i<ARRAYSIZE){
				if(END != _table[i]){
					empty = false;
				}
				++i;
			}
			return empty;
		}
		
		/** Map the specified key to the specified value in this hashtable.
		 * or update the maped value to the key
		 * @param[in] key key of the pair
		 * @param[in] value value of the pair
		 */
		// TODO: optimize this fucking code
		void put(K key, V value){
			// where to put the pair ?
			int index = computehash(key)%ARRAYSIZE;
			// browse alveoles at this place
			Alveole<K,V>* browser = _table[index];
			bool undone = true;
			while(undone and END != browser){
				if(key == browser->getKey()){
					browser->setValue(value);
					undone = false;
				}
				browser = browser->getNext();
			}
			if(undone) _table[index] = new Alveole<K,V>(key, value);
		}
		
		/** Remove the key (and its corresponding value) from this hashtable.
		 * @param[in] key Key of the pair to delete
		 * @exception HashException threw if table does not contain key
		 */
		void remove(const K &key){
			int index = computehash(key)%ARRAYSIZE;
			Alveole<K,V>* bef = new Alveole<K,V>*(); 
			bef->setNext(_table[index]);
			Alveole<K,V>* cur =_table[index];
			bool undone = true;
			while(undone and END != cur){
				if(key == cur->getKey()){
					bef->setNext(cur->getNext());
					delete cur;
					undone = false;
				}
				bef = cur;
				cur = cur->getNext();
			}
			if(undone) throw HashException("Key is not here!");
		}
		
		/** Return a description of the hashtable, enclosed in braces as
		 * well as {key, value}.
		 * @param[out] a string representation of this hashtable.
		 */
		string toString(){
			string desc = "[";
			for(int i = 0; i<ARRAYSIZE; ++i){
				if(END != _table[i]){
					desc += (_table[i]->toString() + ", ");
				}
			}
			return desc + "]";
		}
		
};

#endif // HASHTABLE_HPP
