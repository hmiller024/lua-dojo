#include "newprojectdialog.h"
#include "ui_newprojectdialog.h"

NewProjectDialog::NewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDialog)
{

    ui->setupUi(this);

    imgSize = 32;

    connect(ui->dialogButtonBox, &QDialogButtonBox::accepted, this, &NewProjectDialog::processOkClick);

}

NewProjectDialog::~NewProjectDialog()
{
    delete ui;
}

int NewProjectDialog::getImageSize()
{
    return imgSize;
}

void NewProjectDialog::processOkClick()
{

    if (ui->pixelSize->text().toInt() < 2 || ui->pixelSize->text().toInt() > 256) {

        QMessageBox msgBox;
        msgBox.setText("Please choose a range between 2-256 and try again");
        msgBox.exec();

    } else {
        imgSize = ui->pixelSize->text().toInt();

        close();
    }

}
