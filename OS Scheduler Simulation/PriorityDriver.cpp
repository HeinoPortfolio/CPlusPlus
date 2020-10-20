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
#include <functional>
#include <queue>
#include <vector>
#include "Job.h"

using namespace std;

// Function Definitions.------------------------------------------------------------------------------------------------

void JobArrive(vector<Job> & jobVector, priority_queue<Job> & JOBSQUES, int counter,
			   int & vIndex, bool & done);				// Check to see if a job has arrived.

int JobSchedule(int &memoryUsed, const int totMemory, int & tapesUsed, const int totTapes, priority_queue<Job> & JOBSQUES, 
				priority_queue<Job> & READYQUEUE, bool & done, int counter, int & countextSwitch);

void JobTerminate(priority_queue<Job> & READYQUEUE, priority_queue<Job> & JOBSQUES,
				  int & memoryUsed, const int totMemory, int & tapesUsed, const int totTapes, bool & done, int counter, int & cumulativeWaitTime);


// Program Entry Point.------
int main (int argc, char *argv[])
{
	string filename ="";  // Holds the filename.
	vector<Job> jobVector;   // Queue to hold the jobs read in from the file.
	priority_queue<Job> READYQUEUE;
	priority_queue<Job> JOBSQUES;
	const int totMemory = 100;
	int memoryUsed =0;
	const int totTapes = 5;
	int tapesUsed = 0;
	int contextSwitch = 0;
	int cumulativeWaitTime = 0;
	int numOfJobs = 0;

	bool done = false;
	int vIndex = 0;
	int counter = 0;


//Review before continiueing......

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

		numOfJobs = jobVector.size() ;
		cout << numOfJobs << endl << endl;


// Program Begins Here.************************************************************************************************
		
		while(done != true)
		{	
			JobArrive(jobVector,JOBSQUES, counter,vIndex, done);
			
			if( !JOBSQUES.empty() &&  counter == JOBSQUES.top().getArriveTime())
			{
				JobSchedule(memoryUsed,totMemory, tapesUsed, totTapes, JOBSQUES, READYQUEUE, done, counter, contextSwitch);
			}
			else if(JOBSQUES.top().getPriority() > READYQUEUE.top().getPriority())
			{
				// Call the scheduler to add it to the ready queue.
				JobSchedule(memoryUsed,totMemory, tapesUsed, totTapes, JOBSQUES, READYQUEUE, done, counter, contextSwitch);
			}
			// Reduce the timeleft.
			else if(!READYQUEUE.empty())
			{
				if(READYQUEUE.top().getTimeLeft()  != 0)
				{
					READYQUEUE.top().updateTimeLeft();
					cout << counter << "\tTIME LEFT ON JOB "<< READYQUEUE.top().GetJobNum() <<" :  " << READYQUEUE.top().getTimeLeft() << endl;
				}
				else if(READYQUEUE.top().getTimeLeft()  == 0)		
				{
					JobTerminate(READYQUEUE, JOBSQUES, memoryUsed, totMemory,tapesUsed, totTapes, done, counter, cumulativeWaitTime);
				}
			}
		
			if((READYQUEUE.empty() && JOBSQUES.empty()) && ((jobVector.size() == vIndex)))
			{
				cout << "\n\nThe number of context switches:  " << contextSwitch << endl;
				cout << "The average waiting time was: " <<(cumulativeWaitTime / numOfJobs) << endl;
				cout << "The Number of Jobs in READY QUEUE is: " << READYQUEUE.size() << endl;
				cout << "The Number JObs in the JOBS QUEUE is: " << JOBSQUES.size() << endl;
				cout << "The number of tapes used is: " << tapesUsed << endl;
				cout << "The amount of memory being used is: " << memoryUsed << endl;
				done = true;
			}
			else if(memoryUsed != totMemory  && !JOBSQUES.empty()  && tapesUsed != totTapes)
			{
				JobSchedule(memoryUsed,totMemory, tapesUsed, totTapes, JOBSQUES, READYQUEUE, done, counter, contextSwitch);
			}
		
			counter++;
		} // 

		cout << endl << endl;

	} // end else filename.

	return 0;

} // end Maine.-------- Entering Canada!!!!!!!!

// Function Implementations.------------------------------------------------------------
void JobArrive(vector<Job> & jobVector, priority_queue<Job> & JOBSQUES, int counter,
			   int & vIndex, bool & done)
{ 
		if((jobVector.size()) != vIndex)
		{
			if(counter == jobVector[vIndex].getArriveTime())
			{
				cout << "\n\n\nTime" <<  "\tEvent" << "\t\tMemory Available (Total = 100k)" << "\t\tTapes (Total = 5)" << endl;

				cout <<"\n"<< counter << "\t " << jobVector[vIndex].GetJobNum()
					<< " Job Arrives "<< endl; 
				JOBSQUES.push(jobVector[vIndex]);
				vIndex++;
			}
		}
	


} // end JobArrive.------------------------------------------------------------

