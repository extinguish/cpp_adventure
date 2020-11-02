//
// Created by guoshichao on 2020/6/23.
//

#include <unistd.h>
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

using namespace std;

template<typename T>
class ThreadQueue {
private:
    mutable std::mutex mut;
    std::queue<T> data_queue;
    std::condition_variable data_cond;
    int dataSize;
public:
    ThreadQueue() {}

    ~ThreadQueue() {
    }

    ThreadQueue(ThreadQueue const &other) {
        std::lock_guard<std::mutex> lk(other.mut);
        data_queue = other.data_queue;
    }

    void push(T new_value) {
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(new_value);
        data_cond.notify_one();
        dataSize++;
    }

    void wait_and_pop(T &value) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this] { return !data_queue.empty(); });
        value = data_queue.front();
        data_queue.pop();
        dataSize--;
    }

    std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> lk(mut);
        auto now = std::chrono::system_clock::now();
        data_cond.wait_until(lk, now + std::chrono::milliseconds(1000), [this] { return !data_queue.empty(); });
        if (data_queue.empty()) {
            printf("!!!!!!!!!!!!!!!!!!the timeout after the queue are empty\n");
            return nullptr;
        }
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        dataSize--;
        return res;
    }

    bool try_pop(T &value) {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
            return false;
        value = data_queue.front();
        data_queue.pop();
        dataSize--;
        return true;
    }

    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        dataSize--;
        return res;
    }

    bool empty() const {
        return data_queue.empty();
    }

    int size() const {
        return data_queue.size();
    }
};

typedef struct {
    uint64_t timeStamp;
    uint32_t frameSize;
    uint8_t frameType; // I_FRAME : 1; P_FRAME : 2; B_FRAME : 3; A_FRAME: 4; PENETRATE_FRAME
    uint8_t placeHolder;
} AVFrameInfo;

typedef struct {
    AVFrameInfo frameInfo;
    uint8_t frameData[1024];
} AVFrame;

ThreadQueue<AVFrame *> mFrameQueue;


int main() {
    AVFrame *frame = static_cast<AVFrame *>(malloc(sizeof(AVFrame)));
    AVFrame *frame1 = static_cast<AVFrame *>(malloc(sizeof(AVFrame)));
    AVFrame *frame2 = static_cast<AVFrame *>(malloc(sizeof(AVFrame)));
    AVFrame *frame3 = static_cast<AVFrame *>(malloc(sizeof(AVFrame)));
    mFrameQueue.push(frame);
    mFrameQueue.push(frame1);
    mFrameQueue.push(frame2);
    mFrameQueue.push(frame3);

    // test the ThreadQueue timeout func
    for (;;) {
        std::shared_ptr<AVFrame *> videoFramePtr = mFrameQueue.wait_and_pop();
        if (videoFramePtr == nullptr) {
            printf("unexpected exception happened!!! channel[%d] --> receive null video frame\n");
            break;
        }
        AVFrame *videoFrame = *videoFramePtr;
        printf("receive audio non-empty av frame\n");

        free(videoFrame);
        usleep(1000 * 1000);
    }
}


