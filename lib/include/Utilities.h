#ifndef UTILITIES
#define UTILITIES
#include <vector>
#include <string>

class Utilities {
public:
    static std::vector<std::string> splitString(const std::string& input);
    static bool compare_float(double x, double y, double epsilon = 0.01f);
private:
    Utilities() = default;
};
#endif /* UTILITIES */
