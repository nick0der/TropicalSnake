#ifndef Game_h
#define Game_h

/////////////////////////////////////////////////////////
//          КЛАС ГРА (для управління процесом гри)     //
////////////////////////////////////////////////////////
class Game {
    
private:
    Menu menu;
    Snake snake;
    Fruit fruit;
    BadFruit bomb1, bomb2, bomb3;
    
    double time, timer, delay;
    double bomb_timer1, bomb_timer2, bomb_timer3;  //Таймери для бомб
    double bomb_delay1, bomb_delay2, bomb_delay3;  //Затримка на екрані для бомб
    
    Texture t_limit, t_background;
    Sprite limit, background;
    
    RenderWindow window;
    Font ash;
    Clock clock;
    
    double press_timer;
    bool isPressed;
    bool ExtendedMode;
    
public:
    Game();
    virtual ~Game();
    
    void Run();             //Запуск усієї програми
    void GameProccess();    //Запуск ігрового процесу
    void Reset();           //Встановлення дефолтних параметрів гри
};
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////






//////////////////////////////////////////////////////////
/*                     РЕАЛІЗАЦІЯ                       */
//////////////////////////////////////////////////////////
Game::Game()
{
    ash.loadFromFile("Ash.ttf");
    t_limit.loadFromFile("Images/Limit.png");
     t_background.loadFromFile("/Users/nickpopyk/Desktop/TropicalSnake/TropicalSnake/Images/Back.jpg");
    //t_background.loadFromFile("Images/Back.jpg");
    
    limit.setTexture(t_limit);
    background.setTexture(t_background);
}

Game::~Game()
{
}

void Game::Run()
{
    window.create(VideoMode (WIDTH, HEIGHT), "TropicalSnake");
menu:
    ExtendedMode = menu.Run(window);
start:
    Reset();
    GameProccess();
    menu.ShowGameOver(window, ExtendedMode);
    //Коли гра закінчена, виводиться повідомлення,
    //що гра завершена і кількість очок
    
    
    Event event;
    while (window.waitEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window.close();
            return;
        }
        
        if ((Keyboard::isKeyPressed(Keyboard::R))|| ((IntRect(486, 820, 198, 198).contains(Mouse::getPosition(window))) && (Mouse::isButtonPressed(Mouse::Left))))
        {
            menu.ClickSound.play();
            goto start;
        }
        
        if ((Keyboard::isKeyPressed(Keyboard::Escape))|| ((IntRect(786, 820, 198, 198).contains(Mouse::getPosition(window))) && (Mouse::isButtonPressed(Mouse::Left))))
        {
            menu.ClickSound.play();
            goto menu;
        }
    }
}


void Game::GameProccess()
{
    while (window.isOpen() && !gameover)
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        
        time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        
        //Рахуємо час, що пройшов від моменту кліку
        press_timer+=time;
        
        //Якщо з моменту натискання клавіші пройшло delay секунд
        //Зчитування клавіш вмикається
        if ((press_timer > delay)&&(isPressed))
        {
            isPressed = false;
        }
        //Якщо нажато клавішу, запускаємо таймер, що триває delay секунд
        //Впродовж цього часу не зчитуються інші натискання, що запобігає
        //багу, коли змійка з'їдає саму себе при різкому розвороті
        if ( (!isPressed) && ( (Keyboard::isKeyPressed(Keyboard::Right)) || (Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::Down)) || (Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::D)) || (Keyboard::isKeyPressed(Keyboard::A)) || (Keyboard::isKeyPressed(Keyboard::S)) || (Keyboard::isKeyPressed(Keyboard::W)) ))
        {
            snake.Press();
            press_timer = 0;
            isPressed = true;
        }
        
        
        
        if (timer>delay) {timer=0; snake.Move(); }
        //Якщо таймер перебілшив затримку,
        //Онуляємо його і рухаємо змію
        
        window.clear();
        window.draw(background);
        window.draw(limit);
        snake.Draw(window, fruit);
        fruit.Draw(window);
        menu.DrawScore(window);
        
        if (ExtendedMode)
        {
            snake.CheckExtended(fruit, bomb1);
            snake.CheckExtended(fruit, bomb2);
            snake.CheckExtended(fruit, bomb3);
            //Рахуємо час для бомб
            bomb_timer1+=time;
            bomb_timer2+=time;
            bomb_timer3+=time;
            
            //Оновлення пасток
            if (bomb_timer1>bomb_delay1)
            {
                bomb_timer1=0;
                bomb1.Generate(snake.body, snake.getLength());
            }
            if (bomb_timer2>bomb_delay2)
            {
                bomb_timer2=0;
                bomb2.Generate(snake.body, snake.getLength());
            }
            if (bomb_timer3>bomb_delay3)
            {
                bomb_timer3=0;
                bomb3.Generate(snake.body, snake.getLength());
            }
        }
        else snake.Check(fruit);
        
        
        if (ExtendedMode)
        {
            bomb1.Draw(window);
            bomb2.Draw(window);
            bomb3.Draw(window);
        }
        
        window.display();
        if (snake.getLength() == 266) break;
       
        
    }
}

void Game::Reset()
{
    gameover=false;
   
    timer = 0;
    press_timer = 0;
    isPressed = false;
    
    delay = 0.15; //Затримка змії
    //Чим вона менша, тим більша швидкість змії
    
    snake.setStartParameters();
    fruit.setStartParameters();
    
    if (ExtendedMode)
    {
    bomb_timer1=0;
    bomb_timer2=0;
    bomb_timer3=0;
    
    bomb_delay1=5;
    bomb_delay2=7;
    bomb_delay3=9;
    
    
    bomb1.setStartParameters();
    bomb2.setStartParameters();
    bomb3.setStartParameters();
    }
    clock.restart();
    
}



///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////



#endif /* Game_h */
