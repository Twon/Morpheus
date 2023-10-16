#include "morpheus/core/serialisation/concepts/writer_archtype.hpp"
#include "morpheus/core/serialisation/write_serialiser.hpp"

#include <catch2/catch_all.hpp>

using namespace Catch;

namespace morpheus::serialisation
{

    TEST_CASE("Check concepts for write serialisation", "[morpheus.serialisation.write_serialiser.concepts]")
    {
        STATIC_REQUIRE(concepts::Writer<concepts::WriterArchtype>);
    }

    TEST_CASE("Ensure write serialiser are default constructible where the underlying writer supports it", "[morpheus.serialisation.write_serialiser.default_construction]")
    {
        GIVEN("A default constructible writer")
        {
            STATIC_REQUIRE(std::is_default_constructible_v<concepts::WriterArchtype>);

            WHEN("Ensure write serialiser of given tyoe")
            {
                using WriteSerialiserArchitype = WriteSerialiser<concepts::WriterArchtype>;
                THEN("Is default construtible")
                {
                    STATIC_REQUIRE(std::is_default_constructible_v<WriteSerialiserArchitype>);
                }
            }
        }
        GIVEN("A non-default constructible writer")
        {
            struct NonDefaultConstuctibleWriter : concepts::WriterArchtype
            {
                NonDefaultConstuctibleWriter() = delete;
            };
            STATIC_REQUIRE(!std::is_default_constructible_v<NonDefaultConstuctibleWriter>);

            WHEN("Ensure write serialiser of given tyoe")
            {
                using NonDefaultConstuctibleWriteSerialiserArchitype = WriteSerialiser<NonDefaultConstuctibleWriter>;
                THEN("Is default construtible")
                {
                    STATIC_REQUIRE(!std::is_default_constructible_v<NonDefaultConstuctibleWriteSerialiserArchitype>);
                }
            }
        }
    }

    TEST_CASE("Ensure write serialiser are forward constructible where the underlying writer supports it", "[morpheus.serialisation.write_serialiser.forwarding_construction]")
    {
        GIVEN("A writer with multiple constructors")
        {
            struct MultiConstructorWriter : concepts::WriterArchtype
            {
                MultiConstructorWriter() = delete;
                MultiConstructorWriter(int, bool) {}
                MultiConstructorWriter(int, bool, int, bool){}
            };

            STATIC_REQUIRE(std::is_constructible_v<MultiConstructorWriter, int, bool>);
            STATIC_REQUIRE(std::is_constructible_v<MultiConstructorWriter, int, bool, int, bool>);

            WHEN("Ensure write serialiser of given tyoe")
            {
                using ForwardingSerialiserArchitype = WriteSerialiser<MultiConstructorWriter>;
                THEN("Is default construtible")
                {
                    STATIC_REQUIRE(!std::is_constructible_v<ForwardingSerialiserArchitype, int>);
                    STATIC_REQUIRE(std::is_constructible_v<ForwardingSerialiserArchitype, int, bool>);
                    STATIC_REQUIRE(!std::is_constructible_v<ForwardingSerialiserArchitype, int, bool, int>);
                    STATIC_REQUIRE(std::is_constructible_v<ForwardingSerialiserArchitype, int, bool, int, bool>);
                }
            }
        }
        GIVEN("A non-default constructible writer")
        {
            STATIC_REQUIRE(!std::is_constructible_v<concepts::WriterArchtype, int>);
            STATIC_REQUIRE(!std::is_constructible_v<concepts::WriterArchtype, int, bool>);
            STATIC_REQUIRE(!std::is_constructible_v<concepts::WriterArchtype, int, bool, int>);
            STATIC_REQUIRE(!std::is_constructible_v<concepts::WriterArchtype, int, bool, int, bool>);

            WHEN("Ensure write serialiser of given tyoe")
            {
                using WriteSerialiserArchitype = WriteSerialiser<concepts::WriterArchtype>;
                THEN("Is default construtible")
                {
                    STATIC_REQUIRE(!std::is_constructible_v<WriteSerialiserArchitype, int>);
                    STATIC_REQUIRE(!std::is_constructible_v<WriteSerialiserArchitype, int, bool>);
                    STATIC_REQUIRE(!std::is_constructible_v<WriteSerialiserArchitype, int, bool, int>);
                    STATIC_REQUIRE(!std::is_constructible_v<WriteSerialiserArchitype, int, bool, int, bool>);
                }
            }
        }
    }

} // namespace morpheus::serialisation
