#pragma once 
#include <typeinfo>
#include <iostream>
#include "ClientInterLayer.h"
namespace Client4 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Threading;
	using namespace std;

	ClientInterLayer client;
	/// <summary>
	/// ����� ��� ������ ������� � ��������. ���������� ����������� ������ InterLayer
	/// </summary>
	public ref class ClientForm : public System::Windows::Forms::Form
	{
	public:	String ^ IP;
	public:	Thread ^ th;
#pragma region ����������� ����� ����, ������ �����������
	public:	ClientForm(void)
	{
		InitializeComponent();
		//
		//TODO: �������� ��� ������������
		//
	}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~ClientForm()
		{
			client.Exit();
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabPage^  tabPageMessage;
	private: System::Windows::Forms::Button^  buttonLog;
	private: System::Windows::Forms::TextBox^  textBoxIP1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox_Log;
	private: System::Windows::Forms::Label^  labelMessages;
	private: System::Windows::Forms::TabPage^  tabPageDownload;
	private: System::Windows::Forms::GroupBox^  groupBoxDownload_Loading;
	private: System::Windows::Forms::Button^  buttonDownload_Pause;
	private: System::Windows::Forms::Button^  buttonDownload_Cancel;
	private: System::Windows::Forms::ProgressBar^  progressBarDownload_Loading;
	private: System::Windows::Forms::Button^  buttonDownload;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::ComboBox^  comboBoxDownloadFiles;
	private: System::Windows::Forms::TabPage^  tabPageUpload;
	private: System::Windows::Forms::GroupBox^  groupBoxUpload_Loading;
	private: System::Windows::Forms::Button^  buttonUpload_Pause;
	private: System::Windows::Forms::Button^  buttonUpload_Cancel;
	private: System::Windows::Forms::ProgressBar^  progressBarUpload_Loading;
	private: System::Windows::Forms::Button^  buttonUpload;
	private: System::Windows::Forms::GroupBox^  groupBoxUpload_Access;
	private: System::Windows::Forms::RadioButton^  radioButtonPublic;
	private: System::Windows::Forms::RadioButton^  radioButtonProtected;
	private: System::Windows::Forms::ListView^  listViewUpload_Names;
	private: System::Windows::Forms::RadioButton^  radioButtonPrivate;
	private: System::Windows::Forms::GroupBox^  groupBoxUpload_Puth;
	private: System::Windows::Forms::Button^  buttonUpload_FileDialog;
	private: System::Windows::Forms::Label^  labelUpload_Puth;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPageReupload;
	private: System::Windows::Forms::GroupBox^  groupBoxReupload_Loading;
	private: System::Windows::Forms::Button^  buttonReupload_Pause;
	private: System::Windows::Forms::Button^  buttonReupload_Cancel;
	private: System::Windows::Forms::ProgressBar^  progressBarReupload_Loading;
	private: System::Windows::Forms::Button^  buttonReupload;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::ComboBox^  comboBoxReupload;
	private: System::Windows::Forms::TextBox^  textBoxIP2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBoxIP4;
	private: System::Windows::Forms::TextBox^  textBoxIP3;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  buttonConnect;
	private: System::Windows::Forms::Button^  buttonHome;
	private: System::Windows::Forms::ImageList^  imageListLog;
	private: System::Windows::Forms::ImageList^  imageListPlay;
	private: System::Windows::Forms::ImageList^  imageListHome;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::Label^  label6;
	private: System::ComponentModel::IContainer^  components;

			 /// <summary>
			 /// ������������ ���������� ������������.
			 /// </summary>
#pragma endregion

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ClientForm::typeid));
				 System::Windows::Forms::ListViewItem^  listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(L"1"));
				 System::Windows::Forms::ListViewItem^  listViewItem2 = (gcnew System::Windows::Forms::ListViewItem(L"10"));
				 System::Windows::Forms::ListViewItem^  listViewItem3 = (gcnew System::Windows::Forms::ListViewItem(L"10"));
				 System::Windows::Forms::ListViewItem^  listViewItem4 = (gcnew System::Windows::Forms::ListViewItem(L"11"));
				 System::Windows::Forms::ListViewItem^  listViewItem5 = (gcnew System::Windows::Forms::ListViewItem(L"11"));
				 System::Windows::Forms::ListViewItem^  listViewItem6 = (gcnew System::Windows::Forms::ListViewItem(L"12"));
				 System::Windows::Forms::ListViewItem^  listViewItem7 = (gcnew System::Windows::Forms::ListViewItem(L"12"));
				 System::Windows::Forms::ListViewItem^  listViewItem8 = (gcnew System::Windows::Forms::ListViewItem(L"14"));
				 System::Windows::Forms::ListViewItem^  listViewItem9 = (gcnew System::Windows::Forms::ListViewItem(L"14"));
				 System::Windows::Forms::ListViewItem^  listViewItem10 = (gcnew System::Windows::Forms::ListViewItem(L"15"));
				 System::Windows::Forms::ListViewItem^  listViewItem11 = (gcnew System::Windows::Forms::ListViewItem(L"16"));
				 System::Windows::Forms::ListViewItem^  listViewItem12 = (gcnew System::Windows::Forms::ListViewItem(L"2"));
				 System::Windows::Forms::ListViewItem^  listViewItem13 = (gcnew System::Windows::Forms::ListViewItem(L"3"));
				 System::Windows::Forms::ListViewItem^  listViewItem14 = (gcnew System::Windows::Forms::ListViewItem(L"4"));
				 System::Windows::Forms::ListViewItem^  listViewItem15 = (gcnew System::Windows::Forms::ListViewItem(L"5"));
				 System::Windows::Forms::ListViewItem^  listViewItem16 = (gcnew System::Windows::Forms::ListViewItem(L"6"));
				 System::Windows::Forms::ListViewItem^  listViewItem17 = (gcnew System::Windows::Forms::ListViewItem(L"7"));
				 System::Windows::Forms::ListViewItem^  listViewItem18 = (gcnew System::Windows::Forms::ListViewItem(L"8"));
				 System::Windows::Forms::ListViewItem^  listViewItem19 = (gcnew System::Windows::Forms::ListViewItem(L"9"));
				 System::Windows::Forms::ListViewItem^  listViewItem20 = (gcnew System::Windows::Forms::ListViewItem(L"������� 13"));
				 this->buttonLog = (gcnew System::Windows::Forms::Button());
				 this->imageListLog = (gcnew System::Windows::Forms::ImageList(this->components));
				 this->textBoxIP1 = (gcnew System::Windows::Forms::TextBox());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->textBoxIP2 = (gcnew System::Windows::Forms::TextBox());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->textBoxIP4 = (gcnew System::Windows::Forms::TextBox());
				 this->textBoxIP3 = (gcnew System::Windows::Forms::TextBox());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->label4 = (gcnew System::Windows::Forms::Label());
				 this->buttonConnect = (gcnew System::Windows::Forms::Button());
				 this->imageListPlay = (gcnew System::Windows::Forms::ImageList(this->components));
				 this->buttonHome = (gcnew System::Windows::Forms::Button());
				 this->imageListHome = (gcnew System::Windows::Forms::ImageList(this->components));
				 this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
				 this->label5 = (gcnew System::Windows::Forms::Label());
				 this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
				 this->label6 = (gcnew System::Windows::Forms::Label());
				 this->tabPageMessage = (gcnew System::Windows::Forms::TabPage());
				 this->textBox_Log = (gcnew System::Windows::Forms::TextBox());
				 this->labelMessages = (gcnew System::Windows::Forms::Label());
				 this->tabPageDownload = (gcnew System::Windows::Forms::TabPage());
				 this->groupBoxDownload_Loading = (gcnew System::Windows::Forms::GroupBox());
				 this->buttonDownload_Pause = (gcnew System::Windows::Forms::Button());
				 this->buttonDownload_Cancel = (gcnew System::Windows::Forms::Button());
				 this->progressBarDownload_Loading = (gcnew System::Windows::Forms::ProgressBar());
				 this->buttonDownload = (gcnew System::Windows::Forms::Button());
				 this->label7 = (gcnew System::Windows::Forms::Label());
				 this->comboBoxDownloadFiles = (gcnew System::Windows::Forms::ComboBox());
				 this->tabPageUpload = (gcnew System::Windows::Forms::TabPage());
				 this->groupBoxUpload_Loading = (gcnew System::Windows::Forms::GroupBox());
				 this->buttonUpload_Pause = (gcnew System::Windows::Forms::Button());
				 this->buttonUpload_Cancel = (gcnew System::Windows::Forms::Button());
				 this->progressBarUpload_Loading = (gcnew System::Windows::Forms::ProgressBar());
				 this->buttonUpload = (gcnew System::Windows::Forms::Button());
				 this->groupBoxUpload_Access = (gcnew System::Windows::Forms::GroupBox());
				 this->radioButtonPublic = (gcnew System::Windows::Forms::RadioButton());
				 this->radioButtonProtected = (gcnew System::Windows::Forms::RadioButton());
				 this->listViewUpload_Names = (gcnew System::Windows::Forms::ListView());
				 this->radioButtonPrivate = (gcnew System::Windows::Forms::RadioButton());
				 this->groupBoxUpload_Puth = (gcnew System::Windows::Forms::GroupBox());
				 this->buttonUpload_FileDialog = (gcnew System::Windows::Forms::Button());
				 this->labelUpload_Puth = (gcnew System::Windows::Forms::Label());
				 this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
				 this->tabPageReupload = (gcnew System::Windows::Forms::TabPage());
				 this->groupBoxReupload_Loading = (gcnew System::Windows::Forms::GroupBox());
				 this->buttonReupload_Pause = (gcnew System::Windows::Forms::Button());
				 this->buttonReupload_Cancel = (gcnew System::Windows::Forms::Button());
				 this->progressBarReupload_Loading = (gcnew System::Windows::Forms::ProgressBar());
				 this->buttonReupload = (gcnew System::Windows::Forms::Button());
				 this->label8 = (gcnew System::Windows::Forms::Label());
				 this->comboBoxReupload = (gcnew System::Windows::Forms::ComboBox());
				 this->tabPageMessage->SuspendLayout();
				 this->tabPageDownload->SuspendLayout();
				 this->groupBoxDownload_Loading->SuspendLayout();
				 this->tabPageUpload->SuspendLayout();
				 this->groupBoxUpload_Loading->SuspendLayout();
				 this->groupBoxUpload_Access->SuspendLayout();
				 this->groupBoxUpload_Puth->SuspendLayout();
				 this->tabControl1->SuspendLayout();
				 this->tabPageReupload->SuspendLayout();
				 this->groupBoxReupload_Loading->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // buttonLog
				 // 
				 this->buttonLog->ImageKey = L"login";
				 this->buttonLog->ImageList = this->imageListLog;
				 this->buttonLog->Location = System::Drawing::Point(64, 12);
				 this->buttonLog->Name = L"buttonLog";
				 this->buttonLog->Size = System::Drawing::Size(46, 46);
				 this->buttonLog->TabIndex = 0;
				 this->buttonLog->UseVisualStyleBackColor = true;
				 this->buttonLog->Click += gcnew System::EventHandler(this, &ClientForm::buttonLog_Click);
				 // 
				 // imageListLog
				 // 
				 this->imageListLog->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageListLog.ImageStream")));
				 this->imageListLog->TransparentColor = System::Drawing::Color::Transparent;
				 this->imageListLog->Images->SetKeyName(0, L"login");
				 this->imageListLog->Images->SetKeyName(1, L"logout");
				 // 
				 // textBoxIP1
				 // 
				 this->textBoxIP1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->textBoxIP1->BackColor = System::Drawing::SystemColors::Window;
				 this->textBoxIP1->BorderStyle = System::Windows::Forms::BorderStyle::None;
				 this->textBoxIP1->Location = System::Drawing::Point(266, 31);
				 this->textBoxIP1->MaxLength = 3;
				 this->textBoxIP1->Name = L"textBoxIP1";
				 this->textBoxIP1->Size = System::Drawing::Size(18, 13);
				 this->textBoxIP1->TabIndex = 3;
				 this->textBoxIP1->Text = L"127";
				 this->textBoxIP1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
				 this->textBoxIP1->TextChanged += gcnew System::EventHandler(this, &ClientForm::textBoxIP1_TextChanged);
				 this->textBoxIP1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ClientForm::textBoxIP_KeyPress);
				 // 
				 // label1
				 // 
				 this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->label1->AutoSize = true;
				 this->label1->BackColor = System::Drawing::SystemColors::Window;
				 this->label1->Location = System::Drawing::Point(282, 31);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(10, 13);
				 this->label1->TabIndex = 0;
				 this->label1->Text = L".";
				 // 
				 // textBoxIP2
				 // 
				 this->textBoxIP2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->textBoxIP2->BackColor = System::Drawing::SystemColors::Window;
				 this->textBoxIP2->BorderStyle = System::Windows::Forms::BorderStyle::None;
				 this->textBoxIP2->Location = System::Drawing::Point(290, 31);
				 this->textBoxIP2->MaxLength = 3;
				 this->textBoxIP2->Name = L"textBoxIP2";
				 this->textBoxIP2->Size = System::Drawing::Size(18, 13);
				 this->textBoxIP2->TabIndex = 5;
				 this->textBoxIP2->Text = L"0";
				 this->textBoxIP2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
				 this->textBoxIP2->TextChanged += gcnew System::EventHandler(this, &ClientForm::textBoxIP2_TextChanged);
				 this->textBoxIP2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ClientForm::textBoxIP_KeyPress);
				 // 
				 // label2
				 // 
				 this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->label2->AutoSize = true;
				 this->label2->BackColor = System::Drawing::SystemColors::Window;
				 this->label2->Location = System::Drawing::Point(306, 31);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(10, 13);
				 this->label2->TabIndex = 4;
				 this->label2->Text = L".";
				 // 
				 // textBoxIP4
				 // 
				 this->textBoxIP4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->textBoxIP4->BackColor = System::Drawing::SystemColors::Window;
				 this->textBoxIP4->BorderStyle = System::Windows::Forms::BorderStyle::None;
				 this->textBoxIP4->Location = System::Drawing::Point(338, 31);
				 this->textBoxIP4->MaxLength = 3;
				 this->textBoxIP4->Name = L"textBoxIP4";
				 this->textBoxIP4->Size = System::Drawing::Size(18, 13);
				 this->textBoxIP4->TabIndex = 9;
				 this->textBoxIP4->Text = L"1";
				 this->textBoxIP4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
				 this->textBoxIP4->TextChanged += gcnew System::EventHandler(this, &ClientForm::textBoxIP4_TextChanged);
				 this->textBoxIP4->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ClientForm::textBoxIP_KeyPress);
				 // 
				 // textBoxIP3
				 // 
				 this->textBoxIP3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->textBoxIP3->BackColor = System::Drawing::SystemColors::Window;
				 this->textBoxIP3->BorderStyle = System::Windows::Forms::BorderStyle::None;
				 this->textBoxIP3->Location = System::Drawing::Point(314, 31);
				 this->textBoxIP3->MaxLength = 3;
				 this->textBoxIP3->Name = L"textBoxIP3";
				 this->textBoxIP3->Size = System::Drawing::Size(18, 13);
				 this->textBoxIP3->TabIndex = 7;
				 this->textBoxIP3->Text = L"0";
				 this->textBoxIP3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
				 this->textBoxIP3->TextChanged += gcnew System::EventHandler(this, &ClientForm::textBoxIP3_TextChanged);
				 this->textBoxIP3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ClientForm::textBoxIP_KeyPress);
				 // 
				 // label3
				 // 
				 this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->label3->AutoSize = true;
				 this->label3->BackColor = System::Drawing::SystemColors::Window;
				 this->label3->Location = System::Drawing::Point(330, 31);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(10, 13);
				 this->label3->TabIndex = 6;
				 this->label3->Text = L".";
				 // 
				 // label4
				 // 
				 this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->label4->BackColor = System::Drawing::SystemColors::Window;
				 this->label4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->label4->Location = System::Drawing::Point(263, 25);
				 this->label4->Name = L"label4";
				 this->label4->Size = System::Drawing::Size(96, 20);
				 this->label4->TabIndex = 10;
				 // 
				 // buttonConnect
				 // 
				 this->buttonConnect->ImageKey = L"pause";
				 this->buttonConnect->ImageList = this->imageListPlay;
				 this->buttonConnect->Location = System::Drawing::Point(12, 12);
				 this->buttonConnect->Name = L"buttonConnect";
				 this->buttonConnect->Size = System::Drawing::Size(46, 46);
				 this->buttonConnect->TabIndex = 12;
				 this->buttonConnect->UseVisualStyleBackColor = true;
				 this->buttonConnect->Click += gcnew System::EventHandler(this, &ClientForm::buttonConnect_Click);
				 // 
				 // imageListPlay
				 // 
				 this->imageListPlay->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageListPlay.ImageStream")));
				 this->imageListPlay->TransparentColor = System::Drawing::Color::Transparent;
				 this->imageListPlay->Images->SetKeyName(0, L"play");
				 this->imageListPlay->Images->SetKeyName(1, L"pause");
				 // 
				 // buttonHome
				 // 
				 this->buttonHome->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->buttonHome->ImageKey = L"home";
				 this->buttonHome->ImageList = this->imageListHome;
				 this->buttonHome->Location = System::Drawing::Point(365, 12);
				 this->buttonHome->Name = L"buttonHome";
				 this->buttonHome->Size = System::Drawing::Size(46, 46);
				 this->buttonHome->TabIndex = 16;
				 this->buttonHome->UseVisualStyleBackColor = true;
				 this->buttonHome->Click += gcnew System::EventHandler(this, &ClientForm::buttonSetLocalIP_Click);
				 // 
				 // imageListHome
				 // 
				 this->imageListHome->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageListHome.ImageStream")));
				 this->imageListHome->TransparentColor = System::Drawing::Color::Transparent;
				 this->imageListHome->Images->SetKeyName(0, L"home");
				 // 
				 // openFileDialog
				 // 
				 this->openFileDialog->InitialDirectory = L"D:\\Client";
				 this->openFileDialog->Title = L"�������� ����������� ����";
				 // 
				 // label5
				 // 
				 this->label5->Anchor = System::Windows::Forms::AnchorStyles::Top;
				 this->label5->AutoSize = true;
				 this->label5->Location = System::Drawing::Point(127, 12);
				 this->label5->Name = L"label5";
				 this->label5->Size = System::Drawing::Size(213, 13);
				 this->label5->TabIndex = 17;
				 this->label5->Text = L"������ ����������. ���������������...";
				 this->label5->Visible = false;
				 // 
				 // progressBar1
				 // 
				 this->progressBar1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->progressBar1->Location = System::Drawing::Point(116, 48);
				 this->progressBar1->MarqueeAnimationSpeed = 50;
				 this->progressBar1->Name = L"progressBar1";
				 this->progressBar1->Size = System::Drawing::Size(243, 10);
				 this->progressBar1->Step = 5;
				 this->progressBar1->Style = System::Windows::Forms::ProgressBarStyle::Marquee;
				 this->progressBar1->TabIndex = 18;
				 this->progressBar1->Visible = false;
				 // 
				 // label6
				 // 
				 this->label6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->label6->AutoSize = true;
				 this->label6->Location = System::Drawing::Point(162, 29);
				 this->label6->Name = L"label6";
				 this->label6->Size = System::Drawing::Size(98, 13);
				 this->label6->TabIndex = 19;
				 this->label6->Text = L"IP-����� �������:";
				 // 
				 // tabPageMessage
				 // 
				 this->tabPageMessage->Controls->Add(this->textBox_Log);
				 this->tabPageMessage->Controls->Add(this->labelMessages);
				 this->tabPageMessage->Location = System::Drawing::Point(4, 22);
				 this->tabPageMessage->Name = L"tabPageMessage";
				 this->tabPageMessage->Padding = System::Windows::Forms::Padding(3);
				 this->tabPageMessage->Size = System::Drawing::Size(391, 328);
				 this->tabPageMessage->TabIndex = 0;
				 this->tabPageMessage->Text = L"���������";
				 this->tabPageMessage->UseVisualStyleBackColor = true;
				 // 
				 // textBox_Log
				 // 
				 this->textBox_Log->BackColor = System::Drawing::SystemColors::Window;
				 this->textBox_Log->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->textBox_Log->Location = System::Drawing::Point(3, 3);
				 this->textBox_Log->Multiline = true;
				 this->textBox_Log->Name = L"textBox_Log";
				 this->textBox_Log->ReadOnly = true;
				 this->textBox_Log->Size = System::Drawing::Size(385, 322);
				 this->textBox_Log->TabIndex = 1;
				 // 
				 // labelMessages
				 // 
				 this->labelMessages->Location = System::Drawing::Point(3, 0);
				 this->labelMessages->Name = L"labelMessages";
				 this->labelMessages->Size = System::Drawing::Size(382, 322);
				 this->labelMessages->TabIndex = 0;
				 // 
				 // tabPageDownload
				 // 
				 this->tabPageDownload->Controls->Add(this->groupBoxDownload_Loading);
				 this->tabPageDownload->Controls->Add(this->buttonDownload);
				 this->tabPageDownload->Controls->Add(this->label7);
				 this->tabPageDownload->Controls->Add(this->comboBoxDownloadFiles);
				 this->tabPageDownload->Location = System::Drawing::Point(4, 22);
				 this->tabPageDownload->Name = L"tabPageDownload";
				 this->tabPageDownload->Padding = System::Windows::Forms::Padding(3);
				 this->tabPageDownload->Size = System::Drawing::Size(391, 328);
				 this->tabPageDownload->TabIndex = 2;
				 this->tabPageDownload->Text = L"�������";
				 this->tabPageDownload->UseVisualStyleBackColor = true;
				 // 
				 // groupBoxDownload_Loading
				 // 
				 this->groupBoxDownload_Loading->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->groupBoxDownload_Loading->Controls->Add(this->buttonDownload_Pause);
				 this->groupBoxDownload_Loading->Controls->Add(this->buttonDownload_Cancel);
				 this->groupBoxDownload_Loading->Controls->Add(this->progressBarDownload_Loading);
				 this->groupBoxDownload_Loading->Location = System::Drawing::Point(6, 224);
				 this->groupBoxDownload_Loading->Name = L"groupBoxDownload_Loading";
				 this->groupBoxDownload_Loading->Size = System::Drawing::Size(379, 98);
				 this->groupBoxDownload_Loading->TabIndex = 11;
				 this->groupBoxDownload_Loading->TabStop = false;
				 this->groupBoxDownload_Loading->Text = L"���� ��������...";
				 this->groupBoxDownload_Loading->Visible = false;
				 // 
				 // buttonDownload_Pause
				 // 
				 this->buttonDownload_Pause->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
				 this->buttonDownload_Pause->Location = System::Drawing::Point(6, 69);
				 this->buttonDownload_Pause->Name = L"buttonDownload_Pause";
				 this->buttonDownload_Pause->Size = System::Drawing::Size(75, 23);
				 this->buttonDownload_Pause->TabIndex = 2;
				 this->buttonDownload_Pause->Text = L"�����";
				 this->buttonDownload_Pause->UseVisualStyleBackColor = true;
				 this->buttonDownload_Pause->Click += gcnew System::EventHandler(this, &ClientForm::buttonDownload_Pause_Click);
				 // 
				 // buttonDownload_Cancel
				 // 
				 this->buttonDownload_Cancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
				 this->buttonDownload_Cancel->Location = System::Drawing::Point(298, 69);
				 this->buttonDownload_Cancel->Name = L"buttonDownload_Cancel";
				 this->buttonDownload_Cancel->Size = System::Drawing::Size(75, 23);
				 this->buttonDownload_Cancel->TabIndex = 1;
				 this->buttonDownload_Cancel->Text = L"������";
				 this->buttonDownload_Cancel->UseVisualStyleBackColor = true;
				 this->buttonDownload_Cancel->Click += gcnew System::EventHandler(this, &ClientForm::buttonDownload_Cancel_Click);
				 // 
				 // progressBarDownload_Loading
				 // 
				 this->progressBarDownload_Loading->Dock = System::Windows::Forms::DockStyle::Top;
				 this->progressBarDownload_Loading->Location = System::Drawing::Point(3, 16);
				 this->progressBarDownload_Loading->Name = L"progressBarDownload_Loading";
				 this->progressBarDownload_Loading->Size = System::Drawing::Size(373, 23);
				 this->progressBarDownload_Loading->TabIndex = 0;
				 // 
				 // buttonDownload
				 // 
				 this->buttonDownload->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->buttonDownload->Location = System::Drawing::Point(6, 195);
				 this->buttonDownload->Name = L"buttonDownload";
				 this->buttonDownload->Size = System::Drawing::Size(379, 23);
				 this->buttonDownload->TabIndex = 10;
				 this->buttonDownload->Text = L"�������";
				 this->buttonDownload->UseVisualStyleBackColor = true;
				 this->buttonDownload->Click += gcnew System::EventHandler(this, &ClientForm::buttonDownload_Click);
				 // 
				 // label7
				 // 
				 this->label7->AutoSize = true;
				 this->label7->Location = System::Drawing::Point(45, 32);
				 this->label7->Name = L"label7";
				 this->label7->Size = System::Drawing::Size(89, 13);
				 this->label7->TabIndex = 1;
				 this->label7->Text = L"�������� ����:";
				 // 
				 // comboBoxDownloadFiles
				 // 
				 this->comboBoxDownloadFiles->FormattingEnabled = true;
				 this->comboBoxDownloadFiles->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
					 L"����1", L"����2", L"����3", L"����4",
						 L"����5", L""
				 });
				 this->comboBoxDownloadFiles->Location = System::Drawing::Point(48, 48);
				 this->comboBoxDownloadFiles->Name = L"comboBoxDownloadFiles";
				 this->comboBoxDownloadFiles->Size = System::Drawing::Size(244, 21);
				 this->comboBoxDownloadFiles->TabIndex = 0;
				 // 
				 // tabPageUpload
				 // 
				 this->tabPageUpload->Controls->Add(this->groupBoxUpload_Loading);
				 this->tabPageUpload->Controls->Add(this->buttonUpload);
				 this->tabPageUpload->Controls->Add(this->groupBoxUpload_Access);
				 this->tabPageUpload->Controls->Add(this->groupBoxUpload_Puth);
				 this->tabPageUpload->Location = System::Drawing::Point(4, 22);
				 this->tabPageUpload->Name = L"tabPageUpload";
				 this->tabPageUpload->Padding = System::Windows::Forms::Padding(3);
				 this->tabPageUpload->Size = System::Drawing::Size(391, 328);
				 this->tabPageUpload->TabIndex = 1;
				 this->tabPageUpload->Text = L"���������";
				 this->tabPageUpload->UseVisualStyleBackColor = true;
				 // 
				 // groupBoxUpload_Loading
				 // 
				 this->groupBoxUpload_Loading->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->groupBoxUpload_Loading->Controls->Add(this->buttonUpload_Pause);
				 this->groupBoxUpload_Loading->Controls->Add(this->buttonUpload_Cancel);
				 this->groupBoxUpload_Loading->Controls->Add(this->progressBarUpload_Loading);
				 this->groupBoxUpload_Loading->Location = System::Drawing::Point(6, 224);
				 this->groupBoxUpload_Loading->Name = L"groupBoxUpload_Loading";
				 this->groupBoxUpload_Loading->Size = System::Drawing::Size(379, 98);
				 this->groupBoxUpload_Loading->TabIndex = 9;
				 this->groupBoxUpload_Loading->TabStop = false;
				 this->groupBoxUpload_Loading->Text = L"���� ��������...";
				 this->groupBoxUpload_Loading->Visible = false;
				 // 
				 // buttonUpload_Pause
				 // 
				 this->buttonUpload_Pause->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
				 this->buttonUpload_Pause->Location = System::Drawing::Point(6, 69);
				 this->buttonUpload_Pause->Name = L"buttonUpload_Pause";
				 this->buttonUpload_Pause->Size = System::Drawing::Size(75, 23);
				 this->buttonUpload_Pause->TabIndex = 2;
				 this->buttonUpload_Pause->Text = L"�����";
				 this->buttonUpload_Pause->UseVisualStyleBackColor = true;
				 this->buttonUpload_Pause->Click += gcnew System::EventHandler(this, &ClientForm::buttonUpload_Pause_Click);
				 // 
				 // buttonUpload_Cancel
				 // 
				 this->buttonUpload_Cancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
				 this->buttonUpload_Cancel->Location = System::Drawing::Point(298, 69);
				 this->buttonUpload_Cancel->Name = L"buttonUpload_Cancel";
				 this->buttonUpload_Cancel->Size = System::Drawing::Size(75, 23);
				 this->buttonUpload_Cancel->TabIndex = 1;
				 this->buttonUpload_Cancel->Text = L"������";
				 this->buttonUpload_Cancel->UseVisualStyleBackColor = true;
				 this->buttonUpload_Cancel->Click += gcnew System::EventHandler(this, &ClientForm::buttonUpload_Cancel_Click);
				 // 
				 // progressBarUpload_Loading
				 // 
				 this->progressBarUpload_Loading->Dock = System::Windows::Forms::DockStyle::Top;
				 this->progressBarUpload_Loading->Location = System::Drawing::Point(3, 16);
				 this->progressBarUpload_Loading->Name = L"progressBarUpload_Loading";
				 this->progressBarUpload_Loading->Size = System::Drawing::Size(373, 23);
				 this->progressBarUpload_Loading->TabIndex = 0;
				 // 
				 // buttonUpload
				 // 
				 this->buttonUpload->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->buttonUpload->Location = System::Drawing::Point(6, 195);
				 this->buttonUpload->Name = L"buttonUpload";
				 this->buttonUpload->Size = System::Drawing::Size(379, 23);
				 this->buttonUpload->TabIndex = 8;
				 this->buttonUpload->Text = L"���������";
				 this->buttonUpload->UseVisualStyleBackColor = true;
				 this->buttonUpload->Click += gcnew System::EventHandler(this, &ClientForm::buttonUpload_Click);
				 // 
				 // groupBoxUpload_Access
				 // 
				 this->groupBoxUpload_Access->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->groupBoxUpload_Access->AutoSize = true;
				 this->groupBoxUpload_Access->Controls->Add(this->radioButtonPublic);
				 this->groupBoxUpload_Access->Controls->Add(this->radioButtonProtected);
				 this->groupBoxUpload_Access->Controls->Add(this->listViewUpload_Names);
				 this->groupBoxUpload_Access->Controls->Add(this->radioButtonPrivate);
				 this->groupBoxUpload_Access->Location = System::Drawing::Point(6, 72);
				 this->groupBoxUpload_Access->Name = L"groupBoxUpload_Access";
				 this->groupBoxUpload_Access->Size = System::Drawing::Size(379, 117);
				 this->groupBoxUpload_Access->TabIndex = 7;
				 this->groupBoxUpload_Access->TabStop = false;
				 this->groupBoxUpload_Access->Text = L"������ � �����:";
				 // 
				 // radioButtonPublic
				 // 
				 this->radioButtonPublic->AutoSize = true;
				 this->radioButtonPublic->Location = System::Drawing::Point(6, 65);
				 this->radioButtonPublic->Name = L"radioButtonPublic";
				 this->radioButtonPublic->Size = System::Drawing::Size(60, 17);
				 this->radioButtonPublic->TabIndex = 2;
				 this->radioButtonPublic->Text = L"�����";
				 this->radioButtonPublic->UseVisualStyleBackColor = true;
				 // 
				 // radioButtonProtected
				 // 
				 this->radioButtonProtected->AutoSize = true;
				 this->radioButtonProtected->Location = System::Drawing::Point(6, 42);
				 this->radioButtonProtected->Name = L"radioButtonProtected";
				 this->radioButtonProtected->Size = System::Drawing::Size(99, 17);
				 this->radioButtonProtected->TabIndex = 1;
				 this->radioButtonProtected->Text = L"������������";
				 this->radioButtonProtected->UseVisualStyleBackColor = true;
				 this->radioButtonProtected->CheckedChanged += gcnew System::EventHandler(this, &ClientForm::radioButtonProtected_CheckedChanged);
				 // 
				 // listViewUpload_Names
				 // 
				 this->listViewUpload_Names->Dock = System::Windows::Forms::DockStyle::Right;
				 this->listViewUpload_Names->HideSelection = false;
				 listViewItem1->StateImageIndex = 0;
				 listViewItem2->StateImageIndex = 0;
				 listViewItem2->UseItemStyleForSubItems = false;
				 listViewItem3->StateImageIndex = 0;
				 listViewItem4->StateImageIndex = 0;
				 listViewItem5->StateImageIndex = 0;
				 listViewItem6->StateImageIndex = 0;
				 listViewItem7->StateImageIndex = 0;
				 listViewItem8->StateImageIndex = 0;
				 listViewItem9->StateImageIndex = 0;
				 listViewItem10->StateImageIndex = 0;
				 listViewItem11->StateImageIndex = 0;
				 listViewItem12->StateImageIndex = 0;
				 listViewItem13->StateImageIndex = 0;
				 listViewItem14->StateImageIndex = 0;
				 listViewItem15->StateImageIndex = 0;
				 listViewItem16->StateImageIndex = 0;
				 listViewItem17->StateImageIndex = 0;
				 listViewItem18->StateImageIndex = 0;
				 listViewItem19->StateImageIndex = 0;
				 listViewItem20->StateImageIndex = 0;
				 this->listViewUpload_Names->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(20) {
					 listViewItem1,
						 listViewItem2, listViewItem3, listViewItem4, listViewItem5, listViewItem6, listViewItem7, listViewItem8, listViewItem9, listViewItem10,
						 listViewItem11, listViewItem12, listViewItem13, listViewItem14, listViewItem15, listViewItem16, listViewItem17, listViewItem18,
						 listViewItem19, listViewItem20
				 });
				 this->listViewUpload_Names->LabelWrap = false;
				 this->listViewUpload_Names->Location = System::Drawing::Point(111, 16);
				 this->listViewUpload_Names->Name = L"listViewUpload_Names";
				 this->listViewUpload_Names->ShowGroups = false;
				 this->listViewUpload_Names->Size = System::Drawing::Size(265, 98);
				 this->listViewUpload_Names->Sorting = System::Windows::Forms::SortOrder::Ascending;
				 this->listViewUpload_Names->TabIndex = 2;
				 this->listViewUpload_Names->UseCompatibleStateImageBehavior = false;
				 this->listViewUpload_Names->View = System::Windows::Forms::View::SmallIcon;
				 this->listViewUpload_Names->Visible = false;
				 // 
				 // radioButtonPrivate
				 // 
				 this->radioButtonPrivate->AutoSize = true;
				 this->radioButtonPrivate->Checked = true;
				 this->radioButtonPrivate->Location = System::Drawing::Point(6, 19);
				 this->radioButtonPrivate->Name = L"radioButtonPrivate";
				 this->radioButtonPrivate->Size = System::Drawing::Size(64, 17);
				 this->radioButtonPrivate->TabIndex = 0;
				 this->radioButtonPrivate->TabStop = true;
				 this->radioButtonPrivate->Text = L"������";
				 this->radioButtonPrivate->UseVisualStyleBackColor = true;
				 // 
				 // groupBoxUpload_Puth
				 // 
				 this->groupBoxUpload_Puth->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->groupBoxUpload_Puth->Controls->Add(this->buttonUpload_FileDialog);
				 this->groupBoxUpload_Puth->Controls->Add(this->labelUpload_Puth);
				 this->groupBoxUpload_Puth->Location = System::Drawing::Point(6, 6);
				 this->groupBoxUpload_Puth->Name = L"groupBoxUpload_Puth";
				 this->groupBoxUpload_Puth->Size = System::Drawing::Size(379, 60);
				 this->groupBoxUpload_Puth->TabIndex = 6;
				 this->groupBoxUpload_Puth->TabStop = false;
				 this->groupBoxUpload_Puth->Text = L"���� � �����:";
				 // 
				 // buttonUpload_FileDialog
				 // 
				 this->buttonUpload_FileDialog->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
				 this->buttonUpload_FileDialog->Location = System::Drawing::Point(298, 31);
				 this->buttonUpload_FileDialog->Name = L"buttonUpload_FileDialog";
				 this->buttonUpload_FileDialog->Size = System::Drawing::Size(75, 23);
				 this->buttonUpload_FileDialog->TabIndex = 4;
				 this->buttonUpload_FileDialog->Text = L"�������";
				 this->buttonUpload_FileDialog->UseVisualStyleBackColor = true;
				 this->buttonUpload_FileDialog->Click += gcnew System::EventHandler(this, &ClientForm::buttonUpload_FileDialog_Click);
				 // 
				 // labelUpload_Puth
				 // 
				 this->labelUpload_Puth->AutoEllipsis = true;
				 this->labelUpload_Puth->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->labelUpload_Puth->Location = System::Drawing::Point(3, 16);
				 this->labelUpload_Puth->Name = L"labelUpload_Puth";
				 this->labelUpload_Puth->Size = System::Drawing::Size(373, 41);
				 this->labelUpload_Puth->TabIndex = 3;
				 this->labelUpload_Puth->Text = L"D:\\Client\\";
				 // 
				 // tabControl1
				 // 
				 this->tabControl1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
					 | System::Windows::Forms::AnchorStyles::Left)
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->tabControl1->Controls->Add(this->tabPageUpload);
				 this->tabControl1->Controls->Add(this->tabPageDownload);
				 this->tabControl1->Controls->Add(this->tabPageReupload);
				 this->tabControl1->Controls->Add(this->tabPageMessage);
				 this->tabControl1->Enabled = false;
				 this->tabControl1->Location = System::Drawing::Point(12, 64);
				 this->tabControl1->Name = L"tabControl1";
				 this->tabControl1->SelectedIndex = 0;
				 this->tabControl1->Size = System::Drawing::Size(399, 354);
				 this->tabControl1->TabIndex = 1;
				 this->tabControl1->Click += gcnew System::EventHandler(this, &ClientForm::tabControl1_Click);
				 // 
				 // tabPageReupload
				 // 
				 this->tabPageReupload->Controls->Add(this->groupBoxReupload_Loading);
				 this->tabPageReupload->Controls->Add(this->buttonReupload);
				 this->tabPageReupload->Controls->Add(this->label8);
				 this->tabPageReupload->Controls->Add(this->comboBoxReupload);
				 this->tabPageReupload->Location = System::Drawing::Point(4, 22);
				 this->tabPageReupload->Name = L"tabPageReupload";
				 this->tabPageReupload->Padding = System::Windows::Forms::Padding(3);
				 this->tabPageReupload->Size = System::Drawing::Size(391, 328);
				 this->tabPageReupload->TabIndex = 3;
				 this->tabPageReupload->Text = L"���������";
				 this->tabPageReupload->UseVisualStyleBackColor = true;
				 // 
				 // groupBoxReupload_Loading
				 // 
				 this->groupBoxReupload_Loading->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->groupBoxReupload_Loading->Controls->Add(this->buttonReupload_Pause);
				 this->groupBoxReupload_Loading->Controls->Add(this->buttonReupload_Cancel);
				 this->groupBoxReupload_Loading->Controls->Add(this->progressBarReupload_Loading);
				 this->groupBoxReupload_Loading->Location = System::Drawing::Point(6, 224);
				 this->groupBoxReupload_Loading->Name = L"groupBoxReupload_Loading";
				 this->groupBoxReupload_Loading->Size = System::Drawing::Size(379, 98);
				 this->groupBoxReupload_Loading->TabIndex = 15;
				 this->groupBoxReupload_Loading->TabStop = false;
				 this->groupBoxReupload_Loading->Text = L"���� ��������...";
				 this->groupBoxReupload_Loading->Visible = false;
				 // 
				 // buttonReupload_Pause
				 // 
				 this->buttonReupload_Pause->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
				 this->buttonReupload_Pause->Location = System::Drawing::Point(6, 69);
				 this->buttonReupload_Pause->Name = L"buttonReupload_Pause";
				 this->buttonReupload_Pause->Size = System::Drawing::Size(75, 23);
				 this->buttonReupload_Pause->TabIndex = 2;
				 this->buttonReupload_Pause->Text = L"�����";
				 this->buttonReupload_Pause->UseVisualStyleBackColor = true;
				 this->buttonReupload_Pause->Click += gcnew System::EventHandler(this, &ClientForm::buttonReupload_Pause_Click);
				 // 
				 // buttonReupload_Cancel
				 // 
				 this->buttonReupload_Cancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
				 this->buttonReupload_Cancel->Location = System::Drawing::Point(298, 69);
				 this->buttonReupload_Cancel->Name = L"buttonReupload_Cancel";
				 this->buttonReupload_Cancel->Size = System::Drawing::Size(75, 23);
				 this->buttonReupload_Cancel->TabIndex = 1;
				 this->buttonReupload_Cancel->Text = L"������";
				 this->buttonReupload_Cancel->UseVisualStyleBackColor = true;
				 this->buttonReupload_Cancel->Click += gcnew System::EventHandler(this, &ClientForm::buttonReupload_Cancel_Click);
				 // 
				 // progressBarReupload_Loading
				 // 
				 this->progressBarReupload_Loading->Dock = System::Windows::Forms::DockStyle::Top;
				 this->progressBarReupload_Loading->Location = System::Drawing::Point(3, 16);
				 this->progressBarReupload_Loading->Name = L"progressBarReupload_Loading";
				 this->progressBarReupload_Loading->Size = System::Drawing::Size(373, 23);
				 this->progressBarReupload_Loading->TabIndex = 0;
				 // 
				 // buttonReupload
				 // 
				 this->buttonReupload->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->buttonReupload->Location = System::Drawing::Point(6, 195);
				 this->buttonReupload->Name = L"buttonReupload";
				 this->buttonReupload->Size = System::Drawing::Size(379, 23);
				 this->buttonReupload->TabIndex = 14;
				 this->buttonReupload->Text = L"���������";
				 this->buttonReupload->UseVisualStyleBackColor = true;
				 this->buttonReupload->Click += gcnew System::EventHandler(this, &ClientForm::buttonReupload_Click);
				 // 
				 // label8
				 // 
				 this->label8->AutoSize = true;
				 this->label8->Location = System::Drawing::Point(45, 32);
				 this->label8->Name = L"label8";
				 this->label8->Size = System::Drawing::Size(89, 13);
				 this->label8->TabIndex = 13;
				 this->label8->Text = L"�������� ����:";
				 // 
				 // comboBoxReupload
				 // 
				 this->comboBoxReupload->FormattingEnabled = true;
				 this->comboBoxReupload->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
					 L"����1", L"����2", L"����3", L"����4",
						 L"����5", L""
				 });
				 this->comboBoxReupload->Location = System::Drawing::Point(48, 48);
				 this->comboBoxReupload->Name = L"comboBoxReupload";
				 this->comboBoxReupload->Size = System::Drawing::Size(244, 21);
				 this->comboBoxReupload->TabIndex = 12;
				 // 
				 // ClientForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(423, 430);
				 this->Controls->Add(this->label6);
				 this->Controls->Add(this->label5);
				 this->Controls->Add(this->progressBar1);
				 this->Controls->Add(this->buttonHome);
				 this->Controls->Add(this->buttonConnect);
				 this->Controls->Add(this->textBoxIP4);
				 this->Controls->Add(this->textBoxIP3);
				 this->Controls->Add(this->label3);
				 this->Controls->Add(this->textBoxIP2);
				 this->Controls->Add(this->label2);
				 this->Controls->Add(this->textBoxIP1);
				 this->Controls->Add(this->tabControl1);
				 this->Controls->Add(this->buttonLog);
				 this->Controls->Add(this->label1);
				 this->Controls->Add(this->label4);
				 this->MinimumSize = System::Drawing::Size(439, 469);
				 this->Name = L"ClientForm";
				 this->Text = L"ClientForm";
				 this->Load += gcnew System::EventHandler(this, &ClientForm::ClientForm_Load);
				 this->tabPageMessage->ResumeLayout(false);
				 this->tabPageMessage->PerformLayout();
				 this->tabPageDownload->ResumeLayout(false);
				 this->tabPageDownload->PerformLayout();
				 this->groupBoxDownload_Loading->ResumeLayout(false);
				 this->tabPageUpload->ResumeLayout(false);
				 this->tabPageUpload->PerformLayout();
				 this->groupBoxUpload_Loading->ResumeLayout(false);
				 this->groupBoxUpload_Access->ResumeLayout(false);
				 this->groupBoxUpload_Access->PerformLayout();
				 this->groupBoxUpload_Puth->ResumeLayout(false);
				 this->tabControl1->ResumeLayout(false);
				 this->tabPageReupload->ResumeLayout(false);
				 this->tabPageReupload->PerformLayout();
				 this->groupBoxReupload_Loading->ResumeLayout(false);
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion

