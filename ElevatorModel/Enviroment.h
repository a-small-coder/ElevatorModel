#include "MainTimer.h"
#include <iostream>
#include <ctime>
#using <system.drawing.dll>
using namespace System::Drawing;
using namespace System::Collections::Generic;

ref class Enviroment
{
private:
	int rrand(int range_min, int range_max) {
		return rand() % (range_max - range_min + 1) + range_min;
	}
	static Image^ dayClearImg;
	static Image^ dayRainImg;
	static Image^ dayStormImg;

	static Image^ morningClearImg;
	static Image^ morningRainImg;
	static Image^ morningStormImg;

	static Image^ eveningClearImg;
	static Image^ eveningRainImg;
	static Image^ eveningStormImg;

	static Image^ nightClearImg;
	static Image^ nightRainImg;
	static Image^ nightStormImg;
	Image^ currentImg;
	const int CHANCE = 1;
	int weatherUpVal;
	int weatherDownVal;
	int coutnWeatherTypes = 3;
	static Dictionary<String^, Image^>^ dict = dictInitializer();
	String^ enviromentView;
	String^ dayType;
	String^ weatherType;


public:

	Enviroment() {
		srand(static_cast<unsigned int>(time(NULL)));
		weatherUpVal = 2;
		weatherDownVal = 0;
		MainTimer::OnHourChange += gcnew HourChangeHandler(this, &Enviroment::SetEnviromentView);
		currentImg = dayClearImg;
		dayType = "Утро";
		weatherType = "Ясно";
		enviromentView = dayType + " " + weatherType;
	}

	static Dictionary<String^, Image^>^ dictInitializer() {
		LoadImage();
		Dictionary<String^, Image^>^ dict = gcnew Dictionary<String^, Image^>;
		dict->Add("Утро Ясно", morningClearImg);
		dict->Add("Утро Дождь", morningRainImg);
		dict->Add("Утро Гроза", morningStormImg);

		dict->Add("День Ясно", dayClearImg);
		dict->Add("День Дождь", dayRainImg);
		dict->Add("День Гроза", dayStormImg);

		dict->Add("Вечер Ясно", eveningClearImg);
		dict->Add("Вечер Дождь", eveningRainImg);
		dict->Add("Вечер Гроза", eveningStormImg);

		dict->Add("Ночь Ясно", nightClearImg);
		dict->Add("Ночь Дождь", nightRainImg);
		dict->Add("Ночь Гроза", nightStormImg);
		return dict;
	}

	static void LoadImage() {
		morningClearImg = Image::FromFile("img\\building9MorningClear.png");
		morningRainImg = Image::FromFile("img\\building9MorningRain.png");
		morningStormImg = Image::FromFile("img\\building9MorningStorm.png");

		dayClearImg = Image::FromFile("img\\building9DayClear.png");
		dayRainImg = Image::FromFile("img\\building9DayRain.png");
		dayStormImg = Image::FromFile("img\\building9DayStorm.png");

		eveningClearImg = Image::FromFile("img\\building9EveningClear.png");
		eveningRainImg = Image::FromFile("img\\building9EveningRain.png");
		eveningStormImg = Image::FromFile("img\\building9EveningStorm.png");

		nightClearImg = Image::FromFile("img\\building9NightClear.png");
		nightRainImg = Image::FromFile("img\\building9NightRain.png");
		nightStormImg = Image::FromFile("img\\building9NightStorm.png");
	}

	void SetEnviromentView(int currentHour) {
		enviromentView = createEnviromentView(currentHour);
		currentImg = dict[enviromentView];
	}

	String^ createEnviromentView(int currentHour) {
		if (currentHour % 6 == 0) {
			if (currentHour == 6) {
				dayType = "Утро";
			}
			if (currentHour == 12) {
				dayType = "День";
			}
			if (currentHour == 18) {
				dayType = "Вечер";
			}
			if (currentHour == 24) {
				dayType = "Ночь";
			}
		}
		
		int diceVal = rrand(1, 3);
		if (CHANCE == diceVal) {
			diceVal = rrand(1, 4);
			if (diceVal % 3 == 1) {
				weatherType = "Ясно";
			}
			if (diceVal % 3 == 2) {
				weatherType = "Дождь";
			}
			if (diceVal % 3 == 0) {
				weatherType = "Гроза";
			}
		}
		return dayType + " " + weatherType;

	}

	Image^ GetCurrentImage() {
		return currentImg;
	}

	String^ GetEnviromentView() {
		return enviromentView;
	}
};

