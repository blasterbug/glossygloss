/**
 * @file pair.hpp
 *
 * @section desc File description
 *
 * data structure to store pairs.
 * A pair is a set of two values, not necassary the same type
 *
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * @section infos File informations
 *
 * $Date$ 2014/04/15
 * $Rev$ 0.2
 * $Author$ Benjamin Sientzoff
 * $URL$ http://www.github.com/blasterbug
 *
*/
#ifndef PAIR_HPP
#define PAIR_HPP

// included files section
#include <string>
#include <cassert>

// will desactive cassert
//#define NDEBUG

template <typename L, typename R>
/**
 * A pair is set of two elements.
 */
class pair{
	private:
		L _left; /** the first value of the pair */
		R _right; /** the second value stored in the pair */

	public:
	/** Common constructor
	 * @param[in] value1 The first value to store
	 * @param[in] value2 The second value to store
	 */
	pair(L value1, R value2):
		_left(value1),
		_right(value2) {}

	/** Copy constructor
	 * @param[in] other The pair to copy
	 */
	pair(const pair<L,R> &other):
		_left(other._left),
		_right(other._right) {}

	/** Destructor for pair
	 */
	~pair(){
		delete &_left;
		delete &_right;
	}

	/** Get the first value
	 * @param[out] value1 The first value stored into the pair
	 */
	L getLeft(){ return _left; }

	/** Get the second value
	 * @param[out] value2 The second value stored by the pair
	 */
	R getRight(){ return _right; }
};
#endif // PAIR_HPP
