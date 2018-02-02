#include <iostream>
#include "fluid.h"
#include <SFML/Graphics.hpp>
#include <cmath>

#define SIZE 100

using namespace std;

sf::Color getTColor(sf::Image &color, float x){
    if(x>0.999) x=0.999 ;
    if(x<0.001) x=0.001 ;
    return color.getPixel((int)(x*color.getSize().x),0) ;
}

int main()
{

    Fluid fluid(SIZE, 0.02);

    //sf::RectangleShape lineVec[SIZE][SIZE];

    /*for(int j = 1; j < SIZE; ++j){
        for(int i = 1; i < SIZE; ++i){
            lineVec[i][j].setSize(sf::Vector2f(1, 0.1));
            lineVec[i][j].setOrigin(0, 0);
            lineVec[i][j].setPosition(sf::Vector2f(i, j));
            lineVec[i][j].setFillColor(sf::Color::Black);
        }
    }*/


    sf::RenderWindow window(sf::VideoMode(SIZE*2, SIZE), "SFML works!");
    sf::Image image;
    image.create((SIZE+2)*2, SIZE+2);
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::Image ImgColor;
    ImgColor.loadFromFile("color.jpg");

    sf::Vector2i oldPosMouse;
    sf::Vector2f force;

    bool released = false;
    int scalex = 1080/SIZE;
    int scaley = 1080/SIZE;
    cout << scalex << endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            }

        /*for(int j = 1; j < SIZE; ++j){
            for(int i = 1; i < SIZE; ++i){
                lineVec[i][j].setSize(sf::Vector2f(sqrt(fluid.getVec(i, j).x*fluid.getVec(i, j).x+fluid.getVec(i, j).y*fluid.getVec(i, j).y)*10, 0.1));
                lineVec[i][j].setRotation((atan2(fluid.getVec(i, j).x, fluid.getVec(i, j).y))*180.0 /M_PI+90);
            }
        }*/

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            fluid.reset();
        }


        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(!released){
                force = sf::Vector2f(oldPosMouse.x-sf::Mouse::getPosition(window).x, oldPosMouse.y-sf::Mouse::getPosition(window).y);
                oldPosMouse = sf::Mouse::getPosition(window);

                fluid.addForces(sf::Mouse::getPosition(window).x/scalex, sf::Mouse::getPosition(window).y/scaley, -force.x*100, -force.y*100);
            }

            released = false;
        }else{
            released = true;
            oldPosMouse.x = sf::Mouse::getPosition(window).x; oldPosMouse.y = sf::Mouse::getPosition(window).y;
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            for(int j = sf::Mouse::getPosition(window).y/scaley-10; j <= sf::Mouse::getPosition(window).y/scaley+10; ++j){
                for(int i = sf::Mouse::getPosition(window).x/scalex-10; i <= sf::Mouse::getPosition(window).x/scalex+10; ++i){
                    fluid.addDensity(i,j, 10);
                }
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
            for(int j = sf::Mouse::getPosition(window).y/scaley-1; j <= sf::Mouse::getPosition(window).y/scaley+1; ++j){
                for(int i = sf::Mouse::getPosition(window).x/scalex-1; i <= sf::Mouse::getPosition(window).x/scalex+1; ++i){
                    fluid.addT(i,j, 500);
                }
            }
        }


        fluid.update();


        for(int j = 0; j <= SIZE; ++j){
            for(int i = 0; i <= SIZE; ++i){
                if(fluid.getDens(i, j)*2 > 255)
                    image.setPixel(i, j, sf::Color(255-127.5, 0, 0));
                else
                    image.setPixel(i, j, sf::Color(255-fluid.getDens(i, j), 255-fluid.getDens(i, j)*2, 255-fluid.getDens(i, j)*2));
            }
        }


        for(int j = 0; j <= SIZE; ++j){
            for(int i = SIZE+0; i <= SIZE*2; ++i){
                image.setPixel(i, j, getTColor(ImgColor, fluid.getT(i, j)/500));
            }
        }


        texture.update(image);

        window.clear(sf::Color::White);
        window.draw(sprite);
        /*for(int j = 0; j < 100; ++j){
            for(int i = 0; i < 100; ++i){
                window.draw(lineVec[i][j]);
            }
        }*/
        window.display();
    }

    return 0;
}
