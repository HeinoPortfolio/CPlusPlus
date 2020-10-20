/* Job.cpp **********************************************************************

	Author: Matthew E. Heino <meheino@verizon.net>
	Course:  CS 5610 Operating Systems
	Professor:  Prof. A Galatianos
	Project:  Scheduler Program

********************************************************************************/

#include <iostream>
#include "Job.h"

using namespace std;

// Class Constructor.------

Job::Job(int jobnum, int arrive, int run, int mem, int tape, int prio)
{

	jobNum = jobnum;
	arrivTime = arrive;
	runTime =run;
	memNeeded = mem;
	tapeNeeded = tape;
	priority = prio;


} // end class sonstructor.

Job::Job()
{
	jobNum = 0;
	arrivTime = 0;
	runTime = 0;
	memNeeded = 0;
	tapeNeeded = 0;
	timeLeft = 0;
}


void Job::SetJob(int jid, int arrive, int run, int mem, int tape, int prio)
{
	jobNum = jid;
	arrivTime = arrive;
	runTime = run;
	memNeeded = mem;
	tapeNeeded = tape;
	priority = prio;
	timeLeft = runTime;
	readyQTimeIn =0;


} // end setJob.
void Job::setReadyQueuTimeIn(int counter)
{
	readyQTimeIn = counter;
}


int Job::getArriveTime() const
{
	return arrivTime;
}

int Job::GetJobNum() const
{
	return jobNum;
}

int Job::getPriority() const
{
	return priority;
}

int Job::getMemoryNeeded() const
{
	return memNeeded;
}

int Job::getTapesNeeded() const
{
	return tapeNeeded;
}

int Job::getTimeLeft() const
{
	return timeLeft;
}
int Job::getReadyQTimeIn() const
{
	return readyQTimeIn;
}
void Job::updateTimeLeft()
{
	timeLeft--;
}


void Job::Display(ostream & out) const
{
	out << "\tArrival time: "<< arrivTime << " Job Number: " << jobNum 
		<< " \n\tMemory Needed: "  << memNeeded << " Run Time: " 
		<< runTime << " Tapes needed: " << tapeNeeded 
		<< " Priority: " << priority; 

} // end Display.

ostream & operator<< (ostream &out, const Job &myJob)
{
	myJob.Display(out);
	
	return out; 
} // end opertor << ...

bool Job::operator< (const Job & myJob) const
{
	return priority < myJob.priority;
	
}
