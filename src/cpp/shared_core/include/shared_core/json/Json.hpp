/*
 * Json.hpp
 *
 * Copyright (C) 2009-19 by RStudio, Inc.
 *
 * Unless you have received this program directly from RStudio pursuant to the terms of a commercial license agreement
 * with RStudio, then this program is licensed to you under the following terms:
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef SHARED_CORE_JSON_HPP
#define SHARED_CORE_JSON_HPP

#include <map>
#include <ostream>
#include <set>
#include <utility>
#include <vector>

#include <boost/optional.hpp>

#include <shared_core/PImpl.hpp>
#include <shared_core/Logger.hpp>

namespace rstudio {
namespace core {

class Error;

} // namespace core
} // namespace rstudio

namespace rstudio {
namespace core {
namespace json {

class Array;
class Object;

typedef std::vector<std::pair<std::string, std::string> > StringPairList;
typedef std::map<std::string, std::vector<std::string> > StringListMap;

/**
 * @brief Enum which represents the type of a json value.
 */
enum class Type
{
   ARRAY,
   BOOL,
   INTEGER,
   OBJECT,
   STRING,
   REAL,
   NULL_TYPE,
   UNKNOWN
};

/**
 * @brief Class which represents a json value.
 */
class Value
{
protected:
   // This is defined first so it may be referred to in the class definition.
   /**
    * @brief Private implementation of Value.
    */
   PRIVATE_IMPL_SHARED(m_impl);

   /**
    * @brief Convenience typedef for the type of the private implementation of json::Value.
    */
   typedef std::shared_ptr<Impl> ValueImplPtr;

   friend class Array;

public:
   /**
    * @brief Constructor.
    */
   Value();

   /**
    * @brief Constructor. Creates a JSON value from a Value::Impl object.
    *
    * @param in_valueImpl   The Value::Impl object to use for the creation of this JSON value.
    */
   explicit Value(ValueImplPtr in_valueImpl);

   /**
    * @brief Copy constructor.
    *
    * @param in_other   The value to copy.
    */
   Value(const Value& in_other);

   /**
    * @brief Move constructor.
    *
    * @param in_other   The value to move from.
    */
   Value(Value&& in_other) noexcept;

   /**
    * @brief Conversion constructor.
    *
    * @param in_value   The literal value to set this JSON Value to.
    */
   explicit Value(bool in_value);

   /**
    * @brief Conversion constructor.
    *
    * @param in_value   The literal value to set this JSON Value to.
    */
   explicit Value(double in_value);

   /**
    * @brief Conversion constructor.
    *
    * @param in_value   The literal value to set this JSON Value to.
    */
   explicit Value(float in_value);

   /**
    * @brief Conversion constructor.
    *
    * @param in_value   The literal value to set this JSON Value to.
    */
   explicit Value(int in_value);

   /**
    * @brief Conversion constructor.
    *
    * @param in_value   The literal value to set this JSON Value to.
    */
   explicit Value(int64_t in_value);

   /**
    * @brief Conversion constructor.
    *
    * @param in_value   The literal value to set this JSON Value to.
    */
   explicit Value(const char* in_value);

   /**
    * @brief Conversion constructor.
    *
    * @param in_value   The literal value to set this JSON Value to.
    */
   explicit Value(const std::string& in_value);

   /**
    * @brief Conversion constructor.
    *
    * @param in_value   The literal value to set this JSON Value to.
    */
   explicit Value(unsigned int in_value);

   /**
    * @brief Conversion constructor.
    *
    * @param in_value   The literal value to set this JSON Value to.
    */
   explicit Value(uint64_t in_value);

   /**
    * @brief Virtual destructor.
    */
   virtual ~Value() = default;

   /**
    * @brief Assignment operator from Value.
    *
    * @param in_other   The value to copy to this value.
    *
    * @return A reference to this value.
    */
   Value& operator=(const Value& in_other);

   /**
    * @brief Move operator.
    *
    * @param in_other   The value to move to this value.
    *
    * @return A reference to this value.
    */
   Value& operator=(Value&& in_other) noexcept;

   /**
    * @brief Assignment operator.
    *
    * @param in_value   The literal value to set this JSON Value to.
    *
    * @return A reference to this value.
    */
   Value& operator=(bool in_value);

