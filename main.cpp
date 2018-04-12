//
// Created by Marcus on 15.03.2018.
//


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include "AnimatedSprite.h"


using namespace std;
using namespace sf;

constexpr int window_width{800}, window_height{600};






sf::RenderWindow window(sf::VideoMode(800, 600), "World of Zuul");
sf::Vector2u TextureSize;  //Added to store HeroTexture size.
sf::Vector2u WindowSize;   //Added to store window size.


// TEXTURES
sf::Texture exitButton;
sf::Texture startButton;
sf::Texture BackgroundTexture;
sf::Texture TitleTexture;
sf::Texture HeroTexture;
sf::Texture Chest_close;
sf::Texture Chest_open;
sf::Texture Ground;

// SPRITES

sf::Sprite title;           // Title "World of Zuul" sprite
sf::Sprite background;      // background for Titlescreen sprite
sf::Sprite exitButtonImage; // Exit Button sprite
sf::Sprite startButtonImage;// Start Button sprite
sf::Sprite hero;            // Hero sprite
sf::Sprite chest_close;     // Chest is close sprite
sf::Sprite chest_open;      // Chest is open sprite
sf::Sprite ground;          // Ground sprite


// SOUNDS BBUFFERS
sf::SoundBuffer Musicbuffer;
// SOUNDS
sf::Sound music;


int gameloop()

{
    window.setVisible(false);
    sf::Vector2i screenDimensions(800,600);
    sf::RenderWindow gameWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), "World of Zuul!");
    gameWindow.setFramerateLimit(60);

/**
 *  Backgound load
 */


    if (!Ground.loadFromFile("sprites/ground.png"))
    {
        std::cout << "Failed to load chest_close image!" << std::endl;
        return 1;
    }


    float groundScaleX = 1.2f;
    float groundScaleY = 1.2f;

    ground.setTexture( Ground );
    ground.setScale( groundScaleX, groundScaleY  );



/**
 *  Sprite Close Chest load
 */

    if (!Chest_close.loadFromFile("sprites/chest_close.PNG"))
    {
        std::cout << "Failed to load chest_close image!" << std::endl;
        return 1;
    }

    float chestcloseWidth = chest_close.getLocalBounds().width;
    float chestclosHeight = chest_close.getLocalBounds().height;

    chest_close.setPosition( WindowSize.y /2, 0.5*WindowSize.x  );


    float chest_closeScaleX = 0.15f;
    float chest_closeScaleY = 0.15f;

    chest_close.setTexture( Chest_close );
    chest_close.setScale( chest_closeScaleX, chest_closeScaleY );

/**
 *   Herotextures loading
 */


    if (!HeroTexture.loadFromFile("sprites/hero.png"))
    {
        std::cout << "Failed to load player image!" << std::endl;
        return 1;
    }





    // set up the animations for all four directions (set spritesheet and push frames)
    Animation walkingAnimationDown;
    walkingAnimationDown.setSpriteSheet(HeroTexture);
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect( 0, 0, 32, 32));

    Animation walkingAnimationLeft;
    walkingAnimationLeft.setSpriteSheet(HeroTexture);
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect( 0, 32, 32, 32));

    Animation walkingAnimationRight;
    walkingAnimationRight.setSpriteSheet(HeroTexture);
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect( 0, 64, 32, 32));

    Animation walkingAnimationUp;
    walkingAnimationUp.setSpriteSheet(HeroTexture);
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect( 0, 96, 32, 32));

    Animation* currentAnimation = &walkingAnimationDown;

    // set up AnimatedSprite
    AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
    animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));

    sf::Clock frameClock;

    float speed = 80.f;
    bool noKeyWasPressed = true;

    while (gameWindow.isOpen())
    {
        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                gameWindow.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                gameWindow.close();
        }

        sf::Time frameTime = frameClock.restart();

        // if a key was pressed set the correct animation and move correctly
        sf::Vector2f movement(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)|| sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            currentAnimation = &walkingAnimationUp;
            movement.y -= speed;
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)|| sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            currentAnimation = &walkingAnimationDown;
            movement.y += speed;
            noKeyWasPressed = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)|| sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            currentAnimation = &walkingAnimationLeft;
            movement.x -= speed;
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)|| sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            currentAnimation = &walkingAnimationRight;
            movement.x += speed;
            noKeyWasPressed = false;
        }
        animatedSprite.play(*currentAnimation);
        animatedSprite.move(movement * frameTime.asSeconds());

        // if no key was pressed stop the animation
        if (noKeyWasPressed)
        {
            animatedSprite.stop();
        }
        noKeyWasPressed = true;

        // update AnimatedSprite
        animatedSprite.update(frameTime);

        // draw
        gameWindow.clear();
        gameWindow.draw(ground);
        gameWindow.draw(animatedSprite);
        gameWindow.draw(chest_close);
        gameWindow.display();
    }

    return 0;
}

