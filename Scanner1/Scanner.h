#pragma once

#include "Convert.h"
#include "Auxiliary.h"
#include "ConnectToHost.h"
#include "icmp_ping\ping.h"
#include <string>
#include <map>

#using <System.Drawing.dll>
#using <System.dll>
#using <System.Windows.Forms.dll>


namespace Scanner1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	using namespace std;
	/// <summary>
	/// Scanner 摘要
	/// </summary>

	//存储需要扫描的端口
	map<int, int> TCPPortMap;
	map<int, int> UDPPortMap;
	//
	//存储开放的端口(IP地址和端口的映射)
	multimap<string, int> OpenPortMap;
	//存储IP地址
	map<string, string> IPAddrMap;
	//需要扫描存活主机
	map<string, string> ScanIPAddrMap;
	//存活的主机
	map<string, string> OnlineIpAddrMap;

	public ref class Scanner : public System::Windows::Forms::Form
	{
	public:
		Scanner(void)
		{
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
			//

			InitializeParameter();

		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~Scanner()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  Scan;
	private: System::Windows::Forms::TabPage^  ScanSetting;

	private: System::Windows::Forms::GroupBox^  IPAddress;
	private: System::Windows::Forms::GroupBox^  ScanResult;
	private: System::Windows::Forms::Button^  StopButton;
	private: System::Windows::Forms::Button^  StartButton;
	private: System::Windows::Forms::RichTextBox^  Result1;
	private: System::Windows::Forms::Label^  IPAddressLabel;
	private: System::Windows::Forms::Label^  EndIPAddresslabel;
	private: System::Windows::Forms::TextBox^  EndIPAddressTextBox;
	private: System::Windows::Forms::TextBox^  StartIPAddressTextBox;
	private: System::Windows::Forms::Label^  StartIPAddresslabel;

	private: System::Windows::Forms::CheckBox^  UDPScanCheckBox;

	private: System::Windows::Forms::CheckBox^  TCPScanCheckBox;

	private: System::Windows::Forms::CheckBox^  HostCheckBox;
	private: System::Windows::Forms::ListBox^  TCPPortListBox;//
	private: System::Windows::Forms::Button^  RemoveTCPPort;//
	private: System::Windows::Forms::Button^  AddTCPPort;//
	private: System::Windows::Forms::TextBox^  TCPEndPortTextBox;//

	private: System::Windows::Forms::TextBox^  TCPStartPortTextBox;//



	private: System::Windows::Forms::Label^  TCPEndPortLabel;//
	private: System::Windows::Forms::Label^  TCPStartPortLabel;//
	private: System::Windows::Forms::ListBox^  UDPPortListBox;//
	private: System::Windows::Forms::Button^  RemoveUDPPort;//
	private: System::Windows::Forms::Button^  AddUDPPort;//
	private: System::Windows::Forms::TextBox^  UDPEndPortTextBox;//
	private: System::Windows::Forms::TextBox^  UDPStartPortTextBox;//

	private: System::Windows::Forms::Label^  UDPEndPortLabel;//
	private: System::Windows::Forms::Label^  UDPStartPortLabel;//
	private: System::Windows::Forms::Button^  ClearTCPPortButton;//
	private: System::Windows::Forms::Button^  ClearUDPPortButton;//

	private: System::Windows::Forms::Button^  RemoveIPAddress;
	private: System::Windows::Forms::ListBox^  IPAddressListBox;
	private: System::Windows::Forms::Button^  AddIPAddress;
	private: System::Windows::Forms::TextBox^  IPAddressTextBox;


	private: System::ComponentModel::BackgroundWorker^  ScanPortWorker;
	private: System::Windows::Forms::ProgressBar^  ScanPortPprogressBar;

	private: System::Windows::Forms::RichTextBox^  OnlineHostResult;

	private: System::ComponentModel::BackgroundWorker^  ScanHostWorker;



	private: System::Windows::Forms::ProgressBar^  ScanHostProgressBar;
	private: System::Windows::Forms::TextBox^  NetMask;

	private: System::Windows::Forms::TextBox^  NetWorkAddress;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  SlashLabel;
	private: System::Windows::Forms::Button^  CancelButton;




	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->Scan = (gcnew System::Windows::Forms::TabPage());
			this->ScanResult = (gcnew System::Windows::Forms::GroupBox());
			this->CancelButton = (gcnew System::Windows::Forms::Button());
			this->ScanHostProgressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->OnlineHostResult = (gcnew System::Windows::Forms::RichTextBox());
			this->ScanPortPprogressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->Result1 = (gcnew System::Windows::Forms::RichTextBox());
			this->StopButton = (gcnew System::Windows::Forms::Button());
			this->StartButton = (gcnew System::Windows::Forms::Button());
			this->IPAddress = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SlashLabel = (gcnew System::Windows::Forms::Label());
			this->NetMask = (gcnew System::Windows::Forms::TextBox());
			this->NetWorkAddress = (gcnew System::Windows::Forms::TextBox());
			this->IPAddressListBox = (gcnew System::Windows::Forms::ListBox());
			this->RemoveIPAddress = (gcnew System::Windows::Forms::Button());
			this->AddIPAddress = (gcnew System::Windows::Forms::Button());
			this->EndIPAddressTextBox = (gcnew System::Windows::Forms::TextBox());
			this->StartIPAddressTextBox = (gcnew System::Windows::Forms::TextBox());
			this->IPAddressTextBox = (gcnew System::Windows::Forms::TextBox());
			this->EndIPAddresslabel = (gcnew System::Windows::Forms::Label());
			this->StartIPAddresslabel = (gcnew System::Windows::Forms::Label());
			this->IPAddressLabel = (gcnew System::Windows::Forms::Label());
			this->ScanSetting = (gcnew System::Windows::Forms::TabPage());
			this->UDPEndPortTextBox = (gcnew System::Windows::Forms::TextBox());
			this->UDPStartPortTextBox = (gcnew System::Windows::Forms::TextBox());
			this->UDPEndPortLabel = (gcnew System::Windows::Forms::Label());
			this->UDPStartPortLabel = (gcnew System::Windows::Forms::Label());
			this->UDPPortListBox = (gcnew System::Windows::Forms::ListBox());
			this->ClearUDPPortButton = (gcnew System::Windows::Forms::Button());
			this->AddUDPPort = (gcnew System::Windows::Forms::Button());
			this->RemoveUDPPort = (gcnew System::Windows::Forms::Button());
			this->TCPEndPortLabel = (gcnew System::Windows::Forms::Label());
			this->TCPStartPortLabel = (gcnew System::Windows::Forms::Label());
			this->TCPPortListBox = (gcnew System::Windows::Forms::ListBox());
			this->TCPEndPortTextBox = (gcnew System::Windows::Forms::TextBox());
			this->TCPStartPortTextBox = (gcnew System::Windows::Forms::TextBox());
			this->ClearTCPPortButton = (gcnew System::Windows::Forms::Button());
			this->RemoveTCPPort = (gcnew System::Windows::Forms::Button());
			this->AddTCPPort = (gcnew System::Windows::Forms::Button());
			this->UDPScanCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->TCPScanCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->HostCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->ScanPortWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->ScanHostWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->tabControl1->SuspendLayout();
			this->Scan->SuspendLayout();
			this->ScanResult->SuspendLayout();
			this->IPAddress->SuspendLayout();
			this->ScanSetting->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->Scan);
			this->tabControl1->Controls->Add(this->ScanSetting);
			this->tabControl1->Location = System::Drawing::Point(12, 12);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(497, 412);
			this->tabControl1->TabIndex = 0;
			// 
			// Scan
			// 
			this->Scan->Controls->Add(this->ScanResult);
			this->Scan->Controls->Add(this->IPAddress);
			this->Scan->Location = System::Drawing::Point(4, 22);
			this->Scan->Name = L"Scan";
			this->Scan->Padding = System::Windows::Forms::Padding(3);
			this->Scan->Size = System::Drawing::Size(489, 386);
			this->Scan->TabIndex = 0;
			this->Scan->Text = L"扫描";
			this->Scan->UseVisualStyleBackColor = true;
			// 
			// ScanResult
			// 
			this->ScanResult->Controls->Add(this->CancelButton);
			this->ScanResult->Controls->Add(this->ScanHostProgressBar);
			this->ScanResult->Controls->Add(this->OnlineHostResult);
			this->ScanResult->Controls->Add(this->ScanPortPprogressBar);
			this->ScanResult->Controls->Add(this->Result1);
			this->ScanResult->Controls->Add(this->StopButton);
			this->ScanResult->Controls->Add(this->StartButton);
			this->ScanResult->Location = System::Drawing::Point(6, 172);
			this->ScanResult->Name = L"ScanResult";
			this->ScanResult->Size = System::Drawing::Size(461, 208);
			this->ScanResult->TabIndex = 1;
			this->ScanResult->TabStop = false;
			this->ScanResult->Text = L"扫描结果";
			// 
			// CancelButton
			// 
			this->CancelButton->Location = System::Drawing::Point(274, 172);
			this->CancelButton->Name = L"CancelButton";
			this->CancelButton->Size = System::Drawing::Size(48, 23);
			this->CancelButton->TabIndex = 7;
			this->CancelButton->Text = L"停止";
			this->CancelButton->UseVisualStyleBackColor = true;
			this->CancelButton->Click += gcnew System::EventHandler(this, &Scanner::CancelButton_Click);
			// 
			// ScanHostProgressBar
			// 
			this->ScanHostProgressBar->Location = System::Drawing::Point(271, 154);
			this->ScanHostProgressBar->Name = L"ScanHostProgressBar";
			this->ScanHostProgressBar->Size = System::Drawing::Size(160, 12);
			this->ScanHostProgressBar->TabIndex = 6;
			// 
			// OnlineHostResult
			// 
			this->OnlineHostResult->Location = System::Drawing::Point(261, 20);
			this->OnlineHostResult->Name = L"OnlineHostResult";
			this->OnlineHostResult->Size = System::Drawing::Size(183, 128);
			this->OnlineHostResult->TabIndex = 5;
			this->OnlineHostResult->Text = L"";
			// 
			// ScanPortPprogressBar
			// 
			this->ScanPortPprogressBar->Location = System::Drawing::Point(37, 154);
			this->ScanPortPprogressBar->Name = L"ScanPortPprogressBar";
			this->ScanPortPprogressBar->Size = System::Drawing::Size(162, 12);
			this->ScanPortPprogressBar->TabIndex = 3;
			// 
			// Result1
			// 
			this->Result1->Location = System::Drawing::Point(22, 20);
			this->Result1->Name = L"Result1";
			this->Result1->Size = System::Drawing::Size(192, 128);
			this->Result1->TabIndex = 2;
			this->Result1->Text = L"";
			// 
			// StopButton
			// 
			this->StopButton->Location = System::Drawing::Point(220, 172);
			this->StopButton->Name = L"StopButton";
			this->StopButton->Size = System::Drawing::Size(48, 23);
			this->StopButton->TabIndex = 1;
			this->StopButton->Text = L"暂停";
			this->StopButton->UseVisualStyleBackColor = true;
			this->StopButton->Click += gcnew System::EventHandler(this, &Scanner::StopButton_Click);
			// 
			// StartButton
			// 
			this->StartButton->Location = System::Drawing::Point(163, 172);
			this->StartButton->Name = L"StartButton";
			this->StartButton->Size = System::Drawing::Size(51, 23);
			this->StartButton->TabIndex = 0;
			this->StartButton->Text = L"开始";
			this->StartButton->UseVisualStyleBackColor = true;
			this->StartButton->Click += gcnew System::EventHandler(this, &Scanner::StartButton_Click);
			// 
			// IPAddress
			// 
			this->IPAddress->Controls->Add(this->label1);
			this->IPAddress->Controls->Add(this->SlashLabel);
			this->IPAddress->Controls->Add(this->NetMask);
			this->IPAddress->Controls->Add(this->NetWorkAddress);
			this->IPAddress->Controls->Add(this->IPAddressListBox);
			this->IPAddress->Controls->Add(this->RemoveIPAddress);
			this->IPAddress->Controls->Add(this->AddIPAddress);
			this->IPAddress->Controls->Add(this->EndIPAddressTextBox);
			this->IPAddress->Controls->Add(this->StartIPAddressTextBox);
			this->IPAddress->Controls->Add(this->IPAddressTextBox);
			this->IPAddress->Controls->Add(this->EndIPAddresslabel);
			this->IPAddress->Controls->Add(this->StartIPAddresslabel);
			this->IPAddress->Controls->Add(this->IPAddressLabel);
			this->IPAddress->Location = System::Drawing::Point(6, 6);
			this->IPAddress->Name = L"IPAddress";
			this->IPAddress->Size = System::Drawing::Size(461, 160);
			this->IPAddress->TabIndex = 0;
			this->IPAddress->TabStop = false;
			this->IPAddress->Text = L"IP地址";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(8, 129);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(89, 12);
			this->label1->TabIndex = 12;
			this->label1->Text = L"网络地址范围：";
			// 
			// SlashLabel
			// 
			this->SlashLabel->AutoSize = true;
			this->SlashLabel->Location = System::Drawing::Point(209, 129);
			this->SlashLabel->Name = L"SlashLabel";
			this->SlashLabel->Size = System::Drawing::Size(11, 12);
			this->SlashLabel->TabIndex = 11;
			this->SlashLabel->Text = L"/";
			// 
			// NetMask
			// 
			this->NetMask->Location = System::Drawing::Point(226, 126);
			this->NetMask->Name = L"NetMask";
			this->NetMask->Size = System::Drawing::Size(100, 21);
			this->NetMask->TabIndex = 10;
			// 
			// NetWorkAddress
			// 
			this->NetWorkAddress->Location = System::Drawing::Point(103, 126);
			this->NetWorkAddress->Name = L"NetWorkAddress";
			this->NetWorkAddress->Size = System::Drawing::Size(100, 21);
			this->NetWorkAddress->TabIndex = 9;
			// 
			// IPAddressListBox
			// 
			this->IPAddressListBox->FormattingEnabled = true;
			this->IPAddressListBox->ItemHeight = 12;
			this->IPAddressListBox->Location = System::Drawing::Point(271, 20);
			this->IPAddressListBox->Name = L"IPAddressListBox";
			this->IPAddressListBox->Size = System::Drawing::Size(173, 100);
			this->IPAddressListBox->TabIndex = 8;
			// 
			// RemoveIPAddress
			// 
			this->RemoveIPAddress->Location = System::Drawing::Point(214, 69);
			this->RemoveIPAddress->Name = L"RemoveIPAddress";
			this->RemoveIPAddress->Size = System::Drawing::Size(40, 30);
			this->RemoveIPAddress->TabIndex = 7;
			this->RemoveIPAddress->Text = L"<<";
			this->RemoveIPAddress->UseVisualStyleBackColor = true;
			this->RemoveIPAddress->Click += gcnew System::EventHandler(this, &Scanner::RemoveIPAddress_Click);
			// 
			// AddIPAddress
			// 
			this->AddIPAddress->Location = System::Drawing::Point(214, 26);
			this->AddIPAddress->Name = L"AddIPAddress";
			this->AddIPAddress->Size = System::Drawing::Size(40, 30);
			this->AddIPAddress->TabIndex = 6;
			this->AddIPAddress->Text = L">>";
			this->AddIPAddress->UseVisualStyleBackColor = true;
			this->AddIPAddress->Click += gcnew System::EventHandler(this, &Scanner::AddIPAddress_Click);
			// 
			// EndIPAddressTextBox
			// 
			this->EndIPAddressTextBox->Location = System::Drawing::Point(99, 93);
			this->EndIPAddressTextBox->Name = L"EndIPAddressTextBox";
			this->EndIPAddressTextBox->Size = System::Drawing::Size(100, 21);
			this->EndIPAddressTextBox->TabIndex = 5;
			// 
			// StartIPAddressTextBox
			// 
			this->StartIPAddressTextBox->Location = System::Drawing::Point(99, 66);
			this->StartIPAddressTextBox->Name = L"StartIPAddressTextBox";
			this->StartIPAddressTextBox->Size = System::Drawing::Size(100, 21);
			this->StartIPAddressTextBox->TabIndex = 4;
			// 
			// IPAddressTextBox
			// 
			this->IPAddressTextBox->Location = System::Drawing::Point(99, 32);
			this->IPAddressTextBox->Name = L"IPAddressTextBox";
			this->IPAddressTextBox->Size = System::Drawing::Size(100, 21);
			this->IPAddressTextBox->TabIndex = 3;
			// 
			// EndIPAddresslabel
			// 
			this->EndIPAddresslabel->AutoSize = true;
			this->EndIPAddresslabel->Location = System::Drawing::Point(20, 96);
			this->EndIPAddresslabel->Name = L"EndIPAddresslabel";
			this->EndIPAddresslabel->Size = System::Drawing::Size(77, 12);
			this->EndIPAddresslabel->TabIndex = 2;
			this->EndIPAddresslabel->Text = L"结束IP地址：";
			// 
			// StartIPAddresslabel
			// 
			this->StartIPAddresslabel->AutoSize = true;
			this->StartIPAddresslabel->Location = System::Drawing::Point(20, 69);
			this->StartIPAddresslabel->Name = L"StartIPAddresslabel";
			this->StartIPAddresslabel->Size = System::Drawing::Size(77, 12);
			this->StartIPAddresslabel->TabIndex = 1;
			this->StartIPAddresslabel->Text = L"开始IP地址：";
			// 
			// IPAddressLabel
			// 
			this->IPAddressLabel->AutoSize = true;
			this->IPAddressLabel->Location = System::Drawing::Point(20, 35);
			this->IPAddressLabel->Name = L"IPAddressLabel";
			this->IPAddressLabel->Size = System::Drawing::Size(77, 12);
			this->IPAddressLabel->TabIndex = 0;
			this->IPAddressLabel->Text = L"主机IP地址：";
			// 
			// ScanSetting
			// 
			this->ScanSetting->Controls->Add(this->UDPEndPortTextBox);
			this->ScanSetting->Controls->Add(this->UDPStartPortTextBox);
			this->ScanSetting->Controls->Add(this->UDPEndPortLabel);
			this->ScanSetting->Controls->Add(this->UDPStartPortLabel);
			this->ScanSetting->Controls->Add(this->UDPPortListBox);
			this->ScanSetting->Controls->Add(this->ClearUDPPortButton);
			this->ScanSetting->Controls->Add(this->AddUDPPort);
			this->ScanSetting->Controls->Add(this->RemoveUDPPort);
			this->ScanSetting->Controls->Add(this->TCPEndPortLabel);
			this->ScanSetting->Controls->Add(this->TCPStartPortLabel);
			this->ScanSetting->Controls->Add(this->TCPPortListBox);
			this->ScanSetting->Controls->Add(this->TCPEndPortTextBox);
			this->ScanSetting->Controls->Add(this->TCPStartPortTextBox);
			this->ScanSetting->Controls->Add(this->ClearTCPPortButton);
			this->ScanSetting->Controls->Add(this->RemoveTCPPort);
			this->ScanSetting->Controls->Add(this->AddTCPPort);
			this->ScanSetting->Controls->Add(this->UDPScanCheckBox);
			this->ScanSetting->Controls->Add(this->TCPScanCheckBox);
			this->ScanSetting->Controls->Add(this->HostCheckBox);
			this->ScanSetting->Location = System::Drawing::Point(4, 22);
			this->ScanSetting->Name = L"ScanSetting";
			this->ScanSetting->Padding = System::Windows::Forms::Padding(3);
			this->ScanSetting->Size = System::Drawing::Size(489, 386);
			this->ScanSetting->TabIndex = 1;
			this->ScanSetting->Text = L"扫描参数设置";
			this->ScanSetting->UseVisualStyleBackColor = true;
			// 
			// UDPEndPortTextBox
			// 
			this->UDPEndPortTextBox->Location = System::Drawing::Point(85, 286);
			this->UDPEndPortTextBox->Name = L"UDPEndPortTextBox";
			this->UDPEndPortTextBox->Size = System::Drawing::Size(59, 21);
			this->UDPEndPortTextBox->TabIndex = 20;
			// 
			// UDPStartPortTextBox
			// 
			this->UDPStartPortTextBox->Location = System::Drawing::Point(84, 253);
			this->UDPStartPortTextBox->Name = L"UDPStartPortTextBox";
			this->UDPStartPortTextBox->Size = System::Drawing::Size(60, 21);
			this->UDPStartPortTextBox->TabIndex = 19;
			// 
			// UDPEndPortLabel
			// 
			this->UDPEndPortLabel->AutoSize = true;
			this->UDPEndPortLabel->Location = System::Drawing::Point(18, 289);
			this->UDPEndPortLabel->Name = L"UDPEndPortLabel";
			this->UDPEndPortLabel->Size = System::Drawing::Size(65, 12);
			this->UDPEndPortLabel->TabIndex = 17;
			this->UDPEndPortLabel->Text = L"结束端口：";
			// 
			// UDPStartPortLabel
			// 
			this->UDPStartPortLabel->AutoSize = true;
			this->UDPStartPortLabel->Location = System::Drawing::Point(18, 259);
			this->UDPStartPortLabel->Name = L"UDPStartPortLabel";
			this->UDPStartPortLabel->Size = System::Drawing::Size(65, 12);
			this->UDPStartPortLabel->TabIndex = 16;
			this->UDPStartPortLabel->Text = L"开始端口：";
			// 
			// UDPPortListBox
			// 
			this->UDPPortListBox->FormattingEnabled = true;
			this->UDPPortListBox->ItemHeight = 12;
			this->UDPPortListBox->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"25", L"53", L"137", L"138", L"161" });
			this->UDPPortListBox->Location = System::Drawing::Point(265, 248);
			this->UDPPortListBox->Name = L"UDPPortListBox";
			this->UDPPortListBox->Size = System::Drawing::Size(120, 88);
			this->UDPPortListBox->TabIndex = 15;
			// 
			// ClearUDPPortButton
			// 
			this->ClearUDPPortButton->Location = System::Drawing::Point(170, 306);
			this->ClearUDPPortButton->Name = L"ClearUDPPortButton";
			this->ClearUDPPortButton->Size = System::Drawing::Size(56, 23);
			this->ClearUDPPortButton->TabIndex = 14;
			this->ClearUDPPortButton->Text = L"清空";
			this->ClearUDPPortButton->UseVisualStyleBackColor = true;
			this->ClearUDPPortButton->Click += gcnew System::EventHandler(this, &Scanner::ClearUDPPortButton_Click);
			// 
			// AddUDPPort
			// 
			this->AddUDPPort->Location = System::Drawing::Point(170, 248);
			this->AddUDPPort->Name = L"AddUDPPort";
			this->AddUDPPort->Size = System::Drawing::Size(56, 23);
			this->AddUDPPort->TabIndex = 13;
			this->AddUDPPort->Text = L"添加";
			this->AddUDPPort->UseVisualStyleBackColor = true;
			this->AddUDPPort->Click += gcnew System::EventHandler(this, &Scanner::AddUDPPort_Click);
			// 
			// RemoveUDPPort
			// 
			this->RemoveUDPPort->Location = System::Drawing::Point(170, 277);
			this->RemoveUDPPort->Name = L"RemoveUDPPort";
			this->RemoveUDPPort->Size = System::Drawing::Size(56, 23);
			this->RemoveUDPPort->TabIndex = 12;
			this->RemoveUDPPort->Text = L"删除";
			this->RemoveUDPPort->UseVisualStyleBackColor = true;
			this->RemoveUDPPort->Click += gcnew System::EventHandler(this, &Scanner::RemoveUDPPort_Click);
			// 
			// TCPEndPortLabel
			// 
			this->TCPEndPortLabel->AutoSize = true;
			this->TCPEndPortLabel->Location = System::Drawing::Point(18, 163);
			this->TCPEndPortLabel->Name = L"TCPEndPortLabel";
			this->TCPEndPortLabel->Size = System::Drawing::Size(65, 12);
			this->TCPEndPortLabel->TabIndex = 11;
			this->TCPEndPortLabel->Text = L"结束端口：";
			// 
			// TCPStartPortLabel
			// 
			this->TCPStartPortLabel->AutoSize = true;
			this->TCPStartPortLabel->Location = System::Drawing::Point(18, 131);
			this->TCPStartPortLabel->Name = L"TCPStartPortLabel";
			this->TCPStartPortLabel->Size = System::Drawing::Size(65, 12);
			this->TCPStartPortLabel->TabIndex = 10;
			this->TCPStartPortLabel->Text = L"开始端口：";
			// 
			// TCPPortListBox
			// 
			this->TCPPortListBox->FormattingEnabled = true;
			this->TCPPortListBox->ItemHeight = 12;
			this->TCPPortListBox->Items->AddRange(gcnew cli::array< System::Object^  >(8) {
				L"21", L"22", L"23", L"25", L"53", L"80",
					L"143", L"443"
			});
			this->TCPPortListBox->Location = System::Drawing::Point(266, 120);
			this->TCPPortListBox->Name = L"TCPPortListBox";
			this->TCPPortListBox->Size = System::Drawing::Size(120, 88);
			this->TCPPortListBox->TabIndex = 9;
			// 
			// TCPEndPortTextBox
			// 
			this->TCPEndPortTextBox->Location = System::Drawing::Point(85, 160);
			this->TCPEndPortTextBox->Name = L"TCPEndPortTextBox";
			this->TCPEndPortTextBox->Size = System::Drawing::Size(59, 21);
			this->TCPEndPortTextBox->TabIndex = 7;
			// 
			// TCPStartPortTextBox
			// 
			this->TCPStartPortTextBox->Location = System::Drawing::Point(85, 128);
			this->TCPStartPortTextBox->Name = L"TCPStartPortTextBox";
			this->TCPStartPortTextBox->Size = System::Drawing::Size(59, 21);
			this->TCPStartPortTextBox->TabIndex = 6;
			// 
			// ClearTCPPortButton
			// 
			this->ClearTCPPortButton->Location = System::Drawing::Point(170, 180);
			this->ClearTCPPortButton->Name = L"ClearTCPPortButton";
			this->ClearTCPPortButton->Size = System::Drawing::Size(56, 23);
			this->ClearTCPPortButton->TabIndex = 5;
			this->ClearTCPPortButton->Text = L"清空";
			this->ClearTCPPortButton->UseVisualStyleBackColor = true;
			this->ClearTCPPortButton->Click += gcnew System::EventHandler(this, &Scanner::ClearTCPPortButton_Click);
			// 
			// RemoveTCPPort
			// 
			this->RemoveTCPPort->Location = System::Drawing::Point(170, 150);
			this->RemoveTCPPort->Name = L"RemoveTCPPort";
			this->RemoveTCPPort->Size = System::Drawing::Size(56, 23);
			this->RemoveTCPPort->TabIndex = 4;
			this->RemoveTCPPort->Text = L"删除";
			this->RemoveTCPPort->UseVisualStyleBackColor = true;
			this->RemoveTCPPort->Click += gcnew System::EventHandler(this, &Scanner::RemoveTCPPort_Click);
			// 
			// AddTCPPort
			// 
			this->AddTCPPort->Location = System::Drawing::Point(170, 120);
			this->AddTCPPort->Name = L"AddTCPPort";
			this->AddTCPPort->Size = System::Drawing::Size(56, 23);
			this->AddTCPPort->TabIndex = 3;
			this->AddTCPPort->Text = L"添加";
			this->AddTCPPort->UseVisualStyleBackColor = true;
			this->AddTCPPort->Click += gcnew System::EventHandler(this, &Scanner::AddTCPPort_Click);
			// 
			// UDPScanCheckBox
			// 
			this->UDPScanCheckBox->AutoSize = true;
			this->UDPScanCheckBox->Location = System::Drawing::Point(27, 231);
			this->UDPScanCheckBox->Name = L"UDPScanCheckBox";
			this->UDPScanCheckBox->Size = System::Drawing::Size(90, 16);
			this->UDPScanCheckBox->TabIndex = 2;
			this->UDPScanCheckBox->Text = L"UDP端口扫描";
			this->UDPScanCheckBox->UseVisualStyleBackColor = true;
			// 
			// TCPScanCheckBox
			// 
			this->TCPScanCheckBox->AutoSize = true;
			this->TCPScanCheckBox->Checked = true;
			this->TCPScanCheckBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->TCPScanCheckBox->Location = System::Drawing::Point(27, 97);
			this->TCPScanCheckBox->Name = L"TCPScanCheckBox";
			this->TCPScanCheckBox->Size = System::Drawing::Size(90, 16);
			this->TCPScanCheckBox->TabIndex = 1;
			this->TCPScanCheckBox->Text = L"TCP端口扫描";
			this->TCPScanCheckBox->UseVisualStyleBackColor = true;
			// 
			// HostCheckBox
			// 
			this->HostCheckBox->AutoSize = true;
			this->HostCheckBox->Checked = true;
			this->HostCheckBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->HostCheckBox->Location = System::Drawing::Point(27, 25);
			this->HostCheckBox->Name = L"HostCheckBox";
			this->HostCheckBox->Size = System::Drawing::Size(156, 16);
			this->HostCheckBox->TabIndex = 0;
			this->HostCheckBox->Text = L"扫描存活主机（局域网）";
			this->HostCheckBox->UseVisualStyleBackColor = true;
			// 
			// ScanPortWorker
			// 
			this->ScanPortWorker->WorkerReportsProgress = true;
			this->ScanPortWorker->WorkerSupportsCancellation = true;
			this->ScanPortWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Scanner::ScanPortWorker_DoWork);
			this->ScanPortWorker->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Scanner::ScanPortWorker_ProgressChanged);
			this->ScanPortWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Scanner::ScanPortWorker_DoCompleted);
			// 
			// ScanHostWorker
			// 
			this->ScanHostWorker->WorkerReportsProgress = true;
			this->ScanHostWorker->WorkerSupportsCancellation = true;
			this->ScanHostWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Scanner::ScanHostWorker_DoWork);
			this->ScanHostWorker->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Scanner::ScanHostWorker_ProgressChanged);
			this->ScanHostWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Scanner::ScanHostWorker_DoCompleted);
			// 
			// Scanner
			// 
			this->ClientSize = System::Drawing::Size(514, 431);
			this->Controls->Add(this->tabControl1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"Scanner";
			this->ShowIcon = false;
			this->Text = L"MiniScan";
			this->Load += gcnew System::EventHandler(this, &Scanner::Scanner_Load);
			this->tabControl1->ResumeLayout(false);
			this->Scan->ResumeLayout(false);
			this->ScanResult->ResumeLayout(false);
			this->IPAddress->ResumeLayout(false);
			this->IPAddress->PerformLayout();
			this->ScanSetting->ResumeLayout(false);
			this->ScanSetting->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void Scanner_Load(System::Object^  sender, System::EventArgs^  e) {
	}	 

//开始扫描处理函数
	private: System::Void StartButton_Click(System::Object^  sender, System::EventArgs^  e) {
		// 清空IP和端口对应的映射变量
		ClearParameter();
		this->ScanPortPprogressBar->Value = 0;
		this->ScanHostProgressBar->Value = 0;
		this->Result1->Text = String::Empty;
		this->OnlineHostResult->Text = String::Empty;
		this->Result1->Text = "扫描中,请稍候...\n";
		this->OnlineHostResult->Text = "存活主机数：";
		this->StartButton->Enabled = false;
		this->StopButton->Enabled = true;
		this->CancelButton->Enabled = true;
		HandleHostIPMap(sender, e);
		if (this->HostCheckBox->Checked) {
			ScanHostWorker->RunWorkerAsync();
		}
		ScanPortWorker->RunWorkerAsync();
	}

		 //停止按钮处理函数
private: System::Void StopButton_Click(System::Object^  sender, System::EventArgs^  e) {
	//this->ScanPortWorker->CancelAsync();
	//this->ScanPortWorker->CancellationPending;
	//this->ScanHostWorker->CancelAsync();
	//this->StopButton->Enabled = false;
	//this->StartButton->Enabled = true;
	if (this->StopButton->Text == "暂停") {
		ScanHostMR->Reset();
		ScanPortMR->Reset();
		this->StopButton->Text = "继续";
	}
	else {
		ScanHostMR->Set();
		ScanPortMR->Set();
		this->StopButton->Text = "暂停";
	}
}

		 //取消按钮
private: System::Void CancelButton_Click(System::Object^  sender, System::EventArgs^  e) {
	this->ScanHostWorker->CancelAsync();
	this->ScanPortWorker->CancelAsync();
	this->StartButton->Enabled = true;
}

//添加TCP端口的点击按钮函数
private: System::Void AddTCPPort_Click(System::Object^  sender, System::EventArgs^  e) {

	//处理一个端口的
	if (this->TCPStartPortTextBox->Text->Length > 5 || this->TCPStartPortTextBox->Text->Length <= 0)
		return;
	if (this->TCPEndPortTextBox->Text->Length <= 0)
		this->TCPEndPortTextBox->Text = "0";
	if (this->TCPEndPortTextBox->Text->Length > 5)
		return;
	String^ tmp1 = this->TCPStartPortTextBox->Text;
	String^ tmp2 = this->TCPEndPortTextBox->Text;
	int eport = int::Parse(tmp2);
	int sport = int::Parse(tmp1);
	if ((sport < 1 || sport >65534) && (eport <1 || sport > 65534))
		return;
	if (eport <= sport && (TCPPortMap[sport] != sport)) {
		TCPPortMap[sport] = sport;
		this->TCPPortListBox->Items->Add(tmp1);
	}

	//处理范围端口的
	if (sport < eport) {
		int tmp_port = sport;
		while (tmp_port <= eport) {
			TCPPortMap[tmp_port] = tmp_port;
			++tmp_port;
		}
		this->TCPPortListBox->Items->Add(Convert::ToString(sport + "-" + eport));
	}
	
	this->TCPStartPortTextBox->Text = String::Empty;
	this->TCPEndPortTextBox->Text = String::Empty;
}	

//删除TCP端口的点击按钮函数
private: System::Void RemoveTCPPort_Click(System::Object^  sender, System::EventArgs^  e) {
	if (!this->TCPPortListBox->SelectedItem)
		return;
	String^ tmp = this->TCPPortListBox->SelectedItem->ToString();
	string str;
	MarshalString(tmp, str);
	int index = str.find("-");
	if (index <= 0) {
		int port = int::Parse(tmp);
		TCPPortMap.erase(port);
		this->TCPPortListBox->Items->Remove(tmp);
	}
	else {
		string str_sport = str.substr(0, index);
		string str_eport = str.substr(index + 1, str.length());
		int sport = atoi(str_sport.c_str());
		int eport = atoi(str_eport.c_str());
		this->TCPPortListBox->Items->Remove(tmp);
		while (sport <= eport){
			TCPPortMap.erase(sport);
			++sport;
		}

	}
}

		 //添加UDP端口的点击按钮函数
private: System::Void AddUDPPort_Click(System::Object^  sender, System::EventArgs^  e) {
	//处理一个端口的
	if (this->UDPStartPortTextBox->Text->Length > 5 || this->UDPStartPortTextBox->Text->Length <= 0)
		return;
	if (this->UDPEndPortTextBox->Text->Length <= 0)
		this->UDPEndPortTextBox->Text = "0";
	if (this->UDPEndPortTextBox->Text->Length > 5)
		return;
	String^ tmp1 = this->UDPStartPortTextBox->Text;
	String^ tmp2 = this->UDPEndPortTextBox->Text;
	int eport = int::Parse(tmp2);
	int sport = int::Parse(tmp1);
	if ((sport < 1 || sport >65534) && (eport <1 || sport > 65534))
		return;
	if (eport <= sport && (UDPPortMap[sport] != sport)) {
		UDPPortMap[sport] = sport;
		this->UDPPortListBox->Items->Add(tmp1);
	}

	//处理范围端口的
	if (sport < eport) {
		int tmp_port = sport;
		while (tmp_port <= eport) {
			UDPPortMap[tmp_port] = tmp_port;
			++tmp_port;
		}
		this->UDPPortListBox->Items->Add(Convert::ToString(sport + "-" + eport));
	}

	this->UDPStartPortTextBox->Text = String::Empty;
	this->UDPEndPortTextBox->Text = String::Empty;

}
		 //删除UDP端口处理函数
private: System::Void RemoveUDPPort_Click(System::Object^  sender, System::EventArgs^  e) {
	if (!this->UDPPortListBox->SelectedItem)
		return;
	String^ tmp = this->UDPPortListBox->SelectedItem->ToString();
	string str;
	MarshalString(tmp, str);
	int index = str.find("-");
	if (index <= 0) {
		int port = int::Parse(tmp);
		UDPPortMap.erase(port);
		this->UDPPortListBox->Items->Remove(tmp);
	}
	else {
		string str_sport = str.substr(0, index);
		string str_eport = str.substr(index + 1, str.length());
		int sport = atoi(str_sport.c_str());
		int eport = atoi(str_eport.c_str());
		this->UDPPortListBox->Items->Remove(tmp);
		while (sport <= eport){
			UDPPortMap.erase(sport);
			++sport;
		}

	}
}
		 //清空TCP端口处理函数
private: System::Void ClearTCPPortButton_Click(System::Object^  sender, System::EventArgs^  e) {
	this->TCPPortListBox->Items->Clear();
	TCPPortMap.clear();
}
		 //清空UDP端口处理函数
private: System::Void ClearUDPPortButton_Click(System::Object^  sender, System::EventArgs^  e) {
	this->UDPPortListBox->Items->Clear();
	UDPPortMap.clear();
}

		 //添加IP地址处理函数
private: System::Void AddIPAddress_Click(System::Object^  sender, System::EventArgs^  e) {
	string str_ipaddr;
	string start_ipaddr;
	string end_ipaddr;
	if (this->IPAddressTextBox->Text->Length > 7) {
		MarshalString(this->IPAddressTextBox->Text, str_ipaddr);
		this->IPAddressListBox->Items->Add(this->IPAddressTextBox->Text);
		IPAddrMap.insert({ str_ipaddr, str_ipaddr });
	}
	
	if (this->StartIPAddressTextBox->Text->Length >= 7 && this->EndIPAddressTextBox->Text->Length >=7) {
		MarshalString(this->StartIPAddressTextBox->Text, start_ipaddr);
		MarshalString(this->EndIPAddressTextBox->Text, end_ipaddr);
		GenerateAddressRange(IPAddrMap, start_ipaddr, end_ipaddr);
		this->IPAddressListBox->Items->Add(this->StartIPAddressTextBox->Text + "-" + this->EndIPAddressTextBox->Text);
	}
	this->IPAddressTextBox->Text = String::Empty;
	this->StartIPAddressTextBox->Text = String::Empty;
	this->EndIPAddressTextBox->Text = String::Empty;
}
		 
		 //删除IP地址
private: System::Void RemoveIPAddress_Click(System::Object^  sender, System::EventArgs^  e) {

	if (!this->IPAddressListBox->SelectedItem)
		return;
	String^ tmp_addr = this->IPAddressListBox->SelectedItem->ToString();
	string ipAddr;
	this->IPAddressListBox->Items->Remove(tmp_addr);
	MarshalString(tmp_addr, ipAddr);

	if (ipAddr.find("-") >=0) {
		string start_ipaddr = ipAddr.substr(0, ipAddr.find("-"));
		string end_ipaddr = ipAddr.substr(ipAddr.find("-") + 1, ipAddr.length());
		RemoveAddressRange(IPAddrMap, start_ipaddr, end_ipaddr);
	}
	else {
		IPAddrMap.erase(ipAddr);
	}
	//for (auto item = IPAddrMap.cbegin(); item != IPAddrMap.cend(); ++item) {
	//	this->Result1->Text += gcnew String(item->first.c_str());
	//}
}

		 //初始化某些变量，比如端口容器
private:System::Void InitializeParameter() {

		//初始值TCP端口的容器
		for each (String^ itemValue in TCPPortListBox->Items)
		{
			int port = int::Parse(itemValue);
			TCPPortMap[port] = port;
		}

		//初始值UDP端口的容器
		for each (String^ itemValue in UDPPortListBox->Items)
		{
			int port = int::Parse(itemValue);
			UDPPortMap[port] = port;
		}

	}
		//清空一些变量
		System::Void ClearParameter() {
			OnlineIpAddrMap.clear();
			OpenPortMap.clear();
		}

	//部分功能函数
private:
	ManualResetEvent^ ScanHostMR = gcnew ManualResetEvent(true);
	ManualResetEvent^ ScanPortMR = gcnew ManualResetEvent(true);
	System::Void ScanTCPorUDP(Object^ sender, DoWorkEventArgs^ e){
		int size = 0;
		if (TCPScanCheckBox->Checked && UDPScanCheckBox->Checked)
			size = IPAddrMap.size() * (TCPPortMap.size() + UDPPortMap.size());
		else if (TCPScanCheckBox->Checked && !UDPScanCheckBox->Checked)
			size = IPAddrMap.size() * TCPPortMap.size();
		else if (!TCPScanCheckBox->Checked && UDPScanCheckBox->Checked)
			size = IPAddrMap.size() * UDPPortMap.size();
		int progressValue=0;
		//每个IP地址扫描一次
		for (auto item_addr = IPAddrMap.begin(); item_addr != IPAddrMap.end(); ++item_addr){
			//检查是否TCP扫描
			if (TCPScanCheckBox->Checked){
				for (auto item = TCPPortMap.begin(); item != TCPPortMap.end(); ++item) {
					++progressValue;
					if (!ScanPortWorker->CancellationPending) {
						if (ConnectToHostTCP(item->second, item_addr->first.c_str()))
							OpenPortMap.insert({ item_addr->first, item->second });
						CloseConnection();
					}
					else {
						CloseConnection();
						e->Cancel = true;
						return;
					}
					ScanPortMR->WaitOne();
					int pregressPercent = (float)progressValue / (float)size * 100;
					this->ScanPortWorker->ReportProgress(pregressPercent);
				}
			}
			//检查是否UDP扫描
			if (UDPScanCheckBox->Checked) {
				for (auto item = UDPPortMap.begin(); item != UDPPortMap.end(); ++item) {
					++progressValue;
					if (!ScanPortWorker->CancellationPending) {
						if (ConnectToHostUDP(item->second, item_addr->first.c_str()))
							OpenPortMap.insert({ item_addr->first, item->second });
						CloseConnection();
					}
					else {
						CloseConnection();
						e->Cancel = true;
						return;
					}
					ScanPortMR->WaitOne();
					int pregressPercent = (float)progressValue / (float)size * 100;
					this->ScanPortWorker->ReportProgress(pregressPercent);
				}
			}
		}
	}
	System::Void HandleHostIPMap(System::Object^ sender,System::EventArgs^  e) {
		for (auto item = IPAddrMap.cbegin(); item != IPAddrMap.cend(); ++item) {
			ScanIPAddrMap.insert({ item->second, item->second });
		}
		if (this->NetMask->Text->Length == 0 || this->NetWorkAddress->Text->Length == 0)
			return;
		string net_addr;
		string net_mask;
		MarshalString(this->NetWorkAddress->Text, net_addr);
		MarshalString(this->NetMask->Text, net_mask);
		u_long bcast = inet_addr(net_addr.c_str()) | (~inet_addr(net_mask.c_str()));
		in_addr addr;
		addr.S_un.S_addr = bcast;
		string bcast_addr = string(inet_ntoa(addr));
		GenerateAddressRange(ScanIPAddrMap, net_addr, bcast_addr);
		GenerateAddressRange(IPAddrMap, net_addr, bcast_addr);
	}

private: System::Void ScanPortWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^ e) {
	ScanTCPorUDP(sender, e);
}

		 System::Void ScanPortWorker_DoCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e) {

			 //格式输出
			 for (auto item1 = IPAddrMap.begin(); item1 != IPAddrMap.end(); ++item1){
				 this->Result1->Text += "--------------------------\n";
				 this->Result1->Text += gcnew String(item1->first.c_str()) + " 开放端口：\n";
				 multimap<string, int>::const_iterator item2 = OpenPortMap.cbegin();
				 while (item2 != OpenPortMap.cend()) {
					 if (item2->first == item1->first)
						 this->Result1->Text += "\t" + item2->second + "  " + gcnew String(GetServerNameByPort(item2->second).c_str()) + "\n";
					 ++item2;
				 }
			 }

			 if (e->Cancelled) {
				 this->Result1->Text += "--------------------------\n";
				 this->Result1->Text += "暂停扫描\n";
			 }
			 else {
				 this->Result1->Text += "--------------------------\n";
				 this->Result1->Text += "扫描完成\n";
			 }
			 if ((this->ScanPortPprogressBar->Value == 0 && this->ScanHostProgressBar->Value == 100) || 
				 (this->ScanPortPprogressBar->Value == 100 && this->ScanHostProgressBar->Value == 100)) {
				 this->StartButton->Enabled = true;
				 this->StopButton->Enabled = false;
				 this->CancelButton->Enabled = false;
			 }
			 //OpenPortMap.clear();
		 }

		 System::Void ScanPortWorker_ProgressChanged(System::Object ^sender, System::ComponentModel::ProgressChangedEventArgs^ e) {
			 this->ScanPortPprogressBar->Value = e->ProgressPercentage;
		 }

