#include <iostream>

void InvMatrix(float src[][3], float dst[][3]);

int main()
{
    float matrix[3][3] = {
        {-1,-2, 2},
        { 2, 1, 1},
        { 3, 4, 5}
    };

    float inverse[3][3];

    try {
        InvMatrix(matrix, inverse);

        for (int r = 0; r < 3; ++r)
        {
            for (int c = 0; c < 3; ++c)
                std::cout << inverse[r][c] << " ";
            std::cout << "\n";
        }
    } catch (const char* errorMessage) {
        std::cout << errorMessage << "\n";
    }
}


float determinant(float matrix[][3])
{
    float det = 0;
    for (int i = 0; i < 3; ++i)
        det += matrix[0][i]*matrix[1][(i+1)%3]*matrix[2][(i+2)%3]
               - matrix[2][i]*matrix[1][(i+1)%3]*matrix[0][(i+2)%3];
    return det;
}

float minor(float matrix[][3], int row, int col)
{
    int ir = row == 1 ? -1 : 1;
    int ic = col == 1 ? -1 : 1;
    float a = matrix[(row+ir+3)%3][(col+ic+3)%3];
    float b = matrix[(row+ir+3)%3][(col-ic+3)%3];
    float c = matrix[(row-ir+3)%3][(col+ic+3)%3];
    float d = matrix[(row-ir+3)%3][(col-ic+3)%3];
    return a*d - b*c;
}

void getCofactorMatrix(float src[][3], float dst[][3])
{
    bool neg = false;
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
        {
            dst[r][c] = minor(src, r, c) * (neg ? -1 : 1);
            neg = !neg;
        }
}

void swapValue(float& a, float& b)
{
    float temp = a;
    a = b;
    b = temp;
}

void transpose(float matrix[][3])
{
    for (int r = 0; r < 3; ++r)
        for (int c = r+1; c < 3; ++c)
            if (r != c)
                swapValue(matrix[r][c], matrix[c][r]);
}

void InvMatrix(float src[][3], float dst[][3])
{
    float det = determinant(src);
    if (!det) throw "Singular matrix, cannot inverse.";
    getCofactorMatrix(src, dst);
    transpose(dst);
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            dst[r][c] /= det;
}