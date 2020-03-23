/*
 * Employee.h
 *
 *  Created on: Mar 17, 2020
 *      Author: Heino
 *
 *  Purpose: 	A header file to define the methods and constructors for the
 *  			employee class.
 *
******************************************************************************* */

#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

class Employee
{
	private:

		int empID;								// Employee ID
		float number_of_hours_worked;
		float hourly_rate;
		float pay;								// Calculated pay

	public:

		// Default Constructor
		Employee();
		// Explicit Constructor
		Employee(int id, float num_hours, float hourly);
		Employee(int id, float num_hours, float hourly, float pay);

		// Setters of the class.-------------------------------------------------

		void setEmpID(int emp);					// Sets the employee ID
		void setNumHours(float num_hours);		// Sets the number of hours worked
		void setHourly(float hour);				// Sets the hourly rate
		void setPay(float pay);					// Sets the calculated pay

		// Getters of the class. ----------------------------------------------
		int getEmpID(void) const;				// Gets employee ID
		float getNumHoursWorked() const;		// Gets number of hours worked
		float getHourlyRate() const;			// Gets hourly rate
		float getPay() const;					// Gets calculated pay

		// Functions of the class. ----------------------------------------------
		void Display() const;					// Displays the class information
		float calcPay();						// Calculates the pay

		// Sort by pay.
		bool sortPay(const Employee& left, const Employee& right);

		bool operator<(const Employee& right);
};

#endif /* EMPLOYEE_H_ */
