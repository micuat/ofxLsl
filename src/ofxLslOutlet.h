#pragma once

#include "lsl_cpp.h"
#include "ofMain.h"

class LslOutlet
{
    using OutletPtr = std::shared_ptr<lsl::stream_outlet>;
    class AbstractSample {
    public:
        AbstractSample() {}
        virtual void set(OutletPtr outlet) = 0;
    };

    template <typename T>
    class Sample : public AbstractSample {
    public:
        std::vector<T>* v;
        Sample(std::vector<T>* _v) : v(_v) {}
        void set(OutletPtr outlet) {
            outlet->push_sample(*v);
        }
    };

    using SampleRef = std::shared_ptr<AbstractSample>;
    using InfoPtr = std::shared_ptr<lsl::stream_info>;
    using Outlets = std::map<OutletPtr, SampleRef>;
    Outlets outlets;

    LslOutlet() {
        ofAddListener(ofEvents().update, this, &LslOutlet::ofUpdate, OF_EVENT_ORDER_AFTER_APP);
    }
    ~LslOutlet() {}
    LslOutlet(const LslOutlet &);
    LslOutlet & operator=(const LslOutlet &);
public:
    static LslOutlet &instance() {
        static LslOutlet s_instance;
        return s_instance;
    }

    static void addStream(OutletPtr outlet, SampleRef sample) {
        instance().outlets.insert(Outlets::value_type(outlet, sample));
    }

    static void addStream(InfoPtr info, SampleRef sample) {
        auto outlet = std::make_shared<lsl::stream_outlet>(*info);
        instance().addStream(outlet, sample);
    }

    template <typename T>
    static void addStream(const std::string &name, const std::string &type, std::vector<T> &v) {
        auto info = std::make_shared<lsl::stream_info>(name, type, v.size());
        SampleRef sample = std::make_shared<Sample<T> >(&v);
        addStream(info, sample);
    }

    void ofUpdate(ofEventArgs &args) {
        update();
    }

    void update() {
        for (const auto& keyValue : outlets) {
            const auto& outlet = keyValue.first;
            const auto& sample = keyValue.second;
            sample->set(outlet);
        }
    }
};
