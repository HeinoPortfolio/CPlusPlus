/* Job.h***********************************************************************

	Author: Matthew E. Heino 
	Course:  CS 5610 Operating Systems
	Professor:  Prof. A. Galatianos
	Project:  Scheduler Program

********************************************************************************/


#include <iostream>

using namespace std;
 
#ifndef JOB
#define JOB

class Job
{

	public:

		// Class Constructor.
		Job(int jid, int arrive, int run, int mem, int tape, int priority);
		Job();

		void SetJob(int jobnum, int arrive, int run, int mem, int tape, int pri );
		void setReadyQueuTimeIn(int counter);

		int getArriveTime() const;
		int GetJobNum() const;

		int getPriority() const;
		int getMemoryNeeded() const;
		int getTapesNeeded() const;
		int getTimeLeft() const;
		int getReadyQTimeIn() const;

		void updateTimeLeft();
		
		void Display(ostream & out) const;

		// Operators of the class.
		friend ostream & operator<< (ostream & out, const Job &myJob);
		bool operator< (const Job & myJob) const;

	private:

		int jobNum;				// Job number
		int arrivTime;			// Arrival time of the job
		int runTime;			// Run time needed to complet the job.
		int memNeeded;			// Amount of memory needed to run the job
		int tapeNeeded;			// Number of tapes needed by the job.
		int priority;			// Priority of the job.  1 = low  4 = high.
		int timeLeft;			// time left before job is finished.
		int readyQTimeIn;

}; // end class Job

#endif