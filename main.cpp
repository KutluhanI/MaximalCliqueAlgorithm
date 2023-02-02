#include <iostream>
#include <math.h>
#include <vector>
#include <bitset>
#include <unordered_map>

using namespace std;

std::vector<int> clique;
int nodeCount;

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

//std::vector<int> memory; // For simplerVersion uncomment this.
std::unordered_map<std::pair<int, int>, bool, pair_hash> edgeHash;

int calculateHammingDistance(std::bitset<64>& n1, std::bitset<64>& n2) {
    return (n1 ^ n2).count();
}

std::bitset<64> intToBinary(int n) {
    return std::bitset<64>(n);
}

bool isClique(int x) {
    for (int i = 1; i < x; i++)  {
        for (int j = i+1; j < x; j++) {
            if (!edgeHash[{clique[i], clique[j]}] && !edgeHash[{clique[j], clique[i]}]) {
                return false;
            }
        }
    }
    return true;
}

std::unordered_map<std::pair<int, int>, int, pair_hash> memo;

int getMaximalCliqueSize(int i = 0, int l = 1) {
    int maxSize = 0;

    for (int j = i; j < nodeCount + 1; j++) {
        if (memo.count({j, l})) {
            return memo[{j, l}];
        }

        clique.resize(l+1);

        clique[l] = j;
        if (isClique(l+1)) {
            maxSize = std::max(maxSize, l);
            memo[{j, l}] = maxSize;
            maxSize = std::max(maxSize, getMaximalCliqueSize(j + 1, l + 1));
        }
    }

    return maxSize;
}

//int simplerVersion() {
//    int count=1;
//    int size = 1;
//    for (int i=0; i<nodeCount; i++) {
//        int a = 0;
//        for (int j=0; j<size; j++) {
//            if (edgeHash[{i, memory[j]}] || edgeHash[{memory[j], i}]) {
//                a ++;
//                if (a == size && !std::count(memory.begin(), memory.end(), i)) {
//                    std::cout << "putting "<< i << " to the memo"<< std::endl;
//                    memory.push_back(i);
//                    size ++;
//                    count++;
//                }
//            }
//        }
//    }
//    return count;
//}

int main() {
    int binaryStringLength;
    std::cout << "Please enter the length of binary string:";
    std::cin >> binaryStringLength;

    while (binaryStringLength == 0) {
        std::cout << "Length of binary string can't be zero. Please enter the length of binary string again: ";
        std::cin >> binaryStringLength;
    }

    int max = pow(2, binaryStringLength) - 1;
    int minimumDistance;
    std::cout << "Please enter the d (minimum distance):";
    std::cin >> minimumDistance;

    nodeCount = pow(2, binaryStringLength);

    for (int a = 0; a <= max; a++) {
        for (int b = a + 1; b <= max; b++) {
            bitset<64> aToBinary = intToBinary(a);
            bitset<64> bToBinary = intToBinary(b);
            int calculatedHammingDistance = calculateHammingDistance(aToBinary, bToBinary);

            if (calculatedHammingDistance >= minimumDistance) {
                edgeHash[{a, b}] = true;
            }
        }
    }

//  memory.push_back(0); // For simplerVersion uncomment this.
    int maximalCliqueSize = getMaximalCliqueSize();
    cout << "The size of the maximal clique is: " << maximalCliqueSize << endl;
    return 0;
}