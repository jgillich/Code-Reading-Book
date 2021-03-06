// -*- C++ -*-

//=============================================================================
/**
 * @file LocalObject.h
 *
 * LocalObject.h,v 1.14 2001/05/25 00:20:33 othman Exp
 *
 * Header file for CORBA's base "LocalObject" type.
 *
 * A "LocalObject" is an entity that can be the target of a local
 * invocation.  See the CORBA Component Model specification for
 * details.
 *
 * @author Nanbor Wang <nanbor@cs.wustl.edu>
 */
//=============================================================================


#ifndef TAO_CORBA_LOCALOBJECT_H
#define TAO_CORBA_LOCALOBJECT_H

#include "ace/pre.h"

#include "Object.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

/**
 * @class CORBA_LocalObject
 *
 * @note NW: It is not clear whether minimum CORBA should support
 * LocalObject or not.  I think it should.
 */
class TAO_Export CORBA_LocalObject : public virtual CORBA_Object
{
public:

  /// Destructor
  virtual ~CORBA_LocalObject (void);

  /// Increment the ref count
  static CORBA_LocalObject_ptr _duplicate (CORBA_LocalObject_ptr obj);

  /// Return a NIL object
  static CORBA_LocalObject_ptr _nil (void);

  /**
   * @@ Narrowing a CORBA_LocalObject to a CORBA_Object is broken
   * right now.  The solution seems to be making CORBA_Object an
   * abstract base class and create a CORBA_RemoteObject for regular
   * object.  Or, even easier, add a <is_local> member into
   * CORBA_Object.  I'll take the easier route for now.
   */
  static CORBA_LocalObject_ptr _narrow (CORBA::Object_ptr obj,
                                        CORBA_Environment &ACE_TRY_ENV =
                                          TAO_default_environment ());

  /// No-op it is just here to simplify some templates.
  static CORBA_LocalObject_ptr _unchecked_narrow (
             CORBA::Object_ptr obj,
             CORBA_Environment &ACE_TRY_ENV =
               TAO_default_environment ());

#if (TAO_HAS_MINIMUM_CORBA == 0)

  /// Always returns false.
  virtual CORBA::Boolean _non_existent (CORBA_Environment &ACE_TRY_ENV =
                                          TAO_default_environment ());

  /// Throws CORBA::NO_IMPLEMENT.
  virtual CORBA::ImplementationDef_ptr
      _get_implementation (CORBA_Environment &ACE_TRY_ENV =
                             TAO_default_environment ());

  /// Gets info about object from the Interface Repository.
  virtual CORBA_InterfaceDef_ptr _get_interface (
      CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ()
    );

  /// Throws NO_IMPLEMENT.
  virtual void _create_request (CORBA::Context_ptr ctx,
                                const CORBA::Char *operation,
                                CORBA::NVList_ptr arg_list,
                                CORBA::NamedValue_ptr result,
                                CORBA::Request_ptr &request,
                                CORBA::Flags req_flags,
                                CORBA_Environment &ACE_TRY_ENV =
                                  TAO_default_environment ());

  virtual void _create_request (CORBA::Context_ptr ctx,
                                const CORBA::Char *operation,
                                CORBA::NVList_ptr arg_list,
                                CORBA::NamedValue_ptr result,
                                CORBA::ExceptionList_ptr exclist,
                                CORBA::ContextList_ptr ctxtlist,
                                CORBA::Request_ptr &request,
                                CORBA::Flags req_flags,
                                CORBA_Environment &ACE_TRY_ENV =
                                  TAO_default_environment ());

  /// Throws NO_IMPLEMENT.
  virtual CORBA::Request_ptr _request (const CORBA::Char *operation,
                                       CORBA_Environment &ACE_TRY_ENV =
                                         TAO_default_environment ());

#endif /* TAO_HAS_MINIMUM_CORBA */

#if (TAO_HAS_CORBA_MESSAGING == 1)

  /// Throws CORBA::NO_IMPLEMENT.
  CORBA::Policy_ptr _get_policy (
      CORBA::PolicyType type,
      CORBA_Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    );

  /// Throws CORBA::NO_IMPLEMENT.
  CORBA::Policy_ptr _get_client_policy (
      CORBA::PolicyType type,
      CORBA_Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    );

  /// Throws CORBA::NO_IMPLEMENT.
  CORBA::Object_ptr _set_policy_overrides (
      const CORBA::PolicyList & policies,
      CORBA::SetOverrideType set_add,
      CORBA_Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    );

  /// Throws CORBA::NO_IMPLEMENT.
  CORBA::PolicyList * _get_policy_overrides (
      const CORBA::PolicyTypeSeq & types,
      CORBA_Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    );