#pragma region ��������� ������� �� ����� IP-������
	private: System::Void textBoxIP_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
	{
		wchar_t c = e->KeyChar;
		if (c >= '0' && c <= '9')
		{
			//������� �����, ��������� ����� ������������ �� ������� "TextChanged"
		}
		else if (c == 8)
		{
			//Backspase, ����� ��������������, ������ �� ������
		}
		else
			e->Handled = true;
	}
	private: System::Void textBoxIP1_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		if (textBoxIP1->Text == "")
			textBoxIP1->Text = "0";
		else if (System::Convert::ToInt32(textBoxIP1->Text) > 255)
			textBoxIP1->Text = "255";
	}
	private: System::Void textBoxIP2_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		if (textBoxIP2->Text == "")
			textBoxIP2->Text = "0";
		else if (System::Convert::ToInt32(textBoxIP2->Text) > 255)
			textBoxIP2->Text = "255";
	}
	private: System::Void textBoxIP3_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		if (textBoxIP3->Text == "")
			textBoxIP3->Text = "0";
		else if (System::Convert::ToInt32(textBoxIP3->Text) > 255)
			textBoxIP3->Text = "255";
	}
	private: System::Void textBoxIP4_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		if (textBoxIP4->Text == "")
			textBoxIP4->Text = "0";
		else if (System::Convert::ToInt32(textBoxIP4->Text) > 255)
			textBoxIP4->Text = "255";
	}
	private: System::Void buttonSetLocalIP_Click(System::Object^  sender, System::EventArgs^  e)
	{
		textBoxIP1->Text = "127";
		textBoxIP2->Text = "0";
		textBoxIP3->Text = "0";
		textBoxIP4->Text = "1";
	}
	private: void getIP()
	{
		IP = textBoxIP1->Text + ".";
		IP += textBoxIP2->Text + ".";
		IP += textBoxIP3->Text + ".";
		IP += textBoxIP4->Text;
	}
