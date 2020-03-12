/*
 * ToUpperFirst.cpp
 *
 *      Author: Heino
 *
 *      Purpose: A program to input a paragraph ending with a RETRURN keystroke
 *      and then output the same paragraph wit the first word of of each sentence capitalized.
 *
 *      Assumptions:  There are two spaces after a punctuation.
 *
 **********************************************************************/

#include <iostream>
#include <string>

using namespace std;

int main()
{
	string in_string;
	bool done;
	int index = 0;

	cout << "Please enter a paragraph:  ";
	getline(cin, in_string);

	cout << "The paragraph entered: \n" << in_string << endl;

	done = true;

	while(done)
	{
		if (index == 0)
		{
			while (in_string[index] != ' ')
			{
				in_string[index] = toupper(in_string[index]);
				index++;
			}
		}
		else if((in_string[index] == '.'|| in_string[index] == '!'|| in_string[index] == '?') && index < in_string.size())
		{
			index = index + 2;

			while (in_string[index] != ' ')
			{
				in_string[index] = toupper(in_string[index]);
				index++;
			}
		}
		else if(in_string[index] != '\n')
		{
			index++;
		}
		else
		{
			done = false;
		}
	}
	cout << "The paragraph entered: \n" << in_string << endl;
	cout << "The size of paragraph: " << in_string.size() << endl;
}


