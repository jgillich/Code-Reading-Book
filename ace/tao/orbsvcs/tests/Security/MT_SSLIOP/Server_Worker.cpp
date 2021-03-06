// Server_Worker.cpp,v 1.1 2001/09/05 22:43:02 anandk Exp
#include "Server_Worker.h"

Server_Worker::Server_Worker (CORBA::ORB_ptr orb)
  :  orb_ (CORBA::ORB::_duplicate (orb))
{
}

int
Server_Worker::svc (void)
{
  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      this->orb_->run (ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
    }
  ACE_ENDTRY;
  return 0;
}
