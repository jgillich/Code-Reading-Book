/* -*- C++ -*- */
// Input_Handler.h,v 4.4 1998/10/20 02:34:35 levine Exp

// ============================================================================
//
// = LIBRARY
//    EventComm
//
// = FILENAME
//    Input_Handler.h
//
// = DESCRIPTION
//    Handle input from the keyboard.
//
// = AUTHOR
//    Douglas C. Schmidt (schmidt@cs.wustl.edu)
//
// ============================================================================

#ifndef _INPUT_HANDLER_H
#define _INPUT_HANDLER_H

#include "ace/Service_Config.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#if defined (ACE_HAS_ORBIX) && (ACE_HAS_ORBIX != 0)

// Forward declaration.
class Notifier_Handler;

class Input_Handler : public ACE_Service_Object
{
  // = TITLE
  //   Handles input events generated from a keyboard.
  //
  // = DESCRIPTION
  //   The events are currently framed and forwarded to
  //   all Consumers.  In the future, we will need to
  //   be more selective and only send to those Consumers
  //   whose filtering criteria matches!
public:
  Input_Handler (Notifier_Handler *,
                 ACE_HANDLE = ACE_STDIN);
  // Use stdin by default.

  virtual int handle_input (ACE_HANDLE);
  // Frame input events and notify <Consumers>.

  virtual int handle_close (ACE_HANDLE = ACE_INVALID_HANDLE,
                            ACE_Reactor_Mask = ACE_Event_Handler::NULL_MASK);
  // Close down the handler.

protected:
  virtual ACE_HANDLE get_handle (void) const;

  ACE_HANDLE handle_;
  // ACE_HANDLE where the input comes from.

  Notifier_Handler *notifier_;
  // Pointer to a <Notifier_Handler> that's used to inform Consumers
  // that events of interest have occurred.

  FILE *fp_;
  // Pointer to an input ACE_FILE.

private:
  ~Input_Handler (void);
  // Ensure dynamic allocation.
};

#endif /* ACE_HAS_ORBIX */
#endif /* _INPUT_HANDLER_H */
