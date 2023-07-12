#include <iostream>
using namespace std;

template <typename T>								//structure for creating linked list
struct node {
	T data;
	node<T>* next, * prev;							//prev pointer for connecting to previous node
};

template <typename T>
class list {										//class list defination
	node<T>* head, * it;							//head as head pointer, it as iterator, n as no. of elements
	int n;
public:
	list() {									//constructor
		head = it =  NULL;
		n = 0;
	}
	~list() {									//destructor
		makeempty();
	}
	list(const list<T>& u) {					//copy constructor
		head = it = NULL;
		n = 0;
		operator=(u);
	}
	void operator = (const list<T>& u) {			// = operator overloading
		makeempty();
		node<T>* temp;								//copying data in new list
		temp = u.head;
		while (temp != NULL) {						//using while loop and temporary pointer
			insert(temp->data);
			temp = temp->next;
		}
	}
	void insert(const T& val) {						//function for inserting data
		node<T>* temp;
		temp = new node<T>;							//creating new memory
		temp->data = val;							//storing data in data part
		temp->prev = NULL;							//making prev NULL
		if (head == NULL) {							//checking for empty list
			temp->next = NULL;						//making next NULL
			head = temp;							//storing new node in head
		}
		else {										//if head not NULL
			temp->next = head;						//connecting new node to head
			head->prev = temp;						//connecting head's previous part to new node
			head = temp;							//assigning new node to head
		}
		n++;
	}
	bool find(const T& val) {						//function for finding data
		if (empty()) {								//checking for empty list
			throw "List is empty!\n";
		}
		node<T>* temp;								//finding data using while loop
		temp = head;								//and temporary pointer
		while (temp != NULL) {						//and if
			if (val == temp->data) {				//data found
				return true;						//returning true
			}	
			temp = temp->next;						//else moving temp forward
		}
		return false;
	}
	bool update(const T& oldval, const T& newval) {				//function for updating data
		if (empty()) {
			throw "List is empty!\n";
		}
		if (erase(oldval)) {						//if old value erased
			insert(newval);							//then inserting new value
			return true;							//and returning true
		}
		else {
			return false;							//else false
		}
	}
	bool erase(const T& val) {						//function for erasing data
		if (empty()) {
			throw "List is empty!\n";
		}
		node<T>* temp, * del;						//temporary pointers for erasing data
		it = NULL;
		temp = head;								//pointing temp to head
		if (temp->data == val) {					//if data in head is required data
			head = head->next;						//then moving head forward
			head->prev = NULL;						//and deleting that node
			delete temp;							//using temp 
			n--;
			return true;
		}
		while (temp->next != NULL) {				//if head does not contain required data
			if (temp->next->data == val) {			//then checking data from second node
				del = temp->next;					//and if data found then deleting it using del
				temp->next = del->next;
				if (del->next != NULL) {			//checking for last node
					del->next->prev = del->prev;
				}
				delete del;
				n--;
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
	bool empty() {						//function for checking whether list is empty or not
		return head == NULL;
	}
	bool full() {						//function for checking whether list is full or not
		node<T>* temp;					//checking with the help of temporary memory
		temp = new node<T>;
		if (temp == NULL) {				//if not allocated
			return true;
		}
		else {							//if allocated
			delete temp;
			return false;
		}
	}
	void makeempty() {					//function for making list empty
		if (!empty()) {					//deleting nodes
			it = NULL;					//one by one
			node<T>* temp;				//with the help of
			while (!empty()) {			//temp and while loop
				temp = head;			//until the list is empty
				head = head->next;
				if (head != NULL) {
					head->prev = NULL;
				}
				delete temp;
			}
			n = 0;
		}
	}
	void reset() {						//iterator function for resetting list
		it = head;
	}
	bool is_last() {					//iterator function for checking last element
		return it == NULL;
	}
	T get_next() {						//iterator function for getting next element in list
		if (is_last()) {
			throw "Last element has been reached!\n";
		}
		T val = it->data;
		it = it->next;
		return val;
	}
	int lenght() {						//length of list
		return n;
	}
	void display() {					//displaying list
		node<T>* temp;
		temp = head;						//displaying data
		while (temp->next != NULL) {		//starting from last node
			temp = temp->next;
		}
		while (temp != NULL) {				//in order to display it in the sequence it was inserted
			cout << temp->data << "	";		// (used prev pointer)
			temp = temp->prev;
		}
		cout << endl;
	}
};

/////////////		CLIENT CODE			///////////	

int main()
{
	list<int> u;
	u.insert(1); u.insert(6); u.insert(3); u.insert(5); u.insert(4);	//inserted 5 integers in list
	u.display();														//displaying list
	if (u.find(3)) {													//searching for 3
		cout << "Value found!\n";
	}
	else {
		cout << "Value not found!\n";
	}
	if (u.update(3,9)) {												//updating 3 with 9
		cout << "Value updated!\n";
	}
	else {
		cout << "Value not found!\n";
	}
	u.display();
	cout << "Length of list is: " << u.lenght() << " Values\n";				//getting length of list
	if (u.erase(6)) {														//removing 6
		cout << "Value deleted!\n";
	}
	else {
		cout << "Value not found!\n";
	}
	u.display();

	// below is the code for displaying data using iterators
	/*u.reset();
	while (!u.is_last()) {
		cout << u.get_next() << "	";
	}
	cout << endl;*/
	cout << "Length of list is: " << u.lenght() << " Values\n";
	return 0;
}