/**
 * @file dictionnaire.hpp
 *
 * @section desc File description
 *
 * Dictionnaire utilisant un arbre
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
 

 
#ifndef DICTIONNAIRE_HPP
#define DICTIONNAIRE_HPP

#include "treestring.hpp"
#include <utility>

/**
 * Fonction qui permet de trier un container de pairs construit
 * avec des strings et des entiers. Le critère de tri est l'ordre naturel
 * sur les entiers appliqué à l'entier de la pair.
 * @param[in] first la première pair à comparer
 * @param[in] second la seconde pair à comparer
 * @param[out] bool vrai si first>seconde sinon faux
 */
bool triPair(const pair<string, int> &first, const pair<string, int> &second){
	return first.second > second.second;
}

class Dictionnaire{
	
	private :
		TreeString dico;

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
			bool trouve=false;
			forward_list<string> list;
			dico.getWords(list);
			auto it = list.begin();
			while(it!=list.end() and !trouve){
				trouve = (it->compare(mot)==0);
				++it;
			}
			return trouve;
			
		}			
		
		/**
		 * Fonction qui ajoute un mot non présent dans le dictionnaire
		 * @param[in] mot, le mot à ajouter
		 */
		void ajouterMot(string mot){
			dico.put(mot);
		}	

		/**
		 * Fonction qui modifie la valeur d'un mot présent dans le dictionnaire
		 * @param[in] mot, le mot à modifier
		 * @param[out] bool Renvoyer faux si le mot n'est pas présent, sinon vrai
		 */
		void associerMot(string mot){
			dico.put(mot);
		}	
			
		/**
		 * Fonction qui récupère la valeur associée au mot
		 * @param[in] mot le mot dont on souhaite savoir la valeur associée
		 * @param[out] valeur la valeur associée
		 * @exception lève une exception si le mot n'est pas présent dans le dictionnaire
		 */
		int valeurAssociee(string mot){
			bool trouve=false;
			forward_list<pair<string,int>> words;
			dico.getWordsFrequencies(words);
			auto it = words.begin();
			while(it!=words.end() and !trouve){
				trouve = ((it->first).compare(mot)==0);
				++it;
			}
			return it->second;
		}
				
		/**
		 * Fonction qui retourne les dix mots les plus fréquents dans un tableau
		 * @param[int] frequences tableau des paires<mots,occurences> les plus fréquents
		 */
		void plusFrequentes(pair<string,int> *frequences){
			forward_list<pair<string, int>> pairs;
			// on récupère les mots avec leurs fréquences
			dico.getWordsFrequencies(pairs);
			// on tri la liste
			pairs.sort(&triPair); // complexité : n(log(n))
			auto it_pairs = pairs.begin();
			int i = 0;
			// on met les dix premières pairs dans le tableau
			while(i<10 and pairs.end() != it_pairs){
				frequences[i++] = *it_pairs;
				++it_pairs;
			}
		}
};

#endif // DICTIONNAIRE_HPP
