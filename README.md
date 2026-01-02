<img width="1536" height="1024" alt="image" src="https://github.com/user-attachments/assets/b27f42fa-7ecd-4b3b-8067-b68bea507619" />
<p align="center">
<img src="https://img.shields.io/badge/Language-C-blue">
<img src="https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-lightgrey">
<img src="https://img.shields.io/badge/Build-GCC%20%7C%20Clang-green">
<img src="https://img.shields.io/badge/Cryptography-Symmetric%20Encryption-blueviolet">
<img src="https://img.shields.io/badge/Algorithm-AES--128-informational">
<img src="https://img.shields.io/badge/Hash-SHA--256-orange">
<img src="https://img.shields.io/badge/Interface-CLI%20(Menu--Driven)-purple">
<img src="https://img.shields.io/badge/Purpose-Educational%20Cryptography-lightblue">
<img src="https://img.shields.io/badge/License-MIT-yellow">
</p>
🛡️ SecureCrypt: Modular Encryption System in C
===================================================

**A terminal-based, menu-driven encryption tool featuring custom SHA-256 key derivation and AES-128 symmetric encryption.**

* * * * *

💡 1. Motivation & Purpose
--------------------------

This project was built to demonstrate core **systems programming concepts** in C, specifically **manual memory management**, **file I/O operations**, and **cryptographic logic implementation**.

While modern development often relies on high-level libraries (like OpenSSL), building a cryptographic system from scratch provides a deeper understanding of how data is processed at the byte level. This project serves as an educational exploration into how symmetric encryption and hashing algorithms function under the hood.

🌟 2. Key Features
------------------

-   🖥️ **Interactive CLI:** Clean, menu-driven interface for easy navigation.

-   🔄 **Dual Mode Operation:** Supports both direct text input and binary file encryption.

-   🔑 **Password-Based Security:** Uses user-defined passwords to generate encryption keys.

-   🛡️ **SHA-256 Key Derivation:** Implements SHA-256 hashing to transform passwords into secure fixed-length keys.

-   🔐 **AES-128 Encryption:** Uses a custom educational implementation of the Advanced Encryption Standard (AES).

-   📂 **Native File Dialog:** Integrates with the OS (Windows/Linux) to open native file selection windows.

-   🧩 **Modular Architecture:** Clean code structure separating logic into distinct modules (`crypto`, `io`, `utils`).

🏗️ 3. System Architecture Overview
-----------------------------------

The application is designed using a **Layered Architecture**, separating user interaction from core cryptographic logic.

### 3.1. High-Level Architecture

The system is composed of three distinct layers:

1.  **Presentation Layer (`main.c`):** Handles CLI menus, user inputs, and file dialogs.

