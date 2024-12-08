#include "MyForm.h"
#include "MyForm1.h"
#include "Function.h"

using namespace System::IO;

using namespace System;
using namespace System::Windows::Forms;

double num2, num3;
int flag0 = 0, flag1 = 0, flag2 = 0;

System::Void laba4WF::MyForm1::MyForm1_Load(System::Object^ sender, System::EventArgs^ e) {
	dataGridView1->DataSource = MyForm1::sharedBindingSource; // ��������� ������� � DataGridView ��� �������� �����
	listBox1->Items->Add("�����������\t���.����");
}

System::Void laba4WF::MyForm1::buttonForList_Click(System::Object^ sender, System::EventArgs^ e) {

	listBox1->Items->Clear(); // ������� listBox
	listBox1->Items->Add("�����������\t���.����");
	double num2, num3;
	double minPrice = Double::MaxValue;


	for each (DataGridViewRow ^ row in dataGridView1->Rows) {
		if (!row->IsNewRow) { // ���������� ����� ������
			if (!(String::IsNullOrWhiteSpace(Convert::ToString(row->Cells[0]->Value)))
				&& (!(String::IsNullOrWhiteSpace(Convert::ToString(row->Cells[1]->Value))))
				&& (!(String::IsNullOrWhiteSpace(Convert::ToString(row->Cells[2]->Value))))
				&& checkString(Convert::ToString(row->Cells[0]->Value))
				&& Double::TryParse(Convert::ToString(row->Cells[1]->Value), num2)
				&& Double::TryParse(Convert::ToString(row->Cells[2]->Value), num3)
				&& Convert::ToDouble(Convert::ToString(row->Cells[1]->Value)) >= 0
				&& Convert::ToDouble(Convert::ToString(row->Cells[2]->Value)) >= 0 && Convert::ToDouble(Convert::ToString(row->Cells[2]->Value)) <= 100) {

				double finalPrice = getFinalPrice(System::Convert::ToDouble(row->Cells[1]->Value), System::Convert::ToDouble(row->Cells[2]->Value));

				double price = System::Convert::ToDouble(row->Cells[1]->Value);
				if (minPrice >= finalPrice) {
					if (minPrice > finalPrice) {
						siblings->Clear();
						minPrice = finalPrice;
						siblings->Add(System::Convert::ToString(row->Cells[0]->Value));
					}
					else if (minPrice == finalPrice) {
						minPrice = finalPrice;
						siblings->Add(System::Convert::ToString(row->Cells[0]->Value));
					}

				}
				if (!(siblings->Count == 0)) {
					listBox1->Items->Clear();
					listBox1->Items->Add("�����������\t���.����");
					for each (String ^ str in siblings)
					{
						String^ item = "";
						item = item + str + "\t" + System::Convert::ToString(minPrice);
						listBox1->Items->Add(item);
					}
				}
				else {
					MessageBox::Show("������ ����������� ����.");
				}

			}
			else {
				if (flag0 == 0) {
					MessageBox::Show("������! �� ��� ���� � ������� ������� ������� ��������� ���������." +
						"\n\n���������, ��� �� ������ ������ '��������� �������'." +
						"\n\n�� ��������� ����������� ������ �� ����� ����������� ��� ������ ����������� � ����������� ����������.");
					flag0 += 1;
				}
			}
		}
	}
}

bool laba4WF::MyForm1::checkString(String^ s) {
	for (int i = 0; i < s->Length; i++) {
		wchar_t c = s[i];
		if (!Char::IsLetter(c)) {
			return false; // ������� ����������� ������
		}
	}
	return true; // ���� � ������ ������ �����
}

System::Void laba4WF::MyForm1::buttoncase2_Click(System::Object^ sender, System::EventArgs^ e) {
	
	String^ destination = textBox1->Text; // ��������� ������ �� TextBox
	String^ price = textBox2->Text;
	String^ discount = textBox3->Text;

	if (!String::IsNullOrWhiteSpace(destination) &&
		!String::IsNullOrWhiteSpace(price) &&
		!String::IsNullOrWhiteSpace(discount) &&
		checkString(destination)
		&& Double::TryParse(price, num2)
		&& Double::TryParse(discount, num3)
		&& Convert::ToDouble(price) >= 0
		&& Convert::ToDouble(discount) >= 0 && Convert::ToDouble(discount) <= 100) {
		
		DataGridViewRow^ newRow = gcnew DataGridViewRow(); // ������� ����� ������ ��� DataGridView
		newRow->CreateCells(this->dataGridView1);

		array<String^>^ row = gcnew array<String^> { destination, price, discount }; // ��������� ������ � DataGridView
		((DataTable^)MyForm1::sharedBindingSource->DataSource)->Rows->Add(row);
	}
	else {
		MessageBox::Show("������! ��������� ��������� ��������������� ��������:\n - ���� 1: �����;" +
			"\n - ���� 2: ����, ����� > 0;\n - ���� 3: ������ � ��������� �� 0 �� 100\n(������� ����� ������� ����� �������)." + 
			"\n\n������ �� ���������.\n��� �������� ������ ���������� ��������� ��� ����.");		
	}

	textBox1->Clear(); //������� ������ �� TextBox
	textBox2->Clear();
	textBox3->Clear();

}

