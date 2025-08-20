#include <stdio.h>

int main(void) {
    int counter = 0;
    while (counter < 21) {
				++counter;
				if ((counter & 1) != 0){
					/* do something when counter is odd */
				}
				else {
						/* do something when counter is even */
				}
			}

    return 0;
}
