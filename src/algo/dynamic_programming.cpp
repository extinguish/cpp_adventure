//
// Created by guoshichao on 18-9-30.
//
/// about the dynamic programming practice
/// 以下是问题描述
///         7
///        3 8
///       8 1 0
///      2 7 4 4
///     4 5 2 6 5
/// 需要求解:在上面的数字三角形中寻找一条从顶部到底边的路径，使得路径上所经过的数字之和最大。
/// 路径上的每一步都只能往左下或 右下走。只需要求出这个最大和即可，不必给出具体路径。
/// 三角形的行数大于1小于等于100，数字为 0 - 99
/// 输入格式:
/// 5 // 表示三角形的行数
/// 7
/// 3 8
/// 8 1 0
/// 2 7 4 4
/// 4 5 2 6 5
/// 然后就是求出最大的和

#include <iostream>
#include <algorithm>

#define MAX 101

using namespace std;

int data_triangle[MAX][MAX];
int max_sum(int i, int j) {
    if (i == j) {
        return data_triangle[i][j];
    }
    int x = max_sum(i + 1, j);
    int y = max_sum(i + 1, j + 1);
    return max(x, y) + data_triangle[i][j];
}

int main() {
    int i, j;
    int line_num = 0;

    cout << "input the line of the triangle";
    cin >> line_num;
    cout << "input the data of the triangle " << endl;

    // 三角形本身是一个等边三角形
    for (i = 1; i <= line_num; i++) {
        for (j = 1; j <= i; j++) {
            cin >> data_triangle[i][j];
        }
    }
    cout << max_sum(3, 3) << endl;
    return 1;
}




