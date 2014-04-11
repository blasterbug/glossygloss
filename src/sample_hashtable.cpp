/**
 * @file sample_hashtable.cpp
 *
 * @section desc File description
 *
 * a sample of hashtable usages.
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
 * $Date$ 2014/03/28
 * $Rev$ 0.1
 * $Author$ Benjamin Sientzoff
 * $URL$ http://www.github.com/blasterbug
*/

#include <functional>
#include <iostream>
#include <cstdlib> // nécessaire pour utilisation atoi
#include <fstream> // Permet de lire et enregistrer des données dans un fichier
#include "hashtable.hpp"

#define K string
#define V string

using namespace std;


template<> unsigned computehash<K>(K element){
	// calcul de la clé de hachage en utilisant fonction fournie par API
	hash<K> hashcalculator;
	return hashcalculator(element);
}


int main(int argc,const char** argv){

	if(argc != 4){
		perror("Bad arguments!");
		exit(1);
	}

	Hashtable<K, V> storage = Hashtable<K, V>();
	fstream key_file;
	fstream value_file;

	string key;
	string value;

	key_file.open(argv[1], ios::in);
	key_file >> key;

	value_file.open(argv[2], ios::in);
	value_file >> value;

	int max = atoi(argv[3]);
	int i = 0;

	while(not key_file.eof() and not value_file.eof() and i<max){
		storage.put(key, value);
		key_file >> key;
		key_file >> value;
		++i;
	}

	key_file.close();
	value_file.close();

	cout << storage.toString() << endl;
	string reader ;
	cout << "Give the key to remove:" << endl;
	cin >> reader;
	try{
		storage.remove(reader);
	} catch(HashException ex) {
		cout << ex.what() << endl;
	}
	cout << storage.toString() << endl;
	cout << "Give a key to get the maped value" << endl;
	cin >> reader;
	try{
		cout << reader << " maped to " << storage.get(reader) << endl;
	} catch (HashException ex) {
		cout << ex.what() << endl;
	}
	return 0;
}
