def read_input_file(filename):
    with open(filename, 'r') as file:
        return file.read().strip()

def inputSHA3(v):
    a = [[[0] * 64 for _ in range(5)] for _ in range(5)]
    for i in range(5):
        for j in range(5):
            for k in range(64):
                a[i][j][k] = v[64 * (5 * j + i) + k]
    return a

def outputSHA3(a):
    v = ['0'] * 1600
    for i in range(5):
        for j in range(5):
            for k in range(64):
                v[64 * (5 * j + i) + k] = a[i][j][k]
    return ''.join(v)

def theta(ain):
    aout = [[[0] * 64 for _ in range(5)] for _ in range(5)]
    for x in range(5):
        for y in range(5):
            for z in range(64):
                aout[x][y][z] = ain[x][y][z] ^ (ain[(x + 1) % 5][y][(z - 1) % 64] & ~ain[(x + 2) % 5][y][(z - 1) % 64])
    return aout

input_data = read_input_file('sha3in.txt')
a_in = inputSHA3(input_data)
a_out = theta(a_in)
requested_bits = a_out[3][1][15:25]

print(''.join(requested_bits))