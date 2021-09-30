#pragma once
#include "MainTimer.h"
#include "Human.h"
#include <iostream>
#include <ctime>
#using <system.drawing.dll>
using namespace System::Drawing;
using namespace System;

const int standartY = 606 - 10;
const int standartX = 240;

public delegate void ElevatorEmbarkationHandler(int placeLeft, int Vlvl);
public delegate void DisEmbarkationHandler(int lvl, int id);

ref class Elevator
{
private:
	int x;
	int y;
	int vy;
	int capacity;
	int peopleIn;
	int direction; // 0 - undefine, 1 - top,  2 - bottom
	int totalVerticalLvl; // 1-9
	int targetVerticalLvl; // 1-9, 0 - undefine
	array<int, 1>^  calledFloors; // 0 - calm, 1 - call
	array<int, 1>^ HumansIn;
	array<int, 1>^ HumansInId;
	bool haveCall;
	Image^ img;
	bool visible;
	int waitingHumansTime = 20;

public:
	
	event ElevatorEmbarkationHandler^ OnElevatorEmbarkation;
	event DisEmbarkationHandler^ DisEmbarkation;

	Elevator() {
		x = standartX;
		y = standartY;
		vy = 4;
		capacity = 4;
		peopleIn = 0;
		direction = 0;
		totalVerticalLvl = 1;
		calledFloors = gcnew array<int, 1>(9);
		HumansIn = gcnew array<int, 1>(capacity);
		HumansInId = gcnew array<int, 1>(capacity);
		for (int i = 0; i < calledFloors->Length; i++) {
			calledFloors[i] = 0;
		}
		for (int i = 0; i < capacity; i++) {
			HumansIn[i] = 0;
			HumansInId[i] = -1;
		}
		haveCall = false;
		img = Image::FromFile("img\\elevatorOpen.png");
		visible = false;
		MainTimer::OnMinChange += gcnew MinChangeHandler(this, &Elevator::workMethod);
		Human::OnCallElevator += gcnew CallElevatorHandler(this, &Elevator::listenCall);
	}

	void acceptEmbarkation(int targetLvl, int id, int elevatorWaitingTime) {
		if (elevatorWaitingTime > 0) {
			int i = findIndex(HumansInId, id);
			if (peopleIn < capacity && i == -1) {
				listenCall(targetLvl);
				targetVerticalLvl = getFloorDownTarget(targetLvl);
				waitingHumansTime = 10;
				HumansIn[peopleIn] = targetLvl;
				HumansInId[peopleIn] = id;
				peopleIn += 1;
			}
		}
		
		
	}

	int findIndex(array<int, 1>^ arr, int num) {
		for (int i = 0; i < arr->Length; i++) {
			if (arr[i] == num) {
				return i;
			}
			
		}
		return -1;
	}

	void disEmbarkation() {
		bool f = false;
		for (int i = 0; i < HumansIn->Length; i++) {
			if (HumansIn[i] == totalVerticalLvl) {
				DisEmbarkation(totalVerticalLvl, HumansInId[i]);
				HumansIn[i] = 0;
				HumansInId[i] = -1;
				peopleIn -= 1;
				f = true;
			}
		}
		if (f) {
			targetVerticalLvl = getFloorDownTarget(getMaxFloorCall());
		}
	}

	void workMethod() {
		if (haveCall) {
			if (targetVerticalLvl == -1) {
				visible = false;
				haveCall = false;
			}
			else if (totalVerticalLvl < targetVerticalLvl) {
				moveUp();
			}
			else if (totalVerticalLvl > targetVerticalLvl) {
				moveDown();
			}
			else {
				arriseFloor();
				if (waitingHumansTime <= 0) {
					targetVerticalLvl = getMaxFloorCall();
					waitingHumansTime = 20;
				}
				else {
					waitHumans();
				}
			}

			
		}
	}

	int getMaxFloorCall() {
		if (haveCall) {
			for (int i = calledFloors->Length-1; i >= 0; i--) {
				if (calledFloors[i] == 1) {
					return i+1;
				}
			}
		}
		return -1;
	}

	int getFloorDownTarget(int targetLvl) {
		int total = totalVerticalLvl;
		int maxDown = 0;
		for (int i = HumansIn->Length - 1; i >= 0; i--) {
			if (HumansIn[i] > maxDown && HumansIn[i] < totalVerticalLvl) {
				maxDown = HumansIn[i];
			}
		}
		if (maxDown == 0) {
			return targetLvl;
		}
		else {
			return maxDown;
		}
	}

	void listenCall(int floorNumber) {
		calledFloors[floorNumber-1] = 1;
		haveCall = true;
		targetVerticalLvl = getMaxFloorCall();
		/*if (totalVerticalLvl <= getMaxFloorCall()) {
			targetVerticalLvl = getFloorDownTarget(getMaxFloorCall());
		}*/
		
	}

	void moveUp() {
		if (y > standartY  - totalVerticalLvl * 64) {
			y -= vy;
		}
		else {
			totalVerticalLvl += 1;
		}
	}

	void moveDown() {
		if (y < standartY + 128 - totalVerticalLvl * 64) {
			y += vy;
		}
		else {
			totalVerticalLvl -= 1;
		}
	}

	void arriseFloor() {
		if (totalVerticalLvl == targetVerticalLvl) {
			visible = true;
			calledFloors[totalVerticalLvl - 1] = 0;
			disEmbarkation();
			OnElevatorEmbarkation(capacity - peopleIn, totalVerticalLvl);

		}
	}

	void waitHumans() {
		if (waitingHumansTime > 0) {
			waitingHumansTime -= 1;
		}
	}

	String^ calledFloorsToString() {
		String^ s = "calledFloors: [";
		for (int i = 0; i < calledFloors->Length; i++) {
			s += Convert::ToString(calledFloors[i]) + ", ";
		}
		s += "]";
		return s;
	}

	String^ HumansInToString() {
		String^ s = "Humans: [";
		for (int i = 0; i < HumansIn->Length; i++) {
			s += Convert::ToString(HumansIn[i]) + ", ";
		}
		s += "]";
		return s;
	}

	String^ HumansInIdToString() {
		String^ s = "Humans: [";
		for (int i = 0; i < HumansInId->Length; i++) {
			s += Convert::ToString(HumansInId[i]) + ", ";
		}
		s += "]";
		return s;
	}

	String^ getPeopleIn() {
		return Convert::ToString(peopleIn);
	}

	// getters -------
	Rectangle^ getDimentionsImg() {
		return gcnew Rectangle(x, y, img->Width, img->Height);
	}

	Image^ getImage() {
		return img;
	}

	Point^ getPosition() {
		return gcnew Point(x, y);
	}

	bool isVisible() {
		return visible;
	}

	int getTotalVerticalLvl() {
		return totalVerticalLvl;
	}

};