#pragma endregion

	private: System::Void ClientForm_Load(System::Object^  sender, System::EventArgs^  e)
	{
		buttonConnect->ImageIndex = client.isConnected();
		buttonConnect->Enabled = false;
		buttonLog->ImageIndex = client.isLogged();
		getIP();
	}

#pragma region ���������� ��������� ���������� ��� ������� ��������� �����������
	private: void blockTextBoxIP()
	{
		textBoxIP1->Enabled = false;
		textBoxIP2->Enabled = false;
		textBoxIP3->Enabled = false;
		textBoxIP4->Enabled = false;
		textBoxIP1->BackColor = Drawing::SystemColors::Window;
		textBoxIP2->BackColor = Drawing::SystemColors::Window;
		textBoxIP3->BackColor = Drawing::SystemColors::Window;
		textBoxIP4->BackColor = Drawing::SystemColors::Window;
		label1->Enabled = false;
		label2->Enabled = false;
		label3->Enabled = false;
		label4->Enabled = false;
	}
	private: void unblockTextBoxIP()
	{
		textBoxIP1->Enabled = true;
		textBoxIP2->Enabled = true;
		textBoxIP3->Enabled = true;
		textBoxIP4->Enabled = true;
		label1->Enabled = true;
		label2->Enabled = true;
		label3->Enabled = true;
		label4->Enabled = true;
	}
	private: void block_buttons()
	{
		buttonConnect->Enabled = false;
		buttonLog->Enabled = false;
		buttonHome->Enabled = false;
		tabControl1->Enabled = false;
		blockTextBoxIP();
	}
	private: void unblock_buttons()
	{
		buttonConnect->ImageIndex = client.isConnected();
		buttonLog->ImageIndex = client.isLogged();
		buttonLog->Enabled = true;
		c status = client.Status();
		switch (status)
		{
		case c::avalible:
			tabControl1->Enabled = true;
			update_info();
		case c::connected:
		case c::logged:
			buttonConnect->Enabled = true;
			break;
		case c::stopped:
			buttonHome->Enabled = true;
			unblockTextBoxIP();
			break;
		}
		if (status == c::connected)
		{
			//������ �� ��������
			th = gcnew Thread(gcnew ThreadStart(this, &ClientForm::wait_progressBar1));
			th->Start();
		}
	}
	private: void update_info()
	{
		client.Update();
		if (client.isOutDated_DownloadFiles)
		{
			//���������� ������ ��������� ��� ���������� ������
			comboBoxDownloadFiles->Items->Clear();
			for each (string name_file in client.getFiles())
			{
				comboBoxDownloadFiles->Items->Add(gcnew String(name_file.c_str()));
			}
			
			//���������� ������ ������������ ������
			comboBoxReupload->Items->Clear();
			for each (string name_file in client.getLoadingFiles())
			{
				comboBoxReupload->Items->Add(gcnew String(name_file.c_str()));
			}
			client.isOutDated_DownloadFiles = false;
		}
		if (client.isOutDated_UploadUsers)
		{
			//���������� ������ ��������� �������������
			listViewUpload_Names->Items->Clear();
			ListViewItem ^ user;
			for each (string user_name in client.getUsers())
			{
				user = gcnew ListViewItem(gcnew String(user_name.c_str()));
				listViewUpload_Names->Items->Add(user);
			}
			client.isOutDated_UploadUsers = false;
		}
		while (!client.Log_isEmpty())
		{
			textBox_Log->Text += gcnew String((client.popLog()).c_str()) + Environment::NewLine;
		}
	}
	private: void wait_progressBar1()
	{
		Invoke(gcnew Action(this, &ClientForm::start_progressBar1));
		while (client.Status() == c::connected)
		{
			Thread::CurrentThread->Sleep(2000);
		}
		Invoke(gcnew Action(this, &ClientForm::stop_progressBar1));
	}
	private: void start_progressBar1()
	{
		ClientForm::label5->Visible = true;
		ClientForm::progressBar1->Visible = true;
		ClientForm::progressBar1->Style = ProgressBarStyle::Marquee;
	}
	private: void stop_progressBar1()
	{
		ClientForm::label5->Visible = false;
		ClientForm::progressBar1->Style = ProgressBarStyle::Continuous;
		ClientForm::progressBar1->Visible = false;
	}
