#include <iostream>
#include "database.h"

using namespace std; 

int main (int argc, char* argv[]) {
	
	if (argc != 3) {
		cout << endl 
			 << "Usage: shoppingListSaver <data.txt> <shoppingList.txt>" 
			 << endl; 
	} else {
		Database database(argv[1]); 
		database.createLists(argv[2]);
	}
	
	 
	
	return 0; 
}
