#pragma once
#include "MainTimer.h"
#include "Human.h"
#include <iostream>
#include <ctime>
#using <system.drawing.dll>
using namespace System::Drawing;
using namespace System;

const int standartY = 606 - 10;
const int standartX = 238;

public delegate void ElevatorEmbarkationHandler(int placeLeft, int Vlvl);

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
	bool haveCall;
	Image^ img;
	bool visible;

public:
	
	event ElevatorEmbarkationHandler^ OnElevatorEmbarkation;

	Elevator() {
		x = standartX;
		y = standartY;
		vy = 4;
		capacity = 4;
		peopleIn = 0;
		direction = 0;
		totalVerticalLvl = 1;
		calledFloors = gcnew array<int, 1>(9);
		for (int i = 0; i < calledFloors->Length; i++) {
			calledFloors[i] = 0;
		}
		haveCall = false;
		img = Image::FromFile("img\\elevatorOpen.png");
		visible = false;
		MainTimer::OnMinChange += gcnew MinChangeHandler(this, &Elevator::workMethod);
		Human::OnCallElevator += gcnew CallElevatorHandler(this, &Elevator::listenCall);
	}

	void workMethod() {
		if (haveCall) {
			if (totalVerticalLvl < targetVerticalLvl) {
				moveUp();
				moveUp();
			}
			else {
				arriseFloor();
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

	void listenCall(int floorNumber) {
		calledFloors[floorNumber-1] = 1;
		haveCall = true;
		targetVerticalLvl = getMaxFloorCall();
	}

	void moveUp() {
		if (y > standartY - totalVerticalLvl * 64) {
			y -= vy;
		}
		else {
			totalVerticalLvl += 1;
		}
	}

	void moveDown() {
		if (y < standartY - totalVerticalLvl * 64) {
			y += vy;
		}
		else {
			totalVerticalLvl -= 1;
		}
	}

	void arriseFloor() {
		if (totalVerticalLvl == targetVerticalLvl) {
			visible = true;
			OnElevatorEmbarkation(capacity - peopleIn, totalVerticalLvl);
		}
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



