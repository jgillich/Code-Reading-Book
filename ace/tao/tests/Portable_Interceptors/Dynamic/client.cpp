// client.cpp,v 1.5 2001/02/05 20:01:49 othman Exp

#include "ace/Get_Opt.h"
#include "testC.h"
#include "interceptors.h"
#include "Echo_Client_ORBInitializer.h"

ACE_RCSID (Dynamic,
           client,
           "client.cpp,v 1.5 2001/02/05 20:01:49 othman Exp")

const char *ior = "file://test.ior";

int
parse_args (int argc, char *argv[])
{
  ACE_Get_Opt get_opts (argc, argv, "ef:");
  int c;

  while ((c = get_opts ()) != -1)
    switch (c)
      {
      case 'e':
      break;
      case 'f':
        ior = get_opts.optarg;
        break;
      case '?':
      default:
        ACE_ERROR_RETURN ((LM_ERROR,
                           "usage:  %s "
                           "-v "
                           "\n",
                           argv [0]),
                          -1);
      }
  return 0;
}

void
run_test (Test_Interceptors::Visual_ptr server,
          CORBA::Environment &ACE_TRY_ENV)
{
  server->normal (10, ACE_TRY_ENV);
  ACE_CHECK;

  CORBA::Long one = 1, two = 1, result = 0;
  result = server->calculate (one,
                              two,
                              ACE_TRY_ENV);
  ACE_CHECK;

  ACE_DEBUG ((LM_DEBUG,
              "result = %d\n",
              result));


  ACE_TRY
    {
      server->user (ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCH (Test_Interceptors::Silly, userex)
    {
      ACE_DEBUG ((LM_DEBUG, "Caught Silly\n"));
    }
  ACE_ENDTRY;
  ACE_CHECK;

  ACE_TRY_EX (SYS)
    {
      server->system (ACE_TRY_ENV);
      ACE_TRY_CHECK_EX (SYS);
    }
  ACE_CATCH (CORBA::INV_OBJREF, sysex)
    {
      ACE_DEBUG ((LM_DEBUG, "Caught CORBA::INV_OBJREF\n"));
    }
  ACE_ENDTRY;
}

int
main (int argc, char *argv[])
{
  ACE_TRY_NEW_ENV
    {
      PortableInterceptor::ORBInitializer_ptr temp_initializer =
        PortableInterceptor::ORBInitializer::_nil ();

      ACE_NEW_RETURN (temp_initializer,
                      Echo_Client_ORBInitializer,
                      -1);  // No exceptions yet!
      PortableInterceptor::ORBInitializer_var orb_initializer =
        temp_initializer;

      PortableInterceptor::register_orb_initializer (orb_initializer.in (),
                                                     ACE_TRY_ENV);
      ACE_TRY_CHECK;

      CORBA::ORB_var orb =
        CORBA::ORB_init (argc, argv, "", ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (parse_args (argc, argv) != 0)
        return 1;

      CORBA::Object_var object =
        orb->string_to_object (ior, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      Test_Interceptors::Visual_var server =
        Test_Interceptors::Visual::_narrow (object.in (), ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (CORBA::is_nil (server.in ()))
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             "Object reference <%s> is nil\n",
                             ior),
                            1);
        }

      run_test (server.in (), ACE_TRY_ENV);

      server->shutdown (ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "Caught exception:");
      return 1;
    }
  ACE_ENDTRY;

  return 0;
}
