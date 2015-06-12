#pragma once
#include <Windows.h>

namespace ThreadDemo {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace std;

	/// <summary>
	/// TestThead 摘要
	/// </summary>
	public ref class TestThead : public System::Windows::Forms::Form
	{
	public:
		
		TestThead(void)
		{
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
			//
			Control::CheckForIllegalCrossThreadCalls = false;
		}

	public: delegate void testDelegate();


	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~TestThead()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox1;
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
			
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(89, 28);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &TestThead::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(89, 77);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"button2";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(51, 125);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(172, 21);
			this->textBox1->TabIndex = 2;
			// 
			// TestThead
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"TestThead";
			this->Text = L"TestThead";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		TestThead^ o = gcnew TestThead;
		ThreadStart^ ts = gcnew ThreadStart(o, &TestThead::ThreadProcess);
		Thread^ t = gcnew Thread(ts);
		t->Start();
	}

			 System::Void ThreadProcess(){
				 TestThead^ o = gcnew TestThead;
				 if (textBox1->InvokeRequired) {
					 textBox1->Text = "Hello world!";
					 textBox1->Invoke(gcnew ThreadStart(o, &TestThead::ThreadProcess));
				 }
				 else {
					 textBox1->Text = "Thread Start!";
				 }
			 }
	};
}
