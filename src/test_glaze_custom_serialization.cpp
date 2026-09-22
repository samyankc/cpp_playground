#include <glaze/glaze.hpp>
#include <print>

struct CustomType
{
    int data_int;
    std::string data_str;
};

template<>
struct glz::from<glz::JSON, CustomType>
{
    template<auto Opts>
    static void op( CustomType& value, is_context auto&& ctx, auto&& it, auto&& end )
    {
        auto workspace = std::variant<int, std::string, std::vector<int>>{};
        parse<JSON>::op<Opts>( workspace, ctx, it, end );

        if( std::holds_alternative<int>( workspace ) )
        {
            auto result = std::get<int>( workspace );
            value.data_int = result;
            value.data_str = std::format( "int: [{}]", result );
        }

        if( std::holds_alternative<std::string>( workspace ) )
        {
            auto result = std::get<std::string>( workspace );
            value.data_int = std::stoi( result );
            value.data_str = std::format( "str: [{}]", result );
        }

        if( std::holds_alternative<std::vector<int>>( workspace ) )
        {
            auto result = std::get<std::vector<int>>( workspace );
            value.data_int = result.empty() ? 0 : result[0];
            value.data_str = std::format( "vec: [{}]", result );
        }
    }
};

//  template<>
//  struct to<JSON, CustomType>
//  {
//      template<auto Opts>
//      static void op( CustomType& value, is_context auto&& ctx, auto&& b, auto&& ix ) noexcept
//      {
//          value.data_str = std::to_string( value.data_int );
//          serialize<JSON>::op<Opts>( value.data_str, ctx, b, ix );
//      }
//  };

auto PrintAsJson( auto&& InputObject )
{
    auto Buffer = std::string{};
    std::ignore = glz::write<glz::opts{ .prettify = true }>( InputObject, Buffer );
    std::println( "{}", Buffer );
}

int main()
{
    constexpr auto input_json = R"(
        [
            123,
            "456",
            "789",
            [598,2345,56465,234],
            8888
        ]
    )";

    auto Obj = std::vector<CustomType>{};

    std::ignore = glz::read<glz::opts{ .error_on_unknown_keys = false }>( Obj, input_json );

    PrintAsJson( Obj );
}