   /**
    * @brief Assignment operator.
    *
    * @param in_value   The literal value to set this JSON Value to.
    *
    * @return A reference to this value.
    */
   Value& operator=(double in_value);

   /**
    * @brief Assignment operator.
    *
    * @param in_value   The literal value to set this JSON Value to.
    *
    * @return A reference to this value.
    */
   Value& operator=(float in_value);

   /**
    * @brief Assignment operator.
    *
    * @param in_value   The literal value to set this JSON Value to.
    *
    * @return A reference to this value.
    */
   Value& operator=(int in_value);

   /**
    * @brief Assignment operator.
    *
    * @param in_value   The literal value to set this JSON Value to.
    *
    * @return A reference to this value.
    */
   Value& operator=(int64_t in_value);

   /**
    * @brief Assignment operator.
    *
    * @param in_value   The literal value to set this JSON Value to.
    *
    * @return A reference to this value.
    */
   Value& operator=(const char* in_value);

   /**
    * @brief Assignment operator.
    *
    * @param in_value   The literal value to set this JSON Value to.
    *
    * @return A reference to this value.
    */
   Value& operator=(const std::string& in_value);

   /**
    * @brief Assignment operator.
    *
    * @param in_value   The literal value to set this JSON Value to.
    *
    * @return A reference to this value.
    */
   Value& operator=(unsigned int in_value);

   /**
    * @brief Assignment operator.
    *
    * @param in_value   The literal value to set this JSON Value to.
    *
    * @return A reference to this value.
    */
   Value& operator=(uint64_t in_value);

   /**
    * @brief Equality operator.
    *
    * @param in_other   The value to compare this value to.
    *
    * @return True if the two values are the same; false otherwise.
    */
   bool operator==(const Value& in_other) const;

   /**
    * @brief Makes a copy of this JSON value.
    *
    * @return A copy of this JSON value.
    */
   Value clone() const;

   /**
    * @brief Attempts to coerce a JSON object to conform to the given schema by discarding non-conforming
    *    properties.
    *
    * @param in_schema           The schema to validate this value against.
    * @param out_propViolations  The names of the properties that did not conform to the schema.
    *
    * @return Success if this JSON value matches the schema after coercion; Error otherwise.
    */
   Error coerce(const std::string& in_schema,
                std::vector<std::string>& out_propViolations);

   /**
    * @brief Gets the value as a JSON array. If the call to getType() does not return Type::ARRAY, this method is
    *        invalid.
    *
    * @return The value as a JSON array.
    */
   Array getArray() const;

   /**
    * @brief Gets the value as a bool. If the call to getType() does not return Type::BOOL, this method is invalid.
    *
    * @return The value as a bool.
    */
   bool getBool() const;

   /**
    * @brief Gets the value as a double. If the call to getType() does not return Type::DOUBLE, this method is invalid.
    *
    * @return The value as a double.
    */
   double getDouble() const;

   /**
    * @brief Gets the value as a float. If the call to getType() does not return Type::FLOAT, this method is invalid.
    *
    * @return The value as a float.
    */
   float getFloat() const;

   /**
    * @brief Gets the value as an int. If the call to getType() does not return Type::INT, this method is invalid.
    *
    * @return The value as an int.
    */
   int getInt() const;

   /**
    * @brief Gets the value as an int64. If the call to getType() does not return Type::INT64, this method is invalid.
    *
    * @return The value as an int64.
    */
   int64_t getInt64() const;

   /**
    * @brief Gets the value as a JSON object. IF the call to getType() does not return Type::OBJECT, this method is
    *        invalid.
    *
    * @return The value as a JSON object.
    */
   Object getObject() const;

   /**
    * @brief Gets the value as a string. If the call to getType() does not return Type::STRING, this method is invalid.
    *
    * @return The value as a string.
    */
   std::string getString() const;

   /**
    * @brief Gets the type of this value.
    *
    * @return The type of this value.
    */
   Type getType() const;

   /**
    * @brief Gets the value as an unsigned int. If the call to getType() does not return Type::UINT, this method is
    *        invalid.
    *
    * @return The value as an unsigned int.
    */
   unsigned int getUInt() const;

   /**
    * @brief Gets the value as an uint64. If the call to getType() does not return Type::UINT64, this method is invalid.
    *
    * @return The value as an uint64.
    */
   uint64_t getUInt64() const;

