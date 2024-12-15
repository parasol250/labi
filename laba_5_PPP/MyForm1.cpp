#include "MyForm.h"
#include "MyForm1.h"
#include "Function.h"

using namespace System::IO;

//using namespace System::Data;
//using namespace System::Data::SqlClient;

using namespace System::Data;
using namespace MySql::Data::MySqlClient;

using namespace System;
using namespace System::Windows::Forms;

double num2, num3;
int flag0 = 0, flag1 = 0, flag2 = 0;

System::Void laba4WF::MyForm1::MyForm1_Load(System::Object^ sender, System::EventArgs^ e) {
	//dataGridView1->DataSource = MyForm1::sharedBindingSource; // ��������� ������� � DataGridView ��� �������� �����
	listBox1->Items->Add("�����������\t���.����");


	MySqlConnection^ dbConn = gcnew MySqlConnection("Server=localhost; Database=tableSQLdb; Uid=root; Pwd=0000;");
	MySqlCommand^ dbCmd = gcnew MySqlCommand("SELECT * FROM tariffs", dbConn);
	MySqlDataAdapter^ dataAdapter = gcnew MySqlDataAdapter(dbCmd);
	DataSet^ dataSet = gcnew DataSet();

	dbConn->Open();
	dataAdapter->Fill(dataSet);
	//dbConn->Close();
	dataGridView1->DataSource = dataSet->Tables[0];

	//// ������ ����������� � ���� ������ (���������� �������� �� ����)
 //   String^ connectionString = "Data Source=your_server;Initial Catalog=your_database;Integrated Security=True";
 //   // ������� �����������
 //   SqlConnection^ connection = gcnew SqlConnection(connectionString);
 //   
 //   // ��������� ����������
 //   connection->Open();
 //   
 //   // ������� SQL-������
 //   String^ query = "SELECT * FROM your_table";
 //   
 //   // ������� ������� ������ � ��������� DataSet
 //   SqlDataAdapter^ adapter = gcnew SqlDataAdapter(query, connection);
 //   DataSet^ dataSet = gcnew DataSet();
 //   adapter->Fill(dataSet, "your_table");  // ��������� ������ � DataSet
 //   // ��������� DataGridView � �������� �� DataSet
 //   dataGridView1->DataSource = dataSet->Tables["your_table"];
 //   // ��������� ����������
 //   connection->Close();

}

