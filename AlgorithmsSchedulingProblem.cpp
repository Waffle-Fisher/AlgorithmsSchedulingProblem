#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Time
{
	int hour;
	int minute;
};

int main()
{
	ifstream InputFile("Input.txt");
	ofstream OutputFile("Output.txt");
	vector<string> busyScheduleString;
	vector<string> workingHoursString;
	string finalWorkingHours;
	int durationOfMeeting = 0;
	string inputText;
	int testStart = 0;

	for(int i = testStart; i < testStart + 5; i++)
	{
		getline(InputFile, inputText);
		if (i == 0 || i == 2) { busyScheduleString.push_back(inputText); }
		if (i == 1 || i == 3) { workingHoursString.push_back(inputText); }
		if (i == 4) { durationOfMeeting = stoi(inputText); }
	}


	for (int i = 0; i < busyScheduleString.size(); i++)
	{
		OutputFile << busyScheduleString[i];
	}
	OutputFile << "\n";
	for (int i = 0; i < workingHoursString.size(); i++)
	{
		OutputFile << workingHoursString[i];
	}
	testStart += 5;

	InputFile.close();
	OutputFile.close();
}

// Read file
// Store data: P1_schedule, p1_DailyAct, p2_schedule, p2_dailyAct, duration
// Set daily limits based on both people daily acts
// 
//  Compare p1Schedule and p2schedule
//  Combine blocks together
//  