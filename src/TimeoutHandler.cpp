////
//// Created by guoshichao on 19-4-13.
////
//
///// implement timeout handler
///// we wait on specified things to happen
///// and if reach timeout, then send a signal to notify this timeout event
//
//#include <iostream>
//#include <thread>
//#include <chrono>
//
//class Timer {
//    bool clear = false;
//
//public:
//    void setTimeout(auto function, int delay);
//
//    void setInterval(auto function, int interval);
//
//    void stop();
//
//};
//
////void Timer::setTimeout(auto function, int delay) {
////    this->clear = false;
////    std::thread t([=]() {
////        if (this->clear) {
////            return;
////        }
////        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
////        if (this->clear) {
////            return;
////        }
////        function();
////    });
////    t.detach();
////}
//
////void Timer::setInterval(auto function, int interval) {
////    this->clear = false;
////    std::thread t([=]() {
////        while (true) {
////            if (this->clear) return;
////            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
////            if (this->clear) return;
////            function();
////        }
////    });
////    t.detach();
////}
//
//void Timer::stop() {
//    this->clear = true;
//}
//
//int main(int argc, char **argv) {
//
//
//}
//
