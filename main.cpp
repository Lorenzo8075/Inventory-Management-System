#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <iomanip>
using namespace std;

class InventoryItem {
    protected:
        int item_id;
        bool restocking;

    public:
        static const int DEFAULT_ITEM_ID;
        static const bool DEFAULT_RESTOCKING;

        InventoryItem();
        InventoryItem(int item_id, bool restocking);
        ~InventoryItem();
        
        int get_item_id() const;
        void set_item_id(int item_id);
        bool get_restocking()const;
        void set_restocking(bool restocking);

        void Display();
        
};
const int InventoryItem::DEFAULT_ITEM_ID = 9999;
const bool InventoryItem::DEFAULT_RESTOCKING = false;

class Product : public InventoryItem {
    private:
        string name;
        int quantity;
        double price;
    public:
        static const string DEFAULT_NAME;
        static const int DEFAULT_QUANTITY;
        static const double DEFAULT_PRICE;

        string get_name()const;
        void set_name(string name);
        int get_quantity()const;
        void set_quantity(int quantity);
        double get_price()const;
        void set_price(double price);

        Product();
        Product(int item_id, bool restocking, string name, int quantity, double price);
        ~Product();

        void Display();
        double Cost(int quantity, double price, int &quantity_remaining);
        
};
const string Product::DEFAULT_NAME = "No Product";
const int Product::DEFAULT_QUANTITY = 0;
const double Product::DEFAULT_PRICE = 0.99;

class InventorySystem {
    public:
        static const int DEFAULT_ARRAY_SIZE;
        static const string DEFAULT_STORE_NAME;
        static const int DEFAULT_PRODUCT_COUNT;
        static const string INPUT_FILE;
        static const string OUTPUT_FILE;

    private:
        string store_name;
        static const int kSize = 512;
        InventoryItem * product_list[kSize];
        int product_count;
        InventoryItem* FindInventoryItem(int item_id);

    public:

        string get_store_name()const;
        void set_store_name(string store_name);
        int get_product_count()const;
        void set_product_count(int product_count);

        InventorySystem();
        InventorySystem(string store_name);
        ~InventorySystem();
        void BuildInventory();
        void ShowInventory();
        void UpdateInventory();
        void Terminate();
};

const int InventorySystem::DEFAULT_ARRAY_SIZE = 512;
const string InventorySystem::DEFAULT_STORE_NAME = "My store";
const int InventorySystem::DEFAULT_PRODUCT_COUNT = 0;
const string InventorySystem::INPUT_FILE = "product_list.txt";
const string InventorySystem::OUTPUT_FILE = "output_file.txt";

int main(){

InventorySystem * inventory_system= new InventorySystem("my store");
inventory_system->BuildInventory();
inventory_system->ShowInventory();
inventory_system->UpdateInventory();
inventory_system->Terminate();
delete inventory_system;

    return 0;
}
 //default constructor
InventoryItem::InventoryItem():item_id(InventoryItem::DEFAULT_ITEM_ID), restocking(InventoryItem::DEFAULT_RESTOCKING){}
//2 arg constructor
InventoryItem::InventoryItem(int item_id, bool restocking):item_id(item_id), restocking(restocking){}
//destructor
InventoryItem::~InventoryItem(){ cout << "InventoryItem " << item_id << " with " << restocking << " destroyed...\n";};
//item id accessor
int InventoryItem::get_item_id() const{ return item_id;};
//item id mutator
void InventoryItem::set_item_id(int item_id){this->item_id = item_id;};
//restocking accessor
bool InventoryItem::get_restocking()const{ return restocking;};
//restocking mutator
void InventoryItem::set_restocking(bool restocking){this->restocking = restocking;};
//Display function
void InventoryItem::Display(){

    if(item_id >= 1000){
        cout << item_id << ';' << boolalpha << restocking << ';';
    }
    else if(item_id >= 100){
        cout << "0" << item_id << ';' << boolalpha << restocking << ';';
    }  
    else if(item_id >= 10){
        cout << "00" << item_id << ';' << boolalpha << restocking << ';';
    } 
    else{
        cout << "00" << item_id << ';' << boolalpha << restocking << ';';
    }     
}

//name accessor
string Product::get_name()const{ return name;};
//name setter
void Product::set_name(string name){ this->name = name;};
//quantity accessor
int Product::get_quantity()const{ return quantity;};
//quantity setter
void Product::set_quantity(int quantity){this->quantity = quantity;};
//price accessor
double Product::get_price()const{ return price;};
//price setter
void Product::set_price(double price){this->price = price;};
//Product Default Constructor
Product::Product(): InventoryItem(),name(Product::DEFAULT_NAME),
quantity(Product::DEFAULT_QUANTITY), price(Product::DEFAULT_PRICE){};
//5 args Product constructor
Product::Product(int item_id, bool restocking, string name, int quantity, double price): 
InventoryItem(item_id, restocking),name(name),quantity(quantity), price(price){};
//Product Destructor
Product::~Product(){cout << "Product: " << item_id << " Name " << name << " quantity " << quantity << " price " << price <<
" restocking " << restocking << " destroyed...\n";};
//Product Display Function
void Product::Product::Display(){
    InventoryItem::Display();
    
    if(restocking && (restocking == true)){
        cout << name << ";"  << quantity << ";" << price << " ******************" << endl;
    }
    
    else{
        cout << name << ";" << quantity << ";" << price << endl;
    }
    
}
double Product::Product::Cost(int quantity, double price, int &quantity_remaining){
    
    bool true_restocking = true;
    quantity_remaining = quantity_remaining - quantity;
    if(quantity_remaining <= 0){
        set_restocking(true_restocking);
    }
    set_quantity(quantity_remaining);
    return price * quantity;
}

