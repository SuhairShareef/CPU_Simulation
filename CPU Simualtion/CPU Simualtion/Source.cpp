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
bool compareFCFS(const Process &a, const Process &b)
{
	return a.AT < b.AT;
}

/*
	This function compares two processes pased on arrival time and CPU bursed time
	It takes two parameters
	First one is the first process
	Second one is the second process
	return boolean
	true if the second processs is bigger than the first process
	false if the second processs is smaller than the first process
*/
bool compareSFJ(const Process &a, const Process &b)
{
	return a.AT + a.CPUB < b.AT + a.CPUB;
}

/*
	This function applies FCFS algorithm (First Come First Serve)
	Takes two parameter PCB -> Process Contol Block,
						testFile -> Test File Number
	returns void
*/
void FCFS(vector <Process> PCB, int testFile)
{
	/*
			FCFS Algorithm
			FCFS is a struct that includes all the served processes based on FCFS algorithm
		*/

	vector <Process> FCFS(5);
	FCFS = PCB;

	// Sorting the vector by Arrival Time
	sort(FCFS.begin(), FCFS.end(), compareFCFS);

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
	cout << "                         TEST FILE #" << testFile << endl;
	cout << endl << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "                    FCFS ALGORITHM RESULT         " << endl;
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

}

/*
	This function applies SJF algorithm (Shortest Job First)
	Takes one parameter PCB -> Process Contol Block
	returns void
*/
void SJF(vector <Process> PCB)
{
	/*
			SJF Algorithm
			SJF is a struct that includes all the served processes based on FCFS algorithm
		*/

	vector <Process> SJF(5);
	SJF = PCB;

	// Sorting the vector by Arrival Time
	sort(SJF.begin(), SJF.end(), compareSFJ);

	// Calculating starting time and completion time
	// First process startes at time 0
	if (SJF[0].AT > 0)
		SJF[0].ST = SJF[0].AT;
	else
		SJF[0].ST = 0;

	SJF[0].CT = SJF[0].CPUB;

	for (int i = 1; i < 5; i++)
	{
		if (SJF[i].AT > SJF[i - 1].CT)
			SJF[i].ST = SJF[i].AT - SJF[i - 1].CT;

		else
			SJF[i].ST = SJF[i - 1].CT;
		SJF[i].CT = SJF[i].ST + SJF[i].CPUB;
	}

	// Calculating waiting time
	// First process has waiting time = 0
	SJF[0].WT = 0;

	for (int i = 1; i < 5; i++)
	{
		// If the arrival time of the process is greater than or equal the starting 
		// time of the process then waiting time is zero
		if (SJF[i].AT >= SJF[i].ST)
			SJF[i].WT = 0;

		// otherwise it will equal to starting time - arrival time
		else
			SJF[i].WT = SJF[i].ST - SJF[i].AT;

	}

	// Calculating turnaround time = completion time - arrival time
	for (int i = 0; i < 5; i++)
	{
		SJF[i].TA = SJF[i].CT - SJF[i].AT;
	}

	// Calculating average waiting time
	double waitSum = 0;
	for (int i = 0; i < 5; i++)
	{
		waitSum += SJF[i].WT;
	}
	double avarageWaitingTime = waitSum / 5.0;

	// Calculating average turnaround time
	double turnSum = 0;
	for (int i = 0; i < 5; i++)
	{
		turnSum += SJF[i].TA;
	}
	double avarageTurnTime = turnSum / 5.0;

	cout << endl << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "                    SJF ALGORITHM RESULT         " << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << endl << endl;

	// Printing finishing time, waiting time and turnaround time

	cout << endl << endl;

	cout << "   +-------------+--------------+--------------+---------+" << endl;
	cout << "   | Process ID  | Finish Time  | Waiting Time | TA Time |" << endl;
	cout << "   +-------------+--------------+--------------+---------+" << endl;


	for (int i = 0; i < 5; i++)
	{
		cout << "          " << SJF[i].PID << "            " << SJF[i].CT << "              ";
		cout << SJF[i].WT << "            " << SJF[i].TA << endl;
		cout << "   +-------------+--------------+--------------+---------+" << endl;
	}

	// Printing Gnatt Chart

	cout << endl << endl;
	cout << "                          Gnatt Chart" << endl << endl;
	cout << "                    +----+----+----+----+----+" << endl;
	cout << "                    ";
	for (int i = 0; i < 5; i++)
	{
		cout << "  P" << SJF[i].PID << " ";
	}
	cout << endl << "                    ";
	cout << 0;
	for (int i = 0; i < 5; i++)
	{
		cout << "---" << SJF[i].CT;
	}

	cout << endl << endl << endl;
	cout << "Average Waiting Time: " << avarageWaitingTime << endl;
	cout << "Average TurnAround Time: " << avarageTurnTime << endl;
}

