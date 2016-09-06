#include "ParserTextAbstrait.h"

CParserTextAbstrait::CParserTextAbstrait( void )
	: m_Filename( "" )
	, m_FileStream()
	, m_IsOpen( false )
{
}

CParserTextAbstrait::~CParserTextAbstrait( void )
{
	
}	

bool CParserTextAbstrait::OpenFile( const string& Filename )
{
	m_Filename = Filename;
	m_FileStream.open( Filename.c_str(), ios::in );

	m_IsOpen = m_FileStream.is_open();

	return m_IsOpen;
}

void CParserTextAbstrait::CloseFile( void )
{
	if( m_IsOpen )
	{
		m_FileStream.close();
		m_IsOpen = false;
		m_Filename.clear();
	}
}
