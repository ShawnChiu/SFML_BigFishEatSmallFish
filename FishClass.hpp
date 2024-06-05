#pragma once
#include "ScoreClass.hpp"

class BackGround:public MovingBase{
	protected:
		Texture tex[2];
	public:
		BackGround();
		Sprite& getSprite();
}; 

class Player:public MovingBase{
	protected:
		IntRect uvRect;
		int time;
		BackGround back;
		double eatTime,speed,area,size;
		bool is_die;
	public:
		Scoreboard score;
		Player(Texture& texture,Font& font,double spd);
		void draw(sf::RenderTarget& target, sf::RenderStates states)const;
		void Action();
		void eat(double eatenArea);
		Sprite& getback();
		BackGround& getback2();
		double getArea();
		double getSize();
		void setSpeed(double spd);
		void setSize(double size);
		void upAreaData();
		void die();
		bool dead();
};

class Fish:public MovingBase{
	protected:
		IntRect mark_uvRect;
		Sprite mark;
		double area,speed,size;
	public:
		Fish();
		Fish(Texture& fishTexture,Texture& markTexture,Sprite back,double spd,float setSize);
		void draw(sf::RenderTarget& target, sf::RenderStates states)const;
		void Action(Player& player);
		void randomPosition(Sprite& back);
		double getArea();
		void upAreaData();
};

class BlackShark:public Fish{
	protected:
		IntRect uvRect;
		double eatTime;
		int time;
	public:
		BlackShark();
		BlackShark(Texture& fishTexture,Texture& markTexture,Sprite back,double spd,float setSize);
		bool touch(MovingBase Moving2);
		void Action(Player& player,Fish (&fish)[20],BlackShark (&shark)[3],int self);
		void randomPosition(Sprite& back);
		void eat(double eatenArea);
};  
