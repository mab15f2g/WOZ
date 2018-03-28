#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace std;
using namespace sf;

constexpr int window_width{800}, window_height{600};






sf::RenderWindow window(sf::VideoMode(800, 600), "World of Zuul");
sf::Vector2u TextureSize;  //Added to store texture size.
sf::Vector2u WindowSize;   //Added to store window size.


// TEXTURES
sf::Texture exitButton;
sf::Texture startButton;
sf::Texture startGameButton;
sf::Texture BackgroundTexture;
sf::Texture EnterNameTexture;
sf::Texture TitleTexture;

// SPRITES

sf::Sprite title;
sf::Sprite background;
sf::Sprite exitButtonImage;
sf::Sprite startButtonImage;
sf::Sprite startGameImage;
sf::Sprite enterplayername;



int entername()
{

    sf::Font font;
    if (!font.loadFromFile("fonts/MATURASC.TTF"))
        return EXIT_FAILURE;

    sf::Event event;
    sf::String playerInput;
    sf::Text playerText;
    playerText.setPosition(300,300);
    playerText.setColor(sf::Color::Red);

    while (window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::TextEntered)
            {
                if(event.text.unicode < 128)
                {
                    playerInput +=event.text.unicode;
                    playerText.setString(playerInput);
                }
            }

        }

        window.draw(playerText);
        //window.display();
    }
    return 0;
}




void setPlayerName(){



    if(!TitleTexture.loadFromFile("sprites/entername.png"))
    {
        std:: cout << "Can't find title Image file ";
    }
    else
    {
        TextureSize = TitleTexture.getSize(); //Get size of texture.
        WindowSize = window.getSize();             //Get size of window.

        float ScaleX = (float) WindowSize.x / TextureSize.x;
        float ScaleY = (float) 0.5 * WindowSize.y / TextureSize.y;     //Calculate scale.

        enterplayername.setTexture(TitleTexture);
        enterplayername.setScale(ScaleX, ScaleY);      //Set scale.
    }


    window.clear();
    window.draw(background);
    window.draw(enterplayername);
    startButtonImage.setScale(0.9 ,0.9);
    startButtonImage.setPosition(WindowSize.y /2 -100, 0.3*WindowSize.x +160 );


    exitButtonImage.setScale(0.9,0.9);
    exitButtonImage.setPosition( WindowSize.y /2 +100, 0.5*WindowSize.x  );



    window.display();


}


void drawGame(){


}


void startGameLoop(){

}





/**
 *  Inventory class
 *
 * */

class Inventory{
public:
    Inventory() {

    }


};


/**
 *  Class Player with inventory ,  lifepoints ,  save data
 *
 * */

class Player {
public:

    // vector<Inventory> inventory;
    int lifepoints;
    String name;
    Image playerImage;


    Player(int lifepoints, String name, Image image) {
        this-> lifepoints = lifepoints;
        this -> name = name;

    }
    /**
    *   getInventory shows all items in the inventory
    *
    * */
    vector<Inventory> getInventory(){
        vector<Inventory> inventory;
        return inventory;
    }

};

/**
 *   Inventory
 *   shows all items in the inventory
 *
 * */
vector<Inventory> getInventory(){
    vector<Inventory> inventory;
    return inventory;
}






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



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
        TextureSize = BackgroundTexture.getSize(); //Get size of texture.
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
        TextureSize = TitleTexture.getSize(); //Get size of texture.
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

                        setPlayerName();
                        drawGame();
                        startGameLoop();

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

    startGame();





    return 0;
}
