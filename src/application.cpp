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


 
 int main(int argc,const char** argv){

	if(2 != argc){
		perror("Bad arguments!");
		exit(1);
	}

	Dictionnaire dico = Dictionnaire();	
	
	fstream file;
	string word;
	file.open(argv[1], ios::in);
	int j=0;
	cout<<"Fichier ouvert, début de la lecture"<<endl;
	while(not file.eof()){
		file >> word;
		if(dico.contientMot(word)){
			dico.associerMot(word);
		}
		else{
			dico.ajouterMot(word);
		}
		++j;
	}
	file.close();
	cout<<"Lecture terminé "<<j<<" mots ont été ajoutés"<<endl;

	pair<string,int>* freq = new pair<string,int>[10];

	cout<<"Récupération des mots les plus fréquents : "<<endl;
	dico.plusFrequentes(freq);
	cout<<"Test"<<endl;
	for(int i=0;i<10;++i){
		cout<<freq[i].first<<" : "<<freq[i].second<<endl;
	}
	return 0;
}
