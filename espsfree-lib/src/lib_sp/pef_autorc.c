/* 
 * This material contains proprietary software of Entropic Speech, Inc.   
 * Any reproduction, distribution, or publication without the the prior	   
 * written permission of Entropic Speech, Inc. is strictly prohibited.
 * Any public distribution of copies of this work authorized in writing by
 * Entropic Speech, Inc. must bear the notice			
 *
 *      "Copyright (c) 1987 Entropic Speech, Inc."; All Rights Reserved
 *				
 * Written by:  John P. Burg
 * Modified by: David Burton for ESPS
 * Module:	pef_autorc.c
 *	
 * Generates autocorrelation values (r) and reflection coefficients
 * (c) from prediction error filter (pef) coefficients and  the residual
 * mean square value
 * 
 *	ORDER - number of input reflection coefficients
 *	C     - output array of size ORDER+1. C[0] contains the residual;
 *		C[1] through C[ORDER] contain the reflection coefficients.
 *	R     - output array of size ORDER+1. R[0] contains the energy of the
 *		the data (sum of squares); R[1] through R[ORDR] contains the
 *		rest of the autocorrelations
 *	PEF   - input array of size ORDER+1. PEF[0] contains the residual;
 *		PEF[1] through PEF[ORDER] contain prediction error filter
 *		coefficients. 
 *
 * NOTE: R[1] = R[0] * C[1]
 *
 * If the input residual is less <= 0, then pef_autorc exits
 * with a return value of -1. If one of the reflection coefficients >= 1, 
 * pef_autorc exits with a return value = to the index of the invalid
 * RC index. Otherwiase pef_autorc returns 0.
 */

#ifndef lint
static char *sccs_id = "@(#)pef_autorc.c	1.2 11/19/87 ESI";
#endif



	  pef_autorc(order, pef, r, c)
	  int    order;
	  double pef[], r[], c[];
	  {
	    int    m, i;
	    double temp;
	    if (pef[0] <= 0.0)      /* check that mean square  */
	      return(-1);            /* error is positive.      */

          /* Calculate the reflection coefficients.  */
          /* We shall use the r and c arrays for working storage. */

	  /*
	   * First change sign of PEFs for compatibility with ESPS
	  */
	    for(i = 1;i <= order;i++)
		pef[i] = -pef[i];

	    for (m = 0; m <= order; m++)
	      c[m] = pef[m];
            r[0] = pef[0];	/*initialize r[0] to residual*/
	    for (m = order; m > 0; m--)
	    {
	      temp = (1.0 - c[m]*c[m]);
	      if (temp <= 0.0) /* check validity of RCs*/
		return(m);

              r[0] /= temp;   /*update signal energy after finding each RC*/
	      for (i = 1; i < m; i++)
		r[i] = c[i];
	      for (i = 1; i < m; i++)
		c[i] = (c[i] - c[m]*r[m-i])/temp;
            }

          /* To keep storage requirements to a minimum, we calculate  */
	  /* the autocorrelation by means of the prediction error     */
	  /* filter generated by the negative reflection coefficients */

	    for (m = 1; m <= order; m++)
	    {
	      r[m] = -c[m];
	      for (i = 1; i <= m/2; i++)
	      {
	        temp = r[i] - c[m]*r[m-i];
		r[m-i] -= c[m]*r[i];
		r[i] = temp;
	      }
	    }

	  /* Scale the numerator pef by r[0]/2 */

	    r[0] /= 2.0;
	    for (m = 1; m <= order; m++)
	      r[m] *= r[0];

          /* Now, divide by the pef. */

	    for (m = 1; m <= order; m++)
	      for (i = 0; i < m; i++)
		r[m] -= r[i]*pef[m-i];

	    r[0] += r[0];  /* Double r[0] back */

	    /*
	     * Flip signs again for ESPS compatibility
	    */

	    for(i=1; i <= order; i++){
	      pef[i] = -pef[i];
	      c[i] = -c[i];
	    }

	    return(0);
          }
