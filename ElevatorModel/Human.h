#pragma once
#include "MainTimer.h"
#include <iostream>
#include <ctime>
#using <system.drawing.dll>
using namespace System::Drawing;
using namespace System;

public delegate void CallElevatorHandler(int floor);
public delegate void OpenDoorHandler(int door, int totalVerticalLvl);
public delegate void ChangePictureHandler(int id);
public delegate void EmbarkatedInElevatorHandler(int targetLvl, int id);

const int homeDoorX = 320;
const int elevatorX = 265;
const int elevatorDoorX = 222;
const int ladderRightX = 197;
const int ladderLeftX = 145;
const int homeExitX = 380;
const int rightBorderX = 554;
const int leftBorderX = 0;


ref class Human
{

protected:
	int rrand(int range_min, int range_max) {
		return rand() % (range_max - range_min + 1) + range_min;
	}
	int x;
	int y;
	int vx = 3;
	int vy = 3;
	int totalVerticalLvl;
	int whatObjectNearby;
	int homeIndex;
	int targetPlaceIndex;
	int elevatorWaitingTime;
	String^ type;
	bool visible;
	Image^ img;
	bool halfStairswalk;
	bool needGoBack;
	bool needGoOut;
	int whenGoHome;
	int whenGoOut;
	int whenGoMin;
	int behaviorType;
	int elevatorWaitingTimeRand = 25 * 6;
	static int countObjects = 0;
	int id;
	int  embarkated; // 0 - no, 1 - start, 2 - end nearly
public:
	static event OpenDoorHandler^ OnOpenDoor;
	static event CallElevatorHandler^ OnCallElevator;
	event ChangePictureHandler^ ChangePicture;
	event EmbarkatedInElevatorHandler^ EmbarkatedInElevator;
	Human() {
		MainTimer::OnMinChange += gcnew MinChangeHandler(this, &Human::live);
		MainTimer::OnHourChange += gcnew HourChangeHandler(this, &Human::setNeedGoBack);
		totalVerticalLvl = rrand(2, 9);
		x = homeDoorX;
		y = 650 + 14 - totalVerticalLvl*64;
		whatObjectNearby = 0;
		visible = false;
		homeIndex = totalVerticalLvl;
		
		elevatorWaitingTime = rrand(elevatorWaitingTimeRand, elevatorWaitingTimeRand*2);
		halfStairswalk = false;
		needGoBack = false;
		needGoOut = false;
		whenGoHome = rrand(18, 22);
		whenGoOut = rrand(6, 10);
		behaviorType = rrand(1, 4);
		img = Image::FromFile("img\\people" + Convert::ToString(behaviorType) + ".png");
		countObjects += 1;
		id = countObjects;
		whenGoMin = (behaviorType * 5 + rrand(5, 25)) * 6;
		embarkated = 0;
		if (behaviorType != 2) {
			targetPlaceIndex = 1;
		}
		else {
			targetPlaceIndex = rrand(2, 9);
			while (targetPlaceIndex == homeIndex) {
				targetPlaceIndex = rrand(2, 9);
			}
		}
	}

	

	void setNeedGoBack(int hour) {
		if (hour == whenGoHome) {
			needGoBack = true;
			needGoOut = false;
			elevatorWaitingTime = rrand(elevatorWaitingTimeRand, elevatorWaitingTimeRand * 2);
			whenGoMin = (behaviorType * 5 + rrand(5, 25)) * 6;
			if (totalVerticalLvl != homeIndex) {
				targetPlaceIndex = homeIndex;
			}
			else {
				if (behaviorType != 2) {
					targetPlaceIndex = 1;
				}
				else {
					targetPlaceIndex = rrand(2, 9);
					while (targetPlaceIndex == homeIndex) {
						targetPlaceIndex = rrand(2, 9);
					}
				}
			}
			
		}
		if (hour == whenGoOut) {
			needGoBack = false;
			needGoOut = true;
			elevatorWaitingTime = rrand(elevatorWaitingTimeRand, elevatorWaitingTimeRand * 2);
			whenGoMin = (behaviorType * 5 + rrand(5, 25)) * 6;
			if (totalVerticalLvl != homeIndex) {
				targetPlaceIndex = homeIndex;
			}
			else {
				if (behaviorType != 2) {
					targetPlaceIndex = 1;
				}
				else {
					targetPlaceIndex = rrand(2, 9);
					while (targetPlaceIndex == homeIndex) {
						targetPlaceIndex = rrand(2, 9);
					}
				}
			}
		}

	}

	void waitingMins() {
		if (whenGoMin > 0) {
			whenGoMin--;
		}
	}

	void live() {
		if (behaviorType == 2) {
			// ------go back--------
			
			if (needGoBack) {
				
				goFromOtherHomeToHome();
			}
			if (needGoOut) // ----go to neighbour----
			{
				goFromHomeToOtherHome();
			}
		}
		else // go out
		{
			// ------go back--------
			if (needGoBack) {
				goFromStreetToHome();
			}
			if (needGoOut) // ----go work----
			{
				goFromHomeToStreet();
			}
		}

	}

	void disEmbarkation(int Vlvl, int index) {
		if (index == id) {
			whatObjectNearby = 4;
			visible = true;
			totalVerticalLvl = Vlvl;
			embarkated = 0;
			x = 238;
			y = 650 + 14 - totalVerticalLvl * 64;
			ChangePicture(id);
			img = Image::FromFile("img\\people" + Convert::ToString(behaviorType) + ".png");
		}
		
	}

	void goFromHomeToOtherHome() {
		if (whatObjectNearby == 0) { // at home
			waitingMins();
			if (whenGoMin == 0) {
				visible = true;
				goToElevator();
			}
			
		}
		if (whatObjectNearby == 1) { // at elevator

			if (embarkated == 1) {
				embarkating();
			}
			else if (embarkated == 0) {
				waitElevator();
			}
			
			if (elevatorWaitingTime == 0) {
				moveToLadder();
			}
		}
		if (whatObjectNearby == 4) {  // at ladder
			if (totalVerticalLvl > targetPlaceIndex) {
				if (!halfStairswalk) {
					goDowunStairsRight();
				}
				else {
					goDowunStairsLeft();
				}

			}
			else if (totalVerticalLvl < targetPlaceIndex) {
				if (!halfStairswalk) {
					goUpStairsRight();
				}
				else {
					goUpStairsLeft();
				}
			}
			else {
				goToApartment();
			}
		}
	}

	void goFromOtherHomeToHome() {
		if (whatObjectNearby == 9) {
			waitingMins();
			if (whenGoMin == 0) {
				visible = true;
				goToElevator();
			}
		}
		if (whatObjectNearby == 1) { // at elevator
			if (embarkated == 1) {
				embarkating();
			}
			else if (embarkated == 0) {
				waitElevator();
			}
			if (elevatorWaitingTime == 0) {
				moveToLadder();
			}
		}
		if (whatObjectNearby == 4) {  // at ladder
			if (totalVerticalLvl > homeIndex) {
				if (!halfStairswalk) {
					goDowunStairsRight();
				}
				else {
					goDowunStairsLeft();
				}

			}
			else if (totalVerticalLvl < homeIndex) {
				if (!halfStairswalk) {
					goUpStairsRight();
				}
				else {
					goUpStairsLeft();
				}
			}
			else {
				goToApartment();
			}
		}
	}

	void goFromHomeToStreet() {
		if (whatObjectNearby == 0) { // at home
			waitingMins();
			if (whenGoMin == 0) {
				visible = true;
				goToElevator();
			}
		}
		if (whatObjectNearby == 1) { // at elevator
			if (embarkated == 1) {
				embarkating();
			}
			else if (embarkated == 0) {
				waitElevator();
			}
			if (elevatorWaitingTime == 0) {
				moveToLadder();
			}
		}

		if (whatObjectNearby == 4) {  // at ladder
			if (totalVerticalLvl != 1) {
				if (!halfStairswalk) {
					goDowunStairsRight();
				}
				else {
					goDowunStairsLeft();
				}

			}
			else {
				moveToExit(); // at 1 lvl
			}
		}
		if (whatObjectNearby == 8) { // at exit door
			goOutFrom();
		}
	}

	void goFromStreetToHome() {
		if (whatObjectNearby == 6) {
			waitingMins();
			if (whenGoMin == 0) {
				visible = true;
				moveToHouse();
			}
		}
		if (whatObjectNearby == 8) {
			goInHouse();
		}
		if (whatObjectNearby == 1) {
			if (embarkated == 1) {
				embarkating();
			}
			else if (embarkated == 0) {
				waitElevator();
			}
			if (elevatorWaitingTime == 0) {
				moveToLadder();
			}
		}

		if (whatObjectNearby == 4) {
			if (totalVerticalLvl != homeIndex) {
				if (!halfStairswalk) {
					goUpStairsRight();
				}
				else {
					goUpStairsLeft();
				}
			}
			else {
				goToApartment();
			}
		}
	}

	void moveHorizontal(bool toRight) {
		if (toRight) {
			x += vx;
		}
		else {
			x -= vx;
		}
	}

	void moveVertical(bool toTop) {
		if (!toTop) {
			y += vy;
		}
		else {
			y -= vy;
		}
	}

	void embarkating() {
		if (x < 238) {
			moveHorizontal(false);
		}
		else {
			embarkated = 2;
			visible = false;
		}

	}

	void tryEmbarkation(int spaceLost, int elevatorVerticalLvl) {
		if (elevatorVerticalLvl == totalVerticalLvl && spaceLost > 0 && whatObjectNearby == 1) {
			embarkated = 1;
			EmbarkatedInElevator(targetPlaceIndex, id);
		}
		
	}

	void goToElevator() {
		if (x > elevatorX) {
			moveHorizontal(false);
		}
		else {
			whatObjectNearby = 1;
		}
	}

	void waitElevator() {
		OnCallElevator(totalVerticalLvl);
		if (elevatorWaitingTime > 0) {
			if (elevatorWaitingTime < 5 * 6) {
				img = Image::FromFile("img\\people" + Convert::ToString(behaviorType) + "Rage.png");
				ChangePicture(id);
			}
			elevatorWaitingTime--;
		}
		else {
			ChangePicture(id);
			img = Image::FromFile("img\\people" + Convert::ToString(behaviorType) + ".png");
		}
		
	}

	void moveToLadder() {
		if (x > ladderLeftX) {
			moveHorizontal(false);
			/*if (x > elevatorDoorX + 5 && x < elevatorDoorX - 5) {
				OnOpenDoor(7, totalVerticalLvl);
			}*/
		}
		else {
			whatObjectNearby = 4;
		}
	}

	void goDowunStairsRight() {
		if (x < ladderRightX) {
			moveHorizontal(true);
			moveVertical(false);
			moveHorizontal(true);
		}
		else {
			halfStairswalk = true;
		}
	}

	void goDowunStairsLeft() {
		if (x > ladderLeftX) {
			moveHorizontal(false);
			moveVertical(false);
			moveHorizontal(false);
		}
		else {
			totalVerticalLvl -= 1;
			halfStairswalk = false;
			y = 650 + 16 - totalVerticalLvl * 64; // correction coord y
		}
	}

	void moveToExit() 
	{
		if (x < homeExitX) {
			moveHorizontal(true);
		}
		else {
			whatObjectNearby = 8;
		}
		
	} 

	void goOutFrom() {
		if (y < 640) {
			moveVertical(false);
		}
		else {
			if (behaviorType == 1 || behaviorType == 4) { // костыль по определению направления выхода
				if (x < rightBorderX) {
					moveHorizontal(true);
				}
				else {
					visible = false;
					whatObjectNearby = 6;
				}
			}
			else {
				if (x > -30) {
					moveHorizontal(false);
				}
				else {
					visible = false;
					whatObjectNearby = 6;
				}
			}
			
		}
	}

	void moveToHouse() // костыль по определению направления входа
	{
		if (behaviorType == 1 || behaviorType == 4) {
			if (x > homeExitX) {
				moveHorizontal(false);
			}
			else {
				whatObjectNearby = 8;
			}
		}
		else {
			if (x < homeExitX) {
				moveHorizontal(true);
			}
			else {
				whatObjectNearby = 8;
			}
		}
		
	}

	void goInHouse() {
		if (y > 602) {
			moveVertical(true);
		}
		else {
			goToElevator();  // костыль какой-то
		}
	}

	void goUpStairsRight() {
		if (x < ladderRightX) {
			moveHorizontal(true);
			moveVertical(true);
			moveHorizontal(true);
		}
		else {
			halfStairswalk = true;
		}
	}

	void goUpStairsLeft() {
		if (x > ladderLeftX) {
			moveHorizontal(false);
			moveVertical(true);
			moveHorizontal(false);
		}
		else {
			totalVerticalLvl += 1;
			halfStairswalk = false;
			y = 650 + 16 - totalVerticalLvl * 64; // correction coord y
		}
	}

	void goToApartment() {
		
		if (x < homeDoorX) {
			moveHorizontal(true);
		}
		else {
			if (totalVerticalLvl == homeIndex) {
				whatObjectNearby = 0;
			}
			else {
				whatObjectNearby = 9;
			}
			visible = false;
		}
	}


	// getters ------------
	int getId() {
		return id;
	}

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

	int getWhatObjectNearby() {
		return whatObjectNearby;
	}
	int getTargetPlaceIndex() {
		return targetPlaceIndex;
	}
	int getHomeIndex() {
		return homeIndex;
	}
};

