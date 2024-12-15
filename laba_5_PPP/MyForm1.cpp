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
	//dataGridView1->DataSource = MyForm1::sharedBindingSource; // добавляем столбцы в DataGridView при загрузке формы
	listBox1->Items->Add("Направление\tМин.цена");


	MySqlConnection^ dbConn = gcnew MySqlConnection("Server=localhost; Database=tableSQLdb; Uid=root; Pwd=0000;");
	MySqlCommand^ dbCmd = gcnew MySqlCommand("SELECT * FROM tariffs", dbConn);
	MySqlDataAdapter^ dataAdapter = gcnew MySqlDataAdapter(dbCmd);
	DataSet^ dataSet = gcnew DataSet();

	dbConn->Open();
	dataAdapter->Fill(dataSet);
	//dbConn->Close();
	dataGridView1->DataSource = dataSet->Tables[0];

	//// Строка подключения к базе данных (необходимо заменить на вашу)
 //   String^ connectionString = "Data Source=your_server;Initial Catalog=your_database;Integrated Security=True";
 //   // Создаем подключение
 //   SqlConnection^ connection = gcnew SqlConnection(connectionString);
 //   
 //   // Открываем соединение
 //   connection->Open();
 //   
 //   // Создаем SQL-запрос
 //   String^ query = "SELECT * FROM your_table";
 //   
 //   // Создаем адаптер данных и заполняем DataSet
 //   SqlDataAdapter^ adapter = gcnew SqlDataAdapter(query, connection);
 //   DataSet^ dataSet = gcnew DataSet();
 //   adapter->Fill(dataSet, "your_table");  // Загружаем данные в DataSet
 //   // Связываем DataGridView с таблицей из DataSet
 //   dataGridView1->DataSource = dataSet->Tables["your_table"];
 //   // Закрываем соединение
 //   connection->Close();

}

System::Void laba4WF::MyForm1::buttonForList_Click(System::Object^ sender, System::EventArgs^ e) {

	listBox1->Items->Clear(); // очищаем listBox
	listBox1->Items->Add("Направление\tМин.цена");
	//double num2, num3;
	double minPrice = Double::MaxValue;

	//System::Collections::Generic::List<String^>^ siblings = gcnew System::Collections::Generic::List<String^>();
	MySqlConnection^ dbConn = nullptr;
	MySqlCommand^ dbCmd = nullptr;
	MySqlDataReader^ reader = nullptr;

	try {
		// Строка подключения к базе данных (замените на вашу)
		dbConn = gcnew MySqlConnection("Server=localhost; Database=tableSQLdb; Uid=root; Pwd=0000;");
		dbConn->Open();

		// SQL-запрос для выборки данных
		String^ query = "SELECT destination, price, discount FROM tariffs";
		dbCmd = gcnew MySqlCommand(query, dbConn);

		// Выполняем SQL-запрос и получаем данные
		reader = dbCmd->ExecuteReader();
		// Используем цикл while для перебора строк из reader
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
						listBox1->Items->Add("Направление\tМин.цена");
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
						MessageBox::Show("Ошибка! Не все поля в строках таблицы тарифов корректно заполнены." +
							"\n\nУбедитесь, что Вы нажали кнопку 'Сохранить таблицу'." +
							"\n\nНе полностью заполненные строки не будут учитываться при поиске направления с минимальной стоимостью.", "Ошибка!");
						flag0 += 1;
					}
				}
			}
		}
		else {
			MessageBox::Show("Список направлений пуст.");
		}
	}
	catch (MySqlException^ ex) {
		// Обработка ошибок SQL
		MessageBox::Show("Ошибка MySQL: " + ex->Message);
	}
	catch (Exception^ ex) {
		// Обработка общих ошибок
		MessageBox::Show("Общая ошибка: " + ex->Message);
	}
	//for each (DataGridViewRow ^ row in dataGridView1->Rows) {
	//	if (!row->IsNewRow) { // пропускаем новую строку
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
	//				listBox1->Items->Add("Направление\tМин.цена");
	//				for each (String ^ str in siblings)
	//				{
	//					String^ item = "";
	//					item = item + str + "\t" + System::Convert::ToString(minPrice);
	//					listBox1->Items->Add(item);
	//				}
	//			}
	//			else {
	//				MessageBox::Show("Список направлений пуст.");
	//			}
	//		}
	//		else {
	//			if (flag0 == 0) {
	//				MessageBox::Show("Ошибка! Не все поля в строках таблицы тарифов корректно заполнены." +
	//					"\n\nУбедитесь, что Вы нажали кнопку 'Сохранить таблицу'." +
	//					"\n\nНе полностью заполненные строки не будут учитываться при поиске направления с минимальной стоимостью.", "Ошибка!");
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
			return false; // попался небуквенный символ
		}
	}
	return true; // если в строке только буквы
}

