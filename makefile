shoppingManager: main.cpp database.cpp database.h
	g++ -g main.cpp database.cpp -o $@
	./$@ data.txt shoppingList.txt
	
gshoppingManager: main.cpp database.cpp database.h
	g++ -g main.cpp database.cpp -o $@
	gdb -tui --args $@ data.txt shoppingList.txt

clean: 
	rm mercadona.txt dia.txt supersol.txt shoppingListManager

