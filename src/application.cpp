/**
 * @file dictionnaire.cpp
 *
 * @section desc File description
 * 
 * Programme permettant de construire un dictionnaire en utilisant une 
 * structure de données de la librairie
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
 * $Date$ 2014/04/02
 * $Rev$ 0.2
 * $Author$ François Hallereau
 * $URL$ http://www.github.com/blasterbug/glossygloss
*/
#include <functional>
#include <iostream>
#include <fstream> // Permet de lire et enregistrer des données dans un fichier
//#include "dictionnaire_hash.hpp" //dictionnaire utilisant la hashtable
#include "dictionnaire_arbre.hpp"  //dictionnaire utilisant l'arbre

using namespace std;


 
 int main(){

	Dictionnaire dico = Dictionnaire();	
	dico.ajouterMot("mot");
	dico.ajouterMot("test");
	dico.associerMot("test");
	dico.ajouterMot("bla");
	dico.ajouterMot("truc");
	dico.ajouterMot("chien");
	dico.ajouterMot("chat");
	dico.ajouterMot("banane");
	dico.ajouterMot("sac");
	dico.ajouterMot("swag");
	dico.ajouterMot("mortel");
	dico.ajouterMot("lapin");
	dico.associerMot("banane");
	dico.associerMot("chien");
	dico.associerMot("chien");
	dico.associerMot("chien");
	dico.associerMot("chat");
	dico.associerMot("mot");
	dico.associerMot("mortel");
	pair<string,int>* freq = new std::pair<string,int>[10];
	dico.plusFrequentes(freq);
	cout<<freq<<endl<<&dico<<endl;
	
	for(int i=0;i<10;++i){
		cout<<freq[i].first<<" : "<<freq[i].second<<endl;
	}
	return 0;
}