/*
	This function applies RR algorithm (Round Robin)
	Takes one parameter PCB -> Process Contol Block,
						CS -> Context Switch
						Q -> Time Quantum
	returns void
*/
void RoundRobin(vector <Process> PCB, int CS, int Q)
{
	vector<Process> RR;
	RR = PCB;
	int i, time, numOfProcess, remain, temps = 0; 
	double totalWaitTime = 0, totalTurnTime = 0, totalBurstTime = 0;
	int idle = 0;

	numOfProcess = 5;
	remain = 5;
	vector <int> burstRemain(numOfProcess);

	// Initializing burst time remainder
	for (int j = 0; j < numOfProcess; j++)
	{
		burstRemain[j] = RR[j].CPUB;
		RR[j].TA = 0;
		RR[j].WT = 0;
		totalBurstTime += RR[j].CPUB;
	}

	for (time = 0, i = 0; remain != 0;)
	{
		if ((burstRemain[i] <= Q) && (burstRemain[i] > 0)) 
		{
			time += burstRemain[i];
			burstRemain[i] = 0;
			temps = 1;

			if (i < 4) {
				RR[i + 1].WT += CS;
				idle += CS;
			}
				
		}

		else if (burstRemain[i] > 0)
		{
			// Subtracting Qunatum from the burst time
			burstRemain[i] -= Q;
			time += Q;
			RR[i].WT += CS;
			idle += CS;
			if (i < 4) {
				RR[i + 1].WT += CS;
			}
		}

		if (burstRemain[i] == 0 && temps == 1)
		{
			remain--;
			RR[i].WT += time - RR[i].AT - RR[i].CPUB;
			RR[i].TA += time - RR[i].AT;
			RR[i].CT = time;
			totalWaitTime += RR[i].WT;
			totalTurnTime += RR[i].TA;
			temps = 0;
		}

		if (i == (numOfProcess - 1))
			i = 0;
		else if (RR[i + 1].AT <= time)
			i++;
		else
			i = 0;

	}
	cout << endl << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "                    RR ALGORITHM RESULT         " << endl;
	cout << "--------------+---------------+--------------+--------------" << endl;
	cout << "                   Round Robin QUANTUM: " << Q << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << endl << endl;

	// Printing finishing time, waiting time and turnaround time

	cout << endl << endl;

	cout << "   +-------------+--------------+--------------+---------+" << endl;
	cout << "   | Process ID  | Finish Time  | Waiting Time | TA Time |" << endl;
	cout << "   +-------------+--------------+--------------+---------+" << endl;


	for (int i = 0; i < 5; i++)
	{
		cout << "          " << RR[i].PID << "            " << RR[i].CT << "              ";
		cout << RR[i].WT << "            " << RR[i].TA << endl;
		cout << "   +-------------+--------------+--------------+---------+" << endl;
	}

	cout << endl << endl << endl;
	cout << "Average Waiting time: " << totalWaitTime * 1.0 / numOfProcess << endl;
	cout << "Average Turnaround time: " << totalTurnTime * 1.0 / numOfProcess << endl;
	cout << "CPU Utilization: " << (totalBurstTime/(totalBurstTime + idle)) * 100 << "%" << endl;
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

	for (int i = 0; i < 4; i++) {
		fin.open(Test_Files[i]);
		if (!fin) {
			cerr << "Unable to open file";
			exit(1); // terminate with error
		}


		/*
			This vector is from process type that includes all information needed in this project
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

		// Applying FCFS 
		//FCFS(PCB, i + 1);

		// Applying SFJ
		//SJF(PCB);

		// Applying RoundRobin
		//RoundRobin(PCB, CS, Q);

		int frameNum = mSize / pSize;
		int* memFrames = new int[mSize / pSize];
		for (int i = 0; i < frameNum; i++)
		{
			memFrames[i] = i;
		}
		vector<string>MemoryFrames(frameNum);

		// for process one
		int sizeArrayp0 = PCB[0].Size / pSize;
		int* p0 = new int[sizeArrayp0];
		int frameIndex, page;
		for (int i = 0; i < sizeArrayp0; i++)
		{
			frameIndex = rand() % frameNum;
			while (memFrames[frameIndex] == -1)
			{
				frameIndex = rand() % frameNum;
			}
			p0[i] = memFrames[frameIndex];
			MemoryFrames[memFrames[frameIndex]] = "page " + to_string(i) + " process 0";
			memFrames[frameIndex] = -1;
		}

		cout << "Page Table for the first process is :" << endl;
		cout << "Page" << "      " << "Frame" << endl;
		for (int i = 0; i < sizeArrayp0; i++)
		{
			cout << "  " << i << "\t\t" << p0[i] << "\t\t" << endl;
		}

		//for process two
		int sizeArrayp1 = PCB[1].Size / pSize;
		int* p1 = new int[PCB[1].Size / pSize];
		for (int i = 0; i < sizeArrayp1; i++)
		{
			frameIndex = rand() % frameNum;
			while (memFrames[frameIndex] == -1)
			{
				frameIndex = rand() % frameNum;
			}
			p1[i] = memFrames[frameIndex];
			MemoryFrames[memFrames[frameIndex]] = "page " + to_string(i) + " process 1";
			memFrames[frameIndex] = -1;
		}

		cout << "Page Table for the second process is :" << endl;
		cout << "Page" << "      " << "Frame" << endl;
		for (int i = 0; i < sizeArrayp1; i++)
		{
			cout << "  " << i << "\t\t" << p1[i] << "\t\t" << endl;
		}

		//for process three
		int sizeArrayp2 = PCB[2].Size / pSize;
		int* p2 = new int[PCB[2].Size / pSize];
		for (int i = 0; i < sizeArrayp2; i++)
		{
			frameIndex = rand() % frameNum;
			while (memFrames[frameIndex] == -1)
			{
				frameIndex = rand() % frameNum;
			}
			p2[i] = memFrames[frameIndex];
			MemoryFrames[memFrames[frameIndex]] = "page " + to_string(i) + " process 2";
			memFrames[frameIndex] = -1;
		}

		cout << "Page Table for the third process is :" << endl;
		cout << "Page" << "      " << "Frame" << endl;
		for (int i = 0; i < sizeArrayp2; i++)
		{
			cout << "  " << i << "\t\t" << p2[i] << "\t\t" << endl;
		}

		// for process four
		int sizeArrayp3 = PCB[3].Size / pSize;
		int* p3 = new int[PCB[3].Size / pSize];
		for (int i = 0; i < sizeArrayp3; i++)
		{
			frameIndex = rand() % frameNum;
			while (memFrames[frameIndex] == -1)
			{
				frameIndex = rand() % frameNum;
			}
			p3[i] = memFrames[frameIndex];
			MemoryFrames[memFrames[frameIndex]] = "page " + to_string(i) + " process 3";
			memFrames[frameIndex] = -1;
		}

		cout << "Page Table for the fourth process is :" << endl;
		cout << "Page" << "      " << "Frame" << endl;
		for (int i = 0; i < sizeArrayp3; i++)
		{
			cout << "  " << i << "\t\t" << p3[i] << "\t\t" << endl;
		}

		int sizeArrayp4 = PCB[4].Size / pSize;
		int* p4 = new int[PCB[4].Size / pSize];
		for (int i = 0; i < sizeArrayp4; i++)
		{
			frameIndex = rand() % frameNum;
			while (memFrames[frameIndex] == -1)
			{
				frameIndex = rand() % frameNum;
			}
			p4[i] = memFrames[frameIndex];
			MemoryFrames[memFrames[frameIndex]] = "page " + to_string(i) + " process 4";
			memFrames[frameIndex] = -1;
		}

		cout << "Page Table for the fifth process is :" << endl;
		cout << "Page" << "      " << "Frame" << endl;
		for (int i = 0; i < sizeArrayp4; i++)
		{
			cout << "  " << i << "\t\t" << p4[i] << "\t\t" << endl;
		}
		cout << endl << endl << endl;


		//display the memory
		cout << "MEMORY" << endl << endl;;
		cout << "________________________________________" << endl;
		int memoryLocation = 0;
		for (int i = 0; i < frameNum; i++)
		{
			if (MemoryFrames[i] == "")
				cout << memoryLocation << "     FREE FRAME" << "             Frame" << i << endl;
			else
				cout << memoryLocation << "     " << MemoryFrames[i] << "      Frame" << i << endl;
			memoryLocation += pSize;
		}
		cout << "________________________________________" << endl << endl;;
		int processNum;
		int logicalAdd;
		cout << "Please enter the number of the process :" << endl;
		cin >> processNum;
		cout << " Please enter the logical address :" << endl;
		cin >> logicalAdd;
		int pageNum = logicalAdd / pSize;
		int displacement = logicalAdd % pSize;
		int frame;
		if (logicalAdd > PCB[processNum].Size || processNum > 5 || processNum < 0)
		{
			cout << "ERROR ->>>> the logical addressis not valid to this process." << endl;
		}
		else
		{
			if (processNum == 0)
				frame = p0[pageNum];
			else if (processNum == 1)
				frame = p1[pageNum];
			else if (processNum == 2)
				frame = p2[pageNum];
			else if (processNum == 3)
				frame = p3[pageNum];
			else if (processNum == 4)
				frame = p4[pageNum];
			cout << logicalAdd << " -> (p,d) = ( " << pageNum << " , " << displacement << " )" << " =" << "(f,d) = (" << frame << "," << displacement << " ) ->" << displacement + (frame * pSize) << endl;
			cout << endl << endl << endl;
		
		}

		system("PAUSE");
		system("CLS");
	}

	system("PAUSE");
	return 0;
}