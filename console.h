//1.0.3
#ifndef _CONSOLE_H_
#define _CONSOLE_H_
#include<string>
#include<utility>
#include<cstdlib>
#define WIN_OS
#ifdef WIN_OS
#include<cstdio>
#include<windows.h>
#include<conio.h>
#else
#include<cstdint>
#include<curses.h>
#include<system.h>
#endif
class Console{
	public:
		class Color{
			public:
				enum color:char{
					black,red,green,c3,blue,c5,yellow,white
				};
				Color(color front,color back):m_front(front),m_back(back){
					#ifndef WIN_OS
					m_id=rand()%32768|(rand()%32768<<15);
					inited=false;
					#endif
				}
				unsigned Windows()const{
					return m_front|(m_back<<4)|0x8|0x80;
				}
			private:
				color m_front,m_back;
				#ifndef WIN_OS
				int_least32_t m_id;
				bool m_inited;
				#endif
		};
		Console(){
			#ifndef WIN_OS
			initscr();
			#endif
		}
		~Console(){
			#ifndef WIN_OS
			endwin();
			#endif
		}
		static void move(int x,int y){
			#ifdef WIN_OS
			HANDLE hout;
			hout=GetStdHandle(STD_OUTPUT_HANDLE);
			COORD pos={x,y};
			SetConsoleCursorPosition(hout,pos);
			#else
			::move(x,y);
			#endif
		}
		static void cursor_set(bool visible){
			#ifdef WIN_OS
			HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_CURSOR_INFO cci;
			GetConsoleCursorInfo(hout,&cci);
			cci.bVisible=visible;
			SetConsoleCursorInfo(hout,&cci);
			#else
			curs_set(visible);
			#endif
		}
		static void print(const char *str){
			#ifdef WIN_OS
			printf("%s",str);
			#else
			addstr(str);
			#endif
		}
		static void print(const std::string &str){
			print(str.c_str());
		}
		static void print(int n){
			#ifdef WIN_OS
			printf("%d",n);
			#else
			printw("%d",n);
			#endif
		}
		static void mvprint(int x,int y,const char *str){
			#ifdef WIN_OS
			move(x,y);
			printf("%s",str);
			#else
			mvaddstr(str);
			#endif
		}
		static void mvprint(int x,int y,const std::string &str){
			mvprint(x,y,str.c_str());
		}
		static void mvprint(int x,int y,int n){
			#ifdef WIN_OS
			move(x,y);
			printf("%d",n);
			#else
			mvprintw("%d",n);
			#endif
		}
		static bool colorable(){
			#ifdef WIN_OS
			return true;
			#else
			return has_colors();
			#endif
		}
		static void set_color(Color color){
			using namespace std;
			#ifdef WIN_OS
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color.Windows());
			#else
			static bool started=false;
			static int_least32_t used=-1;
			if(!started)
				if(start_color()!=OK)
					throw string("Cannot use the colors");
			if(!color.m_inited)
				init_pair(color,m_id);
			if(used!=-1)
				attroff(COLOR_PAIR(used));
			attron(COLOR_PAIR(used=m_id));
			#endif
		}
		static void clear(){
			system(
				#ifdef WIN_OS
				"cls"
				#else
				"clear"
				#endif
			);
		}
		static void sleep(unsigned ms){
			#ifdef WIN_OS
			Sleep(ms);
			#else
			usleep(ms);
			#endif
		}
};
#endif