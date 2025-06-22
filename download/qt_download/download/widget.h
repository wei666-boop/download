#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_download_button_clicked();

    void on_savebutton_clicked();

    void on_browser_download_clicked();

    void on_thread_stateChanged(int arg1);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
