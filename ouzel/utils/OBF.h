// Copyright (C) 2016 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include <cassert>
#include <cstdint>
#include <limits>
#include <map>
#include <string>
#include <vector>

namespace ouzel
{
    namespace obf
    {
        class Value
        {
        public:
            enum class Type: uint8_t
            {
                NONE,
                INT8,
                INT16,
                INT32,
                INT64,
                FLOAT,
                DOUBLE,
                STRING,
                LONG_STRING,
                BYTE_ARRAY,
                OBJECT,
                ARRAY,
                DICTIONARY
            };

            Value() {}
            Value(Type aType): type(aType) {}
            Value(uint8_t value):
                type(Type::INT8), intValue(value)
            {
            }
            Value(uint16_t value):
                intValue(value)
            {
                if (intValue > std::numeric_limits<uint8_t>::max())
                {
                    type = Type::INT16;
                }
                else
                {
                    type = Type::INT8;
                }
            }
            Value(uint32_t value):
                intValue(value)
            {
                if (intValue > std::numeric_limits<uint16_t>::max())
                {
                    type = Type::INT32;
                }
                else if (intValue > std::numeric_limits<uint8_t>::max())
                {
                    type = Type::INT16;
                }
                else
                {
                    type = Type::INT8;
                }
            }
            Value(uint64_t value):
                intValue(value)
            {
                if (intValue > std::numeric_limits<uint32_t>::max())
                {
                    type = Type::INT64;
                }
                else if (intValue > std::numeric_limits<uint16_t>::max())
                {
                    type = Type::INT32;
                }
                else if (intValue > std::numeric_limits<uint8_t>::max())
                {
                    type = Type::INT16;
                }
                else
                {
                    type = Type::INT8;
                }
            }
            Value(float value): type(Type::FLOAT), doubleValue(value) {}
            Value(double value): type(Type::DOUBLE), doubleValue(value) {}
            Value(const std::string& value):
                stringValue(value)
            {
                if (value.length() > std::numeric_limits<uint16_t>::max())
                {
                    type = Type::LONG_STRING;
                }
                else
                {
                    type = Type::STRING;
                }
            }
            Value(const std::vector<uint8_t>& value): type(Type::BYTE_ARRAY), byteArrayValue(value) {}
            Value(const std::map<uint32_t, Value>& value): type(Type::OBJECT), objectValue(value) {}
            Value(const std::vector<Value>& value): type(Type::ARRAY), arrayValue(value) {}

            Value& operator=(Type newType)
            {
                type = newType;

                return *this;
            }

            Value& operator=(uint8_t value)
            {
                type = Type::INT8;
                intValue = value;

                return *this;
            }

            Value& operator=(uint16_t value)
            {
                intValue = value;

                if (intValue > std::numeric_limits<uint8_t>::max())
                {
                    type = Type::INT16;
                }
                else
                {
                    type = Type::INT8;
                }

                return *this;
            }

            Value& operator=(uint32_t value)
            {
                intValue = value;

                if (intValue > std::numeric_limits<uint16_t>::max())
                {
                    type = Type::INT32;
                }
                else if (intValue > std::numeric_limits<uint8_t>::max())
                {
                    type = Type::INT16;
                }
                else
                {
                    type = Type::INT8;
                }

                return *this;
            }

            Value& operator=(uint64_t value)
            {
                intValue = value;

                if (intValue > std::numeric_limits<uint32_t>::max())
                {
                    type = Type::INT64;
                }
                else if (intValue > std::numeric_limits<uint16_t>::max())
                {
                    type = Type::INT32;
                }
                else if (intValue > std::numeric_limits<uint8_t>::max())
                {
                    type = Type::INT16;
                }
                else
                {
                    type = Type::INT8;
                }

                return *this;
            }

            Value& operator=(float value)
            {
                type = Type::FLOAT;
                doubleValue = value;

                return *this;
            }

            Value& operator=(double value)
            {
                type = Type::DOUBLE;
                doubleValue = value;

                return *this;
            }

            Value& operator=(const std::string& value)
            {
                stringValue = value;
                if (value.length() <= std::numeric_limits<uint16_t>::max())
                {
                    type = Type::STRING;
                }
                else
                {
                    type = Type::LONG_STRING;
                }
                return *this;
            }

            Value& operator=(const std::vector<uint8_t>& value)
            {
                type = Type::BYTE_ARRAY;
                byteArrayValue = value;

                return *this;
            }

            Value& operator=(const std::map<uint32_t, Value>& value)
            {
                type = Type::OBJECT;
                objectValue = value;

                return *this;
            }

            Value& operator=(const std::vector<Value>& value)
            {
                type = Type::ARRAY;
                arrayValue = value;

                return *this;
            }

            Type getType() const { return type; }

            uint32_t decode(const std::vector<uint8_t>& buffer, uint32_t offset = 0);
            uint32_t encode(std::vector<uint8_t>& buffer) const;

            int8_t asInt8() const
            {
                assert(type == Type::INT8 || type == Type::INT16 || type == Type::INT32 || type == Type::INT64);

                return static_cast<int8_t>(intValue);
            }

