/*
 *  TEST SUITE FOR MB/WC FUNCTIONS IN C LIBRARY
 *
 *	 FILE:	dat_mbsrtowcs.c
 *
 *	 MBSRTOWCS:  size_t mbsrtowcs (wchar_t *ws, char **s, size_t n,
 *				       mbstate_t *ps);
 */


TST_MBSRTOWCS tst_mbsrtowcs_loc [] = {
  {
    { Tmbsrtowcs, TST_LOC_de },
    {
      { /*----------------- #01 -----------------*/
	{
	  {
	    { 1,  "\xfc\xe4\xf6",	    4,			 0,0 },
	    { 1,  "\xfc\xe4\xf6",	    3,			 0,0 },
	    { 1,  "\xfc\xe4\xf6",	    2,			 0,0 },
	  }
	},
	{
	  {
	    { 0,1,3, { 0x00FC,0x00E4,0x00F6,0x0000 }	     },
	    { 0,1,3, { 0x00FC,0x00E4,0x00F6,0x0000 }	     },
	    { 0,1,2, { 0x00FC,0x00E4,0x00F6,0x0000 }	     },
	  }
	}
      },
      { /*----------------- #02 -----------------*/
	{
	  {
	    { 1,  "\xfc\xe4\xf6",	    4,			 0,0 },
	    { 1,  "",			    1,			 0,0 },
	    { 0,  "\xfc\xe4\xf6",	    4,			 0,0 },
	  }
	},
	{
	  {
	    { 0,1,3, { 0x00FC,0x00E4,0x00F6,0x0000 }	     },
	    { 0,1,0, { 0x0000 }			     },
	    { 0,1,3, { 0x0000 }			     },
	  }
	}
      },
      { /*----------------- END -----------------*/
	.is_last = 1
      }
    }
  },

  {
    { Tmbsrtowcs, TST_LOC_enUS },
    {
      { /*----------------- #01 -----------------*/
	{
	  {
	    { 1,  "ABC",	    4,			 0,0 },
	    { 1,  "ABC",	    3,			 0,0 },
	    { 1,  "ABC",	    2,			 0,0 },
	  }
	},
	{
	  {
	    { 0,1,3, { 0x0041,0x0042,0x0043,0x0000 }	     },
	    { 0,1,3, { 0x0041,0x0042,0x0043,0x0000 }	     },
	    { 0,1,2, { 0x0041,0x0042,0x0043,0x0000 }	     },
	  }
	}
      },
      { /*----------------- #02 -----------------*/
	{
	  {
	    { 1,  "ABC",	    4,			 0,0 },
	    { 1,  "",		    1,			 0,0 },
	    { 0,  "ABC",	    4,			 0,0 },
	  }
	},
	{
	  {
	    { 0,1,3, { 0x0041,0x0042,0x0043,0x0000 }	     },
	    { 0,1,0, { 0x0000 }			     },
	    { 0,1,3, { 0x0000 }			     },
	  }
	}
      },
      { /*----------------- END -----------------*/
	.is_last = 1
      }
    }
  },

  {
    { Tmbsrtowcs, TST_LOC_eucJP },
    {
      { /*----------------- #01 -----------------*/
	{
	  {
	    { 1,  "\244\242\244\244\244\246ABC",      7, 0,0 },
	    { 1,  "\244\242\244\244\244\246ABC",      6, 0,0 },
	    { 1,  "\244\242\244\244\244\246ABC",      4, 0,0 },
	  }
	},
	{
	  {
	    { 0,1,6, { 0x3042,0x3044,0x3046,0x0041,0x0042,0x0043,0x0000 }},
	    { 0,1,6, { 0x3042,0x3044,0x3046,0x0041,0x0042,0x0043,0x0000 }},
	    { 0,1,4, { 0x3042,0x3044,0x3046,0x0041,0x0000 }		   },
	  }
	}
      },
      { /*----------------- #02 -----------------*/
	{
	  {
	    { 1,  "\244\242\244\244\244\246ABC",      7, 0,0 },
	    { 1,  "",		      1, 0,0 },
	    { 0,  "\244\242\244\244\244\246ABC",      7, 0,0 },
	  }
	},
	{
	  {
	    { 0,1,6, { 0x3042,0x3044,0x3046,0x0041,0x0042,0x0043,0x0000 }},
	    { 0,1,0, { 0x0000 }					   },
	    { 0,1,6, { 0x0000 }					   },
	  }
	}
      },
      { /*----------------- END -----------------*/
	.is_last = 1
      }
    }
  },
  {
    { Tmbsrtowcs, TST_LOC_end }
  }
};
