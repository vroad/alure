#ifndef BUFFER_H
#define BUFFER_H

#include "alure2.h"

#include "al.h"

#include "refcount.h"

#if __cplusplus < 201103L
#define final
#endif

namespace alure {

class ALDevice;


ALuint FramesToBytes(ALuint size, SampleConfig chans, SampleType type);
ALenum GetFormat(SampleConfig chans, SampleType type);


class ALBuffer : public Buffer {
    ALDevice *const mDevice;
    ALuint mId;

    ALuint mFrequency;
    SampleConfig mSampleConfig;
    SampleType mSampleType;

    RefCount mRefs;

public:
    ALBuffer(ALDevice *device, ALuint id, ALuint freq, SampleConfig config, SampleType type)
      : mDevice(device), mId(id), mFrequency(freq), mSampleConfig(config), mSampleType(type), mRefs(0)
    { }

    void cleanup();

    long addRef() { return ++mRefs; }
    long decRef() { return --mRefs; }
    long getRef() { return mRefs.load(); }

    ALDevice *getDevice() { return mDevice; }
    const ALuint &getId() const { return mId; }

    virtual ALuint getLength() final;

    virtual ALuint getFrequency() final;
    virtual SampleConfig getSampleConfig() final;
    virtual SampleType getSampleType() final;

    virtual ALuint getSize() final;

    virtual bool isRemovable() const final;
};

} // namespace alure

#endif /* BUFFER_H */
