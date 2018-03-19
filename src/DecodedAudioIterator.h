#ifndef EQULIZER_DECODEDAUDIOITERATOR_H
#define EQULIZER_DECODEDAUDIOITERATOR_H


#include <QtMultimedia/QAudioBuffer>

template<typename SampleType>
class DecodedAudioIterator {
public:
    explicit DecodedAudioIterator(std::vector<QAudioBuffer> *buffer);

    explicit DecodedAudioIterator(std::vector<QAudioBuffer> *buffer, std::size_t frameNumber);

    DecodedAudioIterator operator++(int);

    DecodedAudioIterator &operator++();

    const SampleType &operator*() const;


    bool operator==(const DecodedAudioIterator &rhs) const;

    bool operator!=(const DecodedAudioIterator &rhs) const;

private:
    std::size_t externalPos_;
    std::size_t internalPos_;
    std::vector<QAudioBuffer> *buffer_;
};

template<typename SampleType>
DecodedAudioIterator<SampleType>::DecodedAudioIterator(std::vector<QAudioBuffer> *buffer)
        :buffer_{buffer},
         internalPos_{0},
         externalPos_{0} {
    if (buffer_ == nullptr) {
        internalPos_ = -1;
        externalPos_ = -1;
    }
}

template<typename SampleType>
DecodedAudioIterator<SampleType>::DecodedAudioIterator(std::vector<QAudioBuffer> *buffer, std::size_t frame)
        :buffer_{buffer},
         internalPos_{std::numeric_limits<std::size_t>::max()},
         externalPos_{std::numeric_limits<std::size_t>::max()} {
    if (buffer_ == nullptr) {
        internalPos_ = -1;
        externalPos_ = -1;
        return;
    }
    std::size_t total = 0;
    for (auto &&i: *buffer_) {
        if (total + i.frameCount() >= frame) {
            internalPos_ = frame - total - 1;
            return;
        }
        total += i.frameCount();
        ++externalPos_;
    }
    internalPos_ = -1;
    externalPos_ = -1;
    buffer_ = nullptr;

}

template<typename SampleType>
DecodedAudioIterator<SampleType> DecodedAudioIterator<SampleType>::operator++(int) {
    if (buffer_ == nullptr) {
        return *this;
    }
    DecodedAudioIterator iter{this->buffer_};
    ++(*this);
    return iter;
}

template<typename SampleType>
DecodedAudioIterator<SampleType> &DecodedAudioIterator<SampleType>::operator++() {
    if (buffer_ == nullptr) {
        return *this;
    }

    if (internalPos_ == buffer_->back().frameCount() - 1) {
        internalPos_ = 0;
        ++externalPos_;
    }
    if (externalPos_ == buffer_->size()) {
        externalPos_ = -1;
        internalPos_ = -1;
        buffer_ = nullptr;
        return *this;
    }
    ++internalPos_;
    return *this;
}

template<typename SampleType>
const SampleType &DecodedAudioIterator<SampleType>::operator*() const {
    if (buffer_ == nullptr) {
        throw std::runtime_error{"End iterator dereference"};
    }
    const SampleType *frames = (*buffer_)[externalPos_].template constData<SampleType>();
    return frames[internalPos_];
}

template<typename SampleType>
bool DecodedAudioIterator<SampleType>::operator==(const DecodedAudioIterator &rhs) const {
    return externalPos_ == rhs.externalPos_ &&
           internalPos_ == rhs.internalPos_ &&
           buffer_ == rhs.buffer_;
}

template<typename SampleType>
bool DecodedAudioIterator<SampleType>::operator!=(const DecodedAudioIterator &rhs) const {
    return !(rhs == *this);
}


#endif //EQULIZER_DECODEDAUDIOITERATOR_H
