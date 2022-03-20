#ifndef Fruit_h
#define Fruit_h

/////////////////////////////////////////////////////////
/*                 КЛАС ФРУКТ                         */
////////////////////////////////////////////////////////

//using namespace sf;

class Fruit {
    
protected:
    Sprite picture;
    Texture texture;
    short x, y;
public:
    
    Fruit();
    virtual ~Fruit();
    
    virtual void setStartParameters();         //Ініціалізація початкових параметрів
    virtual void Generate(const Part*, const int&);     //Генерація координат
    bool IsNear (Part*) const;         //Перевірка чи фрукт знаходиться поряд з головою змії
    void Draw(RenderWindow&);
    
    int getX() const;
    int getY() const;
};
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////
/*                     РЕАЛІЗАЦІЯ                       */
//////////////////////////////////////////////////////////


Fruit::Fruit()
{
    setStartParameters();
    texture.loadFromFile("Images/Fruit.png");
    picture.setTexture(texture);
}

Fruit::~Fruit()
{
}

void Fruit::setStartParameters()
{
    //Початкові координати
    x = 10;
    y = 5;
}


void Fruit::Generate(const Part* snake_body, const int& n)
{
generate_again:
    x =  rand() % (N - 1) + 1;
    y =  rand() % (M - 1) + 1;
    
    //Перевірка чи нові координати не зачіпають змію
    for (int i=1; i<n; ++i)
    {
        if ((x == snake_body[i].x) && (y == snake_body[i].y))
            goto generate_again;
    }
}


bool Fruit::IsNear (Part *b) const
{
    if ( (b[0].x == x-2) && (b[0].y == y) && b[0].direction==RIGHT) return true;
    if ( (b[0].x == x+2) && (b[0].y == y) && b[0].direction==LEFT) return true;
    if ( (b[0].x == x) && (b[0].y == y-2) && b[0].direction==DOWN) return true;
    if ( (b[0].x == x) && (b[0].y == y+2) && b[0].direction==UP) return true;
    
    if ((b[0].x == x-1)&&(b[0].y == y)) return true;
    if ((b[0].x == x+1)&&(b[0].y == y)) return true;
    if ((b[0].x == x)&&(b[0].y == y-1)) return true;
    if ((b[0].x == x)&&(b[0].y == y+1)) return true;
    
    return false;
}

void Fruit::Draw(RenderWindow& window)
{
    picture.setPosition(x*SIZE, y*SIZE);
    window.draw(picture);
}

int Fruit::getX() const
{
    return x;
}

int Fruit::getY() const
{
    return y;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


#endif /* Fruit_h */
