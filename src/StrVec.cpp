//
// Created by guoshichao on 18-10-11.
//
/// the following file are excerpt from "Cpp Primer"

#include <memory>
#include <iostream>
#include <string>

class StrVec {
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {

    }

    StrVec(const StrVec &);

    StrVec &operator=(const StrVec &);

    ~StrVec();

    void push_back(const std::string &);

    size_t size() const {
        return first_free - elements;
    }

    size_t capacity() const {
        return cap - elements;
    }

    std::string *begin() const {
        return elements;
    }

    std::string *end() const {
        return first_free;
    }

private:
    static std::allocator <std::string> alloc;

    /// 检查当前的StrVec的存储空间，是否需要重新扩大存储空间
    /// 类似于Java当中的ArrayList检查底层数组容量是否合适，不合适就进行扩容
    void chk_n_alloc() {
        if (size() == capacity()) {
            reallocate();
        }
    }

    std::pair<std::string *, std::string *> alloc_n_cpy(const std::string *, const std::string *);

    void free();

    void reallocate();

    /// 指向数组首元素
    std::string *elements;
    /// 指向数组的第一个空闲元素
    std::string *first_free;
    /// 指向数组尾部之后的元素
    std::string *cap;

};

int main(void) {


}

