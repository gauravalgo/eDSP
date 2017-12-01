//
// Created by Mohammed Boujemaoui on 22/10/2017.
//

#ifndef EDSP_CROSSCORRELATION_H
#define EDSP_CROSSCORRELATION_H

#include "config.h"
#include "math/complex.h"
#include "transforms/fft.h"
#include "transforms/ifft.h"
EDSP_BEGING_NAMESPACE
    namespace frequency {
        template<typename T, std::size_t N = 1024>
        class AutoCorrelation  {
        public:
            explicit AutoCorrelation() = default;
            ~AutoCorrelation() = default;

            template<typename Container>
            typename std::enable_if<std::is_same<typename Container::value_type,
                    T>::value, Container>::type
            compute(const Container& input) {
                const auto& fft_data = fft.compute(math::complex::real_to_complex(input));
                std::transform(fft_data.begin(), fft_data.end(), fft_data.begin(), [](std::complex<T>& value) {
                    auto tmp = static_cast<T>(std::abs(value));
                    return std::complex<T>(tmp * tmp, 0);
                });

                const auto& out = ifft.compute(fft_data);
                Container data(input.size());
                std::transform(out.begin(), out.end(), data.begin(), [](const std::complex<T>& value) {
                    return value.real();
                });
                return data;
            };
        private:
            using complex_array = std::vector<std::complex<T>>;
            transforms::FFT<T, N>  fft;
            transforms::IFFT<T, N> ifft;
        };
    }
EDSP_END_NAMESPACE


#endif //EDSP_CROSSCORRELATION_H