void playTitleMusic(){
    if (!Musicbuffer.loadFromFile("music/Castle.ogg"))
        std:: cout << "Can't find music file file ";


    music.setBuffer(Musicbuffer);
    music.play();
}








///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  INTRO SCREEN
 *
 *
 *
*/
int startGame(){


    /**
     *    Background image load
     *
     * */

    if(!BackgroundTexture.loadFromFile("sprites/background.png"))
    {
        std:: cout << "Can't find background Image file ";
    }
    else
    {
        TextureSize = BackgroundTexture.getSize(); //Get size of HeroTexture.
        WindowSize = window.getSize();             //Get size of window.

        float ScaleX = (float) WindowSize.x / TextureSize.x;
        float ScaleY = (float) WindowSize.y / TextureSize.y;     //Calculate scale.

        background.setTexture(BackgroundTexture);
        background.setScale(ScaleX, ScaleY);      //Set scale.
    }
    /**
     *    Title image load
     *
     * */

    if(!TitleTexture.loadFromFile("sprites/title.png"))
    {
        std:: cout << "Can't find title Image file ";
    }
    else
    {
        TextureSize = TitleTexture.getSize(); //Get size of HeroTexture.
        WindowSize = window.getSize();             //Get size of window.

        float ScaleX = (float) WindowSize.x / TextureSize.x;
        float ScaleY = (float) 0.5 * WindowSize.y / TextureSize.y;     //Calculate scale.

        title.setTexture(TitleTexture);
        title.setScale(ScaleX, ScaleY);      //Set scale.
    }
    /**
     *    Main Menu load
     *
     * */
    sf::Font font;
    if ( !font.loadFromFile( "fonts/MATURASC.TTF" ) )
        std::cout << "Can't find the font file" << std::endl;

    //
    // EXIT BUTTON
    //


    if ( !exitButton.loadFromFile( "sprites/exit.png" ) )
        std::cout << "Can't find the image" << std::endl;
    float exitButtonWidth = exitButtonImage.getLocalBounds().width;
    float exitButtonHeight = exitButtonImage.getLocalBounds().height;

    exitButtonImage.setPosition( WindowSize.y /2-exitButtonHeight, 0.5*WindowSize.x - exitButtonWidth );


    float exitScaleX = (float) 2*WindowSize.x / TextureSize.x;
    float exitScaleY = (float) 0.3*WindowSize.y / TextureSize.y;

    exitButtonImage.setTexture( exitButton );
    exitButtonImage.setScale( exitScaleX, exitScaleY );

    //
    // StartGame BUTTON
    //


    if ( !startButton.loadFromFile( "sprites/start.png" ) )
        std::cout << "Can't find the image" << std::endl;
    startButtonImage.setPosition( WindowSize.y /2 -100, 0.3*WindowSize.x  );

    float startButtonWidth = startButtonImage.getLocalBounds().width;
    float startButtonHeight = startButtonImage.getLocalBounds().height;
    float startScaleX = (float) 2*WindowSize.x / TextureSize.x;
    float startScaleY = (float) 0.3*WindowSize.y / TextureSize.y;

    startButtonImage.setTexture( startButton );
    startButtonImage.setScale( startScaleX, startScaleY );

    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::MouseMoved:
                {
                    /**
                     *  Button Color change then Mousover
                     *
                     * */
                    sf::Vector2i mousePos = sf::Mouse::getPosition( window );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );


                    if ( startButtonImage.getGlobalBounds().contains( mousePosF ) )
                    {
                        startButtonImage.setColor( sf::Color( 250, 20, 20 ) );
                    }
                    else
                    {
                        startButtonImage.setColor( sf::Color( 255, 255, 255 ) );
                    }
                    if ( exitButtonImage.getGlobalBounds().contains( mousePosF ) )
                    {
                        exitButtonImage.setColor( sf::Color( 250, 20, 20 ) );
                    }
                    else
                    {
                        exitButtonImage.setColor( sf::Color( 255, 255, 255 ) );
                    }
                }
                    break;
                    // MOUSE Button click on Button
                    // EXIT BUTTON
                case sf::Event::MouseButtonPressed:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition( window );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    if ( exitButtonImage.getGlobalBounds().contains( mousePosF ) )
                    {
                        std::cout << "Exit Button clicked!" << std::endl;
                        window.close();

                    }
                    if ( startButtonImage.getGlobalBounds().contains( mousePosF ) )
                    {
                        std::cout << "StartGame Button clicked!" << std::endl;

                        ////////
                        //Start Game
                        ////////
                        gameloop();


                    }
                }

                    break;
            }
        }
        /**
         *   Drawing the elements to Titlescreen
         *
         * */


        window.clear();
        window.draw(background);
        window.draw(title);
        window.draw(exitButtonImage);
        window.draw(startButtonImage);
        window.display();

    }

}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {

    playTitleMusic();
    startGame();





    return 0;
}