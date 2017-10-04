/*!
 * \author Allen Higgins
 * \version 1.0.0
 * \copyright GNU Public Licence
 * \mainpage Signal Lab2
 * \section Two threads with Semaphores that signal one thread to proceed and one Thread to wait their turn 
 */

#include "Semaphore.h"
#include <iostream>
#include <thread>


void taskOne(std::shared_ptr<Semaphore> theSemaphore){
  std::cout <<"I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first" << std::endl;
  theSemaphore->Signal();
}

void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  theSemaphore->Wait();
  std::cout << "This ";
  std::cout << "will ";
  std::cout << "appear ";
  std::cout << "second" << std::endl;
}

int main(void){
  
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore);

  /**< Launch the threads  */
  threadOne=std::thread(taskTwo,sem);
  threadTwo=std::thread(taskOne,sem);

  
  threadOne.join();
  threadTwo.join();

  return 0;
}

