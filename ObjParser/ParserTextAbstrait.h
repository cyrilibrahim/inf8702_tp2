#ifndef __PARSER_TEXT_ABSTRAIT__
#define __PARSER_TEXT_ABSTRAIT__

#include <fstream>
using namespace std;

class CParserTextAbstrait
{
	public:
		CParserTextAbstrait( void );
		virtual ~CParserTextAbstrait( void );

		bool OpenFile( const string& Filename );
		void CloseFile( void );
		
		virtual void ParseFile( void ) = 0;

	protected:
		string  m_Filename;
	    fstream m_FileStream;
		bool	m_IsOpen;
};

#endif
