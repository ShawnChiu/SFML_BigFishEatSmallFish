#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib> 
#include <cmath>
#include <cfloat> 
using namespace sf;
using namespace std;
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 700
#define PI 3.14159265359
#define fps 60
#define SCREENRECT FloatRect(0,0,WINDOW_WIDTH,WINDOW_HEIGHT)

class MovingBase: public Drawable {
	private:
		double rx,ry;
	protected:
		Sprite sprite;  
		FloatRect rect;
	   	double x,y,dx,dy;   
	   	int left,right,top,bottom; 
	public: 
		MovingBase();
		~MovingBase();
		MovingBase(Texture& texture,bool random_pos,Vector2f random_move,Vector2f scale=Vector2f(1,1));
		MovingBase(Texture& texture, Vector2f pos, Vector2f move,Vector2f scale=Vector2f(1,1));
		void set(Texture& texture,bool random_pos,Vector2f random_move,Vector2f scale=Vector2f(1,1));
		void set(Texture& texture, Vector2f pos, Vector2f move,Vector2f scale=Vector2f(1,1));
		void set(Vector2f pos, Vector2f move,Vector2f scale=Vector2f(1,1));
		void updata(Vector2f backPos=Vector2f(0,0));
		void Action1(Vector2f backPos=Vector2f(0,0));
		void Action2(Vector2f backPos=Vector2f(0,0));
		void Action3(Vector2f backPos=Vector2f(0,0));
		void Action4(Sprite background);
		void draw(sf::RenderTarget& target, sf::RenderStates states)const;
		void setPosition(double px,double py);
		void setPosition(Vector2f pos,Vector2f backPos=Vector2f(0,0));
		void setOrigin(double ox,double oy);
		void setOrigin(Vector2f ori);
		void setCenterOrigin();
		//void randomPosition();
		void setMove(double mx,double my);
		void setMove(Vector2f move);
		void setdx(double sdx);
		void setdy(double sdy);
		void setSpeed(double spd);
		void randomMove(int min_d,int max_d);
		void setRotation(double angle);
		void autoRotation(double deviation=0);
		void setScale(double sx,double sy);
		void setScale(Vector2f scale);
		void setColor(Color color);
		void randomColor(int alpha=255);
		void setTexture(Texture& tex);
		Texture getTexture();
		Vector2f getPosition();
		Vector2f getMove();
		double getdx();
		double getdy();
		double getSpeed();
		double getRotation();
		Vector2f getScale();
		Color getColor();
		FloatRect getGlobalBounds();
		bool touch(MovingBase Moving2);
		double getBord(string Str);
};


double getDistance(Vector2f pos1,Vector2f pos2);
int nearestTarget(MovingBase self,MovingBase target[],int n2,int except=-1);

