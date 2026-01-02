// utils.c
#include "utils.h"

#ifdef _WIN32
    #define POPEN _popen
    #define PCLOSE _pclose
#else
    #define POPEN popen
    #define PCLOSE pclose
#endif

void print_hex(const char *label, const uint8_t *data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; ++i) printf("%02x", data[i]);
    printf("\n");
}

void hex_string_to_bytes(const char *hex, uint8_t *out, size_t out_len) {
    unsigned int temp;
    for (size_t i = 0; i < out_len; i++) {
        if (sscanf(hex + 2*i, "%02x", &temp) == 1) out[i] = (uint8_t)temp;
        else out[i] = 0;
    }
}

void secure_memzero(void *p, size_t n) {
    volatile uint8_t *v = p;
    while (n--) *v++ = 0;
}

// NEW: Cross-platform File Dialog
void get_file_path_from_dialog(char *buffer, size_t size) {
    FILE *pipe;
    buffer[0] = '\0'; // Clear buffer

    printf("Opening file manager... please select a file.\n");

    #ifdef _WIN32
        // Windows: Use PowerShell to open a file dialog
        pipe = POPEN("powershell -command \"Add-Type -AssemblyName System.Windows.Forms; $f = New-Object System.Windows.Forms.OpenFileDialog; $f.ShowDialog() | Out-Null; $f.FileName\"", "r");
    #else
        // Linux: Use Zenity (common in Ubuntu/Mint) or kdialog
        // Check if zenity is installed first
        pipe = POPEN("zenity --file-selection 2>/dev/null", "r");
    #endif

    if (!pipe) {
        printf("Error: Could not open file dialog. Please type path manually.\n");
        return;
    }

    // Read the output (the path selected by user)
    if (fgets(buffer, size, pipe) != NULL) {
        // Remove trailing newline character
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }

    PCLOSE(pipe);

    // Fallback if dialog was cancelled or failed
    if (strlen(buffer) == 0) {
        printf("No file selected. Please enter path manually: ");
        scanf(" %[^\n]s", buffer);
    } else {
        printf("Selected File Path: %s\n", buffer);
    }
}