#pragma endregion

#pragma region ������� Connect � Login
	private: System::Void buttonConnect_Click(System::Object^  sender, System::EventArgs^  e)
	{
		block_buttons();
		if (client.isConnected())
		{
			client.Disconnect();
		}
		else
		{
			client.Connect();
			//��������� ������ ��� ��������� ���������� �� ��������
		}
		unblock_buttons();
	}
	private: System::Void buttonLog_Click(System::Object^  sender, System::EventArgs^  e)
	{
		block_buttons();
		if (client.isLogged())
		{
			if (MessageBox::Show("���� �� ��������� ������, �� ��������� ������ � ������� ������. ������ � ����� ������ ���������.", "��������!", MessageBoxButtons::OKCancel, MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button1)
				== System::Windows::Forms::DialogResult::OK)
			{
				client.Logout();
			}
		}
		else
		{
			getIP();

			const char* chars = (const char*)(Runtime::InteropServices::Marshal::StringToHGlobalAnsi(IP)).ToPointer();
			string s = chars;
			Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr((void*)chars));

			client.Login(s);
			//��������� ����������� �����������
		}
		unblock_buttons();
	}
#pragma endregion

	private: System::Void tabControl1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		block_buttons();
		update_info();
		unblock_buttons();
	}

#pragma region Upload
	private: System::Void buttonUpload_FileDialog_Click(System::Object^  sender, System::EventArgs^  e)
	{
		openFileDialog->ShowDialog();
		labelUpload_Puth->Text = openFileDialog->FileName;
	}
	private: System::Void radioButtonProtected_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		if (radioButtonProtected->Checked)
			listViewUpload_Names->Visible = true;
		else
			listViewUpload_Names->Visible = false;
	}
	private: System::Void buttonUpload_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (client.Status() != c::avalible)
		{
			block_buttons();
			update_info();
			unblock_buttons();
			return;
		}
		if (client.isOutDated_UploadUsers)
		{
			//�������� �����, ��������� ��� ��� �������� �������������
			if (MessageBox::Show("������ ������������� �������. ������ �������� ������?", "��������!", MessageBoxButtons::YesNo, MessageBoxIcon::Warning, MessageBoxDefaultButton::Button1)
				== System::Windows::Forms::DialogResult::Yes)
			{
				block_buttons();
				update_info();
				unblock_buttons();
				return;
			}
			else
			{
				//������ �� ������, ��� ��������. 
			}
		}
		const char* chars = (const char*)(Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->labelUpload_Puth->Text)).ToPointer();
		string puth = chars;
		Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr((void*)chars));

		a type;
		vector<string> access = {};
		if (radioButtonPrivate->Checked)
			type = a::a_private;
		else if (radioButtonPublic->Checked)
			type = a::a_public;
		else
		{
			type = a::a_protected;
			ListView::CheckedListViewItemCollection ^ checked = this->listViewUpload_Names->CheckedItems;
			for (int i = 0; i < checked->Count; i++)
			{
				ListViewItem ^ item = checked[i];
				const char* chars1 = (const char*)(Runtime::InteropServices::Marshal::StringToHGlobalAnsi(item->Text)).ToPointer();
				string item_text = chars;
				Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr((void*)chars));
				access.push_back(item_text);
			}
		}

		client.UploadFile(puth, type, access);
		ProgressBarUpload ^ o1 = gcnew  ProgressBarUpload(this);
		Thread^ t1 = gcnew Thread(gcnew ThreadStart(o1, &ProgressBarUpload::wait_progressBarUpload));
		t1->Name = "t1";
		t1->Start();
	}
	private: System::Void buttonUpload_Pause_Click(System::Object^  sender, System::EventArgs^  e)
	{
		client.setPauseLoad();
	}
	private: System::Void buttonUpload_Cancel_Click(System::Object^  sender, System::EventArgs^  e)
	{
		client.setEndLoad();
	}

	public: ref class ProgressBarUpload
	{
	public: Client4::ClientForm ^ this_form;
	public: ProgressBarUpload(Client4::ClientForm ^ my_form)
	{
		this_form = my_form;
	}
			delegate void StringDelegate(String^ text);
	public: void wait_progressBarUpload()
	{

		this_form->Invoke(gcnew Action(this, &ClientForm::ProgressBarUpload::start_progressBarUpload));
		while (client.isEndLoad() != true)
		{
			Thread::CurrentThread->Sleep(200);
			this_form->Invoke(gcnew Action(this, &ClientForm::ProgressBarUpload::add_progressBarUpload));
		}
		this_form->Invoke(gcnew Action(this, &ClientForm::ProgressBarUpload::stop_progressBarUpload));
		client.Update();
	}
	private: void start_progressBarUpload()
	{
		//��������� ��� ������
		this_form->buttonLog->Enabled = false;
		this_form->buttonConnect->Enabled = false;
		this_form->groupBoxUpload_Puth->Enabled = false;
		this_form->groupBoxUpload_Access->Enabled = false;
		this_form->buttonUpload->Enabled = false;
		this_form->tabControl1->TabPages[1]->Enabled = false;
		this_form->tabControl1->TabPages[2]->Enabled = false;
		this_form->tabControl1->TabPages[3]->Enabled = false;

		this_form->progressBarUpload_Loading->Minimum = 0;
		this_form->progressBarUpload_Loading->Maximum = 100;
		this_form->progressBarUpload_Loading->Value = 0;
		this_form->groupBoxUpload_Loading->Visible = true;
		this_form->progressBarUpload_Loading->Style = ProgressBarStyle::Blocks;
	}
	private: void add_progressBarUpload()
	{
		this_form->progressBarUpload_Loading->Value = client.getPercent();
	}
	private: void stop_progressBarUpload()
	{
		this_form->groupBoxUpload_Loading->Visible = false;

		//���������� ���, ��� ���������
		this_form->buttonLog->Enabled = true;
		this_form->buttonConnect->Enabled = true;
		this_form->groupBoxUpload_Puth->Enabled = true;
		this_form->groupBoxUpload_Access->Enabled = true;
		this_form->buttonUpload->Enabled = true;
		this_form->tabControl1->TabPages[1]->Enabled = true;
		this_form->tabControl1->TabPages[2]->Enabled = true;
		this_form->tabControl1->TabPages[3]->Enabled = true;
		//ClientForm::progressBar1->Style = ProgressBarStyle::Continuous;
	}
	};
