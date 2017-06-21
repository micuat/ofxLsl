#pragma once

#include "lsl_cpp.h"
#include "ofMain.h"

class LslInlet
{
public:
    using InletPtr = std::shared_ptr<lsl::stream_inlet>;

private:
    class AbstractSample {
    public:
        AbstractSample() {}
        virtual void get(InletPtr inlet) = 0;
    };

    template <typename T, typename R>
    class Sample : public AbstractSample {
    public:
        using Setter = std::function<R(std::vector<T>&)>;
        Sample(Setter _setter) : setter(_setter) {}
        void get(InletPtr inlet) {
            // receive data
            vector<vector<T> > chunk;
            inlet->pull_chunk(chunk);
            for (auto& c : chunk) {
                setter(c);
            }
        }
    private:
        Setter setter;
    };

    template <typename R>
    class Sample<void, R> : public AbstractSample {
    public:
        using Setter = std::function<R(InletPtr)>;
        Sample(Setter _setter) : setter(_setter) {}
        void get(InletPtr inlet) {
            setter(inlet);
        }
    private:
        Setter setter;
    };

    using SampleRef = std::shared_ptr<AbstractSample>;
    using InfoPtr = std::shared_ptr<lsl::stream_info>;
    using Inlets = std::map<InletPtr, SampleRef>;
    Inlets inlets;

    LslInlet() {
        ofAddListener(ofEvents().update, this, &LslInlet::ofUpdate, OF_EVENT_ORDER_AFTER_APP);
    }
    ~LslInlet() {}
    LslInlet(const LslInlet &);
    LslInlet & operator=(const LslInlet &);
public:
    using InletPtr = std::shared_ptr<lsl::stream_inlet>;

    static LslInlet &instance() {
        static LslInlet s_instance;
        return s_instance;
    }

    static InletPtr addStream(InletPtr inlet, SampleRef sample) {
        instance().inlets.insert(Inlets::value_type(inlet, sample));
        return inlet;
    }

    static InletPtr addStream(InfoPtr info, SampleRef sample) {
        auto inlet = std::make_shared<lsl::stream_inlet>(*info);
        return instance().addStream(inlet, sample);
    }

    template <typename R>
    static InletPtr addStream(const std::string &prop, const std::string &value, std::function<R(InletPtr)> callback) {
        std::vector<lsl::stream_info> infos = lsl::resolve_stream(prop, value);
        SampleRef sample = std::make_shared<Sample<void, R> >(callback);
        return addStream(std::make_shared<lsl::stream_info>(infos.at(0)), sample);
    }

    template <typename R, typename T>
    static InletPtr addStream(const std::string &prop, const std::string &value, std::function<R(std::vector<T>&)> callback) {
        std::vector<lsl::stream_info> infos = lsl::resolve_stream(prop, value);
        SampleRef sample = std::make_shared<Sample<T, R> >(callback);
        return addStream(std::make_shared<lsl::stream_info>(infos.at(0)), sample);
    }

    void ofUpdate(ofEventArgs &args) {
        update();
    }

    void update() {
        for (const auto& keyValue : inlets) {
            const auto& inlet = keyValue.first;
            const auto& sample = keyValue.second;
            sample->get(inlet);
        }
    }
};
