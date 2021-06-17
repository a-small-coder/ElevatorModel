#pragma once
#include "Human.h"
#include "MainTimer.h"
#include "Enviroment.h"
#include "Elevator.h"
namespace ElevatorModel {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Threading;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void);

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ mainBackground;
	private: System::Windows::Forms::GroupBox^ timeGroupBox;

	protected:

	protected:

	private: System::Windows::Forms::Button^ TimerStartStopBtn;
	private: System::Windows::Forms::Label^ dateInfoLabel;
	private: System::Windows::Forms::Label^ timeInfoLabel;
	private: System::Windows::Forms::TrackBar^ timeTrackBar;
	private: System::Windows::Forms::GroupBox^ weatherGroupBox;
	private: System::Windows::Forms::Label^ weatherLabel;



	private: System::Windows::Forms::Label^ partOfDayLabel;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Label^ elevatorLvlLabel;
	private: System::Windows::Forms::Label^ elevatorCallsLabel;
	private: System::Windows::Forms::Label^ elevatorHumansLabel;
	private: System::Windows::Forms::Label^ elevatorPeopleInLabel;
	private: System::Windows::Forms::Label^ elevatorHumansIdLabel;








	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->mainBackground = (gcnew System::Windows::Forms::PictureBox());
			this->timeGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->TimerStartStopBtn = (gcnew System::Windows::Forms::Button());
			this->dateInfoLabel = (gcnew System::Windows::Forms::Label());
			this->timeInfoLabel = (gcnew System::Windows::Forms::Label());
			this->timeTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->weatherGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->weatherLabel = (gcnew System::Windows::Forms::Label());
			this->partOfDayLabel = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->elevatorHumansLabel = (gcnew System::Windows::Forms::Label());
			this->elevatorCallsLabel = (gcnew System::Windows::Forms::Label());
			this->elevatorLvlLabel = (gcnew System::Windows::Forms::Label());
			this->elevatorPeopleInLabel = (gcnew System::Windows::Forms::Label());
			this->elevatorHumansIdLabel = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mainBackground))->BeginInit();
			this->timeGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->timeTrackBar))->BeginInit();
			this->weatherGroupBox->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// mainBackground
			// 
			this->mainBackground->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"mainBackground.Image")));
			this->mainBackground->Location = System::Drawing::Point(-5, -9);
			this->mainBackground->Name = L"mainBackground";
			this->mainBackground->Size = System::Drawing::Size(557, 750);
			this->mainBackground->TabIndex = 0;
			this->mainBackground->TabStop = false;
			// 
			// timeGroupBox
			// 
			this->timeGroupBox->Controls->Add(this->TimerStartStopBtn);
			this->timeGroupBox->Controls->Add(this->dateInfoLabel);
			this->timeGroupBox->Controls->Add(this->timeInfoLabel);
			this->timeGroupBox->Location = System::Drawing::Point(592, 13);
			this->timeGroupBox->Name = L"timeGroupBox";
			this->timeGroupBox->Size = System::Drawing::Size(259, 100);
			this->timeGroupBox->TabIndex = 1;
			this->timeGroupBox->TabStop = false;
			this->timeGroupBox->Text = L"Time info";
			// 
			// TimerStartStopBtn
			// 
			this->TimerStartStopBtn->Location = System::Drawing::Point(9, 72);
			this->TimerStartStopBtn->Name = L"TimerStartStopBtn";
			this->TimerStartStopBtn->Size = System::Drawing::Size(171, 23);
			this->TimerStartStopBtn->TabIndex = 2;
			this->TimerStartStopBtn->Text = L"Start/Stop";
			this->TimerStartStopBtn->UseVisualStyleBackColor = true;
			this->TimerStartStopBtn->Click += gcnew System::EventHandler(this, &MyForm::TimerStartStopBtn_Click);
			// 
			// dateInfoLabel
			// 
			this->dateInfoLabel->AutoSize = true;
			this->dateInfoLabel->Location = System::Drawing::Point(6, 25);
			this->dateInfoLabel->Name = L"dateInfoLabel";
			this->dateInfoLabel->Size = System::Drawing::Size(68, 13);
			this->dateInfoLabel->TabIndex = 1;
			this->dateInfoLabel->Text = L"Current date:";
			// 
			// timeInfoLabel
			// 
			this->timeInfoLabel->AutoSize = true;
			this->timeInfoLabel->Location = System::Drawing::Point(7, 46);
			this->timeInfoLabel->Name = L"timeInfoLabel";
			this->timeInfoLabel->Size = System::Drawing::Size(66, 13);
			this->timeInfoLabel->TabIndex = 0;
			this->timeInfoLabel->Text = L"Current time:";
			// 
			// timeTrackBar
			// 
			this->timeTrackBar->LargeChange = 1;
			this->timeTrackBar->Location = System::Drawing::Point(601, 131);
			this->timeTrackBar->Maximum = 5;
			this->timeTrackBar->Minimum = 1;
			this->timeTrackBar->Name = L"timeTrackBar";
			this->timeTrackBar->Size = System::Drawing::Size(250, 45);
			this->timeTrackBar->TabIndex = 2;
			this->timeTrackBar->Value = 3;
			this->timeTrackBar->Scroll += gcnew System::EventHandler(this, &MyForm::timeTrackBar_Scroll);
			// 
			// weatherGroupBox
			// 
			this->weatherGroupBox->Controls->Add(this->weatherLabel);
			this->weatherGroupBox->Controls->Add(this->partOfDayLabel);
			this->weatherGroupBox->Location = System::Drawing::Point(592, 183);
			this->weatherGroupBox->Name = L"weatherGroupBox";
			this->weatherGroupBox->Size = System::Drawing::Size(259, 100);
			this->weatherGroupBox->TabIndex = 3;
			this->weatherGroupBox->TabStop = false;
			this->weatherGroupBox->Text = L"Weather";
			// 
			// weatherLabel
			// 
			this->weatherLabel->AutoSize = true;
			this->weatherLabel->Location = System::Drawing::Point(8, 57);
			this->weatherLabel->Name = L"weatherLabel";
			this->weatherLabel->Size = System::Drawing::Size(85, 13);
			this->weatherLabel->TabIndex = 3;
			this->weatherLabel->Text = L"Current weather:";
			// 
			// partOfDayLabel
			// 
			this->partOfDayLabel->AutoSize = true;
			this->partOfDayLabel->Location = System::Drawing::Point(7, 29);
			this->partOfDayLabel->Name = L"partOfDayLabel";
			this->partOfDayLabel->Size = System::Drawing::Size(97, 13);
			this->partOfDayLabel->TabIndex = 3;
			this->partOfDayLabel->Text = L"Current part of day:";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->elevatorHumansIdLabel);
			this->groupBox1->Controls->Add(this->elevatorPeopleInLabel);
			this->groupBox1->Controls->Add(this->elevatorHumansLabel);
			this->groupBox1->Controls->Add(this->elevatorCallsLabel);
			this->groupBox1->Controls->Add(this->elevatorLvlLabel);
			this->groupBox1->Location = System::Drawing::Point(592, 305);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(259, 153);
			this->groupBox1->TabIndex = 4;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Elevator info";
			// 
			// elevatorHumansLabel
			// 
			this->elevatorHumansLabel->AutoSize = true;
			this->elevatorHumansLabel->Location = System::Drawing::Point(11, 76);
			this->elevatorHumansLabel->Name = L"elevatorHumansLabel";
			this->elevatorHumansLabel->Size = System::Drawing::Size(13, 13);
			this->elevatorHumansLabel->TabIndex = 6;
			this->elevatorHumansLabel->Text = L"h";
			// 
			// elevatorCallsLabel
			// 
			this->elevatorCallsLabel->AutoSize = true;
			this->elevatorCallsLabel->Location = System::Drawing::Point(11, 54);
			this->elevatorCallsLabel->Name = L"elevatorCallsLabel";
			this->elevatorCallsLabel->Size = System::Drawing::Size(28, 13);
			this->elevatorCallsLabel->TabIndex = 5;
			this->elevatorCallsLabel->Text = L"calls";
			// 
			// elevatorLvlLabel
			// 
			this->elevatorLvlLabel->AutoSize = true;
			this->elevatorLvlLabel->Location = System::Drawing::Point(11, 30);
			this->elevatorLvlLabel->Name = L"elevatorLvlLabel";
			this->elevatorLvlLabel->Size = System::Drawing::Size(98, 13);
			this->elevatorLvlLabel->TabIndex = 4;
			this->elevatorLvlLabel->Text = L"Current elevator lvl:";
			// 
			// elevatorPeopleInLabel
			// 
			this->elevatorPeopleInLabel->AutoSize = true;
			this->elevatorPeopleInLabel->Location = System::Drawing::Point(11, 120);
			this->elevatorPeopleInLabel->Name = L"elevatorPeopleInLabel";
			this->elevatorPeopleInLabel->Size = System::Drawing::Size(50, 13);
			this->elevatorPeopleInLabel->TabIndex = 7;
			this->elevatorPeopleInLabel->Text = L"people in";
			// 
			// elevatorHumansIdLabel
			// 
			this->elevatorHumansIdLabel->AutoSize = true;
			this->elevatorHumansIdLabel->Location = System::Drawing::Point(11, 97);
			this->elevatorHumansIdLabel->Name = L"elevatorHumansIdLabel";
			this->elevatorHumansIdLabel->Size = System::Drawing::Size(24, 13);
			this->elevatorHumansIdLabel->TabIndex = 8;
			this->elevatorHumansIdLabel->Text = L"h id";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(863, 711);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->weatherGroupBox);
			this->Controls->Add(this->timeTrackBar);
			this->Controls->Add(this->timeGroupBox);
			this->Controls->Add(this->mainBackground);
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mainBackground))->EndInit();
			this->timeGroupBox->ResumeLayout(false);
			this->timeGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->timeTrackBar))->EndInit();
			this->weatherGroupBox->ResumeLayout(false);
			this->weatherGroupBox->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
