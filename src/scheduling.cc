#include "scheduling.h"

#include <iostream>

std::vector<std::vector<double>>
scheduling(const std::vector<std::vector<double>>& origin_models) {
    std::vector<std::vector<double>> rm(origin_models);

    // for (auto om : origin_models) {
    //     for (auto om_data : om) {
    //         std::cout << om_data << " ";
    //     }
    //     std::cout << std::endl;
    // }

    double middian_sum = 0;
    std::vector<double> sum_each(origin_models.size());
    for (int i = 0; i < origin_models.size(); i++) {
        double sum_t = 0;
        for (int j = 0; j < origin_models[i].size(); j++) {
            middian_sum += origin_models[i][j];
            sum_t += origin_models[i][j];
        }
        sum_t /= origin_models[i].size();
        sum_each[i] = sum_t;
    }
    middian_sum /= origin_models.size();

    // for (auto i : sum_each)
    //     std::cout << i << " ";
    // std::cout << std::endl;
    // std::cout << middian_sum << std::endl;

    return rm;
}