//System::Void laba4WF::MyForm1::dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
//
//	//// Получаем индекс измененной строки
//	//int rowIndex = e->RowIndex;
//	//// Проверка, что строка не является новой строкой для добавления
//	//if (rowIndex >= dataGridView1->Rows->Count - 1) return;
//	//// Получаем индекс измененного столбца
//	//int columnIndex = e->ColumnIndex;
//
//	//// Получаем имя столбца
//	//String^ columnName = dataGridView1->Columns[columnIndex]->Name;
//
//	//// Получаем значение измененной ячейки
//	//String^ cellValue = dataGridView1->Rows[rowIndex]->Cells[columnIndex]->Value->ToString();
//
//	////Получаем ID строки
//	//String^ idValue = dataGridView1->Rows[rowIndex]->Cells[0]->Value->ToString();//Предполагаем, что id в 0 столбце
//
//	//// Строка подключения к базе данных (замените на вашу)
//	//MySqlConnection^ dbConn = gcnew MySqlConnection("Server=localhost; Database=tableSQLdb; Uid=root; Pwd=0000;");
//	//MySqlCommand^ dbCmd = nullptr;
//
//	//try {
//	//	dbConn->Open();
//
//	//	// SQL-запрос для обновления данных
//	//	String^ query = "UPDATE tariffs SET " + columnName + " = @value WHERE destination = @id";
//	//	dbCmd = gcnew MySqlCommand(query, dbConn);
//
//	//	// Добавление параметров для защиты от SQL-инъекций
//	//	dbCmd->Parameters->AddWithValue("@value", cellValue);
//	//	dbCmd->Parameters->AddWithValue("@id", idValue);
//
//	//	dbCmd->ExecuteNonQuery();
//
//	//	MessageBox::Show("Данные в базе данных обновлены!");
//
//	//}
//	//catch (MySqlException^ ex) {
//	//	// Обработка ошибок SQL
//	//	MessageBox::Show("Ошибка MySQL: " + ex->Message);
//	//}
//	//catch (Exception^ ex) {
//	//	// Обработка общих ошибок
//	//	MessageBox::Show("Общая ошибка: " + ex->Message);
//	//}
//
//}


