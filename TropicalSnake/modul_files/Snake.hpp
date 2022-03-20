#ifndef Snake_h
#define Snake_h


/////////////////////////////////////////////////////////
/*                 КЛАС ЗМІЯ                          */
////////////////////////////////////////////////////////

class Snake {
private:
    Texture AllBody;
    int length;
    Texture t_boom;
    Sprite boom;
    bool eatingBomb;
    
    SoundBuffer buffer1, buffer2;
    Sound EatSound, BoomSound;
public:
    
    Part *body;
    Snake();
    virtual ~Snake();
    
    void setStartParameters();              //Встановлення початкових параметрів
    void Press();                           //Зчитування клавіш
    void Move();                            //Рух змії
    void Check(Fruit&);         //Перевірка на зіткнення
    void CheckExtended (Fruit&, BadFruit&);
    void Draw(RenderWindow&, const Fruit&);
    
    int getLength() const;
};
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////









//////////////////////////////////////////////////////////
/*                     РЕАЛІЗАЦІЯ                       */
//////////////////////////////////////////////////////////

Snake::Snake()
{
    body = new Part[N*M];

    setStartParameters();
    
    AllBody.loadFromFile("Images/TEXTURE.png");   //Текстура змії
    t_boom.loadFromFile("Images/Boom.png");      //Текстура вибух
    boom.setTexture(t_boom);
    
    //Звуки поїдання та вибуху
    buffer1.loadFromFile("Sounds/EatSound.wav");
    buffer2.loadFromFile("Sounds/BoomSound.wav");
    EatSound.setBuffer(buffer1);
    BoomSound.setBuffer(buffer2);
}

Snake::~Snake()
{
    delete []body;
}

void Snake::Press()
{
    if ((body[0].direction == LEFT)||(body[0].direction == RIGHT))
    {
        if ((Keyboard::isKeyPressed(Keyboard::Up))||(Keyboard::isKeyPressed(Keyboard::W)))
        { body[0].direction=UP; return; }
        if ((Keyboard::isKeyPressed(Keyboard::Down))||(Keyboard::isKeyPressed(Keyboard::S)))
        { body[0].direction=DOWN; return; }
    }
    else
    {
        if ((Keyboard::isKeyPressed(Keyboard::Right))||(Keyboard::isKeyPressed(Keyboard::D)))
        { body[0].direction=RIGHT; return; }
        if ((Keyboard::isKeyPressed(Keyboard::Left))||(Keyboard::isKeyPressed(Keyboard::A)))
        { body[0].direction=LEFT; return; }
    }
}

void Snake::Move()
{
    eatingBomb = false;
    for (int i = length; i>0; --i)
    {
        body[i].x = body[i-1].x;
        body[i].y = body[i-1].y;
        body[i].picture = body[i-1].picture;
        body[i].direction = body[i-1].direction;
    }
    
    switch (body[0].direction)
    {
       case DOWN:
            body[0].y++; break;
        case LEFT:
            body[0].x--; break;
        case RIGHT:
            body[0].x++; break;
        case UP:
            body[0].y--; break;
    }
}


void Snake::Check(Fruit& f)
{
    //Якщо голова стає на місце фрукта

    if ((body[0].x == f.getX())&&(body[0].y == f.getY()))
    {
        
        EatSound.play();
        length++;
        score = length - 4;    //Збільшуємо довжину
        if (length == 266) return;
        f.Generate(body, length); //Генеруємо фрукт
    }
    //Рахунок дорівнює поточній довжині мінус початкова
    
    
    //Якщо довжина змії = 1, гру закінчено
    if (length==1) gameover = true;
    
    //Перевіряємо зіткнення з полем
    if (body[0].x==N) gameover = true;
    if (body[0].y==M) gameover = true;
    if (body[0].x==0) gameover = true;
    if (body[0].y==0) gameover = true;
    
    //Перевіряємо зіткнення з власним тілом
    for (int i=1; i<length; ++i)
    {
        if ((body[0].x == body[i].x) && (body[0].y == body[i].y))
            gameover = true;
    }
}

void Snake::CheckExtended(Fruit& f, BadFruit& b)
{
    //Якщо голова стає на місце фрукта
    if ((body[0].x == f.getX())&&(body[0].y == f.getY()))
    {
        EatSound.play();
        length++;//Збільшуємо довжину
        f.Generate(body, length); //Генеруємо фрукт
    }
    
    if ((body[0].x == b.getX())&&(body[0].y == b.getY()))
    {
        //Якщо голова стає на місце пастки
        eatingBomb=true;
        BoomSound.play();
        length--;                   //Зменшуємо довжину
        b.Generate(body, length);  //Генеруємо пастку
    }
    //Рахунок дорівнює поточній довжині мінус початкова
    score = length - 4;
    
    //Якщо довжина змії = 1, гру закінчено
    if (length==1) gameover = true;
    
    //Перевіряємо зіткнення з полем
    if (body[0].x==N) gameover = true;
    if (body[0].y==M) gameover = true;
    if (body[0].x==0) gameover = true;
    if (body[0].y==0) gameover = true;
    
    //Перевіряємо зіткнення з власним тілом
    for (int i=1; i<length; ++i)
    {
        if ((body[0].x == body[i].x) && (body[0].y == body[i].y))
            gameover = true;
    }
}

