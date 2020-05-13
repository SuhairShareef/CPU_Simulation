#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

int main() {

	ifstream fin;
	ofstream fout;

	// Open input from test file folder, to change the file just uncomment
	// the desired file and comment the previous file
	fin.open("Test_File/Test_file_1.txt");
	//fin.open("Test_File/Test_file_1.txt");
	//fin.open("Test_File/Test_file_1.txt");
	//fin.open("Test_File/Test_file_1.txt");

	/*
		This struct identifies the process
		 PID: Process ID,
		 AT: Arrival Time,
		 CPUB: CPU Burst,
		 size: Size in Bytes,
		 ST: Starting Time,
		 FT: Finishing Time,
		 WT: Waiting Time,
		 TA: Turn Around

	*/
	struct Process
	{
		int PID;
		int AT;
		int CPUB;
		int Size;
		int ST;
		int FT;
		int WT;
		int TA;

	};

	vector <Process> PCB(5);

	/*
		Reading file content from the input files

		msize: Physical Memory Size,
		psize: Page size,
		Q: Round Robin Quantum,
		CS:Context Switch,
		PI: Process Information array that includes four parts:
			Process ID, Arrival Time, CPU Burst, Size in Bytes.
	*/

	long int mSize;
	int pSize, Q, CS;
	int PI[5][4];

	fin >> mSize >> pSize >> Q >> CS;
	for (int i = 0; i < 5; i++) {

		fin >> PCB[i].PID;
		fin >> PCB[i].AT;
		fin >> PCB[i].CPUB;
		fin >> PCB[i].Size;

	}





	system("pause");
	return 0;
}