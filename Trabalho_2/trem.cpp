#include "trem.h"
#include <QtCore>
#include <QSemaphore>
#include <QMutex>
#include <QWaitCondition>

QSemaphore cruzamentoCritico1(2), cruzamentoCritico2(2), cruzamentoCritico3(2);
QSemaphore deadLock1(3), deadlock2(3), deadlock3(4);
QMutex mutexRegiao1, mutexRegiao2,mutexRegiao3, mutexRegiao4, mutexRegiao5, mutexRegiao6, mutexRegiao7;
QWaitCondition waitRegiao1, waitRegiao2, waitRegiao3, waitRegiao4, waitRegiao5, waitRegiao6, waitRegiao7;

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
                    if(x==310 && y==30){
                        deadlock3.tryAcquire(1);
                        while(deadlock3.available() == 0);

                        deadLock1.tryAcquire(1);
                        while(deadLock1.available() == 0);

                        cruzamentoCritico1.tryAcquire(1);
                        while(cruzamentoCritico1.available() == 0);

                        mutexRegiao1.lock();
                    }

                    if(x==310 && y==150){
                        deadlock3.release(1);
                        deadLock1.release(1);
                        cruzamentoCritico1.release(1);
                        waitRegiao1.wakeOne();
                        mutexRegiao1.unlock();
                    }

                    if(x==330 && y==130){
                        mutexRegiao3.lock();
                    }

                    if(x==160 && y==150){
                        waitRegiao3.wakeAll();
                        mutexRegiao3.unlock();
                    }

                    if (y == 30 && x < 330){
                        x+=10;
                    }
                    else if (x == 330 && y < 150){
                        y+=10;
                    }
                    else if (x > 60 && y == 150){
                        x-=10;
                    }
                    else{
                        y-=10;
                    }
                    emit updateGUI(ID,x,y);    //Emite um sinal
                    break;


                case 2: //Trem 2
                    if(x==350 && y==30){
                        waitRegiao1.wakeAll();
                        mutexRegiao1.unlock();
                    }

                    if(x==350 && y==150){
                        mutexRegiao1.lock();
                    }

                    if(x==580 && y==30){
                        deadlock3.tryAcquire(1);
                        while(deadlock3.available() == 0);

                        deadlock2.tryAcquire(1);
                        while(deadlock2.available() == 0);

                        cruzamentoCritico2.tryAcquire(1);
                        while(cruzamentoCritico2.available() == 0);

                        mutexRegiao2.lock();
                    }

                    if(x==450 && y==150){
                        deadlock3.release(1);
                        deadlock2.release(1);
                        cruzamentoCritico2.release(1);
                        waitRegiao2.wakeAll();
                        mutexRegiao2.unlock();
                    }

                    if(x==600 && y==130){
                        deadLock1.tryAcquire(1);
                        while(deadLock1.available() == 0);

                        cruzamentoCritico3.tryAcquire(1);
                        while(cruzamentoCritico3.available() == 0);

                        mutexRegiao5.lock();
                    }

                    if(x == 430 && y == 150){
                        deadLock1.release(1);
                        cruzamentoCritico3.release(1);
                        waitRegiao5.wakeAll();
                        mutexRegiao5.unlock();
                    }

                    if(x==500 && y==150){
                        cruzamentoCritico1.tryAcquire(1);
                        while(cruzamentoCritico1.available() == 0);

                        mutexRegiao4.lock();
                    }

                    if(x==330 && y==130){
                        waitRegiao4.wakeAll();
                        mutexRegiao4.unlock();
                    }

                    if(x==500 && y==30){
                        cruzamentoCritico1.release(1);
                    }

                    if (y == 30 && x < 600){
                        x+=10;
                    }
                    else if (x == 600 && y < 150){
                        y+=10;
                    }
                    else if (x > 330 && y == 150){
                        x-=10;
                    }
                    else{
                        y-=10;
                    }
                    emit updateGUI(ID,x,y);    //Emite um sinal
                    break;


                case 3: //Trem 3
                    if(x==620 && y==150){
                        mutexRegiao2.lock();
                    }

                    if(x==620 && y==30){
                        waitRegiao2.wakeAll();
                        mutexRegiao2.unlock();
                    }

                    if(x==770 && y==150){
                        deadlock3.tryAcquire(1);
                        while(deadlock3.available() == 0);

                        deadlock2.tryAcquire(1);
                        while(deadlock2.available() == 0);

                        cruzamentoCritico2.tryAcquire(1);
                        while(cruzamentoCritico2.available() == 0);

                        mutexRegiao6.lock();
                    }

                    if(x==600 && y==130){
                        deadlock3.release(1);
                        deadlock2.release(1);
                        cruzamentoCritico2.release(1);
                        waitRegiao6.wakeAll();
                        mutexRegiao6.unlock();
                    }

                    if (y == 30 && x < 870){
                        x+=10;
                    }
                    else if (x == 870 && y < 150){
                        y+=10;
                    }
                    else if (x > 600 && y == 150){
                        x-=10;
                    }
                    else{
                        y-=10;
                    }
                    emit updateGUI(ID, x,y);    //Emite um sinal
                    break;


                case 4: //Trem 4
                    if(x==445 && y==150){
                        mutexRegiao7.lock();
                    }

                    if(x==445 && y==270){
                        waitRegiao7.wakeAll();
                        mutexRegiao7.unlock();
                    }

                    if(x==305 && y==150){
                        deadlock2.tryAcquire(1);
                        while(deadlock2.available() == 0);

                        cruzamentoCritico3.tryAcquire(1);
                        while(cruzamentoCritico3.available() == 0);

                        mutexRegiao4.lock();

                    }

                    if(x==475 && y==170){
                        deadlock2.release(1);
                        cruzamentoCritico3.release(1);
                        waitRegiao4.wakeAll();
                        mutexRegiao4.unlock();
                    }

                    if(x==205 && y==170){
                        deadlock3.tryAcquire(1);
                        while(deadlock3.available() == 0);

                        deadLock1.tryAcquire(1);
                        while(deadLock1.available() == 0);

                        cruzamentoCritico1.tryAcquire(1);
                        while(cruzamentoCritico1.available() == 0);

                        mutexRegiao3.lock();

                    }

                    if(x==355 && y==150){
                        waitRegiao3.wakeAll();
                        mutexRegiao3.unlock();
                    }

                    if(x==475 && y==170){
                        deadlock3.release(1);
                        deadLock1.release(1);
                        cruzamentoCritico1.release(1);
                    }

                    if (y == 150 && x < 475){
                        x+=10;
                    }
                    else if (x >= 475 && y < 270){
                        y+=10;
                    }
                    else if (x > 205 && y == 270){
                        x-=10;
                    }
                    else{
                        y-=10;
                    }
                    emit updateGUI(ID, x,y);    //Emite um sinal
                    break;


                case 5: //Trem 5
                    if(x==495 && y==270){
                        deadlock3.tryAcquire(1);
                        while(deadlock3.available() == 0);

                        deadlock2.tryAcquire(1);
                        while(deadlock2.available() == 0);

                        deadLock1.tryAcquire(1);
                        while(deadLock1.available() == 0);

                        cruzamentoCritico3.tryAcquire(1);
                        while(cruzamentoCritico3.available() == 0);
                        mutexRegiao7.lock();
                    }

                    if(x==505 && y==150){
                        deadlock3.release(1);
                        deadlock2.release(1);
                        deadLock1.release(1);
                        cruzamentoCritico3.release(1);
                        waitRegiao7.wakeAll();
                        mutexRegiao7.unlock();
                    }

                    if(x==575 && y==150){
                        mutexRegiao6.lock();
                    }

                    if(x==745 && y==170){
                        waitRegiao6.wakeAll();
                        mutexRegiao6.unlock();
                    }

                    if(x==475 && y==170){
                        cruzamentoCritico2.tryAcquire(1);
                        while(cruzamentoCritico2.available() == 0);
                        mutexRegiao5.lock();
                    }

                    if(x==625 && y==150){
                        cruzamentoCritico2.release(1);
                        waitRegiao5.wakeAll();
                        mutexRegiao5.unlock();
                    }

                    if (y == 150 && x < 745){
                        x+=10;
                    }
                    else if (x == 745 && y < 270){
                        y+=10;
                    }
                    else if (x > 475 && y == 270){
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