   /**
    * @brief Gets this JSON value as the specified type.
    *
    * Before calling this method, the appropriate is<T> method should return true.
    *
    * @tparam T     The type to retrieve this value as.
    *
    * @return This value as an object of type T.
    */
   template <typename T>
   T getValue() const;

   /**
    * @brief Checks whether the value is a JSON array or not.
    *
    * @return True if the value is a JSON array; false otherwise.
    */
   bool isArray() const;

   /**
    * @brief Checks whether the value is a boolean value or not.
    *
    * @return True if the value is a boolean value; false otherwise.
    */
   bool isBool() const;

   /**
    * @brief Checks whether the value is a double value or not.
    *
    * @return True if the value is a double value; false otherwise.
    */
   bool isDouble() const;

   /**
    * @brief Checks whether the value is a float value or not.
    *
    * @return True if the value is a float value; false otherwise.
    */
   bool isFloat() const;

   /**
    * @brief Checks whether the value is an int 32 value or not.
    *
    * @return True if the value is an int 32 value; false otherwise.
    */
   bool isInt() const;

   /**
    * @brief Checks whether the value is an int 64 value or not.
    *
    * @return True if the value is an int 64 value; false otherwise.
    */
   bool isInt64() const;

   /**
    * @brief Checks whether the value is a JSON object or not.
    *
    * @return True if the value is a JSON object; false otherwise.
    */
   bool isObject() const;

   /**
    * @brief Checks whether the value is a string value or not.
    *
    * @return True if the value is a string value; false otherwise.
    */
   bool isString() const;

   /**
    * @brief Checks whether the value is null or not.
    *
    * @return True if the value is null; false otherwise.
    */
   bool isNull() const;

   /**
    * @brief Checks whether the value is an unsigned int 32 value or not.
    *
    * @return True if the value is an unsigned int 32 value; false otherwise.
    */
   bool isUInt() const;

   /**
    * @brief Checks whether the value is an unsigned int 64 value or not.
    *
    * @return True if the value is an unsigned int 64 value; false otherwise.
    */
   bool isUInt64() const;

   /**
    * @brief Parses the JSON string into this value.
    *
    * @param in_jsonStr     The JSON string to parse.
    *
    * @return Success on successful parse; error otherwise (e.g. ParseError)
    */
   Error parse(const char* in_jsonStr);

   /**
    * @brief Parses the JSON string into this value.
    *
    * @param in_jsonStr     The JSON string to parse.
    *
    * @return Success on successful parse; error otherwise (e.g. ParseError)
    */
   Error parse(const std::string& in_jsonStr);

   /**
    * @brief Parses the JSON string and validates it against the schema.
    *
    * @param in_jsonStr     The JSON string to parse.
    * @param in_schema      The schema to validate the JSON value against.
    *
    * @return Success if the string could be parsed and the parsed object matches the schema; Error otherwise.
    */
   Error parseAndValidate(const std::string& in_jsonStr, const std::string& in_schema);

   /**
    * @brief Validates this JSON value against a schema.
    *
    * @param in_schema      The schema to validate this value against.
    *
    * @return Success if this JSON value matches the schema; the Error that occurred during validation otherwise.
    */
   Error validate(const std::string& in_schema) const;

   /**
    * @brief Writes this value to a string.
    *
    * @return The string representation of this value.
    */
   std::string write() const;

   /**
    * @brief Writes this value to the specified output stream.
    *
    * @param io_ostream     The output stream to which to write this value.
    */
   void write(std::ostream& io_ostream) const;

   /**
    * @brief Writes and formats this value to a string.
    *
    * @return The formatted string representation of this value.
    */
   std::string writeFormatted() const;

   /**
    * @brief Writes and formats this value to the specified output stream.
    *
    * @param io_ostream     The output stream to which to write this value.
    */
   void writeFormatted(std::ostream& io_ostream) const;

private:
   /**
    * @brief Moves the provided value into this value.
    *
    * @param in_other   The value to move.
    */
   void move(Value&& in_other);
};

/**
 * @brief Class which represents a specific type of JSON Value: a JSON object.
 */
class Object : public Value
{
public:
   class Iterator;

