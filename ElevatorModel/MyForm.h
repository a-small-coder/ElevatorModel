#pragma once
#include "MainTimer.h"
#include "Enviroment.h"
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
	protected:

	protected:
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Button^ TimerStartStopBtn;
	private: System::Windows::Forms::Label^ dateInfoLabel;
	private: System::Windows::Forms::Label^ timeInfoLabel;
	private: System::Windows::Forms::TrackBar^ timeTrackBar;





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
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->TimerStartStopBtn = (gcnew System::Windows::Forms::Button());
			this->dateInfoLabel = (gcnew System::Windows::Forms::Label());
			this->timeInfoLabel = (gcnew System::Windows::Forms::Label());
			this->timeTrackBar = (gcnew System::Windows::Forms::TrackBar());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mainBackground))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->timeTrackBar))->BeginInit();
			this->SuspendLayout();
			// 
			// mainBackground
			// 
			this->mainBackground->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"mainBackground.Image")));
			this->mainBackground->Location = System::Drawing::Point(0, -39);
			this->mainBackground->Name = L"mainBackground";
			this->mainBackground->Size = System::Drawing::Size(585, 750);
			this->mainBackground->TabIndex = 0;
			this->mainBackground->TabStop = false;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->TimerStartStopBtn);
			this->groupBox1->Controls->Add(this->dateInfoLabel);
			this->groupBox1->Controls->Add(this->timeInfoLabel);
			this->groupBox1->Location = System::Drawing::Point(592, 13);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(185, 100);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Time info";
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
			this->timeTrackBar->Size = System::Drawing::Size(171, 45);
			this->timeTrackBar->TabIndex = 2;
			this->timeTrackBar->Value = 3;
			this->timeTrackBar->Scroll += gcnew System::EventHandler(this, &MyForm::timeTrackBar_Scroll);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 711);
			this->Controls->Add(this->timeTrackBar);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->mainBackground);
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mainBackground))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->timeTrackBar))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		MainTimer^ mainTimer;
		Thread^ timerThread;
		Enviroment^ env;
		void ChangeBackgroundImg(int currentHour);
		void ChangeInformation();
		System::Void TimerStartStopBtn_Click(System::Object^ sender, System::EventArgs^ e);

		System::Void timeTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e);
};
}
