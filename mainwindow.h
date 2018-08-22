#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMimeData>
#include <QClipboard>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void pushClipboard(unsigned index);
    void popClipboard(unsigned index);

private:
    Ui::MainWindow *ui;

    QVector<QString> multiple_buffer;

    QClipboard *clipboard;
    const QMimeData *mime_data;

    void clipboardDataChanged();
    void keyPressEvent(QKeyEvent *event);

};

#endif // MAINWINDOW_H
