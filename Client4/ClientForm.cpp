#include "ClientForm.h"
#include <clocale>

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main() {
	setlocale(LC_ALL, "rus");

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Client4::ClientForm form;
	Application::Run(%form);
}