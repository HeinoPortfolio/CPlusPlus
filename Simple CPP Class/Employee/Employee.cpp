/*
 * Employee.cpp
 *
 *  Created on: Mar 17, 2020
 *      Author: Heino
 *
 *  Purpose:   	A CPP file that define the implementation of the functions
 * 				that are found in Employee.h
 *
 *****************************************************************************/


#include <iomanip>
#include <iostream>
#include "Employee.h"

using namespace std;

/* Construct a class object (Explicit Values)
 *
 *  Precondition: 		A Employee object has been declared
 *  Receive:  			Initial values emp, num_hours, and hourly
 *  Postcondition:		The empId, number_of_hours_worked, hourly_rate,
 *  					and pay have been set.
 */
Employee::Employee(int emp, float num_hours, float hourly)
{
	empID = emp;
	number_of_hours_worked= num_hours;
	hourly_rate = hourly;
	pay = 0.0;
}

/* Construct a class object (Explicit Values)
 *
 *  Precondition: 		A Employee object has been declared
 *  Receive:  			Initial values emp, num_hours, and hourly, pay
 *  Postcondition:		The empId, number_of_hours_worked, hourly_rate,
 *  					and pay have been set.
 *******************************************************************************/
Employee::Employee(int emp, float num_hours, float hourly, float py)
{
	empID = emp;
	number_of_hours_worked= num_hours;
	hourly_rate = hourly;
	pay = py;
}

/* Construct a class object (Default)
 *
 *  Precondition: 		A Employee object has been declared
 *  Receive:  			Initial values emp, num_hours, and hourly
 *  Postcondition:		The empId, number_of_hours_worked, hourly_rate,
 *  					and pay have been set.
 ******************************************************************************/
Employee::Employee()
{
	empID = 0000;
	hourly_rate = 0.0;
	number_of_hours_worked = 0.0;
	pay = 0.0;
}

/* setEmpID - sets the employee ID
 *
 * Receives: an int ID
 *
 ********************************************************************************/
void Employee::setEmpID(int emp)
{
	empID= emp;
}

/* setHourly- sets the employee hourly rate
 *
 * Receives: a float hour
 * Postcondition:  class variable has been set
 *
 ********************************************************************************/
void Employee::setHourly(float hourly)
{
	hourly_rate= hourly;
}

/* setNumHours- sets the employee number of hours worked
 *
 * Receives: a float num_hours
 * Postcondition:  class variable has been set
 *
 ********************************************************************************/
void Employee::setNumHours(float num_hours)
{
	number_of_hours_worked = num_hours;
}

/* setPay- sets the employee calculated pay of  employee
 *
 * Receives: a float pay
 * Postcondition:  class variable has been set
 *
 ********************************************************************************/
void Employee::setPay(float py)
{
	pay = py;
}

//Getters***********************************************************************
/* getEmpID - gets the mployee's ID
 *
 * Returns: an int employee ID
 * Postcondition:  class variable has been returned
 *
 ********************************************************************************/
int Employee::getEmpID(void) const
{
	return empID;
}

/* getNumHoursWorked()- gets the employee number of hours worked
 *
 * Returns: an float employee number of hours worked
 * Postcondition:  class variable has been returned
 *
 ********************************************************************************/
float Employee::getNumHoursWorked() const
{
	return number_of_hours_worked;
}

/* getHourlyRate()- gets the employee hourly rate
 *
 * Returns: an float employee hourly rate
 * Postcondition:  class variable has been returned
 *
 ********************************************************************************/
float Employee::getHourlyRate() const
{
	return hourly_rate;
}

/* getPay()- gets the employee pay
 *
 * Returns: an float employee pay
 * Postcondition:  class variable has been returned
 *
 ********************************************************************************/
float Employee::getPay() const
{
 return pay;
}

/* Display()- Displays all the employee information
 *
 * Returns: an float employee hourly rate
 * Postcondition:  class variable has been returned
 *
 ********************************************************************************/
void Employee::Display() const
{
	cout << "\tEmployee ID: "<< empID << " with number of hours worked: " << number_of_hours_worked
			<< "\n\tHourly rate of: $"  << hourly_rate << "\n\tPay: $";
	cout << setprecision(2) << fixed << pay << endl;
}

/* calcPay()- Calculates the pay of the employee
 *
 * Returns: an float employee pay
 * Postcondition:  class variable has been returned
 *
 ********************************************************************************/
float Employee::calcPay()
{
	float paycheck;

	if(number_of_hours_worked < 40)
	{
		paycheck =  this->hourly_rate * this->number_of_hours_worked;
	}
	else
	{
		paycheck = (40 * hourly_rate) +
				((number_of_hours_worked - 40)  * (hourly_rate * 1.5));
	}

	return paycheck;
}

/* operator< - comparison operator for sort
 *
 * Returns: an float employee hourly rate
 * Postcondition:  class variable has been returned
 *
 ********************************************************************************/
bool Employee::operator< (const Employee& right)
{
	return this->empID < right.empID;
}



