#pragma once
#include "movingBase.hpp"

class Scoreboard:public Text{
	public:
		int score;
		double x,y;
		string startStr,endStr;
		Scoreboard();
		Scoreboard(Font& font,Vector2f pos,string startStr,string endStr);
		void Action();
}; 
