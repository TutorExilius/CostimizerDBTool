#include "config.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

// constructors ---
Config::Config( const QString &configFile )
: configFile{ configFile }
{
    if( !this->loadConfigFile() )
    {
        throw QString{ "Error while loading configFile: '"+ configFile +"'" };
    }
}
// ---

Config& Config::operator=( const Config &obj )
{
    this->configFile = obj.configFile;
    this->settings = obj.settings;

    return *this;
}

QString& Config::operator[]( const QString &key )
{
    if( !this->keyExists( key ) )
    {
        throw QString{ "Missing 'Database' entry in config.txt" };
    }

    return this->settings[key];
}

bool Config::writeConfigFile() const
{
    QFile file( this->configFile );
    if( !file.open( QFile::WriteOnly|QFile::Text ) )
    {
        qDebug() << " Could not open the file for writing";
        return false;
    }

    QTextStream out(&file);

    for( auto settingKey : this->settings.keys() )
    {
        const QString keyValPair = settingKey + ":" +  this->settings.value(settingKey);
        out << keyValPair << '\n';
    }

    file.close();

    return true;
}

QString Config::getValueOf( const QString &key ) const
{
    if( !this->keyExists( key ) )
    {
        throw QString{ "Missing 'Database' entry in config.txt" };
    }

    return this->settings[key];
}

bool Config::keyExists( const QString &key ) const
{
    return this->settings.contains( key );
}

// helper ---
bool Config::loadConfigFile()
{
    QFile file( this->configFile );
    if( !file.open( QFile::ReadOnly|QFile::Text ) )
    {
        qDebug() << " Could not open the file for reading";
        return false;
    }

    QStringList stringList;

    while( !file.atEnd() )
    {
        QString line = file.readLine().trimmed();

        if( !line.isEmpty() )
        {
            stringList.append( line.trimmed() );
        }
    }

    file.close();

    // Fill setting-Map
    foreach( QString line, stringList )
    {
        if( !line.startsWith( '#' ) )
        {
            // TODO: pos of doublepoint should be validated!
            int pos = line.indexOf(':');

            QString key = line.mid( 0, pos );
            QString value = line.mid( pos+1 );

            this->settings.insert( key, value );
        }
    }

    return true;
}
// ---
