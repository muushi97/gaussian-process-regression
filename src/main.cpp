#include <iostream>
#include <random>
#include <fstream>
#include <functional>

#include "tensor/tensor.hpp"
#include "gpr.hpp"
#include "gnuplotter/writer.hpp"

void GPR_test() {
    std::random_device seed_gen;
    std::mt19937_64 engine(seed_gen());

    double sigma = 0.2;  // 標準偏差
    double sigma2 = sigma * sigma;  // 分散
    int N = 5;
    int NN = 100;

    std::normal_distribution<> dist(0.0, sigma);
    GPR gpr(sigma2, GPR::se);
    //GPR gpr(sigma2, GPR::m52);

    std::function<double(double)> func = [] (double x) { return std::sin(x); };

    /* add train data */ {
        std::ofstream file("train-data.csv");
        for (int i = 0; i < N; i++) {
            tensor<double> x{1}; x() = (3.14 * 2 / static_cast<double>(N-1)) * i;
            double y = func(x()) + dist(engine);
            gpr.add_train_data(x, y);
            file << x() << " " << y << std::endl;
        }
    }

    /* test */ {
        std::ofstream orig("origin-data.csv");
        std::ofstream file("test-data.csv");
        for (int i = 0; i < NN; i++) {
            tensor<double> x{1}; x() = (3.14 * 2 / static_cast<double>(NN-1)) * i;
            auto ev = gpr.EV(x);
            file << x() << " " << ev[0] << " " << 2.0 * std::sqrt(ev[1]) << std::endl;
            orig << x() << " " << func(x()) << std::endl;
        }
    }

    /* plot */ {
        plt_writer writer("hoge.plt");
        writer.write_command("plot 'train-data.csv' with points");
        writer.write_command("replot 'origin-data.csv' with lines");
        writer.write_command("replot 'test-data.csv' with errorbars, 'test-data.csv' notitle with lines");
        writer.write_command("pause -1");
        writer.run();
    }
}

int main() {
    GPR_test();
    return 0;
}

