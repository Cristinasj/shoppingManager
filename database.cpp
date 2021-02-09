#include "database.h" 
#include <iostream> 
#include <fstream> 
#include <algorithm>
#include <utility>

using namespace std; 

Database::Database(string filename) {
	ifstream data; 
	int numberShops; 
	int numberProducts;
	
	data.open(filename); 
	data >> numberShops; 
	for (int i = 0; i < numberShops; i++) {
		string newShop; 
		data >> newShop; 
		shops.push_back(newShop); 
	}
	data >> numberProducts; 
	for (int i = 0; i < numberProducts; i++) {
		string newProduct; 
		data >> newProduct; 
		products.push_back(newProduct); 
		vector<double> pricesAux = {}; 
		for (int j = 0; j < numberShops; j++) {
			double newPrice;
			data >> newPrice; 
			pricesAux.push_back(newPrice); 
		}
		prices.push_back(pricesAux); 
	}
	data.close();
}

void Database::createLists(string shoppingList) {
	// Reading of the shopping list 
	vector<string> shopping; 
	ifstream file; 
	file.open(shoppingList);
	string item;
	if (!file.eof())
		file >> item; 
	while(!file.eof()) { 
		shopping.push_back(item);
		file >> item;  
	}
	file.close();
	
	// Creation of the smaller lists
	vector<vector<pair<string,double>>> smallLists;  
	// Name of the shop 
	for (int i = 0; i < shops.size(); i++) { 
		vector<pair<string,double>> aux;
		pair<string,double> first; 
		aux.push_back(first); 
		aux[0].second = 0.0; 
		string shopName = shops[i]; 
		// Capital leters 
		for(char &c: shopName) {
			if (c >= 'a' && c <= 'z')
				c = c -32; 
		}
		aux[0].first = shopName; 
		smallLists.push_back(aux); 
	}
	
	// Rest of the items 
	vector<string>::iterator it; // Finding the product 
	vector<string>::iterator itproduct; // The found product 
	for (it=shopping.begin(); it!=shopping.end(); ++it) {
		itproduct = find(products.begin(), products.end(), *it);
		if (itproduct == products.end()) { // Not in database
			// Add to every small list
			for (int i=0; i<shops.size(); i++) {
				pair<string,double> item; 
				item.first = *it; 
				item.second = 0; // By default the price is 0
				smallLists[i].push_back(item); 
			}
		} else { // In database 
			// Add to the shops with the lowest price
			int index = distance(products.begin(), itproduct);
			vector<int> cheapest = findCheapest(prices[index]); 
			for (int i=0; i<cheapest.size(); ++i) {
				pair<string,double> item; 
				item.first = *it; 
				item.second = prices[index][cheapest[i]];
				smallLists[cheapest[i]].push_back(item);
			}
		}
	}
	
	// Writting of the files for every shop
	ofstream shoptxt; 
	for (int i = 0; i < shops.size(); i++) {
		shoptxt.open(shops[i] + ".txt"); 
		for (int j = 0; j < smallLists[i].size(); j++) {
			shoptxt << smallLists[i][j].first << " "
			        << smallLists[i][j].second << endl; 
		}
		shoptxt.close(); 
	}
	
}

vector<int> Database::findCheapest(vector<double> v) {
	vector<int> result;
	int i = 0; 
	while (v[i] == -1) i++; 
	double cheapest = v[i]; 
	while(i<(v.size())) {
		if ((v[i]<cheapest) && (v[i]!=-1))
			cheapest=v[i];
		i++; 
	} 
	for (int i=0; i<v.size(); i++)
		if ((v[i]==cheapest) && (v[i]!=-1)) 
			result.push_back(i); 
	return result; 
}