#pragma endregion

#pragma region Download
	private: System::Void buttonDownload_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (client.Status() != c::avalible)
		{
			block_buttons();
			update_info();
			unblock_buttons();
			return;
		}
		if (client.isOutDated_DownloadFiles)
		{
			//�������� �����, ��������� ��� ��� �������� �������������
			if (MessageBox::Show("������ ��������� ������ �������. ������ �������� ������?", "��������!", MessageBoxButtons::YesNo, MessageBoxIcon::Warning, MessageBoxDefaultButton::Button1)
				== System::Windows::Forms::DialogResult::Yes)
			{
				block_buttons();
				update_info();
				unblock_buttons();
				return;
			}
			else
			{
				//������ �� ������, ��� ��������. 
			}
		}
		const char* chars = (const char*)(Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->comboBoxDownloadFiles->SelectedItem->ToString())).ToPointer();
		string name = chars;
		Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr((void*)chars));

		client.DownloadFile(name);
		ProgressBarDownload ^ o1 = gcnew  ProgressBarDownload(this);
		Thread^ t1 = gcnew Thread(gcnew ThreadStart(o1, &ProgressBarDownload::wait_progressBarDownload));
		t1->Name = "t1";
		t1->Start();
	}
	private: System::Void buttonDownload_Pause_Click(System::Object^  sender, System::EventArgs^  e)
	{
		client.setPauseLoad();
	}
	private: System::Void buttonDownload_Cancel_Click(System::Object^  sender, System::EventArgs^  e)
	{
		client.setEndLoad();
	}
	public: ref class ProgressBarDownload
	{
	public: Client4::ClientForm ^ this_form;
	public: ProgressBarDownload(Client4::ClientForm ^ my_form)
	{
		this_form = my_form;
	}
	public: delegate void StringDelegate(String^ text);
	public: void wait_progressBarDownload()
	{
		this_form->Invoke(gcnew Action(this, &ClientForm::ProgressBarDownload::start_progressBarDownload));
		while (client.isEndLoad() != true)
		{
			Thread::CurrentThread->Sleep(200);
			this_form->Invoke(gcnew Action(this, &ClientForm::ProgressBarDownload::add_progressBarDownload));
		}
		this_form->Invoke(gcnew Action(this, &ClientForm::ProgressBarDownload::stop_progressBarDownload));
		client.Update();
	}
	private: void start_progressBarDownload()
	{
		//��������� ��� ������
		this_form->buttonLog->Enabled = false;
		this_form->buttonConnect->Enabled = false;
		this_form->comboBoxDownloadFiles->Enabled = false;
		this_form->buttonDownload->Enabled = false;
		this_form->tabControl1->TabPages[0]->Enabled = false;
		this_form->tabControl1->TabPages[2]->Enabled = false;
		this_form->tabControl1->TabPages[3]->Enabled = false;

		this_form->progressBarDownload_Loading->Minimum = 0;
		this_form->progressBarDownload_Loading->Maximum = 100;
		this_form->progressBarDownload_Loading->Value = 0;
		this_form->groupBoxDownload_Loading->Visible = true;
		this_form->progressBarDownload_Loading->Style = ProgressBarStyle::Blocks;
	}
	private: void add_progressBarDownload()
	{
		this_form->progressBarDownload_Loading->Value = client.getPercent();
	}
	private: void stop_progressBarDownload()
	{
		this_form->groupBoxDownload_Loading->Visible = false;

		//���������� ���, ��� ���������
		this_form->buttonLog->Enabled = true;
		this_form->buttonConnect->Enabled = true;
		this_form->comboBoxDownloadFiles->Enabled = true;
		this_form->buttonDownload->Enabled = true;
		this_form->tabControl1->TabPages[0]->Enabled = true;
		this_form->tabControl1->TabPages[2]->Enabled = true;
		this_form->tabControl1->TabPages[3]->Enabled = true;
	}
	};
