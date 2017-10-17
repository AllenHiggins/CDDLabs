/*!
 * \author Allen Higgins
 * \version 1.0.0
 * \copyright GNU Public Licence
 * \mainpage Lab4 reusable barrier
 * \section  using Semaphore class create a programe that demonstrates a reusable barrier
 *
 *
 * bug = deadlock after passing first barrier?
 */

#include "Semaphore.h"
#include <iostream>
#include <thread>

int count = 0;
int numOfThreads = 3;

/*!
 * \brief add One to current count
 * \param semaphore mutex
 * \param semaphore barrier
 * \param semaphore barrier
 * \details reuse a barrier with three threads
 */


/*! 
 * \breif loop threads
 * \param Semaphore mutex
 * \param Semaphore barrier
 * \param Semaphore barrier
 * \details three thread do some work on a section of code, wait until all threads are done before moving on to the next section of work
 */
void doSomeThing(std::shared_ptr<Semaphore> mutex,std::shared_ptr<Semaphore> barrierA,std::shared_ptr<Semaphore> barrierB){

  while(true){

    std::cout << "Do Something frist part " << " ThreadID: " << std::this_thread::get_id() << std::endl;
    
    mutex->Wait();
    count++;
    if(count == numOfThreads){
      barrierB->Wait();
      barrierA->Signal();
      std::cout << "barrier B now open --- barrier A closed --- thread count = " << count << std::endl;
    }
    mutex->Signal();

    
    barrierA->Wait();
    barrierB->Signal();


    std::cout << "Do Something second part " << " ThreadID: " << std::this_thread::get_id() << std::endl;
    
    mutex->Wait();
    count--;
    if(count == 0){
      barrierA->Wait();
      barrierB->Signal();
      std::cout << "barrier A now open --- barrier B closed --- thread count = " << count << std::endl;
    }
    
    barrierB->Wait();
    barrierB->Signal();
   
  }
 
}


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

