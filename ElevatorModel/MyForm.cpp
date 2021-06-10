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
	InitializeComponent();
	mainTimer = gcnew MainTimer();
	env = gcnew Enviroment();
	MainTimer::OnHourChange += gcnew HourChangeHandler(this, &ElevatorModel::MyForm::ChangeBackgroundImg);
	MainTimer::OnMinChange += gcnew MinChangeHandler(this, &ElevatorModel::MyForm::ChangeInformation);
	
	 
}

void MyForm::ChangeBackgroundImg(int currentHour) {
	mainBackground->Image = env->GetCurrentImage();
}

void MyForm::ChangeInformation() {
	String^ tempData = mainTimer->GetTimeInfo();
	timeInfoLabel->Text = "Current time: " + tempData->Split(' ')[1] + ":" + tempData->Split(' ')[2];
	dateInfoLabel->Text = "Days late: " + tempData->Split(' ')[0];
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