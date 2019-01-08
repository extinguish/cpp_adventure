//
// Created by guoshichao on 18-9-30.
//
/// basic file operations
#include <iostream>
#include <fstream>

using namespace std;

void create_file_test() {
    ofstream my_file;
    my_file.open("../../test_dir/cpu_usage"); // this operation will create a new file named as "cpu_usage" under current directory
    my_file << "new line into cpu usage file" << endl;
    my_file.close();
}

#include <string>

void dump_file_content_test() {
    string line;
    // ifstream的参数不接收相对路径，只能是绝对路径
    ifstream file_to_open("/home/guoshichao/scguo_cache/cpu_usage");
    if (file_to_open.is_open()) {
        while (getline(file_to_open, line)) {
            cout << line << endl;
        }
        file_to_open.close();
    } else {
        cout << "fail to open the file" << endl;
    }
}


int main() {
    create_file_test();
    dump_file_content_test();
    return 1;
}


