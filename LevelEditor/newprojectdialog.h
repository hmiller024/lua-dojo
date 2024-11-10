/// newprojectdialog.h
///
/// File that creates a new popup window to ask for the size of a new project.
///
/// Author: Gavin Kerr, Hans Andersen, Hayden Miller, Solon Grover
/// Date: March 30, 2023

#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class NewProjectDialog;
}

class NewProjectDialog : public QDialog
{
    Q_OBJECT

public:

    /// @brief Default constructor for the QDialog
    /// @param QWidget *parent, default nullptr
    explicit NewProjectDialog(QWidget *parent = nullptr);

    /// @brief Deconstructor
    ~NewProjectDialog();

    /// @brief Returns the selected image size
    int getImageSize();

private slots:

    /// @brief Slot for when the OK button is clicked within
    /// the new dialog window
    void processOkClick();

private:

    Ui::NewProjectDialog *ui;
    int imgSize;

};

#endif // NEWPROJECTDIALOG_H