#pragma endregion
	
#pragma region Reupload
	private: System::Void buttonReupload_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (client.Status() != c::avalible)
		{
			block_buttons();
			update_info();
			unblock_buttons();
			return;
		}
		const char* chars = (const char*)(Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->comboBoxReupload->SelectedItem->ToString())).ToPointer();
		string name = chars;
		Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr((void*)chars));

		client.ReuploadFile(name);
		ProgressBarReupload ^ o1 = gcnew  ProgressBarReupload(this);
		Thread^ t1 = gcnew Thread(gcnew ThreadStart(o1, &ProgressBarReupload::wait_progressBarReupload));
		t1->Name = "t1";
		t1->Start();
	}
	private: System::Void buttonReupload_Pause_Click(System::Object^  sender, System::EventArgs^  e)
	{
		client.setPauseLoad();
	}
	private: System::Void buttonReupload_Cancel_Click(System::Object^  sender, System::EventArgs^  e)
	{
		client.setEndLoad();
	}
	public: ref class ProgressBarReupload
	{
	public: Client4::ClientForm ^ this_form;
	public: ProgressBarReupload(Client4::ClientForm ^ my_form)
	{
		this_form = my_form;
	}
	public: delegate void StringDelegate(String^ text);
	public: void wait_progressBarReupload()
	{
		this_form->Invoke(gcnew Action(this, &ClientForm::ProgressBarReupload::start_progressBarReupload));
		while (client.isEndLoad() != true)
		{
			Thread::CurrentThread->Sleep(200);
			this_form->Invoke(gcnew Action(this, &ClientForm::ProgressBarReupload::add_progressBarReupload));
		}
		this_form->Invoke(gcnew Action(this, &ClientForm::ProgressBarReupload::stop_progressBarReupload));
		client.Update();
	}
	private: void start_progressBarReupload()
	{
		//��������� ��� ������
		this_form->buttonLog->Enabled = false;
		this_form->buttonConnect->Enabled = false;
		this_form->comboBoxReupload->Enabled = false;
		this_form->buttonReupload->Enabled = false;
		this_form->tabControl1->TabPages[0]->Enabled = false;
		this_form->tabControl1->TabPages[1]->Enabled = false;
		this_form->tabControl1->TabPages[3]->Enabled = false;

		this_form->progressBarReupload_Loading->Minimum = 0;
		this_form->progressBarReupload_Loading->Maximum = 100;
		this_form->progressBarReupload_Loading->Value = 0;
		this_form->groupBoxReupload_Loading->Visible = true;
		this_form->progressBarReupload_Loading->Style = ProgressBarStyle::Blocks;
	}
	private: void add_progressBarReupload()
	{
		this_form->progressBarReupload_Loading->Value = client.getPercent();
	}
	private: void stop_progressBarReupload()
	{
		this_form->groupBoxReupload_Loading->Visible = false;

		//���������� ���, ��� ���������
		this_form->buttonLog->Enabled = true;
		this_form->buttonConnect->Enabled = true;
		this_form->comboBoxReupload->Enabled = true;
		this_form->buttonReupload->Enabled = true;
		this_form->tabControl1->TabPages[0]->Enabled = true;
		this_form->tabControl1->TabPages[1]->Enabled = true;
		this_form->tabControl1->TabPages[3]->Enabled = true;
	}
	};
#pragma endregion
	};
}