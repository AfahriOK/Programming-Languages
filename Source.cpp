#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>//Reads and outputs from file

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

//Clears the screen
void clearScreen() {
	cout << "\033[2J\033[1;1H";
 }

//Prints the menu
void printMenu() {
	string strings[] = { "Display All Item Counts", "Display Specific Item Count", "Display Item Histogram", "Exit Program" };

	cout << string(40, '*') << endl;

	for (unsigned int s = 1; s <= size(strings); ++s) {
		cout << "* " << s << " - " << strings[s - 1] << string(40 - (size(strings[s - 1]) + 7), ' ') << '*' << endl;
	}

	cout << string(40, '*') << endl;
}

void main()
{
	bool keepGoing = true; //Bool to keep program running
	int userChoice = 0; //Holds menu choice
	string userItem = "none"; //Holds item name
	ifstream inFS; //Reads from file
	string item; //Holds current item in file
	string frequency; //Holds frequency of item
	int frequencyInt = 0; //Holds frequency int form

	while (keepGoing) {
		clearScreen();
		printMenu();

		//Enter menu choice and throw error if invalid
		cout << "Enter your choice (1-4)" << endl;
		try {
			cin >> userChoice;
			if (!cin || (userChoice < 1 || userChoice > 4)) {
				throw runtime_error("Invalid Choice");
			}
		}
		catch (runtime_error& excpt) {
			cin.clear();
			cin.ignore();
			cout << excpt.what() << endl;
			cout << "Enter any key to continue..." << endl;
			cin >> userChoice;
			cin.clear();
			cin.ignore();
			continue;
		}
		switch (userChoice) {
		case 1:
			CallProcedure("readItems");
			cout << "Enter any key to continue..." << endl;
			cin >> userItem;
			cin.clear();
			cin.ignore();
			break;

		case 2:
			cout << "Enter an item" << endl;
			cin >> userItem;
			//If input is invalid, ask again
			while (!cin) {
				cout << "Please enter a valid item" << endl;
				cin.clear();
				cin.ignore();
				cin >> userItem;
			}
			cout << callIntFunc("findItem", userItem) << endl;
			cout << "Enter any key to continue..." << endl;
			cin >> userItem;
			cin.clear();
			cin.ignore();
			break;

		case 3:
			CallProcedure("writeFrequency");
			cout << "Opening file 'frequency.dat'" << endl;
			inFS.open("frequency.dat");
			if (!inFS.is_open()) {
				cout << "Could not open file" << endl;
				break;
			}
			//Get data and output histogram
			while (!inFS.fail()) {
				inFS >> item;
				cout << item << " ";
				inFS >> frequency;
				frequencyInt = stoi(frequency);
				cout << string(frequencyInt, '*') << endl;
			}

			//Output error if file not finished
			if (!inFS.eof()) {
				cout << "Error reading file" << endl;
			}
			
			
			cout << "Closing file 'frequency.dat'" << endl;
			inFS.close();
			cout << "Enter any key to continue..." << endl;
			cin >> userItem;
			cin.clear();
			cin.ignore();
			break;

		case 4:
			keepGoing = false;
			break;
		}
	}
}