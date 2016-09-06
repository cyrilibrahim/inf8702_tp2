
#include "StringUtils.h"

#include <cmath>
#include <sstream>
#include <algorithm>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////
///
///  Tokenize @a str using @a delimiters
///
///  @param [in]  str : source string
///  @param [in]  delimiters : delimiters each characters are checked
///                            individually.
///
///  @return a list of tokens
///
////////////////////////////////////////////////////////////////////////

std::vector<std::string> StringUtils::Tokenize( const std::string& str,
                                                const std::string& delimiters )
{
  std::vector<std::string> tokens;

  // skip delimiters at beginning.
  std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);

  // find first "non-delimiter".
  std::string::size_type pos = str.find_first_of(delimiters, lastPos);

  while (std::string::npos != pos || std::string::npos != lastPos)
  {
    // found a token, add it to the vector.
    tokens.push_back(str.substr(lastPos, pos - lastPos));

    // skip delimiters.  Note the "not_of"
    lastPos = str.find_first_not_of(delimiters, pos);

    // find next "non-delimiter"
    pos = str.find_first_of(delimiters, lastPos);
  }

  return tokens;
}

////////////////////////////////////////////////////////////////////////
///
///  Tokenize @a str using @a delimiters retaining empty fields between all
///  delimiters.
///
///  @param [in]  str : source string
///  @param [in]  delimiters : delimiters each characters are checked
///                            individually.
///
///  @return a list of tokens
///
////////////////////////////////////////////////////////////////////////
std::vector<std::string> StringUtils::Tokenize2(const std::string& str,
                                                const std::string& delimiters)
{
  std::vector<std::string> tokens;

  std::string::size_type lastPos = 0, pos = 0;
  int count = 0;

  if(str.length()<1)  return tokens;

  // skip delimiters at beginning.
  lastPos = str.find_first_not_of(delimiters, 0);

  if((str.substr(0, lastPos-pos).length()) > 0)
  {
    count = str.substr(0, lastPos-pos).length();

    for(int i=0; i < count; i++)
      tokens.push_back("");

    if(std::string::npos == lastPos)
      tokens.push_back("");
  }

  // find first "non-delimiter".
  pos = str.find_first_of(delimiters, lastPos);

  while (std::string::npos != pos || std::string::npos != lastPos)
  {
    // found a token, add it to the vector.
    tokens.push_back( str.substr(lastPos, pos - lastPos));

    // skip delimiters.  Note the "not_of"
    lastPos = str.find_first_not_of(delimiters, pos);

    if((std::string::npos != pos) && (str.substr(pos, lastPos-pos).length() > 1))
    {
      count = str.substr(pos, lastPos-pos).length();

      for(int i=0; i < count; i++)
        tokens.push_back("");
    }

    pos = str.find_first_of(delimiters, lastPos);
  }

  return tokens;
}

std::string StringUtils::TrimRight(const std::string& source,
                                    const std::string& t /*= " " */ )
{
  std::string str = source;
  return str.erase ( str.find_last_not_of ( t ) + 1 ) ;
}

std::string StringUtils::TrimLeft(const std::string& source,
                                   const std::string& t /*= " " */ )
{
  std::string str = source;
  return str.erase ( 0 , source.find_first_not_of ( t ) ) ;
}

std::string StringUtils::Trim(const std::string& source,
                              const std::string& t /*= " " */ )
{
  std::string str = source;
  return TrimLeft ( TrimRight ( str , t ) , t ) ;
}

void StringUtils::FindAndReplace(std::string& source,
                                 const std::string& find,
                                 const std::string& replace)
{
  size_t j;
  for (; (j = source.find(find)) != std::string::npos;)
  {
    source.replace(j, find.length(), replace);
  }
}

std::string StringUtils::BinaryToDecimal(const std::string& rhs)
{
  long sum = 0;
  for (std::string::const_iterator c = rhs.begin(),
                                   end = rhs.end(); c != end; ++c)
  {
    if (*c == '0')
    {
      sum <<= 1;
    }
    else if (*c == '1')
    {
      sum = (sum << 1) + 1;
    }
    else
    {
      sum = 0;
      break;
    }
  };

  std::stringstream ss;
  ss << sum;
  return ss.str();
}

std::string StringUtils::DecimalTobinary(const std::string& rhs)
{
  std::stringstream ss;
  ss << rhs;
  long l;
  ss >> l;
  return DecimalTobinary(l);
}

std::string StringUtils::DecimalTobinary(int l)
{
  return StringUtils::itoa(l, 2);
}

std::string StringUtils::itoa(int value, int base)
{

	enum { kMaxDigits = 35 };
	std::string buf;
	buf.reserve( kMaxDigits ); // Pre-allocate enough space.

	// check that the base if valid
	if (base < 2 || base > 16) return buf;

	int quotient = value;

	// Translating number to string with base:
	do {
		buf += "0123456789abcdef"[ std::abs( quotient % base ) ];
		quotient /= base;
	} while ( quotient );

	// Append the negative sign for base 10
	if ( value < 0 && base == 10) buf += '-';

	std::reverse( buf.begin(), buf.end() );
	return buf;
}

