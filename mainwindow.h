#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMimeData>
#include <QClipboard>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void pushClipboard();
    void popClipboard();

private:
    Ui::MainWindow *ui;

    QStringList multiple_buffer;
    QClipboard *clipboard;
    const QMimeData *mime_data;

    void clipboardDataChanged();

};

#endif // MAINWINDOW_H
