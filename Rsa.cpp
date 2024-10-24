#include <iostream>
#include <string>
#include <vector>
#include <random> //для рандомных ключей
#include <cstdint>  // Для uint64_t

using std::cout;
using std::cin;

//Нод(алгоритм евклида?)
uint64_t Nod(uint64_t a, uint64_t b) {
    uint64_t temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

//Ключи
void generateKey(uint64_t& e, uint64_t& d, uint64_t& n) {
    std::vector<uint64_t> primes = {
        3, 5, 7, 11, 13, 17, 19, 23, 31, 37, 41, 61, 101, 109, 113, 181,
        199, 211, 257, 281, 313, 409, 421, 503, 571, 613, 631, 661, 719,
        761, 829, 911, 1013, 1051, 1201, 1301, 1361, 1429, 1531, 1601,
        1741, 1861, 1901, 1999, 2341, 2521, 2617, 2917, 3209, 3449, 3613,
        4253, 4621, 4789, 5471, 5659, 6427, 7741, 8089, 9127, 9551, 10513,
        11113, 12323, 14741, 17551, 18713, 21113, 21841, 22541, 23371,
        25577, 26399, 27499, 29537, 36749, 44471, 57599, 64289
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, primes.size() - 1);

    uint64_t p = primes[distrib(gen)];
    uint64_t q;

    do {
        q = primes[distrib(gen)];
    } while (p == q);

    n = p * q;
    uint64_t phi = (p - 1) * (q - 1);

    e = 3;
    while (Nod(e, phi) != 1) {
        e++;
    }

    uint64_t k = 1;
    while ((1 + k * phi) % e != 0) {
        k++;
    }
    d = (1 + k * phi) / e;
}

// возведение в степень по модулю
uint64_t PowNum(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t res = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

//шифрование
std::vector<uint64_t> Rsa(const std::string& mes, uint64_t e, uint64_t n) {
    std::vector<uint64_t> MesASCII;
    for (char c : mes) {
        uint64_t num = static_cast<uint64_t>(c);
        MesASCII.push_back(PowNum(num, e, n));
    }
    return MesASCII;
}

//рассшифрование
std::string DeRsa(const std::vector<uint64_t>& mes, uint64_t d, uint64_t n) {
    std::string MesASCII;
    for (uint64_t c : mes) {
        uint64_t num = PowNum(c, d, n);
        MesASCII += static_cast<char>(num);
    }
    return MesASCII;
}

int main() {
    std::string message;
    std::getline(cin, message);

    uint64_t e, d, n;
    cout << "Your message: " << message << "\n";

    generateKey(e, d, n);
    cout << "e: " << e << "\n"<< "d: " << d << "\n"<< "n: " << n << "\n";

    std::vector<uint64_t> mess = Rsa(message, e, n);
    cout << "After Rsa:\n";
    for (uint64_t c : mess) {
        cout << c;
    }

    std::string DeRsaMes = DeRsa(mess, d, n);
    cout << "\nAfter DeRsa:\n" << DeRsaMes << "\n";

    return 0;
}
