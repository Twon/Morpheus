#include "morpheus/application/po/options.hpp"

#include <boost/program_options/options_description.hpp>

#include <catch2/catch_all.hpp>

namespace morpheus::application::po
{

struct Person
{
    std::string firstName;
    std::string surname;
    std::uint32_t age = 0;
    std::uint32_t yearOfBirth = 0;
    bool alive = false;

    void addOptions(boost::program_options::options_description& options)
    {
        namespace po = boost::program_options;
        // clang-format off
        options.add_options()
            ("first-name", po::value(&firstName)->required(), "The persons first name.")
            ("surname", po::value(&surname)->required(), "The persons surname")
            ("age", po::value(&age)->required(), "The persons age")
            ("year-of-birth", po::value(&yearOfBirth)->required(), "The persons year of birth")
            ("alive", po::value(&alive)->required(), "Is the persons still alive");
        // clang-format on
    }
};


TEST_CASE("Ensure options parsing of native types works", "[morpheus.application.po.basic_types]")
{
    GIVEN("A type supporting addOptions")
    {
        Person person;

        WHEN("Parsing valid parameters")
        {
            std::array cliOptions = { "dummyProgram.exe", "--first-name", "John", "--surname", "Doe", "--age", "42", "--year-of-birth", "1980", "--alive", "true" };
            auto const result = parseProgramOptions(cliOptions.size(), cliOptions.data(), HelpDocumentation{}, person);

            THEN("Expect no error results and valid values extracted")
            {
                REQUIRE(!result);
                REQUIRE(person.firstName == "John");
                REQUIRE(person.surname == "Doe");
                REQUIRE(person.age == 42);
                REQUIRE(person.yearOfBirth == 1980);
                REQUIRE(person.alive == true);
            }
        }
        WHEN("Parsing invalid parameters because the first parameter is not a program name")
        {
            std::array cliOptions = { "--first-name", "John", "--surname", "Doe", "--age", "42", "--year-of-birth", "1980", "--alive", "true" };
            auto const result = parseProgramOptions(cliOptions.size(), cliOptions.data(), HelpDocumentation{}, person);
            THEN("Expect no error results and valid values extracted")
            {
                REQUIRE(result);
            }
        }
    }
}

} // namespace morpheus::application::po