System::Void laba4WF::MyForm1::buttoncase2_Click(System::Object^ sender, System::EventArgs^ e) {
	
	String^ destination = textBox1->Text; // считываем данные из TextBox
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

			// SQL-запрос для вставки данных
			String^ query = "INSERT INTO tariffs (destination, price, discount) VALUES (@destination, @price, @discount)";
			dbCmd = gcnew MySqlCommand(query, dbConn);

			// Добавление параметров для защиты от SQL-инъекций
			dbCmd->Parameters->AddWithValue("@destination", destination);
			dbCmd->Parameters->AddWithValue("@price", price);
			dbCmd->Parameters->AddWithValue("@discount", discount);

			dbCmd->ExecuteNonQuery();  // Выполняем запрос

			// Выполняем запрос для обновления данных в DataGridView
			String^ selectQuery = "SELECT * FROM tariffs";
			dataAdapter = gcnew MySqlDataAdapter(selectQuery, dbConn);
			dataSet = gcnew DataSet();
			dataAdapter->Fill(dataSet, "tariffs");

			//Обновление DataGridView
			dataGridView1->DataSource = dataSet->Tables["tariffs"];

			//MessageBox::Show("Данные добавлены!");

		}
		catch (MySqlException^ ex) {
			// Обработка ошибок SQL
			MessageBox::Show("Ошибка MySQL: " + ex->Message);
		}
		catch (Exception^ ex) {
			// Обработка общих ошибок
			MessageBox::Show("Общая ошибка: " + ex->Message);
		}

		//DataGridViewRow^ newRow = gcnew DataGridViewRow(); // создаем новую строку для DataGridView
		//newRow->CreateCells(this->dataGridView1);
		//array<String^>^ row = gcnew array<String^> { destination, price, discount }; // добавляем строку в DataGridView
		//((DataTable^)MyForm1::sharedBindingSource->DataSource)->Rows->Add(row);
	}
	else {
		MessageBox::Show("Ошибка! Допустимы следующие соответствующие значения:\n - поле 1: буквы;" +
			"\n - поле 2: цена, число > 0;\n - поле 3: скидка в процентах от 0 до 100\n(дробная часть пишется через запятую)." + 
			"\n\nДанные не добавлены.\nДля внесения данных необходимо заполнить все поля.", "Ошибка!");
	}

	textBox1->Clear(); //удаляем данные из TextBox
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

		// SQL-запрос для вставки данных
		String^ query = "INSERT INTO tariffs (destination, price, discount) VALUES (@destination, @price, @discount)";
		//dbCmd = gcnew MySqlCommand(query, dbConn);

		//// Добавление параметров для защиты от SQL-инъекций
		//dbCmd->Parameters->AddWithValue("@destination", destination);
		//dbCmd->Parameters->AddWithValue("@price", price);
		//dbCmd->Parameters->AddWithValue("@discount", discount);

		//dbCmd->ExecuteNonQuery();  // Выполняем запрос

		// Выполняем запрос для обновления данных в DataGridView
		String^ selectQuery = "SELECT * FROM tariffs";
		dataAdapter = gcnew MySqlDataAdapter(selectQuery, dbConn);
		dataSet = gcnew DataSet();
		dataAdapter->Fill(dataSet, "tariffs");

		//Обновление DataGridView
		dataGridView1->DataSource = dataSet->Tables["tariffs"];

		//MessageBox::Show("Данные добавлены!");

	}
	catch (MySqlException^ ex) {
		// Обработка ошибок SQL
		MessageBox::Show("Ошибка MySQL: " + ex->Message);
	}
	catch (Exception^ ex) {
		// Обработка общих ошибок
		MessageBox::Show("Общая ошибка: " + ex->Message);
	}


	//MySqlConnection^ dbConn = nullptr;
	//MySqlDataAdapter^ dataAdapter = nullptr;
	//MySqlCommandBuilder^ commandBuilder = nullptr;
	//DataSet^ dataSet = nullptr;

	//try {
	//	// Строка подключения к базе данных (замените на вашу)
	//	dbConn = gcnew MySqlConnection("Server=localhost; Database=tableSQLdb; Uid=root; Pwd=0000;");
	//	dbConn->Open();

	//	// Получаем DataTable из DataSource
	//	dataSet = gcnew DataSet();
	//	dataAdapter = gcnew MySqlDataAdapter("SELECT * FROM tariffs", dbConn);
	//	dataAdapter->Fill(dataSet, "tariffs");

	//	commandBuilder = gcnew MySqlCommandBuilder(dataAdapter);

	//	// Обновляем базу данных
	//	dataAdapter->Update(dataSet, "tariffs");

	//	// Обновление DataGridView
	//	dataGridView1->DataSource = dataSet->Tables["tariffs"];

	//	MessageBox::Show("Данные сохранены в базу данных!");
	//}
	//catch (MySqlException^ ex) {
	//	// Обработка ошибок SQL
	//	MessageBox::Show("Ошибка MySQL: " + ex->Message);
	//}
	//catch (Exception^ ex) {
	//	// Обработка общих ошибок
	//	MessageBox::Show("Общая ошибка: " + ex->Message);
	//}


	//MySqlConnection^ dbConn = gcnew MySqlConnection("Server=localhost; Database=tableSQLdb; Uid=root; Pwd=0000;");
	//MySqlCommand^ dbCmd = nullptr;
	//MySqlDataAdapter^ dataAdapter = nullptr;
	//DataSet^ dataSet = nullptr;


	////dataGridView1->DataSource = dataSet->Tables["tariffs"];
	////dataGridView1->DataSource = MyForm1::sharedBindingSource;

	//dbConn->Open();

	//// SQL-запрос для вставки данных
	//String^ query = "INSERT INTO tariffs (destination, price, discount) VALUES (@destination, @price, @discount)";
	//dbCmd = gcnew MySqlCommand(query, dbConn);

	//// Добавление параметров для защиты от SQL-инъекций
	//dbCmd->Parameters->AddWithValue("@destination", destination);
	//dbCmd->Parameters->AddWithValue("@price", price);
	//dbCmd->Parameters->AddWithValue("@discount", discount);

	//dbCmd->ExecuteNonQuery();  // Выполняем запрос

	// Выполняем запрос для обновления данных в DataGridView
	//String^ selectQuery = "SELECT * FROM tariffs";
	//dataAdapter = gcnew MySqlDataAdapter(selectQuery, dbConn);
	//dataSet = gcnew DataSet();
	//dataAdapter->Fill(dataSet, "tariffs");

	////Обновление DataGridView
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
		int с = dataGridView1->RowCount, r = dataGridView1->ColumnCount;

		int i, j;
		for (i = 0; i < с; i++) {

			for (j = 0; j < r; j++)
			{
				if (!String::IsNullOrWhiteSpace(Convert::ToString(dataGridView1->Rows[i]->Cells[j]->Value))
					&& (j == 0 && checkString(Convert::ToString(dataGridView1->Rows[i]->Cells[j]->Value)))
					&& ((j == 1 || j == 2) && Double::TryParse(Convert::ToString(dataGridView1->Rows[i]->Cells[j]->Value), num2))) {}
				else {
					if (flag1 == 0) {
						MessageBox::Show("Предупреждение!\nДопустимы следующие соответствующие значения:\n - поле 1: буквы;" +
							"\n - поле 2: цена, число > 0; \n - поле 3: скидка в процентах от 0 до 100\n(дробная часть пишется через запятую)." +
							"\n\nПри необходимости скорректируйте данные и сохраните их в файл заново." +
							"\nИначе открыть файл с помощью данной программы не получится.", "Предупреждение!");
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
	openFileDialog1->Title = "Выберите файл";

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

							// SQL-запрос для вставки данных
							String^ query = "INSERT INTO tariffs (destination, price, discount) VALUES (@destination, @price, @discount)";
							dbCmd = gcnew MySqlCommand(query, dbConn);

							// Добавление параметров для защиты от SQL-инъекций
							dbCmd->Parameters->AddWithValue("@destination", parts[0]);
							dbCmd->Parameters->AddWithValue("@price", Double::Parse(parts[1]));
							dbCmd->Parameters->AddWithValue("@discount", Double::Parse(parts[2]));


							dbCmd->ExecuteNonQuery();  // Выполняем запрос

							// Выполняем запрос для обновления данных в DataGridView
							String^ selectQuery = "SELECT * FROM tariffs";
							dataAdapter = gcnew MySqlDataAdapter(selectQuery, dbConn);
							dataSet = gcnew DataSet();
							dataAdapter->Fill(dataSet, "tariffs");

							//Обновление DataGridView
							dataGridView1->DataSource = dataSet->Tables["tariffs"];
							dataGridView1->Update();
							dataGridView1->Refresh();
							

						}
						else {
							if (flag2 < 1) {
								MessageBox::Show("Некоторые данные в указанном файле некорректны.\n\nНеобходимо три столбца подходящих значений." +
									"\n(1 ст.: буквы; 2 ст.: цена > 0; 3 ст.: скидка в процентах от 0 до 100).\n\n" +
									"Некорректные данные не будут перенесены в таблицу.", "Ошибка!");
								flag2 += 1;
							}
						}
					}
					else {
						if (flag2 < 1) {
							MessageBox::Show("Некоторые данные в указанном файле некорректны.\n\nНеобходимо три столбца подходящих значений." +
								"\n(1 ст.: буквы; 2 ст.: цена > 0; 3 ст.: скидка в процентах от 0 до 100).\n\n" +
								"Некорректные данные не будут перенесены в таблицу.", "Ошибка!");
							flag2 += 1;
						}
					}
				}
				else {
					if (flag2 < 1) {
						MessageBox::Show("Некоторые данные в указанном файле некорректны.\n\nНеобходимо три столбца подходящих значений." +
							"\n(1 ст.: буквы; 2 ст.: цена > 0; 3 ст.: скидка в процентах от 0 до 100).\n\n" +
							"Некорректные данные не будут перенесены в таблицу.", "Ошибка!");
						flag2 += 1;
					}
				}
			}
			MessageBox::Show("Данные успешно загружены из файла в базу данных.");
		}
		catch (MySqlException^ ex) {

			MessageBox::Show("Ошибка MySQL: " + ex->Message);
		}
		catch (Exception^ ex) {

			MessageBox::Show("Общая ошибка: " + ex->Message);
		}
	}

	//dataGridView1->DataSource = MyForm1::sharedBindingSource;
	//if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
	//	String^ filePath = openFileDialog1->FileName;
	//	System::IO::StreamReader sr(filePath);
	//	array<wchar_t>^ splitBy = { ' ' };
	//	array<Double>^ numbers = gcnew array<Double, 1>(3);
	//	for (;;) { // бесконечный цикл (эквивалентно while(true) {}), выход из него break или return
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
	//						DataRow^ newRow = dataTable->NewRow(); // добавляем новую строку в DataTable
	//						newRow[0] = Convert::ToString(parts[0]);
	//						newRow[1] = Double::Parse(parts[1]);
	//						newRow[2] = Double::Parse(parts[2]);
	//						dataTable->Rows->Add(newRow); // добавляем строку в DataTable
	//						sharedBindingSource->ResetBindings(false); // обновляем DataGridView
	//				}
	//				else {
	//					if (flag2 < 1) {
	//						MessageBox::Show("Некоторые данные в указанном файле некорректны.\n\nНеобходимо три столбца подходящих значений."+
	//							"\n(1 ст.: буквы; 2 ст.: цена > 0; 3 ст.: скидка в процентах от 0 до 100).\n\n"+
	//							"Некорректные данные не будут перенесены в таблицу.", "Ошибка!");
	//						flag2 += 1;
	//					}
	//				}
	//			}
	//			else {
	//				if (flag2 < 1) {
	//					MessageBox::Show("Некоторые данные в указанном файле некорректны.\n\nНеобходимо три столбца подходящих значений."+
	//						"\n(1 ст.: буквы; 2 ст.: цена > 0; 3 ст.: скидка в процентах от 0 до 100).\n\n"+
	//						"Некорректные данные не будут перенесены в таблицу.", "Ошибка!");
	//					flag2 += 1;
	//				}
	//			}
	//		}
	//		else {
	//			if (flag2 < 1) {
	//				MessageBox::Show("Некоторые данные в указанном файле некорректны.\n\nНеобходимо три столбца подходящих значений."+
	//					"\n(1 ст.: буквы; 2 ст.: цена > 0; 3 ст.: скидка в процентах от 0 до 100).\n\n"+
	//					"Некорректные данные не будут перенесены в таблицу.", "Ошибка!");
	//				flag2 += 1;
	//			}
	//		}
	//	}
	//}
}