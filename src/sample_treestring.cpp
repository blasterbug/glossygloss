/**
 * @file sample_treestring.cpp
 *
 * @section desc File description
 *
 * a sample to show how to use TreeString class
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
 * $Date$ 2014/04/21
 * $Rev$ 0.1
 * $Author$ Benjamin Sientzoff
 * $URL$ http://www.github.com/blasterbug
 */

#include <functional>
#include <iostream>
#include <cstdlib> // nécessaire pour utilisation atoi
#include <fstream> // Permet de lire et enregistrer des données dans un fichier
#include "treestring.hpp"

using namespace std;

int main(int argc,const char** argv){
	
	if(3 != argc){
		perror("Bad arguments!");
		exit(1);
	}
	
	fstream file;
	
	string word;
	
	file.open(argv[1], ios::in);
	
	TreeString storage = TreeString();
	
	int max = atoi(argv[2]);
	int i = 0;
	while(not file.eof() and i<max){
		file >> word;
		//cout << word << endl;
		storage.put(word);
		++i;
	}
	
	file.close();

	cout << "Tree nodes : " << storage.toString() << endl;
	cout << "Tree height : " << storage.height() << endl;
	forward_list<string> words;
	storage.getWords(words);
	cout << "Word in tree :" << words.front();
	words.pop_front();
	for(string word : words){
		cout << ", " << word;
	}
	cout << endl;
	forward_list<pair<string, int>> freq = forward_list<pair<string, int>>();
	storage.getWordsFrequencies(freq);
	cout << "Frequencies words : " << endl;
	cout << freq.front().first << " : " << freq.front().second << endl;
	freq.pop_front();
	for(pair<string, int> freqWord : freq){
		cout << ", " << freqWord.first << " : " << freqWord.second;
	}
	cout << endl;
	return 0;
}

