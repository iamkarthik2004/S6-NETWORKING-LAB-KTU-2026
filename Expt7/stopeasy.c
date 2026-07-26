#include <stdio.h>
#include <stdlib.h>

int s=0,a,t=1,ef,ea,time=5;

void send() {
    static int f=0;

    if(t) {
        if(ea && f) printf("SENDER: Received ACK for packet %d\n",a);

        if(s==5) exit(0);

        if(ea) s++;

        printf("SENDER: sent packet with seq NO:%d\n",s);

        ef=rand()%4;

        if(!ef) printf("Error While sending Packet\n");

        t=0;
        f=1;
    }
    else {
        printf("SENDER time reducing\n");

        if(--time==0) {
            t=1;
            ea=0;
            time=5;
        }
    }
}

void receive() {
    static int e=1;

    if(!t && ef) {

        if(s==e) {
            printf("RECEIVER: Received packet with seq %d\n",s);
            a=s;
            e++;
        }
        else {
            printf("RECEIVER: Duplicated packet with seq %d\n",e-1);
            a=e-1;
        }

        ea=rand()%4;

        if(!ea) printf("Error While sending ACK\n");

        t=1;
    }
}

int main() {
    while(1) {
        send();

        for(int i=0;i<10000000;i++);

        receive();
    }
}
