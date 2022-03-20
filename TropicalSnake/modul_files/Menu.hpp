#ifndef Menu_h
#define Menu_h

  //////////////////////////////////////////////////////////
 /////                   КЛАС МЕНЮ                     ////
//////////////////////////////////////////////////////////

class Menu
{
private:
    
    Texture t_back, t_frame, t1, t2, t3, t4, c1, c2, c3, c4, RB, MB;
    Texture t_button, t_over, t_yourscore, t_about, t_choose, t_mod1, t_mod2, t_mod1c, t_mod2c;
    Sprite Background, Frame, NewGame, HighScores, Info, Exit;
    Sprite button, GameOver, YourHScore, About, Choose, Classic, Extended;
    Text InGameScore, ScoreMessage, textHScore1, textHScore2;
    Font ash;
    
    SoundBuffer buffer1, buffer2, buffer3;
public:
    Sprite RestartButton, MenuButton;            //public спрайти для доступу з класу Game
    Sound ClickSound, GameOverSound, BackMusic;
    
    Menu();
    virtual ~Menu();
    int Run(RenderWindow&);            //Запуск меню
    void DrawScore(RenderWindow&);      //Відображення очок
    void ShowGameOver(RenderWindow&, const bool&);   //Запускається після завершення ігрового процесу
};

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////






//////////////////////////////////////////////////////////
/*                     РЕАЛІЗАЦІЯ                       */
//////////////////////////////////////////////////////////

Menu::Menu()
{
    //Загрузка всіх необхідних файлів
    t_back.loadFromFile("MenuPictures/tropical-background.jpg");
    t_frame.loadFromFile("MenuPictures/Frame.png");
    t1.loadFromFile("MenuPictures/NewGameBlue.png");
    t2.loadFromFile("MenuPictures/RecordBlue.png");
    t3.loadFromFile("MenuPictures/InfoBlue.png");
    t4.loadFromFile("MenuPictures/ExitBlue.png");
    c1.loadFromFile("MenuPictures/NewGameGreen.png");
    c2.loadFromFile("MenuPictures/RecordGreen.png");
    c3.loadFromFile("MenuPictures/InfoGreen.png");
    c4.loadFromFile("MenuPictures/ExitGreen.png");
    t_button.loadFromFile("MenuPictures/EmptyButton.png");
    t_over.loadFromFile("MenuPictures/GameOver.png");
    
    t_choose.loadFromFile("MenuPictures/ChooseMode.png");
    t_mod1.loadFromFile("MenuPictures/ClassicBlue.png");
    t_mod1c.loadFromFile("MenuPictures/ClassicGreen.png");
    t_mod2.loadFromFile("MenuPictures/ExtendedBlue.png");
    t_mod2c.loadFromFile("MenuPictures/ExtendedGreen.png");
    
    RB.loadFromFile("MenuPictures/RestartButton.png");
    MB.loadFromFile("MenuPictures/MenuButton.png");
    
    //Встановлюємо текстури спрайтів
    Background.setTexture(t_back);
    Frame.setTexture(t_frame);
    button.setTexture(t_button);
    GameOver.setTexture(t_over);
    Choose.setTexture(t_choose);
    
    ash.loadFromFile("Ash.ttf");
    
    //Виводить фінальний результат вкінці гри
    ScoreMessage.setFont(ash);
    ScoreMessage.setString("");
    ScoreMessage.setCharacterSize(80);
    ScoreMessage.setFillColor(Color::Black);
    ScoreMessage.setStyle(Text::Bold);
    
    //Виводить очки під час гри
    InGameScore.setFont(ash);
    InGameScore.setCharacterSize(50);
    
    //Встановлення звуків
    buffer1.loadFromFile("Sounds/ClickSound.wav");
    buffer2.loadFromFile("Sounds/GameOverSound.wav");
    buffer3.loadFromFile("Sounds/BackMusic.wav");
    ClickSound.setBuffer(buffer1);
    GameOverSound.setBuffer(buffer2);
    BackMusic.setBuffer(buffer3);
    
    //2 кнопки: рестарт і для переходу в меню
    RestartButton.setTexture(RB);
    MenuButton.setTexture(MB);
    
    //4 кнопки меню:
    NewGame.setPosition(530, 270);
    HighScores.setPosition(580, 405);
    Info.setPosition(635, 530);
    Exit.setPosition(625, 665);
    
    Frame.setPosition(210, 130);
    
    //Текст, що показує рекорд
    textHScore1.setFont(ash);
    textHScore1.setCharacterSize(65);
    textHScore1.setFillColor(Color::Blue);
    textHScore2.setFont(ash);
    textHScore2.setCharacterSize(65);
    textHScore2.setFillColor(Color::Blue);
    
    //Повідомлення("Ваш рекорд")
    t_yourscore.loadFromFile("MenuPictures/YourScore.png");
    YourHScore.setTexture(t_yourscore);
    
    //Повідомлення(інформація про проект)
    t_about.loadFromFile("MenuPictures/Info.png");
    About.setTexture(t_about);

}