   /**
    * @brief Class which represents a single member of a JSON object.
    */
   class Member
   {
   private:
      // Private implementation of member, declared first so it can be used.
      PRIVATE_IMPL_SHARED(m_impl);

      // Iterators can construct members.
      friend class Iterator;
   public:
      /**
       * @brief Default constructor.
       */
      Member() = default;

      /**
       * @brief Creates a Member object via its private implementation.
       *
       * @param in_impl The private implementation of the member.
       */
      Member(const std::shared_ptr<Impl>& in_impl);

      /**
       * @brief Gets the name of the member.
       *
       * @return The name of the member.
       */
      const std::string& getName() const;

      /**
       * @brief Gets the value of the member.
       *
       * @return The value of the member.
       */
      Value getValue() const;
   };

   /**
    * @brief Class which allows iterating over the members of a JSON object.
    */
   class Iterator: public std::iterator<
      std::bidirectional_iterator_tag,   // iterator_category
      Member,                            // value_type
      std::ptrdiff_t,                    // difference_type
      const Member*,                     // pointer
      Member>                            // reference
   {
   public:
      /**
       * @brief Constructor.
       *
       * @param in_parent       The parent object which will be iterated.
       * @param in_startPos     The starting position of the iterator. Default: the first member.
       */
      explicit Iterator(const Object* in_parent, std::ptrdiff_t in_startPos = 0);

      /**
       * @brief Copy constructor.
       *
       * @param in_other    The iterator to copy.
       */
      Iterator(const Iterator& in_other) = default;

      /**
       * @brief Assignment operator.
       *
       * @param in_other    The iterator to copy.
       *
       * @return A reference to this iterator.
       */
      Iterator& operator=(const Iterator& in_other);

      /**
       * @brief Pre-increment operator.
       *
       * @return A reference to this operator, incremented by one position.
       */
      Iterator& operator++();

      /**
       * @brief Pre-decrement operator.
       *
       * @return A reference to this operator, decremented by one position.
       */
      Iterator& operator--();

      /**
       * @brief Post-increment operator.
       *
       * @return A copy of this operator prior to this increment.
       */
      Iterator operator++(int);

      /**
       * @brief Post-decrement operator.
       *
       * @return A copy of this operator prior to this decrement.
       */
      Iterator operator--(int);

      /**
       * @brief Equality operator.
       *
       * @return True if this iterator is the same as in_other; false otherwise.
       */
      bool operator==(const Iterator& in_other) const;

      /**
       * @brief Inequality operator.
       *
       * @return True if this iterator is not the same as in_other; false otherwise.
       */
      bool operator!=(const Iterator& in_other) const;

      /**
       * @brief Dereference operator.
       *
       * @return A reference to the value this iterator is currently pointing at.
       */
      reference operator*() const;

   private:
      /**
       * The object that is being iterated.
       */
      const Object* m_parent;

      /**
       * @brief The current position of the iterator.
       */
      std::ptrdiff_t m_pos;

      // Let the parent class manipulate its iterators.
      friend class Object;
   };

   /**
    * @brief Reverse iterator for a JSON object.
    */
   typedef std::reverse_iterator<Iterator> ReverseIterator;

   /**
    * @brief Constructs an empty JSON object.
    */
   Object();

   /**
    * @brief Constructs a JSON object from a list of string pairs.
    *
    * @param in_strPairs    The list of string pairs from which to construct this object.
    */
   explicit Object(const StringPairList& in_strPairs);

   /**
    * @brief Copy constructor.
    *
    * @param in_other   The JSON object to copy from.
    */
   Object(const Object& in_other);

   /**
    * @brief Move constructor.
    *
    * @param in_other   The JSON object to move to this Object.
    */
   Object(Object&& in_other);

   /**
    * @brief Creates a JSON object from the given name and JSON value.
    *
    * @param in_name    The name of the JSON object.
    * @param in_value   The value of the JSON object.
    *
    * @return The newly created member.
    */
   static Member createMember(const std::string& in_name, const Value& in_value);

   /**
    * @brief Creates a JSON object which represents the schema defaults of the provided JSON schema string.
    *
    * @param in_schema              The JSON schema string to parse into a JSON object.
    * @param out_schemaDefaults     The parsed schema defaults. This object is not valid if an error is returned.
    *
    * @return Success if in_schema could be parsed; Error otherwise.
    */
   static Error getSchemaDefaults(const std::string& in_schema, Object& out_schemaDefaults);

