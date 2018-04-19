#ifndef WORDIFIER_H
#define WORDIFIER_H


#include <QStyledItemDelegate>
#include <QVariant>

class Wordifier : public QStyledItemDelegate{
    Q_DISABLE_COPY(Wordifier)
public:
    Wordifier(QObject* parent = Q_NULLPTR) : QStyledItemDelegate(parent){}
    QString displayText(const QVariant &value, const QLocale &locale) const Q_DECL_OVERRIDE{
        if(value.canConvert(QMetaType::Int)){
            switch(value.toInt()){
                case 0: return QStringLiteral("Zero"); break;
                case 1: return QStringLiteral("One"); break;
                case 2: return QStringLiteral("Two"); break;
                case 3: return QStringLiteral("Three"); break;
                case 4: return QStringLiteral("Four"); break;

                //default: break;
            }
        }
        return QStyledItemDelegate::displayText(value,locale);
    }
};


#endif // WORDIFIER_H
