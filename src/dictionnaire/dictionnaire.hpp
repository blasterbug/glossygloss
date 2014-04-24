/**
 * @file dictionnaire.hpp
 *
 * @section desc File description
 *
 * Dictionnaire utilisant une hashtable
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
 #include <utility>
 
#ifndef DICTIONNAIRE_HPP
#define DICTIONNAIRE_HPP


class Dictionnaire{
	
	private :
		Hashtable<string,int> dico;
		
		
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
		void ajoutTrie(std::pair<string,int>* freq,std::pair<string,int> valeur,int* nb ){						
			if(*nb<9){//si il y a moins de 9 occurences dans le tableau
				freq[*nb] = valeur;//on ajoute le mot sans soucier de l'ordre
				++(*nb);
			}else if(*nb==9){//si il y a 9 occurences
				freq[*nb] = valeur;//on ajoute le mot
				++(*nb);
				triABulle(freq,*nb);//puis on tri le tableau
			}
			else{//sinon
				int i=0;
				while(valeur.second<freq[i].second && i<10){//on parcours le tableau jusqu'à trouver une occurence inférieur 
					++i;									//au mot que l'on souhaite ajouter
				}
				if(valeur.second>freq[i].second){//si il en existe une
					std::pair<string,int> tmp = freq[i];
					freq[i] = valeur;//on ajoute le mot
					for(int j = i+1;j<9;++j){//puis on décale toutes les valeurs
						std::pair<string,int> tmp2=freq[j];
						freq[j]=tmp;
						tmp=tmp2;
				}
			}
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
			return dico.contains(mot);
		}			
		
		/**
		 * Fonction qui ajoute un mot non présent dans le dictionnaire
		 * @param[in] mot, le mot à ajouter
		 * @param[in] v, la valeur associée
		 */
		void ajouterMot(string mot){
			dico.put(mot,1);
		}	

		/**
		 * Fonction qui modifie la valeur d'un mot présent dans le dictionnaire
		 * @param[in] mot, le mot à modifier
		 * @param[in] v, la valeur à modifier
		 * @param[out] bool Renvoyer faux si le mot n'est pas présent, sinon vrai
		 */
		bool associerMot(string mot){
			if(dico.contains(mot)){
				dico.put(mot,dico.get(mot)+1);
				return true;
			}
			else {
				return false;
			}
		}	

		/**
		 * Fonction qui supprime un mot présent dans le dictionnaire
		 * @param[in] mot, le mot à supprimer
		 * @param[out] bool Renvoie vrai si le mot a été supprimé, sinon faux
		 */
		bool supprimerMot(string mot){
			try{
				dico.remove(mot);
				return true;
			}catch(HashException e){
				return false;
			}
		}	
		
		/**
		 * Fonction qui récupère la valeur associée au mot
		 * @param[in] mot le mot dont on souhaite savoir la valeur associée
		 * @param[out] valeur la valeur associée
		 * @exception lève une exception si le mot n'est pas présent dans le dictionnaire
		 */
		int valeurAssociee(string mot){
			int valeur;
			try{
				valeur = dico.get(mot);
				return valeur;
			}catch(HashException e){
				throw HashException("Le mot spécifié n'existe pas dans le dictionnaire");
			}
		}
				
		/**
		 * Fonction qui retourne les 10 mots les plus fréquents
		 * @param[out] frequences, tableau des paires<mots,occurences> les plus fréquents
		 */
		void plusFrequentes(std::pair<string,int>* frequences){
			int nb = 0;
			std::vector<string> mots(0);
			dico.getAllKeys(&mots);//on stocke toutes les clés de la table
			for(string mot : mots){//puis on les ajoutes si nécessaire.
				ajoutTrie(frequences,std::pair<string,int>(mot,dico.get(mot)), &nb); 
			}
		}	
				
};

#endif // DICTIONNAIRE_HPP
