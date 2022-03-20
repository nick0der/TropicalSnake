#ifndef Utilities_h
#define Utilities_h

const int N=20, M=15;           
const int SIZE=70;
const int WIDTH = N*SIZE + 70;
const int HEIGHT = M*SIZE + 70;
short score = 0;
bool gameover = false;
enum E {DOWN=0, LEFT, RIGHT, UP};


// Структура, що містить дані про частину(клітинку) змії
struct Part
{
    short x, y;      //Координати
    Sprite picture;  //Картинка(текстура)
    E direction;      //Напрям
};
///////////////////////////////////////////////////////



#endif /* Utilities_h */
