#include "movingBase.hpp"

double getDistance(Vector2f pos1,Vector2f pos2){
	return sqrt((pos1.x-pos2.x)*(pos1.x-pos2.x)+(pos1.y-pos2.y)*(pos1.y-pos2.y));
}
int nearestTarget(MovingBase self,MovingBase target[],int n2,int except){
	double min=DBL_MAX;
	for(int j=0;j<n2;j++)if(j!=except)min=(getDistance(target[j].getPosition(),self.getPosition())<min?getDistance(target[j].getPosition(),self.getPosition()):min);
	if(min!=DBL_MAX){
		for(int j=0;j<n2;j++){
			if(target[j].getPosition().x!=-100)if(min==getDistance(target[j].getPosition(),self.getPosition())){
				return j;
			}
		}
	}
}

MovingBase::MovingBase(){};
MovingBase::~MovingBase(){};  
MovingBase::MovingBase(Texture& texture,bool random_pos,Vector2f random_move,Vector2f scale){
	sprite.setTexture(texture);    
    //randomPosition();    
    rx=x,ry=y;
    randomMove(random_move.x,random_move.y);
    rect=sprite.getGlobalBounds();
	left=rect.left ;
	top=rect.top ;
	right=left+rect.width ;
	bottom=top+rect.height ;
    sprite.setOrigin(rect.width/2.0,rect.height/2.0);
    sprite.setScale(scale);
};
MovingBase::MovingBase(Texture& texture, Vector2f pos, Vector2f move,Vector2f scale){
	sprite.setTexture(texture);    
    x=pos.x;
	y=pos.y;
	dx=move.x ;
    dy=move.y ;    
    rect=sprite.getGlobalBounds();
	left=rect.left ;
	top=rect.top ;
	right=left+rect.width ;
	bottom=top+rect.height ;
    sprite.setOrigin(rect.width/2.0,rect.height/2.0);
    sprite.setPosition(x,y) ;
    rx=x,ry=y;
    sprite.setScale(scale);
};
void MovingBase::set(Texture& texture,bool random_pos,Vector2f random_move,Vector2f scale){
	sprite.setTexture(texture);    
    //randomPosition();    
    rx=x,ry=y;
    randomMove(random_move.x,random_move.y);
    rect=sprite.getGlobalBounds();
	left=rect.left ;
	top=rect.top ;
	right=left+rect.width ;
	bottom=top+rect.height ;
    sprite.setOrigin(rect.width/2.0,rect.height/2.0);
    sprite.setScale(scale);
};
void MovingBase::set(Texture& texture, Vector2f pos, Vector2f move,Vector2f scale){
	sprite.setTexture(texture);    
    x=pos.x;
	y=pos.y;
	dx=move.x ;
    dy=move.y ;    
    rect=sprite.getGlobalBounds();
	left=rect.left ;
	top=rect.top ;
	right=left+rect.width ;
	bottom=top+rect.height ;
    sprite.setOrigin(rect.width/2.0,rect.height/2.0);
    sprite.setPosition(x,y) ;
    rx=x,ry=y;
    sprite.setScale(scale);
};
void MovingBase::set(Vector2f pos, Vector2f move,Vector2f scale){    
    x=pos.x;
	y=pos.y;
	dx=move.x ;
    dy=move.y ;    
    rect=sprite.getGlobalBounds();
	left=rect.left ;
	top=rect.top ;
	right=left+rect.width ;
	bottom=top+rect.height ;
    sprite.setOrigin(rect.width/2.0,rect.height/2.0);
    sprite.setPosition(x,y) ;
    rx=x,ry=y;
    sprite.setScale(scale);
};
void MovingBase::updata(Vector2f backPos){
	sprite.setPosition(rx+backPos.x,ry+backPos.y);
	sprite.move(dx, dy);
	x=sprite.getPosition().x;
	y=sprite.getPosition().y;
	rx=x-backPos.x;
	ry=y-backPos.y;
	rect=sprite.getGlobalBounds();
	left=rect.left ;
	top=rect.top ;
	right=left+rect.width ;
	bottom=top+rect.height ;	
}
void MovingBase::Action1(Vector2f backPos){
	updata(backPos);	
	if(right>WINDOW_WIDTH)dx=-fabs(dx);
	if(left<0)dx=fabs(dx);
	if(bottom>WINDOW_HEIGHT)dy=-fabs(dy);
	if(top<0)dy=fabs(dy);
}//¤Ï¼uwindow 
void MovingBase::Action2(Vector2f backPos){
	updata(backPos);	
	if(dx>0&&right>WINDOW_WIDTH+rect.width)x=-rect.width;
	if(dx<0&&left<-rect.width)x=WINDOW_WIDTH+rect.width;
	if(dy>0&&bottom>WINDOW_HEIGHT+rect.height)y=-rect.height;
	if(dy<0&&top<-rect.height)y=WINDOW_HEIGHT+rect.height;
}//¬ï³zwindow 
void MovingBase::Action3(Vector2f backPos){
	updata(backPos);
	if(right>=WINDOW_WIDTH)rx=WINDOW_WIDTH-rect.width/2;
	if(left<=0)rx=rect.width/2;
	if(bottom>=WINDOW_HEIGHT)ry=WINDOW_HEIGHT-rect.height/2;
	if(top<=0)ry=rect.height/2;	
	sprite.setPosition(rx+backPos.x,ry+backPos.y);	
}//¦bwindow°±¤î
void MovingBase::Action4(Sprite background){
	Vector2f backPos=background.getPosition();	
	double BACK_WIDTH=background.getGlobalBounds().width;
	double BACK_HEIGHT=background.getGlobalBounds().height;
	if(right>backPos.x+BACK_WIDTH)dx=-fabs(dx);
	if(left<backPos.x)dx=fabs(dx);
	if(bottom>backPos.y+BACK_HEIGHT)dy=-fabs(dy);
	if(top<backPos.y)dy=fabs(dy);
	updata(backPos);
}//¤Ï¼u­I´º 
void MovingBase::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}
void MovingBase::setPosition(double px,double py){
	sprite.setPosition(px,py);
	x=px,y=py;
    rx=x,ry=y;
}
void MovingBase::setPosition(Vector2f pos,Vector2f backPos){
	sprite.setPosition(pos);
	x=pos.x,y=pos.y;
    rx=x-backPos.x,ry=y-backPos.y;
}
void MovingBase::setOrigin(double ox,double oy){
	sprite.setOrigin(ox,oy);
}
void MovingBase::setOrigin(Vector2f ori){
	sprite.setOrigin(ori);
}
void MovingBase::setCenterOrigin(){
	rect=sprite.getGlobalBounds();
	left=rect.left ;
	top=rect.top ;
	right=left+rect.width ;
	bottom=top+rect.height ;	
	sprite.setOrigin(rect.width/2.0,rect.height/2.0);
}
/*void MovingBase::randomPosition(){
	int rax=rand()%(WINDOW_WIDTH-100+1-(int)rect.width)+rect.width+50,ray=rand()%(WINDOW_HEIGHT-100+1-(int)rect.height)+rect.height+50;
	sprite.setPosition(rax,ray);
	x=rax,y=ray;
	rx=x,ry=y;
}*/
void MovingBase::setMove(double mx,double my){
	dx=mx,dy=my;
}
void MovingBase::setMove(Vector2f move){
	dx=move.x,dy=move.y;
}
void MovingBase::setdx(double sdx){
	dx=sdx;
}
void MovingBase::setdy(double sdy){
	dy=sdy;
}
void MovingBase::setSpeed(double spd){
	dx=spd*cos(atan2(dy,dx)),dy=spd*sin(atan2(dy,dx));
}
void MovingBase::randomMove(int min_d,int max_d){
	int d=max_d-min_d;
	dx=rand()%(d+1)+min_d,dy=rand()%(d+1)+min_d;
	if(dx==0&&dy==0)randomMove(min_d,max_d);
}
void MovingBase::setRotation(double angle){
	sprite.setRotation(angle);
}
void MovingBase::autoRotation(double deviation){
	double sx=sprite.getScale().x;
	if(dx>0||(dx==0&&dy!=0))sprite.setScale(fabs(sx),sprite.getScale().y);  	
	if(dx<0)sprite.setScale(-fabs(sx),sprite.getScale().y);
	sprite.setRotation(atan(dx==0&&dy==0?0:dy/dx)*180/PI+deviation);
}
void MovingBase::setScale(double sx,double sy){
	sprite.setScale(sx,sy);
}
void MovingBase::setScale(Vector2f scale){
	sprite.setScale(scale);
}
void MovingBase::setColor(Color color){
	sprite.setColor(color);
}
void MovingBase::randomColor(int alpha){
	sprite.setColor(Color(rand()%256,rand()%256,rand()%256,alpha));
}
void MovingBase::setTexture(Texture& tex){
	sprite.setTexture(tex);
}
Texture MovingBase::getTexture(){
	return *sprite.getTexture();
}
Vector2f MovingBase::getPosition(){
	return sprite.getPosition();
}
Vector2f MovingBase::getMove(){
	return Vector2f(dx,dy);
}
double MovingBase::getdx(){
	return dx;
}
double MovingBase::getdy(){
	return dy;
}
double MovingBase::getSpeed(){
	return sqrt(dx*dx+dy*dy);
}
double MovingBase::getRotation(){
	return sprite.getRotation();
}
Vector2f MovingBase::getScale(){
	return sprite.getScale();
}
Color MovingBase::getColor(){
	return sprite.getColor();
}
FloatRect MovingBase::getGlobalBounds(){
	return rect;
}
bool MovingBase::touch(MovingBase Moving2){
	return rect.intersects(Moving2.getGlobalBounds());
}	
double MovingBase::getBord(string Str){
	double result=-1;   
	if(Str=="left")result=left;
	if(Str=="right")result=right;
	if(Str=="top")result=top;
	if(Str=="bottom")result=bottom;
	return result;
}
