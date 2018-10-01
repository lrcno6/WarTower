//1.0.1
#ifndef _GAME_H_
#define _GAME_H_
#include<cstring>
class Game{
	public:
		Game():x(0),y(0){
			memset(tower_map,0,sizeof(tower_map));
			memset(shot_map,0,sizeof(shot_map));
		}
		void play();
	private:
		struct Tower{
			enum type{
				shooter,tank,maze,home
			};
			enum side{
				red,blue
			};
			type m_type;
			side m_side;
			int m_health;
			int m_attack;
			Tower(type t,side s):m_type(t),m_side(s){
				switch(t){
					case shooter:
						m_health=10;
						m_attack=10;
						break;
					case tank:
						m_health=20;
						m_attack=0;
						break;
					case maze:
						m_health=5;
						m_attack=15;
						break;
					case home:
						m_health=100;
						m_attack=0;
				}
			}
		};
		Tower *tower_map[10][10];
		int shot_map[10][10];
		int x,y;
};
#endif