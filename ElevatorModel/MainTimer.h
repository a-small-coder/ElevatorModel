#pragma once
public delegate void HourChangeHandler(int hour);
public delegate void MinChangeHandler();

using namespace System;
using namespace System::Threading;

ref class MainTimer
{
public: 
	static event HourChangeHandler^ OnHourChange;
	static event MinChangeHandler^ OnMinChange;
private:
	const int SSIM = 60;
	const int SHID = 24;
	int DTimeS = 10;
	int secStep = 90;
	int sec;
	int mins;
	int hours;
	int days;
	int timeSpeed;
	bool stop;
	static bool isFirstRun = true;

public:
	MainTimer() {
		SetDefaultSettings();
	}

	// return "days hours mins"
	String^ GetTimeInfo() {
		return Convert::ToString(days) + " " + Convert::ToString(hours % SHID) + " " + Convert::ToString(mins % SSIM);
	}

	bool IsFirstRun() {
		return isFirstRun;
	}

	void SetTimeSpeed(int secondStep, int timeDalayMiliseconds) {
		DTimeS = timeDalayMiliseconds;
		secStep = secondStep;
	}

	bool IsRunning() {
		return !stop;
	}

	void SetDefaultSettings() {
		timeSpeed = DTimeS;
		sec = 0.0;
		mins = 0;
		hours = 0;
		days = 0;
		stop = true;
	}

	int GetTimeSpeed() {
		return timeSpeed;
	}
	void SetTimeSpeed(int ts) {
		timeSpeed = ts;
	}

	void StopTimer() {
		stop = true;
	}

	void StartTimer() {
		if (isFirstRun) {
			isFirstRun = false;
		}
		stop = false;
	}

	void RunTimer() {
		StartTimer();
		while (true && !stop) {
			sec += secStep;
			if (sec > SSIM) {
				mins += sec / SSIM;
				sec %= SSIM;
				OnMinChange();
				if (mins >= SSIM) {
					hours += mins / SSIM;
					mins %= SSIM;
					OnHourChange(hours);
					if (hours >= SHID) {
						days += hours / SHID;
						hours %= SHID;
					}
				}

			}
			Thread::Sleep(timeSpeed);
		}
	}
};

