// reading a text file
#include <vector>
#include "Header.hpp"


std::vector<char> getVec1(const std::vector<char> vec, int i, int j, int length, int width) {

    std::vector<char> res(4);

    for (int k = 0; k < 4; ++k) {

        if (i + k < length) {
            res[k] = vec[(i + k) * width + j];
        }
    }
    return res;
}

std::vector<char> getVec2(const std::vector<char> vec, int i, int j, int length, int width) {

    std::vector<char> res(4);

    for (int k = 0; k < 4; ++k) {

        if (i + k < length && j + k < width) {
            res[k] = vec[(i + k) * width + j + k];
        }
    }
    return res;
}

std::vector<char> getVec3(const std::vector<char> vec, int i, int j, int length, int width) {

    std::vector<char> res(4);

    for (int k = 0; k < 4; ++k) {

        if (j + k < width) {
            res[k] = vec[i * width + j + k];
        }
    }
    return res;
}

std::vector<char> getVec4(const std::vector<char> vec, int i, int j, int length, int width) {

    std::vector<char> res(4);

    for (int k = 0; k < 4; ++k) {

        if (i - k >= 0 && j + k < width) {
            res[k] = vec[(i - k) * width + j + k];
        }
    }
    return res;
}

std::vector<char> getVec5(const std::vector<char> vec, int i, int j, int length, int width) {

    std::vector<char> res(4);

    for (int k = 0; k < 4; ++k) {

        if (i - k >= 0) {
            res[k] = vec[(i - k) * width + j];
        }
    }
    return res;
}

std::vector<char> getVec6(const std::vector<char> vec, int i, int j, int length, int width) {

    std::vector<char> res(4);

    for (int k = 0; k < 4; ++k) {

        if (i - k >= 0 && j - k >= 0) {
            res[k] = vec[(i - k) * width + j - k];
        }
    }
    return res;
}

std::vector<char> getVec7(const std::vector<char> vec, int i, int j, int length, int width) {

    std::vector<char> res(4);

    for (int k = 0; k < 4; ++k) {

        if (j - k >= 0) {
            res[k] = vec[i * width + j - k];
        }
    }
    return res;
}

std::vector<char> getVec8(const std::vector<char> vec, int i, int j, int length, int width) {

    std::vector<char> res(4);

    for (int k = 0; k < 4; ++k) {

        if (i + k < length && j - k >= 0) {
            res[k] = vec[(i + k) * width + j - k];
        }
    }
    return res;
}