string InventorySystem::get_store_name()const{return store_name;};
void InventorySystem::set_store_name(string store_name){this->store_name = store_name;};
int InventorySystem::get_product_count()const{return product_count;};
void InventorySystem::set_product_count(int product_count){this->product_count = product_count;};

//default constructor
InventorySystem::InventorySystem():store_name(InventorySystem::DEFAULT_STORE_NAME), 
product_count(InventorySystem::DEFAULT_PRODUCT_COUNT){
    for ( int i = 0; i < kSize; i++) {
       product_list[i] = nullptr;
    }
}
//1 arg constructor
InventorySystem::InventorySystem(string store_name):store_name(store_name){
     for ( int i = 0; i < kSize; i++) {
       product_list[i] = nullptr;
    }
}
//destructor
InventorySystem::~InventorySystem(){
    Product* p_product = nullptr;
    for ( int i = 0; i < product_count;  i++) {
       p_product = static_cast<Product*>(product_list[i]);
       delete p_product;
    }
}

InventoryItem* InventorySystem::FindInventoryItem(int item_id){
  
    for(int i = 0; i < product_count; i++){
        if((product_list[i]->get_item_id()) == item_id){
            return product_list[i];
        } 
    }
    return nullptr;
};

void InventorySystem::BuildInventory(){

   ifstream fin(INPUT_FILE);
   int item_id, quantity;
   double price;
   string name;
   bool restocking;
   string buffer, restocking_value;
    
   product_count = 0;
    
    if(!fin){
        cout <<"ERROR: Failed to open input file\n";   
    }

    else{
        cout << endl;
        while(getline(fin, buffer, ';')){
            istringstream(buffer) >> item_id;
            getline(fin, buffer, ';');
            restocking_value = buffer;
            if(restocking_value == "false"){restocking = false;}
            else{restocking = true;}
            getline(fin, buffer, ';');
            name = buffer;
            getline(fin, buffer, ';');
            istringstream(buffer) >> quantity;
            getline(fin, buffer, '\n');
            istringstream(buffer) >> price;
        
            product_list[product_count] = new Product(item_id, restocking, name,quantity, price);
           
            product_count++;
            
            
        } //while loop

    }// else

    fin.close();
}

void InventorySystem::ShowInventory(){
    Product* p_product = nullptr;

    for(int i = 0; i < product_count; i++){
        if(product_list[i] != nullptr){
            p_product = static_cast<Product*>(product_list[i]);
            cout << fixed << showpoint << setprecision(2);
            p_product->Display();
        }    
    }
}

void InventorySystem::UpdateInventory(){
    int item_id, quantity;
    double price;
    int quantity_remaining;
    string user_input;

    do{
        cout << "\nPlease enter item id and quantity: " << endl;
        cin >> item_id >> quantity;

    InventoryItem* p_find_item = FindInventoryItem(item_id);
    Product* p_product = static_cast<Product*>(p_find_item);

    if(p_find_item != nullptr){
        quantity_remaining = p_product->get_quantity();
        if(quantity <= quantity_remaining){
            price = p_product->get_price();
            cout << fixed << showpoint << setprecision(2);
            cout << "Total cost is: $" << p_product->Cost(quantity, price, quantity_remaining) << endl;
        }
        else{
            cout << "The amount of products requested is sold out or not available." << endl;
        }
    }

    else{
        cout << "Item id not found!" << endl;
        }
    
    cout << "Would you like to make another purchase? " << endl;
    cin >> user_input;
    cin.ignore();
      
    }
    while(user_input == "yes" || user_input == "Yes");
    
}
void InventorySystem::Terminate(){
    ofstream write_file;
    write_file.open(OUTPUT_FILE);
    Product* p_product = nullptr;
    string line;
    int i = 0;

    if(!write_file){
        cout << "ERROR: Failed to open output file.\n" << endl;
        exit(-1);
    }
    while (i < product_count) {
         
         p_product = static_cast<Product*>(product_list[i]);
         write_file << p_product->get_item_id() << ";";
         write_file << boolalpha << p_product->get_restocking() << ";";
         write_file << p_product->get_name() << ";";
         write_file << p_product->get_quantity() << ";";
         write_file << p_product->get_price() << ";" << endl;
         i++;  
      } 
    write_file.close();
}    
