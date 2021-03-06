// test_i.h,v 1.3 1999/12/16 08:33:11 irfan Exp

// ============================================================================
//
// = LIBRARY
//   TAO/performance-tests/RTCorba/Oneways/Reliable
//
// = FILENAME
//   test_i.h
//
// = AUTHOR
//   Jeff Parsons
//
// ============================================================================

#ifndef TAO_RELIABLE_TEST_I_H
#define TAO_RELIABLE_TEST_I_H

#include "testS.h"

class Test_i : public POA_Test
{
  // = TITLE
  //   An implementation for the Test interface
  //
  // = DESCRIPTION
  //   Implements the Test interface in test.idl
  //
public:
  Test_i (CORBA::ORB_ptr orb);
  // ctor

  // = The Test methods.
  void oneway_payload_test (const Test::data &d,
                            CORBA::Environment &ACE_TRY_ENV =
                            TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  void oneway_work_test (CORBA::ULong work,
                         CORBA::Environment &ACE_TRY_ENV =
                         TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  void twoway_work_test (CORBA::ULong work,
                         CORBA::Environment &ACE_TRY_ENV =
                         TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  void shutdown (CORBA::Environment &ACE_TRY_ENV =
                   TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

private:
  CORBA::ORB_var orb_;
  // The ORB
};

#if defined(__ACE_INLINE__)
#include "test_i.i"
#endif /* __ACE_INLINE__ */

#endif /* TAO_RELIABLE_TEST_I_H */