int JobSchedule(int &memoryUsed, const int totMemory,int & tapesUsed, const int totTapes, priority_queue<Job> & JOBSQUES, 
				priority_queue<Job> & READYQUEUE, bool & done, int counter, int & contextSwitch)
{
	if(((JOBSQUES.top().getMemoryNeeded()  + memoryUsed) <= totMemory) && (JOBSQUES.top().getTapesNeeded() + tapesUsed <= totTapes))
	{			
		// Subtract memory used by method from memory available.
		memoryUsed = memoryUsed + JOBSQUES.top().getMemoryNeeded();
		tapesUsed = tapesUsed + JOBSQUES.top().getTapesNeeded();
		


		if(!READYQUEUE.empty() &&(READYQUEUE.top().getPriority() < JOBSQUES.top().getPriority()))
		{
			cout << "\tJob " << READYQUEUE.top().GetJobNum() << " WAITS" << endl;
			cout << "\tContext switch has occurred! \n " << endl;
			contextSwitch++;

			// Set the Ready Que wait time.
			READYQUEUE.top().setReadyQueuTimeIn(counter);
		}
		// Add the job to the ready queue.
		READYQUEUE.push(JOBSQUES.top());

		

			if(READYQUEUE.top().GetJobNum() == JOBSQUES.top().GetJobNum())
			{
				cout << "\tJob " << READYQUEUE.top().GetJobNum() << " RUNS. " 
					<< "\t\t\t" << (totMemory - memoryUsed) << "\t\t\t" << (totTapes - tapesUsed) << endl << endl;
			}
			else
			{
				cout << "\tJob " << JOBSQUES.top().GetJobNum() << " WAITS. " 
					<< "\t\t\t" << (totMemory - memoryUsed) << "\t\t\t" << (totTapes - tapesUsed) << endl << endl;
				// set the wait time.
				READYQUEUE.top().setReadyQueuTimeIn(counter);
			}
		
		JOBSQUES.pop();
		
		return 0;
		
	}
	else if((JOBSQUES.top().getPriority() >  READYQUEUE.top().getPriority()))
	{
		if( ((JOBSQUES.top().getMemoryNeeded() + memoryUsed)  >  totMemory) || (JOBSQUES.top().getTapesNeeded()  + tapesUsed > totTapes )   )
		{
			queue<Job> tempQ;

			cout << "\tContext switch has occurred!\n  " << endl;
			contextSwitch++;
			/******************************************************************
			
			To maintain the order in which the jobs entered system.  (SLOPPY BUT IT WORKS.)
			The reason for this segment of code is that if you try to run the program 
			as it is it will not keep the order of the jobs as they are read in.  
			Since the JOBSQUES will insert the job with like priority after the one 
			that has been there the longeest.  If you test it with the only memory Job 3
			will be in the JOBSQUEUS the longest since it did not get a chance to run.
			Job 2 should be the one that should run ahead of it since it entered the
			system earlier.  

			***********************************************************************/
			if(!JOBSQUES.empty())
			{
				system("pause");
				
				while(!JOBSQUES.empty())
				{
					tempQ.push(JOBSQUES.top());
					JOBSQUES.pop();
				}

			}
			// Remove Jobs from the ready queue to make room for hte job with a higher priority.
			while(!READYQUEUE.empty())
			{
				memoryUsed = memoryUsed - READYQUEUE.top().getMemoryNeeded();
				tapesUsed = tapesUsed - READYQUEUE.top().getTapesNeeded();
				
				// Push the jobs back on to the JOBSQUEUE.
				JOBSQUES.push(READYQUEUE.top());
				READYQUEUE.pop();
			}
			// Put thr jobs back on the job que preserving the order that they entered the system.
			while(!tempQ.empty())
			{
				tempQ.front().setReadyQueuTimeIn(0);  // Reset time in ready queue.
				JOBSQUES.push(tempQ.front());
				tempQ.pop();
			
			}

		// Add the jobs back to the ready queu.
		JobSchedule(memoryUsed,totMemory, tapesUsed, totTapes, JOBSQUES, READYQUEUE, done, counter, contextSwitch);
			
		}

		return 0;
	}
	else
	{
		// cout << "NOT ENOUGH MEMORY  OR TAPES AVAILABLE!!!!!!!!!!!!!!!!!!!" << endl << endl;
		return 0;
	}
	
} // JObSchedule.---------------------------------------------------------------

void JobTerminate(priority_queue<Job> & READYQUEUE, priority_queue<Job> & JOBSQUES,
				  int & memoryUsed, const int totMemory, int & tapesUsed, const int totTapes, 
				  bool & done, int counter,int & cumulativeWaitTime)
{

	cout << "\nTime = " << counter << "  TERMINATING JOB: " << READYQUEUE.top().GetJobNum() 
		<<"  REALLOCATING RESOURCES BACK TO THE SYSTEM!!!" <<  endl;

	memoryUsed = memoryUsed - READYQUEUE.top().getMemoryNeeded();
	tapesUsed = tapesUsed - READYQUEUE.top().getTapesNeeded();
		
	READYQUEUE.pop();  // Remove the job from the QUEUE.

	if(!READYQUEUE.empty()) // Calculate the time a job has spent in the ReadyQueue
	{
		cumulativeWaitTime = cumulativeWaitTime + (counter - READYQUEUE.top().getReadyQTimeIn());
		cout << "The current cumulative wait time is: " << cumulativeWaitTime << endl;
		cout << "Job " << READYQUEUE.top().GetJobNum() << " has spent: " 
			<< (counter - READYQUEUE.top().getReadyQTimeIn()) << endl;
	}

} //  JobTerminate.------------------------------------------------------------

/************************************MEH***************************************/

// REMOVE BELOW***************************************************************
/******************************************************************************  
	 NOTES:

****************************************************/