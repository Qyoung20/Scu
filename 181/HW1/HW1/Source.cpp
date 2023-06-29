#include <iostream>
#include <string>

std::string vigenere_encrypt(const std::string& plaintext, const std::string& keyword) {
    std::string ciphertext = "";
    int keyword_length = keyword.length();

    for (size_t i = 0; i < plaintext.length(); ++i) {
        char plaintext_char = plaintext[i];
        char keyword_char = keyword[i % keyword_length];

        char encrypted_char = 'A' + (plaintext_char - 'A' + keyword_char - 'A') % 26;
        ciphertext += encrypted_char;
    }

    return ciphertext;
}

std::string vigenere_decrypt(const std::string& ciphertext, const std::string& keyword) {
    std::string plaintext = "";
    int keyword_length = keyword.length();

    for (size_t i = 0; i < ciphertext.length(); ++i) {
        char ciphertext_char = ciphertext[i];
        char keyword_char = keyword[i % keyword_length];

        char decrypted_char = 'A' + (ciphertext_char - keyword_char + 26) % 26;
        plaintext += decrypted_char;
    }

    return plaintext;
}

int main() {
    std::string plaintext = "TESTMESSAGE";
    std::string keyword = "KEYWORD";
    std::string ciphertext = vigenere_encrypt(plaintext, keyword);

    std::cout << "Plaintext: " << plaintext << std::endl;
    std::cout << "Ciphertext: " << ciphertext << std::endl;

    std::string decrypted_text = vigenere_decrypt(ciphertext, keyword);
    std::cout << "Decrypted text: " << decrypted_text << std::endl;

    return 0;
}
