#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Starts a new game upon button click.
    void onNewGameButtonClicked();

private:
    Ui::MainWindow *ui;
    Game *m_game;

    void initializeUi();

    // Updates the score box display.
    void onScoreUpdated(int score);
};
#endif // MAINWINDOW_H
