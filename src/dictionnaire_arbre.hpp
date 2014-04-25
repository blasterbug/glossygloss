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

class Dictionnaire{
	
	private :
		TreeString dico;

		/**
		 * Fonction basique d'échange
		 */
		void echanger(std::pair<string,int>* freq, int i){			
			std::pair<string,int> tmp = freq[i];
			freq[i]=freq[i+1];
			freq[i+1]=tmp;
		}
		
		/**
		 * Fonction basique de tri à bulle
		 */
		void triABulle(std::pair<string,int>* tableau, int longueur)
		{
		   int i;
		   bool permutation;
		   do{
			  permutation = false;
			  for(i=0; i<longueur-1; i++){
				 if(tableau[i].second<tableau[i+1].second){
					echanger(tableau, i);
					permutation = true;
				 }
			  }
			  longueur--;
		   }
		   while(permutation);
		}
		
		
		/**
		 * Fonction privée qui ajoute si nécessaire un mot dans la table des occurences
		 * @param[in] freq le tableau d'occurences
		 * @param[in] valeur la valeur à ajouter
		 * @param[in] nb le nombre de mots déjà présent dans le tableau
		 */
		void ajoutTrie(std::pair<string,int>* freq,std::pair<string,int> valeur){						
			int i=0;
			int j=10;
			while(valeur.second<freq[i].second and i<10){//on parcours le tableau jusqu'à trouver une occurence inférieur 
				++i;									//au mot que l'on souhaite ajouter
			}
			if(valeur.second>=freq[i].second){//si il en existe une
				//std::pair<string,int> tmp = freq[i];
			
				//~ for(int j = i+1;j<=9;++j){//puis on décale toutes les valeurs
					//~ std::pair<string,int> tmp2=freq[j];
					//~ freq[j]=tmp;
					//~ tmp=tmp2;
				//~ }
				while(j<i){
					freq[--j] = freq[j];
				}
				freq[i] = valeur;	//on ajoute le mot
			}
		}


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
		bool associerMot(string mot){
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
		 * Fonction qui retourne les 10 mots les plus fréquents
		 * @param[out] frequences, tableau des paires<mots,occurences> les plus fréquents
		 */
		void plusFrequentes(std::pair<string,int>* frequences){
			forward_list<pair<string,int>> words;
			dico.getWordsFrequencies(words);
			auto it = words.begin();
			while(it!=words.end()){
				ajoutTrie(frequences,*it); 
				++it;
			}
		}	
				
};

#endif // DICTIONNAIRE_HPP
