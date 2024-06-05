#include "FishClass.hpp"

//BackGround
BackGround::BackGround(){
	tex[0].loadFromFile("resources/background.png");
	sprite.setTexture(tex[0]);    
    x=0,y=0,dx=0,dy=0;    
    rect=sprite.getGlobalBounds();
	left=rect.left ;
	top=rect.top ;
	right=left+rect.width ;
	bottom=top+rect.height ;
    sprite.setPosition(x,y) ;
}
Sprite& BackGround::getSprite(){
	return sprite;
}

//Player
Player::Player(Texture& texture,Font& font,double spd):
	size(1),time(0),speed(spd),eatTime(0),is_die(false){
	uvRect=IntRect(0,0,22,14);
	sprite.setTexture(texture);
	sprite.setTextureRect(uvRect);
	set(Vector2f(WINDOW_WIDTH/2.0,WINDOW_HEIGHT/2.0),Vector2f(0,0),Vector2f(5*size,5*size));
	area=rect.width*rect.height;
	score=Scoreboard(font,Vector2f(10,10),"SCORE: ","");
}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
	target.draw(score, states);
}
void Player::Action(){
	if(Keyboard::isKeyPressed(Keyboard::Space)&&score.score>0){
		if(eatTime>0){
			eatTime-=1.0/fps;
			uvRect.top=42;
		}
		else uvRect.top=28;
		if(time++%10==0){		
			if(uvRect.left==0)uvRect.left=22;
			else uvRect.left=0;
		}	
	}
	else{
		if(eatTime>0){
			eatTime-=1.0/fps;
			uvRect.top=14;
		}
		else uvRect.top=0;
		if(time++%30==0){		
			if(uvRect.left==0)uvRect.left=22;
			else uvRect.left=0;
		}
	}
	sprite.setTextureRect(uvRect);
	setMove(0,0);
	back.setMove(0,0);
	bool move=false;
	FloatRect back_rect=back.getGlobalBounds();
    if(Keyboard::isKeyPressed(Keyboard::Left)){
		dx-=10;
		if(back_rect.left<-2*speed&&x<WINDOW_WIDTH/2.0)back.setdx(back.getdx()+10);
		else move=true;
	}
    if(Keyboard::isKeyPressed(Keyboard::Right)){
		dx+=10;
		if(back_rect.left+back_rect.width>WINDOW_WIDTH+2*speed&&x>WINDOW_WIDTH/2.0)back.setdx(back.getdx()-10);
		else move=true;
	}
    if(Keyboard::isKeyPressed(Keyboard::Up)){
		dy-=10;
		if(back_rect.top<-2*speed&&y<WINDOW_HEIGHT/2.0)back.setdy(back.getdy()+10);
		else move=true;
	}
    if(Keyboard::isKeyPressed(Keyboard::Down)){
		dy+=10;
		if(back_rect.top+back_rect.height>WINDOW_HEIGHT+2*speed&&y>WINDOW_HEIGHT/2.0)back.setdy(back.getdy()-10);
		else move=true;
	}
    autoRotation();
    setScale((getScale().x>0?1:-1)*5*size,5*size);
    if(!move)setMove(0,0);
    if(dx!=0&&back.getdx()!=0)dx=0;
    if(dy!=0&&back.getdy()!=0)dy=0;
    if(dx!=0||dy!=0){
    	if(Keyboard::isKeyPressed(Keyboard::Space)&&score.score>0){
    		double spd=speed;
			setSpeed(2*speed);
			speed=spd;
		}
    	else setSpeed(speed);	
	}
    if(back.getdx()!=0||back.getdy()!=0){
    	if(Keyboard::isKeyPressed(Keyboard::Space)&&score.score>0){
    		double spd=speed;
			back.setSpeed(2*speed);
			speed=spd;
		}
    	else back.setSpeed(speed);	
	}
	if(Keyboard::isKeyPressed(Keyboard::Space)&&score.score>0)size-=0.0001;
    
	back.updata();
	Action3();
	
	upAreaData();
	score.score=area-7700;
	if(score.score<0)score.score=0;
	score.Action();
}
void Player::eat(double eatenArea){
	size*=1+0.05*eatenArea/(area);
	eatTime=0.5;
}
Sprite& Player::getback(){
	return back.getSprite();
}

