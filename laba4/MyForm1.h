#include <list>
#include <string>
#pragma once

namespace laba4WF {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm1
	/// </summary>
	public ref class MyForm1 : public System::Windows::Forms::Form
	{
	public:
		List<String^>^ siblings = gcnew List<String^>();
 	
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::Button^ buttonForList;
	private: System::Windows::Forms::Button^ buttonTableSaving;
	private: System::Windows::Forms::Button^ buttonSaveToFile;
	private: System::Windows::Forms::Button^ buttonLoadFromFile;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;

	private: System::Windows::Forms::ListBox^ listBox1;
		   /*void SetMyListBox(System::Windows::Forms::ListBox^ listBox)
		   {
			   listBox = listBox1;
		   }*/
	public:
		static BindingSource^ sharedBindingSource;

		static MyForm1() {
			DataTable^ dt = gcnew DataTable(); // Создаем один DataTable
			dt->Columns->Add("Destination", String::typeid);
			dt->Columns->Add("Price", String::typeid);
			dt->Columns->Add("Discount", String::typeid);
			sharedBindingSource = gcnew BindingSource();
			sharedBindingSource->DataSource = dt;
		}
	public:
		System::ComponentModel::BindingList<String^>^ dataList;

		MyForm1()
		{
			InitializeComponent();
			dataList = gcnew System::ComponentModel::BindingList<String^>();
			//
			//TODO: добавьте код конструктора
			//
			case1->Visible = true;
			case2->Visible = false;
			textBox1->Visible = true;
			textBox2->Visible = true;
			textBox2->Visible = true;
			label1->Visible = true;
			label2->Visible = true;
			label3->Visible = true;
			dataGridView1->Visible = true;
			listBox1->Visible = false;
			buttonForList->Visible = false;
			buttonTableSaving->Visible = true;
			buttonSaveToFile->Visible = true;
			buttonLoadFromFile->Visible = true;
		}

		MyForm1(bool)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			case1->Visible = false;
			case2->Visible = true;
			textBox1->Visible = false;
			textBox2->Visible = false;
			textBox3->Visible = false;
			label1->Visible = false;
			label2->Visible = false;
			label3->Visible = false;
			buttoncase2->Visible = false;
			dataGridView1->Visible = false;
			listBox1->Visible = true;
			buttonForList->Visible = true;
			buttonTableSaving->Visible = false;
			buttonSaveToFile->Visible = false;
			buttonLoadFromFile->Visible = false;
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ case1;
	protected:
	private: System::Windows::Forms::Label^ case2;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Button^ buttoncase2;


	protected:

	protected:


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
			this->case1 = (gcnew System::Windows::Forms::Label());
			this->case2 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->buttoncase2 = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->buttonForList = (gcnew System::Windows::Forms::Button());
			this->buttonTableSaving = (gcnew System::Windows::Forms::Button());
			this->buttonSaveToFile = (gcnew System::Windows::Forms::Button());
			this->buttonLoadFromFile = (gcnew System::Windows::Forms::Button());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// case1
			// 
			this->case1->AutoSize = true;
			this->case1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->case1->Location = System::Drawing::Point(271, 103);
			this->case1->Name = L"case1";
			this->case1->Size = System::Drawing::Size(286, 32);
			this->case1->TabIndex = 0;
			this->case1->Text = L"Добавление тарифа";
			this->case1->Click += gcnew System::EventHandler(this, &MyForm1::case1_Click);
			// 
			// case2
			// 
			this->case2->AutoSize = true;
			this->case2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->case2->Location = System::Drawing::Point(249, 59);
			this->case2->Name = L"case2";
			this->case2->Size = System::Drawing::Size(676, 32);
			this->case2->TabIndex = 1;
			this->case2->Text = L"Список направлений с минимальной стоимостью:";
			this->case2->Click += gcnew System::EventHandler(this, &MyForm1::case2_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(314, 191);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(212, 22);
			this->textBox1->TabIndex = 2;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(314, 244);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(212, 22);
			this->textBox2->TabIndex = 3;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(314, 294);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(212, 22);
			this->textBox3->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(74, 191);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(220, 16);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Введите название направления";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(195, 244);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(98, 16);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Введите цену";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(183, 294);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(111, 16);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Введите скидку";
			// 
			// buttoncase2
			// 
			this->buttoncase2->Location = System::Drawing::Point(341, 350);
			this->buttoncase2->Name = L"buttoncase2";
			this->buttoncase2->Size = System::Drawing::Size(147, 59);
			this->buttoncase2->TabIndex = 8;
			this->buttoncase2->Text = L"Добавить тариф";
			this->buttoncase2->UseVisualStyleBackColor = true;
			this->buttoncase2->Click += gcnew System::EventHandler(this, &MyForm1::buttoncase2_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(581, 59);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(467, 360);
			this->dataGridView1->TabIndex = 9;
			this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm1::dataGridView1_CellContentClick_1);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 16;
			this->listBox1->Location = System::Drawing::Point(277, 114);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(627, 260);
			this->listBox1->TabIndex = 11;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm1::listBox1_SelectedIndexChanged);
			// 
			// buttonForList
			// 
			this->buttonForList->Location = System::Drawing::Point(494, 391);
			this->buttonForList->Name = L"buttonForList";
			this->buttonForList->Size = System::Drawing::Size(199, 83);
			this->buttonForList->TabIndex = 12;
			this->buttonForList->Text = L"Обновить список";
			this->buttonForList->UseVisualStyleBackColor = true;
			this->buttonForList->Click += gcnew System::EventHandler(this, &MyForm1::buttonForList_Click);
			// 
			// buttonTableSaving
			// 
			this->buttonTableSaving->Location = System::Drawing::Point(622, 425);
			this->buttonTableSaving->Name = L"buttonTableSaving";
			this->buttonTableSaving->Size = System::Drawing::Size(115, 60);
			this->buttonTableSaving->TabIndex = 13;
			this->buttonTableSaving->Text = L"Сохранить таблицу";
			this->buttonTableSaving->UseVisualStyleBackColor = true;
			this->buttonTableSaving->Click += gcnew System::EventHandler(this, &MyForm1::buttonTableSaving_Click);
			// 
			// buttonSaveToFile
			// 
			this->buttonSaveToFile->Location = System::Drawing::Point(762, 425);
			this->buttonSaveToFile->Name = L"buttonSaveToFile";
			this->buttonSaveToFile->Size = System::Drawing::Size(119, 60);
			this->buttonSaveToFile->TabIndex = 14;
			this->buttonSaveToFile->Text = L"Сохранить таблицу в файл";
			this->buttonSaveToFile->UseVisualStyleBackColor = true;
			this->buttonSaveToFile->Click += gcnew System::EventHandler(this, &MyForm1::buttonSaveToFile_Click);
			// 
			// buttonLoadFromFile
			// 
			this->buttonLoadFromFile->Location = System::Drawing::Point(905, 425);
			this->buttonLoadFromFile->Name = L"buttonLoadFromFile";
			this->buttonLoadFromFile->Size = System::Drawing::Size(113, 60);
			this->buttonLoadFromFile->TabIndex = 15;
			this->buttonLoadFromFile->Text = L"Загрузить таблицу из файла";
			this->buttonLoadFromFile->UseVisualStyleBackColor = true;
			this->buttonLoadFromFile->Click += gcnew System::EventHandler(this, &MyForm1::buttonLoadFromFile_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// MyForm1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1119, 509);
			this->Controls->Add(this->buttonLoadFromFile);
			this->Controls->Add(this->buttonSaveToFile);
			this->Controls->Add(this->case2);
			this->Controls->Add(this->buttonTableSaving);
			this->Controls->Add(this->buttonForList);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->buttoncase2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->case1);
			this->Controls->Add(this->listBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"MyForm1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyForm1";
			this->Load += gcnew System::EventHandler(this, &MyForm1::MyForm1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm1_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void case1_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void case2_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void buttoncase2_Click(System::Object^ sender, System::EventArgs^ e);

private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {}
private: System::Void dataGridView1_CellContentClick_1(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {}
private: System::Void saveFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {

}
private: System::Void listBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e){}
private: System::Void buttonForList_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void buttonTableSaving_Click(System::Object^ sender, System::EventArgs^ e);

private: bool laba4WF::MyForm1::checkString(String^ s);
private: System::Void buttonSaveToFile_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void buttonLoadFromFile_Click(System::Object^ sender, System::EventArgs^ e);
};
}
