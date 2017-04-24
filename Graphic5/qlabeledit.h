#ifndef QLABELEDIT_H
#define QLABELEDIT_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QString>
#include <QValidator>

#define MARGIN 7

class QLabelEdit : public QWidget
{
    Q_OBJECT
private:
    QLabel *label;
    QLineEdit *edit;
    QHBoxLayout *layout;
    QString string;
public:
    explicit QLabelEdit(QWidget *parent = 0);
    QLabelEdit(const QString text = "", QWidget *parent = 0);
    QString getEditText(void);
    void setEditText(const QString);
    void setLabelText(const QString);
    void setEditValidator(const QValidator*);

signals:
    void edited(QString);
public slots:
    void changeEditText(QString);
};

#endif // QLABELEDIT_H
