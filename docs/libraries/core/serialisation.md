# Serialisation

The Morpheus serialisation framework provides a unified, extensible interface for converting C++ objects to and from various data formats. A key design principle is **extensibility**, allowing the framework to support a diverse range of formats while maintaining a consistent user-facing API.

Currently, the framework supports:
*   **JSON**: A human-readable text format, implemented via RapidJSON.
*   **Binary**: A high-performance, compact format for storage and transmission.

In the future, support is planned for additional formats including XML, YAML, BSON, S-Expressions (SEXP), TOML, FlatBuffers, MessagePack, and Protobuf.

## Architecture

The framework is built on a layered architecture that decouples the object-level serialisation logic from the low-level format implementation.

### Customisation Point Objects (CPOs)

The primary entry points are the `serialise` and `deserialise` [Customisation Point Objects (CPOs)](https://quuxplusone.github.io/blog/2018/03/19/customization-points-for-functions/). These CPOs dispatch the work to the appropriate overload for the type being processed, supporting both intrusive (member functions) and non-intrusive (ADL-found free functions) patterns.

### Serialisers

User-level interaction typically happens through `WriteSerialiser` and `ReadSerialiser` templates. These act as wrappers around specific `Writer` or `Reader` implementations, providing a high-level API for serialising complex types and managing the serialisation state.

### Readers and Writers

At the lowest level, the framework defines concepts for **Readers** and **Writers**. These are responsible for the actual byte-level or text-level representation of fundamental primitive types.


.. doxygenconcept:: morpheus::serialisation::concepts::Reader
   :project: morpheus_core

.. doxygenconcept:: morpheus::serialisation::concepts::Writer
   :project: morpheus_core

.. doxygenconcept:: morpheus::serialisation::concepts::ReadSerialisable
   :project: morpheus_core

.. doxygenconcept:: morpheus::serialisation::concepts::WriteSerialisable
   :project: morpheus_core

## Supported Formats

### Binary

The binary format is designed for maximum performance and minimum storage overhead. It writes data as a raw byte stream. Note that the binary format requires many sequence types (like `std::vector`) to provide their size upfront during serialisation.

### JSON

The JSON format provides a human-readable representation of data. It is implemented using the RapidJSON library and supports all standard JSON data types.

## Usage Guide

### Serialising Data (Write)

To serialise an object, you create a `WriteSerialiser` with the desired `Writer` implementation and call the `serialise` function.

```cpp
#include "morpheus/core/serialisation/serialisers.hpp"
#include <iostream>
#include <vector>

void example() {
    // Compounding: Serialising a container of complex types
    std::vector<std::string> tags = {"engine", "graphics", "core"};
    morpheus::serialisation::JsonWriteSerialiser serialiser(std::cout);
    morpheus::serialisation::serialise(serialiser, tags);
}
```

### Deserialising Data (Read)

Deserialisation follows a similar pattern using `ReadSerialiser` and the `deserialise` function.

```cpp
#include "morpheus/core/serialisation/serialisers.hpp"
#include <sstream>
#include <vector>

void example() {
    std::stringstream ss(R"(["engine", "graphics", "core"])");
    morpheus::serialisation::JsonReadSerialiser serialiser(ss);
    auto tags = morpheus::serialisation::deserialise<std::vector<std::string>>(serialiser);
}
```

## Making Types Serialisable

### Intrusive Pattern

Add `serialise` and `deserialise` member functions to your class.

```cpp
struct MyStruct {
    int a;
    double b;

    template <typename Serialiser>
    void serialise(Serialiser& s) const {
        s.serialise("a", a);
        s.serialise("b", b);
    }

    template <typename Serialiser>
    void deserialise(Serialiser& s) {
        a = s.template deserialise<int>("a");
        b = s.template deserialise<double>("b");
    }
};
```

### Non-Intrusive Pattern (ADL)

Define free functions in the same namespace as your type.

```cpp
namespace my_namespace {
    struct MyOtherStruct {
        int x;
    };

    template <typename Serialiser>
    void serialise(Serialiser& s, MyOtherStruct const& val) {
        s.serialise("x", val.x);
    }

    template <typename Serialiser>
    void deserialise(Serialiser& s, MyOtherStruct& val) {
        val.x = s.template deserialise<int>("x");
    }
}
```

## Adapters: Deep Integration

One of the most powerful features of the Morpheus serialisation framework is its **Adapter** system. Adapters act as the "connective tissue" between the core framework and external libraries, allowing types from disparate sources to be serialised transparently.

The goal is to provide a "just-works" experience: once the relevant adapter header is included, types from that library can be used seamlessly within the serialisation pipeline.

### Standard Library (STL) Support

Morpheus provides out-of-the-box support for the majority of the C++ Standard Library. Adapters are located in `morpheus/core/serialisation/adapters/std/` and cover:

*   **Containers**: `std::vector`, `std::list`, `std::map`, `std::unordered_map`, `std::set`, etc. These leverage C++20 ranges for generic and efficient support.
*   **Vocabulary Types**: `std::optional`, `std::variant` (including `std::monostate`), `std::pair`, and `std::tuple`.
*   **Smart Pointers**: `std::unique_ptr` and `std::shared_ptr`.
*   **Time**: `std::chrono::duration` and `std::chrono::time_point`. In textual formats (JSON), these produce human-readable strings like `"100ms"`.
*   **Bytes**: `std::byte` is supported as a primitive. Arrays of bytes (such as `std::vector<std::byte>` or `std::span<std::byte const>`) are automatically encoded as **Base64 strings** in JSON to ensure compact and efficient storage of binary blobs.

### Formatting Adapters: Hex

Sometimes you want to explicitly control the textual representation of a value without changing its underlying type. The `Hex<T>` adapter allows you to serialise any integral type or `std::byte` as a hexadecimal string in textual formats.

```cpp
#include "morpheus/core/serialisation/adapters/hex.hpp"

void example() {
    std::byte secret{0xB4};
    morpheus::serialisation::JsonWriteSerialiser serialiser(std::cout);

    // Serialises as "0xB4" in JSON
    morpheus::serialisation::serialise(serialiser, morpheus::serialisation::Hex{secret});
}
```

In binary formats, `Hex<T>` is a zero-overhead pass-through that writes the raw bits, ensuring you don't pay a performance penalty for human-readable debugging elsewhere.

### External Library Integration (Boost)

The framework is designed to integrate with major C++ ecosystems to reduce boilerplate:

*   **Automatic Aggregate Serialisation**: Through `morpheus/core/serialisation/adapters/aggregate.hpp`, simple structs (aggregates) can opt-in to automatic serialisation via `boost::pfr`. This enables field-by-field serialisation without writing any manual logic.
*   **Stable Type Naming**: The `std::variant` adapter uses `boost::type_index` to ensure that type names stored in textual formats are stable and consistent regardless of the compiler or platform.

## Showcase: Compounding Types

The recursive nature of the framework allows for depth and complexity without additional effort. Below is a realistic example of a configuration structure compounding multiple STL types.

```cpp
#include "morpheus/core/serialisation/serialisers.hpp"
#include "morpheus/core/serialisation/adapters/std/vector.hpp"
#include "morpheus/core/serialisation/adapters/std/map.hpp"
#include "morpheus/core/serialisation/adapters/std/variant.hpp"
#include "morpheus/core/serialisation/adapters/std/optional.hpp"
#include "morpheus/core/serialisation/adapters/std/chrono.hpp"
#include <iostream>

struct AppConfig {
    std::string name;
    // Compounding: A map of dynamic properties using variants and containers
    std::map<std::string, std::variant<int, double, std::string, std::vector<int>>> properties;
    // An optional timeout duration
    std::optional<std::chrono::seconds> timeout;

    // Intrusive serialisation
    template <typename Serialiser>
    void serialise(Serialiser& s) const {
        s.serialise("name", name);
        s.serialise("properties", properties);
        s.serialise("timeout", timeout);
    }
};

void example() {
    AppConfig config{
        .name = "MorpheusEngine",
        .properties = {
            {"version", 1},
            {"threshold", 0.75},
            {"tags", std::vector{10, 20, 30}}
        },
        .timeout = std::chrono::seconds{30}
    };

    // Serialising the compound type to JSON
    morpheus::serialisation::JsonWriteSerialiser serialiser(std::cout);
    morpheus::serialisation::serialise(serialiser, config);
}
```
