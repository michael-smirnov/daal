#include <iostream>
#include <decomposition/pca.hpp>
#include <data_management/table.hpp>

int main()
{
    using namespace onedal::decomposition;
    auto params = pca::Params()
        .set_n_components(3);

    float data[] = {
        1.f, 2.f,
        0.f, 0.f, 
        -1.f, -2.f,
    };

    auto data_table = onedal::data_management::Table(data, 3, 2);

    std::cout << "pca number of components = " << params.get_n_components() << std::endl;

    return 0;
}
