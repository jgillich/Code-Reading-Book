// Get_Opt.cpp
// Get_Opt.cpp,v 4.22 2000/10/07 08:03:47 brunsch Exp

#include "ace/Get_Opt.h"
#include "ace/Log_Msg.h"

#if !defined (__ACE_INLINE__)
#include "ace/Get_Opt.i"
#endif /* __ACE_INLINE__ */

ACE_RCSID(ace, Get_Opt, "Get_Opt.cpp,v 4.22 2000/10/07 08:03:47 brunsch Exp")

/*
 * Copyright (c) 1987, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

ACE_ALLOC_HOOK_DEFINE(ACE_Get_Opt)

ACE_Get_Opt::ACE_Get_Opt (int argc,
			  ACE_TCHAR **argv,
			  const ACE_TCHAR *optstring,
			  int skip,
			  int report_errors)
  : optarg (0),
    optind (skip),
    opterr (report_errors),
    argc_ (argc),
    argv_ (argv),
    nextchar_ (0),
    optstring_ (optstring)
{
  ACE_TRACE ("ACE_Get_Opt::ACE_Get_Opt");
}

void
ACE_Get_Opt::dump (void) const
{
  ACE_TRACE ("ACE_Get_Opt::dump");

  ACE_DEBUG ((LM_DEBUG, ACE_BEGIN_DUMP, this));
  ACE_DEBUG ((LM_DEBUG,  ACE_LIB_TEXT ("\n")));
  ACE_DEBUG ((LM_DEBUG, ACE_END_DUMP));
}

int
ACE_Get_Opt::operator () (void)
{
  ACE_TRACE ("ACE_Get_Opt::operator");

  if (argv_ == 0)
    {
      // It can happen, e.g., on VxWorks.
      optind = 0;
      return EOF;
    }

  int opt; // Character checked for validity.
  const ACE_TCHAR *oli; // Option letter index.

  if (this->nextchar_ == 0 || *this->nextchar_ == '\0')
    {
      // Update scanning pointer.

      if (this->optind >= this->argc_
	  || *(this->nextchar_ = this->argv_[this->optind]) != '-')
	{
	  this->nextchar_ = ACE_const_cast (ACE_TCHAR *, ACE_LIB_TEXT (""));
	  return EOF;
	}

      if (this->nextchar_[1] != 0
	  && *++this->nextchar_ == '-')
	{
	  // Found "--".
	  ++this->optind;
	  this->nextchar_ = ACE_const_cast (ACE_TCHAR *, ACE_LIB_TEXT (""));
	  return EOF;
	}
    }

  // Option letter okay?
  opt = (int) *this->nextchar_++;

  if (opt == (int) ':'
      || ((oli = ACE_OS::strchr (this->optstring_, opt)) == 0))
    {
      // If the user didn't specify '-' as an option, assume it means
      // EOF.
      if (opt == (int) '-')
	return EOF;

      if (*this->nextchar_ == 0)
	++this->optind;

      if (this->opterr && *this->optstring_ != ':')
	ACE_ERROR ((LM_ERROR,
                    ACE_LIB_TEXT ("%s: illegal option -- %c\n"),
		    this->argv_[0],
                    opt));
      return '?';
    }

  if (*++oli != ':')
    { // Don't need argument.
      this->optarg = 0;
      if (!*this->nextchar_)
	++this->optind;
    }
  else
    { // Need an argument.
      if (*this->nextchar_) // No white space.
	this->optarg = this->nextchar_;
      else if (this->argc_ <= ++this->optind)
	{
	  // No arg.
	  this->nextchar_ = ACE_const_cast (ACE_TCHAR *, ACE_LIB_TEXT (""));

	  if (*this->optstring_ == ':')
	    return ':';
	  if (this->opterr)
	    ACE_ERROR ((LM_ERROR,
			ACE_LIB_TEXT ("%s: option requires an argument -- %c\n"),
			this->argv_[0], opt));
	  return '?';
	}
      else // White space.
	this->optarg = this->argv_[this->optind];

      this->nextchar_ = ACE_const_cast (ACE_TCHAR *, ACE_LIB_TEXT (""));
      ++this->optind;
    }

  return opt; // Dump back option letter.
}
