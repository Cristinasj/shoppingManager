#include <vector>
#include <string>

class Database {
private:
	const std::string data = "data.txt"; 
	std::vector<std::string> shops; 
	std::vector<std::string> products; 
	std::vector<std::vector<double>> prices; 
	

public: 
	/** 
	 * Reads the data to fill in the private atributes
	 * If filename does not exist it gets created empty 
	 */ 
	Database(std::string filename); 

	/**
	 * Creates a txt for each of the shops on the working directory. 
	 * 
	 * Structure: 
	 * NAME OF THE SHOP 
	 * item1
	 * item2
	 * item3
	 * ...
	 * 
	 * In case of a draw, the item gets added to the one of draw
	 * In case of a miss in the database, it's added to all 
	 */ 
	void createLists(std::string shoppingList); 
	
private: 
	/**
	 * @brief Returns a list with the indexes of the smallest 
	 */
	std::vector<int> findCheapest(std::vector<double>); 
};
