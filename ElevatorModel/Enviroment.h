#include "MainTimer.h"
#using <system.drawing.dll>
using namespace System::Drawing;

ref class Enviroment
{
private:
	Image^ dayImg;
	Image^ nightImg;
	Image^ currentImg;

public:

	Enviroment() {
		LoadImage();
		MainTimer::OnHourChange += gcnew HourChangeHandler(this, &Enviroment::ChangeWeather);
		currentImg = dayImg;
	}

	void LoadImage() {
		dayImg = Image::FromFile("img\\building9.png");
		nightImg = Image::FromFile("img\\building9Night.png");
	}

	void ChangeWeather(int currentHour) {
		if (currentHour == 19) {
			currentImg = nightImg;
		}
		if (currentHour == 7) {
			currentImg = dayImg;
		}
	}

	Image^ GetCurrentImage() {
		return currentImg;
	}

};

