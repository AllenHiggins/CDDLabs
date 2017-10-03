/*!
 * \author Allen Higgins
 * \version 1.0.0
 * \copyright GNU Public Licence
 * \mainpage Signal Lab1
 * \section Two threads with Semaphores that signal one thread to proceed and one Thread to wait their turn 
 */

#include "Semaphore.h"
#include <iostream>
#include <thread>

/*! \breif Start task one */
void taskOne(std::shared_ptr<Semaphore> theSemaphore){
  std::cout << "First Thread to run. Thread two is waiting..." << std::endl;
  theSemaphore->Signal();
}

/*! \breif Start task two */
void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  theSemaphore->Wait();
  std::cout << "Second Thread to run." << std::endl;
}

int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore);

  /**< Launch the threads  */
  threadOne = std::thread(taskTwo,sem);
  threadTwo = std::thread(taskOne,sem);

  std::cout << "Launched from the main\n";

  threadOne.join();
  threadTwo.join();
  
  return 0;
}
