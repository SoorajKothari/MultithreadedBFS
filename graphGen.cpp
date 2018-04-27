#include <ctime>
#include <fstream>
#include <cstdlib>
#include <iostream>

using namespace std;

int main()
{
	cout << "Generating ..." << endl;
	
	srand(time(NULL));
	ofstream graphOut("generated.txt");
	
	cout << "Writing number of nodes and edges ..." << endl;
	graphOut << 400001 << " " << 400000 << endl;
	
	cout << "Writing the data contained in individual nodes ..." << endl;
	for (int i = 0; i < 400001; ++i)
	{
		graphOut << (i) << '\n';
	}
	
	cout << "Writing the edge list with random weights ..." << endl;
	
	graphOut << 0 << " " << 1 << " " << (rand() % 100) << '\n';
	
	for (int i = 1; i < 100000; ++i)
	{
		graphOut << i << " " << (i + 1) << " " << (rand() % 100) << '\n';
	}
	
	graphOut << 0 << " " << 100001 << " " << (rand() % 100) << '\n';
	
	for (int i = 100001; i < 200000; ++i)
	{
		graphOut << i << " " << (i + 1) << " " << (rand() % 100) << '\n';
	}
	
	graphOut << 0 << " " << 200001 << " " << (rand() % 100) << '\n';
	
	for (int i = 200001; i < 300000; ++i)
	{
		graphOut << i << " " << (i + 1) << " " << (rand() % 100) << '\n';
	}
	
	graphOut << 0 << " " << 300001 << " " << (rand() % 100) << '\n';
	
	for (int i = 300001; i < 400000; ++i)
	{
		graphOut << i << " " << (i + 1) << " " << (rand() % 100) << '\n';
	}
	
	graphOut.flush();
	
	cout << "DONE ..." << endl;
	
	return 0;
}