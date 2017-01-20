#include <iostream>
#include <string>

using namespace std; 

class VPet {
	public: 
		VPet();
		VPet(string n, int w);
		void feed(int amount);
		void pet(); 
		void negative();
		void dead();
		
		double get_weight() const;
		int get_hunger() const;
		int get_love() const;
		string get_name() const;
		bool is_hungry() const;
		int get_life() const;
	private: 
		double weight;
		int hunger, love, life; 
		//amount of hunger, and love 
		string name; 
		bool hungry;		
};

//constructor
VPet::VPet() 
	: name(""), weight(100), hunger(0), love(0), hungry(false), life(0) {	
	
}
VPet::VPet(string n, int w) 
	: name(n), weight(w), hunger(0), love(0), hungry(false), life(0) {
}

//member funtions
void VPet::feed(int amount) {
	if (amount >= 0.5 * weight) {
		hungry = false;
		hunger--;
		love++;
		weight += 0.2 * amount;	
	}
	else  {
		hungry = true; 
		hunger++;
		love--;
		weight -= 0.2 * amount;	
	}		
	
	if (weight < 10) {
		love = 0;
	}
}
void VPet::pet() {
	love++;
}

void VPet::negative() {
	love--;
	hunger++;
}
void VPet::dead() {
	life = -1;
}


//return fuctions 
double VPet::get_weight() const {
	return weight;
}
int VPet::get_hunger() const {
	return hunger;
}
int VPet::get_love() const {
	return love;
}
string VPet::get_name() const {
	return name;
}
bool VPet::is_hungry() const {
	return hungry; 
}
int VPet::get_life() const {
	return life; 
}

//--------------------------------------------------

int main() {
	string name; int weight; 
	
	cout << "Welcome. Enter your pets name: ";
	getline(cin, name);
	
	cout << "and weight(in lbs): "; 
	cin >> weight; 
	
	VPet pet(name, weight);
	
	bool main = true;
	
	string input; int food;
	cout << "\n\nWhat do you want to do?\n(press 'h' for help)\n";
	while(main)
	{
		cin >> input;
		
		if (input == "h") {
			cout << "\n 'f' to feed your pet" 
				 << "\n 'p' to pet your pet"
				 << "\n 'n' to do nothing"
				 << "\n 't' to hit your pet"
				 << "\n 'x' to exit\n\n";
		}
		else if (input == "f") {
			cout << "How much food (# of grams)? ";
			cin >> food;
			pet.feed(food);
			
			if (pet.is_hungry())
				cout << "\nYour pet is hungry.\n";
			else 
				cout << "\n" << pet.get_name() << " has a full stomach.\n"; 
			
			if (pet.get_hunger() > 2)
				cout << "Your pet is starving!\n";
			else 
				cout << pet.get_name() << " liked their meal.\n";
		}
		else if (input == "p") {
			pet.pet();
		}
		else if (input == "n") {
			pet.negative();
		}
		else if (input == "t") {
			pet.negative();
			pet.negative();
			pet.negative();
			cout << pet.get_name() << " has been spanked.";
		}
		else if (input == "x") {
			main = false; 
			
		}
		else {
			pet.negative();
		}
		
		
		
		
		//Tells the player what is happening to their pet
		if (pet.get_love() < -2)
				cout << "\n" << pet.get_name() << " hates you.\n";
		else if (pet.get_love() >= -2 && pet.get_love() <= 2)
			cout << "\n" << pet.get_name() << " is content.\n";
		else if (pet.get_love() > 2)
			cout << "\n" << pet.get_name() << " is happy!\n";
			
		
		//Tells the player if their pet is over weight or under weight
		if (pet.get_weight() > weight * 1.5) 
			cout << "\n" << pet.get_name() << " is getting over weight.";
		else if (pet.get_weight() < weight * 0.2)
			cout << "\n" << pet.get_name() << " is under weight.";
		
		
		
		//Game ends if the owner mistreats their pet
		if (pet.get_hunger() > 5) {
			pet.dead();
			main = false;
		}
		else if (pet.get_love() < -5) {
			pet.dead();
			main = false; 
		}
		else if (pet.get_weight() > weight * 2) {
			pet.dead();
			main = false; 
		}
			
		//game also ends if the owner treats their pet properly	
		else if (pet.get_hunger() == -5) 
			main = false; 
		else if (pet.get_love() == 5)
			main = false; 
	}
	
	
	
	
	int total = pet.get_love() - pet.get_hunger();
	
	if (pet.get_life() != -1) {
		cout << "\nYou are a great owner!\n";
		if (pet.get_hunger() >= -5) 
			cout << pet.get_name() << " was well fed.\n";
		if (pet.get_love() >= 5)
			cout << pet.get_name() << " loved their owner very much.\n"; 
			
		cout << "Your score: " << total; 
		
	}
	else {
		cout << "\nYou're a terrible pet owner!\n";
		
		if (pet.get_hunger() > 5) 
			cout << pet.get_name() << " died of hunger.\n";
		else if (pet.get_love() < -5)
			cout << pet.get_name() << " ran away!\n";
		else if (pet.get_weight() > weight * 1.5)
			cout << pet.get_name() << " died of diabetes.\n";
			
		cout << "Your score: " << total;
	}
	return 0;
}


