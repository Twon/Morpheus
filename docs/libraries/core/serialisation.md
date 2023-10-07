# Serialisation

Serialisation is the process of writing objects to and output format and reading them back in. The serialisation framework is designed to be extensible and support a wide range of format, including both binary and text based serialisation.

Within the framework their are concepts defining interfaces for readers and writers. Reader and writers support a basic set of fundamental operation which must be support for the framework to convert the data of supported types to the serialisation format. Currently supported formats include:
 - Json

Longer term there is intend to be support for the following formats
- Binary
- Json
- Yaml
- Toml
- Xml
- HDF5
- MessagePack: https://msgpack.org/index.html
- Protobuf
- Cap'n Proto

## Entry Points

The serialisation framework is based on 2 entry points, `serialise` and `deserialise` which are [customisation point object (CPOs)](https://quuxplusone.github.io/blog/2018/03/19/customization-points-for-functions/).  These CPOs do the work of then dispatching to an appropriate overload for the actual type being serialised.

## Reader and Writers

The serialisation framework provides concepts for readers and writers, which are interfaces specifying how read and write the fundmental primitive types supported by the C++ language.  All serialisation is build upon these basic building blocks.

.. doxygenconcept:: morpheus::serialisation::concepts::Reader
   :project: morpheus_core

.. doxygenconcept:: morpheus::serialisation::concepts::Writer
   :project: morpheus_core


# Serialisation specifications:
- ASN.1: https://en.wikipedia.org/wiki/ASN.1

# Serialisation Formats
- https://en.wikipedia.org/wiki/Comparison_of_data-serialization_formats

# Overview of serialisation in C++
- Killing C++ Serialization Overhead & Complexity - Eyal Zedaka - CppCon 2022: https://youtu.be/G7-GQhCw8eE

# Exisiting	C++ Serialisation Libraries
- Alpaca: https://github.com/p-ranav/alpaca
- Arvo: https://avro.apache.org/
- Bitsery: https://github.com/fraillt/bitsery
- Boost Serialisation: https://github.com/boostorg/serialization
	- Boost Portable Archive: https://github.com/daldegam/eos-portable-archive
	- Boost Yaml Archive: https://github.com/rwols/yaml-archive
- Cerial: https://github.com/USCiLab/cereal
- Cista: https://github.com/felixguendling/cista
- FlatBuffer: https://github.com/google/flatbuffers
- Thors: https://github.com/Loki-Astari/ThorsSerializer
- Thrift: https://thrift.apache.org/
- YAS: https://github.com/niXman/yas
- zpp::bits: https://github.com/eyalz800/zpp_bits



# Toml Sax Parsers
- loltoml: https://github.com/andrusha97/loltoml
