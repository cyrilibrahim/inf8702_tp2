#ifndef stringutils_h__
#define stringutils_h__

#include <string>
#include <vector>


class StringUtils
{
public:

// General function

  /// Tokenizes @a str with delimiters
  static std::vector<std::string> Tokenize(
    const std::string& str,
    const std::string& delimiters);

  /// Tokenizes @a str with delimiters
  static std::vector<std::string> Tokenize2(
    const std::string& str,
    const std::string& delimiters);

  /// Trim right.
  static std::string TrimRight (
    const std::string& source,
    const std::string& t = " ");

  /// Trim left.
  static std::string TrimLeft (
    const std::string& source,
    const std::string& t = " ");

  /// Trim left and right.
  static std::string Trim (
    const std::string& source,
    const std::string& t = " ");

  /// Find and replace a string
  static void FindAndReplace(
    std::string& source,
    const std::string& find,
    const std::string& replace);

  /// Converts a binary number to a decimal based number
  static std::string BinaryToDecimal(const std::string& rhs);

  /// Converts a string decimal number to a binary based number
  static std::string DecimalTobinary(const std::string& rhs);

  /// Converts a decimal number to a binary based number
  static std::string DecimalTobinary(int l);

  /// C++ version std::string style "itoa"
  static std::string itoa(int value, int base);

private: // Prevent client to create StringUtils objects
  StringUtils(void);
  ~StringUtils(void);
};

#endif // stringutils_h__
