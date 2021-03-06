// Servant_Locator.cpp,v 1.12 2000/07/14 12:07:44 irfan Exp

// ============================================================================
//
// = LIBRARY
//     TAO/examples/POA/On_Demand_Loading
//
// = FILENAME
//     Servant_Locator.cpp
//
// = DESCRIPTION
//     Implementation of ServantLocator_i class, used with a POA
//     having a NON_RETAIN policy.
//
// = AUTHOR
//     Kirthika Parameswaran <kirthika@cs.wustl.edu>
//
// ============================================================================

#include "Servant_Locator.h"

ACE_RCSID(On_Demand_Activation, Servant_Locator, "Servant_Locator.cpp,v 1.12 2000/07/14 12:07:44 irfan Exp")

// Initialization.

ServantLocator_i::ServantLocator_i (CORBA::ORB_ptr orb)
  : servant_manager_ (orb)
{
}

// This method associates an servant with the ObjectID.

PortableServer::Servant
ServantLocator_i::preinvoke (const PortableServer::ObjectId &oid,
                             PortableServer::POA_ptr poa,
                             const char * /* operation */,
                             PortableServer::ServantLocator::Cookie &cookie
                             TAO_ENV_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   PortableServer::ForwardRequest))
{
  TAO_ENV_ARG_DEFN;

  // Convert ObjectID to String.

  CORBA::String_var s =
    PortableServer::ObjectId_to_string (oid);

  // If ObjectID string has a Foo Substring create and return a
  // MyFooServant.

  PortableServer::Servant servant =
    this->servant_manager_.obtain_servant (s.in (),
                                           poa,
                                           27);
  if (servant != 0)
    {
      // Return the servant as the cookie , used as a check when
      // postinvoke is called on this ServantLocator_i.

      cookie = servant;
      return servant;
    }
  else
    ACE_THROW_RETURN (CORBA::OBJECT_NOT_EXIST (),
                      0);
}

// Since the servant gets invoked per operation, the servant has to be
// destroyed per operation too.  This is accomplished in the
// postinvoke method.

void
ServantLocator_i::postinvoke (const PortableServer::ObjectId &oid,
                              PortableServer::POA_ptr /* poa */,
                              const char * /* operation */,
                              PortableServer::ServantLocator::Cookie cookie,
                              PortableServer::Servant servant
                              TAO_ENV_ARG_DECL_NOT_USED)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  // Check the passed servant with the cookie.

  PortableServer::Servant my_servant =
    ACE_reinterpret_cast (PortableServer::Servant,
                          cookie);

  ACE_ASSERT (servant == my_servant);

  this->servant_manager_.destroy_servant (servant,
                                          oid);
  // To avoid warning about unused variable with ACE_NDEBUG.
  ACE_UNUSED_ARG (my_servant);
}

// This method returns an ObjectId when given an dll name and the
// factory function to be invoked in the dll.  The format of the
// ObjectId is libname:factory_function.

PortableServer::ObjectId_var
ServantLocator_i::create_dll_object_id (const char *dllname,
                                        const char *factory_function)
{
  return this->servant_manager_.create_dll_object_id (dllname,
                                                      factory_function);
}
