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


#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <qmap.h>
#include <qstring.h>
#include <qtextstream.h>

class AttrMap : public QMap<QString, QString>
{
public:
    AttrMap() { }
    AttrMap( const QString& name, const QString& value ) {
	insert( name, value );
    }
};

class XmlWriter
{
public:
    XmlWriter( QIODevice *device /*, QTextCodec *codec = 0 */);
    ~XmlWriter();

    void writeRaw( const QString& xml );
    void writeString( const QString& string );
    void writeOpenTag( const QString& name, const AttrMap& attrs = AttrMap() );
    void writeCloseTag( const QString& name );
    void writeAtomTag( const QString& name, const AttrMap& attrs = AttrMap() );
    void writeTaggedString( const QString& name, const QString& string,
			    const AttrMap& attrs = AttrMap() );
    void newLine();
    void setIndentSize( int size ) { indentSize = size; }
    void setAutoNewLine( bool on ) { autoNewLine = on; }

private:
    QString protect( const QString& string );
    QString opening( const QString& tag, const AttrMap& attrs = AttrMap() );
    void writePendingIndent();

    QTextStream out;
    QString indentStr;
    int indentSize;
    bool autoNewLine;
    bool atBeginningOfLine;
};

#endif
