/*!
 * \author Allen Higgins
 * \version 1.0.0
 * \copyright GNU Public Licence
 * \mainpage Lab4 reusable barrier
 * \section  using Semaphore class create a programe that demonstrates a reusable barrier
 *
 *
 * bug = deadlock after passing first barrier? one thread can loop back up quickly and enter first part before waiting for all threads? also, one thread can enter second part before waiting for all threads? suspect barrier(s) as problem?
 */

#include "Semaphore.h"
#include <iostream>
#include <thread>

/*< initialize count */
int count = 0;
/*< initialize the number of threads used in the programe*/
int numOfThreads = 3;

/*! 
 * \breif loop threads
 * \param Semaphore mutex
 * \param Semaphore barrier
 * \param Semaphore barrier
 * \details three thread do some work on a section of code, wait until all threads are done before moving on to the next section of work
 */
void doSomeThing(std::shared_ptr<Semaphore> mutex,std::shared_ptr<Semaphore> barrierA,std::shared_ptr<Semaphore> barrierB){

  while(true){
    
    mutex->Wait();
    count++;
    std::cout << "Do Something frist part " << " ThreadID: " << std::this_thread::get_id() << " count = " << count << std::endl;
    if(count == numOfThreads){
      barrierB->Wait();
      barrierA->Signal();
      std::cout << "barrier B now open --- barrier A closed ---" << std::endl;
    }
    mutex->Signal();

    /*< wait at second barrier for all threads*/
    barrierA->Signal();
    barrierB->Wait();
    
    mutex->Wait();
    count--;
    std::cout << "Do Something second part " << " ThreadID: " << std::this_thread::get_id() << " Count = " << count << std::endl;
    if(count == 0){
      barrierA->Wait();
      barrierB->Signal();
      std::cout << "barrier A now open --- barrier B closed ---" << std::endl;
    }

    /*< wait at the frist barrier for all threads */
    barrierA->Signal();
    barrierB->Wait();
   
  }//end of while
}//end of doSomeThing function


int main(void){

  /*< create three threads */
  std::thread threadOne, threadTwo, threadThree;
  /*< create one semaphore for the mutex */
  std::shared_ptr<Semaphore> mutex( new Semaphore(1) );
  /*< create a semoaphone for a barrierA */
  std::shared_ptr<Semaphore> barrierA( new Semaphore);
  /*< create a semphore for a barrierB */
  std::shared_ptr<Semaphore> barrierB( new Semaphore(1));
  
  /**< Launch the threads  */
  threadOne=std::thread(doSomeThing,mutex,barrierA,barrierB);
  threadTwo=std::thread(doSomeThing,mutex,barrierA,barrierB);
  threadThree=std::thread(doSomeThing,mutex,barrierA,barrierB);

  /*!< threads fork rejoins main thread*/
  threadOne.join();
  threadTwo.join();
  threadThree.join();

  return 0;
}

