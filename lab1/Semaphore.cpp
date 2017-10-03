#include "Semaphore.h"
/*! 
 * \class Semaphore
 * \brief A Semaphore Implementation
 *
 *  Uses C++11 features such as mutex and condition variables to implement Semaphore
 *
 */


/*! \breif subtract value from Semaphore */
void Semaphore::Wait()
{
      std::unique_lock< std::mutex > lock(m_mutex);
      m_condition.wait(lock,[&]() -> bool {
	  return m_uiCount>0;
      });
      --m_uiCount;
}

/*! \breif adds vaule to Semaphore */
void Semaphore::Signal()
{
      std::unique_lock< std::mutex > lock(m_mutex);
      ++m_uiCount;
      m_condition.notify_one();
}
