#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include <tlsh.h>
#include <tlsh_util.h>

#include <array>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string_view>
#include <tuple>
#include <vector>

#define NS "TLSH"

using namespace std::literals::string_view_literals;


TEST_CASE("Evaluation", "[" NS "]")
{
    SECTION("TLSH small buffer hash")
    {
        const auto instr =
            "0684076d82f90066d54f1ccaa555f093a7627286555b0e5cc2e36da3ab41732e79636276530a861db7732eeb420bc2261af2a956f9bb2cf20876ca8819b4a43e"sv;
        const auto res = "8EA0022016221F9C51EE2F20BDAE164C82075B9DD563196665C4652425557542459C81"sv;
        auto t         = Tlsh();
        std::vector<u8> inhex, outhex;
        from_hex(std::vector<u8>(instr.cbegin(), instr.cend()), inhex);
        BENCHMARK("TLSH")
        {
            t.reset();
            REQUIRE_FALSE(t.isValid());
            t.update(inhex);
            t.final();
        };
        REQUIRE(t.isValid());
        CHECK(t.getHashString() == res);
    }
}

TEST_CASE("Helpers", "[" NS "]")
{
}

TEST_CASE("Conversion", "[" NS "]")
{
    SECTION("from_hex small buffer")
    {
        const auto instr1 = "0123456789ABCDEF"sv;
        const std::vector<u8> in(instr1.cbegin(), instr1.cend());
        std::vector<u8> out;
        const std::vector<u8> res{
            0x01,
            0x23,
            0x45,
            0x67,
            0x89,
            0xab,
            0xcd,
            0xef,
        };
        BENCHMARK("from_hex")
        {
            from_hex(in, out);
        };
    }

    SECTION("from_hex large buffer")
    {
        const auto instr1 =
            "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF"sv;
        const std::vector<u8> in(instr1.cbegin(), instr1.cend());
        std::vector<u8> out;
        const std::vector<u8> res{
            // clang-format off
            0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
            0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
            0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
            0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
            0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
            0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
            0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
            0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
            0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
            0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
            // clang-format on
        };
        BENCHMARK("from_hex")
        {
            from_hex(in, out);
        };
        CHECK(out == res);
    }
}
