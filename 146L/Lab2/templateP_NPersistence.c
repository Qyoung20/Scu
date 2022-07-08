//COEN 146L : Lab2, step 4
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
        if (argc != 2) {  // check correct usage
		fprintf(stderr, "usage: %s <n connections> \n", argv[0]);
		exit(1);
	}
        //Declare and values to n (n connections), np (np parralel connections), RTT0, RTT1, RTT2, RTTHTTP, RTTDNS, .. 
        int n=atoi(argv[1]);
        int RTT0= 3, RTT1 = 20, RTT2 = 26, RTTHTTP= 47, RTTDNS, RTTDNS6, RTTDNS6NP, RTTDNS6P, NumSession, NumObject, np;
        np = n;
        RTTDNS = RTT0 + RTT1 +RTT2;
        RTTDNS6 = RTTDNS + 2 * (6 + 1) * RTTHTTP;
               
        printf("One object: %d msec\n", 2*RTTHTTP+RTTDNS);
        printf("Non-Persistent 6 objects: %d msec\n", RTTDNS6);

        //find how many np (parralel connections)
        NumObject = 6.0;
        NumSession = 0;
        if(NumObject>0){
                if(NumObject% np!= 0)
                        NumSession+=(NumObject/np)+1;
                else
                        NumSession+=(NumObject/np);
        }
        printf("NumSession= %d\n", NumSession);
        RTTDNS6P= RTTDNS+(2+NumSession)*RTTHTTP;
        RTTDNS6NP= RTTDNS+(NumSession + 1) * 2 * RTTHTTP;
        printf("%d parallel connection - Persistent: %d msec\n", np, RTTDNS6P);
        printf("%d parallel connection - Non-Persistent: %d msec\n", np, RTTDNS6NP);

return 0;
}