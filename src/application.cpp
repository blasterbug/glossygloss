/**
 * @file dictionnaire.hpp
 *
 * @section desc File description
 * 
 * Classe Test utilisant les deux implémentations du dictionnaire
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
 
 
 
#include <functional>
#include <iostream>
#include <cstdlib> // nécessaire pour utilisation atoi
#include <fstream> // Permet de lire et enregistrer des données dans un fichier
 
 using namespace std;
 
 #include "hash/dictionnaire.hpp" //dictionnaire utilisant la hashtable
 
 template<typename V> unsigned computehash<V>(V element){
	// calcul de la clé de hachage en utilisant fonction fournie par API
	hash<K> hashcalculator;
	return hashcalculator(element);
}
 
 int main(){
	 
	Dictionnaire<int>* dico = new Dictionnaire<int>();	 
	dico->ajouterMot("mot",1); 
	 
	 return 0;
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
