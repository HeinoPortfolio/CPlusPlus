/*
 * Driver.cpp
 *
 *  Created on: Mar 17, 2020
 *      Author: Heino
 */

#include "Employee.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Functions Definitions.
void readFile(vector<Employee>& empVec);			// Read file for employee data
void calcPay (vector<Employee>& empVec);			// Calculate Pay
void displayVec(const vector<Employee>& empVec);  	//  Display all employee data
void sortEmployees(vector<Employee>& empVec);		// Sort by Employee ID
void sortByPay(vector<Employee>& empVec);			// Sort by Pay
void writeToFile(vector<Employee> empVec);			// Write the calculations to separate file
bool sortPay(const Employee& left, const Employee& right); // Sort by pay function
void readPay(vector<Employee>& empPayVec);			// Read pay file

int main()
{

	vector<Employee> empVec;
	vector<Employee> empPayVec;

	readFile(empVec);

	calcPay(empVec);

	sortEmployees(empVec);

	displayVec(empVec);

	writeToFile(empVec);

	sortByPay(empVec);

	cout << "2******************************************************" << endl;

	displayVec(empVec);

	cout << "3****************************************************" << endl;

	readPay(empPayVec);

	displayVec(empPayVec);


	return 0;

} // end main.

// Function Implementations.***************************************************
// *****************************************************************************
/* readFile()- read file that contains the data for the employee.
 *
 * Assumptions:  	The data file does not have the pay calculated.  It will only
 * 					contain four pieces of information.
 * Receives:		A vector of type Employee
 * Returns: 		A vector that has been populated with employee data.
 * Postcondition: 	The file has been successfully read and the vector has been
 * 					populated with employee data.
 *
 ********************************************************************************/
void readFile(vector<Employee>& empVec)
{
	ifstream empDat("EmployeeData.txt", ios::in);

	int empId;
	float hours, rate;

	while(empDat >> empId >> hours >> rate)
	{
		empVec.push_back(Employee(empId, hours, rate));
	} // end while.

	empDat.close();

} // end readFile

/* calcPay()- calculates the employee pay.
 *
 * Assumptions:  	None
 * Receives:		A vector of type Employee
 * Returns: 		A vector that has been updated with each employee pay.
 * Postcondition: 	The employee pay has been successfully calcuated and updated.
 *
 ********************************************************************************/
void calcPay(vector<Employee>& empVec)
{
	for(auto emp = empVec.begin(); emp != empVec.end(); ++emp)
	{
		(*emp).setPay((*emp).calcPay());
	}
}  // end calcPay

/* dispalyVec()- displays all the data that is for the employee.
 *
 * Assumptions:  	None
 * Receives:		A vector of type Employee
 * Returns: 		None
 * Postcondition: 	The contents of the vector have been displayed.
 *
 ********************************************************************************/
void displayVec(const vector<Employee>& empVec)
{
	for(auto emp = empVec.begin(); emp != empVec.end(); ++emp)
		{
			(*emp).Display();
			cout << endl;
		}
}

/* sortEMployees()- sorts the employees based on their ID.
 *
 * Assumptions:  	The vector is not empty
 * Receives:		A vector of type Employee
 * Returns: 		A vector that has been sorted with employee data.
 * Postcondition: 	The file has been successfully sorted.
 *
 ********************************************************************************/
void sortEmployees(vector<Employee>& empVec)
{
  sort(empVec.begin(), empVec.end());
}

/* writeToFile()- writes to a file that contains the data for the employee.
 *
 * Assumptions:  	None
 * Receives:		A vector of type Employee
 * Returns: 		None
 * Postcondition: 	The file has been successfully written.
 *
 ********************************************************************************/
void writeToFile(vector<Employee> empVec)
{
	ofstream  outfile;
	outfile.open("EmployeePay.txt", ios::out);

	for(auto emp = empVec.begin(); emp != empVec.end(); ++emp)
	{
			outfile << (*emp).getEmpID() << " " << (*emp).getNumHoursWorked()
					<< " " << (*emp).getHourlyRate()
					<< " " << (*emp).getPay();
			outfile << endl;
	}

	outfile.close();
}


/* sortPay()- sorts employees based on the their pay.
 *
 * Assumptions:  	None
 * Receives:		two Employee objects
 * Returns: 		boolean
 * Postcondition:
 * Note:			It is used in the sortByPay() function.
 *
 ********************************************************************************/
bool sortPay(const Employee& left, const Employee& right)
{
	return left.getPay() < right.getPay();
}

/* sortByPay()- sorts employees based on the their pay.
 *
 * Assumptions:  	None
 * Receives:		Employee vector
 * Returns: 		Sorted vector based on pay
 * Postcondition:
 *
 ********************************************************************************/
void sortByPay(vector<Employee>& empVec)
{
	Employee temp;
	sort(empVec.begin(),empVec.end(), sortPay);
}

// *****************************************************************************
/* readPay()- read file that contains the pay data for the employee.
 *
 * Assumptions:  	The data file does not have the pay calculated.  It will only
 * 					contain four pieces of information.
 * Receives:		A vector of type Employee
 * Returns: 		A vector that has been populated with employee data.
 * Postcondition: 	The file has been successfully read and the vector has been
 * 					populated with employee data.
 *
 ********************************************************************************/
void readPay(vector<Employee>& empPayVec)
{
	ifstream empPay("EmployeePay.txt", ios::in);

	int empId;
	float hours, rate, pay;

	while(empPay >> empId >> hours >> rate >> pay)
	{
		empPayVec.push_back(Employee(empId, hours, rate, pay));
	} // end while.

	empPay.close();

}