System::Void laba4WF::MyForm1::buttonForList_Click(System::Object^ sender, System::EventArgs^ e) {

	listBox1->Items->Clear(); // ������� listBox
	listBox1->Items->Add("�����������\t���.����");
	//double num2, num3;
	double minPrice = Double::MaxValue;

	//System::Collections::Generic::List<String^>^ siblings = gcnew System::Collections::Generic::List<String^>();
	MySqlConnection^ dbConn = nullptr;
	MySqlCommand^ dbCmd = nullptr;
	MySqlDataReader^ reader = nullptr;

	try {
		// ������ ����������� � ���� ������ (�������� �� ����)
		dbConn = gcnew MySqlConnection("Server=localhost; Database=tableSQLdb; Uid=root; Pwd=0000;");
		dbConn->Open();

		// SQL-������ ��� ������� ������
		String^ query = "SELECT destination, price, discount FROM tariffs";
		dbCmd = gcnew MySqlCommand(query, dbConn);

		// ��������� SQL-������ � �������� ������
		reader = dbCmd->ExecuteReader();
		// ���������� ���� while ��� �������� ����� �� reader
		if (reader->HasRows)
		{
			while (reader->Read()) {

				String^ destination = reader->GetString(0);
				double price = reader->GetDouble(1);
				double discount = reader->GetDouble(2);
				double finalPrice;
				if (checkString(destination) && price >= 0 && discount >= 0 && discount <= 100)
				{
					finalPrice = getFinalPrice(price, discount);
					if (minPrice >= finalPrice)
					{
						if (minPrice > finalPrice)
						{
							siblings->Clear();
							minPrice = finalPrice;
							siblings->Add(destination);
						}
						else if (minPrice == finalPrice)
						{
							minPrice = finalPrice;
							siblings->Add(destination);
						}
					}
					if (!(siblings->Count == 0))
					{
						listBox1->Items->Clear();
						listBox1->Items->Add("�����������\t���.����");
						for each (String ^ str in siblings)
						{
							String^ item = "";
							item = item + str + "\t" + System::Convert::ToString(minPrice);
							listBox1->Items->Add(item);
						}
					}
				}
				else {
					if (flag0 == 0) {
						MessageBox::Show("������! �� ��� ���� � ������� ������� ������� ��������� ���������." +
							"\n\n���������, ��� �� ������ ������ '��������� �������'." +
							"\n\n�� ��������� ����������� ������ �� ����� ����������� ��� ������ ����������� � ����������� ����������.", "������!");
						flag0 += 1;
					}
				}
			}
		}
		else {
			MessageBox::Show("������ ����������� ����.");
		}
	}
	catch (MySqlException^ ex) {
		// ��������� ������ SQL
		MessageBox::Show("������ MySQL: " + ex->Message);
	}
	catch (Exception^ ex) {
		// ��������� ����� ������
		MessageBox::Show("����� ������: " + ex->Message);
	}
	//for each (DataGridViewRow ^ row in dataGridView1->Rows) {
	//	if (!row->IsNewRow) { // ���������� ����� ������
	//		if (!(String::IsNullOrWhiteSpace(Convert::ToString(row->Cells[0]->Value)))
	//			&& (!(String::IsNullOrWhiteSpace(Convert::ToString(row->Cells[1]->Value))))
	//			&& (!(String::IsNullOrWhiteSpace(Convert::ToString(row->Cells[2]->Value))))
	//			&& checkString(Convert::ToString(row->Cells[0]->Value))
	//			&& Double::TryParse(Convert::ToString(row->Cells[1]->Value), num2)
	//			&& Double::TryParse(Convert::ToString(row->Cells[2]->Value), num3)
	//			&& Convert::ToDouble(Convert::ToString(row->Cells[1]->Value)) >= 0
	//			&& Convert::ToDouble(Convert::ToString(row->Cells[2]->Value)) >= 0 && Convert::ToDouble(Convert::ToString(row->Cells[2]->Value)) <= 100) {
	//			double finalPrice = getFinalPrice(System::Convert::ToDouble(row->Cells[1]->Value), System::Convert::ToDouble(row->Cells[2]->Value));
	//			double price = System::Convert::ToDouble(row->Cells[1]->Value);
	//			if (minPrice >= finalPrice) {
	//				if (minPrice > finalPrice) {
	//					siblings->Clear();
	//					minPrice = finalPrice;
	//					siblings->Add(System::Convert::ToString(row->Cells[0]->Value));
	//				}
	//				else if (minPrice == finalPrice) {
	//					minPrice = finalPrice;
	//					siblings->Add(System::Convert::ToString(row->Cells[0]->Value));
	//				}
	//			}
	//			if (!(siblings->Count == 0)) {
	//				listBox1->Items->Clear();
	//				listBox1->Items->Add("�����������\t���.����");
	//				for each (String ^ str in siblings)
	//				{
	//					String^ item = "";
	//					item = item + str + "\t" + System::Convert::ToString(minPrice);
	//					listBox1->Items->Add(item);
	//				}
	//			}
	//			else {
	//				MessageBox::Show("������ ����������� ����.");
	//			}
	//		}
	//		else {
	//			if (flag0 == 0) {
	//				MessageBox::Show("������! �� ��� ���� � ������� ������� ������� ��������� ���������." +
	//					"\n\n���������, ��� �� ������ ������ '��������� �������'." +
	//					"\n\n�� ��������� ����������� ������ �� ����� ����������� ��� ������ ����������� � ����������� ����������.", "������!");
	//				flag0 += 1;
	//			}
	//		}
	//	}
	//}
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

//System::Void laba4WF::MyForm1::dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
//
//	//// �������� ������ ���������� ������
//	//int rowIndex = e->RowIndex;
//	//// ��������, ��� ������ �� �������� ����� ������� ��� ����������
//	//if (rowIndex >= dataGridView1->Rows->Count - 1) return;
//	//// �������� ������ ����������� �������
//	//int columnIndex = e->ColumnIndex;
//
//	//// �������� ��� �������
//	//String^ columnName = dataGridView1->Columns[columnIndex]->Name;
//
//	//// �������� �������� ���������� ������
//	//String^ cellValue = dataGridView1->Rows[rowIndex]->Cells[columnIndex]->Value->ToString();
//
//	////�������� ID ������
//	//String^ idValue = dataGridView1->Rows[rowIndex]->Cells[0]->Value->ToString();//������������, ��� id � 0 �������
//
//	//// ������ ����������� � ���� ������ (�������� �� ����)
//	//MySqlConnection^ dbConn = gcnew MySqlConnection("Server=localhost; Database=tableSQLdb; Uid=root; Pwd=0000;");
//	//MySqlCommand^ dbCmd = nullptr;
//
//	//try {
//	//	dbConn->Open();
//
//	//	// SQL-������ ��� ���������� ������
//	//	String^ query = "UPDATE tariffs SET " + columnName + " = @value WHERE destination = @id";
//	//	dbCmd = gcnew MySqlCommand(query, dbConn);
//
//	//	// ���������� ���������� ��� ������ �� SQL-��������
//	//	dbCmd->Parameters->AddWithValue("@value", cellValue);
//	//	dbCmd->Parameters->AddWithValue("@id", idValue);
//
//	//	dbCmd->ExecuteNonQuery();
//
//	//	MessageBox::Show("������ � ���� ������ ���������!");
//
//	//}
//	//catch (MySqlException^ ex) {
//	//	// ��������� ������ SQL
//	//	MessageBox::Show("������ MySQL: " + ex->Message);
//	//}
//	//catch (Exception^ ex) {
//	//	// ��������� ����� ������
//	//	MessageBox::Show("����� ������: " + ex->Message);
//	//}
//
//}


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
		
		MySqlConnection^ dbConn = gcnew MySqlConnection("Server=localhost; Database=tableSQLdb; Uid=root; Pwd=0000;");
		MySqlCommand^ dbCmd = nullptr;
		MySqlDataAdapter^ dataAdapter = nullptr;
		DataSet^ dataSet = nullptr;

		try {

			dbConn->Open();

			// SQL-������ ��� ������� ������
			String^ query = "INSERT INTO tariffs (destination, price, discount) VALUES (@destination, @price, @discount)";
			dbCmd = gcnew MySqlCommand(query, dbConn);

			// ���������� ���������� ��� ������ �� SQL-��������
			dbCmd->Parameters->AddWithValue("@destination", destination);
			dbCmd->Parameters->AddWithValue("@price", price);
			dbCmd->Parameters->AddWithValue("@discount", discount);

			dbCmd->ExecuteNonQuery();  // ��������� ������

			// ��������� ������ ��� ���������� ������ � DataGridView
			String^ selectQuery = "SELECT * FROM tariffs";
			dataAdapter = gcnew MySqlDataAdapter(selectQuery, dbConn);
			dataSet = gcnew DataSet();
			dataAdapter->Fill(dataSet, "tariffs");

			//���������� DataGridView
			dataGridView1->DataSource = dataSet->Tables["tariffs"];

			//MessageBox::Show("������ ���������!");

		}
		catch (MySqlException^ ex) {
			// ��������� ������ SQL
			MessageBox::Show("������ MySQL: " + ex->Message);
		}
		catch (Exception^ ex) {
			// ��������� ����� ������
			MessageBox::Show("����� ������: " + ex->Message);
		}

		//DataGridViewRow^ newRow = gcnew DataGridViewRow(); // ������� ����� ������ ��� DataGridView
		//newRow->CreateCells(this->dataGridView1);
		//array<String^>^ row = gcnew array<String^> { destination, price, discount }; // ��������� ������ � DataGridView
		//((DataTable^)MyForm1::sharedBindingSource->DataSource)->Rows->Add(row);
	}
	else {
		MessageBox::Show("������! ��������� ��������� ��������������� ��������:\n - ���� 1: �����;" +
			"\n - ���� 2: ����, ����� > 0;\n - ���� 3: ������ � ��������� �� 0 �� 100\n(������� ����� ������� ����� �������)." + 
			"\n\n������ �� ���������.\n��� �������� ������ ���������� ��������� ��� ����.", "������!");
	}

	textBox1->Clear(); //������� ������ �� TextBox
	textBox2->Clear();
	textBox3->Clear();

}

