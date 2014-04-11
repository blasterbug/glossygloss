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
#include "dictionnaire/dictionnaire.hpp" //dictionnaire utilisant la hashtable

using namespace std;
 
template<> unsigned computehash<string>(string element){
	// calcul de la clé de hachage en utilisant fonction fournie par API
	hash<string> hashcalculator;
	return hashcalculator(element);
}
 
 int main(){

	Dictionnaire<int> dico = Dictionnaire<int>();	
	dico.ajouterMot("mot",1);
	//cout << dico.toString() << endl;
	return 0;
}
