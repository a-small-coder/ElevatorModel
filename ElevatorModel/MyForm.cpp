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
	elevator = gcnew Elevator();
	elevatorPicture = gcnew PictureBox();
	InitPictureBox(elevatorPicture, elevator);
	env->createCitizens(5);
	InitializeCitizens(env->getCitizens());
	MainTimer::OnHourChange += gcnew HourChangeHandler(this, &ElevatorModel::MyForm::ChangeBackgroundImg);
	MainTimer::OnMinChange += gcnew MinChangeHandler(this, &ElevatorModel::MyForm::ChangeInformation);
	MainTimer::OnMinChange += gcnew MinChangeHandler(this, &ElevatorModel::MyForm::Paint);
	SubscribeOnHumans();
	
	
	 
}

void MyForm::Paint() {
	PaintHumans(env->getCitizens());
	PaintElevator(elevator);
}

void MyForm::InitializeCitizens(array<Human^>^ humans) {
	humansPictures = gcnew array<PictureBox^, 1>(humans->Length);
	for (int i = 0; i < humans->Length; i++) {
		Rectangle^ dim = humans[i]->getDimentionsImg();
		PictureBox^ testHumanPB = gcnew PictureBox();
		InitPictureBox(testHumanPB, humans[i]);
		//testHumanPB->BeginInvoke(gcnew InitialazePictureBox(this, &MyForm::InitPictureBox), testHumanPB, humans[i]);
		humansPictures[i] = testHumanPB;
	}
}

void MyForm::SubscribeOnHumans() {
	array<Human^>^ humans = env->getCitizens();
	for (int i = 0; i < humans->Length; i++) {
		humans[i]->ChangePicture += gcnew ChangePictureHandler(this, &MyForm::SetDimentionsPB);
		elevator->OnElevatorEmbarkation += gcnew ElevatorEmbarkationHandler(humans[i], &Human::tryEmbarkation);
		humans[i]->EmbarkatedInElevator += gcnew EmbarkatedInElevatorHandler(elevator, &Elevator::acceptEmbarkation);
		elevator->DisEmbarkation += gcnew DisEmbarkationHandler(humans[i], &Human::disEmbarkation);
	}
}

void MyForm::SetDimentionsPB(int id) {
	id -= 1;
	Human^ hum = env->getCitizens()[id];
	Rectangle^ dim = hum->getDimentionsImg();
	humansPictures[id]->BeginInvoke(gcnew ChangePictureBoxDimentions(this, &MyForm::InvokeSetDimentionsPB), humansPictures[id], dim);
}

void MyForm::InvokeSetDimentionsPB(PictureBox^ picture, Rectangle^ dim) {
	picture->Width = dim->Width;
	picture->Height = dim->Height;
	picture->BringToFront();
}

void MyForm::InitPictureBox(PictureBox^ pictBox, Human^ hum) {
	Rectangle^ dim = hum->getDimentionsImg();
	pictBox->Width = dim->Width;
	pictBox->Height = dim->Height;
	pictBox->Location = Point(dim->X, dim->Y);
	pictBox->Visible = hum->isVisible();
	this->Controls->Add(pictBox);
	pictBox->BringToFront();
}

void MyForm::InitPictureBox(PictureBox^ pictBox, Elevator^ hum) {
	Rectangle^ dim = hum->getDimentionsImg();
	pictBox->Width = dim->Width;
	pictBox->Height = dim->Height;
	pictBox->Location = Point(dim->X, dim->Y);
	pictBox->Visible = hum->isVisible();
	this->Controls->Add(pictBox);
	pictBox->BringToFront();
}

void MyForm::PaintElevator(Elevator^ elev) {
	if (elev->isVisible()) {
		Rectangle^ dim = elev->getDimentionsImg();
		elevatorPicture->BeginInvoke(gcnew ChangePictureBoxImage(this, &MyForm::InvokeSetImage), elevatorPicture, elev->getImage(), elev->isVisible());
		elevatorPicture->BeginInvoke(gcnew ChangePictureBoxLocation(this, &MyForm::InvokeSetLocation), elevatorPicture, Point(dim->X, dim->Y));
	}
	else {
		elevatorPicture->BeginInvoke(gcnew ChangePictureBoxImage(this, &MyForm::InvokeSetImage), elevatorPicture, elev->getImage(), elev->isVisible());
	}
	
}

