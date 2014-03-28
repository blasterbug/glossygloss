/**
 * @file HashTable.hpp
 *
 * @section desc File description
 *
 * data structure to store pair in a table
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
#include "HashException.hpp"

/**
 * Fonction you must define
 */
<template K>
int computehash(K key);

using std::string;
/** \brief Alveole class
 * embodies a hashtable's alveole. An alveole store a pair <k,v>.
 * Alveoles are simply-linked elements.
 */
// TODO: implement iterator to browse within alveoles very quickly and easely
<template K = int, V = double>
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
			_valu(other._value)
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
		
		/** Does alveole have next ?
		 * @param[out] true if elements coming next, else false
		 */
		bool isQueue(){ return END == _next; }
		
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
		Alveole<k,V>* getNext(){
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
};

/** \brief Class HashTable to manage hash structure in an array
 */
<template K = int, V = double>
class HashTable {
	private:
		Alveole<K,V>** _table; /* array of alveoles */
		bool** _toc; /* array of occuped array cells */
	public:
		/** Simple constructor
		 */
		HashTable(){
			_table = new Alveole<K,V>[ARRAYSIZE];
			_toc = new bool[ARRAYSIZE];
		}
		
		/** Destructor
		 */
		~HashTable(){
			delete _table;
			delete _toc;
		}
		
		/** Add a new pair in the hash table,
		 * might not be already in
		 * @param[in] key key of the pair
		 * @param[in] value of the pair
		 * @exception HashException Threw if key already recorded
		 */
		// TODO: optimize this fucking code
		void add(K key, V value){
			int index = computehash(key)%ARRAYSIZE;
			// browse alveoles at this place
			Alveole<K,V>* browser = _table[index];
			bool undone = true;
			while(undone and END != browser){
				if(key == browser->getKey()){
					//if(value == browser->getValue()){
						throw HashException("Pair already recorded!");
					//} else {
						browser->setNext(new Alveole<K,V>(key, value));
						undone = false;
					}
				}
				browser = browser->getNext();
			}
			_toc[index] = true;
		}

		/** Change a value asociated to a kay
		 * @param[in] key the key of the pair to change
		 * @apram[in] n_value the new value of the pair
		 * @exception HashException threw if key not recorded
		 */
		void setValue(const K &key, V value){
			int index = computehash(key);
			bool undone = true;
			// browse alveole
			Alveole<K,V>* browser = _table[index];
			while(undone and END != browser){
				if(key == browser->getKey()){
					browser->setValue(value);
					undone = false;
				}
				browser = browser->getNext();
			}
			if(undone){
				throw HashException("Key lost");
			}
		}
};

#endif // HASHTABLE_HPP
