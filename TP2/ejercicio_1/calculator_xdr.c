/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "calculator.h"

bool_t
xdr_Operands (XDR *xdrs, Operands *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->op1))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->op2))
		 return FALSE;
	return TRUE;
}