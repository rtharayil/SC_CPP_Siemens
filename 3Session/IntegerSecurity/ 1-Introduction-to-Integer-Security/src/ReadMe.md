  
  
gcc limits.c 
  
  
gcc overflow_test.c 
  
  
 g++ signed_unsigned.cpp

 g++ -Wall -Wsign-compare -Wconversion signed_unsigned.cpp

 ### Relevant Compiler Flags

* `-Wsign-compare`: Warns when comparing signed and unsigned values.
* `-Wconversion`: Warns on implicit conversions that may alter a value.


gcc -Wall -Wconversion truncation_test.c