void MyForm::PaintHumans(array <Human^>^ humans) {
	for (int i = 0; i < humans->Length; i++) {
		if (humans[i]->isVisible()) {
			Rectangle^ dim = humans[i]->getDimentionsImg();
			humansPictures[i]->BeginInvoke(gcnew ChangePictureBoxImage(this, &MyForm::InvokeSetImage), humansPictures[i], humans[i]->getImage(), humans[i]->isVisible());
			humansPictures[i]->BeginInvoke(gcnew ChangePictureBoxLocation(this, &MyForm::InvokeSetLocation), humansPictures[i], Point(dim->X, dim->Y));
		}
		else {
			humansPictures[i]->BeginInvoke(gcnew ChangePictureBoxImage(this, &MyForm::InvokeSetImage), humansPictures[i], humans[i]->getImage(), humans[i]->isVisible());
		}
	}
}

void MyForm::InvokeSetLocation(PictureBox^ pictureBox, Point^ point) {
	pictureBox->Location = Point(point->X, point->Y);
}

void MyForm::InvokeSetText(Label^ label, String^ text) {
	label->Text = text;
}


void MyForm::InvokeSetImage(PictureBox^ pictureBox, Image^ img, bool visible) {
	pictureBox->Visible = visible;
	pictureBox->Image = img;
}

void MyForm::ChangeBackgroundImg(int currentHour) {
	Image^ img = env->GetCurrentImage();
	String^ temp1 = "Current weather: " + env->GetEnviromentView()->Split(' ')[1];
	String^ temp2 = "Current part of day: " + env->GetEnviromentView()->Split(' ')[0];
	mainBackground->BeginInvoke(gcnew ChangePictureBoxImage(this, &MyForm::InvokeSetImage), mainBackground, img, true);
	weatherLabel->BeginInvoke(gcnew ChangeTextBoxValue(this, &MyForm::InvokeSetText), weatherLabel, temp1);
	partOfDayLabel->BeginInvoke(gcnew ChangeTextBoxValue(this, &MyForm::InvokeSetText), partOfDayLabel, temp2);
	
}

void MyForm::ChangeInformation() {
	String^ elevatorHumansId = elevator->HumansInIdToString();
	String^ elevatorCalls = elevator->calledFloorsToString();
	String^ elevatorHumans = elevator->HumansInToString();
	String^ tempData = mainTimer->GetTimeInfo();
	String^ tempData1 = "Current time: " + tempData->Split(' ')[1] + ":" + tempData->Split(' ')[2];
	String^ tempData2 = "Days late: " + tempData->Split(' ')[0];
	String^ tempData3 = "Current elevator lvl: " + Convert::ToString(elevator->getTotalVerticalLvl());
	timeInfoLabel->BeginInvoke(gcnew ChangeTextBoxValue(this, &MyForm::InvokeSetText), timeInfoLabel, tempData1);
	dateInfoLabel->BeginInvoke(gcnew ChangeTextBoxValue(this, &MyForm::InvokeSetText), dateInfoLabel, tempData2);
	elevatorLvlLabel->BeginInvoke(gcnew ChangeTextBoxValue(this, &MyForm::InvokeSetText), elevatorLvlLabel, tempData3);
	elevatorCallsLabel->BeginInvoke(gcnew ChangeTextBoxValue(this, &MyForm::InvokeSetText), elevatorCallsLabel, elevatorCalls);
	elevatorHumansLabel->BeginInvoke(gcnew ChangeTextBoxValue(this, &MyForm::InvokeSetText), elevatorHumansLabel, elevatorHumans);
	elevatorHumansIdLabel->BeginInvoke(gcnew ChangeTextBoxValue(this, &MyForm::InvokeSetText), elevatorHumansIdLabel, elevatorHumansId);
	elevatorPeopleInLabel->BeginInvoke(gcnew ChangeTextBoxValue(this, &MyForm::InvokeSetText), elevatorPeopleInLabel, elevator->getPeopleIn());
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
		mainTimer->SetTimeSpeed(1080, 10);
	}
	if (mainTimer->IsRunning()) {
		timerThread->Abort();
		timerThread = gcnew Thread(gcnew ThreadStart(mainTimer, &MainTimer::RunTimer));
		timerThread->Start();
	}
	
	
}