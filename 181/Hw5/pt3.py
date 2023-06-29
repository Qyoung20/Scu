import numpy as np

# Define rho offset matrix
rho_offsets = np.array([
    [0, 36, 3, 41, 18],
    [1, 44, 10, 45, 2],
    [62, 6, 43, 15, 61],
    [28, 55, 25, 21, 56],
    [27, 20, 39, 8, 14]
])

def rho_function(input_array):
    # Create output array of same shape as input
    output_array = np.zeros_like(input_array)
    
    # Apply rho transformation
    for x in range(5):
        for y in range(5):
            offset = rho_offsets[x, y]
            for z in range(64):
                output_array[x, y, (z + offset) % 64] = input_array[x, y, z]
    
    return output_array

# Binary string provided
binary_string = """
0011000100110010001100110011010000110101001101100011011100111000001110010011000000110001001100100011001100110100001101010011011000110111001110000011100100110000001100010011001000110011001101000011010100110110001101110011100000111001001100000011000100110010001100110011010000110101001101100011011100111000001110010011000000110001001100100011001100110100001101010011011000110111001110000011100100110000001100010011001000110011001101000011010100110110001101110011100000111001001100000011000100110010001100110011010000110101001101100011011100111000001110010011000000110001001100100011001100110100001101010011011000110111001110000011100100110000001100010011001000110011001101000011010100110110001101110011100000111001001100000011000100110010001100110011010000110101001101100011011100111000001110010011000000110001001100100011001100110100001101010011011000110111001110000011100100110000001100010011001000110011001101000011010100110110001101110011100000111001001100000011000100110010001100110011010000110101001101100011011100111000001110010011000000110001001100100011001100110100001101010011011000110111001110000011100100110000001100010011001000110011001101000011010100110110001101110011100000111001001100000011000100110010001100110011010000110101001101100011011100111000001110010011000000110001001100100011001100110100001101010011011000110111001110000011100100110000
"""

# Remove whitespaces and newlines
binary_string = binary_string.replace('\n', '').replace(' ', '')

# Convert to 3D array
input_array = np.array([[[int(binary_string[i + 64*j + 320*k]) for i in range(64)] for j in range(5)] for k in range(5)])

# Apply rho function
output_array = rho_function(input_array)

# Extract and print desired bits
bits_4_3_9_to_18 = output_array[4, 3, 9:19]
bits_3_1_15_to_24 = output_array[3, 1, 15:25]

bits_4_3_9_to_18_str = ''.join(map(str, bits_4_3_9_to_18))
bits_3_1_15_to_24_str = ''.join(map(str, bits_3_1_15_to_24))

print("Bits aout[4][3][9...18] are: ", bits_4_3_9_to_18_str)
print("Bits aout[3][1][15...24] are: ", bits_3_1_15_to_24_str)