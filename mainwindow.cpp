#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QRegularExpressionMatch>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initial Button States
    ui->pushButtonAdd->setEnabled(true);
    ui->pushButtonUpdate->setEnabled(false);
    ui->pushButtonDelete->setEnabled(false);

    // Connect Slots
    connect(ui->pushButtonAdd, &QPushButton::clicked, this, &MainWindow::onAddClicked);
    connect(ui->pushButtonNext, &QPushButton::clicked, this, &MainWindow::onNextClicked);
    // Previous aur Search buttons ko connect kiya gaya
    connect(ui->pushButtonPrevious, &QPushButton::clicked, this, &MainWindow::onPreviousClicked);
    connect(ui->pushButtonSearch, &QPushButton::clicked, this, &MainWindow::onSearchClicked);

    connect(ui->pushButtonUpdate, &QPushButton::clicked, this, &MainWindow::onUpdateClicked);
    connect(ui->pushButtonDelete, &QPushButton::clicked, this, &MainWindow::onDeleteClicked);

    currentIndex = -1;

    // Load CSV
    QFile file("students.csv");
    if(file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        QString header = in.readLine();

        while(!in.atEnd()) {
            QString line = in.readLine();
            QStringList f = line.split(",");

            if(f.size() == 6) {
                students.append({f[0], f[1], f[2], f[3], f[4], f[5]});
            }
        }
        file.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ----------------------------------------------------
// Helper Functions
// ----------------------------------------------------

void MainWindow::clearFields() {
    ui->lineEditName->clear();
    ui->lineEditRoll->clear();
    ui->lineEditFather->clear();
    ui->lineEditCaste->clear();
    ui->lineEditDistrict->clear();
    ui->lineEditGPA->clear();
}

bool MainWindow::fieldError(QString field) {
    QMessageBox::warning(this, "Missing Field", field + " is required!");
    return false;
}

void MainWindow::saveAll() {
    QFile file("students.csv");
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&file);

        out << "Name,Roll,Father,Caste,District,GPA\n";
        for (auto &s : students)
            out << s.name << "," << s.roll << "," << s.father << ","
                << s.caste << "," << s.district << "," << s.gpa << "\n";

        file.close();
    }
}

bool MainWindow::rollExists(const QString &roll, int ignoreIndex) {
    for (int i = 0; i < students.size(); i++) {
        if (i == ignoreIndex) continue;
        if (students[i].roll.toUpper() == roll.toUpper())
            return true;
    }
    return false;
}

// ✅ Roll Number Format Validation Function
bool MainWindow::isValidRollFormat(const QString &roll) {
    // Format: X00XX000 (e.g., K25SW003) -> One Capital, Two Digits, Two Capitals, Three Digits
    QRegularExpression regex("^[A-Z]\\d{2}[A-Z]{2}\\d{3}$");
    if (!roll.contains(regex)) {
        QMessageBox::warning(this, "Format Error", "Roll Number must be in the exact format: X00XX000 (e.g., K25SW003).");
        return false;
    }
    return true;
}

// 🏠 Load Student Data to UI Fields
void MainWindow::loadStudentToFields(const Student &s) {
    ui->lineEditName->setText(s.name);
    ui->lineEditRoll->setText(s.roll);
    ui->lineEditFather->setText(s.father);
    ui->lineEditCaste->setText(s.caste);
    ui->lineEditDistrict->setText(s.district);
    ui->lineEditGPA->setText(s.gpa);

    // UI state ko 'View/Update' mode mein set karein
    ui->pushButtonAdd->setEnabled(false);
    ui->pushButtonUpdate->setEnabled(true);
    ui->pushButtonDelete->setEnabled(true);
}

// ----------------------------------------------------
// Main Validation (Roll Format Check is integrated here)
// ----------------------------------------------------

bool MainWindow::validateFields() {
    if (ui->lineEditName->text().isEmpty()) return fieldError("Name");
    if (ui->lineEditRoll->text().isEmpty()) return fieldError("Roll Number");

    // Format Validation
    if (!isValidRollFormat(ui->lineEditRoll->text())) return false;

    if (ui->lineEditFather->text().isEmpty()) return fieldError("Father Name");
    if (ui->lineEditCaste->text().isEmpty()) return fieldError("Caste");
    if (ui->lineEditDistrict->text().isEmpty()) return fieldError("District");
    if (ui->lineEditGPA->text().isEmpty()) return fieldError("GPA");
    return true;
}


// ----------------------------------------------------
// Slot Functions
// ----------------------------------------------------

