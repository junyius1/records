#include "notemodeldata.h"
#include <QXmlStreamReader>

void LineStringModelData::data2QVariant(QVariant &variant)
{
    QString str;
    for(QList<QVariant>::iterator it =_noteData.begin(); it!= _noteData.end(); it++)
    {
        str += it->toString();
        str.push_back('\n');
    }
    variant.setValue(str);
}

void LineStringModelData::qVariant2Data(const QVariant &variant)
{
    QString str = variant.toString();
    QStringList t = str.split('\n');
    for(QStringList::iterator it =t.begin(); it!= t.end(); it++)
    {
        _noteData.push_back(*it);
    }
}

void XmlStringModelData::data2QVariant(QVariant &variant)
{
    QString s;
    QXmlStreamWriter writer(&s);
    writer.setCodec("UTF-8");
    writer.writeStartDocument();
    writer.writeStartElement(QLatin1String("MultiItems"));
    for(QList<QVariant>::iterator it =_noteData.begin(); it!= _noteData.end(); it++)
    {
        writer.writeStartElement(QLatin1String("Item"));
        writer.writeTextElement(QLatin1String("Content"), it->toString());
        writer.writeEndElement();
    }
    writer.writeEndDocument();
    variant.setValue<QString>(s);
}

void XmlStringModelData::qVariant2Data(const QVariant &variant)
{
    QString str = variant.toString();
    QXmlStreamReader reader(str);


    //file.close();
    //read a token in input stream
    reader.readNext();
    while(!reader.atEnd())
    {
        if(reader.isStartElement())
        {
            if(QLatin1String("MultiItems") == reader.name())
            {
                //if item, read next token
                reader.readNext();

                //read file main part
                while(!reader.atEnd())
                {
                    //if read close token </Root>
                    if(reader.isEndElement())
                    {
                        reader.readNext();
                        break;
                    }
                    //if read new <Item> start the token
                    if(reader.isStartElement())
                    {
                        //if read new <Item> start the token
                        if(QLatin1String("Item") == reader.name())
                        {
                            reader.readNext();
                            QString s;
                            while(!reader.atEnd())
                            {
                                //if read close token </Item>,break the loop
                                if(QLatin1String("Item") == reader.name() && reader.isEndElement())
                                {
                                    reader.readNext();
                                    break;
                                }

                                //if read new <Content> start the token
                                if(reader.isStartElement())
                                {
                                    //if read new Content token
                                    if(QLatin1String("Content") == reader.name())
                                    {
                                        qint64 start = reader.characterOffset();
                                        qint64 end = start;
                                        while(!reader.atEnd()){
                                            reader.readNext();
                                            if(QLatin1String("Content") == reader.name() && reader.isEndElement())
                                            {
                                                reader.readNext();
                                                break;
                                            } else{
                                                end = reader.characterOffset();
                                                if(reader.isCharacters())
                                                {
                                                    end =end-1;
                                                }
                                            }
                                        }
                                        QString content = str.mid(static_cast<int>(start), static_cast<int>(end -start));
                                        _noteData.push_back(content);
                                    }else if(QLatin1String("Link") ==  reader.name()){
                                        QString link = reader.readElementText();
                                    }
                                    reader.readNext();
                                }else {
                                    reader.readNext();
                                }
                            }
                        }
                    }else {
                        reader.readNext();
                    }
                }

            }else{
                reader.raiseError(QObject::tr("Not a Root file"));
                break;
            }

        }else{
            reader.readNext();
        }

    }

}
