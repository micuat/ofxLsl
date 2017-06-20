#pragma once

#include "lsl_cpp.h"

class LslOutlet
{
    typedef std::map<std::shared_ptr<lsl::stream_info>, std::shared_ptr<lsl::stream_outlet> > Outlets;
    Outlets outlets;

    LslOutlet() {}
    ~LslOutlet() {}
    LslOutlet(const LslOutlet &);
    LslOutlet & operator=(const LslOutlet &);
public:
    static LslOutlet &instance() {
        static LslOutlet s_instance;
        return s_instance;
    }

    void insert(std::shared_ptr<lsl::stream_info> info, std::shared_ptr<lsl::stream_outlet> outlet) {
        instance().outlets.insert(Outlets::value_type(info, outlet));
    }

    std::shared_ptr<lsl::stream_outlet> get(std::shared_ptr<lsl::stream_info> info) {
        return instance().outlets.at(info);
    }
};