            uint8_t asUInt8() const
            {
                assert(type == Type::INT8 || type == Type::INT16 || type == Type::INT32 || type == Type::INT64);

                return static_cast<uint8_t>(intValue);
            }

            int16_t asInt16() const
            {
                assert(type == Type::INT8 || type == Type::INT16 || type == Type::INT32 || type == Type::INT64);

                return static_cast<int16_t>(intValue);
            }

            uint16_t asUInt16() const
            {
                assert(type == Type::INT8 || type == Type::INT16 || type == Type::INT32 || type == Type::INT64);

                return static_cast<uint16_t>(intValue);
            }

            int32_t asInt32() const
            {
                assert(type == Type::INT8 || type == Type::INT16 || type == Type::INT32 || type == Type::INT64);

                return static_cast<int32_t>(intValue);
            }

            uint32_t asUInt32() const
            {
                assert(type == Type::INT8 || type == Type::INT16 || type == Type::INT32 || type == Type::INT64);

                return static_cast<uint32_t>(intValue);
            }

            int64_t asInt64() const
            {
                assert(type == Type::INT8 || type == Type::INT16 || type == Type::INT32 || type == Type::INT64);

                return static_cast<int64_t>(intValue);
            }

            uint64_t asUInt64() const
            {
                assert(type == Type::INT8 || type == Type::INT16 || type == Type::INT32 || type == Type::INT64);

                return intValue;
            }

            float asFloat() const
            {
                assert(type == Type::FLOAT || type == Type::DOUBLE);

                return static_cast<float>(doubleValue);
            }

            double asDouble() const
            {
                assert(type == Type::FLOAT || type == Type::DOUBLE);

                return doubleValue;
            }

            const std::string& asString() const
            {
                assert(type == Type::STRING || type == Type::LONG_STRING);

                return stringValue;
            }

            const std::vector<uint8_t>& asByteArray() const
            {
                assert(type == Type::BYTE_ARRAY);

                return byteArrayValue;
            }

            const std::map<uint32_t, Value>& asMap() const
            {
                assert(type == Type::OBJECT);

                return objectValue;
            }

            const std::vector<Value>& asVector() const
            {
                assert(type == Type::ARRAY);

                return arrayValue;
            }

            const std::map<std::string, Value>& asDictionary() const
            {
                assert(type == Type::DICTIONARY);

                return dictionaryValue;
            }

            std::vector<Value>::iterator begin()
            {
                assert(type == Type::ARRAY);

                return arrayValue.begin();
            }

            std::vector<Value>::const_iterator begin() const
            {
                assert(type == Type::ARRAY);

                return arrayValue.begin();
            }

            std::vector<Value>::iterator end()
            {
                assert(type == Type::ARRAY);

                return arrayValue.end();
            }

            std::vector<Value>::const_iterator end() const
            {
                assert(type == Type::ARRAY);

                return arrayValue.end();
            }

            uint32_t getSize() const
            {
                assert(type == Type::ARRAY);

                return static_cast<uint32_t>(arrayValue.size());
            }

            Value operator[](uint32_t key) const
            {
                assert(type == Type::OBJECT || type == Type::ARRAY);

                if (type == Type::OBJECT)
                {
                    auto i = objectValue.find(key);

                    if (i != objectValue.end())
                    {
                        return i->second;
                    }
                }
                else if (type == Type::ARRAY)
                {
                    if (key < arrayValue.size())
                    {
                        return arrayValue[key];
                    }
                }

                return Value();
            }

            Value& operator[](uint32_t key)
            {
                assert(type == Type::OBJECT || type == Type::ARRAY);

                if (type == Type::OBJECT)
                {
                    return objectValue[key];
                }
                else
                {
                    type = Type::ARRAY;

                    return arrayValue[key];
                }
            }

            Value operator[](const std::string& key) const
            {
                assert(type == Type::DICTIONARY);

                auto i = dictionaryValue.find(key);

                if (i != dictionaryValue.end())
                {
                    return i->second;
                }

                return Value();
            }

            Value& operator[](const std::string& key)
            {
                assert(type == Type::DICTIONARY);

                return dictionaryValue[key];
            }

            bool hasElement(uint32_t key) const
            {
                assert(type == Type::OBJECT || type == Type::ARRAY);

                if (type == Type::OBJECT)
                {
                    return objectValue.find(key) != objectValue.end();
                }
                else if (type == Type::ARRAY)
                {
                    return key < arrayValue.size();
                }
                else
                {
                    return false;
                }
            }

            bool hasElement(const std::string& key) const
            {
                assert(type == Type::DICTIONARY);

                return dictionaryValue.find(key) != dictionaryValue.end();
            }

            void append(const Value& node)
            {
                arrayValue.push_back(node);
            }

        private:
            Type type = Type::NONE;
            uint64_t intValue;
            double doubleValue;
            std::string stringValue;
            std::vector<uint8_t> byteArrayValue;
            std::map<uint32_t, Value> objectValue;
            std::vector<Value> arrayValue;
            std::map<std::string, Value> dictionaryValue;
        };
    } // namespace obf
} // namespace ouzel
