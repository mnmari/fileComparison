// Program for Prime Number Generation

#include <stdio.h>
main()
{
		 int n,i=1,j,c;
		 clrscr();
		 printf("Enter Number Of Terms
");
		 printf("Prime Numbers Are Follwing
");
		 scanf("%d",&n);
		 while(i<=n)
		 {
		    c=0;
		    for(j=1;j<=i;j++)
		    {
              if(i%j==0)
		 		 c++;
 		    }
           if(c==2)
           printf("%d	",i)
           i++;
        }
        getch();
}

