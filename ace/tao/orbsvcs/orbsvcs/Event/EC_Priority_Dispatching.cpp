// EC_Priority_Dispatching.cpp,v 1.14 2001/03/26 21:17:02 coryan Exp

#include "EC_Priority_Dispatching.h"
#include "EC_Dispatching_Task.h"
#include "EC_Event_Channel.h"
#include "EC_QOS_Info.h"

#include "orbsvcs/Event_Service_Constants.h"
#include "orbsvcs/RtecSchedulerC.h"

#include "ace/Sched_Params.h"

#if ! defined (__ACE_INLINE__)
#include "EC_Priority_Dispatching.i"
#endif /* __ACE_INLINE__ */

ACE_RCSID(Event, EC_Priority_Dispatching, "EC_Priority_Dispatching.cpp,v 1.14 2001/03/26 21:17:02 coryan Exp")

TAO_EC_Priority_Dispatching::TAO_EC_Priority_Dispatching (TAO_EC_Event_Channel *ec)
  :  ntasks_ (0),
     tasks_ (0)
{
  CORBA::Object_var tmp = ec->scheduler ();
  this->scheduler_ = RtecScheduler::Scheduler::_narrow (tmp.in ());
}

void
TAO_EC_Priority_Dispatching::activate (void)
{
  if (this->tasks_ != 0)
    return;

  // @@ Query the scheduler to obtain this....
  this->ntasks_ = ACE_Scheduler_MAX_PRIORITIES;
  ACE_NEW (this->tasks_, TAO_EC_Dispatching_Task*[this->ntasks_]);

  // @@ Query the scheduler to obtain the priorities!
  int priority =
    (ACE_Sched_Params::priority_min (ACE_SCHED_FIFO) +
     ACE_Sched_Params::priority_max (ACE_SCHED_FIFO)) / 2;
  priority = ACE_Sched_Params::next_priority (ACE_SCHED_FIFO, priority);

  ACE_DECLARE_NEW_CORBA_ENV;
  for (int i = 0; i < this->ntasks_; ++i)
    {
      ACE_TRY
        {
          RtecScheduler::Period_t period =
            ACE_CU64_TO_CU32 (ACE_Scheduler_Rates[i]);
          char buf[128];
          ACE_OS::sprintf (buf, "Dispatching_Task-%d.us", period);

          RtecScheduler::handle_t rt_info =
            this->scheduler_->create (buf, ACE_TRY_ENV);
          ACE_TRY_CHECK;

          this->scheduler_->set (rt_info,
                                 RtecScheduler::VERY_LOW_CRITICALITY,
                                 0, // worst_cast_execution_time
                                 0, // typical_cast_execution_time
                                 0, // cached_cast_execution_time
                                 period,
                                 RtecScheduler::VERY_LOW_IMPORTANCE,
                                 0, // quantum
                                 1, // threads
                                 RtecScheduler::OPERATION,
                                 ACE_TRY_ENV);
          ACE_TRY_CHECK;
        }
      ACE_CATCHANY
        {
          // Ignore exceptions..
        }
      ACE_ENDTRY;

      ACE_NEW (this->tasks_[i],
               TAO_EC_Dispatching_Task (&this->thread_manager_));

      // @@ Query the scheduler to obtain the priority...
      long flags = THR_BOUND | THR_SCHED_FIFO;
      if (this->tasks_[i]->activate (flags, 1, 1, priority) == -1)
        {
          flags = THR_BOUND;
          priority = ACE_Sched_Params::priority_min (ACE_SCHED_OTHER,
                                                     ACE_SCOPE_THREAD);
          if (this->tasks_[i]->activate (flags, 1, 1, priority) == -1)
            ACE_ERROR ((LM_ERROR,
                        "EC (%P|%t) cannot activate queue %d", i));
        }
    }
}

void
TAO_EC_Priority_Dispatching::shutdown (void)
{
  if (this->tasks_ == 0)
    return;

  for (int i = 0; i < this->ntasks_; ++i)
    this->tasks_[i]->putq (new TAO_EC_Shutdown_Task_Command);

  this->thread_manager_.wait ();

  for (int j = 0; j < this->ntasks_; ++j)
    delete this->tasks_[j];

  delete[] this->tasks_;
  this->tasks_ = 0;
}

void
TAO_EC_Priority_Dispatching::push (TAO_EC_ProxyPushSupplier* proxy,
                                   RtecEventComm::PushConsumer_ptr consumer,
                                   const RtecEventComm::EventSet& event,
                                   TAO_EC_QOS_Info& qos_info,
                                   CORBA::Environment& ACE_TRY_ENV)
{
  RtecEventComm::EventSet event_copy = event;
  this->push_nocopy (proxy, consumer, event_copy, qos_info, ACE_TRY_ENV);
}

void
TAO_EC_Priority_Dispatching::push_nocopy (TAO_EC_ProxyPushSupplier* proxy,
                                          RtecEventComm::PushConsumer_ptr consumer,
                                          RtecEventComm::EventSet& event,
                                          TAO_EC_QOS_Info& qos_info,
                                          CORBA::Environment &ACE_TRY_ENV)
{
  if (this->tasks_ == 0)
    this->activate ();

  int i = qos_info.preemption_priority;
  if (i < 0 || i >= this->ntasks_)
    {
      // @@ Throw something?
      i = 0;
    }


  this->tasks_[i]->push (proxy, consumer, event, ACE_TRY_ENV);
}
