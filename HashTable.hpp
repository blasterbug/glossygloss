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

#ifndef END
#define END 0
#endif

// section of included files
#include <string>
#include "HashException.hpp"



using std::string;
/** Alveole class
 * embodies a hashtable's alveole. An alveole store a pair <k,v>.
 * Alveoles are simply-linked elements.
 */
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
		Alveole(const Alveole<K,V> &other){
			_key = other._key;
			_value = other._value;
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
		Alveole(K key, V value) _key(key),c_value(value), _next(END){}
		
		/** Complex constructor
		 * @param[in] key key of the pair
		 * @param[in] value value of the pair
		 * @param[in] next adresse to the next alveole
		 */
		Alveole(K key, V value, Alveole<K,V>* next) _key(key), _value(value), _next(next){}
		
		/** Does alveole have next ?
		 * @param[out] true if elements coming next, else false
		 */
		bool isQueue(){	return END == _next; }
		
		/** Get the key of an alveole
		 * @param[out] key stored into the alveole
		 */
		 K getKey(){ return _key; }
		 
		/** Get the value stored into an alveole
		 * @param[out] value of the alveole
		 */
		V getValue(){ return _value; }
		 
		 /** Set the value stored into an alveole
		  * @param[in] n_value The new value of the pair
		  */
		void setValue(V n_value){ _value = n_value; }
};

#endif // HASHTABLE_HPP
