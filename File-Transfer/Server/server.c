/*
Authors:
    Shrey Amin:     140070107002
    Nilesh Kevlani: 140070107019
    Ashay Pathak:   140070107043
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

int main()
{
    // structre variable for bluetooth address of server(local) and client(remote)
    struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
    char buf[1024] = { 0 };
    int s, client, bytes_read;
    socklen_t opt = sizeof(rem_addr);

    // allocate socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // bind socket to port 1 of the first available 
    // local bluetooth adapter configuration
    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = *BDADDR_ANY;
    loc_addr.rc_channel = (uint8_t) 1;
    // bunding the socket with local bluetooth adapter
    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));    

    // put socket into listening mode
    listen(s, 1);
    // accept one connection
    client = accept(s, (struct sockaddr *)&rem_addr, &opt);

    ba2str( &rem_addr.rc_bdaddr, buf );
    printf("accepted connection from %s\n", buf);

    // Resst the string buf, or say clear the string
    memset(buf, 0, sizeof(buf));

    // read data from the client
    bytes_read = read(client, buf, sizeof(buf));
    // Keep reading until "END" comes
    while(strcmp(buf, "END")){    
        printf("%s ", buf);
        bytes_read = read(client, buf, sizeof(buf));
    }
    
    // close connection
    close(client);
    close(s);
    return 0;
}