   /**
    * @brief Merges two JSON objects together. Conflicts between the base and the overlay will be resolved by taking the
    *        value in the overlay.
    *
    * @param in_base        The base object to merge.
    * @param in_overlay     The overlay object to merge with the base.
    *
    * @return The merged object.
    */
   static Object mergeObjects(const Object& in_base, const Object& in_overlay);

   /**
    * @brief Assignment operator.
    *
    * @param in_other   The JSON object to copy from.
    *
    * @return A reference to this JSON object.
    */
   Object& operator=(const Object& in_other);

   /**
    * @brief Move operator.
    *
    * @param in_other   The JSON object to move from.
    *
    * @return A reference to this JSON object.
    */
   Object& operator=(Object&& in_other) noexcept;

   /**
    * @brief Accessor operator. Gets the value a member of this JSON object by name. If no such object exists, an empty
    *        JSON value will be returned.
    *
    * @param in_name    The name of the member to access.
    *
    * @return The value of the member with the specified name, if it exists; empty JSON value otherwise.
    */
   Value operator[](const char* in_name);

   /**
    * @brief Accessor operator. Gets the value a member of this JSON object by name. If no such object exists, an empty
    *        JSON value will be returned.
    *
    * @param in_name    The name of the member to access.
    *
    * @return The value of the member with the specified name, if it exists; empty JSON value otherwise.
    */
   Value operator[](const std::string& in_name);

   /**
    * @brief Finds a JSON member by name.
    *
    * @param in_name    The name of the member to find.
    *
    * @return If such a member exists, an iterator pointing to that member; the end iterator otherwise.
    */
   Iterator find(const char* in_name) const;

   /**
    * @brief Finds a JSON member by name.
    *
    * @param in_name    The name of the member to find.
    *
    * @return If such a member exists, an iterator pointing to that member; the end iterator otherwise.
    */
   Iterator find(const std::string& in_name) const;

   /**
    * @brief Gets an iterator pointing to the first member of this object.
    *
    * @return An iterator pointing to the first member of this object.
    */
   Iterator begin() const;

   /**
    * @brief Gets an iterator after the last member of this object.
    *
    * @return An iterator after the last member of this object.
    */
   Iterator end() const;

   /**
    * @brief Gets an iterator pointing to the last member of this object, which iterates in the reverse direction.
    *
    * @return A reverse iterator pointing to the last member of this object.
    */
   ReverseIterator rbegin() const;

   /**
    * @brief Gets an iterator before the first member of this object, which can be compared with an other
    *        ReverseIterator to determine when reverse iteration has ended.
    *
    * @return An iterator before the first member of this object.
    */
   ReverseIterator rend() const;

   /**
    * @brief Clears the JSON object.
    */
   void clear();

   /**
    * @brief Erases a member by name.
    *
    * @param in_name    The name of the member to erase.
    *
    * @return True if a member was erased; false otherwise.
    */
   bool erase(const char* in_name);

   /**
    * @brief Erases a member by name.
    *
    * @param in_name    The name of the member to erase.
    *
    * @return True if a member was erased; false otherwise.
    */
   bool erase(const std::string& in_name);

   /**
    * @brief Erases the member specified by the provided iterator.
    *
    * @param in_itr     The iterator pointing to the member to erase.
    *
    * @return An iterator pointing to the member immediately after the erased member.
    */
   Iterator erase(const Iterator& in_itr);

   /**
    * @brief Gets the number of members in the JSON object.
    *
    * @return The number of members in the JSON object.
    */
   size_t getSize() const;

   /**
    * @brief Checks whether this object has a member with the specified name.
    *
    * @param in_name    The name of the member for which to check.
    *
    * @return True if a member with the specified name exists; false otherwise.
    */
   bool hasMember(const char* in_name) const;

   /**
    * @brief Checks whether this object has a member with the specified name.
    *
    * @param in_name    The name of the member for which to check.
    *
    * @return True if a member with the specified name exists; false otherwise.
    */
   bool hasMember(const std::string& in_name) const;

