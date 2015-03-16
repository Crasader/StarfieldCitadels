#ifndef __SINGLETON_TEMPLATE_H__
#define __SINGLETON_TEMPLATE_H__

/* This template implements is designed to be used as the 
 * base class for a singleton.  
 *
 * The life cycle of objects derived from this class is very 
 * specific:
 * 1. The constructor does NOTHING.
 * 2. The Init() function is called from your application before
 *    using the class.  This is where all the REAL initialization 
 *    is done.  This allows you to control the order that the 
 *    initialization for multiple singletons are executed.
 * 3. Use the singleton...
 * 4. Call Reset() as needed to return it to the ground state.
 *    You may need to call Init() again depending on your needs.
 * 5. Call Shutdown() when you exit the Application to clean 
 *    up.
 *
 * While the implementation in this class is relatively small, the
 * goal is to design a policy for using the a singleton.  That is 
 * to say, lazy initialization is nice but carries complexities,
 * especially in threaded environments.  It's easier to have an 
 * explicit initialaztion as part of the system so that any
 * complex dependencies can be resolved by the order of 
 * execution of the initialization.
 */

template< class T >
class SingletonDynamic
{
private:
public:
   // DERIVED CLASSES MUST IMPLEMENT THESE FUNCTIONS
   // -----------------------------------------------------
   
   // Return false if something goes wrong, true otherwise.
   virtual bool Init() = 0;
   // Reset the singleton to the ground state.
   virtual void Reset() = 0;
   // Shut down the singleton, releasing memory, etc.
   virtual void Shutdown() = 0;
   
   // -----------------------------------------------------
   
   // Get an instance of the singleton.  It exists from the start
   // of time.
   static T& Instance()
   {
      static T _instance;
      return _instance;
   }
protected:
   SingletonDynamic() { }
};

#endif /* __SINGLETON_TEMPLATE_H__ */
