//
// be_union_label.cpp,v 1.6 2000/08/23 16:58:46 parsons Exp
//
#include "idl.h"
#include "idl_extern.h"
#include "be.h"

ACE_RCSID(be, be_union_label, "be_union_label.cpp,v 1.6 2000/08/23 16:58:46 parsons Exp")

be_union_label::be_union_label()
{
}
be_union_label::be_union_label (AST_UnionLabel::UnionLabel ul,
			       AST_Expression *v)
  : AST_UnionLabel (ul, 
                    v)
{
}

int
be_union_label::accept (be_visitor *visitor)
{
  return visitor->visit_union_label (this);
}
