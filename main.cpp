#include "FishClass.hpp"

int main(){
	srand(time(0));
	reset:
	RenderWindow window(VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"WINDOW");
	Font font;
    font.loadFromFile("resources/Mojangles.ttf");
    Texture starttexture;
	starttexture.loadFromFile("resources/start.png");
	Texture sharktexture;
	sharktexture.loadFromFile("resources/shark.png");
	Texture marktexture;
	marktexture.loadFromFile("resources/mark.png");
	Texture fishtexture;
	fishtexture.loadFromFile("resources/fish.png");
	Texture blacksharktexture;
	blacksharktexture.loadFromFile("resources/blackshark.png");
	Player Shark=Player(sharktexture,font,5);
	BlackShark blackshark[3];
	for(int i=0;i<3;i++)blackshark[i]=BlackShark(blacksharktexture,marktexture,Shark.getback(),5,0.1*(rand()%6+8));
	Fish fish[20];
	for(int i=0;i<20;i++)fish[i]=Fish(fishtexture,marktexture,Shark.getback(),0.5*(rand()%11+5),0.1*(rand()%11+5));
	Text gameover("GAMEOVER",font,100);
	gameover.setOrigin(gameover.getGlobalBounds().width/2,gameover.getGlobalBounds().height/2);
	gameover.setPosition(WINDOW_WIDTH/2.0,WINDOW_HEIGHT/2.0);
	gameover.setFillColor(Color::Red); 
	Sprite start(starttexture);
	start.setPosition(-40,-20);
	window.setFramerateLimit(fps);
	
	int sharktime=0;
	bool startscreen=false;
	while (window.isOpen()) {
        Event event; 
        while (window.pollEvent(event)){
            if (event.type == Event::Closed)window.close();	
            if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))window.close();	
		}
		if(Shark.score.score<100000){
			if(sharktime<=300)sharktime++;
			if(sharktime==300)for(int i=0;i<3;i++)blackshark[i].randomPosition(Shark.getback());
			if(!startscreen){
				window.draw(start);
				if(Keyboard::isKeyPressed(Keyboard::LShift)||Keyboard::isKeyPressed(Keyboard::RShift))startscreen=true;
			}
			else{
				window.clear(Color::Black);
				if(!Shark.dead()){
					Shark.Action();
					if(sharktime>=300)for(int i=0;i<3;i++)blackshark[i].Action(Shark,fish,blackshark,i);
					for(int i=0;i<20;i++)fish[i].Action(Shark);
		    	    window.draw(Shark.getback());
		    	    for(int i=0;i<20;i++)window.draw(fish[i]);
		        	if(sharktime>=300)for(int i=0;i<3;i++)window.draw(blackshark[i]);
		        	window.draw(Shark);
		        } 
		        else{
		        	Shark.score.setOrigin(Shark.score.getGlobalBounds().width/2,Shark.score.getGlobalBounds().height/2);
					window.draw(gameover);
					Shark.score.x=WINDOW_WIDTH/2.0,Shark.score.y=WINDOW_HEIGHT/2.0+120;
					Shark.score.Action();
					Shark.score.endStr="\nPress Shift to play again";
					window.draw(Shark.score);
					if(Keyboard::isKeyPressed(Keyboard::LShift)||Keyboard::isKeyPressed(Keyboard::RShift))goto reset;
					if(Keyboard::isKeyPressed(Keyboard::Escape))window.close();	
				} 
			}
		}
		else{
			window.clear(Color::Black);
			window.draw(gameover);
			gameover.setString("WIN");
			gameover.setFillColor(Color::Yellow);
			gameover.setOrigin(gameover.getGlobalBounds().width/2,gameover.getGlobalBounds().height/2);
			gameover.setPosition(WINDOW_WIDTH/2.0,WINDOW_HEIGHT/2.0);
			Shark.score.endStr="\nPress Shift to play again";
			Shark.score.Action();
			Shark.score.setOrigin(Shark.score.getGlobalBounds().width/2,Shark.score.getGlobalBounds().height/2);	
			Shark.score.x=WINDOW_WIDTH/2.0,Shark.score.y=WINDOW_HEIGHT/2.0+120;
			window.draw(Shark.score);
			if(Keyboard::isKeyPressed(Keyboard::LShift)||Keyboard::isKeyPressed(Keyboard::RShift))goto reset;
		} 
        window.display();
    }
	return 0;
}