BackGround& Player::getback2(){
	return back;
}
double Player::getArea(){
	return area;
}  
double Player::getSize(){
	return size;
}
void Player::setSpeed(double spd){
	speed=spd;
	dx=speed*cos(atan2(dy,dx)),dy=speed*sin(atan2(dy,dx));
}
void Player::setSize(double size){
	this->size=size;
}
void Player::upAreaData(){
	double angle=sprite.getRotation();
	sprite.setRotation(0);
	rect=sprite.getGlobalBounds();
	area=rect.width*rect.height;
	sprite.setRotation(angle);
	rect=sprite.getGlobalBounds();
}
void Player::die(){
	is_die=true;
}
bool Player::dead(){
	return is_die;
}

//Fish
Fish::Fish():size(1){}
Fish::Fish(Texture& fishTexture,Texture& markTexture,Sprite back,double spd,float setSize):
	size(setSize),speed(spd){
	sprite.setTexture(fishTexture);
	mark.setTexture(markTexture);	
	mark_uvRect=IntRect(0,0,5,6);
	set(Vector2f(0,0),Vector2f(-5,5),Vector2f(3*size,3*size));
	randomMove(-5,5);
	randomPosition(back);
	mark.setPosition(x-7,y-rect.height-10);
	mark.setScale(3*size,3*size);
	area=rect.width*rect.height;
	setSpeed(speed);
}
void Fish::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mark, states);
	target.draw(sprite, states);
}
void Fish::Action(Player& player){
	setScale(3*size,3*size);
	mark.setScale(3*size,3*size);
	Action4(player.getback());
	autoRotation();
	upAreaData();
	if(player.getArea()<area){
		mark_uvRect.left=5;	
	}
	else{
		mark_uvRect.left=0;
		if(getDistance(Vector2f(x,y),player.getPosition())<300)dx=(x-player.getPosition().x),dy=(y-player.getPosition().y);
		if(touch(player)){
		player.eat(area);
		size=0.1*(rand()%16+8);
		randomMove(-5,5);
		randomPosition(player.getback());
		setSpeed(rand()%3+1);
		}
	}
	setSpeed(speed);
	mark.setTextureRect(mark_uvRect);
	mark.setPosition(x-7,y-rect.height-10);
}
void Fish::randomPosition(Sprite& back){
	FloatRect back_rect=back.getGlobalBounds();
	setPosition(Vector2f(rand()%int(back_rect.width+1)+(int)back_rect.left,rand()%int(back_rect.height+1)+(int)back_rect.top));
	rect=sprite.getGlobalBounds();
	if(rect.intersects(SCREENRECT)||!rect.intersects(back.getGlobalBounds()))randomPosition(back);	
}
double Fish::getArea(){
	return area;
}  
void Fish::upAreaData(){
	double angle=sprite.getRotation();
	sprite.setRotation(0);
	rect=sprite.getGlobalBounds();
	area=rect.width*rect.height;
	sprite.setRotation(angle);
	rect=sprite.getGlobalBounds();
}
//BlackShark
BlackShark::BlackShark(){}
BlackShark::BlackShark(Texture& fishTexture,Texture& markTexture,Sprite back,double spd,float setSize):
	eatTime(0),time(0){
	size=setSize;
	speed=spd;
	uvRect=IntRect(0,0,27,19);
	sprite.setTextureRect(uvRect);
	sprite.setTexture(fishTexture);
	mark.setTexture(markTexture);	
	mark_uvRect=IntRect(0,0,5,6);
	mark.setTextureRect(mark_uvRect);
	set(Vector2f(0,0),Vector2f(-5,5),Vector2f(5*size,5*size));
	randomMove(-5,5);
	randomPosition(back);
	mark.setPosition(x,y-4*rect.height);
	mark.setScale(3*size,3*size);
	area=rect.width*rect.height;
	setSpeed(speed);
}
bool BlackShark::touch(MovingBase Moving2){
	FloatRect nrect=rect;
	nrect.top+=nrect.height*0.2;
	nrect.left+=nrect.width*0.2;
	nrect.height*=0.6;
	nrect.width*=0.6;
	return nrect.intersects(Moving2.getGlobalBounds());
}	
void BlackShark::Action(Player& player,Fish (&fish)[20],BlackShark (&shark)[3],int self){
	if((!touch(player.getback2()))||((area>player.getArea()*1.5||area<player.getArea()/4)&&!(x<WINDOW_WIDTH&&x>0&&y<WINDOW_HEIGHT&&y>0))){
		size=0.1*(rand()%8+8)*player.getSize();
		randomMove(-5,5);
		randomPosition(player.getback());
		setSpeed(rand()%3+1);
	}
	if(eatTime>0){
		eatTime-=1.0/fps;
		uvRect.top=19;
	}
	else uvRect.top=0;
	if(time++%30==0){		
		if(uvRect.left==0)uvRect.left=27;
		else uvRect.left=0;
	}
	setScale(3*size,3*size);
	mark.setScale(3*size,3*size);
	Action4(player.getback());
	autoRotation();
	upAreaData();
	bool isEatPlayer=false;
	if(player.getArea()<area){
		mark_uvRect.left=5;
		if(getDistance(Vector2f(x,y),player.getPosition())<500){
			dx=player.getPosition().x-x,dy=player.getPosition().y-y;	
			isEatPlayer=true;
		}
		if(touch(player)){
			eat(player.getArea());
			player.die();	
		}
	}
	else{
		mark_uvRect.left=0;
		if(getDistance(Vector2f(x,y),player.getPosition())<300)dx=(x-player.getPosition().x),dy=(y-player.getPosition().y);
		if(touch(player)){
			player.eat(area);
			size=0.1*(rand()%9+8)*player.getSize();
			randomMove(-5,5);
			randomPosition(player.getback());
			setSpeed(rand()%3+1);
		}
	}
	for(int i=0;i<3;i++){
		if(i!=self&&area>shark[i].getArea()){
			if(touch(shark[i])){
				eat(shark[i].getArea());
				shark[i].size=0.1*(rand()%9+8)*player.getSize();
				shark[i].randomMove(-5,5);
				shark[i].randomPosition(player.getback());
				shark[i].setSpeed(rand()%3+1);	
			}	
			if(isEatPlayer&&player.getArea()>shark[i].getArea())continue;
			if(getDistance(Vector2f(x,y),shark[i].getPosition())<500)dx=shark[i].getPosition().x-x,dy=shark[i].getPosition().y-y;
		}
		if(i!=self&&area<shark[i].getArea()&&getDistance(Vector2f(x,y),shark[i].getPosition())<300)dx=(x-shark[i].getPosition().x),dy=(y-shark[i].getPosition().y);
	}
	for(int i=0;i<20;i++){
		if(touch(fish[i])&&fish[i].getArea()<area){
			eat(fish[i].getArea());
			fish[i].randomPosition(player.getback());				
		}
	}
	setSpeed(speed);
	sprite.setTextureRect(uvRect);
	mark.setTextureRect(mark_uvRect);
	mark.setPosition(x,y-0.7*rect.height);
}
void BlackShark::randomPosition(Sprite& back){
	FloatRect back_rect=back.getGlobalBounds();
	setPosition(Vector2f(rand()%int(back_rect.width+1)+(int)back_rect.left,rand()%int(back_rect.height+1)+(int)back_rect.top),back.getPosition());
	/*rx=rand()%int(back_rect.width+1)+(int)back_rect.left;
	ry=rand()%int(back_rect.height+1)+(int)back_rect.top;*/
	rect=sprite.getGlobalBounds();
	if(rect.intersects(SCREENRECT)||!rect.intersects(back.getGlobalBounds()))randomPosition(back);	
}
void BlackShark::eat(double eatenArea){
	size*=1+0.05*eatenArea/(area);
	eatTime=0.5;
} 
