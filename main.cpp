//1.0.2
#include"console.h"
#include"launcher.h"
int main(){
	Console con;
	Console::cursor_set(false);
	Launcher::main_menu();
	return 0;
}