void Snake::Draw(RenderWindow &window, const Fruit& f)
{
    //Малює тіло змії
    for (int i = 2; i < length; ++i)
    {
        body[i].picture.setTexture(AllBody);
        
        //Встановлює горизонтальне або вертикальне положення
        if (body[i].direction == DOWN || body[i].direction == UP)
            body[i].picture.setTextureRect(IntRect(77, 154, 77, 77 ));
        else
            body[i].picture.setTextureRect(IntRect(0, 154, 77, 77 ));
        
        //Встановлює відповідну тексткуру на поворотах
        if ( (body[i-1].direction == RIGHT && body[i].direction == UP) ||
            (body[i-1].direction == DOWN && body[i].direction == LEFT))
            body[i].picture.setTextureRect(IntRect(0, 77, 77, 77 ));
        
        else if ((body[i-1].direction == LEFT && body[i].direction == UP) ||
                 (body[i-1].direction == DOWN && body[i].direction == RIGHT))
            body[i].picture.setTextureRect(IntRect(77, 77, 77, 77 ));
        
        else if ((body[i-1].direction == RIGHT && body[i].direction == DOWN) ||
                 (body[i-1].direction == UP && body[i].direction == LEFT))
            body[i].picture.setTextureRect(IntRect(154, 77, 77, 77 ));
        
        else if ((body[i-1].direction == UP && body[i].direction == RIGHT) ||
                 (body[i-1].direction == LEFT && body[i].direction == DOWN))
            body[i].picture.setTextureRect(IntRect(231, 77, 77, 77 ));
        
        body[i].picture.setPosition(body[i-1].x*SIZE, body[i-1].y*SIZE);
        
        window.draw(body[i].picture);
    }
    body[0].picture.setTexture(AllBody);
    
    
    //Малює голову, відповідно до напрямку
    //При цьому, коли фрукт близько, змія відкриває рот
    switch (body[1].direction)
    {
        case DOWN:
        {
            if (f.IsNear(body))  body[0].picture.setTextureRect(IntRect(385, 0, 77, 77 ));
            else  body[0].picture.setTextureRect(IntRect(77, 0, 77, 77 ));
            break;
        }
            
        case LEFT:
        {
            if (f.IsNear(body))  body[0].picture.setTextureRect(IntRect(308, 0, 77, 77 ));
            else   body[0].picture.setTextureRect(IntRect(0, 0, 77, 77 ));
            break;
        }
            
        case RIGHT:
        {
            if (f.IsNear(body))  body[0].picture.setTextureRect(IntRect(539, 0, 77, 77 ));
            else    body[0].picture.setTextureRect(IntRect(231, 0, 77, 77 ));
            break;
        }
            
        case UP:
        {
            if (f.IsNear(body))  body[0].picture.setTextureRect(IntRect(462, 0, 77, 77 ));
            else   body[0].picture.setTextureRect(IntRect(154, 0, 77, 77 ));
            
            break;
        }
    }
    body[0].picture.setPosition(body[0].x*SIZE, body[0].y*SIZE);
    window.draw(body[0].picture);
    
    //Якщо змія натрапила на бомбу, малюємо вибух
    if (eatingBomb)
    {
         boom.setPosition(body[0].x*SIZE, body[0].y*SIZE);
         window.draw(boom);
    }
    
    //Малює хвіст відповідно до напрямку
    body[length-1].picture.setTexture(AllBody);
    switch (body[length-1].direction) {
        case DOWN:
        {
            body[length-1].picture.setTextureRect(IntRect(385, 77, 77, 77 ));
            break;
        }
            
        case LEFT:
        {
            body[length-1].picture.setTextureRect(IntRect(308, 77, 77, 77 ));
            break;
        }
            
        case RIGHT:
        {
            body[length-1].picture.setTextureRect(IntRect(539, 77, 77, 77 ));
            break;
        }
            
        case UP:
        {
            body[length-1].picture.setTextureRect(IntRect(462, 77, 77, 77 ));
            break;
        }
    }
    body[length-1].picture.setPosition(body[length-1].x*SIZE, body[length-1].y*SIZE);
    window.draw(body[length-1].picture);
}

void Snake::setStartParameters()
{
    body[0].x = 5;  body[0].y = 10;
    body[1].x = 4;  body[1].y = 10;
    body[2].x = 3;  body[2].y = 10;
    body[3].x = 2;  body[3].y = 10;
    
    body[0].direction = RIGHT;
    body[1].direction = RIGHT;
    body[2].direction = RIGHT;
    body[3].direction = RIGHT;
    
    length = 4;
    eatingBomb = false;
}

int Snake::getLength() const
{
    return length;
}


///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


#endif /* Snake_h */