Menu::~Menu()
{
}

int Menu::Run(RenderWindow& window)
{
    BackMusic.play();
    BackMusic.setLoop(true);
main_menu:   //Головне меню
    while (window.isOpen())
    {
        NewGame.setTexture(t1);
        HighScores.setTexture(t2);
        Info.setTexture(t3);
        Exit.setTexture(t4);
        
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
                exit(EXIT_SUCCESS);
            }
        }
        
        //Кнопки світяться, коли на них наведено курсор
        if (IntRect(480, 260, 522, 131).contains(Mouse::getPosition(window))) { NewGame.setTexture(c1); }
        if (IntRect(480, 390, 522, 131).contains(Mouse::getPosition(window))) { HighScores.setTexture(c2); }
        if (IntRect(480, 520, 522, 131).contains(Mouse::getPosition(window))) { Info.setTexture(c3); }
        if (IntRect(480, 650, 522, 131).contains(Mouse::getPosition(window))) { Exit.setTexture(c4); }
        
        if ((Mouse::isButtonPressed(Mouse::Left))&&(IntRect(480, 260, 522, 131).contains(Mouse::getPosition(window))))
        {
            //Нажато кнопку "Нова гра"
            ClickSound.play();
            MenuButton.setPosition(650, 915);
            Choose.setPosition(400, 290);
            Classic.setPosition(545, 400);
            Extended.setPosition(520, 525);
            
            while (window.isOpen())
            {
                
                Classic.setTexture(t_mod1);
                Extended.setTexture(t_mod2);
                
                
                if (IntRect(480, 390, 522, 131).contains(Mouse::getPosition(window))) { Classic.setTexture(t_mod1c); }
                if (IntRect(480, 520, 522, 131).contains(Mouse::getPosition(window))) { Extended.setTexture(t_mod2c); }
                
                Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == Event::Closed)
                    {
                        window.close();
                        exit(EXIT_SUCCESS);
                    }
                }
                
                window.clear();
                
                
                window.draw(Background);
                window.draw(Frame);
                window.draw(Choose);
                button.setPosition(480, 390);
                window.draw(button);
                button.setPosition(480, 520);
                window.draw(button);
                
                window.draw(Classic);
                window.draw(Extended);
                window.draw(MenuButton);
                
                window.display();
                if ((Mouse::isButtonPressed(Mouse::Left))&&(IntRect(480, 390, 522, 131).contains(Mouse::getPosition(window))))
                {
                    //Нажато кнопку "Класичний"
                    BackMusic.stop();
                    ClickSound.play();
                    return 0;
                }
                if ((Mouse::isButtonPressed(Mouse::Left))&&(IntRect(480, 520, 522, 131).contains(Mouse::getPosition(window))))
                {
                    //Нажато кнопку "Розширений"
                    BackMusic.stop();
                    ClickSound.play();
                    return 1;
                }
                
                if ((Mouse::isButtonPressed(Mouse::Left))&&(IntRect(650, 915, 198, 198).contains(Mouse::getPosition(window))))
                {
                    //Нажато кнопку "Home"
                    ClickSound.play();
                    goto main_menu;    //Переходимо в головне меню
                }
            }
        }
        
        if ((Mouse::isButtonPressed(Mouse::Left))&&(IntRect(480, 390, 522, 131).contains(Mouse::getPosition(window))))
        {
            //Нажато кнопку "Рекорд"
            ClickSound.play();
            
            //Зчитує рекорд з файлу
            ifstream file1, file2;
            file1.open("Scores/HighScoreClassic.txt", ios_base::in);
            file2.open("Scores/HighScoreExtended.txt", ios_base::in);
            int HighScore1, HighScore2;
           
            file1>>HighScore1;
            file2>>HighScore2;
            file1.close();
            file2.close();
            
            
            textHScore1.setString(to_string(HighScore1));
            textHScore1.setPosition(WIDTH / 2 - textHScore1.getGlobalBounds().width / 2 + 250, 520);
            textHScore2.setString(to_string(HighScore2));
            textHScore2.setPosition(WIDTH / 2 - textHScore2.getGlobalBounds().width / 2 + 250, 620);
            
            Classic.setTexture(t_mod1);
            Extended.setTexture(t_mod2);
            YourHScore.setPosition(400, 350);
            Classic.setPosition(400, 500);
            Extended.setPosition(400, 600);
            MenuButton.setPosition(650, 915);
            
            while (window.isOpen())
            {
                Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == Event::Closed)
                    {
                        window.close();
                        exit(EXIT_SUCCESS);
                    }
                }
                
                window.clear();
                window.draw(Background);
                
                window.draw(Frame);
                window.draw(YourHScore);
                window.draw(Classic);
                window.draw(textHScore1);
                window.draw(Extended);
                window.draw(textHScore2);
                window.draw(MenuButton);

                window.display();
                
                 if ((Mouse::isButtonPressed(Mouse::Left))&&(IntRect(650, 915, 198, 198).contains(Mouse::getPosition(window))))
                 {
                     //Нажато кнопку "Home"
                     ClickSound.play();
                     goto main_menu;    //Переходимо в головне меню
                 }
            }
        }
        
        if ((Mouse::isButtonPressed(Mouse::Left))&&(IntRect(480, 520, 522, 131).contains(Mouse::getPosition(window))))
        {
            //Нажато кнопку "Інфо"
            ClickSound.play();
            About.setPosition(10, 200);
            
            MenuButton.setPosition(650, 915);
            while (window.isOpen())
            {
                Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == Event::Closed)
                    {
                        window.close();
                        exit(EXIT_SUCCESS);
                    }
                }
                
                window.clear();
                window.draw(Background);
                window.draw(About);
                window.draw(MenuButton);
                window.display();
                
                if ((Mouse::isButtonPressed(Mouse::Left))&&(IntRect(650, 915, 198, 198).contains(Mouse::getPosition(window))))
                {
                    //Нажато кнопку "Home"
                    ClickSound.play();
                    goto main_menu;   //Переходимо в головне меню
                }
            }
        }
        
        if ((Mouse::isButtonPressed(Mouse::Left))&&(IntRect(480, 650, 522, 131).contains(Mouse::getPosition(window))))
        {
            //Нажато кнопку "Вихід"
            window.close();
            exit(EXIT_SUCCESS);
            //Закриваємо вікно, виходимо з програми
        }
        
        
        window.clear();
        
        //Малюємо спрайти
        window.draw(Background);
        button.setPosition(480, 260);
        window.draw(button);
        button.setPosition(480, 390);
        window.draw(button);
        button.setPosition(480, 520);
        window.draw(button);
        button.setPosition(480, 650);
        window.draw(button);
        
        window.draw(NewGame);
        window.draw(HighScores);
        window.draw(Info);
        window.draw(Exit);
        window.draw(Frame);
        window.display();
    }
    return -1;
}

