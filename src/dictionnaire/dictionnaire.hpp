/**
 * @file dictionnaire.hpp
 *
 * @section desc File description
 *
 * Dictionnaire utilisant une hashtable
 * 
 * 
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
 * $Rev$ 0.2
 * $Author$ Benjamin Sientzoff & François Hallereau
 * $URL$ http://www.github.com/blasterbug
 */
 
 #include "../hashtable.hpp"
 
#ifndef DICTIONNAIRE_HPP
#define DICTIONNAIRE_HPP


template <typename V>
class Dictionnaire{
	
	private :
		Hashtable<string,V> dico;
	
	public :
	
		/**
		 * Constructeur de la classe Dictionnaire
		 */
		Dictionnaire(){}
		
		
		/**
		 * Destructeur de la classe Dictionnaire
		 */
		~Dictionnaire(){}
	
		/**
		 * Fonction qui renvoie vrai le mot est présent dans le Dictionnaire
		 * @param[in] mot, le mot à tester
		 * @param[out] bool, vrai si présent, faux sinon.
		 */
		bool contientMot(string mot){
			return dico.contains(mot);
		}			
		
		/**
		 * Fonction qui ajoute un mot non présent dans le dictionnaire
		 * @param[in] mot, le mot à ajouter
		 * @param[in] v, la valeur associée
		 */
		void ajouterMot(string mot, V v){
			dico.put(mot,v);
		}	

		/**
		 * Fonction qui modifie la valeur d'un mot présent dans le dictionnaire
		 * @param[in] mot, le mot à modifier
		 * @param[in] v, la valeur à modifier
		 * @exception lève une exception si le mot n'est pas présent
		 */
		void associerMot(string mot, V v){
			if(dico.contains(mot))
				dico.put(mot,v);
			else
				throw HashException("Le mot spécifié n'existe pas dans le dictionnaire");
		}	

		/**
		 * Fonction qui supprime un mot présent dans le dictionnaire
		 * @param[in] mot, le mot à supprimer
		 * @exception lève une exception si le mot n'est pas présent
		 */
		void supprimerMot(string mot){
			try{
				dico.remove(mot);
			}catch(exception& e){
				throw HashException("Le mot spécifié n'existe pas dans le dictionnaire");
			}
		}	
		
		/**
		 * Fonction qui récupère la valeur associée au mot
		 * @param[in] mot, le mot dont on souhaite savoir la valeur associée
		 * @param[out] valeur, la valeur associée
		 * @exception lève une exception si le mot n'est pas présent dans le dictionnaire
		 */
		V valeurAssociee(string mot){
			V valeur;
			try{
				valeur = dico.get(mot);
				return valeur;
			}catch(exception& e){
				throw HashException("Le mot spécifié n'existe pas dans le dictionnaire");
			}
		}		

	
};

#endif // DICTIONNAIRE_HPP
