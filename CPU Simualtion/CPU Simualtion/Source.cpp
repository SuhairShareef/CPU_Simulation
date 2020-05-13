#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include<iomanip>

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
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 4; j++)
			fin >> PI[i][j];





	system("pause");
	return 0;
}