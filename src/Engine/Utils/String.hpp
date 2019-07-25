#ifndef STRING_H_DEFINED
#define STRING_H_DEFINED

#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <algorithm>

#include <boost/algorithm/string.hpp>

// Utilities of `std::string`
namespace String {
    
    // Convert from any type that supports the << operator to `std::string`.
    // @note Due to the templates, we must place the definition on the header.
    template <typename T>
        inline std::string toString(T const& x) {
            std::ostringstream o;
            if (!(o << x))
                throw std::runtime_error("Utils::String::toString");
            return o.str();
        }

    // Convert from `std::string` to any type that supports the >> operator.
    // @note Due to the templates, we must place the definition on the header.
    template <typename T>
        inline void convert(std::string const& s, T& x, bool failIfLeftOverChars = true) {
            std::istringstream i;
            char c;
            if ((!i >> x) && (failIfLeftOverChars && i.get(c)))
                throw std::runtime_error("Utils::String::convert");
        }

    // An easier way to call previous function.
    // @note Call it like `String::to<int>(string)`.
    template <typename T>
        inline T to(std::string const& s, bool failIfLeftOverChars = true) {
            T x;
            convert(s, x, failIfLeftOverChars);
            return x;
        }

    // Remore all the space on the left of #str.
    std::string ltrim(const std::string &str);

    // Remove all the space on the right of #str.
    std::string rtrim(const std::string &str);

    // Remove all the space on both sides of #str.
    std::string trim(const std::string &str);

    // Splits #str according to #delim.
    // @return A vector of string, without the delimiter.
    std::vector < std::string > split(const std::string& str, char delim = ' ', bool flag = false);

    std::string to_lower(std::string str);
}

#endif