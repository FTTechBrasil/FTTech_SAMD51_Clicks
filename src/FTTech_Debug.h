#ifndef _FTTECH_DEBUG_H_
#define _FTTECH_DEBUG_H_

// General defines
#define FTTECH_PRINT Serial
#define FTTECH_NEWLINE "\r\n"

/*! 
  @def DEBUG_FTTECH_SAMD51 
  @brief Possible values:
    0: No debug mode enabled
    1: debug mode enabled for error output messages
    2: debug mode enabled for both error and ok messages
*/
#define DEBUG_FTTECH_SAMD51		2
#define LOG1_FTTECH_PRINT(str1)                 { FTTECH_PRINT.print(str1); }
#define LOG1_FTTECH_PRINTLN(str1)               { FTTECH_PRINT.println(str1); }
#define DEBUG1_FTTECH_PRINT(str1)	              { FTTECH_PRINT.print(F("[FT] ")); FTTECH_PRINT.print(str1); }
#define DEBUG1_FTTECH_PRINTLN(str1)	            { FTTECH_PRINT.print(F("[FT] ")); FTTECH_PRINT.println(str1); }                 
#define DEBUG2_FTTECH_PRINT(str1, str2)	        { FTTECH_PRINT.print(F("[FT] ")); FTTECH_PRINT.print(str1); FTTECH_PRINT.print(str2);}
#define DEBUG2_FTTECH_PRINTLN(str1, str2)	      { FTTECH_PRINT.print(F("[FT] ")); FTTECH_PRINT.print(str1); FTTECH_PRINT.println(str2);}                 


#endif