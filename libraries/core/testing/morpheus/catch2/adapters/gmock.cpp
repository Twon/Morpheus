#include <catch2/catch_all.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstddef>

namespace morpheus
{

namespace
{

struct Listener : public testing::EmptyTestEventListener
{
    void OnTestPartResult(testing::TestPartResult const& result) override
    {
        // LCOV_EXCL_START
        ::Catch::SourceLineInfo const sourceLineInfo(result.file_name() ? result.file_name() : "unknown",
                                                     (result.line_number() == -1) ? 0 : static_cast<std::size_t>(result.line_number()));

        auto const dispositionType = result.nonfatally_failed() ? ::Catch::ResultDisposition::ContinueOnFailure : ::Catch::ResultDisposition::Normal;

        ::Catch::AssertionHandler assertion("GTEST", sourceLineInfo, "", dispositionType);
        auto const resultType = result.failed() ? ::Catch::ResultWas::ExplicitFailure : ::Catch::ResultWas::Ok;
        if (not result.skipped())
            assertion.handleMessage(resultType, result.message());
        assertion.complete();
        // LCOV_EXCL_STOP
    }
};

} // namespace

void enableGmockAdapter(char* argv[])
{
    int gmockArgC = 1;
    ::testing::InitGoogleMock(&gmockArgC, argv);

    ::testing::UnitTest::GetInstance()->listeners().Append(new Listener);

    delete ::testing::UnitTest::GetInstance()->listeners().Release(::testing::UnitTest::GetInstance()->listeners().default_result_printer());
}

} // namespace morpheus
