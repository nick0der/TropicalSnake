#ifndef BadFruit_h
#define BadFruit_h

////////////////////////////////////////////////////////////
/*     КЛАС БОМБА(ПОГАНИЙ ФРУКТ) - нащадок класу ФРУКТ    */
/*  з переопреділеним методом генерації та ініціалізації  */
////////////////////////////////////////////////////////////

class BadFruit: public Fruit
{
public:
    BadFruit();
    virtual void setStartParameters();
    virtual void Generate(const Part*, const int&);
};
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////







//////////////////////////////////////////////////////////
/*                     РЕАЛІЗАЦІЯ                       */
//////////////////////////////////////////////////////////

BadFruit::BadFruit()
{
    texture.loadFromFile("Images/Bomb.png");
    picture.setTexture(texture);
    setStartParameters();
}

void BadFruit::Generate(const Part* snake_body, const int &n)
{
    
again:
    //Генерація (при цьому іноді пастка виходить за межі поля, тобто зникає)
    x =   rand() % (N + 4);
    y =   rand() % (M + 4);
    
    //Якщо пастка знаходиться на межі, генеруємо ще раз
    if ((x == N)||(x==0)||(y==M)||(y==0))
        goto again;
    
    //Якщо пастка перетинає змію, генеруємо ще раз
    for (int i=1; i<n; ++i)
    {
        if ((x == snake_body[i].x) && (y == snake_body[i].y))
            goto again;
    }
}

void BadFruit::setStartParameters()
{
    x = 99;
}


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


#endif /* BadFruit_h */
