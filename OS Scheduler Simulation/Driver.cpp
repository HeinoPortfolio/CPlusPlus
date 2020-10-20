/******************************************************************************
*
*	Author:   Matthew E. Heino 
*	Course:   CS 4720 Operating Systems
*	Prof:     Prof. A. Galatianos
*	Project:  Job Scheduler
*	Purpose:    
*
*
*	
*
******************************************************************************/

#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <functional>
#include <queue>
#include <vector>
#include "Job.h"

using namespace std;

// Function Definitions.
void JobArrive(vector<Job> & jobVector, int & counter, int & vIndex, bool & done, priority_queue<Job> & readyQueue);				// Check to see if a job has arrived.


int main (int argc, char *argv[])
{
	string filename ="";  // Holds the filename.
	vector<Job> jobVector;   // Queue to hold the jobs read in from the file.
	priority_queue<Job> readyQueue;


	bool done = false;
	int vIndex = 0;
	int counter = 0;



	if(argc != 2 || argc >= 3)
	{
		cerr << "Usage: Sched  filename(example: C:\\samplejobs.txt)" << endl;

	} // end if
	else  // Right number of arguments so try to open the file.
	{	
		ifstream inStream(argv[1]);
		assert(inStream.is_open());  // Make sure the file opened!

		// Start reading from the file.-----
		int num=0, arriv=0, run=0, mem=0, tape=0, priority=0;;

		// Read jobs from the file.-------------
		while (!inStream.eof())
		{
			inStream >> num>> arriv >> run >> mem >> tape  >> priority;
			
			// Create an object of type Job

			Job myJob;
			myJob.SetJob(num, arriv, run, mem, tape, priority);


		//	cout << "Value of the myjob is: " << myJob << endl; // REMOVE************

			jobVector.push_back(myJob);

		} // end while loop.

		// Close the stream.
		inStream.close();  // close the stream.---------------------------------------

		while(done != true)
		{
			
	
			JobArrive(jobVector, counter, vIndex, done, readyQueue);

	
		} // 

		//Output the ready queue.
		while( !readyQueue.empty())
		{
			cout << "\nThe contents of the ready queue are: \n" << readyQueue.top()  << endl;
			readyQueue.pop();
		}


	} // end else filename.

	return 0;
} // end main.--------

// Function Implementations
void JobArrive(vector<Job> & jobVector, int  & counter, int & vIndex, bool & done, priority_queue<Job> & readyQueue)
{
	
	if(vIndex == jobVector.size())
	{
		done = true;
	}
	else if(counter == jobVector[vIndex].getArriveTime() )
	{
		cout <<  "\n JOBARRIVES at T= "<< counter << "  the job matches index:" << jobVector[vIndex];
	

		readyQueue.push(jobVector[vIndex]);

		vIndex ++ ;
		counter = counter + 1;
		done = false;
	}
	else
	{
	//	cout << "\n JOB DID NOT MATCH THE index!!!!!!!" << endl; // REMOVE********************************
		counter = counter + 1;
		done = false;
	}

} // end JobArrive.------------------------------------------------------------

/************************************MEH***************************************/

// REMOVE BELOW***************************************************************
/******************************************************************************  
	 NOTES:

	1)  Need to select a job from job queue
	2)  need to keep track of memory.
	3)  Need to check the job queue and the read queue.

******************************************************************************/