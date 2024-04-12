#include <iostream>
#include <ctime>
#define koef 2 

using namespace std;

struct Diploma {
	Diploma() {
		specialty = 'A';
		year = 2000;
		benefit = '-';
	}

	Diploma(char aSpecialty, int aYear, char aBenefit) :
		specialty(aSpecialty),
		year(aYear),
		benefit(aBenefit) {}

	char specialty;
	int year;
	char benefit;
};

struct DynamicArray {
private:
	int length = 32;
	int current_size = 0;
	Diploma* diplomaArray = new Diploma[length];

public:

	void relocateMemmory() {
		length *= koef;
		Diploma* diplomaArray_Copy = new Diploma[length];
		for (int i = 0; i < (length) / 2; i++) {
			diplomaArray_Copy[i] = diplomaArray[i];
		}
		delete[] diplomaArray;
		diplomaArray = diplomaArray_Copy;
		return;
	}

	void push_back(Diploma* diploma) {
		if (length == 0) {
			length = 32;
			diplomaArray = new Diploma[length];
		}
		if (current_size >= length) {
			relocateMemmory();
		}
		diplomaArray[current_size] = *diploma;
		current_size++;
		return;
	}

	Diploma pop_back() {
		if (current_size <= 0) {
			cout << "Error: array is already empty!\n";
			return Diploma();
		}
		current_size--;
		return diplomaArray[current_size];
	}

	Diploma get(int n) {
		if (current_size == 0 || n > current_size || n < 0) {
			cout << "Error: index out of array!\n";
			return Diploma();
		}
		return diplomaArray[n];
	}

	int size() {
		return current_size;
	}

	void print() {
		if (current_size == 0 || length == 0) {
			cout << "Array is empty!\n";
			return;
		}

		int num = 0;
		cout << endl << "Printing all elements:" << endl;
		while (num < current_size) {
			cout << "[" << num + 1 << "] Speciality: " << diplomaArray[num].specialty << "; year: " << diplomaArray[num].year << "; benefit: " << diplomaArray[num].benefit << endl;
			num++;
		}
		return;
	}

	void clear() {
		delete[] diplomaArray;
		diplomaArray = nullptr;
		current_size = 0;
		length = 0;
		return;
	}

	void push_front(Diploma* diploma) {
		if (current_size == 0) {
			push_back(diploma);
			return;
		}
		if (current_size >= length) {
			relocateMemmory();
		}
		for (int i = current_size - 1; i >= 0; i--) {
			diplomaArray[i + 1] = diplomaArray[i];
		}
		diplomaArray[0] = *diploma;
		current_size++;
		return;
	}

	Diploma pop_front() {
		if (current_size == 0) {
			cout << "Error: array is empty!\n";
			return Diploma();
		}
		Diploma save = diplomaArray[0];
		for (int i = 0; i < current_size; i++) {
			diplomaArray[i] = diplomaArray[i + 1];
		}
		current_size--;
		return save;
	}

	void insert(Diploma* diploma, int position) {
		if (position <= 0) {
			cout << "Error: number is wrong!\n";
			return;
		}
		if (current_size < position) {
			push_back(diploma);
			return;
		}
		if (current_size >= length)
			relocateMemmory();

		for (int i = current_size; i >= position; i--) {
			diplomaArray[i - 1] = diplomaArray[i - 2];
		}
		diplomaArray[position - 1] = *diploma;
		current_size++;
		return;
	}

	void remove(int position) {
		if (position <= 0) {
			cout << "Error: number is wrong!\n";
			return;
		}
		if (current_size == 0) {
			cout << "Error: array is already empty!\n";
			return;
		}
		if (current_size < position) {
			pop_back();
			return;
		}
		for (int i = position - 1; i < current_size; i++) {
			diplomaArray[i] = diplomaArray[i + 1];
		}
		current_size--;
		return;
	}
};

struct Node {
	Diploma diploma;
	Node* next_node;
};

struct LinkedList {
private:
	Node* head = nullptr;
	Node* tail = nullptr;
public:
	void push_front(Diploma& diploma) {
		Node* newNode = new Node();
		newNode->diploma = diploma;
		newNode->next_node = head;
		head = newNode;

		if (!tail)
			tail = head;
		return;
	}

	void push_back(Diploma& diploma) {
		if (!head) {
			push_front(diploma);
			return;
		}

		Node* newNode = new Node();
		newNode->diploma = diploma;
		tail->next_node = newNode;
		tail = tail->next_node;

		return;
	}

	Diploma get(int n) {
		Node* getNode = head;
		int current = 0;
		if (!head) {
			cout << "Error: list is empty!\n";
			return Diploma();
		}
		if (n <= 0) {
			cout << "Error: number is out of range!\n";
			return Diploma();
		}
		while (current != n - 1) {
			getNode = getNode->next_node;
			if (!getNode) {
				cout << "Error: number is out of range!\n";
				return Diploma();
			}
			current++;
		}
		return getNode->diploma;
	}

	void pop_front() {
		if (!head) {
			cout << "Error: list is already empty!\n";
			return;
		}
		Node* save_head = head;
		head = head->next_node;
		delete save_head;
		if (!head)
			tail = nullptr;
		return;
	}

	void pop_back() {
		if (!head) {
			cout << "Error: list is already empty!\n";
			return;
		}
		Node* endNode = head;
		while (endNode->next_node != tail) {
			endNode = endNode->next_node;
		}
		delete endNode->next_node;
		tail = endNode;
		tail->next_node = nullptr;
		return;
	}

