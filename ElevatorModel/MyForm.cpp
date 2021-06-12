#include "MyForm.h"
#include <iostream>
#include <ctime>
#using <system.drawing.dll>
using namespace ElevatorModel;
using namespace Drawing;

[STAThreadAttribute]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	ElevatorModel::MyForm form;
	Application::Run(% form);
}

MyForm::MyForm(void)
{
	//delegeteWeather = gcnew ChangeWeatherInfo(this, &ElevatorModel::MyForm::ChangeInformation);
	InitializeComponent();
	mainTimer = gcnew MainTimer();
	env = gcnew Enviroment();
	MainTimer::OnHourChange += gcnew HourChangeHandler(this, &ElevatorModel::MyForm::ChangeBackgroundImg);
	MainTimer::OnMinChange += gcnew MinChangeHandler(this, &ElevatorModel::MyForm::ChangeInformation);
	
	 
}

void MyForm::InvokeSetText(Label^ label, String^ text) {
	label->Text = text;
}

void MyForm::InvokeSetImage(PictureBox^ pictureBox, Image^ img) {
	pictureBox->Image = img;
}

void MyForm::ChangeBackgroundImg(int currentHour) {
	Image^ img = env->GetCurrentImage();
	String^ temp1 = "Current weather: " + env->GetEnviromentView()->Split(' ')[1];
	String^ temp2 = "Current part of day: " + env->GetEnviromentView()->Split(' ')[0];
	mainBackground->BeginInvoke(gcnew ChangePictureBoxImage(this, &MyForm::InvokeSetImage), mainBackground, img);
	weatherLabel->BeginInvoke(gcnew ChangeTextBoxValue(this, &MyForm::InvokeSetText), weatherLabel, temp1);
	partOfDayLabel->BeginInvoke(gcnew ChangeTextBoxValue(this, &MyForm::InvokeSetText), partOfDayLabel, temp2);
	
}

void MyForm::ChangeInformation() {
	String^ tempData = mainTimer->GetTimeInfo();
	String^ tempData1 = "Current time: " + tempData->Split(' ')[1] + ":" + tempData->Split(' ')[2];
	String^ tempData2 = "Days late: " + tempData->Split(' ')[0];
	timeInfoLabel->BeginInvoke(gcnew ChangeTextBoxValue(this, &MyForm::InvokeSetText), timeInfoLabel, tempData1);
	dateInfoLabel->BeginInvoke(gcnew ChangeTextBoxValue(this, &MyForm::InvokeSetText), dateInfoLabel, tempData2);
}

System::Void MyForm::TimerStartStopBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	if (mainTimer->IsFirstRun()) {
		timerThread = gcnew Thread(gcnew ThreadStart(mainTimer, &MainTimer::RunTimer));
		timerThread->Start();
	}
	else {
		if (mainTimer->IsRunning()) {
			mainTimer->StopTimer();
		}
		else {
			timerThread = gcnew Thread(gcnew ThreadStart(mainTimer, &MainTimer::RunTimer));
			timerThread->Start();
		}
	}
	
}

System::Void MyForm::timeTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
	if (timeTrackBar->Value == 1) {
		mainTimer->SetTimeSpeed(10, 50);
	}
	if (timeTrackBar->Value == 2) {
		mainTimer->SetTimeSpeed(30, 50);
	}
	if (timeTrackBar->Value == 3) {
		mainTimer->SetTimeSpeed(90, 50);
	}
	if (timeTrackBar->Value == 4) {
		mainTimer->SetTimeSpeed(90, 25);
	}
	if (timeTrackBar->Value == 5) {
		mainTimer->SetTimeSpeed(90, 10);
	}
	if (mainTimer->IsRunning()) {
		timerThread->Abort();
		timerThread = gcnew Thread(gcnew ThreadStart(mainTimer, &MainTimer::RunTimer));
		timerThread->Start();
	}
	
	
}