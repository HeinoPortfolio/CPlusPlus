#include <iostream>
#include <queue>
#include "Job.h"
#include "MLFBQue.h"

using namespace std;


//Class Constructor.--------------------------------------------------------------------
MLFBQue::MLFBQue()
{
	memoryUsed = 0;
	tapesUsed =0;
	q1Left = 5;
	q2Left = 10;
	queue<Job> q1;					// First queu that will have a time quantum of 5 	
	queue<Job> q2;					//  Second queue with a time quantum of 10.
	queue<Job> q3;	
	
}

int MLFBQue::getMemoryUsed()
{
	return memoryUsed;
}

bool MLFBQue::isEnoughResources(const Job newJob)
{
	if(((newJob.getMemoryNeeded() + memoryUsed) <= totMemory) && 
		((newJob.getTapesNeeded() + tapesUsed) <= totTapes))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MLFBQue::hasResourcesLeft()
{
	if(memoryUsed < totMemory )
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool MLFBQue::push_Job(int counter, Job newJob)
{

	// Push the incoming job onto the queue.
	if(isEnoughResources(newJob))
	{
		cout << "\nTIME" << "\t\tEVENT" << "\t\tMEMORY AVAILABLE" 
			<< "\t\tTAPES AVAILABLE" << endl;
		
		q1.push(newJob);

		if(q1.front().GetJobNum() == newJob.GetJobNum())
		{
			cout << counter <<  "\t\tJob " << q1.front().GetJobNum() << " runs";
		}
		else
		{
			cout << counter << "\t\tJob " << newJob.GetJobNum() << " waits ";
		}

		// Update the amount of memory and tapes used.
		memoryUsed = memoryUsed + newJob.getMemoryNeeded();
		tapesUsed = tapesUsed + newJob.getTapesNeeded();

		cout << "\t \t"<< (totMemory - memoryUsed)<< "\t\t\t\t" <<
			(totTapes - tapesUsed) << endl;
		
		cout << endl;

		return true;
	}
	else
	{
		cout << "\n**** NOT ENOUGH MEMORY OR TAPES TO RUN AT THIS TIME! ****" 
			<< endl << endl;

		return false;
	}

} //end push_Job.----------------------------------------------------------

void MLFBQue::updateQue(int counter)
{
	if(!q1.empty())  // Process the jobs in the first queue
	{
		if(q1.front().getTimeLeft() != 0)
		{
			if(q1Left != 0)
			{
				q1.front().updateTimeLeft();
				cout <<"Time Left On *** JOB " <<q1.front().GetJobNum() 
					<< " *** From Q1: " << q1.front().getTimeLeft() << endl;
			
				// Decrement the timeleft in this queue.
				q1Left--;
			}
			else
			{
			
				cout << endl <<"AT TIME = " << counter << " THE TIME HAS EXPIRED FOR ***** JOB "
					<< q1.front().GetJobNum() <<" ***** IN QUEUE 1 !!" << endl << endl;
			
				// Move the job to second queue
				q2.push (q1.front());
				q1.pop();
			
				// Reset the q1left
				q1Left = 5;

			} //end else.

		}  // end ifq1 front element is notequal to zero.
		else  // Termintate the job.---------------------------------------------
		{
			// Call the Job Terminate Function.
			jobTerminate(counter);
		}

	} // end q1! empty.---
	else if(!q2.empty())
	{
		if(q2.front().getTimeLeft() != 0)
		{
			if(q2Left != 0)
			{
					q2.front().updateTimeLeft();
					cout <<"Time Left on job from update Q2: " 
						<< q2.front().getTimeLeft() << endl; 
		
					// Decrement the timeleft in this queue.
					q2Left--;	
			} // end q2Left.
			else
			{
				// Output the event
				cout<< endl <<"AT TIME = " << counter << "\tTIME HAS EXPIRED FOR ***** JOB " 
					<< q2.front().GetJobNum() << "IN Q2! IT IS BEING MOVED Q3" << endl << endl; 
				
				// Move the job to second queue
				q3.push (q2.front());
				q2.pop();
	
				// Reset the q1left
				q2Left = 10;
			}
		} // end if q2 getTimeleft != 0.
		else // Terminate the job.
		{
			jobTerminate(counter);
		}
	}// end if !q2empty.
	else if(!q3.empty()) // Process the jobs in last queue.
	{
		if(q3.front().getTimeLeft() != 0)
		{
			// Reduce the time left.
			q3.front().updateTimeLeft();
			cout <<"Value of time left on job" <<q3.front().GetJobNum()  <<" from update Q3: " 
				<< q3.front().getTimeLeft() << endl;
		}
		else	// Terminate the Job  
		{
			jobTerminate(counter);
		}
	} // end elseif q3 empty. 


} // end updateQueue.----------------------------------------------------------

bool MLFBQue::isMFBQEmpty()
{	
	if(q1.empty() && q2.empty() && q3.empty())
	{
		return true;
	}
	else 
	{
		return false;
	}

} // End isMFBQEmpty.----------------------------------------------------------]

void MLFBQue::jobTerminate(int counter)
{
	if(!q1.empty() && q1.front().getTimeLeft() == 0)
	{
		cout << "\nAT TIME = " << counter << "  TERMINATING Job " << q1.front().GetJobNum() 
			<< " RETURNING RESOURCES TO THE SYSTEM." << endl;
		
		// Allocate the memory and tapes back to the system.----
		memoryUsed = memoryUsed - q1.front().getMemoryNeeded() ;
		tapesUsed = tapesUsed - q1.front().getTapesNeeded(); 
		q1.pop();
		system("pause");
	}
	else if( !q2.empty()  && q2.front().getTimeLeft() == 0)
	{
		cout <<"\nAT TIME = " << counter << " TERMINATING*** Job " << q2.front().GetJobNum() 
			<< "****RETURNING RESOURCES TO THE SYSTEM." << endl;
		
		// Allocate the memory back to the system.------------
		memoryUsed = memoryUsed - q2.front().getMemoryNeeded();
		tapesUsed =tapesUsed - q2.front().getTapesNeeded();

		q2.pop();
		system("pause");

		cout << "Number of Tapes Used: " << tapesUsed << endl;
	}
	else if(!q3.empty() && q3.front().getTimeLeft() == 0)
	{
		cout << "\nAT TIME = " << counter << " TERMINATING*** Job " << q3.front().GetJobNum() 
			<< "****RETURNING RESOURCES TO THE SYSTEM." << endl;
		
		memoryUsed = memoryUsed - q3.front().getMemoryNeeded();
		tapesUsed = tapesUsed - q3.front().getTapesNeeded(); 
		q3.pop();
		system("pause");
	}
	else
	{
		cerr << "AN ERROR HAS OCCURRED!!!!!!! " << endl <<  endl ;
	}

} // end jobTerminate.