#ifdef SGEOS
#define		MAX_INDEX_ELEMENTS 5
#define		COEF_INDEX	   0
#define		JEFIT_INDEX	   2
#define		COLD_INDEX	   3
#define		MELT_INDEX	   4
#endif

#ifdef PROP
#define		MAX_INDEX_ELEMENTS 10
#define		COEF_INDEX	   0
#define         ABAR_INDEX         6
#define		JEFIT_INDEX	   7
#define		COLD_INDEX	   8
#define		MELT_INDEX	   9
#endif

/* List of indices into the material array returned by		*/
/* readsg().  Most are not currently used by the program.	*/
/* 								*/
/* NOTE: JEFIT occurs in the EOSBFILE printout and in the sgeos	*/
/* source file right after ayz.  But it must occur after ayz in */
/* the binary file so that the cold coefficients will imme-	*/
/* diately follow it.						*/

#define		EOS		 0

#ifdef SGEOS
#define		CZERO		 1
#define		QFB		 2
#define		AREZ		 3
#define		EOSFORM		 4
#define		RHO0		 5
#define		V0		 6
#define		E0		 7
#define		PMIN		 8
#define		PMSW		 9
#define		BHE		10
#define		ETAMIN		11
#define		ETAMAX		12
#endif

#ifdef PROP
#define		CZERO		 2
#define		QFB		 3
#define		AREZ		 4
#define		EOSFORM		 7
#define		RHO0		 8
#define		V0		 9
#define		E0	        10
#define		PMIN	        11
#define		PMSW	        12
#define		BHE		13
#define		ETAMIN		14
#define		ETAMAX		15
#endif

#define		NUM_COEFS	(int)(mat_array[COEF_INDEX] + 0.1)
#define		COEFS		( NUM_COEFS + 1 )

#ifdef SGEOS
#define		CMU		( COEFS + num_coefs )
#endif

#ifdef PROP
#define		CMU		( 4 + (int)(mat_array[ABAR_INDEX] + 0.1) )
#endif

#define		Y		( CMU + 1 )
#define		AU		( Y + 1 )
#define		BU		( AU + 1 )
#define		YE		( BU + 1 )
#define		YP		( YE + 1 )
#define		YB		( YP + 1 )
#define		YC		( YB + 1 )
#define		GAM0		( YC + 1 )
#define		YWHMZ		( GAM0 + 1 )
#define		GZYZ		( YWHMZ + 1 )
#define		ITHERM		( GZYZ + 1 )
#define		THERMF		( ITHERM + 1 )
#define		WYZ		( THERMF + 1 )
#define		TMYZ		( WYZ + 1 )
#define		AYZ		( TMYZ + 1 )
#define		JEFIT		(int)(mat_array[JEFIT_INDEX] + 0.1)
#define		COLD_COEFS	(int)(mat_array[COLD_INDEX]  + 0.1)
#define		MELT_COEFS	(int)(mat_array[MELT_INDEX]  + 0.1)
#define		BEGR		( MELT_COEFS + (int)(data_array[JEFIT] + 0.1) )
#define		ENDR		( BEGR + 1 )
#define		G1		( ENDR + 1 )
#define		G2		( G1 + 1 )
#define		FTWIN		( G2 + 1 )
#define		SPALL		( FTWIN + 1 )
#define		DAM0		( SPALL + 1 )
#define		PCRUSH		( DAM0 + 1 )
#define		C1		( PCRUSH + 1 )
#define		C2		( C1 + 1 )
#define		UK		( C2 + 1 )
#define		Y_P		( UK + 1 )
#define		YA		( Y_P + 1 )
#define		YSTRMX		( YA + 1 )
#define		A1		( YSTRMX + 1 )
#define		A2		( A1 + 1 )
#define		A3		( A2 + 1 )
