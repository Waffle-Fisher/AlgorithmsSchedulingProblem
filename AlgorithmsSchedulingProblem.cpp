#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Returns smaller timer
string getSmallerTime(string a, string b)
{
	if (a.size() < b.size()) { return a; }
	if (b.size() < a.size()) { return b; }
	int i = a.compare(b);
	if (i == 0 || i == -1) { return a; }
	return b;
}

// Returns time difference between two times
int getTimeDifference(string a, string b)
{
	int aMins;
	int bMins;
	if (a[1] == 39) { aMins = stoi(a.substr(0, 1)) * 60 + stoi(a.substr(2, 2)); }
	else { aMins = stoi(a.substr(0, 2)) * 60 + stoi(a.substr(3, 2)); }
	if (b[1] == 39) { bMins = stoi(b.substr(0, 1)) * 60 + stoi(b.substr(2, 2)); }
	else { bMins = stoi(b.substr(0, 2)) * 60 + stoi(b.substr(3, 2)); }
	if (aMins > bMins) { return aMins - bMins; }
	return bMins - aMins;
}

int main()
{
	ifstream InputFile("Input.txt");
	ofstream OutputFile("Output.txt");
	
	for(int numTestCases = 0; numTestCases < 10; numTestCases++)
	{
		vector<string> busyScheduleString;
		vector<pair<string, string>> busySchedule;
		vector<string> workingHoursString;
		pair<string, string> finalWorkHours;
		int durationOfMeeting = 0;
		string inputText;
		string output = "[";

		// Read file, get data
		for (int i = 0; i < 5; i++)
		{
			std::getline(InputFile, inputText);
			if (i == 0 || i == 2) {
				int j = 0;
				while (j < inputText.size())
				{
					if (inputText[j] == 39) {
						if (inputText[j + 6] == 39) {
							busyScheduleString.push_back(inputText.substr(j + 1, 5));
							j += 6;
						}
						else {
							busyScheduleString.push_back(inputText.substr(j + 1, 4));
							j += 5;
						}
					}
					j++;
				}
			}
			if (i == 1 || i == 3) {
				int j = 0;
				while (j < inputText.size())
				{
					if (inputText[j] == 39) {
						if (inputText[j + 6] == 39) {
							workingHoursString.push_back(inputText.substr(j + 1, 5));
							j += 6;
						}
						else {
							workingHoursString.push_back(inputText.substr(j + 1, 4));
							j += 5;
						}
					}
					j++;
				}
			}
			if (i == 4) { durationOfMeeting = stoi(inputText); }
		}

		// get shared workingHours
		finalWorkHours.first = getSmallerTime(workingHoursString[0], workingHoursString[2]);
		finalWorkHours.second = getSmallerTime(workingHoursString[1], workingHoursString[3]);

		// Seperate out each block
		for (int i = 0; i < busyScheduleString.size(); i += 2)
		{
			pair<string, string> tb;
			tb.first = busyScheduleString[i];
			tb.second = busyScheduleString[i + 1];
			busySchedule.push_back(tb);
		}

		// Merge Blocks
		sort(busySchedule.begin(), busySchedule.end());
		int i = 0;
		while (i < busySchedule.size())
		{
			if (i + 1 < busySchedule.size() && busySchedule[i].second > busySchedule[i + 1].first) {
				busySchedule[i].second = busySchedule[i + 1].second;
				busySchedule.erase(busySchedule.begin() + i + 1);
			}
			else
			{
				i++;
			}
		}

		if (getTimeDifference(finalWorkHours.first, busySchedule[0].first) >= durationOfMeeting)
		{
			output += "['" + finalWorkHours.first + "','" + busySchedule[0].first + "']";
		}
		for (int i = 0; i < busySchedule.size() - 1; i++)
		{
			if (getTimeDifference(busySchedule[i].second, busySchedule[i + 1].first) >= durationOfMeeting)
			{
				output += ",['" + busySchedule[i].second + "','" + busySchedule[i + 1].first + "']";
			}
		}
		if (getTimeDifference(finalWorkHours.second, busySchedule[busySchedule.size() - 1].second) >= durationOfMeeting)
		{
			output += "['" + busySchedule[busySchedule.size() - 1].second + "','" + finalWorkHours.second + "']\n";
		}
		OutputFile << output;
		std::getline(InputFile, inputText);
	}

	InputFile.close();
	OutputFile.close();
}