   /**
    * @brief Inserts the specified member into this JSON object. If an object with the same name already exists, it will be
    *        overridden.
    *
    * @param in_name        The name of the JSON value to insert.
    * @param in_value       The value to insert.
    */
   void insert(const std::string& in_name, const Value& in_value);

   /**
    * @brief Inserts the specified member into this JSON object. If an object with the same name already exists, it will be
    *        overridden.
    *
    * @param in_member      The member to insert.
    */
   void insert(const Member& in_member);

   /**
    * @brief Checks whether the JSON object is empty.
    *
    * @return True if the JSON object has no members; false otherwise.
    */
   bool isEmpty() const;

   /**
    * @brief Converts this JSON object to a map with string keys and a list of string values.
    *
    * @param out_map    The converted map, on success.
    *
    * @return True if conversion succeeded; false otherwise.
    */
   bool toStringMap(StringListMap& out_map) const;

   /**
    * @brief Converts this JSON object to a list of string pairs.
    *
    * NOTE: This method will skip any members whose values are not string type.
    *
    * @return The string pairs represented in this object.
    */
   StringPairList toStringPairList() const;

private:
   /**
    * @brief Constructs a JSON object from a JSON value. The specified value should return Type::OBJECT from getType().
    *
    * @param in_value   The private implementation member of a JSON value which returns Type::OBJECT from getType();
    */
   explicit Object(ValueImplPtr in_value);

   friend class Value;
   friend class Iterator;
};

/**
 * @brief Class which represents a JSON array.
 */
class Array : public Value
{
public:

   /**
    * @brief Typedef required for the inheritance of std::iterator with a value_type of json::Value.
    */
   typedef Value value_type;

   /**
    * @brief Class which allows iterating over the elements of a JSON array.
    */
   class Iterator: public std::iterator<std::bidirectional_iterator_tag,   // iterator_category
      Value,                             // value_type
      std::ptrdiff_t,                    // difference_type
      const Value*,                      // pointer
      Value>                             // reference
   {
   public:
      /**
       * @brief Constructor.
       *
       * @param in_parent       The parent array which will be iterated.
       * @param in_startPos     The starting position of the iterator. Default: the first member.
       */
      explicit Iterator(const Array* in_parent, std::ptrdiff_t in_startPos = 0);

      /**
       * @brief Copy constructor.
       *
       * @param in_other    The iterator to copy.
       */
      Iterator(const Iterator& in_other) = default;

      /**
       * @brief Assignment operator.
       *
       * @param in_other    The iterator to copy.
       *
       * @return A reference to this iterator.
       */
      Iterator& operator=(const Iterator& in_other);

      /**
       * @brief Pre-increment operator.
       *
       * @return A reference to this operator, incremented by one position.
       */
      Iterator& operator++();

      /**
       * @brief Pre-decrement operator.
       *
       * @return A reference to this operator, decremented by one position.
       */
      Iterator& operator--();

      /**
       * @brief Post-increment operator.
       *
       * @return A copy of this operator prior to this increment.
       */
      Iterator operator++(int);

      /**
       * @brief Post-decrement operator.
       *
       * @return A copy of this operator prior to this decrement.
       */
      Iterator operator--(int);

      /**
       * @brief Equality operator.
       *
       * @return True if this iterator is the same as in_other; false otherwise.
       */
      bool operator==(const Iterator& in_other) const;

      /**
       * @brief Inequality operator.
       *
       * @return True if this iterator is not the same as in_other; false otherwise.
       */
      bool operator!=(const Iterator& in_other) const;

      /**
       * @brief Dereference operator.
       *
       * @return A reference to the value this iterator is currently pointing at.
       */
      reference operator*() const;

   private:
      /**
       * @brief The parent array that is being iterated.
       */
      const Array* m_parent;

      /**
       * @brief The current position of the iterator.
       */
      std::ptrdiff_t m_pos;

      // Allow the array class to manipulate its own iterators.
      friend class Array;
   };

   /**
    * @brief Reverse iterator for a JSON array.
    */
   typedef std::reverse_iterator<Iterator> ReverseIterator;

   /**
    * @brief Constructs an empty JSON array.
    */
   Array();

   /**
    * @brief Constructs a JSON array from a list of string pairs as an array of strings in the format "key=value".
    *
    * @param in_strPairs    The list of string pairs from which to construct this array.
    */
   explicit Array(const StringPairList& in_strPairs);

