#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QRegularExpression> // For Roll Number Format Validation

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// ============================
// Student Structure
// ============================
struct Student {
    QString name;
    QString roll;      // PRIMARY KEY
    QString father;
    QString caste;
    QString district;
    QString gpa;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddClicked();
    void onNextClicked();
    void onPreviousClicked(); // ⏪ Previous Button
    void onUpdateClicked();
    void onDeleteClicked();
    void onSearchClicked();   // 🔍 Search Button

private:
    Ui::MainWindow *ui;

    QVector<Student> students;
    int currentIndex;

    // ---------- Helpers ----------
    void clearFields();
    bool validateFields();
    bool fieldError(QString field);
    void saveAll();
    bool rollExists(const QString &roll, int ignoreIndex = -1);

    // ✅ Roll Number Format Validation Helper
    bool isValidRollFormat(const QString &roll);

    // 🏠 Helper to load student data onto UI fields
    void loadStudentToFields(const Student &s);
};

#endif // MAINWINDOW_H
