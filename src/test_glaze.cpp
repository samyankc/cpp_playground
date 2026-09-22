#include <glaze/glaze.hpp>
#include <print>

constexpr char JsonInput[] = {
#embed "etc_files/test_input.json" suffix(, '\0' )
};

auto PrintAsJson( auto&& InputObject )
{
    auto Buffer = std::string{};
    std::ignore = glz::write<glz::opts{ .prettify = true }>( InputObject, Buffer );
    std::println( "{}", Buffer );
}



struct DTO {

};

auto foo()
{
    auto generic_json = glz::generic{};

    std::ignore = glz::read<glz::opts{ .error_on_unknown_keys = false }>( generic_json, JsonInput );

    PrintAsJson( generic_json );
}

int main()
{
    std::println( "Begin" );
    foo();
    std::println( "End" );
    return 0;
}