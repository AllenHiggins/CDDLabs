/*!
 * \author Allen Higgins
 * \version 1.0.0
 * \copyright GNU Public Licence
 * \mainpage Lab4 reusable barrier
 * \section  using Semaphore class create a programe that demonstrates a reusable barrier
 */

#include "Semaphore.h"
#include <iostream>
#include <thread>

static int count = 0;

/*!
 * \brief add One to current count
 * \param theSem is a shared pointer for a semaphore
 * \param int num
 * \details Add one to shared int num and print out the result using semaphore as mutex lock for critical section
 *  also print out the thread ID
 */


void doSomeThing(std::shared_ptr<Semaphore> mutex,
		 std::shared_ptr<Semaphore> barrierA,
		 std::shared_ptr<Semaphore> barrierB){

  while(true){

    std::cout << "Do Something frist part " << " ThreadID: " << std::this_thread::get_id() << std::endl
    
    mutex.wait();
    count++;
    if(count == 3){
      barrierB.wait();
      barrierA.signal();
    }
    mutex.signal();

    barrierA.wait();
    barrierB.signal();

    std::cout << "Do Something second part " << " ThreadID: " << std::this_thread::get_id() << std::endl
    
    mutex.wait();
    count--;
    if(count == 0){
      barrierA.wait();
      barrierB.signal();
    }
  
    barrierB.wait();
    barrierB.signal();
  }
 
}


int main(void){

  /*< create three threads */
  std::thread threadOne, threadTwo, threadThree;
  /*< create one semaphore for the mutex */
  std::shared_ptr<Semaphore> mutex( new Semaphore);
  /*< create a semoaphone for a barrierA */
  std::shared_ptr<Semapore> barrierA( new Semaphore);
  /*< create a semphore for a barrierB */
  std::shared_ptr<Semaphore> barrierB( new Semaphore);
  
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

