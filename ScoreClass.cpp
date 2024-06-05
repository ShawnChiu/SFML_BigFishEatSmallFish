#include "ScoreClass.hpp"

Scoreboard::Scoreboard(){}
Scoreboard::Scoreboard(Font& font,Vector2f pos,string startStr,string endStr){
	score=0;
    this->startStr=startStr;
    this->endStr=endStr;
    setFont(font);
    setCharacterSize(30);
    setPosition(pos);
    x=pos.x,y=pos.y;
    setFillColor(sf::Color::White);
    setString(startStr+to_string(score)+endStr);
}
void Scoreboard::Action(){
	setPosition(x,y);
	setString(startStr+to_string(score)+endStr);
}
