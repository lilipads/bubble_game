#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

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
    QSettings m_settings = QSettings(/*organization=*/"game", /*application=*/"bubble");
    const QString m_record_score_key = "record_score";
    int m_record_score = 0;

    Ui::MainWindow *ui;
    Game *m_game;

    void initializeUi();

    // Updates the score box display.
    void onScoreUpdated(int score);

    // Updates the record if `score` is higher than the current record.
    void maybeUpdateRecordScore(int score);

    // Returns the highest score in record. If no record, return 0.
    int getRecordScore() const;
};
#endif // MAINWINDOW_H
