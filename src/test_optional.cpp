#include <vector>
#include <utility>
#include <optional>
#include <string>

using RefractionEntryType = std::optional<std::string>;
struct RefractionRow
{
    RefractionEntryType Sphere{}, Cylinder{}, Axis{}, ADD{}, PD{}, OCH{}, VA{}, Prism{};
};

struct RefractionGroup
{
    std::string Purpose{};
    RefractionRow R{}, L{};
};

struct RefractionRecord2
{
    std::optional<RefractionGroup> Full;
};

int main()
{
    auto a = 123;

    auto b = std::optional<RefractionRecord2>{};

    b = RefractionRecord2{};

    auto k = 123;

    b = RefractionRecord2{
        .Full = RefractionGroup{ .R = { .Sphere = "+100" } },
    };

    auto kk = 123;
    return 0;
}