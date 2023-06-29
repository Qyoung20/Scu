ciphertext = """lpiusnwkwcyiezwwcqelxdeizabhvthgwbkjrcfshevgiwxetnxfesgasgxeibgwmldzrewkfr
rtbkmirhngveirorwvhqqsaxslzdvnlavixpqmgpbhvrbluyqxvglayxrqxjzlragalayqxbhc
mbhsgawkuvnhlltmievksgxkeibfzjhvuthlnkioxlmyugytafvhgnnkxcwanlykuvwltfwqdr
gxvpydvgagnakefygknkegmzxjdwfbfznkiexztxzseglaypvrtdesdfbnlmbhwnfwthgfbmzm
bdxzhjgcqkrjmtfocytqbhoinowlhrwgxhaugxehvwyqfytudikmxxhmnkisbjlnisetfhnkie
wsrshxxggpcqkuhopubprtvliqxbpsrcgshulxxljvlzhoohrowkwrqrusvelwutdevhxredbh
jxubkpcwlnlazbvszxoayuinzwluqhnzwlbhrpxlpiusnwkwcyiezwwcqejhgwuqhvmghewlrh
fxfhwfmjtphprwtruqhgasmbdwztvxuopgawwcijrkwgwhve"""

ciphertext = ciphertext.replace("\n", "")

def frequency_analysis(ciphertext, k):
    frequency_vectors = [[] for _ in range(k)]

    for i in range(k):
        frequency_vector = [0] * 26
        for j in range(i, len(ciphertext), k):
            frequency_vector[ord(ciphertext[j]) - ord('a')] += 1
        frequency_vectors[i] = frequency_vector

    return frequency_vectors

k = 5 # Suppose the keyword length is 5
frequency_vectors = frequency_analysis(ciphertext, k)
for i, vec in enumerate(frequency_vectors):
    print(f"Frequency vector {i + 1}: {vec}")
#This program will output the frequency vectors for the given k. You can analyze the vectors and underline every number that is 4 or more.
#To determine the keyword, we can use the distances between A, E, and T in the alphabet (4, 15, and 7) and compute the possible shifts for each histogram. 
#If there's a pattern that emerges, we can use the shifts to determine the keyword. 
#Once we have the keyword, we can use the Vigenere decryption code from question 2 to decrypt the ciphertext and obtain the plaintext.