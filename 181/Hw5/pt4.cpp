#include <bitset>
#include <array>
using namespace std;
// Define the state array dimensions
constexpr size_t x_dim = 5;
constexpr size_t y_dim = 5;
constexpr size_t z_dim = 64;

// Define the state array type
using state_array = std::array<std::array<std::bitset<z_dim>, y_dim>, x_dim>;

state_array pi_function(const state_array& ain) {
    state_array aout;

    for (size_t x = 0; x < x_dim; ++x) {
        for (size_t y = 0; y < y_dim; ++y) {
            for (size_t z = 0; z < z_dim; ++z) {
                aout[(x + 3 * y) % 5][x][z] = ain[x][y][z];
            }
        }
    }

    return aout;
}

int main() {
    // Initialize ain with some data...
    state_array ain;

    // Apply pi function
    state_array aout = pi_function(ain);

    // Extract and print desired bits
    cout << "Bits aout[4][3][9...18] are: ";
    for (size_t z = 9; z < 19; ++z) {
        cout << aout[4][3][z];
    }
    cout << '\n';

    cout << "Bits aout[3][1][15...24] are: ";
    for (size_t z = 15; z < 25; ++z) {
        cout << aout[3][1][z];
    }
    cout << '\n';

    return 0;
}
