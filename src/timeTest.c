#include <stdio.h>
#include <time.h>

int main()   
{   
 clock_t t1, t2;

 t1 = clock();   

 int i;
float diff;
 for(i = 0; 1 ;i++)   
 {   
 	t2 = clock();  
	diff = (((float)t2 - (float)t1) / 1000000.0F );
	if(diff >0.5){
		printf("%d\n", i);
		t1=t2;
	}
 }   

 

// float diff = (((float)t2 - (float)t1) / 1000000.0F ) * 1000;   
// printf("\n\ndiff time is %f\n\n",diff);   

 return 0;   
 }