System::Void laba4WF::MyForm1::buttonTableSaving_Click(System::Object^ sender, System::EventArgs^ e) {

	MySqlConnection^ dbConn = gcnew MySqlConnection("Server=localhost; Database=tableSQLdb; Uid=root; Pwd=0000;");
	//MySqlCommand^ dbCmd = nullptr;
	MySqlDataAdapter^ dataAdapter = nullptr;
	DataSet^ dataSet = nullptr;

	try {

		dbConn->Open();

		// SQL-������ ��� ������� ������
		String^ query = "INSERT INTO tariffs (destination, price, discount) VALUES (@destination, @price, @discount)";
		//dbCmd = gcnew MySqlCommand(query, dbConn);

		//// ���������� ���������� ��� ������ �� SQL-��������
		//dbCmd->Parameters->AddWithValue("@destination", destination);
		//dbCmd->Parameters->AddWithValue("@price", price);
		//dbCmd->Parameters->AddWithValue("@discount", discount);

		//dbCmd->ExecuteNonQuery();  // ��������� ������

		// ��������� ������ ��� ���������� ������ � DataGridView
		String^ selectQuery = "SELECT * FROM tariffs";
		dataAdapter = gcnew MySqlDataAdapter(selectQuery, dbConn);
		dataSet = gcnew DataSet();
		dataAdapter->Fill(dataSet, "tariffs");

		//���������� DataGridView
		dataGridView1->DataSource = dataSet->Tables["tariffs"];

		//MessageBox::Show("������ ���������!");

	}
	catch (MySqlException^ ex) {
		// ��������� ������ SQL
		MessageBox::Show("������ MySQL: " + ex->Message);
	}
	catch (Exception^ ex) {
		// ��������� ����� ������
		MessageBox::Show("����� ������: " + ex->Message);
	}


	//MySqlConnection^ dbConn = nullptr;
	//MySqlDataAdapter^ dataAdapter = nullptr;
	//MySqlCommandBuilder^ commandBuilder = nullptr;
	//DataSet^ dataSet = nullptr;

	//try {
	//	// ������ ����������� � ���� ������ (�������� �� ����)
	//	dbConn = gcnew MySqlConnection("Server=localhost; Database=tableSQLdb; Uid=root; Pwd=0000;");
	//	dbConn->Open();

	//	// �������� DataTable �� DataSource
	//	dataSet = gcnew DataSet();
	//	dataAdapter = gcnew MySqlDataAdapter("SELECT * FROM tariffs", dbConn);
	//	dataAdapter->Fill(dataSet, "tariffs");

	//	commandBuilder = gcnew MySqlCommandBuilder(dataAdapter);

	//	// ��������� ���� ������
	//	dataAdapter->Update(dataSet, "tariffs");

	//	// ���������� DataGridView
	//	dataGridView1->DataSource = dataSet->Tables["tariffs"];

	//	MessageBox::Show("������ ��������� � ���� ������!");
	//}
	//catch (MySqlException^ ex) {
	//	// ��������� ������ SQL
	//	MessageBox::Show("������ MySQL: " + ex->Message);
	//}
	//catch (Exception^ ex) {
	//	// ��������� ����� ������
	//	MessageBox::Show("����� ������: " + ex->Message);
	//}


	//MySqlConnection^ dbConn = gcnew MySqlConnection("Server=localhost; Database=tableSQLdb; Uid=root; Pwd=0000;");
	//MySqlCommand^ dbCmd = nullptr;
	//MySqlDataAdapter^ dataAdapter = nullptr;
	//DataSet^ dataSet = nullptr;


	////dataGridView1->DataSource = dataSet->Tables["tariffs"];
	////dataGridView1->DataSource = MyForm1::sharedBindingSource;

	//dbConn->Open();

	//// SQL-������ ��� ������� ������
	//String^ query = "INSERT INTO tariffs (destination, price, discount) VALUES (@destination, @price, @discount)";
	//dbCmd = gcnew MySqlCommand(query, dbConn);

	//// ���������� ���������� ��� ������ �� SQL-��������
	//dbCmd->Parameters->AddWithValue("@destination", destination);
	//dbCmd->Parameters->AddWithValue("@price", price);
	//dbCmd->Parameters->AddWithValue("@discount", discount);

	//dbCmd->ExecuteNonQuery();  // ��������� ������

	// ��������� ������ ��� ���������� ������ � DataGridView
	//String^ selectQuery = "SELECT * FROM tariffs";
	//dataAdapter = gcnew MySqlDataAdapter(selectQuery, dbConn);
	//dataSet = gcnew DataSet();
	//dataAdapter->Fill(dataSet, "tariffs");

	////���������� DataGridView
	//dataGridView1->DataSource = dataSet->Tables["tariffs"];

}