	int size() {
		Node* checkNode = head;
		int current_size = 0;
		while (checkNode) {
			checkNode = checkNode->next_node;
			current_size++;
		}
		return current_size;
	}

	void print() {
		Node* currentNode = head;
		if (!head) {
			cout << "List is empty!\n";
			return;
		}
		while (currentNode) {
			cout << "Speciality: " << currentNode->diploma.specialty << "; year: " << currentNode->diploma.year << "; benefit: " << currentNode->diploma.benefit << endl;
			currentNode = currentNode->next_node;
		}
		return;
	}

	void clear() {
		while (head) {
			pop_front();
		}		
		return;
	}

	void incert(Diploma diploma, int position) {
		if (position <= 0) {
			cout << "Error: number is wrong!";
			return;
		}
		if (!head || position == 1) {
			push_front(diploma);
			return;
		}
		Node* checkNode = head;
		for (int i = 1; i < position - 1; i++) {
			if (!checkNode->next_node) {
				push_back(diploma);
				return;
			}
			checkNode = checkNode->next_node;
		}
		Node* newNode = new Node();
		newNode->diploma = diploma;
		newNode->next_node = checkNode->next_node;
		checkNode->next_node = newNode;
		return;
	}

	void remove(int position) {
		Node* deleteNode = head;
		Node* link = nullptr;
		int counter = 0;

		if (position <= 0) {
			cout << "Error: number is wrong!\n";
			return;
		}
		if (!head || position == 1) {
			pop_front();
			return;
		}
		while (deleteNode) {
			if (counter == position) {
				link->next_node = deleteNode->next_node;
				delete deleteNode;
				break;
			}
			link = deleteNode;
			deleteNode = deleteNode->next_node;
			counter++;
		}
		return;
	}

};

int main()
{
	srand(time(NULL));
	LinkedList list;
	DynamicArray arr;
	Diploma dip1 = { 'a', 2000, 'e' };

	cout << "Dynamic Array:\n";

	clock_t startTime = clock();
	for (int i = 0; i < 50000; i++) {
		arr.push_back(&dip1);
	}
	clock_t endTime = clock();
	cout << "Test 1: " << double(endTime - startTime) / 1000 << " sec." << endl;

	startTime = clock();
	for (int i = 0; i < 10000; i++) {
		arr.push_front(&dip1);
	}
	endTime = clock();
	cout << "Test 2: " << double(endTime - startTime) / 1000 << " sec." << endl;

	startTime = clock();
	for (int i = 0; i < 20000; i++) {
		int j = rand() % 5000;
		arr.get(j);
	}
	endTime = clock();
	cout << "Test 3: " << double(endTime - startTime) / 1000 << " sec." << endl;

	startTime = clock();
	for (int i = 0; i < 5000; i++) {
		arr.pop_front();
	}
	endTime = clock();
	cout << "Test 4: " << double(endTime - startTime) / 1000 << " sec." << endl;

	startTime = clock();
	for (int i = 0; i < 5000; i++) {
		arr.pop_back();
	}
	endTime = clock();
	cout << "Test 5: " << double(endTime - startTime) / 1000 << " sec." << endl;


	arr.clear();
	startTime = clock();
	for (int i = 0; i < 50000; i++) {
		arr.push_back(&dip1);
	}
	for (int i = 0; i < 10000; i++) {
		arr.push_front(&dip1);
	}
	for (int i = 0; i < 20000; i++) {
		int j = rand();
		arr.get(j);
	}
	for (int i = 0; i < 5000; i++) {
		arr.pop_front();
	}
	for (int i = 0; i < 5000; i++) {
		arr.pop_back();
	}
	endTime = clock();
	cout << "Sum: " << double(endTime - startTime) / 1000 << " sec." << endl;

	////////////////////////
	cout << endl << "Linked list:";

	startTime = clock();
	for (int i = 0; i < 50000; i++) {
		list.push_back(dip1);
	}
	endTime = clock();
	cout << endl << "Test 1: " << double(endTime - startTime) / 1000 << " sec." << endl;

	startTime = clock();
	for (int i = 0; i < 10000; i++) {
		list.push_front(dip1);
	}
	endTime = clock();
	cout << "Test 2: " << double(endTime - startTime) / 1000 << " sec." << endl;

	startTime = clock();
	for (int i = 0; i < 20000; i++) {
		int j = rand();
		list.get(j);
	}
	endTime = clock();
	cout << "Test 3: " << double(endTime - startTime) / 1000 << " sec." << endl;

	startTime = clock();
	for (int i = 0; i < 5000; i++) {
		list.pop_front();
	}
	endTime = clock();
	cout << "Test 4: " << double(endTime - startTime) / 1000 << " sec." << endl;

	startTime = clock();
	for (int i = 0; i < 5000; i++) {
		list.pop_back();
	}
	endTime = clock();
	cout << "Test 5: " << double(endTime - startTime) / 1000 << " sec." << endl;

	list.clear();
	startTime = clock();
	for (int i = 0; i < 50000; i++) {
		list.push_back(dip1);
	}
	for (int i = 0; i < 10000; i++) {
		list.push_front(dip1);
	}
	for (int i = 0; i < 20000; i++) {
		int j = rand() % 5000 + 1;
		list.get(j);
	}
	for (int i = 0; i < 5000; i++) {
		list.pop_front();
	}
	for (int i = 0; i < 5000; i++) {
		list.pop_back();
	}
	endTime = clock();
	cout << "Sum: " << double(endTime - startTime) / 1000 << " sec." << endl;

	return 0;
}