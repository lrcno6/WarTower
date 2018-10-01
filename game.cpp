#include<queue>
#include<set>
#include<thread>
#include<mutex>
#include<cctype>
#include"game.h"
#include"console.h"
using namespace std;
void Game::play(){
	bool run=true;
	mutex lrun,lmq,lmap;
	queue<char> msg_que;
	thread input([&lrun,run,&lmq,&msg_que]{
		while(1){
			{
				lock_guard<mutex> lock(lrun);
				if(!run)
					break;
			}
			char c=toupper(getch());
			if(set<char>({'W','A','S','D','J','K','L','U','I'}).count(c) || c>='0' && c<='9'){
				lock_guard<mutex> lock(lmq);
				msg_que.push(c);
			}
		}
	}),
	timer([&lrun,run,&lmq,&msg_que]{
		while(1){
			{
				lock_guard<mutex> lock(lrun);
				if(!run)
					break;
			}
			{
				lock_guard<mutex> lock(lmq);
				msg_que.push('\n');
			}
			Console::sleep(400);
		}
	});
	while(1){
		char msg;
		{
			lock_guard<mutex> lock(lmq);
			if(msg_que.empty())
				continue;
			msg=msg_que.front();
			msg_que.pop();
		}
		switch(msg){
			case 'W':
				if(x>0){
					x--;
					
				}
			case 'A':

			case 'S':

			case 'D':

			case 'J':

			case 'K':

			case 'L':

			case 'U':

			case 'I':

			case '\n':

			default:
			
		}
		/*for(int i=0;i<10;i++)
			for(int j=9;j>-1;j--){
				if(shot_map[i][j]>0){
					if(j!=9)
						shot_map[i][j+1]=shot_map[i][j];
					shot_map[i][j]=0;
				}
			}
		for(int i=0;i<10;i++)
			for(int j=0;j<10;j++){
				if(shot_map[i][j]<0){
					if(j!=0)
						shot_map[i][j-1]=shot_map[i][j];
					shot_map[i][j]=0;
				}
			}*/
	}
}