/*!
 * \author Allen Higgins
 * \version 1.0.0
 * \copyright GNU Public Licence
 * \mainpage Lab2 Rendezvous
 * \section create a rendezvous pattern useing semaphores
 */

#include "Semaphore.h"
#include <iostream>
#include <thread>

/*!
 * \brief print twice
 * \param theSem is a shared pointer for a semaphore
 * \param theSem2 is a shared pointer for a semaphore
 * \details print part 1 then signal before waiting for taskTwo then print part 2
 */
void taskOne(std::shared_ptr<Semaphore> theSem1,
	     std::shared_ptr<Semaphore> theSem2){
  std::cout << "Task 1 first print " << std::endl;
  theSem1->Signal();
  theSem2->Wait();
  std::cout << "Task 1 second print " << std::endl;
}

/*!
 * \brief print twice
 * \param theSem is a shared pointer for a semaphore
 * \param theSem2 is a shared pointer for a semaphore
 * \details print part 1 then signal before waiting for taskOne then print part 2
 */
void taskTwo(std::shared_ptr<Semaphore> theSem1,
	     std::shared_ptr<Semaphore> theSem2){
  std::cout << "Task 2 first print " << std::endl;
  theSem2->Signal();
  theSem1->Wait();
  std::cout << "Task 2 second print " << std::endl;
}

int main(void){
  
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore);
  std::shared_ptr<Semaphore> sem2(new Semaphore);

  /**< Launch the threads  */
  threadOne=std::thread(taskTwo,sem,sem2);
  threadTwo=std::thread(taskOne,sem,sem2);

  /*!< threads fork rejoins main thread*/
  threadOne.join();
  threadTwo.join();

  return 0;
}

