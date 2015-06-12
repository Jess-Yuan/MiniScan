#pragma once

#include "Convert.h"
#include <string>
#include "ConnectToHost.h"
#include <map>
#using <System.Drawing.dll>
#using <System.dll>


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
	//存储开放的端口
	multimap<string, int> OpenPortMap;
	//存储IP地址
	map<string, string> IPAddrMap;

	// 处理扫描的变量
	map<int, int>::iterator item_tcp;
	map<int, int>::iterator item_udp = UDPPortMap.begin();
	DWORD WINAPI ProcConnect1(LPVOID lpParam);
	DWORD WINAPI ProcConnect2(LPVOID lpParam);
	HANDLE hThread[2];
	HANDLE mutex;
	//

	public ref class Scanner : public System::Windows::Forms::Form
	{
	public:
		Scanner(void)
		{
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
			//

			//初始化Worker
			InitializeBackgoundWorker();

			//Control::CheckForIllegalCrossThreadCalls = false;

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

			 
			 //声明BackgoundWorker
			 System::ComponentModel::BackgroundWorker^ backgroundWorker;






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
			this->Result1 = (gcnew System::Windows::Forms::RichTextBox());
			this->StopButton = (gcnew System::Windows::Forms::Button());
			this->StartButton = (gcnew System::Windows::Forms::Button());
			this->IPAddress = (gcnew System::Windows::Forms::GroupBox());
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
			this->tabControl1->Location = System::Drawing::Point(12, 15);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(581, 392);
			this->tabControl1->TabIndex = 0;
			// 
			// Scan
			// 
			this->Scan->Controls->Add(this->ScanResult);
			this->Scan->Controls->Add(this->IPAddress);
			this->Scan->Location = System::Drawing::Point(4, 22);
			this->Scan->Name = L"Scan";
			this->Scan->Padding = System::Windows::Forms::Padding(3);
			this->Scan->Size = System::Drawing::Size(573, 366);
			this->Scan->TabIndex = 0;
			this->Scan->Text = L"扫描";
			this->Scan->UseVisualStyleBackColor = true;
			// 
			// ScanResult
			// 
			this->ScanResult->Controls->Add(this->Result1);
			this->ScanResult->Controls->Add(this->StopButton);
			this->ScanResult->Controls->Add(this->StartButton);
			this->ScanResult->Location = System::Drawing::Point(58, 176);
			this->ScanResult->Name = L"ScanResult";
			this->ScanResult->Size = System::Drawing::Size(489, 184);
			this->ScanResult->TabIndex = 1;
			this->ScanResult->TabStop = false;
			this->ScanResult->Text = L"扫描结果";
			// 
			// Result1
			// 
			this->Result1->Location = System::Drawing::Point(7, 21);
			this->Result1->Name = L"Result1";
			this->Result1->Size = System::Drawing::Size(437, 128);
			this->Result1->TabIndex = 2;
			this->Result1->Text = L"";
			// 
			// StopButton
			// 
			this->StopButton->Location = System::Drawing::Point(99, 155);
			this->StopButton->Name = L"StopButton";
			this->StopButton->Size = System::Drawing::Size(75, 23);
			this->StopButton->TabIndex = 1;
			this->StopButton->Text = L"暂停";
			this->StopButton->UseVisualStyleBackColor = true;
			this->StopButton->Click += gcnew System::EventHandler(this, &Scanner::StopButton_Click);
			// 
			// StartButton
			// 
			this->StartButton->Location = System::Drawing::Point(7, 155);
			this->StartButton->Name = L"StartButton";
			this->StartButton->Size = System::Drawing::Size(75, 23);
			this->StartButton->TabIndex = 0;
			this->StartButton->Text = L"开始";
			this->StartButton->UseVisualStyleBackColor = true;
			this->StartButton->Click += gcnew System::EventHandler(this, &Scanner::StartButton_Click);
			// 
			// IPAddress
			// 
			this->IPAddress->Controls->Add(this->IPAddressListBox);
			this->IPAddress->Controls->Add(this->RemoveIPAddress);
			this->IPAddress->Controls->Add(this->AddIPAddress);
			this->IPAddress->Controls->Add(this->EndIPAddressTextBox);
			this->IPAddress->Controls->Add(this->StartIPAddressTextBox);
			this->IPAddress->Controls->Add(this->IPAddressTextBox);
			this->IPAddress->Controls->Add(this->EndIPAddresslabel);
			this->IPAddress->Controls->Add(this->StartIPAddresslabel);
			this->IPAddress->Controls->Add(this->IPAddressLabel);
			this->IPAddress->Location = System::Drawing::Point(58, 6);
			this->IPAddress->Name = L"IPAddress";
			this->IPAddress->Size = System::Drawing::Size(489, 153);
			this->IPAddress->TabIndex = 0;
			this->IPAddress->TabStop = false;
			this->IPAddress->Text = L"IP地址";
			// 
			// IPAddressListBox
			// 
			this->IPAddressListBox->FormattingEnabled = true;
			this->IPAddressListBox->ItemHeight = 12;
			this->IPAddressListBox->Location = System::Drawing::Point(294, 20);
			this->IPAddressListBox->Name = L"IPAddressListBox";
			this->IPAddressListBox->Size = System::Drawing::Size(126, 124);
			this->IPAddressListBox->TabIndex = 8;
			// 
			// RemoveIPAddress
			// 
			this->RemoveIPAddress->Location = System::Drawing::Point(230, 69);
			this->RemoveIPAddress->Name = L"RemoveIPAddress";
			this->RemoveIPAddress->Size = System::Drawing::Size(40, 30);
			this->RemoveIPAddress->TabIndex = 7;
			this->RemoveIPAddress->Text = L"<<";
			this->RemoveIPAddress->UseVisualStyleBackColor = true;
			this->RemoveIPAddress->Click += gcnew System::EventHandler(this, &Scanner::RemoveIPAddress_Click);
			// 
			// AddIPAddress
			// 
			this->AddIPAddress->Location = System::Drawing::Point(230, 26);
			this->AddIPAddress->Name = L"AddIPAddress";
			this->AddIPAddress->Size = System::Drawing::Size(40, 30);
			this->AddIPAddress->TabIndex = 6;
			this->AddIPAddress->Text = L">>";
			this->AddIPAddress->UseVisualStyleBackColor = true;
			this->AddIPAddress->Click += gcnew System::EventHandler(this, &Scanner::AddIPAddress_Click);
			// 
			// EndIPAddressTextBox
			// 
			this->EndIPAddressTextBox->Location = System::Drawing::Point(99, 99);
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
			this->EndIPAddresslabel->Location = System::Drawing::Point(20, 102);
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
			this->ScanSetting->Size = System::Drawing::Size(573, 366);
			this->ScanSetting->TabIndex = 1;
			this->ScanSetting->Text = L"扫描参数设置";
			this->ScanSetting->UseVisualStyleBackColor = true;
			// 
			// UDPEndPortTextBox
			// 
			this->UDPEndPortTextBox->Location = System::Drawing::Point(82, 286);
			this->UDPEndPortTextBox->Name = L"UDPEndPortTextBox";
			this->UDPEndPortTextBox->Size = System::Drawing::Size(59, 21);
			this->UDPEndPortTextBox->TabIndex = 20;
			// 
			// UDPStartPortTextBox
			// 
			this->UDPStartPortTextBox->Location = System::Drawing::Point(81, 253);
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
			this->TCPPortListBox->Location = System::Drawing::Point(266, 120);
			this->TCPPortListBox->Name = L"TCPPortListBox";
			this->TCPPortListBox->Size = System::Drawing::Size(120, 88);
			this->TCPPortListBox->TabIndex = 9;
			// 
			// TCPEndPortTextBox
			// 
			this->TCPEndPortTextBox->Location = System::Drawing::Point(79, 160);
			this->TCPEndPortTextBox->Name = L"TCPEndPortTextBox";
			this->TCPEndPortTextBox->Size = System::Drawing::Size(62, 21);
			this->TCPEndPortTextBox->TabIndex = 7;
			// 
			// TCPStartPortTextBox
			// 
			this->TCPStartPortTextBox->Location = System::Drawing::Point(81, 128);
			this->TCPStartPortTextBox->Name = L"TCPStartPortTextBox";
			this->TCPStartPortTextBox->Size = System::Drawing::Size(60, 21);
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
			// Scanner
			// 
			this->ClientSize = System::Drawing::Size(595, 411);
			this->Controls->Add(this->tabControl1);
			this->Name = L"Scanner";
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
		OpenPortMap.clear();

		this->Result1->Text = String::Empty;
		this->Result1->Text = "扫描中,请稍候...\n";
		this->StartButton->Enabled = false;
		this->StopButton->Enabled = true;
		backgroundWorker->RunWorkerAsync(1);

	}

		 //停止按钮处理函数
private: System::Void StopButton_Click(System::Object^  sender, System::EventArgs^  e) {
	this->backgroundWorker->CancelAsync();
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
		//TCPPortVec[sport] = sport;
		this->TCPPortListBox->Items->Add(tmp1);
	}

	//处理范围端口的
	if (sport < eport) {
		int tmp_port = sport;
		while (tmp_port <= eport) {
			//TCPPortVec[tmp_port] = tmp_port;
			TCPPortMap[tmp_port] = tmp_port;
			++tmp_port;
		}
		this->TCPPortListBox->Items->Add(Convert::ToString(sport + "-" + eport));
	}
	
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
		//TCPPortVec[port] = 0;
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
			//TCPPortVec[sport] = 0;
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
		//TCPPortVec[sport] = sport;
		this->UDPPortListBox->Items->Add(tmp1);
	}

	//处理范围端口的
	if (sport < eport) {
		int tmp_port = sport;
		while (tmp_port <= eport) {
			//TCPPortVec[tmp_port] = tmp_port;
			UDPPortMap[tmp_port] = tmp_port;
			++tmp_port;
		}
		this->UDPPortListBox->Items->Add(Convert::ToString(sport + "-" + eport));
	}


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
	else
		return;
	if (this->StartIPAddressTextBox->Text->Replace(" ","")->Length >= 7 && this->EndIPAddressTextBox->Text->Replace(" ","")->Length >=7) {
		MarshalString(this->StartIPAddressTextBox->Text->Replace(" ",""), start_ipaddr);
		MarshalString(this->EndIPAddressTextBox->Text->Replace(" ", ""), end_ipaddr);
		this->IPAddressListBox->Items->Add(this->StartIPAddressTextBox->Text->Replace(" ", ""));
		this->IPAddressListBox->Items->Add(this->EndIPAddressTextBox->Text->Replace(" ", ""));
	}
	
}
		 
		 //BackgroundWoker DoWork
		System::Void DoWork(Object^ sender, DoWorkEventArgs^ e) {
			item_tcp = TCPPortMap.begin();
			item_udp = UDPPortMap.begin();

			if (TCPScanCheckBox->Checked){
				for (auto item = TCPPortMap.begin(); item != TCPPortMap.end(); ++item) {
					if (!backgroundWorker->CancellationPending) {
						if (ConnectToHostTCP(item->second, "127.0.0.1"))
							OpenPortMap.insert({ "127.0.0.1", item->second });
						CloseConnection();
						e->Cancel = true;
					}
					else
						return;
				}
			}

			if (UDPScanCheckBox->Checked) {
				for (auto item = UDPPortMap.begin(); item != UDPPortMap.end(); ++item) {
					if (!backgroundWorker->CancellationPending) {
						if (ConnectToHostUDP(item->second, "127.0.0.1"))
							OpenPortMap.insert({ "127.0.0.1", item->second });
						CloseConnection();
						e->Cancel = true;
					}
					else
						return;
				}
			}
			
		}

		//BackgroundWoker Completed
		 System::Void OnRunWorkerCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e) {
			 for (auto item = OpenPortMap.begin(); item != OpenPortMap.end(); ++item) {
				 this->Result1->Text += gcnew String(item->first.c_str()) + " " + item->second + "\n";
			 }
			 this->Result1->Text += "扫描完成\n";
			 this->StartButton->Enabled = true;
			 this->StopButton->Enabled = false;
		 }

		 // 初始化BackgroundWorker函数
private:
	System::Void InitializeBackgoundWorker() {
		backgroundWorker = gcnew System::ComponentModel::BackgroundWorker;
		backgroundWorker->DoWork += gcnew DoWorkEventHandler(this, &Scanner::DoWork);
		backgroundWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Scanner::OnRunWorkerCompleted);
	}

private: System::Void RemoveIPAddress_Click(System::Object^  sender, System::EventArgs^  e) {
}

};
}
