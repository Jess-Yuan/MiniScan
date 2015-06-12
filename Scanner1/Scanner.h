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

	protected:


	private: System::Windows::Forms::GroupBox^  IPAddress;
	private: System::Windows::Forms::GroupBox^  ScanResult;
	private: System::Windows::Forms::Button^  StopButton;
	private: System::Windows::Forms::Button^  StartButton;
	private: System::Windows::Forms::RichTextBox^  Result1;
	private: System::Windows::Forms::Label^  IPAddressLabel;
	private: System::Windows::Forms::Label^  EndIPAddresslabel;
	private: System::Windows::Forms::MaskedTextBox^  EndIPAddressTextBox;
	private: System::Windows::Forms::MaskedTextBox^  StartIPAddressTextBox;
	private: System::Windows::Forms::Label^  StartIPAddresslabel;

	private: System::Windows::Forms::CheckBox^  UDPScanCheckBox;

	private: System::Windows::Forms::CheckBox^  TCPScanCheckBox;

	private: System::Windows::Forms::CheckBox^  HostCheckBox;
	private: System::Windows::Forms::ListBox^  TCPPortListBox;
	private: System::Windows::Forms::Button^  RemoveTCPPort;
	private: System::Windows::Forms::Button^  AddTCPPort;
	private: System::Windows::Forms::TextBox^  TCPEndPortTextBox;

	private: System::Windows::Forms::TextBox^  TCPStartPortTextBox;



	private: System::Windows::Forms::Label^  TCPEndPortLabel;
	private: System::Windows::Forms::Label^  TCPStartPortLabel;
	private: System::Windows::Forms::ListBox^  UDPPortListBox;
	private: System::Windows::Forms::Button^  RemoveUDPPort;
	private: System::Windows::Forms::Button^  AddUDPPort;
	private: System::Windows::Forms::TextBox^  UDPEndPortTextBox;
	private: System::Windows::Forms::TextBox^  UDPStartPortTextBox;

	private: System::Windows::Forms::Label^  UDPEndPortLabel;
	private: System::Windows::Forms::Label^  UDPStartPortLabel;
	private: System::Windows::Forms::Button^  ClearTCPPortButton;
	private: System::Windows::Forms::Button^  ClearUDPPortButton;

	private: System::Windows::Forms::Button^  RemoveIPAddress;
	private: System::Windows::Forms::ListBox^  IPAddressListBox;
	private: System::Windows::Forms::Button^  AddIPAddress;
	private: System::Windows::Forms::TextBox^  IPAddressTextBox;

			 
			 //声明BackgoundWorker
			 System::ComponentModel::BackgroundWorker^ backgroundWorker;


	protected:


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
			this->SuspendLayout();
			// 
			// Scanner
			// 
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Name = L"Scanner";
			this->Load += gcnew System::EventHandler(this, &Scanner::Scanner_Load_1);
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
	if (this->UDPStartPortTextBox->Text->Length > 5)
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
	if ((UDPPortMap[sport] != sport) && (eport <= sport)) {
		UDPPortMap[sport] = sport;
		this->UDPPortListBox->Items->Add(tmp1);
	}

	//处理范围端口的
	if (sport < eport) {
		int tmp = sport;
		while (tmp <= eport) {
			UDPPortMap[tmp] = tmp;
			tmp++;
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
			
		}
		 System::Void OnRunWorkerCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e) {
			 for (auto item = OpenPortMap.begin(); item != OpenPortMap.end(); ++item) {
				 this->Result1->Text += gcnew String(item->first.c_str()) + " " + item->second + "\n";
			 }
			 this->Result1->Text += "扫描完成\n";
			 this->StartButton->Enabled = true;
			 this->StopButton->Enabled = false;
		 }

private:
	System::Void InitializeBackgoundWorker() {
		backgroundWorker->DoWork += gcnew DoWorkEventHandler(this, &Scanner::DoWork);
		backgroundWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Scanner::OnRunWorkerCompleted);
	}

private: System::Void Scanner_Load_1(System::Object^  sender, System::EventArgs^  e) {
}
};


//扫描线程的处理函数1
DWORD WINAPI ProcConnect1(LPVOID lpParam)
{
	while (true) {
		WaitForSingleObject(mutex, INFINITE);
		if (item_tcp != TCPPortMap.end()) {
			if (ConnectToHostTCP(item_tcp->second, "127.0.0.1")) {
				OpenPortMap.insert({ "127.0.0.1", item_tcp->second });
				CloseConnection();
				++item_tcp;
				ReleaseMutex(mutex);
			}
			else {
				CloseConnection();
				++item_tcp;
				ReleaseMutex(mutex);
			}
		}
		else {
			break;
		}
	}
	return 0;
}
//扫描线程处理函数2
DWORD WINAPI ProcConnect2(LPVOID lpParam)
{
	while (true) {
		WaitForSingleObject(mutex, INFINITE);
		
		if (item_tcp != TCPPortMap.end()) {
			if (ConnectToHostTCP(item_tcp->second, "127.0.0.1")) {
				OpenPortMap.insert({ "127.0.0.1", item_tcp->second });
				CloseConnection();
				++item_tcp;
				ReleaseMutex(mutex);
			}
			else {
				CloseConnection();
				++item_tcp;
				ReleaseMutex(mutex);
			}
		}
		else {
			break;
		}
	}
	return 0;
}
}
