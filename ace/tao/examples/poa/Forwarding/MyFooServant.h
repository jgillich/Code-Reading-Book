// MyFooServant.h,v 1.6 2001/03/28 01:58:09 parsons Exp
//=============================================================================
//
//
// = FILENAME
//     MyFooServant.h
//
// = DESCRIPTION
//     Defines MyFooServant class for the Foo interface
//
// = AUTHOR
//     Irfan Pyarali and Michael Kircher
//
//=============================================================================

#ifndef MYFOOSERVANT_H
#define MYFOOSERVANT_H

#include "FooS.h"

#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */

class MyFooServantActivator;

class MyFooServant : public virtual PortableServer::RefCountServantBase,
                     public virtual POA_Foo
{
public:
  MyFooServant (CORBA::ORB_ptr orb_ptr,
                PortableServer::POA_ptr poa,
                MyFooServantActivator &activator,
                CORBA::Long value);

  virtual CORBA::Long doit (CORBA::Environment &env)
    ACE_THROW_SPEC ((CORBA::SystemException));

  // Setup forwarding
  virtual void forward (CORBA::Environment &env)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     Foo::Cannot_Forward));

  virtual void shutdown (CORBA::Environment &env)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual PortableServer::POA_ptr _default_POA (CORBA::Environment &env);
  // Returns the default POA for this servant.

protected:
  CORBA::ORB_var orb_;
  PortableServer::POA_var poa_;
  MyFooServantActivator &activator_;
  CORBA::Long value_;
};

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma warning(pop)
#endif /* _MSC_VER */

#endif /* MYFOOSERVANT_H */
