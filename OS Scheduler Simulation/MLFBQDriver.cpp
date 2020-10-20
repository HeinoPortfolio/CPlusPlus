/******************************************************************************
*
*	Author:   Matthew E. Heino 
*	Course:   CS 4720 Operating Systems
*	Prof:     Prof. A. Galatianos
*	Project:  Job Scheduler Program Priority Queue
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
#include <queue>
#include <vector>
#include "Job.h"
#include "MLFBQue.h"

using namespace std;

// Function Definitions.------------------------------------------------------------------------------------------------

void JobArrive(vector<Job> &jobVector, priority_queue<Job> & JOBSQUES, int counter, int & vIndex, bool & done);				// Check to see if a job has arrived.

int JobSchedule(int counter, priority_queue<Job> & JOBSQUES, MLFBQue & mlfb);
void JobTerminate();


// Program Entry Point.------
int main (int argc, char *argv[])
{
	string filename ="";  // Holds the filename.
	vector<Job> jobVector;   // Queue to hold the jobs read in from the file.
	priority_queue<Job> JOBSQUES;
	MLFBQue mlfb;
	const int totMemory = 100;
	int memoryUsed =0;
	const int totTapes = 5;
	int tapesUsed = 0;


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

			jobVector.push_back(myJob);

		} // end while loop.

		inStream.close();  // close the stream.---------------------------------------
	} // end else read in from program.


// Program begins here. ---------------------------------------------------------

	cout << "TIME" << "\t\tEVENT" << "\t\tMEMORY AVAILABLE" << "\t\tTAPES AVAILABLE" << endl;

	while(done != true)
	{
		JobArrive(jobVector, JOBSQUES, counter, vIndex, done);

		if(counter == JOBSQUES.top().getArriveTime())
		{
			// A job that matches the time has enetered the system and should tried to scheduled.
			JobSchedule(counter, JOBSQUES, mlfb);
		}
		else if(!JOBSQUES.empty() && mlfb.isEnoughResources (JOBSQUES.top ()) )
		{
			JobSchedule(counter, JOBSQUES, mlfb);
		}
		else						// Update the queu no jobs arrived to be scheduled
		{
			  mlfb.updateQue(counter);
		}
		
		// Use the isEmpty from the MLFBQ to check to see if they are empty.
		if((jobVector.size() == vIndex) && mlfb.isMFBQEmpty()  && JOBSQUES.empty())
		{
			done = true;
		}

		counter++;
	}
	
	return 0;

} // end Maine entering CANADA!!!!!

// Function Implementations.---------------------------------------------------
void JobArrive(vector<Job> & jobVector, priority_queue<Job> & JOBSQUES, int counter, int & vIndex, bool & done)
{
	
		if((jobVector.size()) != vIndex)
		{
			if(counter == jobVector[vIndex].getArriveTime())
			{
				cout <<"\n"<< counter << "\t\tJOB " << jobVector[vIndex].GetJobNum()
					<< " Arrives "<< endl; ;

				// Add the job to the Jobs awaiting the processing.
				JOBSQUES.push(jobVector[vIndex]);

				vIndex++;
			}
		}
		
} // end JobArrive.-----------------------------------------------------------

int JobSchedule(int counter, priority_queue<Job> & JOBSQUES, MLFBQue & mlfb)
{
	if(mlfb.push_Job(counter, JOBSQUES.top()))
	{
		JOBSQUES.pop();
	}

	return 0;
}

/*
  NOTES:

  Will Need to clean up the output in.
	
*/