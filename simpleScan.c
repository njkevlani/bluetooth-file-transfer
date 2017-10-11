// REFERENCE: https://people.csail.mit.edu/albert/bluez-intro/c404.html
/*
Authors:
    Shrey Amin:     140070107002
    Nilesh Kevlani: 140070107019
    Ashay Pathak:   140070107043
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

int main()
{
    // An structure used to store details of searched devices in near by area.
    inquiry_info *ii = NULL;
    int max_rsp, num_rsp;
    int dev_id, sock, len, flags;
    int i;
    char addr[19] = { 0 };
    char name[248] = { 0 };

    // Invoking the local bluetooth device
    dev_id = hci_get_route(NULL);
    // Negative socket oe dev_id indicates problems while accessing the hardware (Bluetooth here)
    sock = hci_open_dev( dev_id );
    if (dev_id < 0 || sock < 0) {
        perror("Error while opening socket");
        exit(1);
    }

    len  = 8;
    max_rsp = 255;
    flags = IREQ_CACHE_FLUSH;
    ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));
    // &ii is passed
    // That is an address. So the function changes the value of this variable (ii here)
    // The changes will be refelected in main code.
    // ii will contain information about active and visible bluetooth devices in range.
    num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
    if( num_rsp < 0 ) perror("Error in hci_inquiry");
    // Printing details of all devices in ii
    for (i = 0; i < num_rsp; i++) {
        // Converting an address to a string like "48:51:B7:85:2B:62"
        ba2str(&(ii+i)->bdaddr, addr);
        memset(name, 0, sizeof(name));
        if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name), 
            name, 0) < 0)
        strcpy(name, "[unknown]");
        printf("%s  %s\n", addr, name);
    }
    // Print the total number of devices found in the range
    printf("Total %d devices found.\n", num_rsp);

    // Closing sockets, freeing dynamically allocated memory
    free( ii );
    close( sock );
    return 0;
}