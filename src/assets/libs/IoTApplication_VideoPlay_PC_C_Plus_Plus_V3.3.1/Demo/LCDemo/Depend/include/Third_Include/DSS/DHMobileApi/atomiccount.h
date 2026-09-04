#ifndef MX_ATOMICCOUNT_H
#define MX_ATOMICCOUNT_H

#include <cstdlib>

#include "../globaldef.h"
#include "Global.h"

NAMESPACE_BEGIN(DHTools)

  /**
   * @class AtomicCount
   * @author Eric Crahen <http://www.code-foo.com>
   * @date <2003-07-16T09:41:55-0400> 
   * @version 2.3.0
   *
   * This class provides an interface to a small integer whose value can be
   * incremented or decremented atomically. It's designed to be as simple and
   * lightweight as possible so that it can be used cheaply to create reference
   * counts.
   */
class INTERFACE_API_CLASS AtomicCount /*: public NonCopyable */
{
    void* _value;
  
public:
  
    //! Create a new AtomicCount, initialized to a value of 1
    AtomicCount();

    //! Destroy a new AtomicCount
    ~AtomicCount();

    //! Postfix decrement and return the current value
    // size_t operator--(int) { decrement(); } 
  
    //! Postfix increment and return the current value
    // size_t operator++(int) { increment(); }

    //! Prefix decrement and return the current value
    // size_t operator--() { decrement(); }
  
    //! Prefix increment and return the current value
    // size_t operator++() { increment(); }

    bool ref();
    bool deref();

    // void increment();
    // bool decrement();

	DISABLE_COPY(AtomicCount);
}; /* AtomicCount */
 
NAMESPACE_END

#endif // MX_ATOMICCOUNT_H



