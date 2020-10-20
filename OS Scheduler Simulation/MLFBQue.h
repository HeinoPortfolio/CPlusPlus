/* Job.cpp **********************************************************************

	Author: Matthew E. Heino 
	Course:  CS 5610 Operating Systems
	Professor:  Prof. A Galatianos
	Project:  Scheduler Program

********************************************************************************/


#include <iostream>
#include <queue>
#include "Job.h"


using namespace std;

#ifndef MLFBQUE
#define MLFBQUE

//const int timeQuant1 = 5;		// Time quantum for the first queue.
//const int timeQuant = 10;		// Time quantom for the second queue.
const int totMemory = 100;
const int totTapes = 5;

class MLFBQue
{

	public:

		MLFBQue();   // Constructor of the class.

		int getMemoryUsed();

		bool isEnoughResources(const Job newJob);
		bool hasResourcesLeft();
		bool push_Job(int counter, Job newJob);

		void updateQue(int counter);

		bool isMFBQEmpty();
		
		void jobTerminate(int counter);

	private:
		
		int memoryUsed;
		int tapesUsed;
	    int q1Left;
	    int q2Left;
		queue<Job> q1;					// First queu that will have a time quantum of 5 	
		queue<Job> q2;					//  Second queue with a time quantum of 10.
		queue<Job>  q3;					// Third queu that will be first come first serve.

 
		
}; // end class MLFBQue.

#endif
