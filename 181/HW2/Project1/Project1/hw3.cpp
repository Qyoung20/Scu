#include <iostream>
#include <vector>
#include <bitset>

std::vector<int> DecimalToBinary(int number, int n) {
    // This function takes two integer inputs: number and n.
    // It returns a vector of length n, which is the binary representation of the given number.
    std::bitset<32> binary_representation(number);
    std::vector<int> binary_vector(n);

    for (int i = 0; i < n; i++) {
        binary_vector[n - i - 1] = binary_representation[i];
    }

    return binary_vector;
}

std::vector<int> ConvertBitArraytoInt(const std::vector<int>& k, int n) {
    // This function takes an array of bits (k) and an integer (n).
    // It returns a vector of integers, where each group of n bits from k is converted to its decimal representation.
    int array_size = k.size();
    std::vector<int> decimal_array(array_size / n);

    for (int i = 0; i < array_size; i += n) {
        int decimal_number = 0;
        for (int j = 0; j < n; j++) {
            decimal_number = (decimal_number << 1) | k[i + j];
        }
        decimal_array[i / n] = decimal_number;
    }

    return decimal_array;
}

std::vector<int> RC4_keystream_generator(int n, int l, const std::vector<int>& secret_key) {
    // This function generates the RC4 keystream.
    // Inputs:
    // n: Integer, representing the bit size of the elements in the S-box.
    // l: Integer, representing the length of plaintext or ciphertext.
    // secret_key: Vector of integers, representing the secret key as an array of bits.

    std::vector<int> S(1 << n), keystream(n * l);
    int key_length = secret_key.size();
    int i, j;

    // Initialize S-box
    for (i = 0; i < (1 << n); i++) {
        S[i] = i;
    }

    // Key-scheduling algorithm (KSA)
    j = 0;
    for (i = 0; i < (1 << n); i++) {
        j = (j + S[i] + secret_key[i % key_length]) % (1 << n);
        std::swap(S[i], S[j]);
    }

    // Pseudo-random generation algorithm (PRGA)
    i = j = 0;
    for (int k = 0; k < n * l; k++) {
        i = (i + 1) % (1 << n);
        j = (j + S[i]) % (1 << n);
        std::swap(S[i], S[j]);
        int t = (S[i] + S[j]) % (1 << n);
        keystream[k] = S[t];
    }

    return keystream;
}
std::vector<int> RC4_encrypt(const std::vector<int>& plaintext, const std::vector<int>& keystream) {
    int size = plaintext.size();
    std::vector<int> ciphertext(size);

    for (int i = 0; i < size; i++) {
        ciphertext[i] = plaintext[i] ^ keystream[i];
    }

    return ciphertext;
}

std::vector<int> RC4_decrypt(const std::vector<int>& ciphertext, const std::vector<int>& keystream) {
    // Encryption and decryption are the same operation in RC4 (XOR), so we can reuse the encrypt function.
    return RC4_encrypt(ciphertext, keystream);
}

std::vector<int> ConvertIntToBinaryVector(const std::vector<int>& input, int n) {
    int size = input.size();
    std::vector<int> binary_vector(size * n);

    for (int i = 0; i < size; i++) {
        std::vector<int> temp = DecimalToBinary(input[i], n);
        for (int j = 0; j < n; j++) {
            binary_vector[i * n + j] = temp[j];
        }
    }

    return binary_vector;
}
int main() {
    int n = 8;
    int l = 24;
    std::vector<int> secret_key = { 1, 0, 1, 1, 1, 0, 0, 1 , 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1,
1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0,
0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1,
1, 0, 1, 0, 0, 0, 1 };
    std::vector<int> cipher_text = { 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0,
0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0,
0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0,
1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0,
0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1,
0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0,
1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1,
1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0 };
    std::vector<int> c_k = ConvertBitArraytoInt(cipher_text, n);
    std::vector<int> s_k = ConvertBitArraytoInt(secret_key, n);
    std::vector<int> keystream = RC4_keystream_generator(n, l , s_k);
    std::cout << "Keystream: ";
    for (int i = 0; i < keystream.size(); ++i) {
        std::cout << keystream[i] << ", ";
    }
    std::cout << std::endl;
    std::vector<int> message = RC4_decrypt(c_k, keystream);
    std::cout << "Message: ";
    for (int i = 0; i < message.size(); ++i) {
        std::cout << message[i] << ", ";
    }
    std::cout << std::endl;
   /* int number = 100;
    std::vector<int> binary_vector = DecimalToBinary(number, n);
    std::cout << "Binary test: ";
    for (int i = 0; i < binary_vector.size(); i++) {
        std::cout << binary_vector[i];
    }
    std::cout << std::endl;

    std::vector<int> binary_keystream = ConvertIntToBinaryVector(keystream, n);
    std::cout << "Binary Keystream: ";
    for (int i = 0; i < binary_keystream.size(); i++) {
        std::cout << binary_keystream[i];
    }
    std::cout << std::endl;*/
    return 0;
}