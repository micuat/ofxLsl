#pragma once

#include "lsl_cpp.h"
#include "ofMain.h"

class LslOutlet
{
    class AbstractParameter {
        AbstractParameter() {}
    };
    using InfoPtr = std::shared_ptr<lsl::stream_info>;
    using OutletPtr = std::shared_ptr<lsl::stream_outlet>;
    using Outlets = std::map<OutletPtr, std::vector<double>* >;
    Outlets outlets;

    LslOutlet() {
        ofAddListener(ofEvents().update, this, &LslOutlet::update, OF_EVENT_ORDER_AFTER_APP);
    }
    ~LslOutlet() {}
    LslOutlet(const LslOutlet &);
    LslOutlet & operator=(const LslOutlet &);
public:
    static LslOutlet &instance() {
        static LslOutlet s_instance;
        return s_instance;
    }

    void insert(OutletPtr& outlet, std::vector<double> &v) {
        instance().outlets.insert(Outlets::value_type(outlet, &v));
    }

    template <typename T>
    static void addStream(InfoPtr& info, std::vector<T> &v) {
        instance().insert(make_shared<lsl::stream_outlet>(*info), v);
    }

    void update(ofEventArgs &args) {
        for (const auto& keyValue : outlets) {
            const auto& outlet = keyValue.first;
            const auto& value = keyValue.second;
            outlet->push_sample(*value);
        }
    }
};