  /// Throws CORBA::NO_IMPLEMENT.
  CORBA::Boolean _validate_connection (
      CORBA::PolicyList_out inconsistent_policies,
      CORBA_Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    );

#endif /* TAO_HAS_CORBA_MESSAGING == 1 */

  /**
   * Return a hash value for this object.  The hash is based on the
   * address of the object.  On non-32 bit platforms, the hash may be
   * non-unique.
   */
  virtual CORBA::ULong _hash (CORBA::ULong maximum,
                              CORBA_Environment &ACE_TRY_ENV =
                                TAO_default_environment ());

  /**
   * Try to determine if this object is the same as <other_obj>.  This
   * method relies on the representation of the object reference's
   * private state.  Since that changes easily (when different ORB
   * protocols are in use) there is no default implementation.
   */
  virtual CORBA::Boolean _is_equivalent (CORBA_Object_ptr other_obj,
                                         CORBA_Environment &ACE_TRY_ENV =
                                             TAO_default_environment ())
    ACE_THROW_SPEC (());

  // = Reference count managment.
  /// Increment the reference count.
  virtual void _add_ref (void);

  /// Decrement the reference count.
  virtual void _remove_ref (void);

  // = TAO extensions

  /// Throws CORBA::NO_IMPLEMENT.
  virtual TAO_ObjectKey *_key (CORBA_Environment &ACE_TRY_ENV);

#if !defined(__GNUC__) || __GNUC__ > 2 || __GNUC_MINOR__ >= 8
  /// Useful for template programming.
  typedef CORBA_LocalObject_ptr _ptr_type;
  typedef CORBA_LocalObject_var _var_type;
#endif /* __GNUC__ */

protected:

  /// Default constructor.
  /**
   * Make it protected to prevent instantiation of this class.
   */
  CORBA_LocalObject (void);

private:

  /**
   * @name Unimplemented methods
   */
  //@{
  CORBA_LocalObject (const CORBA_LocalObject &);
  CORBA_LocalObject &operator = (const CORBA_LocalObject &);
  //@}

};

class TAO_Export CORBA_LocalObject_var
{
public:
  CORBA_LocalObject_var (void); // default constructor
  CORBA_LocalObject_var (CORBA_LocalObject_ptr);
  CORBA_LocalObject_var (const CORBA_LocalObject_var &); // copy constructor
  ~CORBA_LocalObject_var (void); // destructor

  CORBA_LocalObject_var &operator= (CORBA_LocalObject_ptr);
  CORBA_LocalObject_var &operator= (const CORBA_LocalObject_var &);
  CORBA_LocalObject_ptr operator-> (void) const;

  /// in, inout, out, _retn
  operator const CORBA_LocalObject_ptr &() const;
  operator CORBA_LocalObject_ptr &();
  CORBA_LocalObject_ptr in (void) const;
  CORBA_LocalObject_ptr &inout (void);
  CORBA_LocalObject_ptr &out (void);
  CORBA_LocalObject_ptr _retn (void);
  CORBA_LocalObject_ptr ptr (void) const;

private:
  CORBA_LocalObject_ptr ptr_;
};

class TAO_Export CORBA_LocalObject_out
{
public:
  CORBA_LocalObject_out (CORBA_LocalObject_ptr &);
  CORBA_LocalObject_out (CORBA_LocalObject_var &);
  CORBA_LocalObject_out (const CORBA_LocalObject_out &);
  CORBA_LocalObject_out &operator= (const CORBA_LocalObject_out &);
  CORBA_LocalObject_out &operator= (const CORBA_LocalObject_var &);
  CORBA_LocalObject_out &operator= (CORBA_LocalObject_ptr);
  operator CORBA_LocalObject_ptr &();
  CORBA_LocalObject_ptr &ptr (void);
  CORBA_LocalObject_ptr operator-> (void);

private:
  CORBA_LocalObject_ptr &ptr_;
};

/**
 * @class TAO_Local_RefCounted_Object
 This class adds default reference counting to local objects.
 */
class TAO_Export TAO_Local_RefCounted_Object : public virtual CORBA_LocalObject
{
public:

  /// Increment reference count.
  virtual void _add_ref (void);

  /// Decrement reference count.
  virtual void _remove_ref (void);

protected:

  // Default constructor.
  /**
   * Make it protected to prevent instantiation of this class.
   */
  TAO_Local_RefCounted_Object (void);

private:

  /**
   * @name Unimplemented methods
   */
  //@{
  TAO_Local_RefCounted_Object (const TAO_Local_RefCounted_Object &);
  TAO_Local_RefCounted_Object &operator = (const TAO_Local_RefCounted_Object &);
  //@}

};

#if defined (__ACE_INLINE__)
# include "LocalObject.i"
#endif /* __ACE_INLINE__ */

#include "ace/post.h"
#endif /* TAO_CORBA_LOCALOBJECT_H */
