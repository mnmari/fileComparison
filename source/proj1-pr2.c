/*
check if a number is prime
*/
#include<stdio.h>
#include<math.h>
int main()
{
int j,number;
scanf("%d",&number);
if(number<=1)
return 0;
else if(number==2)
return 1;
else
for(j=3;j<(int)sqrt(number);j+=2)
{
if(number%j==0)
printf("not prime\n");
else
printf("prime\n");
return 1;
}
return 0;
}

