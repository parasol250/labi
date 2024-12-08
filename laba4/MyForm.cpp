#include "MyForm.h"
#include "MyForm1.h"

using namespace System::IO;

using namespace System;
using namespace System::Windows::Forms;


System::Void laba4WF::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e) {
	MyForm1^ frm = gcnew MyForm1();
	frm->Show();
}

System::Void laba4WF::MyForm::button2_Click(System::Object^ sender, System::EventArgs^ e) {
	MyForm1^ frm = gcnew MyForm1(false);
	frm->Show();
}

System::Void laba4WF::MyForm::button3_Click(System::Object^ sender, System::EventArgs^ e) {
	Application::Exit();
}