   /**
    * @brief Copy constructor.
    *
    * @param in_other   The JSON array to copy from.
    */
   Array(const Array& in_other);

   /**
    * @brief Move constructor.
    *
    * @param in_other   The JSON array to move to this Object.
    */
   Array(Array&& in_other);

   /**
    * @brief Assignment operator.
    *
    * @param in_other   The JSON array to copy from.
    *
    * @return A reference to this JSON array.
    */
   Array& operator=(const Array& in_other);

   /**
    * @brief Move operator.
    *
    * @param in_other   The JSON Array to move from.
    *
    * @return A reference to this JSON Array.
    */
   Array& operator=(Array&& in_other) noexcept;

   /**
    * @brief Accessor operator. Gets the JSON value at the specified position in the array.
    *
    * @param in_index   The position of the element to access.
    *
    * @throws std::out_of_range     If in_index is greater than or equal to the value returned by getSize().
    *
    * @return The value of the member with the specified name, if it exists; empty JSON value otherwise.
    */
   Value operator[](size_t in_index) const;

   /**
    * @brief Gets an iterator pointing to the first member of this array.
    *
    * @return An iterator pointing to the first member of this array.
    */
   Iterator begin() const;

   /**
    * @brief Gets an iterator after the last member of this array.
    *
    * @return An iterator after the last member of this array.
    */
   Iterator end() const;

   /**
    * @brief Gets an iterator pointing to the last member of this array, which iterates in the reverse direction.
    *
    * @return A reverse iterator pointing to the last member of this array.
    */
   ReverseIterator rbegin() const;

   /**
    * @brief Gets an iterator before the first member of this array, which can be compared with an other
    *        ReverseIterator to determine when reverse iteration has ended.
    *
    * @return An iterator before the first member of this array.
    */
   ReverseIterator rend() const;

   /**
    * @brief Clears the JSON array.
    */
   void clear();

   /**
    * @brief Erases the member specified by the provided iterator.
    *
    * @param in_itr     The iterator pointing to the member to erase.
    *
    * @return An iterator pointing to the member immediately after the erased member.
    */
   Iterator erase(const Iterator& in_itr);

   /**
    * @brief Erases a range of member specified by the provided iterators to the first and last members to erase.
    *
    * @param in_first       The iterator pointing to the first member to erase.
    * @param in_last        The iterator pointing to the last member to erase.
    *
    * @return An iterator pointing to the member immediately after the last erased member.
    */
   Iterator erase(const Iterator& in_first, const Iterator& in_last);

   /**
    * @brief Gets the value at the back of the JSON array.
    *
    * @return The value at the back of the JSON array or an empty value, if the array is emtpy.
    */
   Value getBack() const;

   /**
    * @brief Gets the value at the front of the JSON array.
    *
    * @return The value at the front of the JSON array or an empty value, if the array is emtpy.
    */
   Value getFront() const;

   /**
    * @brief Gets the value at the specified index of the JSON array.
    *
    * @param in_index   The index of the value to retrieve.
    *
    * @return The value at the specified index or an empty value if the index is out of bounds.
    */
   Value getValueAt(size_t in_index) const;

   /**
    * @brief Gets the number of values in the JSON array.
    *
    * @return The number of values in the JSON array.
    */
   size_t getSize() const;

   /**
    * @brief Checks whether the JSON array is empty.
    *
    * @return True if the JSON array has no members; false otherwise.
    */
   bool isEmpty() const;

   /**
    * @brief Pushes the value onto the end of the JSON array.
    *
    * MAINTENANCE NOTE: This method must be named in the STL style to work with STL functions and types such as
    * std::back_inserter.
    *
    * @param in_value   The value to push onto the end of the JSON array.
    */
   void push_back(const Value& in_value);

   /**
    * @brief Converts this JSON array to a set of strings.
    *
    * @param out_set    The set of strings.
    *
    * @return True if this array could be converted to a set of strings; false otherwise.
    */
   bool toSetString(std::set<std::string>& out_set) const;

   /**
    * @brief Converts this array into a vector of string pairs. Elements of the form "key=value" will be parsed into the
    *        pair <"key", "value">. Elements which are not in that format (e.g. "value") will be parsed as <"value", "">.
    *        Any elements of the array which are not strings will be skipped.
    *
    * @return The string elements of this JSON array as key value pairs.
    */
   StringPairList toStringPairList() const;

