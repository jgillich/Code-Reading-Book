/**
 * @file Loopback_Consumer.h
 *
 * Loopback_Consumer.h,v 1.1 2001/08/24 21:46:48 coryan Exp
 *
 */

#ifndef ECFL_LOOPBACK_CONSUMER_H
#define ECFL_LOOPBACK_CONSUMER_H

#include "Loopback_Supplier.h"
#include "Servant_var.h"
#include "orbsvcs/RtecEventCommS.h"
#include "orbsvcs/RtecEventChannelAdminC.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

/**
 * @class ECFL_Loopback_Consumer
 *
 * @brief Implement a simple consumer to keep track of the latency
 *
 */
class ECFL_Loopback_Consumer
  : public virtual POA_RtecEventComm::PushConsumer
  , public virtual PortableServer::RefCountServantBase

{
public:
  /// Constructor
  ECFL_Loopback_Consumer (CORBA::Long experiment_id,
                          ECFL_Loopback_Supplier *supplier);

  /// Connect to the event channel
  void connect (RtecEventChannelAdmin::EventChannel_ptr ec,
                CORBA::Environment &ACE_TRY_ENV);

  /// Disconnect from the event channel
  void disconnect (CORBA::Environment &ACE_TRY_ENV);

  //@{
  /** @name The RtecEventComm::PushConsumer methods
   */
  virtual void push (const RtecEventComm::EventSet& events,
                     CORBA::Environment &_env)
    ACE_THROW_SPEC ((CORBA::SystemException));
  virtual void disconnect_push_consumer (CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException));
  //@}

private:
  /// Synchronize access to the internal data
  TAO_SYNCH_MUTEX mutex_;

  /// The experiment id
  CORBA::Long experiment_id_;

  /// The supplier used to close the loopback
  Servant_var<ECFL_Loopback_Supplier> supplier_;

  /// The proxy this object is connected to
  RtecEventChannelAdmin::ProxyPushSupplier_var proxy_supplier_;
};

#endif /* ECFL_LOOPBACK_CONSUMER_H */
