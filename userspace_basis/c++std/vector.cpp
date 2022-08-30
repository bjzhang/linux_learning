
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	vector<int> array;
	int count = 10;

	for (int i = 0; i < 10; i++) {
		array.push_back(i);
		cout << "current size: " << array.size() << endl;
	}

	cout << "The first method to loop" << endl;
	for (int i = 0; i < 10; i++) {
		cout << i  << ": " << array[i] << endl;
	}

	cout << "The second method to loop" << endl;
	for (auto i: array) {
		cout << i  << ": " << array[i] << endl;
	}
	cout << "Output value through * for the first element" << endl;
	cout << *(array.begin()) << endl;

	return 0;
}