System::Void laba4WF::MyForm1::buttonTableSaving_Click(System::Object^ sender, System::EventArgs^ e) {
	dataGridView1->DataSource = MyForm1::sharedBindingSource;
}

System::Void laba4WF::MyForm1::buttonSaveToFile_Click(System::Object^ sender, System::EventArgs^ e) {

	SaveFileDialog^ SaveFileDialog1 = gcnew SaveFileDialog;
	SaveFileDialog1->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";

	if (SaveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{

		StreamWriter^ file = File::CreateText(SaveFileDialog1->FileName);
		int � = dataGridView1->RowCount, r = dataGridView1->ColumnCount;

		int i, j;
		for (i = 0; i < � - 1; i++) {

			for (j = 0; j < r; j++)
			{
				if (!String::IsNullOrWhiteSpace(Convert::ToString(dataGridView1->Rows[i]->Cells[j]->Value))
					&& (j == 0 && checkString(Convert::ToString(dataGridView1->Rows[i]->Cells[j]->Value)))
					&& ((j == 1 || j == 2) && Double::TryParse(Convert::ToString(dataGridView1->Rows[i]->Cells[j]->Value), num2))) {}
				else {
					if (flag1 == 0) {
						MessageBox::Show("��������������!!\n��������� ��������� ��������������� ��������:\n - ���� 1: �����;" +
							"\n - ���� 2: ����, ����� > 0; \n - ���� 3: ������ � ��������� �� 0 �� 100\n(������� ����� ������� ����� �������)." +
							"\n\n��� ������������� �������������� ������ � ��������� �� � ���� ������." +
							"\n����� ������� ���� � ������� ������ ��������� �� ���������.");
						flag1 += 1;
					}					
				}
				file->Write(dataGridView1->Rows[i]->Cells[j]->Value);
				file->Write(" ");
			};
			file->WriteLine("");
		}
		file->Close();
	}
}

System::Void laba4WF::MyForm1::buttonLoadFromFile_Click(System::Object^ sender, System::EventArgs^ e) {

	OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog();
	openFileDialog1->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
	openFileDialog1->Title = "�������� ����";

	dataGridView1->DataSource = MyForm1::sharedBindingSource;

	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		String^ filePath = openFileDialog1->FileName;

		System::IO::StreamReader sr(filePath);

		array<wchar_t>^ splitBy = { ' ' };
		array<Double>^ numbers = gcnew array<Double, 1>(3);

		for (;;) { // ����������� ���� (������������ while(true) {}), ����� �� ���� break ��� return
			String^ line = sr.ReadLine();

			if (line == nullptr) break;

			if (line->Length > 0) {
				array<String^>^ parts = line->Split(splitBy, StringSplitOptions::RemoveEmptyEntries);

				if (parts->Length == 3) {
					DataTable^ dataTable = (DataTable^)sharedBindingSource->DataSource;
					String^ str = Convert::ToString(parts[0]);

					if (checkString(str)
						&& Double::TryParse(parts[1], num2)
						&& Double::TryParse(parts[2], num3)
						&& Convert::ToDouble(parts[1]) >= 0
						&& Convert::ToDouble(parts[2]) >= 0 && Convert::ToDouble(parts[2]) <= 100) {
	
							DataRow^ newRow = dataTable->NewRow(); // ��������� ����� ������ � DataTable
							newRow[0] = Convert::ToString(parts[0]);
							newRow[1] = Double::Parse(parts[1]);
							newRow[2] = Double::Parse(parts[2]);

							dataTable->Rows->Add(newRow); // ��������� ������ � DataTable
							sharedBindingSource->ResetBindings(false); // ��������� DataGridView
					}
					else {
						if (flag2 < 1) {
							MessageBox::Show("��������� ������ � ��������� ����� �����������.\n\n���������� ��� ������� ���������� ��������."+
								"\n(1 ��.: �����; 2 ��.: ���� > 0; 3 ��.: ������ � ��������� �� 0 �� 100).\n\n"+
								"������������ ������ �� ����� ���������� � �������.");
							flag2 += 1;
						}
					}
				}
				else {
					if (flag2 < 1) {
						MessageBox::Show("��������� ������ � ��������� ����� �����������.\n\n���������� ��� ������� ���������� ��������."+
							"\n(1 ��.: �����; 2 ��.: ���� > 0; 3 ��.: ������ � ��������� �� 0 �� 100).\n\n"+
							"������������ ������ �� ����� ���������� � �������.");
						flag2 += 1;
					}
				}
			}
			else {
				if (flag2 < 1) {
					MessageBox::Show("��������� ������ � ��������� ����� �����������.\n\n���������� ��� ������� ���������� ��������."+
						"\n(1 ��.: �����; 2 ��.: ���� > 0; 3 ��.: ������ � ��������� �� 0 �� 100).\n\n"+
						"������������ ������ �� ����� ���������� � �������.");
					flag2 += 1;
				}
			}
		}
	}
}