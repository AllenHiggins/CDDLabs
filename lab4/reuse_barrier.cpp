/*!
 * \author Allen Higgins
 * \version 1.0.0
 * \copyright GNU Public Licence
 * \mainpage Lab4 reusable barrier
 * \section  using Semaphore class create a programe that demonstrates a reusable barrier
 *
 *
 *
 */

#include "Semaphore.h"
#include <iostream>
#include <thread>


/*< initialize the number of threads used in the programe*/
int numOfThreads = 3;

/*! 
 * \breif loop threads
 * \param Semaphore mutex
 * \param Semaphore barrier
 * \param Semaphore barrier
 * \details three thread do some work on a section of code, wait until all threads are done before moving on to the next section of work
 */
void doSomeThing(std::shared_ptr<Semaphore> mutex,std::shared_ptr<Semaphore> barrier1,std::shared_ptr<Semaphore> barrier2, int *count){
  
    mutex->Wait();
    *count += 1;
    std::cout << "function doSomething start " <<  *count << std::endl;
    if(*count == 3){
       std::cout << "---------->>>>>  " <<  *count << std::endl;
      barrier1->Signal();
    }
    mutex->Signal();
    barrier1->Wait();
    barrier1->Signal();

    
    mutex->Wait();
    *count -= 1;
    std::cout << "function doSomething end " <<  *count << std::endl;
    if(*count == 0){
      std::cout << "---------->>>>>  " <<  *count << std::endl;
      barrier2->Signal();
    }
    mutex->Signal();
    barrier2->Wait();
    barrier2->Signal();
}


int main(void){

  int count = 0;
  
  /*< create three threads */
  std::thread threadOne, threadTwo, threadThree;
  /*< create one semaphore for the mutex */
  std::shared_ptr<Semaphore> mutex( new Semaphore(1));
  std::shared_ptr<Semaphore> barrier1( new Semaphore(0));
  std::shared_ptr<Semaphore> barrier2( new Semaphore(1));

  std::cout << "Main Started " << std::endl;
  
  /**< Launch the threads  */
  threadOne=std::thread(doSomeThing,mutex,barrier1,barrier2,&count);
  threadTwo=std::thread(doSomeThing,mutex,barrier1,barrier2,&count);
  threadThree=std::thread(doSomeThing,mutex,barrier1,barrier2,&count);

  /*!< threads fork rejoins main thread*/
  threadOne.join();
  threadTwo.join();
  threadThree.join();

  return 0;
}

