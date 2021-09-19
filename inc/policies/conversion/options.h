#ifndef CV_POLICIES_CONVERSION_OPTIONS_H
#define CV_POLICIES_CONVERSION_OPTIONS_H

namespace cv {

union conversion {
    class option {};
    class truncate_on_narrowing : option {};
    class convert_on_narrowing  : option {};
    class assert_on_narrowing   : option {};
    class throw_on_out_of_range : option {};
};

//////////////////////// helpers >>>>>>>>>>>>>>>>>>>>>>>>

using truncate_on_narrowing = conversion::truncate_on_narrowing;
using convert_on_narrowing  = conversion::convert_on_narrowing;
using assert_on_narrowing   = conversion::assert_on_narrowing;
using throw_on_out_of_range = conversion::throw_on_out_of_range;

//////////////////////// helpers <<<<<<<<<<<<<<<<<<<<<<<<
} // namespace cv

#endif
