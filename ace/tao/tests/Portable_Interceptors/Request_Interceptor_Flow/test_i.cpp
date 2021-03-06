// -*- C++ -*-

#include "test_i.h"

ACE_RCSID (Request_Interceptor_Flow,
           test_i,
           "test_i.cpp,v 1.1 2001/04/09 23:27:06 othman Exp")

test_i::test_i (CORBA::ORB_ptr orb)
  : orb_ (CORBA::ORB::_duplicate (orb))
{
}

void
test_i::client_test (Test::TestScenario scenario,
                     CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((Test::X,
                   Test::UnknownScenario,
                   CORBA::SystemException))
{
  switch (scenario)
    {
    case 1:
    case 4:
      // Both the client-side and server-side tests throw this
      // exception in these scenarios.
      ACE_THROW (Test::X ());  // Expected test exception
    case 2:
    case 3:
      break;
    default:
      ACE_THROW (Test::UnknownScenario (scenario));  // Unexpected!
    }
}

void
test_i::server_test (Test::TestScenario scenario,
                     CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((Test::X,
                   Test::UnknownScenario,
                   CORBA::SystemException))
{
  switch (scenario)
    {
    case 1:
    case 4:
      // Both the client-side and server-side tests throw this
      // exception in these scenarios.
      ACE_THROW (Test::X ());  // Expected test exception
    case 2:
    case 3:
      break;
    default:
      ACE_THROW (Test::UnknownScenario (scenario));  // Unexpected!
    }
}

void
test_i::shutdown (CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_DEBUG ((LM_INFO,
              "Server is shutting down.\n"));

  this->orb_->shutdown (0, ACE_TRY_ENV);
}
