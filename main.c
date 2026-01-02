// main.c
#include "utils.h"
#include "crypto_aes.h"
#include "sha256.h"

 
//function to handle file encryption and decryption
void encrypt_file(const char *input_path, const char *password);
void decrypt_file(const char *input_path, const char *password);



void handle_text_encryption() {
    char text[256];
    char password[100];
    
    printf("Enter text to encrypt (max 255 chars): ");
    scanf(" %[^\n]s", text);
    printf("Enter password: ");
    scanf(" %[^\n]s", password);

    uint8_t hash[32];
    sha256((uint8_t*)password, strlen(password), hash);
    uint8_t key[16];
    memcpy(key, hash, 16); 

    size_t len = strlen(text);
    size_t blocks = (len / BLOCK_SIZE) + 1;
    uint8_t buffer[BLOCK_SIZE];
    
    printf("\n--- Encrypted Output (Hex) ---\n");
    for (size_t b = 0; b < blocks; b++) {
        memset(buffer, 0, BLOCK_SIZE);
        strncpy((char*)buffer, text + (b * BLOCK_SIZE), BLOCK_SIZE);
        aes_encrypt_block(buffer, key);
        for(int i=0; i<16; i++) printf("%02x", buffer[i]);
    }
    printf("\n");
}

void handle_text_decryption() {
    char hex_input[1024];
    char password[100];

    printf("Enter encrypted hex string: ");
    scanf(" %[^\n]s", hex_input);
    printf("Enter password: ");
    scanf(" %[^\n]s", password);

    uint8_t hash[32];
    sha256((uint8_t*)password, strlen(password), hash);
    uint8_t key[16];
    memcpy(key, hash, 16);

    size_t hex_len = strlen(hex_input);
    uint8_t buffer[BLOCK_SIZE];

    printf("\n--- Decrypted Plaintext ---\n");
    for (size_t i = 0; i < hex_len; i += 32) {
        hex_string_to_bytes(hex_input + i, buffer, BLOCK_SIZE);
        aes_decrypt_block(buffer, key);
        for(int j=0; j<BLOCK_SIZE; j++) {
            if(buffer[j] == 0) continue;
            printf("%c", buffer[j]);
        }
    }
    printf("\n");
}

int main() {
    int choice;
    do
    {
        printf("\n===== SecureCrypt =====\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int subchoice;
            printf("\n1. Text Input\n2. Select File\nSelect: ");
            scanf("%d", &subchoice);
            if (subchoice == 1) handle_text_encryption();
            else if (subchoice == 2) {
                char path[512], pass[100];
                
                // NEW: Use the pop-up dialog!
                get_file_path_from_dialog(path, sizeof(path));
                
                if (strlen(path) > 0) {
                    printf("Enter Password: ");
                    scanf(" %[^\n]s", pass);
                    encrypt_file(path, pass);
                }
            }
        } else if (choice == 2) {
            int subchoice;
            printf("\n1. Text Input\n2. File Input (Select File)\nSelect: ");
            scanf("%d", &subchoice);
            if (subchoice == 1) handle_text_decryption();
            else if (subchoice == 2) {
                char path[512], pass[100];
                
                // NEW: Use the pop-up dialog!
                get_file_path_from_dialog(path, sizeof(path));
                
                if (strlen(path) > 0) {
                    printf("Enter Password: ");
                    scanf(" %[^\n]s", pass);
                    decrypt_file(path, pass);
                }
            }
        }
    } while (choice != 3);

    return 0;
    
}