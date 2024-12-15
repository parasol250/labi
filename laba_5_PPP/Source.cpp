#include "MyForm.h"
#include "MyForm1.h"
#include "Class.h"
#include "Function.h"

using namespace System::IO;

using namespace System;
using namespace System::Windows::Forms;


[System::STAThread]

void main(cli::array<System::String^>^ args) {

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	laba4WF::MyForm from;
	Application::Run(% from);
}