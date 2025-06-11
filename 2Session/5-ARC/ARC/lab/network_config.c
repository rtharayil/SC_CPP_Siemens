// network_config.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

// Hidden admin functionality
void admin_shell() {
    printf("\n[!] Access granted to Admin Shell!\n");
    printf("[!] Use responsibly.\n");
    
    exit(0);
}

void set_switch_name() {
    
    int id = 1001;
    char location[32];
    char admin_email[64];
    float version = 1.2;
    char buffer[64];  

    
    strcpy(location, "DataCenter-1");
    strcpy(admin_email, "admin@example.com");

    printf("Enter switch name: ");
    gets(buffer);  

    printf("Switch ID: %d\n", id);
    printf("Switch location: %s\n", location);
    printf("Admin contact: %s\n", admin_email);
    printf("Firmware version: %.1f\n", version);
    printf("Switch name set to: %s\n", buffer);
}

int main() {
    printf("=== Network Switch CLI ===\n");
    set_switch_name();
    printf("Exiting CLI...\n");
    return 0;
}
