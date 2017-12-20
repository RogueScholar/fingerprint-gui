/*
    Copyright (C) 1992-2003 Trolltech AS. All Rights Reserved.

    This file ("Example Code"), is part of an example program for Qt,
    and is licensed under the Qt Commercial License Agreement,
    Agreement version 2.4 and higher as well as under the GPL.

    The Example Code is licensed to you "as is" without warranty of
    any kind. To the maximum extent permitted by applicable law,
    Trolltech on behalf of itself and its suppliers, disclaims all
    warranties express or implied, including, but not limited to,
    implied warranties of merchantability and fitness for a particular
    purpose with regard to the Example Code. Trolltech does not
    warrant that the Example Code will satisfy your requirements or
    that it is without defect or error or that the operation thereof
    will be uninterrupted. All use of and reliance on the Example Code
    is at the sole risk of and responsibility of you and your
    customers.

    If you are a holder of a Qt Commercial License Agreement, you can
    use the code under that agreement or you can use it under GPL. If
    you are not a holder of a Qt Commercial License Agreement, you can
    use the code under the GPL. Regardless of the applicable license
    agreement, the Example Code may be used, distributed and modified
    without limitation.
*/


#include <qtextcodec.h>

#include "xmlwriter.h"

XmlWriter::XmlWriter( QIODevice *device/*, QTextCodec *codec */)
    : indentSize( 4 ), autoNewLine( false ), atBeginningOfLine( true )
{
    out.setDevice( device );
//    if ( codec == 0 ) {
//	out.setEncoding( QTextStream::UnicodeUTF8 );
//    } else {
//	out.setCodec( codec );
//	out << "<?xml version=\"1.0\" encoding=\""
//	    << protect( codec->mimeName() ) << "\"?>\n";
//    }
}

XmlWriter::~XmlWriter()
{
    if ( autoNewLine && !atBeginningOfLine )
	out << endl;
}

QString XmlWriter::protect( const QString& string )
{
    QString s = string;
    s.replace( "&", "&amp;" );
    s.replace( ">", "&gt;" );
    s.replace( "<", "&lt;" );
    s.replace( "\"", "&quot;" );
    s.replace( "\'", "&apos;" );
    return s;
}

QString XmlWriter::opening( const QString& tag, const AttrMap& attrs )
{
    QString s = "<" + tag;
    AttrMap::ConstIterator a = attrs.begin();
    while ( a != attrs.end() ) {
	s += " " + a.key() + "=\"" + protect( *a ) + "\"";
	++a;
    }
    s += ">";
    return s;
}

void XmlWriter::writePendingIndent()
{
    if ( atBeginningOfLine ) {
	out << indentStr;
	atBeginningOfLine = false;
    }
}

void XmlWriter::newLine()
{
    out << endl;
    atBeginningOfLine = true;
}

void XmlWriter::writeRaw( const QString& xml )
{
    out << xml;
    atBeginningOfLine = false;
}

void XmlWriter::writeString( const QString& string )
{
    out << protect( string );
    atBeginningOfLine = false;
}

void XmlWriter::writeOpenTag( const QString& name, const AttrMap& attrs )
{
    writePendingIndent();
    out << opening( name, attrs );
    indentStr += QString().fill( ' ', indentSize );
    if ( autoNewLine )
	newLine();
}

void XmlWriter::writeCloseTag( const QString& name )
{
    indentStr = indentStr.mid( indentSize );
    writePendingIndent();
    out << opening( "/" + name );
    if ( autoNewLine )
	newLine();
}

void XmlWriter::writeAtomTag( const QString& name, const AttrMap& attrs )
{
    writePendingIndent();
    QString atom = opening( name, attrs );
    atom.insert( atom.length() - 1, "/" );
    out << atom;
    if ( autoNewLine )
	newLine();
}

void XmlWriter::writeTaggedString( const QString& name, const QString& string,
				   const AttrMap& attrs )
{
    writePendingIndent();
    out << opening( name, attrs );
    writeString( string );
    out << opening( "/" + name );
    if ( autoNewLine )
	newLine();
}
