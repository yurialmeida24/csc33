#include <iostream>
#include <thread>
#include <chrono>
#include <stdexcept>

class Fibonacci {
public:
    Fibonacci(int n) : n(n), result(0) {}

    void operator()() {
        if (n <= 2) {
            result = 1;
        } else {
            Fibonacci fib1(n - 1);
            std::thread t1(std::ref(fib1));

            long fib2 = computeFibonacci(n - 2);

            t1.join();
            result = fib1.getResult() + fib2;
        }
    }

    long getResult() const {
        return result;
    }

    static long computeFibonacci(int n) {
        if (n == 1 || n == 2) {
            return 1;
        }
        return computeFibonacci(n - 1) + computeFibonacci(n - 2);
    }

private:
    int n;
    long result;
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <n>" << std::endl;
        return 1;
    }

    int n = std::stoi(argv[1]);

    try {
        auto start = std::chrono::high_resolution_clock::now();
        Fibonacci fib(n);
        std::thread t1(std::ref(fib));
        t1.join();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Parallel-Fibonacci: " << fib.getResult() << "\tTime: " << duration.count() << " seconds" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        long result = Fibonacci::computeFibonacci(n);
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << "Sequential-Fibonacci: " << result << "\tTime: " << duration.count() << " seconds" << std::endl;
    } 
    catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
