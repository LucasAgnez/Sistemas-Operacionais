#include "trem.h"
#include <QtCore>
#include <QSemaphore>
#include <QMutex>
#include <QWaitCondition>

QSemaphore deadlock0(3), deadlock1(3), deadlock2(3), deadlock3(4), deadLock4(3), deadlock5(3), deadlock6(4);
QMutex mutex_regiao0, mutex_regiao1, mutex_regiao2, mutex_regiao3, mutex_regiao4, mutex_regiao5, mutex_regiao6;
QWaitCondition wait_regiao0, wait_regiao1, wait_regiao2, wait_regiao3, wait_regiao4, wait_regiao5, wait_regiao6;

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        if (velocidade == 200){
            emit updateGUI(ID, x,y);    //Emite um sinal
            msleep(1000);
        }
        else{
            switch(ID){
                case 1:     //Trem 1
                    if(x==450 && y==20){ //

                    }

                    if(x==450 && y==160){

                    }

                    if(x==340 && y==160){ //

                    }

                    if(x==200 && y==140){

                    }

                    if(x==470 && y==140){ //

                    }

                    if(x==300 && y==160){

                    }

                    if (x < 470 && y == 20){ /////////
                        x+=10;
                    }
                    else if (x == 470 && y < 160){
                        y+=10;
                    }
                    else if (x > 200 && y == 160){
                        x-=10;
                    }
                    else{
                        y-=10;
                    }
                    emit updateGUI(ID,x,y);    //Emite um sinal
                    break;


                case 2: //Trem 2
                    if(x==740 && y==140){ //

                    }

                    if(x==570 && y==160){

                    }

                    if(x==610 && y==160){ //

                    }

                    if(x==570 && y==160){

                    }

                    if(x==490 && y==160){ //

                    }

                    if(x == 470 && y == 140){

                    }

                    if (x < 740 && y == 20){ /////////////
                        x+=10;
                    }
                    else if (x == 740 && y < 160){
                        y+=10;
                    }
                    else if (x > 470 && y == 160){
                        x-=10;
                    }
                    else{
                        y-=10;
                    }
                    emit updateGUI(ID,x,y);    //Emite um sinal
                    break;


                case 3: //Trem 3
                    if(x==300 && y==160){ //

                    }

                    if(x==300 && y==280){

                    }

                    if(x==180 && y==160){ //

                    }

                    if(x==320 && y==180){

                    }

                    if (x < 320 && y == 160){ /////////
                        x+=10;
                    }
                    else if (x == 320 && y < 280){
                        y+=10;
                    }
                    else if (x > 60 && y == 280){
                        x-=10;
                    }
                    else{
                        y-=10;
                    }
                    emit updateGUI(ID, x,y);    //Emite um sinal
                    break;


                case 4: //Trem 4
                    if(x==320 && y==180){ //

                    }

                    if(x==490 && y==160){

                    }

                    if(x==440 && y==160){ //

                    }

                    if(x==590 && y==180){

                    }

                    if(x==570 && y==160){ //

                    }

                    if(x==570 && y==280){

                    }

                    if(x==340 && y==280){ //

                    }

                    if(x==340 && y==160){

                    }

                    if (x < 590 && y == 160){ ///////////
                        x+=10;
                    }
                    else if (x == 590 && y < 280){
                        y+=10;
                    }
                    else if (x > 320 && y == 280){
                        x-=10;
                    }
                    else{
                        y-=10;
                    }
                    emit updateGUI(ID, x,y);    //Emite um sinal
                    break;


                case 5: //Trem 5
                    if(x==590 && y==180){ //

                    }

                    if(x==760 && y==160){

                    }

                    if(x==610 && y==280){ //

                    }

                    if(x==610 && y==160){

                    }

                    if (x < 860 && y == 160){ ////////////
                        x+=10;
                    }
                    else if (x == 860 && y < 280){
                        y+=10;
                    }
                    else if (x > 590 && y == 280){
                        x-=10;
                    }
                    else{
                        y-=10;
                    }
                    emit updateGUI(ID,x,y);    //Emite um sinal
                    break;

                default:
                    break;
            }
            msleep(velocidade);
        }
    }
}

void Trem::set_velocidade(int valor){
    this->velocidade = 200 - valor;
}



