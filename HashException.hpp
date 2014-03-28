/**
 * @file HashException.hpp
 *
 * @section desc File description
 *
 * Exception class for hash classes.
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

#ifndef HASHEXCEPTION_HPP
#define HASHEXCEPTION_HPP

#include <string>

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


#endif // HASHEXCEPTION_HPP