public:
	delegate void ChangeTextBoxValue(Label^ label, String^ text);
	delegate void ChangePictureBoxImage(PictureBox^ txtBox, Image^ img, bool visible);
	delegate void ChangePictureBoxLocation(PictureBox^ pictBox, Point^ point);
	delegate void InitialazePictureBox(PictureBox^ pictBox, Human^ human);
	delegate void ChangePictureBoxDimentions(PictureBox^ pictBox, Rectangle^ dim);

private:
		MainTimer^ mainTimer;
		Thread^ timerThread;
		Enviroment^ env;
		Elevator^ elevator;
		array<PictureBox^>^ humansPictures;
		PictureBox^ elevatorPicture;
		void Paint();
		void SubscribeOnHumans();
		void SetDimentionsPB(int id);
		void InvokeSetDimentionsPB(PictureBox^ pictBox, Rectangle^ dim);
		void InitPictureBox(PictureBox^ pictBox, Human^ hum);
		void InitPictureBox(PictureBox^ pictBox, Elevator^ hum);
		void InitializeCitizens(array<Human^>^ humans);
		void PaintElevator(Elevator^ elev);
		void PaintHumans(array<Human^>^ humans);
		void InvokeSetLocation(PictureBox^ pictureBox, Point^ point);
		void InvokeSetText(Label^ label, String^ text);
		void InvokeSetImage(PictureBox^ pictureBox, Image^ img, bool visible);
		void ChangeBackgroundImg(int currentHour);
		void ChangeInformation();
		System::Void TimerStartStopBtn_Click(System::Object^ sender, System::EventArgs^ e);

		System::Void timeTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e);
};
}
