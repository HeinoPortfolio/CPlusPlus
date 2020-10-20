#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <functional>
#include <queue>
#include <vector>
#include "Job.h"

void main()
{
	priority_queue<Job> myQ;

	Job myJob;

	myJob.SetJob(10,10,23,12,2,4);

	myQ.push(myJob);

	myJob.SetJob(23,18,10,23,23,5);

	myQ.push(myJob);


	// Output the statement
	while(!myQ.empty())
	{
		cout << myQ.top() << endl;
		myQ.pop();
	}



}