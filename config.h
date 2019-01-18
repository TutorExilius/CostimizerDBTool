#ifndef CONFIG_H
#define CONFIG_H

#include <QMap>
#include <QString>

class Config
{
public:
    // constructors ---
    Config( const QString &configFile );
    // ---

    Config& operator=( const Config &obj );
    QString& operator[]( const QString &key );

    bool keyExists( const QString &key ) const;
    bool writeConfigFile() const;

    QString getValueOf( const QString &key ) const;

private:
    // helper ---
    bool loadConfigFile();
    // ---

    QString configFile;
    QMap<QString,QString> settings;
};

#endif // CONFIG_H