2.  **Orchestration Layer (`file_crypto.c`):** Manages file streams, buffering, and padding (PKCS#7).

3.  **Cryptographic Primitives (`crypto_aes.c`, `sha256.c`):** Pure mathematical implementations of the algorithms.

### 3.2. The Encryption Pipeline

The data flow follows a strict "Input ➡️ Process ➡️ Output" pipeline:

**Step-by-Step Flow:**

1.  **Key Derivation (KDF):**

    -   User inputs a raw password (string).

    -   The **SHA-256** engine processes this string to produce a 256-bit hash.

    -   The first 128 bits (16 bytes) of this hash are extracted to serve as the **AES Secret Key**.

2.  **File Streaming:**

    -   The system opens the source file in `binary` mode.

    -   Data is read in fixed **16-byte blocks**.

    -   If the last block is smaller than 16 bytes, **PKCS#7 padding** is added to complete the block.

3.  **Core Encryption:**

    -   Each 16-byte block is passed to the `aes_encrypt_block` function.

    -   The function applies Substitution (S-Box), Shifting, and Mixing operations.

    -   The transformed block (ciphertext) is written immediately to the output file.

### 3.3. Data Flow Diagram 

```
[ 👤 USER ]
    │
    ├── (1) Password 🔑 ────────┐
    │                           │
    │                     [ SHA-256 ]
    │                           │
    │                           ▼
    │                    [ 128-bit Key ]
    │                           │
    ├── (2) Input File 📄       │
    │           │               │
    ▼           ▼               ▼
[ READ 16-BYTE BLOCK ] ──▶ [ AES ENGINE ] ──▶ [ 💾 WRITE TO DISK ]
         ▲                                           │
         └──────────────── (Repeat) ─────────────────┘

```

🔐 4. Cryptography Design
-------------------------

### Password Handling & Key Derivation

Raw passwords are variable in length and often weak. To address this, the system uses **SHA-256**.

-   **Implementation:** A custom, dependency-free implementation of SHA-256.

-   **Purpose:** Converts any password string into a deterministic, fixed-size 32-byte digest.

-   **Key Usage:** The first 16 bytes of this digest are used as the **AES-128 Secret Key**.

### AES-128 (Educational Implementation)

The core encryption engine is a simplified implementation of **AES-128 (Rijndael)**.

-   **Block Size:** 128-bit (16 bytes).

-   **Mode of Operation:** ECB (Electronic Codebook) style processing.

-   **Structure:** Implements standard AES transformations including SubBytes (S-Box), ShiftRows, and AddRoundKey.

📂 5. File Encryption & Decryption
----------------------------------

The system handles files in **binary mode** to ensure support for all file types (images 🖼️, PDFs 📄, text 📝).

-   **Reading:** Files are read in 16-byte chunks.

-   **Padding:** PKCS#7-style logic is applied to handle files that are not perfect multiples of the block size.

-   **Output:** Encrypted files are saved with a `.enc` extension, and decrypted files are restored with a `.dec` extension.

📁 6. Project Folder Structure
------------------------------

The codebase is modular, promoting readability and maintainability.


```
SecureCrypt/
├── 📄 main.c           // Entry point and menu logic
├── 🔐 crypto_aes.c     // AES encryption/decryption logic
├── 📜 crypto_aes.h     // AES headers
├── 🛡️ sha256.c         // SHA-256 hashing implementation
├── 📜 sha256.h         // SHA-256 headers
├── 💾 file_crypto.c    // File I/O and padding logic
├── 🛠️ utils.c          // Helpers (Hex printing, GUI dialogs)
├── 📜 utils.h          // Utility headers
└── 📝 README.md        // Documentation

```

⚙️ 7. How to Compile & Run
--------------------------

The project uses standard GCC and requires no external libraries.

**Compilation:**

Bash

```
gcc main.c crypto_aes.c sha256.c file_crypto.c utils.c -o securecrypt

```

**Execution:**

Bash

```
./securecrypt

```

💻 8. Sample Usage
------------------

Upon running the program, the user is presented with the main menu:

Plaintext

```
===== 🛡️ SecureCrypt =====
1. Encrypt
2. Decrypt
3. Exit
Enter choice: 1

> Select Input Type:
1. Text Input
2. File Input (Select File) 📂

```

-   **Encryption:** The user selects a file, enters a password, and the system generates `filename.enc`.

-   **Decryption:** The user selects the `.enc` file, enters the *same* password, and the system restores the original content.

⚠️ 9. Security Considerations & Limitations
-------------------------------------------

**Important Note:** This project is an **educational implementation** intended to demonstrate cryptographic *concepts*. It is **not** production-ready security software.

1.  **ECB Mode:** The current implementation uses Electronic Codebook (ECB) mode. In production, this is considered insecure because identical plaintext blocks produce identical ciphertext blocks (leaking patterns).

2.  **No Salt/IV:** Industrial systems use random Salts for hashing and Initialization Vectors (IVs) for encryption to prevent rainbow table attacks. This project omits them to keep the logic beginner-friendly.

3.  **Side-Channel Attacks:** The code is not hardened against timing attacks or power analysis.

🎓 10. Learning Outcomes
------------------------

Developing this project provided hands-on experience in:

-   **Modular C Design:** Structuring a project across multiple header and source files.

-   **Bitwise Operations:** Heavily used in SHA-256 and AES transformations.

-   **Memory Safety:** Managing buffers and pointers to prevent leaks or overflows.

-   **System Calls:** Using `popen` to integrate OS-native file dialogs.

-   **Algorithm Implementation:** Translating mathematical specs (NIST standards) into working code.

🚀 11. Future Improvements
--------------------------

-   Implement **CBC (Cipher Block Chaining)** mode for better security.

-   Add **PBKDF2** for stronger password hashing (slowing down brute-force attacks).

-   Implement a **Command Line Arguments** mode (e.g., `./securecrypt -e file.txt`).

-   Add a progress bar for large file operations 📊.0