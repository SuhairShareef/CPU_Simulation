#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;
/*
	This struct identifies the process
	 PID: Process ID,
	 AT: Arrival Time,
	 CPUB: CPU Burst,
	 size: Size in Bytes,
	 ST: Starting Time,
	 CT: Completion Time,
	 WT: Waiting Time,
	 TA: Turn Around

*/
struct Process
{
	int PID;
	int AT;
	int CPUB;
	int Size;
	int WT;
	int TA;
	int ST;
	int CT;
};

/*
	This function compares two processes pased on arrival time
	It takes two parameters
	First one is the first process
	Second one is the second process
	return boolean
	true if the second processs is bigger than the first process
	false if the second processs is smaller than the first process
*/
bool compareByArrivalTime(const Process &a, const Process &b)
{
	return a.AT < b.AT;
}

int main() {

	ifstream fin;
	ofstream fout;


	// Saving text files into array
	string Test_Files[4];
	for (int i = 0; i < 4; i++)
	{
		Test_Files[i] = "Test_Files\\Test_file_" + to_string(i + 1) + ".txt";
	}
	// Open input from test file folder, to change the file just uncomment
	// the desired file and comment the previous file

	for (int i = 0; i < 4; i++) {
		fin.open(Test_Files[i]);
		if (!fin) {
			cerr << "Unable to open file";
			exit(1); // terminate with error
		}


		/*
			This vector is from process type that includes all information needed inthis project
		*/
		vector <Process> PCB(5);

		/*
			Reading file content from the input files

			msize: Physical Memory Size,
			psize: Page size,
			Q: Round Robin Quantum,
			CS:Context Switch,
			PCB: Process Control Block that includes all processes

		*/

		int mSize, pSize, Q, CS;
		while (fin) {

			fin >> mSize >> pSize >> Q >> CS;
			for (int i = 0; i < 5; i++)
			{
				fin >> PCB[i].PID;
				fin >> PCB[i].AT;
				fin >> PCB[i].CPUB;
				fin >> PCB[i].Size;
			}
		}

		fin.close();

		/*
			FCFS Algorithm
			FCFS is a struct that includes all the served processes based on FCFS algorithm
		*/

		vector <Process> FCFS(5);
		FCFS = PCB;

		// Sorting the vector by Arrival Time
		sort(FCFS.begin(), FCFS.end(), compareByArrivalTime);

		// Calculating starting time and completion time
		// First process startes at time 0
		if (FCFS[0].AT > 0)
			FCFS[0].ST = FCFS[0].AT;
		else
			FCFS[0].ST = 0;

		FCFS[0].CT = FCFS[0].CPUB;

		for (int i = 1; i < 5; i++)
		{
			if (FCFS[i].AT > FCFS[i - 1].CT)
				FCFS[i].ST = FCFS[i].AT - FCFS[i - 1].CT;

			else
				FCFS[i].ST = FCFS[i - 1].CT;
			FCFS[i].CT = FCFS[i].ST + FCFS[i].CPUB;
		}

		// Calculating waiting time
		// First process has waiting time = 0
		FCFS[0].WT = 0;

		for (int i = 1; i < 5; i++)
		{
			// If the arrival time of the process is greater than or equal the starting 
			// time of the process then waiting time is zero
			if (FCFS[i].AT >= FCFS[i].ST)
				FCFS[i].WT = 0;

			// otherwise it will equal to starting time - arrival time
			else
				FCFS[i].WT = FCFS[i].ST - FCFS[i].AT;

		}

		// Calculating turnaround time = completion time - arrival time
		for (int i = 0; i < 5; i++)
		{
			FCFS[i].TA = FCFS[i].CT - FCFS[i].AT;
		}

		// Calculating average waiting time
		double waitSum = 0;
		for (int i = 0; i < 5; i++)
		{
			waitSum += FCFS[i].WT;
		}
		double avarageWaitingTime = waitSum / 5.0;

		// Calculating average turnaround time
		double turnSum = 0;
		for (int i = 0; i < 5; i++)
		{
			turnSum += FCFS[i].TA;
		}
		double avarageTurnTime = turnSum / 5.0;

		cout << endl << endl;
		cout << "                         TEST FILE #" << i+1  << endl;
		cout << endl << endl;
		cout << "------------------------------------------------------------" << endl;
		cout << "                    FCFS ALGORITHM RESULT         " << endl;
		//cout << "--------------+---------------+--------------+--------------" << endl;
		//cout << "                   Round Robin QUANTUM: " << Q << endl;
		cout << "------------------------------------------------------------" << endl;
		cout << endl << endl;

		cout << "                    Process Control Block " << endl;
		cout << "         +-------------+--------------+-----------+" << endl;
		cout << "         | Process ID  | Arrival Time | CPU Burst |" << endl;
		cout << "         +-------------+--------------+-----------+" << endl;
		
		for (int i = 0; i < 5; i++)
		{
			cout << "                " << FCFS[i].PID << "              " << FCFS[i].AT << "           " << FCFS[i].CPUB << "     " << endl;
			cout << "         +-------------+--------------+-----------+" << endl;
			/*cout << " ST: " << FCFS[i].ST;
			cout << " CT: " << FCFS[i].CT;
			cout << " WT: " << FCFS[i].WT;
			cout << " TA: " << FCFS[i].TA;
			cout << endl;*/
		}

		// Printing finishing time, waiting time and turnaround time

		cout << endl << endl;

		cout << "   +-------------+--------------+--------------+---------+" << endl;
		cout << "   | Process ID  | Finish Time  | Waiting Time | TA Time |" << endl;
		cout << "   +-------------+--------------+--------------+---------+" << endl;
		

		for (int i = 0; i < 5; i++)
		{
			cout << "          " << FCFS[i].PID << "            " << FCFS[i].CT << "              ";
			cout << FCFS[i].WT << "            " << FCFS[i].TA << endl;
			cout << "   +-------------+--------------+--------------+---------+" << endl;
		}

		// Printing Gnatt Chart

		cout << endl << endl;
		cout << "                          Gnatt Chart" << endl << endl;
		cout << "                    +----+----+----+----+----+" << endl;
		cout << "                    ";
		for (int i = 0; i < 5; i++)
		{
			cout << "  P" << FCFS[i].PID << " ";
		}
		cout << endl << "                    ";
		cout << 0;
		for (int i = 0; i < 5; i++)
		{
			cout << "---" << FCFS[i].CT;
		}

		cout << endl << endl << endl;
		cout << "Average Waiting Time: " << avarageWaitingTime << endl;
		cout << "Average TurnAround Time: " << avarageTurnTime << endl;



		
		system("PAUSE");
		system("CLS");
	}






	system("PAUSE");
	return 0;
}