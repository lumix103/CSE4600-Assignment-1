#include <stdio.h>

void print_n_csusb(unsigned short n) {
    if (n % 2 == 0) {
        printf("CSU");
    }
    if (n % 5 == 0) {
        printf("SB");
    } 
    if(n % 2 != 0 && n % 5 != 0) {
        printf("%d", n);
    }
    printf("\n");
}

int main(int argc, char** argv) {
    print_n_csusb(2);
    print_n_csusb(5);
    print_n_csusb(10);
    print_n_csusb(11);
    return 0;
}