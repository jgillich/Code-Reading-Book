//
// cdr_op_ci.cpp,v 1.1 1999/05/06 18:24:23 coryan Exp
//

// ================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    cdr_op_ci.cpp
//
// = DESCRIPTION
//    Visitor generating code for CDR operators for forward
//    declarations of valuetypes. This uses compiled marshaling.
//
// = AUTHOR
//    Torsten Kuepper based on code from
//    Aniruddha Gokhale & Carlos O'Ryan (cdr_op_ci.cpp)
//
// ================================================================

#include        "idl.h"
#include        "idl_extern.h"
#include        "be.h"

#include "be_visitor_valuetype_fwd.h"

ACE_RCSID(be_visitor_valuetype_fwd, cdr_op_ci, "cdr_op_ci.cpp,v 1.1 1999/05/06 18:24:23 coryan Exp")

// ****************************************************************
// Interface visitor for generating CDR operator declarations in the
// client header
// ****************************************************************

be_visitor_valuetype_fwd_cdr_op_ci::
be_visitor_valuetype_fwd_cdr_op_ci (be_visitor_context *ctx)
  : be_visitor_decl (ctx)
{
          ACE_ERROR_RETURN ((LM_ERROR,
                             "(%N:%l) be_visitor_valuetype_fwd_cdr_op_ci::"
                             "must be implemented\n"), -1);
}

be_visitor_valuetype_fwd_cdr_op_ci::
~be_visitor_valuetype_fwd_cdr_op_ci (void)
{
}

int
be_visitor_valuetype_fwd_cdr_op_ci::
visit_valuetype_fwd (be_valuetype_fwd *node)
{
  if (node->cli_inline_cdr_op_gen () || node->imported ())
    return 0;

  TAO_OutStream *os = this->ctx_->stream ();

  // generate the CDR << and >> operator declarations
  os->indent ();
  *os << "ACE_INLINE CORBA::Boolean" << be_nl
      << "operator<< (" << be_idt << be_idt_nl
      << "TAO_OutputCDR &," << be_nl
      << "const " << node->name () << "_ptr" << be_uidt_nl
      << ");" << be_uidt_nl;
  *os << "ACE_INLINE CORBA::Boolean" << be_nl
      << "operator>> (" << be_idt << be_idt_nl
      << "TAO_InputCDR &," << be_nl
      << node->name () << "_ptr &" << be_uidt_nl
      << ");" << be_uidt << "\n";

  node->cli_inline_cdr_op_gen (1);
  return 0;
}
