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
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void);

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
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
	private: System::Windows::Forms::Label^ PeopleCountLable;








	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
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
			this->PeopleCountLable = (gcnew System::Windows::Forms::Label());
			this->weatherLabel = (gcnew System::Windows::Forms::Label());
			this->partOfDayLabel = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->elevatorHumansIdLabel = (gcnew System::Windows::Forms::Label());
			this->elevatorPeopleInLabel = (gcnew System::Windows::Forms::Label());
			this->elevatorHumansLabel = (gcnew System::Windows::Forms::Label());
			this->elevatorCallsLabel = (gcnew System::Windows::Forms::Label());
			this->elevatorLvlLabel = (gcnew System::Windows::Forms::Label());
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
			this->timeGroupBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->timeGroupBox->Location = System::Drawing::Point(576, 12);
			this->timeGroupBox->Name = L"timeGroupBox";
			this->timeGroupBox->Size = System::Drawing::Size(275, 123);
			this->timeGroupBox->TabIndex = 1;
			this->timeGroupBox->TabStop = false;
			this->timeGroupBox->Text = L"Информация о времени";
			// 
			// TimerStartStopBtn
			// 
			this->TimerStartStopBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->TimerStartStopBtn->Location = System::Drawing::Point(14, 89);
			this->TimerStartStopBtn->Name = L"TimerStartStopBtn";
			this->TimerStartStopBtn->Size = System::Drawing::Size(239, 30);
			this->TimerStartStopBtn->TabIndex = 2;
			this->TimerStartStopBtn->Text = L"Начать / Пауза";
			this->TimerStartStopBtn->UseVisualStyleBackColor = true;
			this->TimerStartStopBtn->Click += gcnew System::EventHandler(this, &MyForm::TimerStartStopBtn_Click);
			// 
			// dateInfoLabel
			// 
			this->dateInfoLabel->AutoSize = true;
			this->dateInfoLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->dateInfoLabel->Location = System::Drawing::Point(6, 29);
			this->dateInfoLabel->Name = L"dateInfoLabel";
			this->dateInfoLabel->Size = System::Drawing::Size(232, 16);
			this->dateInfoLabel->TabIndex = 1;
			this->dateInfoLabel->Text = L"Прошло дней с начала симуляции:";
			this->dateInfoLabel->Click += gcnew System::EventHandler(this, &MyForm::dateInfoLabel_Click);
			// 
			// timeInfoLabel
			// 
			this->timeInfoLabel->AutoSize = true;
			this->timeInfoLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->timeInfoLabel->Location = System::Drawing::Point(8, 56);
			this->timeInfoLabel->Name = L"timeInfoLabel";
			this->timeInfoLabel->Size = System::Drawing::Size(111, 16);
			this->timeInfoLabel->TabIndex = 0;
			this->timeInfoLabel->Text = L"Текущее время:";
			// 
			// timeTrackBar
			// 
			this->timeTrackBar->LargeChange = 1;
			this->timeTrackBar->Location = System::Drawing::Point(576, 155);
			this->timeTrackBar->Maximum = 5;
			this->timeTrackBar->Minimum = 1;
			this->timeTrackBar->Name = L"timeTrackBar";
			this->timeTrackBar->Size = System::Drawing::Size(275, 45);
			this->timeTrackBar->TabIndex = 2;
			this->timeTrackBar->Value = 3;
			this->timeTrackBar->Scroll += gcnew System::EventHandler(this, &MyForm::timeTrackBar_Scroll);
			// 
			// weatherGroupBox
			// 
			this->weatherGroupBox->Controls->Add(this->PeopleCountLable);
			this->weatherGroupBox->Controls->Add(this->weatherLabel);
			this->weatherGroupBox->Controls->Add(this->partOfDayLabel);
			this->weatherGroupBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->weatherGroupBox->Location = System::Drawing::Point(576, 206);
			this->weatherGroupBox->Name = L"weatherGroupBox";
			this->weatherGroupBox->Size = System::Drawing::Size(275, 131);
			this->weatherGroupBox->TabIndex = 3;
			this->weatherGroupBox->TabStop = false;
			this->weatherGroupBox->Text = L"Окружающая среда";
			// 
			// PeopleCountLable
			// 
			this->PeopleCountLable->AutoSize = true;
			this->PeopleCountLable->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->PeopleCountLable->Location = System::Drawing::Point(8, 88);
			this->PeopleCountLable->Name = L"PeopleCountLable";
			this->PeopleCountLable->Size = System::Drawing::Size(179, 16);
			this->PeopleCountLable->TabIndex = 4;
			this->PeopleCountLable->Text = L"Общее количество людей:";
			// 
			// weatherLabel
			// 
			this->weatherLabel->AutoSize = true;
			this->weatherLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->weatherLabel->Location = System::Drawing::Point(8, 57);
			this->weatherLabel->Name = L"weatherLabel";
			this->weatherLabel->Size = System::Drawing::Size(116, 16);
			this->weatherLabel->TabIndex = 3;
			this->weatherLabel->Text = L"Текущая погода:";
			// 
			// partOfDayLabel
			// 
			this->partOfDayLabel->AutoSize = true;
			this->partOfDayLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->partOfDayLabel->Location = System::Drawing::Point(7, 29);
			this->partOfDayLabel->Name = L"partOfDayLabel";
			this->partOfDayLabel->Size = System::Drawing::Size(151, 16);
			this->partOfDayLabel->TabIndex = 3;
			this->partOfDayLabel->Text = L"Текущее время суток:";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->elevatorHumansIdLabel);
			this->groupBox1->Controls->Add(this->elevatorPeopleInLabel);
			this->groupBox1->Controls->Add(this->elevatorHumansLabel);
			this->groupBox1->Controls->Add(this->elevatorCallsLabel);
			this->groupBox1->Controls->Add(this->elevatorLvlLabel);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox1->Location = System::Drawing::Point(576, 360);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(275, 61);
			this->groupBox1->TabIndex = 4;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Информация о лифте";
			// 
			// elevatorHumansIdLabel
			// 
			this->elevatorHumansIdLabel->AutoSize = true;
			this->elevatorHumansIdLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->elevatorHumansIdLabel->Location = System::Drawing::Point(11, 97);
			this->elevatorHumansIdLabel->Name = L"elevatorHumansIdLabel";
			this->elevatorHumansIdLabel->Size = System::Drawing::Size(0, 16);
			this->elevatorHumansIdLabel->TabIndex = 8;
			// 
			// elevatorPeopleInLabel
			// 
			this->elevatorPeopleInLabel->AutoSize = true;
			this->elevatorPeopleInLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->elevatorPeopleInLabel->Location = System::Drawing::Point(11, 120);
			this->elevatorPeopleInLabel->Name = L"elevatorPeopleInLabel";
			this->elevatorPeopleInLabel->Size = System::Drawing::Size(0, 16);
			this->elevatorPeopleInLabel->TabIndex = 7;
			// 
			// elevatorHumansLabel
			// 
			this->elevatorHumansLabel->AutoSize = true;
			this->elevatorHumansLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->elevatorHumansLabel->Location = System::Drawing::Point(11, 76);
			this->elevatorHumansLabel->Name = L"elevatorHumansLabel";
			this->elevatorHumansLabel->Size = System::Drawing::Size(0, 16);
			this->elevatorHumansLabel->TabIndex = 6;
			// 
			// elevatorCallsLabel
			// 
			this->elevatorCallsLabel->AutoSize = true;
			this->elevatorCallsLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->elevatorCallsLabel->Location = System::Drawing::Point(11, 54);
			this->elevatorCallsLabel->Name = L"elevatorCallsLabel";
			this->elevatorCallsLabel->Size = System::Drawing::Size(0, 16);
			this->elevatorCallsLabel->TabIndex = 5;
			// 
			// elevatorLvlLabel
			// 
			this->elevatorLvlLabel->AutoSize = true;
			this->elevatorLvlLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->elevatorLvlLabel->Location = System::Drawing::Point(11, 30);
			this->elevatorLvlLabel->Name = L"elevatorLvlLabel";
			this->elevatorLvlLabel->Size = System::Drawing::Size(181, 16);
			this->elevatorLvlLabel->TabIndex = 4;
			this->elevatorLvlLabel->Text = L"Лифт находится на этаже: ";
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
		String^ getPerettyTime(String^ h, String^ m);
		System::Void TimerStartStopBtn_Click(System::Object^ sender, System::EventArgs^ e);

		System::Void timeTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e);
private: System::Void dateInfoLabel_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
