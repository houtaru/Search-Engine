#ifndef STRING_H_DEFINED
#define STRING_H_DEFINED

#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>

namespace String {
    template <typename T>
        inline std::string toString(T const& x) {
            std::ostringstream o;
            if (!(o << x))
                throw std::runtime_error("Utils::String::toString");
            return o.str();
        }
    template <typename T>
        inline void convert(std::string const& s, T& x, bool failIfLeftOverChars = true) {
            std::istringstream i;
            char c;
            if ((!i >> x) && (failIfLeftOverChars && i.get(c)))
                throw std::runtime_error("Utils::String::convert");
        }

    template <typename T>
        inline T to(std::string const& s, bool failIfLeftOverChars = true) {
            T x;
            convert(s, x, failIfLeftOverChars);
            return x;
        }
    std::string ltrim(const std::string &str);

    std::string rtrim(const std::string &str);

    std::string trim(const std::string &str);

    std::vector < std::string > split(const std::string& str, char delim = ' ', bool flag = false);
}

#endif