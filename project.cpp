#include <iostream>
#include <algorithm>
#include <vector>
#include <thread>
#include <chrono>
#include <time.h>
using namespace std;
using namespace chrono;
using namespace this_thread;

//--------------------GUI Functions--------------------
void hide_password(string const &ques, string const &ans){
    cout << "\033[F";
    cout << "\r";
    cout << ques;
    for(int i=0; i<ans.size(); i++){
        cout << "*";
    }
    cout << endl;
}

//----Invalid input handling----
inline void invalid1(){
    string s1 = "Invalid Input";
    for(int i=0; i<s1.size(); i++){
        cout.flush();
        cout << s1[i];
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    sleep_for(milliseconds(1500));
    cout.flush();
    cout << "\r";
    for(int i=0; i<s1.size(); i++){
        cout << " ";
        cout.flush();
        sleep_for(milliseconds(10));
    }
    cout << "\r";
}

inline void invalid2(string const &s1){
    for(int i=0; i<s1.size(); i++){
        cout.flush();
        cout << s1[i];
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    sleep_for(milliseconds(1500));
    cout.flush();
    cout << "\r";
    for(int i=0; i<s1.size(); i++){
        cout << " ";
        cout.flush();
        sleep_for(milliseconds(10));
    }
    cout << "\r";
}

//----For invalid input after a tab----
inline void tab_invalid(string const &s1){
    cout << "\t";
    for(int i=0; i<s1.size(); i++){
        cout.flush();
        cout << s1[i];
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    sleep_for(milliseconds(1500));
    cout.flush();
    cout << "\r";
    for(int i=0; i<s1.size()+8; i++){
        cout << " ";
        cout.flush();
        sleep_for(milliseconds(10));
    }
    cout << "\r";
}

inline void tab_invalid_fast(string const &s1){
    cout << "\t";
    for(int i=0; i<s1.size(); i++){
        cout.flush();
        cout << s1[i];
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(5));
    }
    sleep_for(milliseconds(2000));
    cout.flush();
    cout << "\r";
    for(int i=0; i<s1.size()+8; i++){
        cout << " ";
        cout.flush();
        sleep_for(milliseconds(5));
    }
    cout << "\r";
}

//----For loading effects----
inline void load1(){
    cout.flush();
    cout << "Loading";
    for(int i=0; i<4; i++){
        cout << ".";
        cout.flush();
        sleep_for(milliseconds(1000));
    }
    cout << "\r";
    
    //Load faded erase-
    for(int i=0; i<13; i++){
        cout << " ";
        cout.flush();
        sleep_for(milliseconds(5));
    }
    cout << "\r";
    cout.flush();
}

inline void load2(){
    cout.flush();
    cout << "Searching";
    for(int i=0; i<4; i++){
        cout << ".";
        cout.flush();
        sleep_for(milliseconds(1000));
    }
    cout << "\r";
    
    //Load faded erase-
    for(int i=0; i<15; i++){
        cout << " ";
        cout.flush();
        sleep_for(milliseconds(5));
    }
    cout << "\r";
    cout.flush();
}

inline void load3(string const &str){
    for(int i=0; i<str.length(); i++){
        cout << str.at(i);
        cout.flush();
        sleep_for(milliseconds(100));
    }
}

//----For erasing text on console----
inline void erase1(){
    //Instant Erase
    cout << "\r";
    cout.flush();
    for(int i=0; i<100; i++){
        cout << " ";
        // cout.flush();
        // sleep_for(milliseconds(0));
    }
    cout << "\r";
}

inline void erase2(){
    //Faded Erase
    cout << "\r";
    cout.flush();
    for(int i=0; i<100; i++){
        cout << " ";
        cout.flush();
        sleep_for(milliseconds(10));
    }
    cout << "\r";
}

inline void erase3(){
    //Fast Faded Erase
    cout << "\r";
    cout.flush();
    for(int i=0; i<100; i++){
        cout << " ";
        cout.flush();
        sleep_for(milliseconds(5));
    }
    cout << "\r";
}

//--------------------Main Project--------------------
//Forward Declaration of classes
class Heap; 
class Electronics;
class Item;
class Account;

//Base item class
class Item{
protected:
  string name;
  float rating;
  double price;

public:
  Item(){
    name = "";
    price = 0;
    rating = 0;
  }
  Item(string name, double price, float rating){
    this->name = name;
    this->price = price;
    this->rating = rating;
  }
  
  void display(){
    cout << "Name of the item- " << name << "\t";
    cout << "Price- " << price << "\t";
    cout << "Rating- " << rating << "\t";
    cout << endl;
  }
  string getName(){
    return name;
  }
  double getPrice(){
    return price;
  }
  float getRating(){
    return rating;
  }
  
  friend class Heap;
};

//Order node for implementing stack and queues-
class Order{
public:
    Item item;
    string date;
    Order* next;
    Order(Item &item){
        this->item = item;
        time_t timestamp = time(NULL) + 5*3600 + 30*60;
        date = ctime(&timestamp);
        next = NULL;
    }
};

//Stack to maintain history of orders
class Stack{
private:
    Order* head;
    int count;

public:
    Stack(){
        count = 0;
        head = NULL;
    }
    
    void push(Item &item){
        Order* node = new Order(item);
        node->next = head;
        head = node;
        count++;
    }
    
    void display(){
        cout << "*************************************************************************";
        cout << endl;
    
        cout << "\t\t\t\t\t\t\t\t\t*";
        cout << "\r*";
        cout << "\t\t\t";
        cout << "Your Transaction History";
        cout << endl;
    
        cout << "\t\t\t\t\t\t\t\t\t*";
        cout << "\r\t\t\t\t\t\t      Ordered Date"; 
        cout << "\r\t\t\t\t  Price Paid"; 
        cout << "\r*\t  ";
        cout << "List of Items";
        cout << endl;
        
        Order* temp = head;
        while(temp != NULL){
            cout << "\t\t\t\t\t\t\t\t\t*";
            cout << "\r\t\t\t\t\t       " << temp->date;
            cout << "\033[F";
            cout << "\r\t\t\t\t    " << temp->item.getPrice();
            cout << "\r* ";
            cout << temp->item.getName();
            temp = temp->next;
            cout << endl;
        }
            
        cout << "*************************************************************************";
        cout << endl;
    
    }
    int size(){
        return count;
    }
    friend class hash_map;
};

//Queue for maintaining all the orders that are placed
class Queue{
private:
    Order* head;
    Order* tail;
    int count;

public:
    Queue(){
        count = 0;
        head = tail = NULL;
    }
    
    void push(Item &item){
        Order* node = new Order(item);
        if(head == NULL){
            head = tail = node;
        }
        else{
            tail->next = node;
            tail = node;
        }
        count++;
    }
    
    void display(){
        cout << "*************************************************************************";
        cout << endl;
    
        cout << "\t\t\t\t\t\t\t\t\t*";
        cout << "\r*";
        cout << "\t\t\t      ";
        cout << "Your Orders";
        cout << endl;
    
        cout << "\t\t\t\t\t\t\t\t\t*";
        cout << "\r\t\t\t\t\t\t      Ordered Date"; 
        cout << "\r\t\t\t\t  Price Paid"; 
        cout << "\r*\t  ";
        cout << "List of Items";
        cout << endl;
        
        Order* temp = head;
        while(temp != NULL){
            cout << "\t\t\t\t\t\t\t\t\t*";
            cout << "\r\t\t\t\t\t       " << temp->date;
            cout << "\033[F";
            cout << "\r\t\t\t\t    " << temp->item.getPrice();
            cout << "\r* ";
            cout << temp->item.getName();
            temp = temp->next;
            cout << endl;
        }
            
        cout << "*************************************************************************";
        cout << endl;
    
    }
    int size(){
        return count;
    }
    friend class hash_map;
};

//Tree node for implementing cart-
class Node{
public:
    Item item;
    int height;
    Node* left;
    Node* right;
    
    Node(Item &item){
        this->item = item;
        left = right = NULL;
        height = 1;
    }
};

//AVL Tree for managing cart
class AVLTree{
private:
    Node* root;
    int count;
    
    void inorder(Node* root, vector<Item> &vec){
        if(root == NULL) return;
        
        inorder(root->left, vec);
        vec.push_back(root->item);
        inorder(root->right, vec);
    }
    void update_height(Node* root){
        if(root == NULL) return;
        int l=0, r=0;
        if(root->left) l = root->left->height;
        if(root->right) r = root->right->height;
        root->height = 1 + max(l,r);
    }
    bool isBalanced(Node* root, int &ans){
        if(!root) return true;
        int l, r;
        l = r = 0;
        if(root->left) l = root->left->height;
        if(root->right) r = root->right->height;
        ans = l-r;
        if(ans > 1) return false;
        if(ans < -1) return false;
        return true;
    }
    Node* find_left(Node* root){
        if(root->left == NULL){
            return root;
        }
        Node* ans = find_left(root->left);
        return ans;
    }
    Node* left_rotate(Node* root){
        if(root->right == NULL) return root;
        Node* A = root;
        Node* B = A->right;
        Node* C = B->right;
    
        Node* temp = B->left;
        B->left = A;
        A->right = temp;
        
        update_height(A);
        update_height(B);
        return B;
    }
    Node* right_rotate(Node* root){
        if(root->left == NULL) return root;
        Node* A = root;
        Node* B = A->left;
        Node* C = B->left;
    
        Node* temp = B->right;
        B->right = A;
        A->left = temp;
        update_height(A);
        update_height(B);
        return B;
    }
    
public:
    AVLTree(){
        count = 0;
        root = NULL;
    }
    
    Node* insert_helper(Node* root, Item &item){
        //Normal input:-
        if(root == NULL){
            Node* N = new Node(item);
            root = N;
            count++;
            return root;
        }
        else if(item.getName() > root->item.getName()){
            root->right = insert_helper(root->right, item);
        }
        else {
            root->left = insert_helper(root->left, item);
        }
        update_height(root);
        //After normal input, this recursive function will backtrack
    
        int diff = 0;
        if(isBalanced(root, diff)){
            return root;
        }
    
        if(diff > 1){  
            if(root->left->item.getName() > item.getName()){    //LL
                root = right_rotate(root);
            }
            else{   //LR
                root->left = left_rotate(root->left);
                root = right_rotate(root);
            }
        }   
        else{         
            if(root->right->item.getName() < item.getName()){   //RR
                root = left_rotate(root);
            }
            else{   //RL
                root->right = right_rotate(root->right);
                root = left_rotate(root);
            }
        }
        return root;
    }
    
    void insert(Item &item){
        root = insert_helper(root, item);
    }
    
    Node* remove_helper(Node* root, Item &item){
        if(root == NULL){
            return root;
        }
    
        if (item.getName() < root->item.getName()) {
            root->left = remove_helper(root->left, item);  
        } 
        else if (item.getName() > root->item.getName()) {
            root->right = remove_helper(root->right, item);  
        } 
        else {
            if (root->left == NULL && root->right == NULL) {  // No children
                delete root;
                return NULL;
            } else if (root->left == NULL) {  // Only right child
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == NULL) {  // Only left child
                Node* temp = root->left;
                delete root;
                return temp;
            } else {  // Two children case
                Node* successor = find_left(root->right);  
                root->item = successor->item;  
                root->right = remove_helper(root->right, successor->item);  
            }
        }
        update_height(root);
    
        int diff = 0;
        if(isBalanced(root, diff)){
            return root;
        }
        if (diff > 1) {
            int left_diff = 0;
            if (isBalanced(root->left, left_diff) && left_diff >= 0) {
                return right_rotate(root);  // LL case
            } else {
                root->left = left_rotate(root->left);  // LR case
                return right_rotate(root);
            }
        }
        
        if (diff < -1) {
            int right_diff = 0;
            if (isBalanced(root->right, right_diff) && right_diff <= 0) {
                return left_rotate(root);  // RR case
            } else {
                root->right = right_rotate(root->right);  // RL case
                return left_rotate(root);
            }
        }
        return root;
    }
    
    void remove(Item &item){
        root = remove_helper(root, item);
    }
    
    //Function declaration. Will be defined after account class.
    void display(Account &acc);
    
    friend class hash_map;
};

//Customers account that manages all customers requirement
class Account{
private:
    string name;
    string username;
    string password;
    string address;
    
    Stack history;
    Queue orders;
    AVLTree cart;
    
public:
    Account(){
        name = "";
        username = "";
        password = "";
        address = "";
    }
    Account(string name, string username, string password, string address){
        this->name = name;
        this->username = username;
        this->password = password;
        this->address = address;
    }
    
    void display(){
        cout << name << " ";
        cout << username << " ";
        cout << password << " ";
        cout << address << " ";
        cout << endl;
    }
    
    void place_order(Item &item){
        history.push(item);
        orders.push(item);
    }
    void add_to_cart(Item &item){
        cart.insert(item);
    }
    
    //Important functions for displaying cart, orders and history
    void display_cart(){
        Account &acc = *this;
        cart.display(acc);
    }
    void display_order_history(){
        history.display();
    }
    void display_orders(){
        orders.display();
    }
    
    string getName() const{
        return this->name;
    }
    string getUsername() const{
        return this->username;
    }
    string getPassword() const{
        return this->password;
    }
    friend class hash_map;
};

void AVLTree::display(Account &acc){
megaLabel:
    cout << endl;
    cout << "*****************************************************************";
    cout << endl;

    cout << "\t\t\t\t\t\t\t\t*";
    cout << "\r*";
    cout << "\t\t\t    ";
    cout << "Your Cart";
    cout << endl;

    cout << "\t\t\t\t\t\t\t\t*";
    cout << "\r\t\t\t\t\t\t      Ratings"; 
    cout << "\r\t\t\t\t\tPrice"; 
    cout << "\r*\t";
    cout << "List of Items";
    cout << endl;

    vector<Item> vec;
    inorder(root, vec);
    int x = 1;
    double sum = 0;
    for(int i=0; i<vec.size(); i++, x++){
        cout << "\t\t\t\t\t\t\t\t*";
        cout << "\r\t\t\t\t\t\t\t" << vec[i].getRating();
        cout << "\r\t\t\t\t\t" << vec[i].getPrice();
        sum += vec[i].getPrice();
        cout << "\r* ";
        cout << vec[i].getName();
        cout <<"(" << x << ")";
        cout << endl;
    }
    
    cout << "\t\t\t\t\t\t\t\t*";
    cout << "\r\t\t      Order Total- " << "₹" << sum;
    cout << "\r*";
    
    cout << endl;
    cout << "*****************************************************************";
    cout << endl;
    
    int ch = 1;
    cout << endl;
    cout << "Enter 0 to go back/stop. " << endl;
    cout << "Enter " << x << " for Order Total" << endl;
    
    loop1:
        cout << endl;
        cout << "Enter the item number to order or delete(1 to " << x-1 << ")- ";
        cin >> ch;
        if (ch == 0) return;
        if(ch > x){
            cout << "\033[F";
            erase1();
            invalid1();
            goto loop1;
        }
        else if(ch == x){
            for(int i=0; i<vec.size(); i++){
                acc.place_order(vec[i]);
                remove(vec[i]);
            }
            cout << "\tThank you for purchasing" << endl;
            goto megaLabel;
        }
        
        cout << "\t";
        vec[ch-1].display();
        int ch2;
        cout << "\t1- Order Now" << endl;;
        cout << "\t2- Delete item" << endl;
        
        loop2:
        cout << "\tYour input- ";
        cin >> ch2;
        if(ch2 <=0 || ch2 > 3){
            cout << "\033[F";
            erase1();
            cout << "\t";
            invalid1();
            erase1();
            goto loop2;
        }
        if(ch2 == 1){
            acc.place_order(vec[ch-1]);
            remove(vec[ch-1]);
            cout << "\tThank you for purchasing" << endl;
            goto megaLabel;
        }
        else if(ch2 == 2){
            remove(vec[ch-1]);
            cout << "\tItem deleted sucessfully" << endl;
            goto megaLabel;
        }
}

//Class of Max Heap which is resposible for maintaining priority queue
class Heap{
private:

    static void down_heapify_rating(vector<Item> &arr, int n){
        int it = 0;
        bool heapified = false;
        while(it < n && heapified == false){
    
            int lci = 2*it + 1;      //Left child index
            int rci = 2*it + 2;      //Right child index
            if(lci >= n && rci >= n)
                break;
    
            Item lc;
            Item rc;
            if(lci < n) lc = arr[lci];
            if(rci < n) rc = arr[rci];
    
            int idx = it;
            Item current = arr[it];
            if(current.rating < lc.rating) {
                current = lc;
                idx = lci;
            }
            if(current.rating < rc.rating){
                current = rc;
                idx = rci;
            }
            if(it == idx) heapified = true;
            swap(arr[it], arr[idx]);
            it = idx;
        }
    }
    static void down_heapify_price(vector<Item> &arr, int n){
        int it = 0;
        bool heapified = false;
        while(it < n && heapified == false){
    
            int lci = 2*it + 1;      //Left child index
            int rci = 2*it + 2;      //Right child index
            if(lci >= n && rci >= n)
                break;
    
            Item lc;
            Item rc;
            if(lci < n) lc = arr[lci];
            if(rci < n) rc = arr[rci];
    
            int idx = it;
            Item current = arr[it];
            if(current.price < lc.price) {
                current = lc;
                idx = lci;
            }
            if(current.price < rc.price){
                current = rc;
                idx = rci;
            }
            if(it == idx) heapified = true;
            swap(arr[it], arr[idx]);
            it = idx;
        }
    }
    static void up_heapify_rating(vector<Item> &arr, int n){
        int idx = n-1;
        int parent = (idx-1)/2;
        while(parent > 0){
            if(arr[idx].rating > arr[parent].rating){
                swap(arr[idx], arr[parent]);
            }
            idx = parent;
            parent = (idx-1)/2;
        }
        if(arr[idx].rating > arr[parent].rating){
            swap(arr[idx], arr[parent]);
        }
    }
    static void up_heapify_price(vector<Item> &arr, int n){
        int idx = n-1;
        int parent = (idx-1)/2;
        while(parent > 0){
            if(arr[idx].price > arr[parent].price){
                swap(arr[idx], arr[parent]);
            }
            idx = parent;
            parent = (idx-1)/2;
        }
        if(arr[idx].price > arr[parent].price){
            swap(arr[idx], arr[parent]);
        }
    }
  
public:
    static void create_heap_rating(vector<Item> &arr){
        int n = arr.size();
        for(int i=2; i<= n; i++){
          up_heapify_rating(arr, i);
        }
    }
  
    static void create_heap_price(vector<Item> &arr){
        int n = arr.size();
        for(int i=2; i<= n; i++){
          up_heapify_price(arr, i);
        }
    }
  
    static vector<Item> heap_sort_rating(vector<Item> &arr){
        vector<Item> temp = arr;
        int size = temp.size();
        while(size >= 1){
            swap(temp[0], temp[size-1]);
            size--;
            down_heapify_rating(temp, size);
        }
        return temp;
    }
  
    static vector<Item> heap_sort_price(vector<Item> &arr){
        vector<Item> temp = arr;
        int size = temp.size();
        while(size >= 1){
            swap(temp[0], temp[size-1]);
            size--;
            down_heapify_price(temp, size);
        }
        return temp;
    }
};

//--Different types of items are represented by each of the following 6 classes--
class MobilePhones{
private:
    vector<Item> phones;
  
public:
    MobilePhones(){}
  
    void insertData(){
        phones.push_back(Item("Apple iPhone 16", 79900, 4.5));
        phones.push_back(Item("Apple iPhone 16 Plus", 89900, 4.1));
        phones.push_back(Item("Apple iPhone 16 Pro", 119900, 3.6));
        phones.push_back(Item("Apple iPhone 16 Pro Max", 144900, 4.1));
        phones.push_back(Item("Samsung Galaxy S23", 59999, 4.4));
        phones.push_back(Item("Samsung Galaxy S23 Ultra", 75999, 4.5));
        phones.push_back(Item("Samsung Galaxy Z Flip5", 100999, 4.3));
        phones.push_back(Item("Samsung Galaxy Z Fold5", 125999, 4.1));
        phones.push_back(Item("Redmi 13", 12499, 3.9));
        phones.push_back(Item("Redmi 13 Pro", 22999, 4.0));
        phones.push_back(Item("Redmi 13 Pro Plus", 27999, 3.8));
    }
    void display(){
        for(int i=0; i<phones.size(); i++){
          phones[i].display();
        }
    }
  
    void filter_price(){
        Heap::create_heap_price(phones);
        phones = Heap::heap_sort_price(phones);
    }
    void filter_rating(){
        Heap::create_heap_rating(phones);
        phones = Heap::heap_sort_rating(phones);
    }
  
    int size(){
        return phones.size();
    }
    friend class Electronics;
};

class Laptops{
private:
    vector<Item> laptops;
  
public:
    Laptops(){}
  
    void insertData(){
        laptops.push_back(Item("Apple MacBook", 100999, 4.1));
        laptops.push_back(Item("Apple MacBook Air 13'", 122990, 4.5));
        laptops.push_back(Item("Apple MacBook Pro 13'", 173990, 4.5));
        laptops.push_back(Item("Apple MacBook Pro 16'", 369990, 3.8));
        laptops.push_back(Item("Apple MacBook", 100999, 4.1));
        laptops.push_back(Item("ASUS VivoBook 15", 31990, 4.1));
        laptops.push_back(Item("ASUS VivoBook 16", 50990, 4.5));
        laptops.push_back(Item("ASUS TUF ", 60990, 4.0));
        laptops.push_back(Item("Lenovo IdeaPad 5", 70990, 4.2));
        laptops.push_back(Item("Lenovo IdeaPad Pro 5", 104790, 4.6));
        laptops.push_back(Item("Dell G15", 69990, 4.0));
        laptops.push_back(Item("HP 15", 56990, 3.7));
    }
  
    void filter_price(){
        Heap::create_heap_price(laptops);
        laptops = Heap::heap_sort_price(laptops);
    }
    
    void filter_rating(){
        Heap::create_heap_rating(laptops);
        laptops = Heap::heap_sort_rating(laptops);
    }
  
    void display(){
        for(int i=0; i<laptops.size(); i++){
          laptops[i].display();
        }
    }
    int size(){
        return laptops.size();
    }
    
    friend class Electronics;
};


class SmartWatches{
private:
    vector<Item> watches;
  
public:
    SmartWatches(){}
  
    void insertData(){          
        watches.push_back(Item("Fire-Boltt Ninja Call Pro", 4599, 4.0));
        watches.push_back(Item("Fire-Boltt Ninja Call Pro Max", 5399, 4.2));
        watches.push_back(Item("Titan Smart 3", 4995, 3.7));
        watches.push_back(Item("Noise Twist", 3899, 4.1));
        watches.push_back(Item("Noise Pulse", 4499, 4.0));
        watches.push_back(Item("Apple Watch 10", 49900, 4.4));
        watches.push_back(Item("Apple Watch 10 Ultra", 59900, 4.0));
        watches.push_back(Item("Samsung Galaxy Watch 7", 28990, 3.7));
        watches.push_back(Item("Samsung Galaxy Watch 7 Ultra", 47900, 4.3));
    }
  
    void filter_price(){
        Heap::create_heap_price(watches);
        watches = Heap::heap_sort_price(watches);
    }
    
    void filter_rating(){
        Heap::create_heap_rating(watches);
        watches = Heap::heap_sort_rating(watches);
    }
  
    void display(){
        for(int i=0; i<watches.size(); i++){
            watches[i].display();
        }
    }
    int size(){
        return watches.size();
    }
    
    friend class Electronics;
};

class TopWear{
private:
    vector<Item> clothes;
  
public:
    TopWear(){}
  
    void insertData(){         
        clothes.push_back(Item("Jockey Round Neck T-shirt", 579, 3.7));
        clothes.push_back(Item("Jockey Collar Neck T-shirt", 999, 4.2));
        clothes.push_back(Item("US POLO ASSN Crew Neck", 594, 3.8));
        clothes.push_back(Item("Allen Solly Regular Polo", 1099, 4.2));
        clothes.push_back(Item("Allen Solly Slim Fit Shirt", 2199, 3.9));
        clothes.push_back(Item("Allen Solly Blue Denim", 2589, 4.4));
        clothes.push_back(Item("Van Heusen Polo T-Shirt", 1099, 4.5));
        clothes.push_back(Item("Van Heusen Slim Fit Shirt", 1990, 3.7));
        clothes.push_back(Item("Van Heusen Navy Blue Denim", 2900, 4.1));
    }
  
    void filter_price(){
        Heap::create_heap_price(clothes);
        clothes = Heap::heap_sort_price(clothes);
    }
    void filter_rating(){
        Heap::create_heap_rating(clothes);
        clothes = Heap::heap_sort_rating(clothes);
    }
  
    void display(){
        for(int i=0; i<clothes.size(); i++){
            clothes[i].display();
        }
    }
    int size(){
        return clothes.size();
    }
    friend class Fashion;
};

class BottomWear{
private:
    vector<Item> clothes;
  
public:
    BottomWear(){}
  
    void insertData(){         
        clothes.push_back(Item("Louis Philippe Slim Fit Pant", 1479, 4.0));
        clothes.push_back(Item("Louis Philippe Boardroom Pant", 1999, 3.9));
        clothes.push_back(Item("Peter England Slim Fit Pant", 1594, 3.7));
        clothes.push_back(Item("Levi's Casual Pant", 1599, 4.5));
        clothes.push_back(Item("Levi's Cargo Pant", 2499, 4.6));
        clothes.push_back(Item("Levi's Casual Skinny Jeans", 1589, 4.2));
        clothes.push_back(Item("Allen Solly Jeans", 1689, 4.0));
        clothes.push_back(Item("Allen Solly Slim Jeans", 1990, 3.7));
        clothes.push_back(Item("Allen Solly Cargo Pant", 2199, 4.1));
        clothes.push_back(Item("Arrow Slim Pant", 1899, 4.4));
    }
  
    void filter_price(){
        Heap::create_heap_price(clothes);
        clothes = Heap::heap_sort_price(clothes);
    }
    void filter_rating(){
        Heap::create_heap_rating(clothes);
        clothes = Heap::heap_sort_rating(clothes);
    }
  
    void display(){
        for(int i=0; i<clothes.size(); i++){
            clothes[i].display();
        }
    }
    int size(){
        return clothes.size();
    }
    friend class Fashion;
};

class Accessories{
private:
    vector<Item> gadgets;
  
public:
    Accessories(){}
  
    void insertData(){         
        gadgets.push_back(Item("Titan Timeless Watch", 4799, 4.5));
        gadgets.push_back(Item("Titan Metropolian Watch", 6999, 4.4));
        gadgets.push_back(Item("Fastrack Analog Watch", 2599, 3.7));
        gadgets.push_back(Item("Fastrack Caual Watch", 2199, 3.5));
        gadgets.push_back(Item("Fastrack Automatic Watch", 8999, 4.0));
        gadgets.push_back(Item("Levi's Sunglasses", 999, 4.3));
        gadgets.push_back(Item("Levi's Metal Buckle Belt", 890, 4.2));
    }
  
    void filter_price(){
        Heap::create_heap_price(gadgets);
        gadgets = Heap::heap_sort_price(gadgets);
    }
    void filter_rating(){
        Heap::create_heap_rating(gadgets);
        gadgets = Heap::heap_sort_rating(gadgets);
    }
  
    void display(){
        for(int i=0; i<gadgets.size(); i++){
            gadgets[i].display();
        }
    }
    int size(){
        return gadgets.size();
    }
    friend class Fashion;
};

//Mart of Electronics-
class Electronics{
private:
    MobilePhones phones;
    Laptops laptops;
    SmartWatches watches;
    int total_items;
  
public:
    Electronics(){
        total_items = 0;
    }
    
    void insertData(){
        phones.insertData();
        laptops.insertData();
        watches.insertData();
        total_items = phones.size() + laptops.size() + watches.size();
    }
    
    void filter_rating(MobilePhones &mp, Laptops &lt ,SmartWatches &sw){
        mp.filter_rating();
        lt.filter_rating();
        sw.filter_rating();
        reverse(mp.phones.begin(), mp.phones.end());
        reverse(lt.laptops.begin(), lt.laptops.end());
        reverse(sw.watches.begin(), sw.watches.end());
    }
    
    void filter_price(MobilePhones &mp, Laptops &lt ,SmartWatches &sw){
        mp.filter_price();
        lt.filter_price();
        sw.filter_price();
    }
  
    Item getItem(int id, MobilePhones &mp, Laptops &lt ,SmartWatches &sw){
        if(id <= mp.size()){
            return mp.phones[id-1];
        }
        id = id - phones.size();
        if(id <= lt.size()){
            return lt.laptops[id-1];
        }
        id = id - laptops.size();
        if(id <= sw.size()){
            return sw.watches[id-1];
        }
        return Item();
    }
    
    void show_mart(Account &acc){
        MobilePhones ph = phones;
        Laptops lt = laptops;
        SmartWatches sw = watches;
        int ch;
        
        cout << "1- No filters";
        cout << "\t";
        cout << "2- Price Filter";
        cout << "\t";
        cout << "3- Ratings Filter";
        cout << endl;
        
        loop1:
        cout << "Your input- ";
        cin >> ch;
        if(ch <=0 || ch >4){
            cout << "\033[F";
            erase1();
            invalid1();
            goto loop1;
        }
        
        if(ch == 2) this->filter_price(ph, lt, sw);
        else if(ch == 3) this->filter_rating(ph, lt, sw);
        
        int x=1;
        cout << endl;
        cout << "*****************************************************************";
        cout << endl;
    
        cout << "\t\t\t\t\t\t\t\t*";
        cout << "\r*";
        cout << "\t\t\t";
        cout << "Electronics Mart";
        cout << endl;
    
        cout << "\t\t\t\t\t\t\t\t*";
        cout << "\r\t\t\t\t\t\t      Ratings"; 
        cout << "\r\t\t\t\t\t  Price"; 
        cout << "\r* ";
        cout << "Mobile Phones";
        cout << endl;
    
        for(int i=0; i<ph.size(); i++, x++){
            cout << "\t\t\t\t\t\t\t\t*";
            cout << "\r\t\t\t\t\t\t\t" << ph.phones[i].getRating();
            cout << "\r\t\t\t\t\t  " << ph.phones[i].getPrice();
            cout << "\r*\t";
            cout << ph.phones[i].getName();
            cout <<"(" << x << ")";
            cout << endl;
        }
        
        cout << "\t\t\t\t\t\t\t\t*";
        cout << "\r* ";
        cout << "Laptops";
        cout << endl;
    
        for(int i=0; i<lt.size(); i++, x++){
            cout << "\t\t\t\t\t\t\t\t*";
            cout << "\r\t\t\t\t\t\t\t" << lt.laptops[i].getRating();
            cout << "\r\t\t\t\t\t  " << lt.laptops[i].getPrice();
            cout << "\r*\t";
            cout << lt.laptops[i].getName();
            cout <<"(" << x << ")";
            cout << endl;
        }  
        
        cout << "\t\t\t\t\t\t\t\t*";
        cout << "\r* ";
        cout << "Smart Watches";
        cout << endl;
    
        for(int i=0; i<sw.size(); i++, x++){
            cout << "\t\t\t\t\t\t\t\t*";
            cout << "\r\t\t\t\t\t\t\t" << sw.watches[i].getRating();
            cout << "\r\t\t\t\t\t  " << sw.watches[i].getPrice();
            cout << "\r*\t";
            cout << sw.watches[i].getName();
            cout <<"(" << x << ")";
            cout << endl;
        }
        
        cout << "*****************************************************************";
        cout << endl;
        
        //If user does not log in with an account
        if(acc.getUsername() == ""){
            cout << "Login with an account to buy products" << endl;
            return;
        }
        
        ch = 1;
        while(ch){
            cout << endl;
            cout << "Enter the item number to view details(0 to stop/back)- ";
            cin >> ch;
            if (ch == 0) break;
            if(ch >= x){
                cout << "\033[F";
                erase1();
                invalid1();
                continue;
            }
            
            cout << "\t";
            Item item = getItem(ch, ph, lt, sw);
            item.display();
            int ch2;
            cout << "\t1- Add to cart" << endl;
            cout << "\t2- Buy Now" << endl;
            
            loop2:
            cout << "\tYour input- ";
            cin >> ch2;
            if(ch2 <=0 || ch2 >2){
                cout << "\033[F";
                erase1();
                cout << "\t";
                invalid1();
                erase1();
                goto loop2;
            }
            if(ch2 == 1){
                acc.add_to_cart(item);
                cout << "\tItem added to cart successfully" << endl;
            }
            else {
                acc.place_order(item);
                cout << "\tThank you for purchasing" << endl;
            }
        }
    }
};

//Mart of fashion
class Fashion{
private:
    TopWear tops;
    BottomWear pants;
    Accessories access;
    int total_items;

public:
    Fashion(){
        total_items = 0;
    }
    
    void insertData(){
        tops.insertData();
        pants.insertData();
        access.insertData();
        total_items = tops.size() + pants.size() + access.size();
    }
    
    void filter_rating(TopWear &tw, BottomWear &bw ,Accessories &ass){
        tw.filter_rating();
        bw.filter_rating();
        ass.filter_rating();
        reverse(tw.clothes.begin(), tw.clothes.end());
        reverse(bw.clothes.begin(), bw.clothes.end());
        reverse(ass.gadgets.begin(), ass.gadgets.end());
    }
    
    void filter_price(TopWear &tw, BottomWear &bw ,Accessories &ass){
        tw.filter_rating();
        bw.filter_rating();
        ass.filter_rating();
    }
  
    Item getItem(int id, TopWear &tw, BottomWear &bw ,Accessories &ass){
        if(id <= tw.size()){
            return tw.clothes[id-1];
        }
        id = id - tw.size();
        if(id <= bw.size()){
            return bw.clothes[id-1];
        }
        id = id - bw.size();
        if(id <= ass.size()){
            return ass.gadgets[id-1];
        }
        return Item();
    }
    
    void show_mart(Account &acc){
        TopWear tw = tops;
        BottomWear bw = pants;
        Accessories ass = access;
        int ch;
        
        cout << "1- No filters";
        cout << "\t";
        cout << "2- Price Filter";
        cout << "\t";
        cout << "3- Ratings Filter";
        cout << endl;
        
        loop1:
        cout << "Your input- ";
        cin >> ch;
        if(ch <=0 || ch >4){
            cout << "\033[F";
            erase1();
            invalid1();
            goto loop1;
        }
        
        if(ch == 2) this->filter_price(tw, bw, ass);
        else if(ch == 3) this->filter_rating(tw, bw, ass);
        
        int x=1;
        cout << endl;
        cout << "*****************************************************************";
        cout << endl;
    
        cout << "\t\t\t\t\t\t\t\t*";
        cout << "\r*";
        cout << "\t\t\t";
        cout << "Fashion and Lifestyle";
        cout << endl;
    
        cout << "\t\t\t\t\t\t\t\t*";
        cout << "\r\t\t\t\t\t\t      Ratings"; 
        cout << "\r\t\t\t\t\t  Price"; 
        cout << "\r* ";
        cout << "Top Wear";
        cout << endl;
    
        for(int i=0; i<tw.size(); i++, x++){
            cout << "\t\t\t\t\t\t\t\t*";
            cout << "\r\t\t\t\t\t\t\t" << tw.clothes[i].getRating();
            cout << "\r\t\t\t\t\t  " << tw.clothes[i].getPrice();
            cout << "\r*\t";
            cout << tw.clothes[i].getName();
            cout <<"(" << x << ")";
            cout << endl;
        }
        
        cout << "\t\t\t\t\t\t\t\t*";
        cout << "\r* ";
        cout << "Bottom Wear";
        cout << endl;
    
        for(int i=0; i<bw.size(); i++, x++){
            cout << "\t\t\t\t\t\t\t\t*";
            cout << "\r\t\t\t\t\t\t\t" << bw.clothes[i].getRating();
            cout << "\r\t\t\t\t\t  " << bw.clothes[i].getPrice();
            cout << "\r*\t";
            cout << bw.clothes[i].getName();
            cout <<"(" << x << ")";
            cout << endl;
        }  
        
        cout << "\t\t\t\t\t\t\t\t*";
        cout << "\r* ";
        cout << "Accessories";
        cout << endl;
    
        for(int i=0; i<ass.size(); i++, x++){
            cout << "\t\t\t\t\t\t\t\t*";
            cout << "\r\t\t\t\t\t\t\t" << ass.gadgets[i].getRating();
            cout << "\r\t\t\t\t\t  " << ass.gadgets[i].getPrice();
            cout << "\r*\t";
            cout << ass.gadgets[i].getName();
            cout <<"(" << x << ")";
            cout << endl;
        }    
        cout << "*****************************************************************";
        cout << endl;
        
        //If user does not log in with an account
        if(acc.getUsername() == ""){
            cout << "Login with an account to buy products" << endl;
            return;
        }
        
        ch = 1;
        while(ch){
            cout << endl;
            cout << "Enter the item number to view details(0 to stop/back)- ";
            cin >> ch;
            if (ch == 0) break;
            if(ch >= x){
                cout << "\033[F";
                erase1();
                invalid1();
                continue;
            }
            
            cout << "\t";
            Item item = getItem(ch, tw, bw, ass);
            item.display();
            int ch2;
            cout << "\t1- Add to cart" << endl;
            cout << "\t2- Buy Now" << endl;
            
            loop2:
            cout << "\tYour input- ";
            cin >> ch2;
            if(ch2 <=0 || ch2 > 2){
                cout << "\033[F";
                erase1();
                cout << "\t";
                invalid1();
                erase1();
                goto loop2;
            }
            if(ch2 == 1){
                acc.add_to_cart(item);
                cout << "\tItem added to cart successfully" << endl;
            }
            else {
                acc.place_order(item);
                cout << "\tThank you for purchasing" << endl;
            }
        }
    }
};

//Linked List Node for implementing Hashmap
class acc_node{
public:
    string key;
    Account value;
    acc_node* next;

    acc_node(){
        next = NULL;
    }
    acc_node(string key, Account &value){
        this->key = key;
        this->value = value;
        next = NULL;
    }
};

//Hash Map for quickly accessing user details-
class hash_map{
private:
    acc_node** arr;
    int size;
    int count;
    
    int ascii(string str){
        int ans = 0;
        for(int i=0; i<str.size(); i++){
            ans = ans + int(str[i]);
        }
        return ans;
    }
    
    bool strength_check(string const &pass){
        bool number = false;
        bool special = false;
        if(pass.length() < 6){
            return false;
        }
        for(int i=0; i<pass.size(); i++){
            if(number && special)
                return true;
            
            if(pass[i] >= 48 && pass[i] <= 57){
                number = true;
            }
            else if((pass[i] >= 65 && pass[i] <= 90) || (pass[i] >= 97 && pass[i] <= 122) == false){
                special = true;
            }
        }
        if(number && special) return true;
        else return false;
    }
    
    void rehash(){
        int s = 2*size;
        acc_node** temp = new acc_node*[s];
        for(int i=0; i<s; i++){
            temp[i] = NULL;
        }
        
        for(int i=0; i<size; i++){
            acc_node* it = arr[i];
            while(it != NULL){
                int idx = ascii(it->key);
                idx = idx % s;
                if(temp[idx] == NULL){
                    temp[idx] = new acc_node(it->key, it->value);
                }
                else{
                    acc_node* n = new acc_node(it->key, it->value);
                    n->next = temp[idx];
                    temp[idx] = n;
                }
                it = it->next;
            }
        }
        size *=2;
        delete[] arr;
        arr = temp;
    }
    
public:
    hash_map(){
        size = 10;
        count = 0;
        arr = new acc_node*[size];
        for(int i=0; i<size; i++){
            arr[i] = NULL;
        }
    }
    
    void insertData(){
        Account acc1("ARYAN DUBEY", "aryan_dubey", "aryan#123", "Bhopal MP");
        Account acc2("ANSH AERON", "ansh_aeron", "ansh#123", "Saranpur UP");
        Account acc3("ARJUN GUPTA", "arjun_gupta", "beti#123", "Greater Noida UP");
        
        this->insert("aryan_dubey", acc1);
        this->insert("ansh_aeron", acc2);
        this->insert("arjun_gupta", acc3);
    }
    
    void insert(string key, Account &acc){
        if(float(count)/float(size) >= 0.7){
            rehash();
        }
        int idx = ascii(key);
        idx = idx%size;
        
        if(arr[idx] == NULL){
            arr[idx] = new acc_node(key, acc);
        }
        else{
            acc_node* temp = new acc_node(key, acc);
            temp->next = arr[idx];
            arr[idx] = temp;
        }
        count++;
    }
    
    void remove(string key){
        int idx = ascii(key);
        idx = idx % size;
        if(arr[idx] == NULL){
            return;
        }
        else if(arr[idx]->key == key){
            acc_node* del = arr[idx];
            arr[idx] = arr[idx]->next;
            del->next = NULL;
            delete del;
            return;
        }
        acc_node* it = arr[idx]->next;
        acc_node* prev = arr[idx];
        while(it != NULL){
            if(it->key == key){
                prev->next = it->next;
                it->next = NULL;
                delete it;
            }
            prev = it;
            it = it->next;
        }
    }
    
    bool validate_username(string key){
        int idx = ascii(key);
        idx = idx%size;
        
        if(arr[idx] == NULL){
            return true;
        }
        
        acc_node* it = arr[idx];
        while(it != NULL){
            if(it->key == key){
                return false;
            }
            it = it->next;
        }
        return true;
    }
    
    acc_node* validate(string username, string password){
        int idx = ascii(username);
        idx = idx%size;
        
        if(arr[idx] == NULL){
            return NULL;
        }
        
        acc_node* it = arr[idx];
        while(it != NULL){
            if(it->key == username && it->value.getPassword() == password){
                return it;
            }
            it = it->next;
        }
        return NULL;
    }
    
    void print(){
        for(int i=0; i<size; i++){
            acc_node* it = arr[i];
            while(it != NULL){
                cout << it->key << " ";
                it->value.display(); 
                
                it = it->next;
            }
        }
    }
    int capacity(){
        return count;
    }
    
    ~hash_map(){
        for(int i=0; i<size; i++){
            acc_node* it = arr[i];
            acc_node* ahead = it;
            if(ahead) ahead = arr[i]->next;
            while(ahead != NULL){
                delete it;
                it = ahead;
                ahead = ahead->next;
            }
            delete it;
        }
        delete[] arr;
    }
    
    // Important functions for sign up and login
    Account login(){
        string user, pass;
    
        cout << "Press 0 to go back" << endl;
        loop:
        cout << "\tEnter username- ";
        cin >> user;
        if(user == "0"){
            cout << "\033[F";
            erase1();
            cout << "\033[F";
            erase1();
            return Account();
        }
    
        cout << "\tEnter password- ";
        cin >> pass;
        acc_node* acc = validate(user, pass);
        if(acc){
            hide_password("\tEnter password- ", pass);
            load2();
            cout << endl;
            cout << "Hello " << acc->value.getName() << endl;
            return acc->value;
        }
        else {
            cout << "\033[F";
            erase1();
            cout << "\033[F";
            erase1();
            tab_invalid("Invalid Username or Password");
            goto loop;
        }
    }
    
    Account sign_up(){
        string user, pass, name, address;
        
        cout << "Enter your details to sign up- " << endl;
        cout << "\tEnter name- ";
        cin >> ws;
        getline(cin,name);
        cout << "\tEnter address- ";
        cin >> ws;
        getline(cin, address);
        
        loop1:
        cout << "\tEnter username- ";
        cin >> user;
        if(validate_username(user) == false){
            cout << "\033[F";
            erase1();
            tab_invalid("Username already taken");
            goto loop1;
        }
        
        loop2:
        cout << "\tEnter password- ";
        cin >> pass;
        if(strength_check(pass) == false){
            cout << "\033[F";
            erase1();
            if(pass.length() < 6){
                tab_invalid_fast("Password too short. Should be greater than 5 characters.");
            }
            else{
                tab_invalid_fast("Password should at least have 1 number and 1 special character");
            }
            goto loop2;
        }
        
        hide_password("\tEnter password- ", pass);
        load1();
        
        Account acc(name, user, pass, address);
        insert(user, acc);
        acc_node* node = validate(user, pass);
        
        cout << endl;
        cout << "Hello " << node->value.getName() << endl;
        return acc;
    }
    
    void re_insert(Account &acc){
        string key = acc.getUsername();
        int idx = ascii(key);
        idx = idx%size;
        
        if(arr[idx]->value.getUsername() == key){
            arr[idx]->value.cart = acc.cart;
            arr[idx]->value.history = acc.history;
            //arr[idx]->value.orders = acc.orders;
        }
        
        acc_node* it = arr[idx];
        while(it != NULL){
            if(it->key == key){
                it->value.cart = acc.cart;
                it->value.history = acc.history;
                //it->value.orders = acc.orders;
            }
            it = it->next;
        }
    }
};

//--------------------Main Function--------------------
int main(){
    hash_map customers;
    Electronics electronics;
    Fashion fashion;
    Account acc;
    
    customers.insertData();
    electronics.insertData();
    fashion.insertData();
    
    cout << "\t\t\t\t\t\t\t";
    string s1 = "WELCOME TO THE SHOPPING MART";
    for(int i=0; i<s1.length(); i++){
        cout << s1.at(i);
        cout.flush();
        sleep_for(milliseconds(100));
    }
    cout << "\n\t\t\t\t\t\t\t";
    for(int i=0; i<s1.size(); i++){
        cout << "▔";
    }
    cout << endl;
    
header:
    cout << "How do you wish to proceed?" << endl;
    cout << "1- Log In";
    cout << "\t";
    cout << "2- New Customer? Sign Up";
    cout << "\t";
    cout << "3- View Mart";
    cout << "\t";
    cout << endl;
    
    label1:
    int choice1;
    cout << "Your Input- ";
    cin >> choice1;
    
    if(choice1 <= 0 || choice1 > 3){
        cout << "\033[F";
        erase1();
        invalid1();
        goto label1;
    }
    cout << endl;
    
    
    if(choice1 == 1){
        acc = customers.login();
        if(acc.getUsername() == ""){
            goto header;
        }
        goto main_menu;
    }
    
    else if(choice1 == 2){
        acc = customers.sign_up();
        goto main_menu;
    }
    
    else if(choice1 == 3){
    menu:
        cout << "What category do you wish to Explore?";
        cout << endl;
        cout << "1- Techzone";
        cout << "\t";
        cout << "2- Fashion & Accessories";
        cout << "\t";
        cout << "3- Back to Home Page";
        cout << endl;
        
        int choice4;
    label4:
        cout << "Your Input- ";
        cin >> choice4;
            
        if(choice4 <= 0 || choice4 > 3){
            cout << "\033[F";
            erase1();
            invalid1();
            goto label4;
        }
        cout << endl;
        
        if(choice4 == 1){
            electronics.show_mart(acc);
            cout << endl;
            goto menu;
        }
        
        else if(choice4 == 2){
            fashion.show_mart(acc);
            cout << endl;
            goto menu;
        }
        
        else if(choice4 == 3){
            load1();
            goto header;
        }
    }
    
main_menu:      
    cout << endl;
    cout << "What category do you wish to Explore?";
    cout << endl;
    cout << "1- Techzone";
    cout << "\t";
    cout << "2- Fashion & Accessories";
    cout << "\t";
    cout << "3- Account Settings";
    cout << "\t";
    cout << "4- Log Out";
    cout << "\t";
    cout << "5- Exit";
    cout << "\t";
    cout << endl;
    
    int choice2;
label2:
    cout << "Your Input- ";
    cin >> choice2;
    
    if(choice2 <= 0 || choice2 > 5){
        cout << "\033[F";
        erase1();
        invalid1();
        goto label2;
    }
    cout << endl;
    
    if(choice2 == 1){
        electronics.show_mart(acc);
        acc.display_cart();
        cout << endl;
        acc.display_orders();
        cout << endl;
        goto main_menu;
    }
    
    else if(choice2 == 2){
        fashion.show_mart(acc);
        acc.display_cart();
        cout << endl;
        acc.display_orders();
        cout << endl;
        goto main_menu;
    }

    else if(choice2 == 3){
settings:
        cout << "Select the desired options";
        cout << endl;
        cout << "1- View Orders";
        cout << "\t";
        cout << "2- View Cart";
        cout << "\t";
        cout << "3- View Transaction History";
        cout << "\t";
        cout << "4- Back to Main Menu";
        cout << endl;
        
        int choice3;
label3:
        cout << "Your Input- ";
        cin >> choice3;
        
        if(choice3 <= 0 || choice3 > 4){
            cout << "\033[F";
            erase1();
            invalid1();
            goto label3;
        }
        cout << endl;
        
        if(choice3 == 1){
            acc.display_orders();
            cout << endl;
            goto settings;
        }
        
        else if(choice3 == 2){
            acc.display_cart();
            cout << endl;
            goto settings;
        }
        
        else if(choice3 == 3){
            acc.display_order_history();
            cout << endl;
            goto settings;
        }
        
        else if(choice3 == 4){
            load1();
            goto main_menu;
        }
    }
    
    else if(choice2 == 4){
        load1();
        customers.re_insert(acc);
        acc = Account();
        goto header;
    }
    
    else if(choice2 == 5){
        cout << "THANK YOU FOR VISITING....!! VISIT AGAIN AND BUY MORE :)";
        cout << endl;
        return 0;
    }
}
