#ifndef DECODERS_MPG123_HPP
#define DECODERS_MPG123_HPP

#include "alure2.h"

namespace alure {

class Mpg123DecoderFactory : public DecoderFactory {
    bool mIsInited;

public:
    Mpg123DecoderFactory();
    ~Mpg123DecoderFactory() override final;

    SharedPtr<Decoder> createDecoder(UniquePtr<std::istream> &file) override final;
};

} // namespace alure

#endif /* DECODERS_MPG123_HPP */