private: System::Void ScanHostWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
	int sum = ScanIPAddrMap.size();
	int progressValue = 0;
	for (auto item = ScanIPAddrMap.cbegin(); item != ScanIPAddrMap.cend(); ++item) {
		++progressValue;
		if (!ScanHostWorker->CancellationPending) {
			if (ICMPping(item->second.c_str(), 1, 32)) {
				OnlineIpAddrMap.insert({ item->second, item->second });
			}
		}
		else {
			e->Cancel = true;
			return;
		}
		ScanHostMR->WaitOne();
		int precentComplete = float(progressValue) / float(sum) * 100;
		this->ScanHostWorker->ReportProgress(precentComplete);
	}
}
		 System::Void ScanHostWorker_DoCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e) {
			 this->OnlineHostResult->Text += OnlineIpAddrMap.size() + "\n";
			 for (auto item = OnlineIpAddrMap.cbegin(); item != OnlineIpAddrMap.cend(); ++item) {
				 this->OnlineHostResult->Text += "\t" + gcnew String(item->first.c_str()) + "\n";
			 }
			 this->OnlineHostResult->Text += "--------------------------\n";
			 //OnlineIpAddrMap.clear();
			 //ScanIPAddrMap.clear();
			 if ((this->ScanPortPprogressBar->Value == 100 && this->ScanHostProgressBar->Value == 0) ||
				 (this->ScanPortPprogressBar->Value == 100 && this->ScanHostProgressBar->Value == 100)) {
				 this->StartButton->Enabled = true;
				 this->StopButton->Enabled = false;
				 this->CancelButton->Enabled = false;
			 }
			 this->OnlineHostResult->Text += "完成\n";
		 }
		 System::Void ScanHostWorker_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e) {
			 this->ScanHostProgressBar->Value = e->ProgressPercentage;
		 }

};
}
