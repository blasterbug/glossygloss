Glossygloss
===========

  Glossygloss is set of classes to use several data structures, C++ containers.   
  More might come soon.

### Documentation

  All documented things are [here](http://blasterbug.github.io/glossygloss/ "Glossygloss Main Page").   
  
  A PDF file *refman.pdf* is also available for offline doc.   
  
  You can generate the doc using [doxygen](http://www.stack.nl/~dimitri/doxygen/ "Doxygen Main Page") and the config file *doxygen_config*
  
  Usefull links :
  - [C++ programming on wikibooks](http://en.wikibooks.org/wiki/C%2B%2B_Programming "C++ programming on wikibooks")
  - what else ?
  
### Compilation
  Here is a sort intance showing how to compile and 'use' hashtable.hpp.   
  It works as well for others files.   
  
  We use C++11, so to compile using our classes:
	g++ -std=c++0x -g -Wall -pedantic -o sample_hashtable.bin sample_hashtable.cpp
  
### Testing and usage
  Once you compiled sample_hashtable.cpp, you can run the code using,
  assuming you are using an 
  UNIX system.
  
	chmod +x sample_hashtable.bin

	./sample_hashtable.bin lorem quod 50
  
  The first command giving execution permission to the compiled code.
  And the second one runs the program.
  All the words in the first file (lorem) will be maped to the wrd in quod.
  The last argument stands for the words number you want to put in the hashtable.
  
### Copyright

  This source code is protected by the French intellectual property law.
  
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; version 2
  of the License.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
  See the GNU General Public License for more details.


