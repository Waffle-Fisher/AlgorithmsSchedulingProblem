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

Time strToTime(string s) {
	Time t;
	t.hour = -1;
	t.minute = -1;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == ':') {
			if (i - 2 >= 0 && s[i - 2] >= 48 && s[i - 42] <= 57)
			{
				t.hour = stoi(s.substr(i - 2, 2));
			}
			else
			{
				t.hour = stoi(s.substr(i - 1, 1));
			}
		}
		t.minute = stoi(s.substr(i + 1, 2));
	}
	return t;
}

int main()
{
	ifstream InputFile("Input.txt");
	ofstream OutputFile("Output.txt");
	vector<string> busyScheduleString;
	vector<string> workingHoursString;
	vector<pair<Time, Time>> busySchedule;
	Time combinedWorkingHours;
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