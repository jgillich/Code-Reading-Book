/* -*- C++ -*- */
// config-hpux-9.x-orbix.h,v 4.10 2000/03/23 21:27:02 nanbor Exp

// The following configuration file is designed to work for HP
// platforms running HP/UX 9.x.  Dave added Orbix stuff

#ifndef ACE_CONFIG_H
#define ACE_CONFIG_H
#include "ace/pre.h"

// Compiling for HPUX.
#if !defined (HPUX)
#define HPUX
#endif /* HPUX */

#if __cplusplus < 199707L
#define ACE_HAS_BROKEN_HPUX_TEMPLATES
#endif /* __cplusplus < 199707L */

#define ACE_HAS_BROKEN_CONVERSIONS
// Optimize ACE_Handle_Set for select().
#define ACE_HAS_HANDLE_SET_OPTIMIZED_FOR_SELECT

// They forgot a const in the prototype of const_timewait...
#define ACE_LACKS_CONST_TIMESPEC_PTR

// ************* HERE IS THE ORBIX STUFF - Dave 4/2/96
#define ACE_HAS_ORBIX 1

#define ACE_LACKS_SYSCALL
#define ACE_LACKS_STRRECVFD

// Compiler doesn't support static data member templates.
#define ACE_LACKS_STATIC_DATA_MEMBER_TEMPLATES

// Platform supports System V IPC (most versions of UNIX, but not Win32)
#define ACE_HAS_SYSV_IPC

// Platform supports recvmsg and sendmsg.
#define ACE_HAS_MSG

// Compiler/platform contains the <sys/syscall.h> file.
#define ACE_HAS_SYSCALL_H

// Fixes a problem with HP/UX not wrapping the mmap(2) header files
// with extern "C".
#define ACE_HAS_BROKEN_MMAP_H

// Prototypes for both signal() and struct sigaction are consistent.
#define ACE_HAS_CONSISTENT_SIGNAL_PROTOTYPES

// Compiler/platform has correctly prototyped header files.
#define ACE_HAS_CPLUSPLUS_HEADERS

// Header files lack t_errno for ACE_TLI.
#define ACE_LACKS_T_ERRNO

// Compiler/platform supports poll().
#define ACE_HAS_POLL

// Platform supports POSIX O_NONBLOCK semantics.
#define ACE_HAS_POSIX_NONBLOCK

// Compiler/platform defines the sig_atomic_t typedef
#define ACE_HAS_SIG_ATOMIC_T

// Compiler supports the ssize_t typedef.
#define ACE_HAS_SSIZE_T

// Defines the page size of the system.
#define ACE_PAGE_SIZE 4096

// Compiler/platform supports strerror ().
#define ACE_HAS_STRERROR

// ???
#define ACE_HAS_SUNOS4_GETTIMEOFDAY

// HP/UX has an undefined syscall for GETRUSAGE...
#define ACE_HAS_SYSCALL_GETRUSAGE

// Note, this only works if the flag is set above!
#define ACE_HAS_GETRUSAGE

// Platform uses int for select() rather than fd_set.
// Dave 4/2/96 took this out.  It appears that HP -can- use fd_set for int
// But time.h has a prototype defined so that int must be used ! so it goes
// back in
#define ACE_SELECT_USES_INT

// Platform has prototypes for ACE_TLI.
//#define ACE_HAS_TLI_PROTOTYPES
// Platform has the XLI version of ACE_TLI.
// #define ACE_HAS_XLI

#define ACE_LACKS_ACE_IOSTREAM

#define ACE_NEEDS_DEV_IO_CONVERSION

// Turns off the tracing feature.
#if !defined (ACE_NTRACE)
#define ACE_NTRACE 1
#endif /* ACE_NTRACE */

#include "ace/post.h"
#endif /* ACE_CONFIG_H */
