#include <iostream>
#include <random>

#include "tensor/tensor.hpp"
#include "gpr.hpp"

void GPR_test() {
    std::random_device seed_gen;
    std::mt19937_64 engine(seed_gen());
    std::normal_distribution<> dist(0.0, 0.2);
    //GPR gpr(0.2, GPR::se);
    GPR gpr(0.2, GPR::m52);

    //gpr.jordan_test();

    //std::cout << "train" << std::endl;
    int N;
    std::cout << "sumple number >> ";
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        tensor<double> x{1}; x(0) = (3.14 * 2 / static_cast<double>(N-1)) * i;
        double y = std::sin(x(0)) + dist(engine);
        //std::cout << x(0) << ", " << y << std::endl;
        gpr.add_train_data(x, y);
    }

    //std::cout << std::endl << "test" << std::endl;
    //double i = 0.0;
    //do {
    //    std::cout << ">> ";
    //    std::cin >> i;
    //    tensor<double> x{1}; x(0) = i;
    //    auto ev = gpr.EV(x);
    //    std::cout << "E = " << ev[0] << ", " << "V = " << ev[1] << "(" << std::sqrt(ev[1]) << ")" << std::endl;
    //} while(i > 0.0);
    int NN = 100;
    for (int i = 0; i < NN; i++) {
        tensor<double> x{1}; x(0) = (3.14 * 2 / static_cast<double>(NN-1)) * i;
        auto ev = gpr.EV(x);
        //std::cout << "E = " << ev[0] << ", " << "V = " << ev[1] << "(" << std::sqrt(ev[1]) << ")" << std::endl;
        std::cout << x(0) << " " << ev[0] << " " << std::sqrt(ev[1]) << std::endl;
        //khstd::cout << x(0) << " " << ev[0] << " " << ev[1]) << std::endl;
    }
}

int main() {
    GPR_test();
    return 0;
}

