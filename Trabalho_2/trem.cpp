#include "trem.h"
#include <QtCore>
#include <QSemaphore>
#include <QMutex>
#include <QWaitCondition>

QMutex mutex[7];
QSemaphore sem[3], sem2[2];

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
}

void Trem::inicializa_semaforos(){

    sem[0].release(2); //SEMAFORO QUE CONTROLA O CRUZAMENTO A
    sem[1].release(2); //SEMAFORO QUE CONTROLA O CRUZAMENTO B
    sem[2].release(2); //SEMAFORO QUE CONTROLA O CRUZAMENTO C

    sem2[0].release(3);//SEMAFORO QUE CONTROLA O CRUZAMENTO AB
    sem2[1].release(3);//SEMAFORO QUE CONTROLA O CRUZAMENTO BC

}
/*
                =====================================================================
                | |                              | |                              | |
                | |                              | |                              | |
                | |              T1              |0|              T2              | |
                | |                              | |                              | |
                | |                              | |                              | |
==================--1--===========A=====--2--=====B=======--3--====C========--4--=====================
| |                              | |                              | |                              | |
| |                              | |                              | |                              | |
| |             T3               |5|             T4               |6|             T5               | |
| |                              | |                              | |                              | |
| |                              | |                              | |                              | |
======================================================================================================
*/

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
                    if(x==450 && y==20){ // antes regiao0
                        sem2[1].acquire(3);
                        sem[1].acquire(2);
                        mutex[0].lock();
                    }

                    if(x==450 && y==160){ // depois regiao0
                        sem2[1].release(1);
                        sem[1].release(1);
                        mutex[0].unlock();
                    }

                    if(x==340 && y==160){ // antes regiao1
                        mutex[1].lock();
                    }

                    if(x==200 && y==140){ // depois regiao1
                        sem2[1].release(1);
                        sem[2].release(1);
                        mutex[1].unlock();
                    }

                    if(x==470 && y==140){ // antes regiao2
                        sem[2].acquire(2);
                        mutex[2].lock();
                    }

                    if(x==300 && y==160){ // depois regiao2
                        sem2[1].release(1);
                        sem[1].release(1);
                        sem[2].release(1);
                        mutex[2].unlock();
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
                    if(x==740 && y==140){ // antes regiao4
                        sem2[1].acquire(2);
                        sem2[0].acquire(3);
                        sem[0].acquire(2);
                        mutex[4].lock();
                    }

                    if(x==570 && y==160){ // depois regiao4
                        sem2[0].release(1);
                        sem[0].release(1);
                        mutex[4].unlock();
                    }

                    if(x==610 && y==160){ // antes regiao3
                        sem[1].acquire(2);
                        mutex[3].lock();
                    }

                    if(x==470 && y==140){ //depois regiao3
                        sem2[1].release(1);
                        sem2[0].release(1);
                        sem[0].release(1);
                        sem[1].release(1);
                        mutex[3].unlock();
                    }

                    if(x==490 && y==160){ // antes regiao0
                        mutex[0].lock();
                    }

                    if(x == 490 && y == 20){ // depois regiao0
                        sem2[1].release(1);
                        sem2[0].release(1);
                        sem[1].release(1);
                        mutex[0].unlock();
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
                    if(x==300 && y==160){ // antes regiao5
                        mutex[5].lock();
                    }

                    if(x==300 && y==280){// depois regiao5
                        sem2[1].release(1);
                        sem[2].release(1);
                        mutex[5].unlock();
                    }

                    if(x==180 && y==160){ // antes regiao1
                        sem2[1].acquire(2);
                        sem[2].acquire(2);
                        mutex[1].lock();
                    }

                    if(x==320 && y==180){ // depois regiao1
                        sem2[1].release(1);
                        sem[2].release(1);
                        mutex[1].unlock();
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
                    if(x==320 && y==180){ // antes regiao2
                        sem2[0].acquire(3);
                        sem[1].acquire(2);
                        mutex[2].lock();
                    }

                    if(x==490 && y==160){ // depois regiao2
                        sem2[1].release(1);
                        sem2[0].release(1);
                        sem[2].release(1);
                        sem[1].release(1);
                        mutex[2].unlock();
                    }

                    if(x==450 && y==160){ // antes regiao3
                        sem[0].acquire(2);
                        mutex[3].lock();
                    }

                    if(x==590 && y==180){ // depois regiao3
                        sem2[1].release(1);
                        sem2[0].release(1);
                        sem[1].release(1);
                        sem[0].release(1);
                        mutex[3].unlock();
                    }

                    if(x==570 && y==160){ // antes regiao6
                        mutex[6].lock();
                    }

                    if(x==570 && y==280){ // depois regiao6
                        sem2[0].release(1);
                        sem[0].release(1);
                        mutex[6].unlock();
                    }

                    if(x==340 && y==280){ // antes regiao5
                        sem2[1].acquire(3);
                        sem[2].acquire(2);
                        mutex[5].lock();
                    }

                    if(x==340 && y==160){ // depois regiao5
                        sem2[1].release(1);
                        sem[2].release(1);
                        mutex[5].unlock();
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
                    if(x==590 && y==180){ // antes regiao4
                        mutex[4].lock();
                    }

                    if(x==760 && y==160){ // depois regiao4
                        sem2[0].release(1);
                        sem[0].release(1);
                        mutex[4].unlock();
                    }

                    if(x==610 && y==280){ // antes regiao6
                       sem2[0].acquire(2);
                       sem[0].acquire(2);
                       mutex[6].lock();
                    }

                    if(x==610 && y==160){ // depois regiao6
                        sem2[0].release(1);
                        sem[0].release(1);
                        mutex[6].unlock();
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