void MainWindow::onAddClicked() {
    if (!validateFields()) return; // Validation includes format check

    QString roll = ui->lineEditRoll->text().toUpper(); // Roll ko Upper Case mein save karein

    if (rollExists(roll)) {
        QMessageBox::warning(this, "Duplicate Roll", "This Roll Number already exists!");
        return;
    }

    students.append({
        ui->lineEditName->text(),
        roll,
        ui->lineEditFather->text(),
        ui->lineEditCaste->text(),
        ui->lineEditDistrict->text(),
        ui->lineEditGPA->text()
    });

    saveAll();
    QMessageBox::information(this, "Added", "Record added successfully!");

    clearFields();
    ui->pushButtonAdd->setEnabled(true);
    ui->pushButtonUpdate->setEnabled(false);
    ui->pushButtonDelete->setEnabled(false);
    currentIndex = -1;
}

void MainWindow::onNextClicked() {
    if (students.isEmpty()) {
        QMessageBox::information(this, "Info", "No records available!");
        clearFields();
        return;
    }

    currentIndex = (currentIndex + 1) % students.size();
    loadStudentToFields(students[currentIndex]);
}

void MainWindow::onPreviousClicked() {
    if (students.isEmpty()) {
        QMessageBox::information(this, "Info", "No records available!");
        clearFields();
        return;
    }

    // Index ko ek qadam peeche le jao. Circular movement.
    if (currentIndex <= 0) {
        currentIndex = students.size() - 1;
    } else {
        currentIndex = currentIndex - 1;
    }

    loadStudentToFields(students[currentIndex]);
}

void MainWindow::onUpdateClicked() {
    if (currentIndex < 0 || currentIndex >= students.size()) return;
    if (!validateFields()) return;

    Student &s = students[currentIndex];

    QString oldRoll = s.roll;
    QString newRoll = ui->lineEditRoll->text().toUpper();

    // PRIMARY KEY PROTECTION
    if (oldRoll != newRoll) {
        QMessageBox::warning(this,
                             "Primary Key Error",
                             "You cannot change Roll Number (Primary Key) during update.");
        ui->lineEditRoll->setText(oldRoll);
        return;
    }

    // Update other fields only
    s.name = ui->lineEditName->text();
    s.father = ui->lineEditFather->text();
    s.caste = ui->lineEditCaste->text();
    s.district = ui->lineEditDistrict->text();
    s.gpa = ui->lineEditGPA->text();

    saveAll();

    QMessageBox::information(this, "Updated", "Record updated successfully!");
    clearFields();

    ui->pushButtonAdd->setEnabled(true);
    ui->pushButtonUpdate->setEnabled(false);
    ui->pushButtonDelete->setEnabled(false);
    currentIndex = -1;
}

void MainWindow::onDeleteClicked() {
    if (currentIndex < 0 || currentIndex >= students.size()) return;

    QString oldRoll = students[currentIndex].roll;
    QString enteredRoll = ui->lineEditRoll->text().toUpper();

    // PRIMARY KEY PROTECTION
    if (oldRoll != enteredRoll) {
        QMessageBox::warning(this,
                             "Primary Key Error",
                             "Record mismatch! Cannot delete.");
        ui->lineEditRoll->setText(oldRoll);
        return;
    }

    students.removeAt(currentIndex);
    saveAll();

    QMessageBox::information(this, "Deleted", "Record deleted successfully!");

    if (students.isEmpty()) {
        clearFields();
        ui->pushButtonAdd->setEnabled(true);
        ui->pushButtonUpdate->setEnabled(false);
        ui->pushButtonDelete->setEnabled(false);
        currentIndex = -1;
        return;
    }

    currentIndex %= students.size();
    onNextClicked();
}

// 🔍 Search Function
void MainWindow::onSearchClicked() {
    QString searchRoll = ui->lineEditRoll->text().trimmed();

    if (searchRoll.isEmpty()) {
        QMessageBox::warning(this, "Search Error", "Please enter a Roll Number to search.");
        return;
    }

    // Search karne se pehle format check karein
    if (!isValidRollFormat(searchRoll)) {
        return;
    }

    searchRoll = searchRoll.toUpper(); // Search term ko uppercase mein badal dein

    bool found = false;
    for (int i = 0; i < students.size(); ++i) {
        if (students[i].roll == searchRoll) { // Roll stored is already in Upper Case
            loadStudentToFields(students[i]);
            currentIndex = i;
            found = true;
            QMessageBox::information(this, "Record Found", "Student record successfully loaded.");
            break;
        }
    }

    if (!found) {
        QMessageBox::information(this, "Not Found", "No student found with Roll Number: " + searchRoll);
        clearFields();
        // UI state ko 'Add' mode mein set karein
        ui->pushButtonAdd->setEnabled(true);
        ui->pushButtonUpdate->setEnabled(false);
        ui->pushButtonDelete->setEnabled(false);
        currentIndex = -1;
    }
}
