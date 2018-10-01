#include"launcher.h"
#include"console.h"
#include"game.h"
void Launcher::main_menu(){
	bool echo=true;
	while(1){
		if(echo){
			Console::clear();
			Console::move(0,0);
			Console::print("War Tower");
			Console::move(9,1);
			Console::print("By EnderPearl");
			Console::move(0,2);
			Console::print("1.New Game");
			Console::move(0,3);
			Console::print("2.Help");
			Console::move(0,4);
			Console::print("0.Quit");
			echo=false;
		}
		char c=getch();
		switch(c){
			case '1':{
				Game game;
				game.play();
				echo=true;
				break;
			}
			case '2':{
				help();
				echo=true;
				break;
			}
			case '0':
				return;
		}
	}
}
void Launcher::help(){

}