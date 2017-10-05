/*!
 * \author Allen Higgins
 * \version 1.0.0
 * \copyright GNU Public Licence
 * \mainpage Lab3 Mutual Exclusion
 * \section  using Semaphore class create a programe that demonstrates Mutual Exclusion
 */

#include "Semaphore.h"
#include <iostream>
#include <thread>

static int num = 0;

/*!
 * \brief add One to current count
 * \param theSem is a shared pointer for a semaphore
 * \param int num
 * \details Add one to shared int num and print out the result using semaphore as mutex lock for critical section
 *  also print out the thread ID
 */
void addOne(std::shared_ptr<Semaphore> mutex){
  mutex->Wait();
  num++;
  std::cout << "count equals: " <<  num << " ThreadID: " << std::this_thread::get_id() << std::endl;
  mutex->Signal();
 
}


int main(void){

  /*< create three threads*/
  std::thread threadOne, threadTwo, threadThree;
  /*< create one semaphore for the mutex*/
  std::shared_ptr<Semaphore> sem( new Semaphore);
  
  
  /**< Launch the threads  */
  threadOne=std::thread(addOne,sem);
  threadTwo=std::thread(addOne,sem);
  threadThree=std::thread(addOne,sem);

  /*!< threads fork rejoins main thread*/
  threadOne.join();
  threadTwo.join();
  threadThree.join();

  return 0;
}