void Menu::DrawScore(RenderWindow& window)
{
    InGameScore.setString("Score: " + to_string(score));
    window.draw(InGameScore);
}



void Menu::ShowGameOver(RenderWindow& window, const bool& mode)
{
    GameOverSound.play();
    
    //Зчитуємо поточний рекорд з файлу
    int current_high_score;
    
    ifstream ifile;
    
    if (mode)
      { ifile.open("Scores/HighScoreExtended.txt", ios_base::in); }
    else
      { ifile.open("Scores/HighScoreClassic.txt", ios_base::in); }
   
    ifile >> current_high_score;
    ifile.close();
    
    //Якщо рахунок більший за рекорд, то встановлюємо рахунок новим рекордом
    if (score > current_high_score)
    {
        ofstream ofile;
        if (mode)
          { ofile.open("Scores/HighScoreExtended.txt", ios_base::trunc); }
        else
          { ofile.open("Scores/HighScoreClassic.txt", ios_base::trunc); }
        
        ofile<<score;
        ofile.close();
        
        ScoreMessage.setString("New high score: " + to_string(score));
    }
    else
        ScoreMessage.setString("Score: " + to_string(score));
    
 
    
    GameOver.setPosition(WIDTH / 2 - GameOver.getGlobalBounds().width / 2, 80);
    ScoreMessage.setPosition(WIDTH / 2 - ScoreMessage.getGlobalBounds().width / 2, 400);
    RestartButton.setPosition(486, 820);
    MenuButton.setPosition(786, 820);

    window.draw(RestartButton);
    window.draw(MenuButton);
    window.draw(GameOver);
    window.draw(ScoreMessage);

        window.display();
}


///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


#endif /* Menu_h */