   /**
    * @brief Converts this JSON array to a vector of integers.
    *
    * @param out_set    The vector of integers.
    *
    * @return True if this array could be converted to a vector of integers; false otherwise.
    */
   bool toVectorInt(std::vector<int>& out_set) const;

   /**
    * @brief Converts this JSON array to a vector of strings.
    *
    * @param out_set    The vector of strings.
    *
    * @return True if this array could be converted to a vector of strings; false otherwise.
    */
   bool toVectorString(std::vector<std::string>& out_set) const;

private:
   /**
    * @brief Constructs a JSON array from a JSON value. The specified value should return Type::ARRAY from getType().
    *
    * @param in_value   A JSON value which returns Type::ARRAY from getType();
    */
   explicit Array(ValueImplPtr in_value);

   friend class Value;
};

template <typename T>
bool isType(const Value& in_value)
{ 
   if (in_value.isNull())
      return false;
   else if (std::is_same<T, Object>::value)
      return in_value.getType() == Type::OBJECT;
   else if (std::is_same<T, Array>::value)
      return in_value.getType() == Type::ARRAY;
   else if (std::is_same<T, std::string>::value)
      return in_value.getType() == Type::STRING;
   else if (std::is_same<T, bool>::value)
      return in_value.getType() == Type::BOOL;
   else if (std::is_same<T, int>::value)
      return in_value.getType() == Type::INTEGER;
   else if (std::is_same<T, unsigned int>::value)
      return in_value.getType() == Type::INTEGER;
   else if (std::is_same<T, int64_t>::value)
      return in_value.getType() == Type::INTEGER;
   else if (std::is_same<T, uint64_t>::value)
      return in_value.getType() == Type::INTEGER;
   else if (std::is_same<T, unsigned long>::value)
      return in_value.getType() == Type::INTEGER;
   else if (std::is_same<T, double>::value)
      return (in_value.getType() == Type::INTEGER) || (in_value.getType() == Type::REAL);
   else
      return false;
}

std::string typeAsString(Type in_type);
std::ostream& operator<<(std::ostream& io_ostream, Type in_type);

namespace detail {

template <typename T>
Type asJsonType(const T& in_object,
               std::true_type)
{
   return in_object.getType();
}

template <typename T>
Type asJsonType(const T& in_object,
               std::false_type)
{
   if (std::is_same<T, bool>::value)
      return Type::BOOL;
   else if (std::is_same<T, int>::value)
      return Type::INTEGER;
   else if (std::is_same<T, double>::value)
      return Type::REAL;
   else if (std::is_same<T, std::string>::value)
      return Type::STRING;
   
   log::logErrorMessage("Unexpected type");
   return Type::NULL_TYPE;
}

template <typename T>
struct is_json_type : public std::is_base_of<Value, T>
{
};

} // namespace detail

template <typename T>
Type asJsonType(const T& object)
{
   return detail::asJsonType(
            object,
            detail::is_json_type<T>());
}

inline std::string typeAsString(const Value& value)
{
   return typeAsString(value.getType());
}

namespace detail {

template <typename T>
inline Value toJsonValue(const T& val)
{
   return Value(val);
}

template <typename T>
inline Value toJsonValue(const boost::optional<T>& val)
{
   return val ? Value(*val) : Value();
}

} // namespace detail

template <typename T>
inline Value toJsonValue(const T& val)
{
   return detail::toJsonValue(val);
}

inline Value toJsonValue(const boost::optional<std::string>& val)
{
   return val ? Value(*val) : Value();
}

inline Value toJsonString(const std::string& val)
{
   return Value(val);
}

template<typename T>
Array toJsonArray(const std::vector<T>& vector)
{
   Array results;
   for (const T& val : vector)
   {
      results.push_back(Value(val));
   }
   return results;
}

template<typename T>
Array toJsonArray(const std::set<T>& set)
{
   Array results;
   for (const T& val : set)
   {
      results.push_back(Value(val));
   }
   return results;
}

} // namespace json
} // namespace core
} // namespace rstudio

#endif // SHARED_CORE_JSON_HPP

