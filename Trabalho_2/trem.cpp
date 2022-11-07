#include "trem.h"
#include <QtCore>
#include <QSemaphore>
#include <QMutex>
#include <QWaitCondition>

QSemaphore cruzamento1(2), cruzamento2(2), cruzamento3(2);
QSemaphore deadlock1(3), deadlock2(3), deadlock3(4);
QMutex mutex1, mutex2,mutex3, mutex4, mutex5, mutex6, mutex7;
QWaitCondition wait1, wait2, wait3, wait4, wait5, wait6, wait7;

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
}
/*
                =====================================================================
                | |                              | |                              | |
                | |                              | |                              | |
                | |              T1              |0|              T2              | |
                | |                              | |                              | |
                | |                              | |                              | |
==================--1--================--2--============--3--============--4--========================
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
                        deadlock3.tryAcquire(1);
                        while(deadlock3.available() == 0);

                        deadlock2.tryAcquire(1);
                        while(deadlock2.available() == 0);

                        deadlock1.tryAcquire(1);
                        while(deadlock1.available() == 0);

                        cruzamento3.tryAcquire(1);
                        while(cruzamento3.available() == 0);
                        mutex7.lock();
                    }

                    if(x==450 && y==160){ // depois regiao0
                        deadlock3.release(1);
                        deadlock2.release(1);
                        deadlock1.release(1);
                        cruzamento3.release(1);
                        wait7.wakeAll();
                        mutex7.unlock();
                    }

                    if(x==340 && y==160){ // antes regiao1
                        mutex6.lock();
                    }

                    if(x==200 && y==140){ // depois regiao1
                        wait6.wakeAll();
                        mutex6.unlock();
                    }

                    if(x==470 && y==140){ // antes regiao2
                        cruzamento2.tryAcquire(1);
                        while(cruzamento2.available() == 0);
                        mutex5.lock();
                    }

                    if(x==300 && y==160){ // depois regiao2
                        cruzamento2.release(1);
                        wait5.wakeAll();
                        mutex5.unlock();
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
                        deadlock3.tryAcquire(1);
                        while(deadlock3.available() == 0);

                        deadlock1.tryAcquire(1);
                        while(deadlock1.available() == 0);

                        cruzamento1.tryAcquire(1);
                        while(cruzamento1.available() == 0);

                        mutex3.lock();
                    }

                    if(x==570 && y==160){ // depois regiao4
                        wait3.wakeAll();
                        mutex3.unlock();
                    }

                    if(x==610 && y==160){ // antes regiao3
                        deadlock2.tryAcquire(1);
                        while(deadlock2.available() == 0);

                        cruzamento3.tryAcquire(1);
                        while(cruzamento3.available() == 0);

                        mutex4.lock();
                    }

                    if(x==470 && y==130){ //depois regiao3
                        deadlock3.release(1);
                        deadlock2.release(1);
                        deadlock1.release(1);
                        cruzamento1.release(1);
                        cruzamento3.release(1);
                        wait4.wakeAll();
                        mutex4.unlock();
                    }

                    if(x==490 && y==160){ // antes regiao0
                        mutex7.lock();
                    }

                    if(x == 490 && y == 20){ // depois regiao0
                        wait7.wakeAll();
                        mutex7.unlock();
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
                        mutex2.lock();
                    }

                    if(x==300 && y==280){// depois regiao5
                        wait2.wakeAll();
                        mutex2.unlock();
                    }

                    if(x==180 && y==160){ // antes regiao1
                        deadlock3.tryAcquire(1);
                        while(deadlock3.available() == 0);

                        deadlock2.tryAcquire(1);
                        while(deadlock2.available() == 0);

                        cruzamento2.tryAcquire(1);
                        while(cruzamento2.available() == 0);

                        mutex6.lock();
                    }

                    if(x==320 && y==180){ // depois regiao1
                        deadlock3.release(1);
                        deadlock2.release(1);
                        cruzamento2.release(1);
                        wait6.wakeAll();
                        mutex6.unlock();
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
                        deadlock1.tryAcquire(1);
                        while(deadlock1.available() == 0);

                        cruzamento3.tryAcquire(1);
                        while(cruzamento3.available() == 0);

                        mutex5.lock();
                    }

                    if(x==490 && y==160){ // depois regiao2
                        deadlock1.release(1);
                        cruzamento3.release(1);
                        wait5.wakeAll();
                        mutex5.unlock();
                    }

                    if(x==450 && y==160){ // antes regiao3
                        cruzamento1.tryAcquire(1);
                        while(cruzamento1.available() == 0);

                        mutex4.lock();
                    }

                    if(x==590 && y==180){ // depois regiao3
                        wait4.wakeAll();
                        mutex4.unlock();
                    }

                    if(x==570 && y==160){ // antes regiao6
                        mutex1.lock();
                    }

                    if(x==570 && y==280){ // depois regiao6
                        wait1.wakeAll();
                        mutex1.unlock();
                    }

                    if(x==340 && y==280){ // antes regiao5
                        deadlock3.tryAcquire(1);
                        while(deadlock3.available() == 0);

                        deadlock2.tryAcquire(1);
                        while(deadlock2.available() == 0);

                        cruzamento2.tryAcquire(1);
                        while(cruzamento2.available() == 0);

                        mutex2.lock();
                    }

                    if(x==550 && y==280){ // depois regiao5
                        cruzamento1.release(1);
                    }

                    if(x==490 && y==160){
                        deadlock3.release(1);
                        deadlock2.release(1);
                        cruzamento2.release(1);
                        wait2.wakeAll();
                        mutex2.unlock();
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
                        mutex3.lock();
                    }

                    if(x==760 && y==160){ // depois regiao4
                        wait3.wakeAll();
                        mutex3.unlock();
                    }

                    if(x==610 && y==280){ // antes regiao6
                        deadlock3.tryAcquire(1);
                        while(deadlock3.available() == 0);

                        deadlock1.tryAcquire(1);
                        while(deadlock1.available() == 0);

                        cruzamento1.tryAcquire(1);
                        while(cruzamento1.available() == 0);

                        mutex1.lock();
                    }

                    if(x==610 && y==160){ // depois regiao6
                        deadlock3.release(1);
                        deadlock1.release(1);
                        cruzamento1.release(1);
                        wait1.wakeOne();
                        mutex1.unlock();
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



