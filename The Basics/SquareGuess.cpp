/*
 * SquareGuess.cpp
 *
 *      Author: Heino
 *
 *      Purpose:  A program to calculate the square root of a number N. A
 *      square root can be approximated by making an initial guess of the
 *      root.  This initial guess can be checked by squaring and comparing against the number N.
 *
 *      Will use the following formula to get next guess:
 *
 *      next_guess = 0.5(last_guess + (N / last_guess))
 *
 *      This program will repeat until the difference between two
 *      successive guess is less than 0.005
 *
 ******************************************************************************/

#include <iostream>

using namespace std;

int main(){

	float N;
	float init_guess = 1;
	float last_guess, next_guess;
	bool done = true;

	cout << "Enter the number to find the square of: ";
	cin >> N;

	cout << "Value of square root to find (N): " << N << endl;

	last_guess = 0;

		while (done)
		{

			if ((next_guess * next_guess) == N)
			{
				cout << "The square root is: " << next_guess << endl;
				done = false;
			}
			else if(last_guess ==  0)
			{
				last_guess = init_guess;
				next_guess = 0.5 * (last_guess + (N / last_guess));
				cout << ">>>>Calculating Next Values>>>>>  ";
				cout << "Value of next guess: "<< next_guess << " value of last guess:  " << last_guess << endl;
			}
			else if((next_guess - last_guess) >  0.005 || (last_guess - next_guess ) > 0.005)
			{
				last_guess = next_guess;
				next_guess = 0.5 * (last_guess + (N / last_guess));
				cout << ">>>>Calculating Next Values>>>>>  ";
				cout << "Value of next guess: "<< next_guess << " value of last guess:  " << last_guess << endl;
			}
			else if ((next_guess - last_guess) <  0.005 || (last_guess - next_guess ) < 0.005){
				done = false;
				cout << "Approximate  of the Square root is between the value of next guess: "<< next_guess << "  and value of last guess:  " << last_guess << endl;
				cout << "DONE!" << endl;
			}
		}
	return 0;
}