System::Void laba4WF::MyForm1::buttonSaveToFile_Click(System::Object^ sender, System::EventArgs^ e) {

	SaveFileDialog^ SaveFileDialog1 = gcnew SaveFileDialog;
	SaveFileDialog1->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";

	if (SaveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		dataGridView1->Update();
		dataGridView1->Refresh();
		StreamWriter^ file = File::CreateText(SaveFileDialog1->FileName);
		int � = dataGridView1->RowCount, r = dataGridView1->ColumnCount;

		int i, j;
		for (i = 0; i < �; i++) {

			for (j = 0; j < r; j++)
			{
				if (!String::IsNullOrWhiteSpace(Convert::ToString(dataGridView1->Rows[i]->Cells[j]->Value))
					&& (j == 0 && checkString(Convert::ToString(dataGridView1->Rows[i]->Cells[j]->Value)))
					&& ((j == 1 || j == 2) && Double::TryParse(Convert::ToString(dataGridView1->Rows[i]->Cells[j]->Value), num2))) {}
				else {
					if (flag1 == 0) {
						MessageBox::Show("��������������!\n��������� ��������� ��������������� ��������:\n - ���� 1: �����;" +
							"\n - ���� 2: ����, ����� > 0; \n - ���� 3: ������ � ��������� �� 0 �� 100\n(������� ����� ������� ����� �������)." +
							"\n\n��� ������������� �������������� ������ � ��������� �� � ���� ������." +
							"\n����� ������� ���� � ������� ������ ��������� �� ���������.", "��������������!");
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

	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		String^ filePath = openFileDialog1->FileName;
		MySqlConnection^ dbConn = nullptr;
		MySqlCommand^ dbCmd = nullptr;
		MySqlDataAdapter^ dataAdapter = nullptr;
		DataSet^ dataSet = nullptr;

		try {
			dbConn = gcnew MySqlConnection("Server=localhost; Database=tableSQLdb; Uid=root; Pwd=0000;");
			dbConn->Open();
			System::IO::StreamReader sr(filePath);
			array<wchar_t>^ splitBy = { ' ' };
			//double num2, num3;

			while (!sr.EndOfStream) {
				String^ line = sr.ReadLine();
				if (line == nullptr) break;
				if (line->Length > 0) {
					array<String^>^ parts = line->Split(splitBy, StringSplitOptions::RemoveEmptyEntries);

					if (parts->Length == 3) {
						String^ str = Convert::ToString(parts[0]);
						if (checkString(str)
							&& Double::TryParse(parts[1], num2)
							&& Double::TryParse(parts[2], num3)
							&& Convert::ToDouble(parts[1]) >= 0
							&& Convert::ToDouble(parts[2]) >= 0 && Convert::ToDouble(parts[2]) <= 100) {

							// SQL-������ ��� ������� ������
							String^ query = "INSERT INTO tariffs (destination, price, discount) VALUES (@destination, @price, @discount)";
							dbCmd = gcnew MySqlCommand(query, dbConn);

							// ���������� ���������� ��� ������ �� SQL-��������
							dbCmd->Parameters->AddWithValue("@destination", parts[0]);
							dbCmd->Parameters->AddWithValue("@price", Double::Parse(parts[1]));
							dbCmd->Parameters->AddWithValue("@discount", Double::Parse(parts[2]));


							dbCmd->ExecuteNonQuery();  // ��������� ������

							// ��������� ������ ��� ���������� ������ � DataGridView
							String^ selectQuery = "SELECT * FROM tariffs";
							dataAdapter = gcnew MySqlDataAdapter(selectQuery, dbConn);
							dataSet = gcnew DataSet();
							dataAdapter->Fill(dataSet, "tariffs");

							//���������� DataGridView
							dataGridView1->DataSource = dataSet->Tables["tariffs"];
							dataGridView1->Update();
							dataGridView1->Refresh();
							

						}
						else {
							if (flag2 < 1) {
								MessageBox::Show("��������� ������ � ��������� ����� �����������.\n\n���������� ��� ������� ���������� ��������." +
									"\n(1 ��.: �����; 2 ��.: ���� > 0; 3 ��.: ������ � ��������� �� 0 �� 100).\n\n" +
									"������������ ������ �� ����� ���������� � �������.", "������!");
								flag2 += 1;
							}
						}
					}
					else {
						if (flag2 < 1) {
							MessageBox::Show("��������� ������ � ��������� ����� �����������.\n\n���������� ��� ������� ���������� ��������." +
								"\n(1 ��.: �����; 2 ��.: ���� > 0; 3 ��.: ������ � ��������� �� 0 �� 100).\n\n" +
								"������������ ������ �� ����� ���������� � �������.", "������!");
							flag2 += 1;
						}
					}
				}
				else {
					if (flag2 < 1) {
						MessageBox::Show("��������� ������ � ��������� ����� �����������.\n\n���������� ��� ������� ���������� ��������." +
							"\n(1 ��.: �����; 2 ��.: ���� > 0; 3 ��.: ������ � ��������� �� 0 �� 100).\n\n" +
							"������������ ������ �� ����� ���������� � �������.", "������!");
						flag2 += 1;
					}
				}
			}
			MessageBox::Show("������ ������� ��������� �� ����� � ���� ������.");
		}
		catch (MySqlException^ ex) {

			MessageBox::Show("������ MySQL: " + ex->Message);
		}
		catch (Exception^ ex) {

			MessageBox::Show("����� ������: " + ex->Message);
		}
	}

	//dataGridView1->DataSource = MyForm1::sharedBindingSource;
	//if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
	//	String^ filePath = openFileDialog1->FileName;
	//	System::IO::StreamReader sr(filePath);
	//	array<wchar_t>^ splitBy = { ' ' };
	//	array<Double>^ numbers = gcnew array<Double, 1>(3);
	//	for (;;) { // ����������� ���� (������������ while(true) {}), ����� �� ���� break ��� return
	//		String^ line = sr.ReadLine();
	//		if (line == nullptr) break;
	//		if (line->Length > 0) {
	//			array<String^>^ parts = line->Split(splitBy, StringSplitOptions::RemoveEmptyEntries);
	//			if (parts->Length == 3) {
	//				DataTable^ dataTable = (DataTable^)sharedBindingSource->DataSource;
	//				String^ str = Convert::ToString(parts[0]);
	//				if (checkString(str)
	//					&& Double::TryParse(parts[1], num2)
	//					&& Double::TryParse(parts[2], num3)
	//					&& Convert::ToDouble(parts[1]) >= 0
	//					&& Convert::ToDouble(parts[2]) >= 0 && Convert::ToDouble(parts[2]) <= 100) {
	//
	//						DataRow^ newRow = dataTable->NewRow(); // ��������� ����� ������ � DataTable
	//						newRow[0] = Convert::ToString(parts[0]);
	//						newRow[1] = Double::Parse(parts[1]);
	//						newRow[2] = Double::Parse(parts[2]);
	//						dataTable->Rows->Add(newRow); // ��������� ������ � DataTable
	//						sharedBindingSource->ResetBindings(false); // ��������� DataGridView
	//				}
	//				else {
	//					if (flag2 < 1) {
	//						MessageBox::Show("��������� ������ � ��������� ����� �����������.\n\n���������� ��� ������� ���������� ��������."+
	//							"\n(1 ��.: �����; 2 ��.: ���� > 0; 3 ��.: ������ � ��������� �� 0 �� 100).\n\n"+
	//							"������������ ������ �� ����� ���������� � �������.", "������!");
	//						flag2 += 1;
	//					}
	//				}
	//			}
	//			else {
	//				if (flag2 < 1) {
	//					MessageBox::Show("��������� ������ � ��������� ����� �����������.\n\n���������� ��� ������� ���������� ��������."+
	//						"\n(1 ��.: �����; 2 ��.: ���� > 0; 3 ��.: ������ � ��������� �� 0 �� 100).\n\n"+
	//						"������������ ������ �� ����� ���������� � �������.", "������!");
	//					flag2 += 1;
	//				}
	//			}
	//		}
	//		else {
	//			if (flag2 < 1) {
	//				MessageBox::Show("��������� ������ � ��������� ����� �����������.\n\n���������� ��� ������� ���������� ��������."+
	//					"\n(1 ��.: �����; 2 ��.: ���� > 0; 3 ��.: ������ � ��������� �� 0 �� 100).\n\n"+
	//					"������������ ������ �� ����� ���������� � �������.", "������!");
	//				flag2 += 1;
	//			}
	//		}
	//	}
	//}
}